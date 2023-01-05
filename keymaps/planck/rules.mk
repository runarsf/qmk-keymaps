# https://docs.qmk.fm/#/getting_started_make_guide
SRC += common.c
ifeq ($(strip $(AUDIO_ENABLE)), yes)
  SRC += muse.c
endif
LTO_ENABLE = yes
NKRO_ENABLE = yes
CONSOLE_ENABLE = yes
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
