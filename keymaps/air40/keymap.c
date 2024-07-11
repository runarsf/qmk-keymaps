#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"

enum planck_layers {
  QTY,
  SLR,
  LWR,
  RSE,
  CMB,
  QMK,
  RST,
  SUS,
};

enum planck_keycodes {
  PLACEHOLDER = SAFE_RANGE,
};

uint8_t sus_counter = 0;

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
  [QTY] = LAYOUT_ortho_4x12(
    KC_ESC,  NO_Q,    NO_W,    NO_E,    NO_R,    NO_T,    NO_Y,    NO_U,    NO_I,    NO_O,    NO_P,    KC_BSPC,
    KC_TAB,  NO_A,    NO_S,    NO_D,    NO_F,    NO_G,    NO_H,    NO_J,    NO_K,    NO_L,    NO_QUOT, KC_DEL,
    KC_LSFT, NO_Z,    NO_X,    NO_C,    NO_V,    NO_B,    NO_N,    NO_M,    NO_COMM, NO_DOT,  NO_MINS, KC_ENT,
    KC_LCTL, TT(QMK), KC_LGUI, KC_LALT, MO(LWR), KC_SPC,  KC_SPC,  MO(RSE), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),

  /** Swap Lower & Raise
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │     │     │     │     │     │     │     │     │     │     │     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │     │     │     │     │     │     │     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │     │     │     │     │     │     │     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │     │     │     │ RSE │           │ LWR │     │     │     │     │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [SLR] = LAYOUT_ortho_4x12(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, MO(RSE), _______, _______, MO(LWR), _______, _______, _______, _______
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
  [LWR] = LAYOUT_ortho_4x12(
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
  [RSE] = LAYOUT_ortho_4x12(
    NO_PIPE, NO_1,    NO_2,    NO_3,    NO_4,    NO_5,    NO_6,    NO_7,    NO_8,    NO_9,    NO_0,    NO_ARNG,
    _______, _______, _______, _______, _______, _______, _______, NO_BSLS, NO_LCBR, NO_RCBR, NO_OSTR, NO_AE,
    _______, _______, _______, _______, _______, _______, _______, NO_DIAE, NO_LABK, NO_RABK, NO_CIRC, _______,
    _______, _______, _______, KC_ALGR, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
  ),

  /** Combine (Lower + Raise)
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ F01 │ F02 │ F03 │ F04 │ F05 │ F06 │ F07 │ F08 │ F09 │ F10 │ F11 │ F12 │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ Mod │ SaI │ HuI │ VaI │ Tog │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ CwT │ --- │ --- │ --- │ --- │ Mut │ Mic │ Rmd │ SaD │ HuD │ VaD │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ --- │ [_] │ PlayPause │ [_] │ Prv │ Vo- │ Vo+ │ Nxt │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [CMB] = LAYOUT_ortho_4x12(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_F9,   KC_F10,  KC_F11,  KC_F12,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD,  RGB_SAI, RGB_HUI, RGB_VAI, RGB_TOG,
    CW_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_F20,  RGB_RMOD, RGB_SAD, RGB_HUD, RGB_VAD, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_MPLY, KC_MPLY, _______,  KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
  ),

  /** QMK
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │     │ Ms2 │ MsU │ Ms1 │ MwU │ N07 │ N08 │ N09 │ Rec │ --- │ RST │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │ MsL │ MsD │ MsR │ MwD │ N04 │ N05 │ N06 │ Ply │ Lck │     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │ --- │ --- │ --- │ --- │ N01 │ N02 │ N03 │     │     │     │     │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │     │ [_] │     │     │ Ms1 │  NumPad0  │ NLk │     │     │     │     │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [QMK] = LAYOUT_ortho_4x12(
    _______, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_U, KC_KP_7, KC_KP_8, KC_KP_9, DM_REC1, XXXXXXX, MO(RST), _______,
    _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_KP_4, KC_KP_5, KC_KP_6, DM_PLY1, QK_LOCK, _______, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_KP_1, KC_KP_2, KC_KP_3, _______, _______, _______, _______,
    _______, _______, _______, _______, KC_BTN1, KC_KP_0, KC_KP_0, KC_NUM,  _______, _______, _______, _______
  ),

  /** Reset
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ QTY │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ SLR │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ --- │ --- │   Reset   │ --- │ --- │ --- │ --- │ --- │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [RST] = LAYOUT_ortho_4x12(
    DF(QTY), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    DF(SLR), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  )
};

// TODO brightness https://github.com/qmk/qmk_firmware/blob/master/docs/feature_rgb_matrix.md#examples-idindicator-examples
// const RGB ___ = {.r=0,   .g=0,   .b=0  };
// const RGB DWH = {.r=100, .g=100, .b=100};
// const RGB BLU = {.r=0,   .g=140, .b=255};
// const RGB LBL = {.r=160, .g=215, .b=255};
// const RGB RED = {.r=250, .g=30,  .b=30 };
// const RGB LRD = {.r=242, .g=153, .b=168};
// const RGB DRD = {.r=100, .g=0,   .b=0  };
//
// const RGB PROGMEM ledmap[][RGB_MATRIX_LED_COUNT] = {
//   [LWR] = {
//     BLU, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
//     BLU, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
//     BLU, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
//     BLU, BLU, BLU, BLU, BLU,    ___,   ___, ___, ___, ___, ___,
//   },
//   [RSE] = {
//     ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, BLU,
//     ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, BLU,
//     ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, BLU,
//     ___, ___, ___, ___, ___,    ___,   BLU, BLU, BLU, BLU, BLU,
//   },
//   [CMB] = {
//     BLU, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, BLU,
//     BLU, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, BLU,
//     BLU, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, BLU,
//     BLU, BLU, BLU, BLU, BLU,    BLU,   BLU, BLU, BLU, BLU, BLU,
//   },
//   [QMK] = {
//     LBL, ___, BLU, ___, ___, LBL, LBL, LBL, ___, ___, RED, ___,
//     ___, BLU, BLU, BLU, ___, LBL, LBL, LBL, ___, ___, LBL, ___,
//     ___, ___, ___, ___, ___, LBL, LBL, LBL, ___, ___, ___, ___,
//     ___, ___, ___, ___, ___,    LBL,   BLU, ___, ___, ___, ___,
//   },
//   [RST] = {
//     BLU, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
//     BLU, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
//     ___, ___, ___, ___, ___, LRD, LRD, ___, ___, ___, ___, ___,
//     ___, ___, ___, ___, LRD,    RED,   LRD, ___, ___, ___, ___,
//   },
//   [SUS] = {
//     ___, ___, ___, ___, DRD, DRD, DRD, ___, ___, ___, ___, ___,
//     ___, ___, ___, DRD, DRD, DWH, DWH, DRD, ___, ___, ___, ___,
//     ___, ___, ___, DRD, DRD, DRD, DRD, DRD, ___, ___, ___, ___,
//     ___, ___, ___, ___, DRD,    ___,   DRD, ___, ___, ___, ___,
//   },
// };

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, LWR, RSE, CMB);
}

// void set_layer_color(uint8_t layer) {
//   for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
//     RGB color = ledmap[layer][i];
//     rgb_matrix_set_color(i, color.r, color.g, color.b);
//   }
// }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t sus_word[3] = {NO_S, NO_U, NO_S};

  if (record->event.pressed) {
    sus_counter = (keycode == sus_word[sus_counter]) ? sus_counter+1 : 0;
  }

  return true;
};

// bool rgb_matrix_indicators_user(void) {
//   // TODO clear leds on QTY when returning
//   uint8_t layer = biton32(layer_state);
//
//   if (layer != QTY) {
//     set_layer_color(layer);
//   } else if (sus_counter >= 3) {
//     set_layer_color(SUS);
//   } else if (host_keyboard_led_state().caps_lock) {
//     rgb_matrix_set_color_all(0, 0, 0);
//     rgb_matrix_set_color(24, 255, 255, 255);
//   }
//
//   return true;
// }

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  // Disables 3 LEDs that are centered between spacebar keycaps
  int disable_leds[3] = {41, 43, 45};

  for (int i = 0; i < sizeof(disable_leds) / sizeof(disable_leds[0]); i++) {
    rgb_matrix_set_color(*(disable_leds + i), 0, 0, 0);
  }

  /* if (get_highest_layer(layer_state) > 0) { */
  /*     uint8_t layer = get_highest_layer(layer_state); */
  /**/
  /*     for (uint8_t row = 0; row < MATRIX_ROWS; ++row) { */
  /*         for (uint8_t col = 0; col < MATRIX_COLS; ++col) { */
  /*             uint8_t index = g_led_config.matrix_co[row][col]; */
  /**/
  /*             if (index >= led_min && index < led_max && index != NO_LED && */
  /*             keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) { */
  /*                 rgb_matrix_set_color(index, RGB_GREEN); */
  /*             } */
  /*         } */
  /*     } */
  /* } */
  return false;
  if (host_keyboard_led_state().caps_lock) {
      RGB_MATRIX_INDICATOR_SET_COLOR(5, 255, 255, 255); // assuming caps lock is at led #5
  } else {
      RGB_MATRIX_INDICATOR_SET_COLOR(41, 0, 0, 0);
  }
  return false;
}
