#!/usr/bin/env bash
# vim: set foldmethod=marker nomodeline:
# Initialization {{{
#set -o errexit   # abort on nonzero exit status
#set -o nounset   # abort on unbound variable
#set -o pipefail  # don't hide errors within pipes
#set -o noclobber # disallow redirect overwriting

__dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)" # /home/user/deploy
#__file="${__dir}/$(basename "${BASH_SOURCE[0]}")"                     # /home/user/deploy/deploy.sh
#__base="$(basename ${__file} .sh)"                                    # deploy
# }}}

# Colours {{{
RESET=$'\e[0;39m'

E_UNDERLINE=$'\e[4m'

C_DEFAULT=$'\e[19m'
C_BLACK=$'\e[30m'
C_RED=$'\e[31m'
C_GREEN=$'\e[32m'
C_YELLOW=$'\e[33m'
C_BLUE=$'\e[34m'
C_MAGENTA=$'\e[35m'
C_CYAN=$'\e[36m'
C_LGRAY=$'\e[37m'
C_DGRAY=$'\e[90m'
C_LRED=$'\e[91m'
C_LGREEN=$'\e[92m'
C_LYELLOW=$'\e[93m'
C_LBLUE=$'\e[94m'
C_LMAGENTA=$'\e[95m'
C_LCYAN=$'\e[96m'
C_WHITE=$'\e[97m'
# }}}

# Debug {{{
# FIXME: expand variables in debug and why tf does it expand newlines...
#printf "\e[94m[run-order|line number>|function:function-call] \e[4mcommand\e[0m\n"
#trap 'printf "\e[94m[$((runlineno+=1))|${LINENO}|${FUNCNAME[1]:-0}:${BASH_LINENO[0]}] \e[4m${BASH_COMMAND}\e[0m\n"; read -n 1 -s -r' DEBUG
#commad -v bash_debug && bash_debug
# }}}

usage () { # {{{
	cat <<-EOMAN
	${RESET}${C_GREEN}Usage:${RESET} ${0}       <${C_RED}options${RESET}>   [${C_BLUE}layout${RESET}]
	
	${C_GREEN}Options:${RESET}
	  -h, --help                      Display usage menu.
	  -u, --user         <${C_RED}username${RESET}> ${C_RED}!${RESET} QMK user.
	  -w, --fw-folder   <${C_RED}directory${RESET}>   qmk_firmware folder location.
	  -p, --podman                    Build using podman instead of docker.
	  -f, --flash                     Flash and build.
	  --keyboard         <${C_RED}keyboard${RESET}> ${C_YELLOW}*${RESET} Keyboard.
	  --make-prefix        <${C_RED}prefix${RESET}> ${C_YELLOW}*${RESET} Make prefix.
	  --make-suffix        <${C_RED}suffix${RESET}> ${C_YELLOW}*${RESET} Make suffix.
	  --image-extension <${C_RED}extension${RESET}> ${C_YELLOW}*${RESET} Image extension.
	${C_GREEN}Layouts:${RESET}
	  preonic
	  planck
	${C_GREEN}Examples:${RESET}
	  ${0} ${C_RED}--user runarsf ${C_BLUE}planck${RESET}
	  ${0} ${C_RED}--user runarsf ${C_BLUE}preonic ${C_RED}--flash${RESET}
	${RESET}
	Options marked with ${C_RED}!${RESET} are required.
	Options marked with ${C_YELLOW}*${RESET} are required ${E_UNDERLINE}if${RESET} you provide an undefined layout.
	
	Initialize the qmk_firmware folder/submodule:
	  git submodule add https://github.com/qmk/qmk_firmware.git
	  git submodule update --init --recursive
	${RESET}
	EOMAN
} # }}}

# Argument parsing {{{
# TODO: Check if zsa firmware should be used for planck_ez https://github.com/zsa/qmk_firmware/
# TODO: Consider using a default QMK user instead of forcing the user to provide one
# TODO: Add support for entire make string and not separate arguments
# TODO: Support only -f and not build
# TODO: https://github.com/zawaken/sys-help#building-qmk-keymaps-without-sudo-doesnt-work
QMK_FIRMWARE_FOLDER='qmk_firmware'
positional=()
while test "${#}" -gt "0"; do
  case "${1}" in
    -h|--help)
      usage
      exit 0;;
    -u|--user)
      QMK_USER="${2}"
      shift;shift;;
    -w|--fw-folder)
      QMK_FIRMWARE_FOLDER="${2}"
      shift;shift;;
    -p|--podman)
      PODMAN="true"
      shift;;
    -f|--flash)
      FLASH="true"
      shift;;
    -q|--qmk)
      #printf "Initializing QMK firmware repo to ${QMK_FIRMWARE_FOLDER}...\n"
      if test -d "${QMK_FIRMWARE_FOLDER}"; then
        git submodule init
        git submodule update --recursive
      else
        git clone https://github.com/qmk/qmk_firmware.git "${QMK_FIRMWARE_FOLDER}"
      fi
      shift;;
    --keyboard)
      TARGET_KEYBOARD="${2}"
      shift;shift;;
    --make-prefix)
      MAKE_PREFIX="${2}"
      shift;shift;;
    --make-suffix)
      MAKE_SUFFIX="${2}"
      shift;shift;;
    --image-extension)
      IMAGE_EXTENSION="${2}"
      shift;shift;;
    --*)
      printf '%s\n' "Unknown option: ${1}"
      exit 1
      shift;;
    -*)
      shopts="${1}"
      if test "${#shopts}" -le "2"; then
        printf '%s\n' "Unknown option: ${shopts}"
        exit 2
      fi
      shift
      set -- "${shopts:0:2}" "-${shopts:2}" "${@}"
      ;;
    *)
      positional+=("${1}")
      shift;;
  esac
done

set -- "${positional[@]}"

if test -z "${QMK_USER}"; then printf '%s\n' "Required argument -u|--user not provided.\nSee --help for more info." && exit 1; fi

if test "${#}" -gt "1"; then
  printf '%s\n' "Too many arguments, expected target layout.\nSee --help for more info."
  exit 1
elif test "${#}" -lt "1"; then
  printf '%s\n' "Too few arguments, expected target layout.\nSee --help for more info."
  exit 1
fi
# }}}

confirm () { # {{{
  local -r msg="${1:-Continue?}"
  printf '%s\n' "${msg} [Y/n]"
  read -p "? " -n 1 -r </dev/tty
  printf '\n'
  case "${REPLY}" in
    [Yy]*) return 0; break;;
    [Nn]*) return 1;;
    *) printf '%s\n' 'Please answer yes or no...';;
  esac
} # }}}

# Folder for build-files? ./preonic
TARGET_LAYOUT="${1}"

# Predefined layouts
if test -z "${KEYBOARD}" \
     -o -z "${MAKE_PREFIX}" \
     -o -z "${MAKE_SUFFIX}" \
     -o -z "${IMAGE_EXTENSION}"; then
  case "${TARGET_LAYOUT}" in
    preonic)
      TARGET_KEYBOARD='preonic'
      MAKE_PREFIX='preonic/rev3'
      IMAGE_EXTENSION='bin'
      MAKE_SUFFIX=":dfu-util"
      ;;
    planck)
      TARGET_KEYBOARD='planck'
      MAKE_PREFIX='planck/rev6'
      IMAGE_EXTENSION='bin'
      MAKE_SUFFIX=':dfu-util'
      ;;
    *)
      printf '%s\n' "Undefined layout '${TARGET_LAYOUT}' found, and missing required options."
      exit 1
      ;;
  esac
fi

# preonic_runarsf.bin
BINARY_NAME="${TARGET_LAYOUT}_${QMK_USER}.${IMAGE_EXTENSION}"

if test ! -f "${QMK_FIRMWARE_FOLDER}/Makefile"; then
  printf '%s\n' "QMK_FIRMWARE_FOLDER (${QMK_FIRMWARE_FOLDER}) does not exist or Makefile is not present, get it from qmk/qmk_firmware on github."
  if confirm 'Update submodules?'; then
    git submodule update --init --recursive
  else
    exit 1
  fi
fi

# Remove build folder
printf '%s\n' "Deleting preexisting build-files: ${QMK_FIRMWARE_FOLDER}/.build"
rm -rf "${QMK_FIRMWARE_FOLDER}/.build"

# qmk_firmware/keyboards/preonic/keymaps/runarsf
printf '%s\n' "Creating keymap folder: ${QMK_FIRMWARE_FOLDER}/keyboards/${TARGET_KEYBOARD}/keymaps/${QMK_USER}"
mkdir -p "${QMK_FIRMWARE_FOLDER}/keyboards/${TARGET_KEYBOARD}/keymaps/${QMK_USER}"

# preonic/{config.h,keymap.c,rules.mk} qmk_firmware/keyboards/preonic/keymaps/runarsf/
printf '%s\n' "Copying keymap: ${TARGET_LAYOUT}/{config.h,keymap.c,rules.mk} -> ${QMK_FIRMWARE_FOLDER}/keyboards/${TARGET_KEYBOARD}/keymaps/${QMK_USER}/"
rsync --archive --verbose --human-readable ${TARGET_LAYOUT}/{config.h,keymap.c,rules.mk} ${QMK_FIRMWARE_FOLDER}/keyboards/${TARGET_KEYBOARD}/keymaps/${QMK_USER}/

# Used for shared/common configurations
#printf "Copying common: ./common -> ./${QMK_FIRMWARE_FOLDER}/users/${QMK_USER}/\n"
#rsync --archive --verbose --human-readable --delete ./common/ "./${QMK_FIRMWARE_FOLDER}/users/${QMK_USER}/" >/dev/null 2>&1

printf '%s\n' "Initializing submodules"
make --directory="${QMK_FIRMWARE_FOLDER}" git-submodule >/dev/null 2>&1

printf '%s\n' "Deleting preexisting binary: ${QMK_FIRMWARE_FOLDER}/${TARGET_LAYOUT}_${QMK_USER}.${IMAGE_EXTENSION}"
rm -rf "${QMK_FIRMWARE_FOLDER}/${TARGET_LAYOUT}_${QMK_USER}.${IMAGE_EXTENSION}"

cd "${QMK_FIRMWARE_FOLDER}"

if test -z "${PODMAN}"; then
  if test -n "${FLASH}"; then
    printf '%s\n' "Building and flashing (docker) ${MAKE_PREFIX}:${QMK_USER}"
    ./util/docker_build.sh "${MAKE_PREFIX}:${QMK_USER}${MAKE_SUFFIX}"
  else
    printf '%s\n' "Building (docker) ${MAKE_PREFIX}:${QMK_USER}"
    ./util/docker_build.sh "${MAKE_PREFIX}:${QMK_USER}"
  fi
else
  printf '%s\n' "Copying podman_build.sh: ${__dir}/podman_build.sh -> ./util/"
  rsync --archive --verbose --human-readable --delete "${__dir}/podman_build.sh" ./util/
  if test -n "${FLASH}"; then
    printf '%s\n' "Building and flashing (podman) ${MAKE_PREFIX}:${QMK_USER}"
    ./util/podman_build.sh "${MAKE_PREFIX}:${QMK_USER}${MAKE_SUFFIX}"
  else
    printf '%s\n' "Building (podman) ${MAKE_PREFIX}:${QMK_USER}"
    ./util/podman_build.sh "${MAKE_PREFIX}:${QMK_USER}"
  fi
fi

makeExit="${?}"
if test "${makeExit}" -ne "0"; then
  printf '%s\n' "Something went wrong, Make exited with code ${makeExit}."
else
  printf '%s\n' "Make finished, you can find the binaries in ${QMK_FIRMWARE_FOLDER}/.build"
fi
