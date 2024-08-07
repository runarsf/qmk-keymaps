#!/usr/bin/env bash

set -o errexit
set -o nounset
set -o pipefail

# TODO migrate to userspace (QMK_USER) instead of KEYMAP
# TODO image extension (hex/bin)

__DIR="$( cd -- "$(dirname "${0}")" >/dev/null 2>&1 ; pwd -P )"
FIRMWARE_DIR="$(realpath "${__DIR}/qmk_firmware")"
KEYMAPS_DIR="$(realpath "${__DIR}/keymaps")"

known_keymaps() { # keymap -> KEYBOARD, KEYMAP, BOOTLOADER, MAKE_COMMAND {{{
  KEYMAP="${1}"
  case "${KEYMAP}" in
    preonic)
      _KEYBOARD=preonic/rev3_drop
      _TARGET=dfu-util;;
    planck)
      _KEYBOARD=planck/ez/glow
      _TARGET=dfu-util;;
    air40)
      _KEYBOARD='ymdk/ymd40/air40'
      _TARGET=flash
      _EXTENSION='hex'
      ;;
    *)
      if test ! -d "${KEYMAPS_DIR}/${KEYMAP}" -o -z "${KEYBOARD}"; then
        printf '%s\n' "Error: Unknown or not properly formatted keymap: ${KEYMAP}"
        exit 1
      fi;;
  esac
  : "${KEYBOARD:=${_KEYBOARD}}"
  : "${TARGET:=${FLASH:+${_TARGET}}}"
  : "${EXTENSION:=${_EXTENSION:-bin}}"
} # }}}

prompt () { # {{{
  _msg="${1:-Continue?}"
  printf '%s' "${_msg} [Y/n] " >&2
  read -r REPLY </dev/tty
  case "${REPLY}" in
    [Yy]*|"") return 0;;
    [Nn]*) return 1;;
    *) prompt 'Please answer yes or no...';;
  esac
} # }}}

# TODO Only checkout if git hashes diverge
# TODO Use --git-dir for all git commands
firmware_lock() { # {{{
  if test ! -d "${FIRMWARE_DIR}"; then
    git clone "https://github.com/qmk/qmk_firmware" "${FIRMWARE_DIR}"
  fi
  cd "${FIRMWARE_DIR}"
  git config advice.detachedHead false
  if test -f "${KEYMAPS_DIR}/${KEYMAP}/firmware.lock"; then
    FIRMWARE_LOCK_HASH="$(cat "${KEYMAPS_DIR}/${KEYMAP}/firmware.lock" | head -1)"
    git checkout "${FIRMWARE_LOCK_HASH}"
  else
    if prompt "No firmware lockfile found, update QMK firmware to the latest version?"; then
      git checkout master
      git --git-dir "${FIRMWARE_DIR}/.git" pull
    fi
    git rev-parse HEAD > "${KEYMAPS_DIR}/${KEYMAP}/firmware.lock"
  fi
  cd "${__DIR}"
} # }}}

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
RUNTIME="docker" QMK_USER="${USER}" EXTENSION="" POSITIONALS="" FLASH="" TARGET="" KEYBOARD="" KEYMAP=""
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
    -e|--extension)
      EXTENSION="${2}"
      shift;;
    -u|--user)
      QMK_USER="${2}"
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
MAKE_COMMAND="${KEYBOARD}:${QMK_USER}${TARGET:+:${TARGET}}"
KEYMAP_DIR="${KEYMAPS_DIR}/${KEYMAP}"
KEYMAP_BIN="$(printf '%s' "${KEYBOARD}_${QMK_USER}" | sed -e 's/[^A-Za-z0-9._-]/_/g').${EXTENSION}"
USERSPACE_DIR=$(readlink -m "${__DIR}/common")
FIRMWARE_KEYMAPS_DIR="$(readlink -m "${FIRMWARE_DIR}/keyboards/${KEYBOARD}/keymaps")"
FIRMWARE_KEYMAP_DIR="${FIRMWARE_KEYMAPS_DIR}/${QMK_USER}"
FIRMWARE_USERSPACES_DIR="$(readlink -m "${FIRMWARE_DIR}/users")"
FIRMWARE_USERSPACE_DIR="${FIRMWARE_USERSPACES_DIR}/${QMK_USER}"
# }}}

printf '%-23s | %s\n' \
  "KEYBOARD" "${KEYBOARD}" \
  "KEYMAP" "${KEYMAP}" \
  "KEYMAP_BIN" "${KEYMAP_BIN}" \
  "KEYMAPS_DIR" "${KEYMAPS_DIR}" \
  "KEYMAP_DIR" "${KEYMAP_DIR}" \
  "FIRMWARE_KEYMAPS_DIR" "${FIRMWARE_KEYMAPS_DIR}" \
  "FIRMWARE_KEYMAP_DIR" "${FIRMWARE_KEYMAP_DIR}" \
  "FIRMWARE_USERSPACES_DIR" "${FIRMWARE_USERSPACES_DIR}" \
  "FIRMWARE_USERSPACE_DIR" "${FIRMWARE_USERSPACE_DIR}" \
  "QMK_USER" "${QMK_USER}" \
  "RUNTIME" "${RUNTIME}" \
  "FLASH" "${FLASH}" \
  "TARGET" "${TARGET}" \
  "MAKE_COMMAND" "${MAKE_COMMAND}"

prompt "Looking good?"

main() { # {{{
  make --directory="${FIRMWARE_DIR}" git-submodule
  rm -rf "${FIRMWARE_DIR:?}/.build" \
         "${FIRMWARE_DIR:?}/${KEYMAP_BIN}" \
         "${FIRMWARE_USERSPACE_DIR}" \
         "${FIRMWARE_KEYMAP_DIR}"

  mkdir -p "${FIRMWARE_KEYMAPS_DIR}" \
           "${FIRMWARE_USERSPACES_DIR}"
  cp -r "${KEYMAP_DIR}" "${FIRMWARE_KEYMAP_DIR}"
  cp -r "${USERSPACE_DIR}" "${FIRMWARE_USERSPACE_DIR}"

  cd "${FIRMWARE_DIR}"

  case "${RUNTIME}" in
    docker|podman) RUNTIME="${RUNTIME}" ./util/docker_build.sh "${MAKE_COMMAND}";;
    local)
      # FIXME
      make "${MAKE_COMMAND}"
      if test -n "${TARGET}"; then
        qmk flash "${KEYMAP_BIN}" --bootloader "${TARGET}"
      fi;;
  esac
} # }}}

firmware_lock
main

printf '\n%s\n' "Done! You can find the built files in ${FIRMWARE_DIR}/.build"
