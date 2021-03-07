#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
  #include "muse.h"
#endif
#include "keymap_norwegian.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)

// https://beta.docs.qmk.fm/using-qmk/software-features/feature_layers#switching-and-toggling-layers-id-switching-and-toggling-layers

//#define LOWER MO(_LOWER)
//#define RAISE MO(_RAISE)

enum preonic_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _CLEAR,
  _SPECIAL
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  CLEAR,
  SPECIAL
};

#define ARROW MO(_ARROW)
#define CTL_ESC MT(MOD_LCTL, KC_ESC)

/**
 * https://beta.docs.qmk.fm/using-qmk/simple-keycodes/keycodes
 * MUV_DE / MUV_IN are undocumented: https://github.com/qmk/qmk_firmware/issues/4616
 * https://github.com/qmk/qmk_firmware/pull/1112
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_preonic_grid(
    KC_ESC,  KC_1,         KC_2,    KC_3,    KC_4,  KC_5,   KC_6,   KC_7,  KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,  KC_Q,         KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_DEL,
    KC_TAB,  KC_A,         KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_BSLS, KC_DEL,
    KC_LSFT, KC_Z,         KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_ENTER,
    KC_LCTL, TT(_SPECIAL), KC_LGUI, KC_LALT, LOWER, KC_SPC, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),

  /*
  [_LOWER] = LAYOUT_preonic_grid(
    S(KC_EQL), KC_EXLM, ALGR(KC_2), KC_HASH, ALGR(KC_4), KC_PERC, S(KC_6), S(KC_7), ALGR(KC_RBRC), S(KC_0),    KC_MINS, _______,
    KC_TILD,   KC_EXLM, KC_AT,      KC_HASH, KC_DLR,     KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR,       KC_LPRN,    KC_RPRN, KC_DEL,
    _______,   _______, KC_NUHS,    _______, _______,    _______, _______, _______, ALGR(KC_8),    ALGR(KC_9), _______, _______,
    _______,   _______, _______,    _______, _______,    _______, _______, _______, _______,       _______,    _______, _______,
    _______,   _______, _______,    _______, _______,    KC_SPC,  KC_SPC,  _______, KC_HOME,       KC_PGDN,    KC_PGUP, KC_END
  ),
  */
  [_LOWER] = LAYOUT_preonic_grid(
    NO_GRV,  KC_EXLM, NO_AT,   KC_HASH, NO_DLR,  KC_PERC, NO_AMPR, NO_SLSH, NO_TILD, NO_EQL,  NO_PLUS,        KC_BSPC,
    NO_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,           KC_DEL,
    _______, NO_BSLS, NO_QUO2, _______, NO_EURO, _______, _______, NO_QUOT, NO_LBRC, NO_RBRC, KC_KP_ASTERISK, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, NO_LESS, NO_GRTR, NO_CIRC,        _______,
    _______, _______, _______, _______, _______, KC_SPC,  KC_SPC,  _______, KC_HOME, KC_PGDN, KC_PGUP,        KC_END
  ),

  [_RAISE] = LAYOUT_preonic_grid(
    NO_PIPE_ALT, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,        KC_8,    KC_9,    KC_0,    NO_AM ,
    NO_PIPE_ALT, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,        KC_8,    KC_9,    KC_0,    NO_AM ,
    _______,     _______, NO_QUOT, _______, _______, _______, _______, NO_BSLS_ALT, NO_LCBR, NO_RCBR, NO_OSLH, NO_AE,
    _______,     _______, _______, _______, _______, _______, _______, _______,     NO_LESS, NO_GRTR, NO_CIRC, _______,
    _______,     _______, _______, _______, _______, KC_SPC,  KC_SPC,  _______,     KC_HOME, KC_PGDN, KC_PGUP, KC_END
  ),

  [_ADJUST] = LAYOUT_preonic_grid(
    KC_F1,      KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,               KC_F7,               KC_F8,   KC_F9,               KC_F10,            KC_F11,          KC_F12,
    _______,    MU_ON,   MU_OFF,  MU_MOD,  _______, TERM_ON,             TERM_OFF,            _______, _______,             _______,           _______,         _______,
    _______,    AU_ON,   AU_OFF,  _______, _______, AG_NORM,             AG_SWAP,             _______, _______,             _______,           _______,         _______,
    _______,    MI_ON,   MI_OFF,  _______, _______, MUV_DE,              MUV_IN,              _______, _______,             _______,           _______,         _______,
    TT(_CLEAR), _______, _______, _______, _______, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_PLAY_PAUSE, _______, KC_MEDIA_PREV_TRACK, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_MEDIA_NEXT_TRACK
  ),
  
  // TODO: Replace (1,0) with DF(_SPECIAL)?
  [_SPECIAL] = LAYOUT_preonic_grid(
    _______, _______,    _______,    _______,     _______,      _______, _______, _______,    _______,       _______,        _______, _______,
    _______, KC_MS_BTN1, KC_MS_UP,   KC_MS_BTN2,  KC_MS_ACCEL2, KC_KP_7, KC_KP_8, KC_KP_9,    KC_MS_WH_LEFT, KC_MS_WH_RIGHT, _______, _______,
    _______, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_MS_ACCEL1, KC_KP_4, KC_KP_5, KC_KP_6,    KC_MS_WH_DOWN, KC_MS_WH_UP,    _______, _______,
    _______, KC_MS_BTN4, KC_MS_BTN3, KC_MS_BTN5,  KC_MS_ACCEL0, KC_KP_1, KC_KP_2, KC_KP_3,    _______,       _______,        _______, _______,
    _______, _______,    _______,    _______,     KC_MS_BTN1,   KC_KP_0, KC_KP_0, KC_NUMLOCK, _______,       _______,        _______, _______
  ),

  /** Plover layer (http://opensteno.org)
   * ,-----------------------------------------------------------------------------------.
   * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
   * `-----------------------------------------------------------------------------------'
   */
  [_PLOVER] = LAYOUT_planck_grid(
    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
    _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    EXT_PLV, _______, _______, KC_C,    KC_V,    _______, _______, KC_N,    KC_M,    _______, _______, _______
  ),

  [_CLEAR] = LAYOUT_preonic_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, DEBUG,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, RESET,   RESET,   _______, _______, _______, _______, _______
  ),
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
