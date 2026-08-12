#include "stdint.h"
typedef struct{
    uint8_t x;
    uint8_t y;
} hud_position_t;

typedef enum {
    HUD_AREA_WPM,
    HUD_AREA_LAYER,
    HUD_AREA_STATUS,
    HUD_AREA_RECORD,
} hud_area_t;

bool hud_init(void);
bool hud_notify(const char *text);
bool hud_notify_by_position(const char *text, hud_position_t position);
bool hud_notify_by_area(const char *text, hud_area_t area);
bool hud_render_task(void);
