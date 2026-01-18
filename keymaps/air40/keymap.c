#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"

#define RECEIVE _______

enum layers {
  QTY,
  SWP,
  LWR,
  RSE,
  CMB,
  QMK,
  LAYER_COUNT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /** Qwerty
     * ┌───────────────────────────────────────────────────────────────────────┐
     * │ Esc │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │ Bsp │
     * |───────────────────────────────────────────────────────────────────────┤
     * │ Tab │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  '  │ Del │
     * |───────────────────────────────────────────────────────────────────────┤
     * │ Sft │  Z  │  X  │  C  │  V  │  B  │  N  │  M  │ , ; │ . : │ - _ │ Ent │
     * |───────────────────────────────────────────────────────────────────────┤
     * │ Ctl │ Qmk │ Win │ Alt │ LWR │   Space   │ RSE │ Lft │ Dwn │ Up  │ Rgt │
     * └───────────────────────────────────────────────────────────────────────┘
     */
    [QTY] = LAYOUT_ortho_4x12(
        //
        KC_ESC, NO_Q, NO_W, NO_E, NO_R, NO_T, NO_Y, NO_U, NO_I, NO_O, NO_P,
        KC_BSPC,
        //
        KC_TAB, NO_A, NO_S, NO_D, NO_F, NO_G, NO_H, NO_J, NO_K, NO_L, NO_QUOT,
        KC_DEL,
        //
        KC_LSFT, NO_Z, NO_X, NO_C, NO_V, NO_B, NO_N, NO_M, NO_COMM, NO_DOT,
        NO_MINS, KC_ENT,
        //
        KC_LCTL, TT(QMK), KC_LGUI, KC_LALT, MO(LWR), KC_SPC, KC_SPC, MO(RSE),
        KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),

    /** Swap Lower & Raise
     * ┌───────────────────────────────────────────────────────────────────────┐
     * │     │     │     │     │     │     │     │     │     │     │     │     │
     * |───────────────────────────────────────────────────────────────────────┤
     * │     │     │     │     │     │     │     │     │     │     │     │     │
     * |───────────────────────────────────────────────────────────────────────┤
     * │     │     │     │     │     │     │     │     │     │     │     │     │
     * |───────────────────────────────────────────────────────────────────────┤
     * │     │     │     │     │ RSE │           │ LWR │     │     │     │     │
     * └───────────────────────────────────────────────────────────────────────┘
     */
    [SWP] = LAYOUT_ortho_4x12(
        //
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,
        //
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,
        //
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,
        //
        _______, _______, _______, _______, MO(RSE), _______, _______, MO(LWR),
        _______, _______, _______, _______),

    /** Lower
     * ┌───────────────────────────────────────────────────────────────────────┐
     * │  `  │  !  │  @  │  #  │  $  │  %  │  &  │  /  │  (  │  )  │  =  │  ~  │
     * |───────────────────────────────────────────────────────────────────────┤
     * │  ´  │ --- │  "  │ --- │ --- │ --- │ --- │  \  │  [  │  ]  │  *  │     │
     * |───────────────────────────────────────────────────────────────────────┤
     * │     │ --- │ --- │ --- │ --- │ --- │ --- │  ¨  │  {  │  }  │  +  │     │
     * |───────────────────────────────────────────────────────────────────────┤
     * │     │     │     │     │ [_] │           │ CMB │ AGr │     │     │     │
     * └───────────────────────────────────────────────────────────────────────┘
     */
    [LWR] = LAYOUT_ortho_4x12(
        //
        NO_GRV, NO_EXLM, NO_AT, NO_HASH, NO_DLR, NO_PERC, NO_AMPR, NO_SLSH,
        NO_LPRN, NO_RPRN, NO_EQL, NO_TILD,
        //
        NO_ACUT, XXXXXXX, NO_DQUO, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, NO_BSLS,
        NO_LBRC, NO_RBRC, NO_ASTR, _______,
        //
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, NO_DIAE,
        NO_LCBR, NO_RCBR, NO_PLUS, _______,
        //
        _______, _______, _______, _______, RECEIVE, _______, _______, _______,
        KC_ALGR, _______, _______, _______),

    /** Raise
     * ┌───────────────────────────────────────────────────────────────────────┐
     * │  |  │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  Å  │
     * |───────────────────────────────────────────────────────────────────────┤
     * │     │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │  Ø  │  Æ  │
     * |───────────────────────────────────────────────────────────────────────┤
     * │     │ --- │ --- │ --- │ --- │ --- │ --- │ --- │  <  │  >  │  ^  │     │
     * |───────────────────────────────────────────────────────────────────────┤
     * │     │     │     │     │ CMB │           │ [_] │ Hom │ PgD │ PgU │ End │
     * └───────────────────────────────────────────────────────────────────────┘
     */
    [RSE] = LAYOUT_ortho_4x12(
        //
        NO_PIPE, NO_1, NO_2, NO_3, NO_4, NO_5, NO_6, NO_7, NO_8, NO_9, NO_0,
        NO_ARNG,
        //
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, NO_OSTR, NO_AE,
        //
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        NO_LABK, NO_RABK, NO_CIRC, _______,
        //
        _______, _______, _______, _______, _______, _______, _______, RECEIVE,
        KC_HOME, KC_PGDN, KC_PGUP, KC_END),

    /** Combine (Lower + Raise)
     * ┌───────────────────────────────────────────────────────────────────────┐
     * │ F01 │ F02 │ F03 │ F04 │ F05 │ F06 │ F07 │ F08 │ F09 │ F10 │ F11 │ F12 │
     * |───────────────────────────────────────────────────────────────────────┤
     * │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ RST │
     * |───────────────────────────────────────────────────────────────────────┤
     * │ --- │ QTY │ SWP │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ Dbg │ --- │
     * |───────────────────────────────────────────────────────────────────────┤
     * │ --- │ --- │ --- │ --- │ [_] │ PlayPause │ [_] │ Prv │ Vo- │ Vo+ │ Nxt │
     * └───────────────────────────────────────────────────────────────────────┘
     */
    [CMB] = LAYOUT_ortho_4x12(
        //
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
        KC_F11, KC_F12,
        //
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
        //
        XXXXXXX, DF(QTY), DF(SWP), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, KC_F13, XXXXXXX,
        //
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RECEIVE, KC_MPLY, KC_MPLY, RECEIVE,
        KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT),

    /** QMK
     * ┌───────────────────────────────────────────────────────────────────────┐
     * │     │ --- │ MsU │ --- │ --- │ N07 │ N08 │ N09 │ --- │ --- │  +  │     │
     * |───────────────────────────────────────────────────────────────────────┤
     * │     │ MsL │ MsD │ MsR │ --- │ N04 │ N05 │ N06 │ --- │ --- │     │     │
     * |───────────────────────────────────────────────────────────────────────┤
     * │     │ --- │ --- │ --- │ --- │ N01 │ N02 │ N03 │     │     │     │     │
     * |───────────────────────────────────────────────────────────────────────┤
     * │     │ [_] │     │     │ 1/2 │  NumPad0  │ NLk │     │     │     │     │
     * └───────────────────────────────────────────────────────────────────────┘
     */
    [QMK] = LAYOUT_ortho_4x12(
        //
        _______, XXXXXXX, MS_UP, XXXXXXX, XXXXXXX, KC_KP_7, KC_KP_8, KC_KP_9,
        XXXXXXX, XXXXXXX, NO_PLUS, _______,
        //
        _______, MS_LEFT, MS_DOWN, MS_RGHT, XXXXXXX, KC_KP_4, KC_KP_5, KC_KP_6,
        XXXXXXX, XXXXXXX, _______, _______,
        //
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_KP_1, KC_KP_2, KC_KP_3,
        _______, _______, _______, _______,
        //
        _______, RECEIVE, _______, _______, MS_BTN1, KC_KP_0, KC_KP_0, KC_NUM,
        _______, _______, _______, _______),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // SHIFT+LOWER for Mouse2 in QMK layer
  if (get_highest_layer(layer_state) == QMK) {
    bool shift_held = get_mods() & MOD_MASK_SHIFT;

    switch (keycode) {
    case MS_BTN1:
      if (record->event.pressed && shift_held) {
        // Clear shift mods temporarily to prevent interference
        uint8_t saved_mods = get_mods();
        clear_mods();

        tap_code(MS_BTN2);

        // Restore the original modifiers
        set_mods(saved_mods);

        return false;
      }

      break;
    }
  }

  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, LWR, RSE, CMB);
}

// Reduces firmware size
#ifndef MAGIC_ENABLE
uint16_t keycode_config(uint16_t keycode) { return keycode; }
uint8_t mod_config(uint8_t mod) { return mod; }
#endif

const RGB ___ = {.r = 0, .g = 0, .b = 0};
// TODO: Could this be 256 instead?
const RGB ANIM = {.r = 255, .g = 255, .b = 255};
const RGB BLUE = {.r = 0, .g = 140, .b = 255};
const RGB RED = {.r = 255, .g = 0, .b = 0};
const RGB GREEN = {.r = 0, .g = 255, .b = 0};
const RGB YELLOW = {.r = 255, .g = 255, .b = 0};
const RGB PURPLE = {.r = 128, .g = 0, .b = 128};
const RGB CYAN = {.r = 0, .g = 255, .b = 255};

const RGB layer_colors[LAYER_COUNT][4][12] = {
    [QTY] = {{ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM,
              ANIM},
             {ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM,
              ANIM},
             {ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM,
              ANIM},
             {ANIM, ANIM, ANIM, ANIM, ___, ANIM, ANIM, ___, ANIM, ANIM, ANIM,
              ANIM}},

    [SWP] = {{ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM,
              ANIM},
             {ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM,
              ANIM},
             {ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM,
              ANIM},
             {ANIM, ANIM, ANIM, ANIM, ANIM, ___, ___, ANIM, ANIM, ANIM, ANIM,
              ANIM}},

    [LWR] = {{ANIM, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___},
             {ANIM, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___},
             {ANIM, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___},
             {ANIM, ANIM, ANIM, ANIM, ANIM, ___, ___, ___, ___, ___, ___, ___}},

    [RSE] = {{___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ANIM},
             {___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ANIM},
             {___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ANIM},
             {___, ___, ___, ___, ___, ___, ___, ANIM, ANIM, ANIM, ANIM, ANIM}},

    [CMB] = {{ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM,
              ANIM},
             {___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, RED},
             {___, BLUE, BLUE, ___, ___, ___, ___, ___, ___, ___, YELLOW, ___},
             {___, ___, ___, ___, ___, GREEN, GREEN, ___, GREEN, GREEN, GREEN,
              GREEN}},

    [QMK] = {{___, ___, ANIM, ___, ___, BLUE, BLUE, BLUE, ___, ___, ___, ___},
             {___, ANIM, ANIM, ANIM, ___, BLUE, BLUE, BLUE, ___, ___, ___, ___},
             {___, ___, ___, ___, ___, BLUE, BLUE, BLUE, ___, ___, ___, ___},
             {___, ___, ___, ___, ___, BLUE, ___, ___, ___, ___, ___, ___}},
};

uint8_t get_led_index(uint8_t row, uint8_t col) {
  // Handle special case for spacebar (indices 42, 44, 45 don't exist in
  // matrix)
  if (row == 3 && (col == 5 || col == 6)) {
    // Spacebar positions - map to actual LED indices
    return (col == 5) ? 43 : 41; // Based on the matrix layout in led.c
  }

  return g_led_config.matrix_co[row][col];
}

void set_layer_colors(uint8_t layer) {
  if (layer >= LAYER_COUNT)
    return;

  // Get current brightness level
  uint8_t brightness = rgb_matrix_get_val();

  for (uint8_t row = 0; row < 4; row++) {
    for (uint8_t col = 0; col < 12; col++) {
      RGB color = layer_colors[layer][row][col];
      uint8_t led_index = get_led_index(row, col);

      if (color.r == 255 && color.g == 255 && color.b == 255) {
        continue;
      } else {
        uint8_t scaled_r = (color.r * brightness) / 255;
        uint8_t scaled_g = (color.g * brightness) / 255;
        uint8_t scaled_b = (color.b * brightness) / 255;
        rgb_matrix_set_color(led_index, scaled_r, scaled_g, scaled_b);
      }
    }
  }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  uint8_t current_layer = get_highest_layer(layer_state);

  // For layers other than QTY, turn off all LEDs first
  // if (current_layer != QTY) {
  //   for (uint8_t i = led_min; i < led_max; i++) {
  //     rgb_matrix_set_color(i, 0, 0, 0);
  //   }
  // }

  // Apply the colors for the current layer
  set_layer_colors(current_layer);

  if (current_layer < LAYER_COUNT) {
    uint8_t brightness = rgb_matrix_get_val();

    // LEDs 42 and 44 (around spacebar) are orphaned, we need to set them
    // manually
    RGB color_left = layer_colors[current_layer][3][5];
    RGB color_right = layer_colors[current_layer][3][6];

    // Only set if not ANIM (let animation show through)
    if (!(color_left.r == 255 && color_left.g == 255 && color_left.b == 255)) {
      rgb_matrix_set_color(42, (color_left.r * brightness) / 255,
                           (color_left.g * brightness) / 255,
                           (color_left.b * brightness) / 255);
    }
    if (!(color_right.r == 255 && color_right.g == 255 &&
          color_right.b == 255)) {
      rgb_matrix_set_color(44, (color_right.r * brightness) / 255,
                           (color_right.g * brightness) / 255,
                           (color_right.b * brightness) / 255);
    }
  }

  // Always disable problematic spacebar LEDs
  // int disable_leds[] = {42, 44, 45};
  // for (int i = 0; i < sizeof(disable_leds) / sizeof(disable_leds[0]); i++) {
  //   if (disable_leds[i] >= led_min && disable_leds[i] < led_max) {
  //     rgb_matrix_set_color(disable_leds[i], 0, 0, 0);
  //   }
  // }

  int disable_leds[4] = {
      41, 45, // When using a 1x2u spacebar, these LEDs shine between the
              // keycaps on the side.
      42, 44  // These LEDs shine a bit too bright when using a 1x2u spacebar.
  };
  for (int i = 0; i < sizeof(disable_leds) / sizeof(disable_leds[0]); i++) {
    rgb_matrix_set_color(disable_leds[i], 0, 0, 0);
  }

  return false;
}
