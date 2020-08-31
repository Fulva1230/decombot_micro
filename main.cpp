#include <ros/node_handle.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include "pin_definition.h"
#include "HardwareImpl.h"
#include <mbed.h>
#include "LinearDivider.h"

ros::NodeHandle_<Hardware> nh;

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
    while (true) {
        led = !led;

    }
    return 0;
}




