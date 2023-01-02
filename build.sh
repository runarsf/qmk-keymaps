#!/usr/bin/env dash
set -o errexit
set -o nounset

# Argument parsing {{{
known_keymaps() { # keymap -> KEYBOARD, KEYMAP, BOOTLOADER, MAKE_COMMAND
  KEYMAP="${1}"
  case "${KEYMAP}" in
    mylayout)
      _KEYBOARD=preonic/rev3
      _TARGET=dfu-util;;
    *)
      if test ! -d "${KEYMAPS_DIR}/${KEYMAP}" -o -z "${KEYBOARD}"; then
        printf '%s\n' "Error: Unknown or not properly formatted keymap: ${KEYMAP}"
        exit 1
      fi;;
  esac
  : "${KEYBOARD:=${_KEYBOARD}}"
  : "${TARGET:=${FLASH:+${_TARGET}}}"
}

parse_make_command() { # make_command -> KEYBOARD, KEYMAP, TARGET, MAKE_COMMAND
  MAKE_COMMAND="${1}"
  KEYBOARD="$(printf '%s' "${1}" | awk '{split($0,a,":"); print a[1]}')"
  KEYMAP="$(printf '%s' "${1}" | awk '{split($0,a,":"); print a[2]}')"
  : "${TARGET:=$(printf '%s' "${1}" | awk '{split($0,a,":"); print a[3]}')}"
}

arrstash () {
  for i; do
    printf '%s\n' "${i}" | sed "s/'/'\\\\''/g;1s/^/'/;\$s/\$/' \\\\/"
  done
  printf ' \n'
}

RUNTIME="docker" POSITIONALS="" FLASH="" TARGET="" KEYBOARD="" KEYMAP=""
while test "${#}" -gt "0"; do
  case "$(printf '%s' "${1}" | tr '[:upper:]' '[:lower:]')" in
    # -h|--help)
    -l|--local) RUNTIME="local";;
    -d|--docker) RUNTIME="docker";;
    -p|--podman) RUNTIME="podman";;
    -f|--flash) FLASH="true";;
    -t|--target)
      TARGET="${2}"
      shift;;
    -k|--keyboard)
      KEYBOARD="${2}"
      shift;;
    --*)
      printf '%s\n' "Unknown option: ${1}"
      exit 1;;
    -*)
      shortOptions="${1}"
      if test "${#shortOptions}" -le "2"; then
        printf '%s\n' "Unknown option: ${1}"
        exit 1
      fi
      shift
      set -- \
        "placeholder" \
        "$(printf '%s' "${shortOptions}" | cut -c-2)" \
        "-$(printf '%s' "${shortOptions}" | cut -c3-)" \
        "${@}";;
    *)
      _shopts="$(arrstash ${@})"
      eval "set -- ${POSITIONALS} ${1}"
      POSITIONALS="$(arrstash ${@})"
      eval "set -- ${_shopts}";;
  esac
  shift
done

eval "set -- ${POSITIONALS}"

if test "${#}" -le "0"; then
  printf '%s\n' "Missing layout or make-string."
  exit 1
fi

if test "${1#*:}" != "${1}"; then
  parse_make_command "${1}"
else
  known_keymaps "${1}"
fi

FIRMWARE_DIR="./qmk_firmware"
MAKE_COMMAND="${KEYBOARD}:${KEYMAP}${TARGET:+:${TARGET}}"
KEYMAP_BIN="$(printf '%s' "${KEYBOARD}_${KEYMAP}" | sed -e 's/[^A-Za-z0-9._-]/_/g').bin"
KEYMAPS_DIR="./keymaps"
FIRMWARE_KEYMAPS_DIR="${FIRMWARE_DIR}/keyboards/${KEYBOARD}/keymaps"
# }}}

printf '%-21s| %s\n' \
  "KEYBOARD" "${KEYBOARD}" \
  "KEYMAP" "${KEYMAP}" \
  "KEYMAP_BIN" "${KEYMAP_BIN}" \
  "KEYMAPS_DIR" "${KEYMAPS_DIR}" \
  "FIRMWARE_KEYMAPS_DIR" "${FIRMWARE_KEYMAPS_DIR}" \
  "RUNTIME" "${RUNTIME}" \
  "FLASH" "${FLASH}" \
  "TARGET" "${TARGET}" \
  "MAKE_COMMAND" "${MAKE_COMMAND}"

# git submodule update --init --recursive --remote "${FIRMWARE_DIR}"
git submodule update --remote "${FIRMWARE_DIR}"
make --directory="${FIRMWARE_DIR}" git-submodule
rm -rf "${FIRMWARE_DIR}/.build"
mkdir -p "${FIRMWARE_KEYMAPS_DIR}"
rm -rf "${FIRMWARE_KEYMAPS_DIR}/${KEYMAP}"
cp -r "${KEYMAPS_DIR}/${KEYMAP}" "${FIRMWARE_KEYMAPS_DIR}"
rm -f "${FIRMWARE_DIR}/${KEYMAP_BIN}"

cd "${FIRMWARE_DIR}"

case "${RUNTIME}" in
  docker|podman) RUNTIME="${RUNTIME}" ./util/docker_build.sh "${MAKE_COMMAND}";;
  local)
    make "${MAKE_COMMAND}"
    if test -n "${TARGET}"; then
      # TODO python3 -m pip install -r /qmk_firmware/requirements.txt
      qmk flash "${KEYMAP_BIN}" --bootloader "${TARGET}"
    fi;;
esac

printf '%s\n' "Build finished! You can find the built files in ${FIRMWARE_DIR}/.build"
