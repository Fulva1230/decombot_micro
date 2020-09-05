#include <ros/node_handle.h>
#include "HardwareImpl.h"
#include <mbed.h>
#include "std_msgs/String.h"
#include "Logger.h"
#include "servo_init.h"
#include "encoder.h"

ros::NodeHandle_<Hardware> nh;

std_msgs::String dummyString;
ros::Publisher logpub{"mculog", &dummyString};

NullLogger nullLogger;
Logger *logger{&nullLogger};

void rosSpin() {
    while (true) {
        nh.spinOnce();
        ThisThread::sleep_for(20ms);
    }
}

int main() {
    nh.initNode();
    // logging functionality
    nh.advertise(logpub);
    LoggerImpl logger_l{logpub};
    logger = &logger_l;

    initServos(nh);

    Thread rosSpinThread;
    rosSpinThread.start(&rosSpin);
    DigitalOut led(LED1);
    while (true) {
        led = !led;
        ThisThread::sleep_for(50ms);
    }
    return 0;
}




