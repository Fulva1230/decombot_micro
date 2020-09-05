//
// Created by fulva on 2020/9/5.
//

#ifndef F446ZE_ENCODER_H
#define F446ZE_ENCODER_H

#include "stm32f446xx.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_gpio_ex.h"
#include "stm32f4xx_hal_gpio.h"

GPIO_InitTypeDef encoder_gpio{
        .Pin = GPIO_PIN_0,
        .Mode = GPIO_MODE_AF_PP,
        .Pull = GPIO_PULLUP,
        .Speed = GPIO_SPEED_FREQ_MEDIUM,
};

void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM1) {
        __HAL_RCC_TIM1_CLK_ENABLE();
        __HAL_RCC_GPIOE_CLK_ENABLE();
        GPIO_InitTypeDef encoder_gpioE9{encoder_gpio};
        encoder_gpioE9.Pin = GPIO_PIN_9;
        encoder_gpioE9.Alternate = GPIO_AF1_TIM1;
        HAL_GPIO_Init(GPIOE, &encoder_gpioE9);
        GPIO_InitTypeDef encoder_pigoE11{encoder_gpio};
        encoder_pigoE11.Pin = GPIO_PIN_11;
        encoder_pigoE11.Alternate = GPIO_AF1_TIM1;
        HAL_GPIO_Init(GPIOE, &encoder_pigoE11);
    }
    if (htim->Instance == TIM4) {
        __HAL_RCC_TIM4_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        GPIO_InitTypeDef encoder_gpioD12{encoder_gpio};
        encoder_gpioD12.Pin = GPIO_PIN_12;
        encoder_gpioD12.Alternate = GPIO_AF2_TIM4;
        HAL_GPIO_Init(GPIOD, &encoder_gpioD12);
        GPIO_InitTypeDef encoder_gpioD13{encoder_gpio};
        encoder_gpioD13.Pin = GPIO_PIN_13;
        encoder_gpioD13.Alternate = GPIO_AF2_TIM4;
        HAL_GPIO_Init(GPIOD, &encoder_gpioD13);
    }
}

TIM_Base_InitTypeDef baseInitTypeDef{
        .CounterMode = TIM_COUNTERMODE_UP,
        .ClockDivision = TIM_CLOCKDIVISION_DIV4,
        .AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE,
};

TIM_Encoder_InitTypeDef encoderInitTypeDef{
        .EncoderMode = TIM_ENCODERMODE_TI12,
        .IC1Polarity = TIM_ICPOLARITY_RISING,
        .IC1Selection = TIM_ICSELECTION_DIRECTTI,
        .IC1Prescaler = TIM_ICPSC_DIV4,
        .IC1Filter = 0x0,
        .IC2Polarity = TIM_ICPOLARITY_RISING,
        .IC2Selection = TIM_ICSELECTION_DIRECTTI,
        .IC2Prescaler = TIM_ICPSC_DIV4,
        .IC2Filter = 0x0,
};

void encoderInit() {
    TIM_HandleTypeDef tim1HandleTypeDef{
            .Instance = TIM1,
            .Init = baseInitTypeDef,
    };

    HAL_TIM_Encoder_Init(&tim1HandleTypeDef, &encoderInitTypeDef);

    TIM_HandleTypeDef tim4HandleTypeDef{
            .Instance = TIM4,
            .Init = baseInitTypeDef,
    };
    HAL_TIM_Encoder_Init(&tim4HandleTypeDef, &encoderInitTypeDef);

    HAL_TIM_Encoder_Start(&tim1HandleTypeDef, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&tim4HandleTypeDef, TIM_CHANNEL_ALL);
}

#endif //F446ZE_ENCODER_H
