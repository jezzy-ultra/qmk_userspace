#include <sys/types.h>
#include "action_layer.h"
#include "color.h"
#include "config.h"
#include "keyboard.h"
#include "keycodes.h"
#include "process_tap_dance.h"
#include "quantum.h"
#include "rgb_matrix.h"
#include QMK_KEYBOARD_H

// clang-format off

enum layers{
    QWERTY,
    CLMKDH,  // Colemak Mod-DH
    FN,
};

enum {
    TD_FN_LCTL,
};

void mod_dance_on_each_tap(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        layer_on(FN);
    } else {
        layer_off(FN);
        register_code(KC_LCTL);
        // skip remaining TAPPING_TERM time if two taps are counted to reduce latency
        state->finished = true;
    }
}

void mod_dance_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        layer_off(FN);
    } else {
        unregister_code(KC_LCTL);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_FN_LCTL] = ACTION_TAP_DANCE_FN_ADVANCED(mod_dance_on_each_tap, NULL, mod_dance_reset),
};

#define TD_MOD TD(TD_FN_LCTL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWERTY] = LAYOUT_ansi_98(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,             KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_DEL,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_P7,    KC_P8,    KC_P9,
        TD_MOD,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,    KC_P1,    KC_P2,    KC_P3,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_RWIN,    KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,    KC_PDOT,  KC_PENT),
    [CLMKDH] = LAYOUT_ansi_98(
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,  _______,  _______,  _______,
        _______,  KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,     KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,  _______,    _______,  _______,            _______,  _______,  _______,
        _______,  KC_A,     KC_R,     KC_S,     KC_T,     KC_G,     KC_M,     KC_N,     KC_E,     KC_I,     KC_O,     _______,              _______,            _______,  _______,  _______,  _______,
        _______,            KC_X,     KC_C,     KC_D,     KC_V,     KC_Z,     KC_K,     KC_H,     _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______),
    [FN] = LAYOUT_ansi_98(
        QK_BOOT,            _______,  _______,  _______,  _______,  EE_CLR,   _______,  _______,  _______,  QK_RBT,   _______,    _______,  _______,            KC_PSCR,  KC_SCRL,  KC_PAUS,  RM_TOGG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  KC_INS,             KC_NUM,   RM_SPDD,  RM_SPDU,  _______,
        _______,  KC_ESC,   KC_UP,    KC_ENT,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            RM_HUEU,  RM_SATU,  RM_VALU,
        _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  _______,  _______,              _______,            RM_HUED,  RM_SATD,  RM_VALD,  _______,
        _______,            KC_DEL,   KC_BSPC,  KC_CAPS,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  KC_PGUP,  _______,  _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  KC_APP,     _______,  KC_HOME,  KC_PGDN,  KC_END,   _______,  NK_TOGG,  _______),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [CLMKDH] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [FN]     = { ENCODER_CCW_CW(RM_PREV, RM_NEXT)},
};
#endif  // ENCODER_MAP_ENABLE

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        // Switch between QWERTY and CLMKDH layers
        default_layer_set(1UL << (active ? 1 : 0));
    }
    // Skip running the default `dip_switch_update_kb()`
    return false;
}
#endif  // DIP_SWITCH_ENABLE

uint8_t get_current_layer(void) {
    // Check if any temporary layers are active first
    if (layer_state > 0) {
        return get_highest_layer(layer_state);
    }
    return get_highest_layer(default_layer_state);
}

#if defined(RGB_MATRIX_ENABLE)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == RM_TOGG) {
        if (record->event.pressed) {
            switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL:
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_set_color_all(0, 0, 0);
                    break;
                default:
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    break;
            }
        }
        if (!rgb_matrix_is_enabled()) {
            rgb_matrix_set_flags(LED_FLAG_ALL);
            rgb_matrix_enable();
        }

        return false;
    }

    return true;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    rgb_t orange   = { .r = 255, .g = 43,  .b = 0   };
    rgb_t lavender = { .r = 255, .g = 40,  .b = 255 };
    rgb_t magenta  = { .r = 255, .g = 28,  .b = 40  };
    rgb_t green    = { .r = 102, .g = 255, .b = 0   };

    #ifdef CAPS_LOCK_LED_INDEX
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, orange.r, orange.g, orange.b);
    }
    #endif  // CAPS_LOCK_LED_INDEX

    #ifdef NUM_LOCK_LED_INDEX
    if (host_keyboard_led_state().num_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(NUM_LOCK_LED_INDEX, orange.r, orange.g, orange.b);
    }
    #endif  // NUM_LOCK_LED_INDEX

    #ifdef SCROLL_LOCK_LED_INDEX
    if (host_keyboard_led_state().scroll_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(SCROLL_LOCK_LED_INDEX, orange.r, orange.g, orange.b);
    }
    #endif  // SCROLL_LOCK_LED_INDEX

    #ifdef LAYER_INDICATOR_LED_INDEX
    uint8_t current_layer = get_current_layer();
    switch (current_layer) {
        case QWERTY:
            RGB_MATRIX_INDICATOR_SET_COLOR(LAYER_INDICATOR_LED_INDEX, lavender.r, lavender.g, lavender.b);
            break;
        case CLMKDH:
            RGB_MATRIX_INDICATOR_SET_COLOR(LAYER_INDICATOR_LED_INDEX, magenta.r, magenta.g, magenta.b);
            break;
        case FN:
            RGB_MATRIX_INDICATOR_SET_COLOR(LAYER_INDICATOR_LED_INDEX, green.r, green.g, green.b);
            break;
        default:
            RGB_MATRIX_INDICATOR_SET_COLOR(LAYER_INDICATOR_LED_INDEX, orange.r, orange.g, orange.b);
            break;
    }
    #endif  // LAYER_INDICATOR_LED_INDEX

    // continue to `rgb_matrix_indicators_advanced_kb`?
    return false;
}

#endif  // RGB_MATRIX_ENABLE

void keyboard_post_init_user(void) {
    debug_enable   = true;
    debug_matrix   = true;
    debug_keyboard = true;
    debug_mouse    = true;
}
