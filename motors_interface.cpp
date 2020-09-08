//
// Created by fulva on 2020/9/5.
//

#include "motors_interface.h"

DcMotorDriver left_motor_driver{
        MOBILE_LEFT_PWM,
        MOBILE_LEFT_D1,
        MOBILE_LEFT_D2
};

DcMotorDriver right_motor_driver{
        MOBILE_RIGHT_PWM,
        MOBILE_RIGHT_D1,
        MOBILE_RIGHT_D2
};


ServoMotorDriver arm0driver{ARM_0_PWM};
ServoMotorDriver arm1driver{ARM_1_PWM};
ServoMotorDriver arm2driver{ARM_2_PWM};
ServoMotorDriver arm3driver{ARM_3_PWM};
ServoMotorDriver arm4driver{ARM_4_PWM};
ServoMotorDriver arm5driver{ARM_5_PWM};

DcMotorDriver::DcMotorDriver(const PinName &gainPin, PinName d1_pin, PinName d2_pin) : _gain(gainPin), _d1(d1_pin),
                                                                                       _d2(d2_pin) {}

ServoMotorDriver::ServoMotorDriver(const PinName &pwm_pin) : pwmOut(pwm_pin) {}
