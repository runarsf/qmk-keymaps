#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
  #include "muse.h"
#endif
//#include "keymap_norwegian.h"

enum preonic_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST
};

#define ARROW MO(_ARROW)
#define CTL_ESC MT(MOD_LCTL, KC_ESC)

/* https://beta.docs.qmk.fm/using-qmk/simple-keycodes/keycodes
 * MUV_DE / MUV_IN are undocumented: https://github.com/qmk/qmk_firmware/issues/4616
 * https://github.com/qmk/qmk_firmware/pull/1112
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_preonic_grid( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,  KC_5,   KC_6,   KC_7,  KC_8,    KC_9,    KC_0,    KC_BSPC,  \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_DEL,   \
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_BSLS, KC_DEL,   \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_ENTER, \
    KC_LCTL, KC_LCTL, KC_LGUI, KC_LALT, LOWER, KC_SPC, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT   \
  ),

  /*
  [_LOWER] = LAYOUT_preonic_grid( \
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, \
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, _______, _______, _______, _______, KC_ENTER, \
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______, _______, _______, _______, KC_END,  _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_VOLD, KC_VOLU, KC_MNXT \
  ),
  */
  [_LOWER] = LAYOUT_preonic_grid( \
    S(KC_EQL), KC_EXLM, ALGR(KC_2), KC_HASH, ALGR(KC_4), KC_PERC, S(KC_6), S(KC_7), ALGR(KC_RBRC), S(KC_0),    KC_MINS, _______, \
    KC_TILD,   KC_EXLM, KC_AT,      KC_HASH, KC_DLR,     KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR,       KC_LPRN,    KC_RPRN, KC_DEL,  \
    _______,   _______, KC_NUHS,    _______, _______,    _______, _______, _______, ALGR(KC_8),    ALGR(KC_9), _______, _______, \
    _______,   _______, _______,    _______, _______,    _______, _______, _______, _______,       _______,    _______, _______, \
    _______,   _______, _______,    _______, _______,    KC_SPC,  KC_SPC,  _______, KC_HOME,       KC_PGDN,    KC_PGUP, KC_END   \
  ),

  [_RAISE] = LAYOUT_preonic_grid( \
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,          KC_8,       KC_9,       KC_0,       KC_LBRC , \
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,          KC_8,       KC_9,       KC_0,       KC_LBRC , \
    _______, _______, KC_NUHS, _______, _______, _______, _______, S(ALGR(KC_7)), ALGR(KC_7), ALGR(KC_0), KC_SCLN,    KC_QUOT,  \
    _______, _______, _______, _______, _______, _______, _______, _______,       KC_NUBS,    S(KC_NUBS), S(KC_RBRC), _______,  \
    _______, _______, _______, _______, ADJUST,  KC_SPC,  KC_SPC,  ADJUST,        KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END    \
  ),

  [_ADJUST] = LAYOUT_preonic_grid( \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,  \
    _______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF, _______, _______, _______,  \
    _______, KC_INS,  MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______,  _______, _______, _______, \
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______,  _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______  \
  )
};

/* https://beta.docs.qmk.fm/using-qmk/guides/custom_quantum_functions#example-process_record_user-implementation
 * Called by QMK during key processing before the actual key event is handled.
 * If this function returns true QMK will process the keycodes as usual.
 * That can be handy for extending the functionality of a key rather than replacing it.
 * If this function returns false QMK will skip the normal key handling,
 * and it will be up to you to send any key up or down events that are required.
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record -> event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      // If the LOWER key was pressed.
      if (record -> event.pressed) {
        layer_on(_LOWER);
        /* Check to see if the first two layers are on (_LOWER and _RAISE).
         * If they both are, then turn on the third layer (_ADJUST).
         * If one or both are not on, then turn off the adjust layer.
         * TL;DR: Hold LOWER and RAISE for ADJUSt.
         */
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      // Skip all further processing of this key, return true to let QMK send the key events.
      return false;
      break;
    case RAISE:
      if (record -> event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    /*
    case BACKLIT:
      if (record -> event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef __AVR__
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef __AVR__
          writePinHigh(E6);
        #endif
      }
      return false;
      break;
    */
  }
  return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}


void matrix_scan_user(void) {
  #ifdef AUDIO_ENABLE
      if (muse_mode) {
          if (muse_counter == 0) {
              uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
              if (muse_note != last_muse_note) {
                  stop_note(compute_freq_for_midi_note(last_muse_note));
                  play_note(compute_freq_for_midi_note(muse_note), 0xF);
                  last_muse_note = muse_note;
              }
          }
          muse_counter = (muse_counter + 1) % muse_tempo;
      } else {
          if (muse_counter) {
              stop_all_notes();
              muse_counter = 0;
          }
      }
  #endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
