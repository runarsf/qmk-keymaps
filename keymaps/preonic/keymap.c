#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"

#ifdef AUDIO_ENABLE
  #include "muse.h"
#endif

#define CTL_ESC MT(MOD_LCTL, KC_ESC)

enum preonic_layers {
  QTY,
  LWR,
  RSE,
  CMB,
  QMK,
  RST,
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  BACKLIT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /** Qwerty
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ Esc │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │ Bsp │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ Tab │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │ Del │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ CtE │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  '  │  "  │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ Sft │  Z  │  X  │  C  │  V  │  B  │  N  │  M  │ , ; │ . : │ - _ │ Ret │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │ Ctl │ Qmk │ Win │ Alt │ LWR │   Space   │ RSE │ ArL │ ArD │ ArU │ ArR │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [QTY] = LAYOUT_preonic_grid(
    KC_ESC,  NO_1,    NO_2,    NO_3,    NO_4,    NO_5,    NO_6,    NO_7,    NO_8,    NO_9,    NO_0,    KC_BSPC,
    KC_TAB,  NO_Q,    NO_W,    NO_E,    NO_R,    NO_T,    NO_Y,    NO_U,    NO_I,    NO_O,    NO_P,    KC_DEL,
    CTL_ESC, NO_A,    NO_S,    NO_D,    NO_F,    NO_G,    NO_H,    NO_J,    NO_K,    NO_L,    NO_QUOT, NO_DQUO,
    KC_LSFT, NO_Z,    NO_X,    NO_C,    NO_V,    NO_B,    NO_N,    NO_M,    NO_COMM, NO_DOT,  NO_MINS, KC_ENT,
    KC_LCTL, TT(QMK), KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),

  /** Lower
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │  `  │  !  │  @  │  #  │  $  │  %  │  &  │  /  │  ~  │  =  │  +  │  ´  │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │  "  │     │     │     │     │     │  [  │  ]  │  *  │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │     │     │     │     │  (  │  )  │     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │ [_] │           │ CMB │     │     │     │     │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [LWR] = LAYOUT_preonic_grid(
    NO_GRV,  NO_EXLM, NO_AT,   NO_HASH, NO_DLR,  NO_PERC, NO_AMPR, NO_SLSH, NO_TILD, NO_EQL,  NO_PLUS, NO_ACUT,
    _______, NO_1,    NO_2,    NO_3,    NO_4,    NO_5,    NO_6,    NO_7,    NO_8,    NO_9,    NO_0,    _______,
    _______, _______, NO_DQUO, _______, _______, _______, _______, _______, NO_LBRC, NO_RBRC, NO_ASTR, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, NO_LPRN, NO_RPRN, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  /** Raise
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │  |  │     │     │     │     │     │     │     │     │     │     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  Å  │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │     │     │     │  \  │  {  │  }  │  Ø  │  Æ  │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │     │     │     │     │  <  │  >  │  ^  │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │ CMB │           │ [_] │ Hom │ PgD │ PgU │ End │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [RSE] = LAYOUT_preonic_grid(
    NO_PIPE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, NO_1,    NO_2,    NO_3,    NO_4,    NO_5,    NO_6,    NO_7,    NO_8,    NO_9,    NO_0,    NO_ARNG,
    _______, _______, _______, _______, _______, _______, _______, NO_BSLS, NO_LCBR, NO_RCBR, NO_OSTR, NO_AE,
    _______, _______, _______, _______, _______, _______, _______, _______, NO_LABK, NO_RABK, NO_CIRC, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
  ),

  /** Combine (Lower + Raise)
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ F01 │ F02 │ F03 │ F04 │ F05 │ F06 │ F07 │ F08 │ F09 │ F10 │ F11 │ F12 │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ --- │ [_] │ PlayPause │ [_] │ Prv │ Vo- │ Vo+ │ Nxt │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [CMB] = LAYOUT_preonic_grid(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, KC_MPLY, KC_MPLY, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
  ),

  /** QMK
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ RST │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ Ms1 │ MsU │ Ms2 │ MWU │ N07 │ N08 │ N09 │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ Cps │ MsL │ MsD │ MsR │ MWD │ N04 │ N05 │ N06 │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ MWL │ MWR │ N01 │ N02 │ N03 │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ [_] │ --- │ Ms2 │ Ms1 │  NumPad0  │ NLk │ --- │ --- │ --- │ --- │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [QMK] = LAYOUT_preonic_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, MO(RST),
    _______, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_U, KC_KP_7, KC_KP_8, KC_KP_9, _______, _______, _______, _______,
    KC_CAPS, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_KP_4, KC_KP_5, KC_KP_6, _______, _______, _______, _______,
    _______, _______, _______, KC_WH_L, KC_WH_R, KC_KP_1, KC_KP_2, KC_KP_3, _______, _______, _______, _______,
    _______, _______, _______, KC_BTN2, KC_BTN1, KC_KP_0, KC_KP_0, KC_NUM,  _______, _______, _______, _______
  ),

  /** Reset
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ [_] │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ [_] │ --- │ --- │ --- │   Reset   │ --- │ --- │ --- │ --- │ --- │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [RST] = LAYOUT_preonic_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(QTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(LWR);
        update_tri_layer(LWR, RSE, CMB);
      } else {
        layer_off(LWR);
        update_tri_layer(LWR, RSE, CMB);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(RSE);
        update_tri_layer(LWR, RSE, CMB);
      } else {
        layer_off(RSE);
        update_tri_layer(LWR, RSE, CMB);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef RGBLIGHT_ENABLE
          rgblight_step();
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
  }
  return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(RSE)) {
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
  return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        layer_on(CMB);
      } else {
        layer_off(CMB);
      }
      break;
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
      }
  }
  return true;
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
