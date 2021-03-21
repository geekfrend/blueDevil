#include QMK_KEYBOARD_H
#include "5x7.h"


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _FN     1
#define _NUMPAD 2

// Some basic macros
#define TASK    LCTL(LSFT(KC_ESC))
#define TAB_R   LCTL(KC_TAB)
#define TAB_L   LCTL(LSFT(KC_TAB))
#define TAB_RO  LCTL(LSFT(KC_T))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_5x7(
  // left hand
   KC_GRV,    KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,
   KC_TAB,    KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   KC_LBRC,
   KC_LSFT,   KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   KC_PGUP,
   KC_LCTL,   KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,
                       KC_LCMD, KC_SPC,
                                        KC_LEFT,  KC_RGHT,
                                                        KC_LOPT, KC_ESC,
                                                        LCAG(KC_ENT),KC_MUTE,
        // right hand
              KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
              KC_RBRC, KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_BSLS,
              KC_PGDN, KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
                       KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_DEL,
                                         KC_DEL,   KC_ENT,
                       KC_DOWN, KC_UP,
    TG(1), TG(2),
    KC_VOLD, KC_VOLU
    ),

[_FN] = LAYOUT_5x7(
  // left hand
   _______,   KC_F1,     KC_F2,      KC_F3,    KC_F4,     KC_F5,    KC_F6,
   _______,   _______,   _______,    KC_UP,    _______,   _______,  _______,
   _______,   _______,   KC_LEFT,    KC_DOWN,  KC_RGHT,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,
                         _______,   _______,
                               _______, _______,
                               _______, _______,
                               _______, _______,
        // right hand
                     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,    KC_F12,    _______,
                     _______,   _______,   _______,   _______,   _______,   _______,   _______,
                     _______,   _______,   _______,   _______,   _______,   KC_UP,     _______,
                                _______,   _______,   _______,   KC_LEFT,   KC_DOWN,   KC_RIGHT,
                                                      _______,   _______,
        _______, _______,
        TG(0),   TG(2),
        _______, _______),

[_NUMPAD] = LAYOUT_5x7(
  // left hand
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   _______,  _______,
   _______,   _______,   _______,   _______,   _______,   RESET,
                         _______,   _______,
                               _______, _______,
                               _______, _______,
                               _______, _______,
        // right hand
                     _______,   _______,   KC_NLCK,   _______,   KC_PMNS,   KC_PPLS,   _______,
                     _______,   _______,   KC_P7,     KC_P8,     KC_P9,     _______,   _______,
                     _______,   _______,   KC_P4,     KC_P5,     KC_P6,     KC_PAST,   _______,
                                _______,   KC_P1,     KC_P2,     KC_P3,     KC_PSLS,   _______,
                                                      KC_P0,     KC_PDOT,
        _______, _______,
        TG(0),   TG(1),
        _______, _______),

};

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _FN:
            oled_write_P(PSTR("FN\n"), false);
            break;
        case _NUMPAD:
            oled_write_P(PSTR("NUMPAD\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}
#endif
