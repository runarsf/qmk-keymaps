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
  SUS,
  GAY,
};

enum planck_keycodes {
  PLACEHOLDER = SAFE_RANGE,
  SARCASM,
  MU_MGLV,
  MU_USSR,
  MU_MCSR,
  MU_ROLL,
  MU_SUSS,
  MU_SLAY,
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;
uint8_t sus_counter = 0;
uint8_t slay_counter = 0;
uint8_t gay_counter = 0;

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
   * │ --- │ --- │ --- │ --- │ MuT │ MuM │ --- │ Mod │ SaI │ HuI │ VaI │ Tog │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ CwT │ --- │ --- │ --- │ AuT │ --- │ --- │ Rmd │ SaD │ HuD │ VaD │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ --- │ [_] │ PlayPause │ [_] │ Prv │ Vo- │ Vo+ │ Nxt │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [CMB] = LAYOUT_planck_grid(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_F9,   KC_F10,  KC_F11,  KC_F12,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MU_TOG,  MU_MOD,  XXXXXXX, RGB_MOD,  RGB_SAI, RGB_HUI, RGB_VAI, RGB_TOG,
    CW_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, AU_TOG,  XXXXXXX, XXXXXXX, RGB_RMOD, RGB_SAD, RGB_HUD, RGB_VAD, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_MPLY, KC_MPLY, _______,  KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
  ),

  /** QMK
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ Lck │ MwD │ MsU │ MwU │ Rec │ N07 │ N08 │ N09 │ --- │ --- │ --- │ RST │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ MsL │ MsD │ MsR │ Ply │ N04 │ N05 │ N06 │ --- │ --- │ --- │ SRC │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ --- │ --- │ N01 │ N02 │ N03 │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ [_] │ --- │ Ms2 │ Ms1 │  NumPad0  │ NLk │ --- │ --- │ --- │ --- │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [QMK] = LAYOUT_planck_grid(
    QK_LOCK, KC_WH_D, KC_MS_U, KC_WH_U, DM_REC1, KC_KP_7, KC_KP_8, KC_KP_9, XXXXXXX, XXXXXXX, XXXXXXX, MO(RST),
    XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, DM_PLY1, KC_KP_4, KC_KP_5, KC_KP_6, XXXXXXX, XXXXXXX, XXXXXXX, SARCASM,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_KP_1, KC_KP_2, KC_KP_3, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, _______, XXXXXXX, KC_BTN2, KC_BTN1, KC_KP_0, KC_KP_0, KC_NUM,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  /** Reset
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
   * │ --- │ --- │ --- │ --- │ Rol │ --- │ --- │ Rus │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ SUS │ --- │ --- │ --- │ Gay │ --- │ --- │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ --- │ Mch │ --- │ --- │ Mgl │ --- │ --- │ --- │ --- │
   * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
   * │ --- │ --- │ --- │ --- │ --- │   Reset   │ --- │ --- │ --- │ --- │ --- │
   * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
   */
  [RST] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MU_ROLL, XXXXXXX, XXXXXXX, MU_USSR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, MU_SUSS, XXXXXXX, XXXXXXX, XXXXXXX, MU_SLAY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MU_MCSR, XXXXXXX, XXXXXXX, MU_MGLV, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  )
};

// TODO brightness https://github.com/qmk/qmk_firmware/blob/master/docs/feature_rgb_matrix.md#examples-idindicator-examples
const RGB ___ = {.r=0,   .g=0,   .b=0  };
const RGB DWH = {.r=100, .g=100, .b=100};
const RGB BLU = {.r=0,   .g=140, .b=255};
const RGB LBL = {.r=160, .g=215, .b=255};
const RGB RED = {.r=250, .g=30,  .b=30 };
const RGB LRD = {.r=242, .g=153, .b=168};
const RGB DRD = {.r=100, .g=0,   .b=0  };

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
  [SUS] = {
    ___, ___, ___, ___, DRD, DRD, DRD, ___, ___, ___, ___, ___,
    ___, ___, ___, DRD, DRD, DWH, DWH, DRD, ___, ___, ___, ___,
    ___, ___, ___, DRD, DRD, DRD, DRD, DRD, ___, ___, ___, ___,
    ___, ___, ___, ___, DRD,    ___,   DRD, ___, ___, ___, ___,
  },
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, LWR, RSE, CMB);
}

void set_layer_color(uint8_t layer) {
  for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    RGB color = ledmap[layer][i];
    rgb_matrix_set_color(i, color.r, color.g, color.b);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef AUDIO_ENABLE
  static float megalovania[][2] = SONG(MEGALOVANIA);
  static float among_us[][2] = SONG(AMONG_US);
  static float ussr_anthem[][2] = SONG(USSR_ANTHEM);
  static float michishirube[][2] = SONG(MICHISHIRUBE);
  static float rick_roll[][2] = SONG(RICK_ROLL);
  static float slay_soul_sister[][2] = SONG(SLAY_SOUL_SISTER);
#endif

  static bool sarcastic = false;
  static bool capitalized = false;
  static uint8_t same = 0;
  static uint16_t sus_word[3] = {NO_S, NO_U, NO_S};
  static uint16_t slay_word[4] = {NO_S, NO_L, NO_A, NO_Y};
  static uint16_t gay_word[3] = {NO_G, NO_A, NO_Y};

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

#ifdef AUDIO_ENABLE
  if (record->event.pressed) {
    sus_counter = (keycode == sus_word[sus_counter]) ? sus_counter+1 : 0;
    if (sus_counter >= 3) {
      PLAY_SONG(among_us);
    }
    slay_counter = (keycode == slay_word[slay_counter]) ? slay_counter+1 : 0;
    if (slay_counter >= 4) {
      PLAY_SONG(slay_soul_sister);
    }
    gay_counter = (keycode == gay_word[gay_counter]) ? gay_counter+1 : 0;
    if (gay_counter >= 3) {
      PLAY_SONG(slay_soul_sister);
    }
  }
#endif

  switch (keycode) {
    case SARCASM:
      if (record->event.pressed) {
        sarcastic = !sarcastic;
        if (capitalized) {
          register_code(KC_CAPS);
          unregister_code(KC_CAPS);
        }
      }
      return false;
      break;
    case MU_MGLV:
      if (record->event.pressed) {
        PLAY_SONG(megalovania);
      }
      return false;
      break;
    case MU_USSR:
      if (record->event.pressed) {
        PLAY_SONG(ussr_anthem);
      }
      return false;
      break;
    case MU_MCSR:
      if (record->event.pressed) {
        PLAY_SONG(michishirube);
      }
      return false;
      break;
    case MU_ROLL:
      if (record->event.pressed) {
        PLAY_SONG(rick_roll);
      }
      return false;
      break;
    case MU_SUSS:
      if (record->event.pressed) {
        PLAY_SONG(among_us);
      }
      return false;
      break;
    case MU_SLAY:
      if (record->event.pressed) {
        PLAY_SONG(slay_soul_sister);
      }
      return false;
      break;
  }
  return true;
};

bool rgb_matrix_indicators_user(void) {
  // TODO clear leds on QTY when returning
  uint8_t layer = biton32(layer_state);

  if (layer != QTY) {
    set_layer_color(layer);
  } else if (sus_counter >= 3) {
    set_layer_color(SUS);
  } else if (host_keyboard_led_state().caps_lock) {
    rgb_matrix_set_color_all(0, 0, 0);
    rgb_matrix_set_color(24, 255, 255, 255);
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
    case RSE:
    case LWR:
      return false;
    default:
      return true;
  }
}