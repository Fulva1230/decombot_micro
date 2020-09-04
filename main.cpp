#include <ros/node_handle.h>
#include "HardwareImpl.h"
#include <mbed.h>
#include "std_msgs/String.h"
#include "Logger.h"
#include "servo_init.h"

ros::NodeHandle_<Hardware> nh;

std_msgs::String dummyString;
ros::Publisher logpub{"mculog", &dummyString};

Logger *logger{};

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
    initServos(nh);
    Logger logger_l{logpub};
    logger = &logger_l;
    rosSpinThread.start(&rosSpin);
    while (true) {
        led = !led;
        ThisThread::sleep_for(50ms);
    }
    return 0;
}




