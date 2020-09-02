//
// Created by fulva on 2020/9/2.
//

#ifndef F446ZE_SERVOSUB_H
#define F446ZE_SERVOSUB_H

#include "ros/node_handle.h"
#include "std_msgs/Float64.h"
#include "servo_motor_order_consumer.h"
#include "pin_definition.h"

ServoMotorOrderConsumer orderConsumer{ARM_0_PWM, ServoMotorTransform{1.0, 0}};

void servosubcb(const std_msgs::Float64 &msg) {
    orderConsumer(msg.data);
}

ros::Subscriber<std_msgs::Float64> servosub{"servosub", &servosubcb};


#endif //F446ZE_SERVOSUB_H
