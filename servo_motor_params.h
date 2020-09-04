//
// Created by fulva on 2020/9/4.
//

#ifndef F446ZE_SERVO_MOTOR_PARAMS_H
#define F446ZE_SERVO_MOTOR_PARAMS_H

constexpr double ARM_SCALE[] = {0.008, 0.001176, 0.001176, 0.001176, 0.001176, 0.001176};
constexpr double ARM_OFFSET[] = {0.05, 0.1, 0.05, 0.05, 0.05, 0.05};
constexpr double ARM_DEFAULT_PWM[] = {0.122, 0.1, 0.14, 0.15, 0.167647, 0.25};

constexpr double ARM_0_SCALE = ARM_SCALE[0];
constexpr double ARM_0_OFFSET = ARM_OFFSET[0];
constexpr double ARM_0_DEFAULT_PWM = ARM_DEFAULT_PWM[0];
constexpr double ARM_1_SCALE = ARM_SCALE[1];
constexpr double ARM_1_OFFSET = ARM_OFFSET[1];
constexpr double ARM_1_DEFAULT_PWM = ARM_DEFAULT_PWM[1];
constexpr double ARM_2_SCALE = ARM_SCALE[2];
constexpr double ARM_2_OFFSET = ARM_OFFSET[2];
constexpr double ARM_2_DEFAULT_PWM = ARM_DEFAULT_PWM[2];
constexpr double ARM_3_SCALE = ARM_SCALE[3];
constexpr double ARM_3_OFFSET = ARM_OFFSET[3];
constexpr double ARM_3_DEFAULT_PWM = ARM_DEFAULT_PWM[3];
constexpr double ARM_4_SCALE = ARM_SCALE[4];
constexpr double ARM_4_OFFSET = ARM_OFFSET[4];
constexpr double ARM_4_DEFAULT_PWM = ARM_DEFAULT_PWM[4];
constexpr double ARM_5_SCALE = ARM_SCALE[5];
constexpr double ARM_5_OFFSET = ARM_OFFSET[5];
constexpr double ARM_5_DEFAULT_PWM = ARM_DEFAULT_PWM[5];

// PWM = (ARM_O_SCALE[i] * input_angle) + ARM_O_OFFSET[i];

#endif //F446ZE_SERVO_MOTOR_PARAMS_H
