
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdint.h>
#include "config.h"


static void GPIO_Init(void)
{

        
    GPIO_InitTypeDef gpio = {0};

   
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    //Ініціалізація СВІТЛОДІОДІВ
    gpio.Pin = LED_R_PIN;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(LED_R_PORT, &gpio);
    HAL_GPIO_WritePin(LED_R_PORT, LED_R_PIN, GPIO_PIN_RESET);

    gpio.Pin = LED_G_PIN;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(LED_G_PORT, &gpio);
    HAL_GPIO_WritePin(LED_G_PORT, LED_G_PIN, GPIO_PIN_RESET);

     gpio.Pin = LED_W_PIN;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(LED_W_PORT, &gpio);
    HAL_GPIO_WritePin(LED_W_PORT, LED_W_PIN, GPIO_PIN_RESET);




}

static void TIM2_Init(void)
{
    __HAL_RCC_TIM2_CLK_ENABLE();

    htim2.Instance               = TIM2;
    htim2.Init.Prescaler         = 16000 - 1;          /* 16 MHz / 16000 = 1 kHz (1 ms tick) */
    htim2.Init.CounterMode       = TIM_COUNTERMODE_UP;
    htim2.Init.Period            = DEBOUNCE_MS - 1;    /* 50 ms */
    htim2.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
        Error_Handler();
    }

    HAL_NVIC_SetPriority(TIM2_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);

void SysTick_Handler(void)
{
    HAL_IncTick();
}

void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(BTN_PIN);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint32_t now = HAL_GetTick();

    if (GPIO_Pin == BTN_PIN)
    {
        if (now - last_press > DEBOUNCE_MS)
        {
            last_press = now;
            press = true;
            LED_STATE_IS ++; 
        }
    }
}

int main(void)
{
    HAL_Init();
    GPIO_Init();
    TIM2_Init();

    while (1) {
        __WFI();
    }
}