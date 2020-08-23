#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _FUNCTION 1
#define _NUMPAD 2

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

//Tap dance enums
enum {
    TD_LSFT_ENT = 0,
    TD_BR_R,
    TD_BR_L,
    TD_RESET,
};

void right_bracket(qk_tap_dance_state_t *state, void *user_data);
void end_right_bracket(qk_tap_dance_state_t *state, void *user_data);

void left_bracket(qk_tap_dance_state_t *state, void *user_data);
void end_left_bracket(qk_tap_dance_state_t *state, void *user_data);

void safe_reset(qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_LSFT_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_ENT),
    [TD_BR_R] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, right_bracket, end_right_bracket),
    [TD_BR_L] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, left_bracket, end_left_bracket),
    [TD_RESET] = ACTION_TAP_DANCE_FN(safe_reset),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LGUI, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_BTN1,          KC_BTN2, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RALT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                TT(_NUMPAD), KC_SPC,  TD(TD_BR_L),                TD(TD_BR_R), KC_ENT, MO(_FUNCTION)
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_FUNCTION] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, KC_UP,   _______, _______,                            _______, KC_INS,  KC_HOME, KC_PGUP, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______,                           _______, KC_DEL,  KC_END,  KC_PGDN, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_NUBS, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_NUMPAD] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
TD(TD_RESET), _______, _______, _______, _______, _______,                            _______, KC_P7,   KC_P8,   KC_P9,   KC_MINS, KC_EQL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, RGB_TOG, RGB_MOD, RGB_RMOD,RGB_HUI, RGB_HUD,                            _______, KC_P4,   KC_P5,   KC_P6,   _______, KC_RBRC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, RGB_M_P, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD,                            _______, KC_P1,   KC_P2,   KC_P3,   _______, KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, RGB_SPI, RGB_SPD, _______, _______, _______, _______,          _______, _______, KC_P0,   KC_P0,   KC_PDOT, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};

void keyboard_post_init_user(void) {
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
    debug_mouse=true;
    //backlight_enable();
    //backlight_level(5);
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (layer_state_is(_QWERTY)) {
            if (clockwise) {
                tap_code16(C(KC_Z));;
            } else {
                tap_code16(C(KC_Y));
            }
        } else if (layer_state_is(_FUNCTION)) {
            if (clockwise) {
                tap_code16(KC_WH_D);
            } else {
                tap_code16(KC_WH_U);
            }
        } else {
            //layer state is _NUMPAD
            report_mouse_t currentReport = pointing_device_get_report();
            if (clockwise) {
                currentReport.y = -100;
            } else {
                currentReport.y = 100;
            }
            pointing_device_set_report(currentReport);
            pointing_device_send();
        }
    } else if (index == 1) {
        if (layer_state_is(_QWERTY)){
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(KC_LALT);
            }
            if (clockwise) {
                alt_tab_timer = timer_read();
                tap_code16(KC_TAB);
            } else {
                alt_tab_timer = timer_read();
                tap_code16(S(KC_TAB));
            }
        } else if (layer_state_is(_FUNCTION)) {
            if (clockwise) {
                tap_code16(C(KC_TAB));
            } else {
                tap_code16(S(C(KC_TAB)));
            }
        } else {
            //layer state is _NUMPAD
            if (clockwise) {
                tap_code16(KC_MS_R);
            } else {
                tap_code16(KC_MS_L);
            }
        }
    }
}

void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 400) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}

void left_bracket(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count)
    {
    case 1:
        register_code16(KC_LALT);
        break;
    case 2:
        register_code16(S(KC_8));
        break;
    case 3:
        register_code16(ALGR(KC_7));
        break;
    case 4:
    default:
        register_code16(ALGR(KC_8));
        break;
    }
}

void end_left_bracket(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count)
    {
    case 1:
        unregister_code16(KC_LALT);
        break;
    case 2:
        unregister_code16(S(KC_8));
        break;
    case 3:
        unregister_code16(ALGR(KC_7));
        break;
    case 4:
    default:
        unregister_code16(ALGR(KC_8));
        break;
    }
}

void right_bracket(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count)
    {
    case 1:
        register_code16(KC_LSFT);
        break;
    case 2:
        register_code16(S(KC_9));
        break;
    case 3:
        register_code16(ALGR(KC_0));
        break;
    case 4:
    default:
        register_code16(ALGR(KC_9));
        break;
    }
}

void end_right_bracket(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count)
    {
    case 1:
        unregister_code16(KC_LSFT);
        break;
    case 2:
        unregister_code16(S(KC_9));
        break;
    case 3:
        unregister_code16(ALGR(KC_0));
        break;
    case 4:
    default:
        unregister_code16(ALGR(KC_9));
        break;
    }
}

void safe_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count >= 3) {
        // Reset the keyboard if you tap the key more than three times
        reset_keyboard();
        reset_tap_dance(state);
    }
}
