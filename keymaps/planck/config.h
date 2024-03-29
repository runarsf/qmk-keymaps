#pragma once

#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(NO_SOUND)
#endif

#define ENCODER_RESOLUTION 4

#undef DEBOUNCE
#define DEBOUNCE 7

#define MIDI_BASIC

#define AUDIO_ENABLE_TONE_MULTIPLEXING
#define AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT 10

// #define RGBLIGHT_SLEEP
// #define RGBLIGHT_LAYERS
// #define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
// #define RGBLIGHT_LAYER_BLINK
