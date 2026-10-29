
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
    htim2.Init.Period            = DEBOUNCE_MS - 1;    /* кожні 100 ms */
    htim2.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

   
    HAL_TIM_Base_Init(&htim2);
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_NVIC_SetPriority(TIM2_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}

void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim2);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim2)
{
    if (htim2->Instance == TIM2)
    {
        TIM2_counter++; //значення від 1 до 10 використовуємо

       switch (TIM2_counter)
       {
            case BLINK_R_TIME_MS:
                HAL_GPIO_TogglePin(GPIOC, LED_R_PIN);
            break;
            
            case BLINK_G_TIME_MS:
                HAL_GPIO_TogglePin(GPIOC, LED_G_PIN);
            break;
            
            case BLINK_W_TIME_MS:
                HAL_GPIO_TogglePin(GPIOC, LED_W_PIN);
            break;

        }
        
           if(TIM2_counter > 10) TIM2_counter = 0; 
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