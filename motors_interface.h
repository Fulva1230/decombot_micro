//
// Created by fulva on 2020/9/5.
//

#ifndef F446ZE_MOTORS_INTERFACE_H
#define F446ZE_MOTORS_INTERFACE_H

#include "mbed.h"
#include "pin_definition.h"

struct DcMotorDriver {
    PwmOut _gain;
    DigitalOut _d1;
    DigitalOut _d2;
};

class DcMotor {
public:
    explicit DcMotor(DcMotorDriver &dcMotorDriver) : dcMotorDriver(dcMotorDriver) {
    }

    // the velocity should be between -1 to 1
    void operator()(double velocity) {
        if (velocity > 0) {
            dcMotorDriver._d1 = 1;
            dcMotorDriver._d2 = 0;
            dcMotorDriver._gain = velocity;
        } else {
            dcMotorDriver._d2 = 1;
            dcMotorDriver._d1 = 0;
            dcMotorDriver._gain = -velocity;
        }
    }

private:
    DcMotorDriver &dcMotorDriver;
};

struct ServoMotorDriver {
    PwmOut pwmOut;
};

class ServoMotor {
public:
    explicit ServoMotor(ServoMotorDriver &servoMotorDriver) : servoMotorDriver(servoMotorDriver) {
        servoMotorDriver.pwmOut.period_ms(10);
    }

    void operator()(float dutyCycle) {
        servoMotorDriver.pwmOut = dutyCycle;
    }

private:
    ServoMotorDriver &servoMotorDriver;
};

extern DcMotorDriver left_motor_driver;

extern DcMotorDriver right_motor_driver;

extern ServoMotorDriver arm0driver;
extern ServoMotorDriver arm1driver;
extern ServoMotorDriver arm2driver;
extern ServoMotorDriver arm3driver;
extern ServoMotorDriver arm4driver;
extern ServoMotorDriver arm5driver;


#endif //F446ZE_MOTORS_INTERFACE_H
