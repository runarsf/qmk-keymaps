#!/usr/bin/env dash
# TODO #!/usr/bin/env bash
set -o errexit
set -o nounset

__DIR="$( cd -- "$(dirname "${0}")" >/dev/null 2>&1 ; pwd -P )"
FIRMWARE_DIR="$(realpath "${__DIR}/qmk_firmware")"
KEYMAPS_DIR="$(realpath "${__DIR}/keymaps")"

prompt () { # {{{
  _msg="${1:-Continue?}"
  printf '%s' "${_msg} [Y/n] " >&2
  read -r REPLY </dev/tty
  case "${REPLY}" in
    [Yy]*|"") return 0; break;;
    [Nn]*) return 1;;
    *) prompt 'Please answer yes or no...';;
  esac
} # }}}

firmware_lock() { # {{{
  cd "${FIRMWARE_DIR}"
  git config advice.detachedHead false
  if test -f "${__DIR}/keymaps/mylayout/firmware.lock"; then
    FIRMWARE_LOCK_HASH="$(cat "${__DIR}/keymaps/mylayout/firmware.lock" | head -1)"
    git checkout "${FIRMWARE_LOCK_HASH}"
  else
    if test ! -d "${FIRMWARE_DIR}"; then
      git clone "https://github.com/qmk/qmk_firmware" "${FIRMWARE_DIR}"
    elif prompt "No firmware lockfile found, update QMK firmware to the latest version?"; then
      git checkout master
      git --git-dir "${FIRMWARE_DIR}/.git" pull
    fi
    git rev-parse --short HEAD > "${__DIR}/keymaps/mylayout/firmware.lock"
  fi
  cd "${__DIR}"
} # }}}

known_keymaps() { # keymap -> KEYBOARD, KEYMAP, BOOTLOADER, MAKE_COMMAND {{{
  KEYMAP="${1}"
  case "${KEYMAP}" in
    mylayout)
      _KEYBOARD=preonic/rev3_drop
      _TARGET=dfu-util;;
    *)
      if test ! -d "${KEYMAPS_DIR}/${KEYMAP}" -o -z "${KEYBOARD}"; then
        printf '%s\n' "Error: Unknown or not properly formatted keymap: ${KEYMAP}"
        exit 1
      fi;;
  esac
  : "${KEYBOARD:=${_KEYBOARD}}"
  : "${TARGET:=${FLASH:+${_TARGET}}}"
} # }}}

parse_make_command() { # make_command -> KEYBOARD, KEYMAP, TARGET, MAKE_COMMAND {{{
  MAKE_COMMAND="${1}"
  KEYBOARD="$(printf '%s' "${1}" | awk '{split($0,a,":"); print a[1]}')"
  KEYMAP="$(printf '%s' "${1}" | awk '{split($0,a,":"); print a[2]}')"
  : "${TARGET:=$(printf '%s' "${1}" | awk '{split($0,a,":"); print a[3]}')}"
} # }}}

arrstash () { # {{{
  for i; do
    printf '%s\n' "${i}" | sed "s/'/'\\\\''/g;1s/^/'/;\$s/\$/' \\\\/"
  done
  printf ' \n'
} # }}}

# Argument parsing {{{
RUNTIME="docker" POSITIONALS="" FLASH="" TARGET="" KEYBOARD="" KEYMAP=""
while test "${#}" -gt "0"; do
  case "$(printf '%s' "${1}" | tr '[:upper:]' '[:lower:]')" in
    # -h|--help)
    -l|--local) RUNTIME="local";;
    -d|--docker) RUNTIME="docker";;
    -p|--podman) RUNTIME="podman";;
    -f|--flash) FLASH="true";;
    -t|--target|-b|--build)
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
MAKE_COMMAND="${KEYBOARD}:${KEYMAP}${TARGET:+:${TARGET}}"
KEYMAP_BIN="$(printf '%s' "${KEYBOARD}_${KEYMAP}" | sed -e 's/[^A-Za-z0-9._-]/_/g').bin"
FIRMWARE_KEYMAPS_DIR="$(realpath "${FIRMWARE_DIR}/keyboards/${KEYBOARD}/keymaps")"
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

main() { # {{{
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
        # FIXME
        # TODO Flash binary file
        qmk flash "${KEYMAP_BIN}" --bootloader "${TARGET}"
      fi;;
  esac
} # }}}

firmware_lock
main

printf '\n%s\n' "Done! You can find the built files in ${FIRMWARE_DIR}/.build"
