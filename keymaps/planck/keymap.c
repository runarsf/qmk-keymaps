#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"
#include "common.h"

#ifdef AUDIO_ENABLE
#include "muse.h"
#include "user_song_list.h"
#endif

#define RECEIVE _______

#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;
#endif

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
        KC_LCTL, TT(QMK), KC_LGUI, KC_LALT, MO(LWR), KC_SPC, KC_SPC,
        TD(TD_RSE_QMK), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),

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
    [SWP] = LAYOUT_planck_grid(
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
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │ F01 │ F02 │ F03 │ F04 │ F05 │ F06 │ F07 │ F08 │ F09 │ F10 │ F11 │ F12 │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ RST │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │ --- │ QTY │ SWP │ --- │ --- │ --- │ --- │ --- │ --- │ --- │ Dbg │ --- │
     * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
     * │ --- │ --- │ --- │ --- │ [_] │ PlayPause │ [_] │ Prv │ Vo- │ Vo+ │ Nxt │
     * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
     */
    [CMB] = LAYOUT_planck_grid(
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
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │ Ms1 │ MsU │ Ms2 │ MwU │ N07 │ N08 │ N09 │ --- │ --- │  +  │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │ MsL │ MsD │ MsR │ MwD │ N04 │ N05 │ N06 │ --- │ --- │     │ RST │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │ --- │ --- │ --- │ --- │ N01 │ N02 │ N03 │     │     │     │     │
     * ├─────┼─────┼─────┼─────┼─────┼─────┴─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │ [_] │     │     │ Ms1 │  NumPad0  │ NLk │     │     │     │     │
     * └─────┴─────┴─────┴─────┴─────┴───────────┴─────┴─────┴─────┴─────┴─────┘
     */
    [QMK] = LAYOUT_planck_grid(
        //
        _______, MS_BTN1, MS_UP, MS_BTN2, MS_WHLU, KC_KP_7, KC_KP_8, KC_KP_9,
        XXXXXXX, XXXXXXX, NO_PLUS, _______,
        //
        _______, MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLD, KC_KP_4, KC_KP_5, KC_KP_6,
        XXXXXXX, XXXXXXX, _______, QK_BOOT,
        //
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_KP_1, KC_KP_2, KC_KP_3,
        _______, _______, _______, _______,
        //
        _______, RECEIVE, _______, _______, MS_BTN1, KC_KP_0, KC_KP_0, KC_NUM,
        _______, _______, _______, _______)};

tap_dance_action_t tap_dance_actions[] = {
    [TD_RSE_QMK] =
        ACTION_TAP_DANCE_FN_ADVANCED(NULL, rse_qmk_finished, rse_qmk_reset),
};

#ifdef AUDIO_ENABLE
// Typing `word` anywhere can play a song and/or flash an RGB layer. To add
// one: define the melody in user_song_list.h (if it plays a song), declare
// the trigger word below, and add one WORD_SONG() / WORD_RGB() /
// WORD_SONG_RGB() entry to word_triggers[].
typedef struct {
  const uint16_t *word;
  uint8_t word_length;
  float (*song)[2];    // NULL if this word doesn't play a song
  uint16_t song_length;
  uint8_t rgb_layer;   // layer to flash, or NO_RGB_LAYER
} word_trigger_t;

#define COUNT_OF(x) (sizeof(x) / sizeof((x)[0]))
#define NO_RGB_LAYER 0xFF
#define RGB_FLASH_DURATION_MS 1000

#define WORD_SONG(word, song) {word, COUNT_OF(word), song, COUNT_OF(song), NO_RGB_LAYER}
#define WORD_RGB(word, layer) {word, COUNT_OF(word), NULL, 0, layer}
#define WORD_SONG_RGB(word, song, layer) {word, COUNT_OF(word), song, COUNT_OF(song), layer}

static const uint16_t sus_word[] = {NO_S, NO_U, NO_S};
static const uint16_t gay_word[] = {NO_G, NO_A, NO_Y};
static const uint16_t slay_word[] = {NO_S, NO_L, NO_A, NO_Y};
static const uint16_t wash_word[] = {NO_P, NO_U, NO_S, NO_S, NO_Y, KC_SPC,
                                      NO_F, NO_R, NO_E, NO_S, NO_H};
static const uint16_t michael_word[] = {NO_C, NO_H, NO_E, NO_E, NO_S, NO_Y, KC_SPC,
                                         NO_M, NO_I, NO_C, NO_H, NO_A, NO_E, NO_L};

static float among_us[][2] = SONG(AMONG_US);
static float slay_soul_sister[][2] = SONG(SLAY_SOUL_SISTER);
static float samsung_washing_machine[][2] = SONG(SAMSUNG_WASHING_MACHINE);
static float cheesy_michael[][2] = SONG(CHEESY_MICHAEL);

static const word_trigger_t word_triggers[] = {
    WORD_SONG_RGB(sus_word, among_us, SUS),
    WORD_SONG(gay_word, slay_soul_sister),
    WORD_SONG(slay_word, slay_soul_sister),
    WORD_SONG(wash_word, samsung_washing_machine),
    WORD_SONG(michael_word, cheesy_michael),
};

static uint8_t word_trigger_progress[COUNT_OF(word_triggers)] = {0};
static uint32_t word_trigger_rgb_hit[COUNT_OF(word_triggers)] = {0};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef AUDIO_ENABLE
  if (record->event.pressed) {
    for (uint8_t i = 0; i < COUNT_OF(word_triggers); i++) {
      const word_trigger_t *trigger = &word_triggers[i];
      uint8_t *progress = &word_trigger_progress[i];
      *progress = (keycode == trigger->word[*progress]) ? *progress + 1 : 0;
      if (*progress >= trigger->word_length) {
        if (trigger->song) {
          audio_play_melody((float (*)[][2])trigger->song, trigger->song_length, false);
        }
        if (trigger->rgb_layer != NO_RGB_LAYER) {
          word_trigger_rgb_hit[i] = timer_read32();
        }
        *progress = 0;
      }
    }
  }
#endif

  // SHIFT+BTN1 for Mouse2 in QMK layer
  if (get_highest_layer(layer_state) == QMK) {
    bool shift_held = get_mods() & MOD_MASK_SHIFT;
    if (keycode == MS_BTN1 && record->event.pressed && shift_held) {
      uint8_t saved_mods = get_mods();
      clear_mods();
      tap_code(MS_BTN2);
      set_mods(saved_mods);
      return false;
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
  case RSE:
  case LWR:
    return false;
  default:
    return true;
  }
}

// Reduces firmware size
#ifndef MAGIC_ENABLE
uint16_t keycode_config(uint16_t keycode) { return keycode; }
uint8_t mod_config(uint8_t mod) { return mod; }
#endif

// Flat LED order: rows 0-2 have 12 LEDs each, row 3 has 11 (spacebar = 1 LED).
// Row 3 positions: Ctl Qmk Win Alt LWR Spc RSE Lft Dwn Up Rgt
const RGB layer_colors[LAYER_COUNT][RGB_MATRIX_LED_COUNT] = {
    [QTY] = {
        ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM,
        ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM,
        ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM,
        ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM,
    },
    [SWP] = {
        ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM,
        ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM,
        ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM,
        ANIM, ANIM, ANIM, ANIM, ANIM, ___, ANIM, ANIM, ANIM, ANIM, ANIM,
    },
    [LWR] = {
        ANIM, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
        ANIM, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
        ANIM, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
        ANIM, ANIM, ANIM, ANIM, ANIM, ___, ___, ___, ___, ___, ___,
    },
    [RSE] = {
        ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ANIM,
        ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ANIM,
        ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ANIM,
        ___, ___, ___, ___, ___, ___, ANIM, ANIM, ANIM, ANIM, ANIM,
    },
    [CMB] = {
        ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM, ANIM,
        ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, RED,
        ___, BLUE, BLUE, ___, ___, ___, ___, ___, ___, ___, YELLOW, ___,
        ___, ___, ___, ___, ___, GREEN, ___, GREEN, GREEN, GREEN, GREEN,
    },
    [QMK] = {
        ___, ___, ANIM, ___, ___, BLUE, BLUE, BLUE, ___, ___, ___, ___,
        ___, ANIM, ANIM, ANIM, ___, BLUE, BLUE, BLUE, ___, ___, ___, ___,
        ___, ___, ___, ___, ___, BLUE, BLUE, BLUE, ___, ___, ___, ___,
        ___, ___, ___, ___, ___, BLUE, ___, ___, ___, ___, ___,
    },
    [SUS] = {
        ___, ___, ___, ___, RED, RED, RED, ___, ___, ___, ___, ___,
        ___, ___, ___, RED, RED, RED, ANIM, ANIM, ___, ___, ___, ___,
        ___, ___, ___, RED, RED, RED, RED, ___, ___, ___, ___, ___,
        ___, ___, ___, ___, RED, ___, RED, ___, ___, ___, ___,
    },
};

void set_layer_colors(uint8_t layer) {
  if (layer >= LAYER_COUNT)
    return;

  uint8_t brightness = rgb_matrix_get_val();

  for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    RGB color = layer_colors[layer][i];
    if (color.r == 255 && color.g == 255 && color.b == 255)
      continue; // ANIM: let animation show through

    rgb_matrix_set_color(i, (color.r * brightness) / 255,
                         (color.g * brightness) / 255,
                         (color.b * brightness) / 255);
  }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  uint8_t current_layer = get_highest_layer(layer_state);

  set_layer_colors(current_layer);

#ifdef AUDIO_ENABLE
  for (uint8_t i = 0; i < COUNT_OF(word_triggers); i++) {
    const word_trigger_t *trigger = &word_triggers[i];
    if (trigger->rgb_layer != NO_RGB_LAYER &&
        timer_elapsed32(word_trigger_rgb_hit[i]) < RGB_FLASH_DURATION_MS) {
      set_layer_colors(trigger->rgb_layer);
    }
  }
#endif

  return false;
}
