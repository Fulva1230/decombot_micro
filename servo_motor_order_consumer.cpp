//
// Created by fulva on 2020/8/31.
//

#include "servo_motor_order_consumer.h"
#include "logger.h"

void ServoMotorOrderConsumer::operator()(double endPos) {
    *logger << "motor order get call" << std::endl;
    double endPosInDutyCycle{servoMotorTransform(endPos)};
    double currentPos{servoMotorTransform.reverse(currentPosInDutyCycle)};
    int step_num = ((endPos - currentPos) / MAX_SPEED * 1000) / SERVO_CONTROL_INTERVAL.count();
    _cache_linearDivider = {currentPosInDutyCycle, endPosInDutyCycle, step_num};
    thread.terminate();
    *logger << "before new thread start" << std::endl;
    thread.start([&]() {
        auto beginItr{_cache_linearDivider.begin()};
        auto endItr{_cache_linearDivider.end()};
        while (beginItr != endItr) {
            pwmOut = *beginItr;
            *logger << "pwm output" << *beginItr << std::endl;
            ++beginItr;
            ThisThread::sleep_for(SERVO_CONTROL_INTERVAL);
        }
    });
}

ServoMotorOrderConsumer::ServoMotorOrderConsumer(PinName pinName, ServoMotorTransform servoMotorTransform)
        : servoMotorTransform(servoMotorTransform), pwmOut(pinName) {
    pwmOut.period_ms(10);
}

