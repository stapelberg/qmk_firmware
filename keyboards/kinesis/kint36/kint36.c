#include "kint36.h"
#include "chprintf.h"

// called once when the firmware starts up
void matrix_init_kb(void) {
    matrix_init_user();
    led_init_ports();
}

// runs every cycle
void matrix_scan_kb(void) {
    // TODO: measure how long since the last scan callback, that is how long a scan takes
    // only update variable, don’t print. user can query by toggling caps lock LED
    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // could this be where we start latency measurement? is this when a keypress
    // was detected? or should we start before debounce?

    return process_record_user(keycode, record);
}

#define ledTurnOff palSetLine
#define ledTurnOn palClearLine

#define LED_KEYPAD LINE_PIN12
#define LED_SCROLL_LOCK LINE_PIN24
#define LED_NUM_LOCK LINE_PIN25
#define LED_CAPS_LOCK LINE_PIN26

void led_init_ports() {
    palSetLineMode(LED_KEYPAD, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LED_SCROLL_LOCK, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LED_NUM_LOCK, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LED_CAPS_LOCK, PAL_MODE_OUTPUT_PUSHPULL);

    ledTurnOff(LED_KEYPAD);
    ledTurnOff(LED_SCROLL_LOCK);
    ledTurnOff(LED_NUM_LOCK);
    ledTurnOff(LED_CAPS_LOCK);

// Turn on the Teensy 3.6 Power LED:
#define LED_POWER LINE_PIN13
    palSetLineMode(LED_POWER, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLine(LED_POWER);
}

void led_set_kb(uint8_t usb_led) {
    // TODO: take a time measurement here
    chprintf((BaseSequentialStream *)&SD5, "led_set_kb\r\n");
    dprintf("led_set_kb\n");
    if (usb_led & (1 << USB_LED_COMPOSE)) {
        ledTurnOn(LED_KEYPAD);
    } else {
        ledTurnOff(LED_KEYPAD);
    }

    if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
        ledTurnOn(LED_SCROLL_LOCK);
    } else {
        ledTurnOff(LED_SCROLL_LOCK);
    }

    if (usb_led & (1 << USB_LED_NUM_LOCK)) {
        ledTurnOn(LED_NUM_LOCK);
    } else {
        ledTurnOff(LED_NUM_LOCK);
    }

    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        ledTurnOn(LED_CAPS_LOCK);
    } else {
        ledTurnOff(LED_CAPS_LOCK);
    }
}
