//
// Created by fulva on 2020/8/31.
//

#include "servo_motor_order_consumer.h"

void ServoMotorOrderConsumer::operator()(double endPos) {
    double endPosInDutyCycle{servoMotorTransform(endPos)};
    double currentPos{servoMotorTransform.reverse(currentPosInDutyCycle)};
    int step_num = ((endPos - currentPos) / MAX_SPEED * 1000) / SERVO_CONTROL_INTERVAL.count();
    LinearDivider linearDivider = {currentPosInDutyCycle, endPosInDutyCycle, step_num};
    thread.terminate();
    thread.start(std::bind(&ServoMotorOrderConsumer::controlroutine, this, linearDivider));
}

ServoMotorOrderConsumer::ServoMotorOrderConsumer(PinName pinName, ServoMotorTransform servoMotorTransform)
        : servoMotorTransform(servoMotorTransform), pwmOut(pinName) {
    pwmOut.period_ms(10);
}

