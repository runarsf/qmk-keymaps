#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"
#include <stdlib.h>

#ifdef AUDIO_ENABLE
  #include "muse.h"
#endif

enum planck_layers {
  QTY,
  LWR,
  RSE,
  CMB,
  QMK,
  RST,
};

enum planck_keycodes {
  PLACEHOLDER = SAFE_RANGE,
  SARCASM,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /** Qwerty
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ Esc │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │ Bsp │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ Tab │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  '  │ Del │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ Sft │  Z  │  X  │  C  │  V  │  B  │  N  │  M  │ , ; │ . : │ - _ │ Ret │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │ Ctl │ Qmk │ Win │ Alt │ LWR │   Space   │ RSE │ ArL │ ArD │ ArU │ ArR │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [QTY] = LAYOUT_planck_grid(
    KC_ESC,  NO_Q,    NO_W,    NO_E,    NO_R,    NO_T,    NO_Y,    NO_U,    NO_I,    NO_O,    NO_P,    KC_BSPC,
    KC_TAB,  NO_A,    NO_S,    NO_D,    NO_F,    NO_G,    NO_H,    NO_J,    NO_K,    NO_L,    NO_QUOT, KC_DEL,
    KC_LSFT, NO_Z,    NO_X,    NO_C,    NO_V,    NO_B,    NO_N,    NO_M,    NO_COMM, NO_DOT,  NO_MINS, KC_ENT,
    KC_LCTL, TT(QMK), KC_LGUI, KC_LALT, MO(LWR), KC_SPC,  KC_SPC,  MO(RSE), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),

  /** Lower
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │  `  │  !  │  @  │  #  │  $  │  %  │  &  │  /  │  ~  │  =  │  +  │  ´  │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │  "  │     │     │     │     │     │  [  │  ]  │  *  │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │     │     │     │     │  (  │  )  │     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │ [_] │           │ CMB │     │     │     │     │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [LWR] = LAYOUT_planck_grid(
    NO_GRV,  NO_EXLM, NO_AT,   NO_HASH, NO_DLR,  NO_PERC, NO_AMPR, NO_SLSH, NO_TILD, NO_EQL,  NO_PLUS, NO_ACUT,
    _______, _______, NO_DQUO, _______, _______, _______, _______, _______, NO_LBRC, NO_RBRC, NO_ASTR, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, NO_LPRN, NO_RPRN, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  /** Raise
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │  |  │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  Å  │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │     │     │     │  \  │  {  │  }  │  Ø  │  Æ  │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │     │     │     │  ¨  │  <  │  >  │  ^  │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │ AGr │ CMB │           │ [_] │ Hom │ PgD │ PgU │ End │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [RSE] = LAYOUT_planck_grid(
    NO_PIPE, NO_1,    NO_2,    NO_3,    NO_4,    NO_5,    NO_6,    NO_7,    NO_8,    NO_9,    NO_0,    NO_ARNG,
    _______, _______, _______, _______, _______, _______, _______, NO_BSLS, NO_LCBR, NO_RCBR, NO_OSTR, NO_AE,
    _______, _______, _______, _______, _______, _______, _______, NO_DIAE, NO_LABK, NO_RABK, NO_CIRC, _______,
    _______, _______, _______, KC_ALGR, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
  ),

  /** Combine (Lower + Raise)
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ F01 │ F02 │ F03 │ F04 │ F05 │ F06 │ F07 │ F08 │ F09 │ F10 │ F11 │ F12 │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ Cps │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ --- │ [_] │ PlayPause │ [_] │ Prv │ Vo- │ Vo+ │ Nxt │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [CMB] = LAYOUT_planck_grid(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_MPLY, KC_MPLY, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
  ),

  /** QMK
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ QTY │ Ms1 │ MsU │ Ms2 │ MWU │ N07 │ N08 │ N09 │ Sai │ Hui │ Vai │ RST │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ MsL │ MsD │ MsR │ MWD │ N04 │ N05 │ N06 │ Sad │ Hud │ Vad │ SRC │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ MWL │ MWR │ N01 │ N02 │ N03 │ Rmd │ Mod │ Tog │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ [_] │ --- │ Ms2 │ Ms1 │  NumPad0  │ NLk │ --- │ --- │ --- │ --- │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [QMK] = LAYOUT_planck_grid(
    DF(QTY), KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_U, KC_KP_7, KC_KP_8, KC_KP_9, RGB_SAI,  RGB_HUI, RGB_VAI, MO(RST),
    _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_KP_4, KC_KP_5, KC_KP_6, RGB_SAD,  RGB_HUD, RGB_VAD, SARCASM,
    _______, _______, _______, KC_WH_L, KC_WH_R, KC_KP_1, KC_KP_2, KC_KP_3, RGB_RMOD, RGB_MOD, RGB_TOG, _______,
    _______, _______, _______, KC_BTN2, KC_BTN1, KC_KP_0, KC_KP_0, KC_NUM,  _______,  _______, _______, _______
  ),

  /** Reset
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ --- │ --- │   Reset   │ --- │ --- │ --- │ --- │ --- │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [RST] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  )
};

// TODO set RGB brightness
const RGB ___ = {.r=0,   .g=0,   .b=0};
const RGB BLU = {.r=0,   .g=138, .b=255};
const RGB LBL = {.r=162, .g=213, .b=252};
const RGB RED = {.r=248, .g=33,  .b=33};
const RGB LRD = {.r=242, .g=153, .b=168};

const RGB PROGMEM ledmap[][RGB_MATRIX_LED_COUNT] = {
  [LWR] = {
    BLU, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
    BLU, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
    BLU, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
    BLU, BLU, BLU, BLU, BLU,    ___,   ___, ___, ___, ___, ___,
  },
  [RSE] = {
    ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, BLU,
    ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, BLU,
    ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, BLU,
    ___, ___, ___, ___, ___,    ___,   BLU, BLU, BLU, BLU, BLU,
  },
  [CMB] = {
    BLU, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, BLU,
    BLU, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, BLU,
    BLU, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, BLU,
    BLU, BLU, BLU, BLU, BLU,    BLU,   BLU, BLU, BLU, BLU, BLU,
  },
  [QMK] = {
    LBL, ___, BLU, ___, ___, LBL, LBL, LBL, ___, ___, ___, RED,
    ___, BLU, BLU, BLU, ___, LBL, LBL, LBL, ___, ___, ___, LBL,
    ___, ___, ___, ___, ___, LBL, LBL, LBL, ___, ___, ___, ___,
    ___, ___, ___, ___, ___,    LBL,   BLU, ___, ___, ___, ___,
  },
  [RST] = {
    ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, LRD, LRD, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, LRD,    RED,   LRD, ___, ___, ___, ___,
  },
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, LWR, RSE, CMB);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool sarcastic = false;
  static bool capitalized = false;
  static uint8_t same = 0;

  if(sarcastic && record->event.pressed) {
    if (rand() % 2 == 1 || same > 0) {
      register_code(KC_CAPS);
      unregister_code(KC_CAPS);
      capitalized = !capitalized;
      same = 0;
    } else {
      same++;
    }
  }

  switch (keycode) {
    case SARCASM:
      if(record->event.pressed) {
        sarcastic = !sarcastic;
        if(capitalized) {
          register_code(KC_CAPS);
          unregister_code(KC_CAPS);
        }
      }
      return false;
      break;
  }
  return true;
};

void set_layer_color(uint8_t layer) {
  for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    RGB color = ledmap[layer][i];
    rgb_matrix_set_color(i, color.r, color.g, color.b);
  }
}

bool rgb_matrix_indicators_user(void) {
  // TODO clear leds on QTY when returning
  uint8_t layer = biton32(layer_state);

  if (layer != QTY) {
    set_layer_color(layer);
  } else if (host_keyboard_led_state().caps_lock) {
    rgb_matrix_set_color_all(0, 0, 0);
    rgb_matrix_set_color(12, 255, 255, 255);
  }

  return true;
}
