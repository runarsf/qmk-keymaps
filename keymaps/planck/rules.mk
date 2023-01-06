# https://docs.qmk.fm/#/getting_started_make_guide
# ifeq ($(strip $(AUDIO_ENABLE)), yes)
  SRC += muse.c
# endif
AUDIO_ENABLE = yes
LTO_ENABLE = yes
NKRO_ENABLE = yes
CONSOLE_ENABLE = yes
# RGBLIGHT_ENABLE = yes
RGB_MATRIX_ENABLE = yes
CAPS_WORD_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes
KEY_LOCK_ENABLE = yes
SEND_STRING_ENABLE = yes