#include "bsp/board_api.h"
#include <stdbool.h>
#include <stdint.h>

#include "board.h"
#include "ch32v20x.h"

#include "led.h"
#include "queued_task.h"

static void led_blinking_task(void) {
    static bool led_state = false;

    GPIO_WriteBit(BLINK_PORT, BLINK_PIN, led_state & 0x1);
    led_state = !led_state;
}

void sd_led_set(bool host, bool ts) {
    GPIO_WriteBit(SD_HOST_LED_PORT, SD_HOST_LED_PIN, host & 0x1);
    GPIO_WriteBit(SD_TS_LED_PORT, SD_TS_LED_PIN, ts & 0x1);
}

void led_init(void) {
    GPIO_InitTypeDef sd_host_led_init = {
        .GPIO_Pin = SD_HOST_LED_PIN,
        .GPIO_Mode = GPIO_Mode_Out_PP,
        .GPIO_Speed = GPIO_Speed_10MHz,
    };
    GPIO_Init(SD_HOST_LED_PORT, &sd_host_led_init);

    GPIO_InitTypeDef sd_ts_led_init = {
        .GPIO_Pin = SD_TS_LED_PIN,
        .GPIO_Mode = GPIO_Mode_Out_PP,
        .GPIO_Speed = GPIO_Speed_10MHz,
    };
    GPIO_Init(SD_TS_LED_PORT, &sd_ts_led_init);

    GPIO_InitTypeDef blink_led_init = {
        .GPIO_Pin = BLINK_PIN,
        .GPIO_Mode = GPIO_Mode_Out_PP,
        .GPIO_Speed = GPIO_Speed_10MHz,
    };
    GPIO_Init(BLINK_PORT, &blink_led_init);
    queued_task_add(led_blinking_task, BLINK_INTERVAL, 1);
}

void led_task(void) {
}
