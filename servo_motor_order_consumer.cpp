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
    step_num = step_num == 0 ? 1 : step_num;
    *logger << "the step_num is " << step_num << std::endl;
    _cache_linearDivider = {currentPosInDutyCycle, endPosInDutyCycle, step_num};
    *logger << "before new thread start" << std::endl;
    thread->start(Callback<void()>{this, &ServoMotorOrderConsumer::pwmCorotine});
}

ServoMotorOrderConsumer::ServoMotorOrderConsumer(ServoMotorTransform servoMotorTransform, double currentPosInDutyCycle,
                                                 const ServoMotor &servoMotor)
        : servoMotor(servoMotor), currentPosInDutyCycle(currentPosInDutyCycle),
          servoMotorTransform(servoMotorTransform) {
}

void ServoMotorOrderConsumer::pwmCorotine() {
    auto beginItr{_cache_linearDivider.begin()};
    auto endItr{_cache_linearDivider.end()};
    while (beginItr != endItr) {
        double output_pwm = *beginItr;
        servoMotor(output_pwm);
        currentPosInDutyCycle = output_pwm;
        *logger << "pwm output " << output_pwm << std::endl;
        ++beginItr;
        ThisThread::sleep_for(SERVO_CONTROL_INTERVAL);
    }
}

void ServoMotorOrderConsumer::init() {
    operator()(servoMotorTransform.reverse(currentPosInDutyCycle));
}

