//
// Created by fulva on 2020/8/31.
//

#include "servo_motor_order_consumer.h"
#include "Logger.h"

void ServoMotorOrderConsumer::operator()(double endPos) {
    thread->terminate();
    delete thread;
    thread = new Thread{};
    *logger << "motor order get call" << std::endl;
    double endPosInDutyCycle{servoMotorTransform(endPos)};
    double currentPos{servoMotorTransform.reverse(currentPosInDutyCycle)};
    uint16_t step_num = (std::abs(endPos - currentPos) / MAX_SPEED * 1000) / SERVO_CONTROL_INTERVAL.count();
    *logger << "the step_num is " << step_num << std::endl;
    _cache_linearDivider = {currentPosInDutyCycle, endPosInDutyCycle, step_num};
    *logger << "before new thread start" << std::endl;
    thread->start(Callback<void()>{this, &ServoMotorOrderConsumer::pwmCorotine});
}

ServoMotorOrderConsumer::ServoMotorOrderConsumer(PinName pinName, ServoMotorTransform servoMotorTransform,
                                                 double currentPosInDutyCycle)
        : pwmOut(pinName), currentPosInDutyCycle(currentPosInDutyCycle), servoMotorTransform(servoMotorTransform) {
    pwmOut.period_ms(10);
}

void ServoMotorOrderConsumer::pwmCorotine() {
    auto beginItr{_cache_linearDivider.begin()};
    auto endItr{_cache_linearDivider.end()};
    while (beginItr != endItr) {
        double output_pwm = *beginItr;
        pwmOut = output_pwm;
        currentPosInDutyCycle = output_pwm;
        *logger << "pwm output " << output_pwm << std::endl;
        ++beginItr;
        ThisThread::sleep_for(SERVO_CONTROL_INTERVAL);
    }
}

