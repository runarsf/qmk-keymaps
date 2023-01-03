#pragma once

#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(NO_SOUND)
#endif

#define MUSIC_MASK (keycode != KC_NO)

#define TAPPING_TOGGLE 2

#define ENCODER_RESOLUTION 4

#define MIDI_BASIC