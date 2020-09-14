//
// Created by fulva on 2020/8/31.
//

#ifndef F446ZE_SERVO_MOTOR_ORDER_CONSUMER_H
#define F446ZE_SERVO_MOTOR_ORDER_CONSUMER_H

#include <mbed.h>
#include "open_pd_controller.h"
#include "servomotortransform.h"
#include "motors_interface.h"

constexpr chrono::milliseconds SERVO_CONTROL_INTERVAL{50ms};
constexpr double KP = 4;
constexpr double KD = 3.8;

class ServoMotorOrderConsumer {
public:
    ServoMotorOrderConsumer(ServoMotorTransform servoMotorTransform, double currentPosInDutyCycle,
                            const ServoMotor &servoMotor);

    // the unit is angle in degree
    void operator()(double endPos);

    void pwmCorotine();

    void init();

private:
    Thread thread;
    Timer timer;
    ServoMotor servoMotor;
    ServoMotorTransform servoMotorTransform;
    OpenPDController openPdController;
};


#endif //F446ZE_SERVO_MOTOR_ORDER_CONSUMER_H
