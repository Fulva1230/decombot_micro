#include "mobile_init.h"
#include <ros/node_handle.h>
#include "HardwareImpl.h"
#include <mbed.h>
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"
#include "Logger.h"
#include "servo_init.h"

ros::NodeHandle_<Hardware> nh;

std_msgs::String dummyString;
ros::Publisher logpub{"mculog", &dummyString};


NullLogger nullLogger;
Logger *logger{&nullLogger};

void rosSpin() {
    while (true) {
        nh.spinOnce();
    }
}

void watchdog_kick(const std_msgs::Int16 &dummy) {
    *logger << "watckdog_fun_call" << std::endl;
    static bool isEnable(false);
    if (!isEnable) {
        isEnable = true;
        Watchdog::get_instance().start(500);
        *logger << "start watchdog" << std::endl;
    } else {
        Watchdog::get_instance().kick();
        *logger << "kick watchdog" << std::endl;
    }
}

ros::Subscriber<std_msgs::Int16> watchdog_sub("mcu_watchdog", &watchdog_kick);

int main() {
    nh.initNode();
    // logging functionality
//    nh.advertise(logpub);
//    LoggerImpl logger_l{logpub};
//    logger = &logger_l;

    servo_driver_init();
    initServos(nh);
    initMobile(nh);

    Thread rosSpinThread;
    rosSpinThread.start(&rosSpin);
    nh.subscribe(watchdog_sub);

    DigitalOut led(LED1);
    while (true) {
        led = !led;
        ThisThread::sleep_for(50ms);
    }
    return 0;
}




