//
// Created by fulva on 2020/8/31.
//

#include "servo_motor_order_consumer.h"

void ServoMotorOrderConsumer::operator()(double endPos) {
    double endPosInDutyCycle{servoMotorTransform(endPos)};
    double currentPos{servoMotorTransform.reverse(currentPosInDutyCycle)};
    int step_num = ((endPos - currentPos) / MAX_SPEED * 1000) / SERVO_CONTROL_INTERVAL.count();
    LinearDivider linearDivider = {currentPosInDutyCycle, endPosInDutyCycle, step_num};
    auto beginItr{linearDivider.begin()};
    auto endItr{linearDivider.end()};
    thread.terminate();
    thread.start([&]() {
        while (beginItr != endItr) {
            pwmOut = *beginItr;
            ++beginItr;
        }
    });
}

ServoMotorOrderConsumer::ServoMotorOrderConsumer(PinName pinName, ServoMotorTransform servoMotorTransform)
        : servoMotorTransform(servoMotorTransform), pwmOut(pinName) {
    pwmOut.period_ms(10);
}

