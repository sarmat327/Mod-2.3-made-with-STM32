#pragma once

#include "stm32f4xx_hal.h"
#include <stdbool.h>

struct Config
{
    #define LED_R_PORT GPIOC
    #define LED_R_PIN GPIO_PIN_13
    #define BLINK_R_TIME_MS 200

    #define LED_G_PORT GPIOC
    #define LED_G_PIN GPIO_PIN_14
    #define BLINK_G_TIME_MS 500

    #define LED_W_PORT GPIOC
    #define LED_W_PIN GPIO_PIN_15
    #define BLINK_W_TIME_MS 1000

    #define DEBOUNCE_MS  50

   
};

    TIM_HandleTypeDef htim2;

    