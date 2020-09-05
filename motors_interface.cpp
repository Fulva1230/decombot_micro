//
// Created by fulva on 2020/9/5.
//

#include "motors_interface.h"

DcMotorDriver left_motor_driver{
        ._gain{MOBILE_LEFT_PWM},
        ._d1{MOBILE_LEFT_D1},
        ._d2{MOBILE_LEFT_D2},
};

DcMotorDriver right_motor_driver{
        ._gain{MOBILE_RIGHT_PWM},
        ._d1{MOBILE_RIGHT_D1},
        ._d2{MOBILE_RIGHT_D2},
};

ServoMotorDriver arm0driver{.pwmOut{ARM_0_PWM}};
ServoMotorDriver arm1driver{.pwmOut{ARM_1_PWM}};
ServoMotorDriver arm2driver{.pwmOut{ARM_2_PWM}};
ServoMotorDriver arm3driver{.pwmOut{ARM_3_PWM}};
ServoMotorDriver arm4driver{.pwmOut{ARM_4_PWM}};
ServoMotorDriver arm5driver{.pwmOut{ARM_5_PWM}};
