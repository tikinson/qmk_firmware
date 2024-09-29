#include QMK_KEYBOARD_H

enum layers {
    _layerOne,
    _layerTwo,
    _layerThree,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_layerOne] = LAYOUT (
  //,-----------------------------.                  
        MO(1),    KC_W,   MO(2),   
  //|--------+--------+--------+--|             
  KC_MS_WH_UP, KC_CAPS,   KC_MS_WH_DOWN,   // THIS line is for navigation buttons keycodes
  //|--------+--------+--------+--|             
         KC_A,    KC_S,   KC_D,   
  //|--------+--------+--------+--|             
      KC_LEFT,  KC_NUM,   KC_RIGHT   // THIS line is for navigation buttons keycodes
  //|--------+--------+--------+--|    
    ),
    [_layerTwo] = LAYOUT (
    //,-----------------------------.                  
        _______,KC_KB_POWER,   MO(3),   
    //|--------+--------+--------+--|             
    	KC_PGUP, KC_TRNS,   KC_PGDN ,   // THIS line is for navigation buttons keycodes
    //|--------+--------+--------+--|             
        KC_MAIL, KC_WSCH,   KC_ENT,   
    //|--------+--------+--------+--|             
        KC_MRWD, KC_MSTP,   KC_MFFD   // THIS line is for navigation buttons keycodes
    //|--------+--------+--------+--|    
    ),
    [_layerThree] = LAYOUT (
    //,-----------------------------.                  
        MO(3), KC_MYCM,    _______,   
    //|--------+--------+--------+--|             
        KC_BRIU, KC_TRNS,   KC_BRID,   // THIS line is for navigation buttons keycodes
    //|--------+--------+--------+--|             
        KC_LNG1, KC_LNG2,   KC_LNG3,   
    //|--------+--------+--------+--|             
    KC_KB_VOLUME_DOWN, KC_MUTE,   KC_KB_VOLUME_UP   // THIS line is for navigation buttons keycodes
    //|--------+--------+--------+--|    
    )

};