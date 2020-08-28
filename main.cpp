#include <ros/node_handle.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include "HardwareImpl.h"
#include <mbed.h>

std_msgs::Float64 local_time_msg;
ros::Publisher micontroller_time_pub("micontime", &local_time_msg);
std_msgs::String stringInfo;
ros::Publisher string_pub("chatter", &stringInfo);
ros::NodeHandle_<Hardware> nh;
std::string echo_string{"iojiojfsiodjf"};

void echo_sub_cb(const std_msgs::String &msg) {
    echo_string.append(msg.data);
    stringInfo.data = echo_string.c_str();
}

ros::Subscriber<std_msgs::String> echo_sub{"echo_sub", &echo_sub_cb};

void rosSpin() {
    while (true) {
        nh.spinOnce();
        ThisThread::sleep_for(20ms);
    }
}

int main() {
    Thread rosSpinThread;
    DigitalOut led(LED1);
    nh.initNode();
    rosSpinThread.start(&rosSpin);
    stringInfo.data = "jfwoiejf";
    nh.advertise(micontroller_time_pub);
    nh.advertise(string_pub);
    nh.subscribe(echo_sub);
    while (true) {
        led = !led;
        local_time_msg.data = nh.getHardware()->time();
        micontroller_time_pub.publish(&local_time_msg);
        string_pub.publish(&stringInfo);
        ThisThread::sleep_for(20ms);
    }
    return 0;
}




