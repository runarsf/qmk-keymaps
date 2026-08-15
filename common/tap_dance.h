#pragma once

enum {
  TD_RSE_QMK,
};

void rse_qmk_finished(tap_dance_state_t *state, void *user_data);
void rse_qmk_reset(tap_dance_state_t *state, void *user_data);
