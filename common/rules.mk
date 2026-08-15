SRC += layers.c
SRC += tap_dance.c

ifeq ($(strip $(AUDIO_ENABLE)), yes)
  SRC += muse.c
endif

LTO_ENABLE = yes
NKRO_ENABLE = yes
