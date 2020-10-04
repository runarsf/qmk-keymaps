#!/usr/bin/env bash
# TODO: expand variables in debug and why tf does it expand newlines...
printf "\e[94m[run-order|line number>|function:function-call] \e[4mcommand\e[0m\n"
trap 'printf "\e[94m[$((runlineno+=1))|${LINENO}|${FUNCNAME[1]:-0}:${BASH_LINENO[0]}] \e[4m${BASH_COMMAND}\e[0m\n"; read -n 1 -s -r' DEBUG

usage () {
  printf "heLP!\n"
}

# if you don't have the submodule already
#   git submodule add https://github.com/qmk/qmk_firmware.git
# then - or if you already have the submodule but not updated/pulled it (--recursive might not be needed, since we update it using make later)
#   git submodule update --init --recursive

QMK_FIRMWARE_FOLDER='qmk_firmware'
positional=()
while test "${#}" -gt "0"; do
  case "${1}" in
    -u|--user)
      QMK_USER="${2}"
      shift;shift;;
    -f|--fw-folder)
      QMK_FIRMWARE_FOLDER="${2}"
      shift;shift;;
    -p|--podman)
      PODMAN="true"
      shift;;
    -f|--flash)
      FLASH="true"
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
      printf "Unknown option: ${1}\n"
      exit 1
      shift;;
    -*)
      shopts="${1}"
      if test "${#shopts}" -le "2"; then
        printf "Unknown option: ${shopts}\n"
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

if test -z "${QMK_USER}"; then usage && exit 1; fi

if test "${#}" -gt "1"; then
  printf "Too many arguments, expected target layout.\n"
  exit 1
elif test "${#}" -lt "1"; then
  printf "Too few arguments, expected target layout.\n"
  exit 1
fi

# preonic
TARGET_LAYOUT="${1}"

if test -z "${KEYBOARD}" -o -z "${MAKE_PREFIX}" -o -z "${MAKE_SUFFIX}" -o -z "${IMAGE_EXTENSION}"; then
  case "${TARGET_LAYOUT}" in
    preonic)
      TARGET_KEYBOARD='preonic'
      MAKE_PREFIX='preonic/rev3'
      IMAGE_EXTENSION='bin'
      MAKE_SUFFIX=":dfu-util-wait"
      ;;
    planck)
      TARGET_KEYBOARD='planck'
      MAKE_PREFIX='planck/rev6'
      IMAGE_EXTENSION='bin'
      MAKE_SUFFIX=':dfu-util-wait'
      ;;
    *)
      printf "\n"
      exit 1
      ;;
  esac
fi

# preonic_runarsf.bin
BINARY_NAME="${TARGET_LAYOUT}_${QMK_USER}.${IMAGE_EXTENSION}"

if test ! -f "${QMK_FIRMWARE_FOLDER}/Makefile"; then
  printf "QMK_FIRMWARE_FOLDER (${QMK_FIRMWARE_FOLDER}) does not exist or Makefile is not present, get it from qmk/qmk_firmware on github.\n"
  exit 1
fi

# Remove build folder
printf "Deleting preexisting build-files: ${QMK_FIRMWARE_FOLDER}/.build\n"
rm -rf "${QMK_FIRMWARE_FOLDER}/.build"

# qmk_firmware/keyboards/preonic/keymaps/runarsf
printf "Creating keymap folder: ${QMK_FIRMWARE_FOLDER}/keyboards/${TARGET_KEYBOARD}/keymaps/${QMK_USER}\n"
mkdir -p "${QMK_FIRMWARE_FOLDER}/keyboards/${TARGET_KEYBOARD}/keymaps/${QMK_USER}"

# preonic/{config.h,keymap.c,rules.mk} qmk_firmware/keyboards/preonic/keymaps/runarsf/
printf "Copying keymap: ${TARGET_LAYOUT}/{config.h,keymap.c,rules.mk} -> ${QMK_FIRMWARE_FOLDER}/keyboards/${TARGET_KEYBOARD}/keymaps/${QMK_USER}/\n"
rsync --archive --verbose --human-readable ${TARGET_LAYOUT}/{config.h,keymap.c,rules.mk} ${QMK_FIRMWARE_FOLDER}/keyboards/${TARGET_KEYBOARD}/keymaps/${QMK_USER}/

printf "Copying common: ./common -> ./${QMK_FIRMWARE_FOLDER}/users/${QMK_USER}/\n"
rsync --archive --verbose --human-readable --delete ./common/ "./${QMK_FIRMWARE_FOLDER}/users/${QMK_USER}/" >/dev/null 2>&1

printf "Initializing submodules\n"
make --directory="${QMK_FIRMWARE_FOLDER}" git-submodule >/dev/null 2>&1

printf "Deleting preexisting binary: ${QMK_FIRMWARE_FOLDER}/${TARGET_LAYOUT}_${QMK_USER}.${IMAGE_EXTENSION}\n"
rm -rf "${QMK_FIRMWARE_FOLDER}/${TARGET_LAYOUT}_${QMK_USER}.${IMAGE_EXTENSION}"

cd "${QMK_FIRMWARE_FOLDER}"

if test -z "${PODMAN}"; then
  if test -n "${FLASH}"; then
    printf "Building and flashing ${MAKE_PREFIX}:${QMK_USER}\n"
    ./util/docker_build.sh "${MAKE_PREFIX}:${QMK_USER}${MAKE_SUFFIX}"
  else
    printf "Building ${MAKE_PREFIX}:${QMK_USER}\n"
    ./util/docker_build.sh "${MAKE_PREFIX}:${QMK_USER}"
  fi
else
  # use own podman_build.sh script
  #rsync --archive --verbose --human-readable --delete ../podman_build.sh ./util/
  if test -n "${FLASH}"; then
    printf "building and flashing ${MAKE_PREFIX}:${QMK_USER}\n"
    ./util/podman_build.sh "${MAKE_PREFIX}:${QMK_USER}${MAKE_SUFFIX}"
  else
    printf "building ${MAKE_PREFIX}:${QMK_USER}\n"
    ./util/podman_build.sh "${MAKE_PREFIX}:${QMK_USER}"
  fi
fi