SRC += modules/cartridge/cartridge.c
SRC += modules/event_queue/event_queue.c
SRC += modules/hud/hud.c
SRC += modules/transport/transport_uart.c

CONSOLE_ENABLE = yes

RGBLIGHT_ENABLE = yes
RGBLIGHT_ANIMATIONS = yes

ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes

DEBOUNCE_TYPE = asym_eager_defer_pk

NO_SUSPEND_POWER_DOWN = yes

OLED_ENABLE = yes
OLED_TRANSPORT = i2c
OLED_DRIVER_ENABLE = yes

OPT_DEFS += -DHAL_USE_I2C=TRUE

UART_DRIVER_REQUIRED = yes
