//
// Created by fulva on 2020/8/31.
//

#include "servo_motor_order_consumer.h"
#include "Logger.h"

void ServoMotorOrderConsumer::operator()(double endPos) {
    *logger << "new goal " << endPos << std::endl;
    double endPosInDutyCycle{servoMotorTransform(endPos)};
    openPdController.setNewGoal(endPosInDutyCycle);
}

ServoMotorOrderConsumer::ServoMotorOrderConsumer(ServoMotorTransform servoMotorTransform, double currentPosInDutyCycle,
                                                 const ServoMotor &servoMotor)
        : servoMotor(servoMotor),
          servoMotorTransform(servoMotorTransform),
          openPdController(currentPosInDutyCycle, currentPosInDutyCycle, 0, KP, KD) {
}

void ServoMotorOrderConsumer::pwmCorotine() {
    while (true) {
        int timeInterval = timer.elapsed_time().count();
        timer.reset();
        double output_pwm = openPdController.calc(timeInterval);
        servoMotor(output_pwm);
        *logger << "pwm output " << output_pwm << std::endl;
        ThisThread::sleep_for(SERVO_CONTROL_INTERVAL);
    }
}

void ServoMotorOrderConsumer::init() {
    timer.start();
    thread.start(Callback<void()>(this, &ServoMotorOrderConsumer::pwmCorotine));
}

