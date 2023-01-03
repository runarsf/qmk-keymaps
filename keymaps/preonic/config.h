#pragma once

#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(NO_SOUND)
#endif

#define MUSIC_MASK (keycode != KC_NO)

#define MIDI_BASIC