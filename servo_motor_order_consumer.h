//
// Created by fulva on 2020/8/31.
//

#ifndef F446ZE_SERVO_MOTOR_ORDER_CONSUMER_H
#define F446ZE_SERVO_MOTOR_ORDER_CONSUMER_H

#include <mbed.h>
#include "lineardivider.h"
#include "servomotortransform.h"

constexpr chrono::milliseconds SERVO_CONTROL_INTERVAL{50ms};
constexpr double MAX_SPEED(5.0); // angle per second

class ServoMotorOrderConsumer {
public:
    ServoMotorOrderConsumer(PwmOut pwmOut, ServoMotorTransform servoMotorTransform);

    void controlroutine(const LinearDivider &linearDivider) {
        auto beginItr{linearDivider.begin()};
        auto endItr{linearDivider.end()};
        while (beginItr != endItr) {
            pwmOut = *beginItr;
            ++beginItr;
        }
    }

    // the unit is angle in degree
    void operator()(double endPos);

private:
    Thread thread;
    PwmOut pwmOut;
    double currentPosInDutyCycle; //stored as the pwm duty cycle
    ServoMotorTransform servoMotorTransform;
};


#endif //F446ZE_SERVO_MOTOR_ORDER_CONSUMER_H