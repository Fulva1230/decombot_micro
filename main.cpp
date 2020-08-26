#include <ros/node_handle.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include "HardwareImpl.h"
#include <mbed.h>

std_msgs::Float64 local_time_msg;
ros::Publisher micontroller_time_pub("micontime", &local_time_msg);
ros::NodeHandle_<Hardware> nh;

void rosSpin() {
    while (true) {
        nh.spinOnce();
        ThisThread::sleep_for(100ms);
    }
}

int main() {
    Thread rosSpinThread;
    DigitalOut led(LED1);
    nh.initNode();
    rosSpinThread.start(&rosSpin);
    nh.advertise(micontroller_time_pub);
    while (true) {
        led = !led;
        local_time_msg.data = nh.getHardware()->time();
        micontroller_time_pub.publish(&local_time_msg);
        ThisThread::sleep_for(20ms);
    }
    return 0;
}




