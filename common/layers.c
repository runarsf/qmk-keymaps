#include QMK_KEYBOARD_H
#include "layers.h"

uint8_t sus_counter = 0;

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, LWR, RSE, CMB);
}
