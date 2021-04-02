#include QMK_KEYBOARD_H
#include "5x7.h"


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _FN     1
#define _NUMPAD 2

//layer macros
#define TOQWERTY TG(_QWERTY)
#define TOFN TG(_FN)
#define TONUM TG(_NUMPAD)


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
    TOFN, TONUM,
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
   TOFN, TONUM,
   _______, _______
   ),

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
    KC_NO, TONUM,
    _______, _______
    )

};

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }

    return rotation;
}


void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_logo();  // Renders a static logo
        oled_scroll_left();  // Turns on scrolling
    } else {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("qwerty\n"), false);
            break;
        case _FN:
            oled_write_P(PSTR("function\n"), false);
            break;
        case _NUMPAD:
            oled_write_P(PSTR("numbers\n"), false);
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
}
#endif

