#include <stdbool.h>
#include "hud.h"
#include "tknbrd/tknbrd0/modules/cartridge/cartridge.h"
#include "tknbrd/tknbrd0/modules/protocol/protocol.h"



static const hud_position_t hud_area_positions[] = {
    [HUD_AREA_WPM]    = { .x = 0,  .y = 0 },
    [HUD_AREA_LAYER]  = { .x = 0,  .y = 1 },
    [HUD_AREA_STATUS] = { .x = 0,  .y = 2 },
    [HUD_AREA_RECORD] = { .x = 18, .y = 0 },
};

bool hud_init(void){
    return true;
};

bool hud_notify(const char *text){
    return true;
};

bool hud_notify_by_position(const char *text, const hud_position_t position){
    oled_set_cursor(position.x, position.y);
    oled_write(text, false);
    return true;
};

bool hud_notify_by_area(const char *text, hud_area_t area){
    return hud_notify_by_position(text, hud_area_positions[area]);
};

// polling some states to show it on oled or maybe create animation etc.
// keymap layers indication is in keymap, here are all other stuff.

bool hud_render_task(){
    oled_set_cursor(0,2);

    switch (protocol_get_state()){
        case PROTOCOL_IDLE:
            oled_write_P(PSTR("IDLE"), false);
            break;

        case PROTOCOL_WAITING:
            oled_write_P(PSTR("WAITING"), false);
            break;

        case PROTOCOL_CONNECTED:
            oled_write_P(PSTR("LINK"), false);
            break;

        case PROTOCOL_DISCONNECTED:
            oled_write_P(PSTR("NO LINK"), false);
            break;

        default:
            break;
    }

    oled_set_cursor(18,0);
    switch (cartridge_get_state()) {
        case STATE_RECORDING:
            oled_write_P(PSTR("REC"), false);
            break;

        case STATE_IDLE:
            oled_write_P(PSTR("   "), false);
            break;

        default:
            break;
    }
    return false;
};
