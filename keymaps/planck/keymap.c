#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"
#include <stdlib.h>

#ifdef AUDIO_ENABLE
  #include "muse.h"
#endif

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
  SARCASM,
  MU_STOP,
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
uint8_t wash_counter = 0;
uint8_t gay_counter = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[QTY] = LAYOUT_planck_grid(
//    ┌──────┬─────────┬──────┬──────┬─────────┬──────┬──────┬─────────┬─────────┬────────┬─────────┬──────┐
//    │ esc  │  NO_Q   │ NO_W │ NO_E │  NO_R   │ NO_T │ NO_Y │  NO_U   │  NO_I   │  NO_O  │  NO_P   │ bspc │
//    ├──────┼─────────┼──────┼──────┼─────────┼──────┼──────┼─────────┼─────────┼────────┼─────────┼──────┤
//    │ tab  │  NO_A   │ NO_S │ NO_D │  NO_F   │ NO_G │ NO_H │  NO_J   │  NO_K   │  NO_L  │ NO_QUOT │ del  │
//    ├──────┼─────────┼──────┼──────┼─────────┼──────┼──────┼─────────┼─────────┼────────┼─────────┼──────┤
//    │ lsft │  NO_Z   │ NO_X │ NO_C │  NO_V   │ NO_B │ NO_N │  NO_M   │ NO_COMM │ NO_DOT │ NO_MINS │ ent  │
//    ├──────┼─────────┼──────┼──────┼─────────┼──────┼──────┼─────────┼─────────┼────────┼─────────┼──────┤
//    │ lctl │ TT(QMK) │ lgui │ lalt │ MO(LWR) │ spc  │ spc  │ MO(RSE) │  left   │  down  │   up    │ rght │
//    └──────┴─────────┴──────┴──────┴─────────┴──────┴──────┴─────────┴─────────┴────────┴─────────┴──────┘
  KC_ESC  , NO_Q    , NO_W    , NO_E    , NO_R    , NO_T   , NO_Y   , NO_U    , NO_I    , NO_O    , NO_P    , KC_BSPC,
  KC_TAB  , NO_A    , NO_S    , NO_D    , NO_F    , NO_G   , NO_H   , NO_J    , NO_K    , NO_L    , NO_QUOT , KC_DEL ,
  KC_LSFT , NO_Z    , NO_X    , NO_C    , NO_V    , NO_B   , NO_N   , NO_M    , NO_COMM , NO_DOT  , NO_MINS , KC_ENT ,
  KC_LCTL , TT(QMK) , KC_LGUI , KC_LALT , MO(LWR) , KC_SPC , KC_SPC , MO(RSE) , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT
),

[SLR] = LAYOUT_planck_grid(
//    ┌─────┬─────┬─────┬─────┬─────────┬─────┬─────┬─────────┬─────┬─────┬─────┬─────┐
//    │     │     │     │     │         │     │     │         │     │     │     │     │
//    ├─────┼─────┼─────┼─────┼─────────┼─────┼─────┼─────────┼─────┼─────┼─────┼─────┤
//    │     │     │     │     │         │     │     │         │     │     │     │     │
//    ├─────┼─────┼─────┼─────┼─────────┼─────┼─────┼─────────┼─────┼─────┼─────┼─────┤
//    │     │     │     │     │         │     │     │         │     │     │     │     │
//    ├─────┼─────┼─────┼─────┼─────────┼─────┼─────┼─────────┼─────┼─────┼─────┼─────┤
//    │     │     │     │     │ MO(RSE) │     │     │ MO(LWR) │     │     │     │     │
//    └─────┴─────┴─────┴─────┴─────────┴─────┴─────┴─────────┴─────┴─────┴─────┴─────┘
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______,
  _______ , _______ , _______ , _______ , MO(RSE) , _______ , _______ , MO(LWR) , _______ , _______ , _______ , _______
),

[LWR] = LAYOUT_planck_grid(
//    ┌────────┬─────────┬─────────┬─────────┬────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
//    │ NO_GRV │ NO_EXLM │  NO_AT  │ NO_HASH │ NO_DLR │ NO_PERC │ NO_AMPR │ NO_SLSH │ NO_TILD │ NO_EQL  │ NO_PLUS │ NO_ACUT │
//    ├────────┼─────────┼─────────┼─────────┼────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
//    │        │         │ NO_DQUO │         │        │         │         │         │ NO_LBRC │ NO_RBRC │ NO_ASTR │         │
//    ├────────┼─────────┼─────────┼─────────┼────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
//    │        │         │         │         │        │         │         │         │ NO_LPRN │ NO_RPRN │         │         │
//    ├────────┼─────────┼─────────┼─────────┼────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
//    │        │         │         │         │        │         │         │         │         │         │         │         │
//    └────────┴─────────┴─────────┴─────────┴────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
  NO_GRV  , NO_EXLM , NO_AT   , NO_HASH , NO_DLR  , NO_PERC , NO_AMPR , NO_SLSH , NO_TILD , NO_EQL  , NO_PLUS , NO_ACUT,
  _______ , _______ , NO_DQUO , _______ , _______ , _______ , _______ , _______ , NO_LBRC , NO_RBRC , NO_ASTR , _______,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , NO_LPRN , NO_RPRN , _______ , _______,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
),

[RSE] = LAYOUT_planck_grid(
//    ┌─────────┬──────┬──────┬──────┬──────┬──────┬──────┬─────────┬─────────┬─────────┬─────────┬─────────┐
//    │ NO_PIPE │ NO_1 │ NO_2 │ NO_3 │ NO_4 │ NO_5 │ NO_6 │  NO_7   │  NO_8   │  NO_9   │  NO_0   │ NO_ARNG │
//    ├─────────┼──────┼──────┼──────┼──────┼──────┼──────┼─────────┼─────────┼─────────┼─────────┼─────────┤
//    │         │      │      │      │      │      │      │ NO_BSLS │ NO_LCBR │ NO_RCBR │ NO_OSTR │  NO_AE  │
//    ├─────────┼──────┼──────┼──────┼──────┼──────┼──────┼─────────┼─────────┼─────────┼─────────┼─────────┤
//    │         │      │      │      │      │      │      │ NO_DIAE │ NO_LABK │ NO_RABK │ NO_CIRC │         │
//    ├─────────┼──────┼──────┼──────┼──────┼──────┼──────┼─────────┼─────────┼─────────┼─────────┼─────────┤
//    │         │      │      │ aLGR │      │      │      │         │  home   │  pgdn   │  pgup   │   end   │
//    └─────────┴──────┴──────┴──────┴──────┴──────┴──────┴─────────┴─────────┴─────────┴─────────┴─────────┘
  NO_PIPE , NO_1    , NO_2    , NO_3    , NO_4    , NO_5    , NO_6    , NO_7    , NO_8    , NO_9    , NO_0    , NO_ARNG,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , NO_BSLS , NO_LCBR , NO_RCBR , NO_OSTR , NO_AE  ,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , NO_DIAE , NO_LABK , NO_RABK , NO_CIRC , _______,
  _______ , _______ , _______ , KC_ALGR , _______ , _______ , _______ , _______ , KC_HOME , KC_PGDN , KC_PGUP , KC_END
),

[CMB] = LAYOUT_planck_grid(
//    ┌─────────┬────┬────┬─────────┬────────┬──────┬──────┬──────────┬─────────┬─────────┬─────────┬─────────┐
//    │   f1    │ f2 │ f3 │   f4    │   f5   │  f6  │  f7  │    f8    │   f9    │   f10   │   f11   │   f12   │
//    ├─────────┼────┼────┼─────────┼────────┼──────┼──────┼──────────┼─────────┼─────────┼─────────┼─────────┤
//    │   no    │ no │ no │ MU_MOD  │ MU_TOG │  no  │  no  │ RGB_MOD  │ RGB_SAI │ RGB_HUI │ RGB_VAI │ RGB_TOG │
//    ├─────────┼────┼────┼─────────┼────────┼──────┼──────┼──────────┼─────────┼─────────┼─────────┼─────────┤
//    │ CW_TOGG │ no │ no │ MU_STOP │ AU_TOG │ mute │ f20  │ RGB_RMOD │ RGB_SAD │ RGB_HUD │ RGB_VAD │   no    │
//    ├─────────┼────┼────┼─────────┼────────┼──────┼──────┼──────────┼─────────┼─────────┼─────────┼─────────┤
//    │   no    │ no │ no │   no    │        │ mply │ mply │          │  mprv   │  vold   │  volu   │  mnxt   │
//    └─────────┴────┴────┴─────────┴────────┴──────┴──────┴──────────┴─────────┴─────────┴─────────┴─────────┘
  KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_F7   , KC_F8    , KC_F9   , KC_F10  , KC_F11  , KC_F12 ,
  XXXXXXX , XXXXXXX , XXXXXXX , MU_MOD  , MU_TOG  , XXXXXXX , XXXXXXX , RGB_MOD  , RGB_SAI , RGB_HUI , RGB_VAI , RGB_TOG,
  CW_TOGG , XXXXXXX , XXXXXXX , MU_STOP , AU_TOG  , KC_MUTE , KC_F20  , RGB_RMOD , RGB_SAD , RGB_HUD , RGB_VAD , XXXXXXX,
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ , KC_MPLY , KC_MPLY , _______  , KC_MPRV , KC_VOLD , KC_VOLU , KC_MNXT
),

[QMK] = LAYOUT_planck_grid(
//    ┌─────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬─────────┬─────────┬─────────┬─────┐
//    │     │ btn2 │ ms_u │ btn1 │ wh_u │ kp_7 │ kp_8 │ kp_9 │ DM_REC1 │   no    │ MO(RST) │     │
//    ├─────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼─────────┼─────────┼─────────┼─────┤
//    │     │ ms_l │ ms_d │ ms_r │ wh_d │ kp_4 │ kp_5 │ kp_6 │ DM_PLY1 │ QK_LOCK │ SARCASM │     │
//    ├─────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼─────────┼─────────┼─────────┼─────┤
//    │     │  no  │  no  │  no  │  no  │ kp_1 │ kp_2 │ kp_3 │         │         │         │     │
//    ├─────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼─────────┼─────────┼─────────┼─────┤
//    │     │      │      │      │ btn1 │ kp_0 │ kp_0 │ nUM  │         │         │         │     │
//    └─────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴─────────┴─────────┴─────────┴─────┘
  _______ , KC_BTN2 , KC_MS_U , KC_BTN1 , KC_WH_U , KC_KP_7 , KC_KP_8 , KC_KP_9 , DM_REC1 , XXXXXXX , MO(RST) , _______,
  _______ , KC_MS_L , KC_MS_D , KC_MS_R , KC_WH_D , KC_KP_4 , KC_KP_5 , KC_KP_6 , DM_PLY1 , QK_LOCK , SARCASM , _______,
  _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_KP_1 , KC_KP_2 , KC_KP_3 , _______ , _______ , _______ , _______,
  _______ , _______ , _______ , _______ , KC_BTN1 , KC_KP_0 , KC_KP_0 , KC_NUM  , _______ , _______ , _______ , _______
),

[RST] = LAYOUT_planck_grid(
//    ┌─────────┬────┬────┬────┬────┬─────────┬─────────┬────┬────┬────┬────┬────┐
//    │ DF(QTY) │ no │ no │ no │ no │   no    │   no    │ no │ no │ no │ no │ no │
//    ├─────────┼────┼────┼────┼────┼─────────┼─────────┼────┼────┼────┼────┼────┤
//    │ DF(SLR) │ no │ no │ no │ no │   no    │   no    │ no │ no │ no │ no │ no │
//    ├─────────┼────┼────┼────┼────┼─────────┼─────────┼────┼────┼────┼────┼────┤
//    │   no    │ no │ no │ no │ no │   no    │   no    │ no │ no │ no │ no │ no │
//    ├─────────┼────┼────┼────┼────┼─────────┼─────────┼────┼────┼────┼────┼────┤
//    │   no    │ no │ no │ no │ no │ QK_BOOT │ QK_BOOT │ no │ no │ no │ no │ no │
//    └─────────┴────┴────┴────┴────┴─────────┴─────────┴────┴────┴────┴────┴────┘
  DF(QTY) , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  DF(SLR) , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , QK_BOOT , QK_BOOT , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
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
    LBL, ___, BLU, ___, ___, LBL, LBL, LBL, ___, ___, RED, ___,
    ___, BLU, BLU, BLU, ___, LBL, LBL, LBL, ___, ___, LBL, ___,
    ___, ___, ___, ___, ___, LBL, LBL, LBL, ___, ___, ___, ___,
    ___, ___, ___, ___, ___,    LBL,   BLU, ___, ___, ___, ___,
  },
  [RST] = {
    BLU, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
    BLU, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
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
  static bool sarcastic = false;
  static bool capitalized = false;
  static uint8_t same = 0;
  static uint16_t sus_word[3] = {NO_S, NO_U, NO_S};
  static uint16_t gay_word[3] = {NO_G, NO_A, NO_Y};
  static uint16_t slay_word[4] = {NO_S, NO_L, NO_A, NO_Y};
  static uint16_t wash_word[11] = {NO_P, NO_U, NO_S, NO_S, NO_Y, KC_SPC, NO_F, NO_R, NO_E, NO_S, NO_H};

#ifdef AUDIO_ENABLE
  static float no_sound[][2] = SONG(NO_SOUND);
  static float among_us[][2] = SONG(AMONG_US);
  static float slay_soul_sister[][2] = SONG(SLAY_SOUL_SISTER);
  static float samsung_washing_machine[][2] = SONG(SAMSUNG_WASHING_MACHINE);

  if (record->event.pressed) {
    sus_counter = (keycode == sus_word[sus_counter]) ? sus_counter+1 : 0;
    slay_counter = (keycode == slay_word[slay_counter]) ? slay_counter+1 : 0;
    gay_counter = (keycode == gay_word[gay_counter]) ? gay_counter+1 : 0;
    wash_counter = (keycode == wash_word[wash_counter]) ? wash_counter+1 : 0;
    if (sus_counter >= 3) {
      PLAY_SONG(among_us);
    }
    if (gay_counter >= 3 || slay_counter >= 4) {
      PLAY_SONG(slay_soul_sister);
    }
    if (wash_counter >= 11) {
      PLAY_SONG(samsung_washing_machine);
    }
  }
#endif

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
      if (record->event.pressed) {
        sarcastic = !sarcastic;
        if (capitalized) {
          register_code(KC_CAPS);
          unregister_code(KC_CAPS);
        }
      }
      return false;
      break;
    case MU_STOP:
      if (record->event.pressed) {
        PLAY_SONG(no_sound);
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
