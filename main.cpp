#include <ros/node_handle.h>
#include "pin_definition.h"
#include "HardwareImpl.h"
#include <mbed.h>
#include "ros/publisher.h"
#include "std_msgs/String.h"
#include "Logger.h"

ros::NodeHandle_<Hardware> nh;

std_msgs::String dummyString;
ros::Publisher logpub{"mculog", &dummyString};

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
    nh.advertise(logpub);
    Logger logger_l{logpub};
    logger = &logger_l;
    rosSpinThread.start(&rosSpin);
    while (true) {
        *logger << "testmsg";
        led = !led;
        ThisThread::sleep_for(50ms);
    }
    return 0;
}




