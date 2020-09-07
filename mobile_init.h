//
// Created by fulva on 2020/9/6.
//

#ifndef F446ZE_MOBILE_INIT_H
#define F446ZE_MOBILE_INIT_H

#include "ros/node_handle.h"
#include "std_msgs/Int16.h"
#include "motors_interface.h"

namespace {
    enum class MOBILE_DIR {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        STOP,
    };
}

DcMotor left_motor{left_motor_driver};
DcMotor right_motor{right_motor_driver};


void mobile_control_cb(const std_msgs::Int16 &msg) {
    switch (msg.data) {
        case static_cast<int>(MOBILE_DIR::FORWARD):
            left_motor(1);
            right_motor(1);
            break;
        case static_cast<int>(MOBILE_DIR::BACKWARD):
            left_motor(-1);
            right_motor(-1);
            break;
        case static_cast<int>(MOBILE_DIR::LEFT):
            left_motor(-1);
            right_motor(1);
            break;
        case static_cast<int>(MOBILE_DIR::RIGHT):
            left_motor(1);
            right_motor(-1);
            break;
        case static_cast<int>(MOBILE_DIR::STOP):
            left_motor(0);
            right_motor(0);
            break;
    }
}

ros::Subscriber<std_msgs::Int16> mobile_sub{"mobile_dir", &mobile_control_cb};

template<class node_t>
void initMobile(node_t &nh) {
    nh.subscribe(mobile_sub);
}


#endif //F446ZE_MOBILE_INIT_H
