#pragma once

#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdint.h>

struct Config
{
    #define LED_R_PORT GPIOC
    #define LED_R_PIN GPIO_PIN_13
    #define BLINK_R_TIME_MS 2    //період 100 мс. лічильник 2, тобто кожні 200 мс

    #define LED_G_PORT GPIOC
    #define LED_G_PIN GPIO_PIN_14
    #define BLINK_G_TIME_MS 5

    #define LED_W_PORT GPIOC
    #define LED_W_PIN GPIO_PIN_15
    #define BLINK_W_TIME_MS 10

    #define DEBOUNCE_MS  100

   
};

    static volatile uint32_t lastTimeChange = 0;
    static volatile uint8_t TIM2_counter = 0;
    TIM_HandleTypeDef htim2;

    