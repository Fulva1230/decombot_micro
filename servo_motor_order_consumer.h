//
// Created by fulva on 2020/8/31.
//

#ifndef F446ZE_SERVO_MOTOR_ORDER_CONSUMER_H
#define F446ZE_SERVO_MOTOR_ORDER_CONSUMER_H

#include <mbed.h>
#include "lineardivider.h"
#include "servomotortransform.h"
#include "motors_interface.h"

constexpr chrono::milliseconds SERVO_CONTROL_INTERVAL{50ms};
constexpr double MAX_SPEED(5.0); // angle per second

class ServoMotorOrderConsumer {
public:
    ServoMotorOrderConsumer(ServoMotorTransform servoMotorTransform, double currentPosInDutyCycle,
                            const ServoMotor &servoMotor);

    // the unit is angle in degree
    void operator()(double endPos);

    void pwmCorotine();

private:
    Thread *thread{new Thread{}};
    ServoMotor servoMotor;
    double currentPosInDutyCycle; //stored as the pwm duty cycle
    ServoMotorTransform servoMotorTransform;
    LinearDivider _cache_linearDivider{0, 0, 1};
};


#endif //F446ZE_SERVO_MOTOR_ORDER_CONSUMER_H
