//
// Created by fulva on 2020/9/5.
//

#ifndef F446ZE_MOTORS_INTERFACE_H
#define F446ZE_MOTORS_INTERFACE_H

#include "mbed.h"
#include "pin_definition.h"

struct DcMotorDrivers {
    PwmOut _gain;
    DigitalOut _d1;
    DigitalOut _d2;
};

class DcMotors {
public:
    explicit DcMotors(DcMotorDrivers &dcMotorsPins) :
            _gain(&dcMotorsPins._gain),
            _d1(&dcMotorsPins._d1),
            _d2(&dcMotorsPins._d2) {
    }

    // the velocity should be between -1 to 1
    void operator()(double velocity) {
        if (velocity > 0) {
            *_d1 = 1;
            *_d2 = 0;
            *_gain = velocity;
        } else {
            *_d2 = 1;
            *_d1 = 0;
            *_gain = -velocity;
        }
    }

private:
    PwmOut *_gain;
    DigitalOut *_d1;
    DigitalOut *_d2;
};

DcMotorDrivers left_motor_driver{
        ._gain{MOBILE_LEFT_PWM},
        ._d1{MOBILE_LEFT_D1},
        ._d2{MOBILE_LEFT_D2},
};

DcMotorDrivers right_motor_driver{
        ._gain{MOBILE_RIGHT_PWM},
        ._d1{MOBILE_RIGHT_D1},
        ._d2{MOBILE_RIGHT_D2},
};

#endif //F446ZE_MOTORS_INTERFACE_H
