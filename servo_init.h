//
// Created by fulva on 2020/9/2.
//

#ifndef F446ZE_SERVO_INIT_H
#define F446ZE_SERVO_INIT_H

#include "ros/node_handle.h"
#include "std_msgs/Float64.h"
#include "servo_motor_order_consumer.h"
#include "pin_definition.h"
#include "servo_motor_params.h"
#include "motors_interface.h"

#define SERVO_MOTOR_ORDER_CONSUMER(index) ServoMotorOrderConsumer servoMotorOrderConsumer_##index{ServoMotorTransform{ARM_##index##_SCALE, ARM_##index##_OFFSET}, ARM_##index##_DEFAULT_PWM, ServoMotor{arm##index##driver}};
#define SERVO_MOTOR_SUB_WRAPPER(index) ServoMotorSubWrapper servoMotorSubWrapper_##index{"servo_"#index"_angle", servoMotorOrderConsumer_##index};

class ServoMotorSubWrapper {
public:
    void cb(const std_msgs::Float64 &msg) {
        _servoMotorOrderConsumer(msg.data);
    }

    ServoMotorSubWrapper(const char *topic_name,
                         ServoMotorOrderConsumer &servoMotorOrderConsumer) :
            _sub(topic_name, &ServoMotorSubWrapper::cb, this),
            _servoMotorOrderConsumer(servoMotorOrderConsumer) {
    }

    void init(ros::NodeHandle_<Hardware> &nh) {
        nh.subscribe(_sub);
    }

private:
    ros::Subscriber<std_msgs::Float64, ServoMotorSubWrapper> _sub;
    ServoMotorOrderConsumer &_servoMotorOrderConsumer;
};

SERVO_MOTOR_ORDER_CONSUMER(0)
SERVO_MOTOR_ORDER_CONSUMER(1)
SERVO_MOTOR_ORDER_CONSUMER(2)
SERVO_MOTOR_ORDER_CONSUMER(3)
SERVO_MOTOR_ORDER_CONSUMER(4)
SERVO_MOTOR_ORDER_CONSUMER(5)

SERVO_MOTOR_SUB_WRAPPER(0)
SERVO_MOTOR_SUB_WRAPPER(1)
SERVO_MOTOR_SUB_WRAPPER(2)
SERVO_MOTOR_SUB_WRAPPER(3)
SERVO_MOTOR_SUB_WRAPPER(4)
SERVO_MOTOR_SUB_WRAPPER(5)

ServoMotorSubWrapper *servoMotorSubWrapper[] = {&servoMotorSubWrapper_0,
                                                &servoMotorSubWrapper_1,
                                                &servoMotorSubWrapper_2,
                                                &servoMotorSubWrapper_3,
                                                &servoMotorSubWrapper_4,
                                                &servoMotorSubWrapper_5};

template<class... T>
void initServos(T &&...args) {
    for (auto servosub : servoMotorSubWrapper) {
        servosub->init(std::forward<T>(args)...);
    }
}


#endif //F446ZE_SERVO_INIT_H
