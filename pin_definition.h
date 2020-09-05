//
// Created by fulva on 2020/8/28.
//

#ifndef F446ZE_PIN_DEFINITION_H
#define F446ZE_PIN_DEFINITION_H

#include <PinNames.h>

//TIM1 and TIM4 are used to interface the encoder
constexpr PinName MOBILE_LEFT_ENCODER_A = PE_9; //TIM1/1
constexpr PinName MOBILE_LEFT_ENCODER_B = PE_11; //TIM1/2

constexpr PinName MOBILE_RIGHT_ENCODER_A = PD_12; //TIM4/1
constexpr PinName MOBILE_RIGHT_ENCODER_B = PD_13; //TIM4/2

constexpr PinName ARM_0_PWM = PC_7; //TIM3/2
constexpr PinName ARM_1_PWM = PB_3; //TIM2/2
constexpr PinName ARM_2_PWM = PA_6; //TIM3/1
constexpr PinName ARM_3_PWM = PA_0; //TIM2/1
constexpr PinName ARM_4_PWM = PB_10; //TIM2/3
constexpr PinName ARM_5_PWM = PB_11; //TIM2/4

constexpr PinName MOBILE_LEFT_PWM = PC_8; //TIM3/3
constexpr PinName MOBILE_RIGHT_PWM = PC_9; //TIM3/4

constexpr PinName MOBILE_LEFT_D1 = PG_2;
constexpr PinName MOBILE_LEFT_D2 = PG_3;

constexpr PinName MOBILE_RIGHT_D1 = PF_0;
constexpr PinName MOBILE_RIGHT_D2 = PF_1;


#endif //F446ZE_PIN_DEFINITION_H
