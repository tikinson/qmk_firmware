
#include "tknbrd/tknbrd0/custom_keycodes.h"
#include "tknbrd/tknbrd0/modules/cartridge/cartridge.h"
#include "tknbrd/tknbrd0/modules/protocol/protocol.h"
#include "tknbrd/tknbrd0/modules/event_queue/event_queue.h"
#include QMK_KEYBOARD_H
#include "keymap_ukrainian.h"
#include "tknbrd/tknbrd0/custom_keycodes.h"
#include "debug.h"
#include <stdio.h>
#include "oled_frames.h"

char wpm_str[10];

#define CAD LCTL(LALT(KC_DEL))

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _GAMINGONE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT (
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_LALT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(1),  KC_SPC,     KC_ENT,   MO(2), KC_BSPC
                                      //`--------------------------'  `--------------------------'
    ),

    [_LOWER] = LAYOUT (
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,   UA_GE,  KC_GRV, KC_LBRC, KC_RBRC, XXXXXXX,                      KC_PSCR,   KC_UP,  KC_DEL,  KC_CAPS, KC_NUM, UG_TOGG,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   CAD,                       KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, UG_PREV, UG_NEXT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT,   MO(3), KC_BSPC
                                      //`--------------------------'  `--------------------------'
    ),
    [_RAISE] = LAYOUT (
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,   KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,                      KC_MINS,  KC_EQL,  KC_GRV, KC_LBRC, KC_RBRC, KC_PIPE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,   KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,                      KC_UNDS, KC_PLUS, KC_TILD, KC_LCBR, KC_RCBR, KC_LALT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(3),  KC_SPC,     KC_ENT, _______, KC_BSPC
                                      //`--------------------------'  `--------------------------'
    ),
    [_ADJUST] = LAYOUT (
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                      KC_F7,    KC_F8,    KC_F9,  KC_F10, KC_F11,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TO(_GAMINGONE),                   CAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
                                      //`--------------------------'  `--------------------------'
    ),
    [_GAMINGONE] = LAYOUT (
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, TO(_QWERTY),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Q,    KC_S,    KC_D,    KC_F,    KC_C,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_LALT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_SPC,KC_ESC,  KC_ENT,    KC_LGUI,   HELLO, PING_C
                                      //`--------------------------'  `--------------------------'
    )
};

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable=true;
    //debug_matrix=true;
    debug_keyboard=true;
    //debug_mouse=true;
    //uart_init(115200);
    cartridge_init();

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //all the "user input" we will filter except dedicated keycodes
    return user_input(keycode, record);
};

void housekeeping_task_user(void) {
    cartridge_task();
};

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_A):
            // Do not force the mod-tap key press to be handled as a modifier
            // if any other key was pressed while the mod-tap key is held down.
            return false;
        default:
            // Force the= mod-tap key press to be handled as a modifier if any
            // other key was pressed while the mod-tap key is held down.
            return true;
    }
};



// OLED
#ifdef OLED_ENABLE

void suspend_power_down_kb(void) {
    //rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    //rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}

uint32_t anim_timer         = 0;
uint32_t anim_sleep         = 0;
uint8_t current_idle_frame = 0;
uint8_t current_tap_frame = 0;


static void render_animation(void) {
    void animation_phase(void) {
        if (get_current_wpm() <= IDLE_SPEED) {
            current_idle_frame = (current_idle_frame + 1) % IDLE_FRAMES;
            oled_write_raw_P(idle[abs((IDLE_FRAMES - 1) - current_idle_frame)], ANIM_SIZE);
        }

        if (get_current_wpm() > IDLE_SPEED && get_current_wpm() < TAP_SPEED) {
            oled_write_raw_P(prep[0], ANIM_SIZE);
        }

        if (get_current_wpm() >= TAP_SPEED) {
            current_tap_frame = (current_tap_frame + 1) % TAP_FRAMES;
            oled_write_raw_P(tap[abs((TAP_FRAMES - 1) - current_tap_frame)], ANIM_SIZE);
        }
    }
    if (get_current_wpm() != 000) {
        oled_on();  // Enables OLED on any alpha keypress

        if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            anim_timer = timer_read32();
            animation_phase();
        }

        anim_sleep = timer_read32();
    } else {
        if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
            oled_off();
        } else {
            if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                anim_timer = timer_read32();
                animation_phase();
            }
        }
    }
}

// Draw to OLED
bool oled_task_user(void) {
    render_animation();

    // WPM text
    oled_set_cursor(0, 0);
    sprintf(wpm_str, "%03d", get_current_wpm()); // %03d defines digits to display
    oled_write(wpm_str, false);

    // Layer text
    oled_set_cursor(0, 1);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("DFLT"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("LWR"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("RS"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("ADJ"), false);
            break;
        case _GAMINGONE:
            oled_write_P(PSTR("GMNG1"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    oled_set_cursor(0,2);

    switch (protocol_get_state()){
        case PROTOCOL_IDLE:
            oled_write_P(PSTR("IDLE"), false);
            break;

        case PROTOCOL_WAITING_PONG:
            oled_write_P(PSTR("WAIT"), false);
            break;

        case PROTOCOL_CONNECTED:
            oled_write_P(PSTR("LINK"), false);
            break;

        case PROTOCOL_DISCONNECTED:
            oled_write_P(PSTR("NO LINK"), false);
            break;
    }

    // Caps lock text
    led_t led_state = host_keyboard_led_state();
    oled_set_cursor(0, 3);
    oled_write_P(led_state.caps_lock ? PSTR("CAPS") : PSTR(""), false);

    return false;
}
#endif

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD),                             ENCODER_CCW_CW(KC_LEFT, KC_RIGHT)  }, // default layout
    [1] = { ENCODER_CCW_CW(KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP),           ENCODER_CCW_CW(UG_PREV, UG_NEXT)  }, //
    [2] = { ENCODER_CCW_CW(UG_HUED, UG_HUEU),                             ENCODER_CCW_CW(UG_SATD, UG_SATU)  }, //
    [3] = { ENCODER_CCW_CW(UG_VALD, UG_VALU),                             ENCODER_CCW_CW(UG_SPDU, UG_SPDD) }, // two mods are pressed
    [4] = { ENCODER_CCW_CW(KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP),           ENCODER_CCW_CW(MS_WHLU, MS_WHLD)  }, // gaming layout
};
#endif
