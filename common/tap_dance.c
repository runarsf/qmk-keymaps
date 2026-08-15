#include QMK_KEYBOARD_H
#include "layers.h"
#include "tap_dance.h"

typedef struct {
  bool is_press_action;
  uint8_t state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD,
  DOUBLE_TAP,
  DOUBLE_HOLD,
  DOUBLE_SINGLE_TAP,
};

static uint8_t cur_dance(tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed)
      return SINGLE_TAP;
    else
      return SINGLE_HOLD;
  } else if (state->count == 2) {
    if (!state->pressed)
      return DOUBLE_TAP;
    else
      return DOUBLE_HOLD;
  } else
    return 8;
}

static tap rse_qmk_tap_state = {.is_press_action = true, .state = 0};

void rse_qmk_finished(tap_dance_state_t *state, void *user_data) {
  rse_qmk_tap_state.state = cur_dance(state);
  switch (rse_qmk_tap_state.state) {
  case SINGLE_HOLD:
    layer_on(RSE);
    break;
  case DOUBLE_HOLD:
    layer_on(QMK);
    break;
  }
}

void rse_qmk_reset(tap_dance_state_t *state, void *user_data) {
  switch (rse_qmk_tap_state.state) {
  case SINGLE_HOLD:
    layer_off(RSE);
    break;
  case DOUBLE_HOLD:
    layer_off(QMK);
    break;
  }
  rse_qmk_tap_state.state = 0;
}

