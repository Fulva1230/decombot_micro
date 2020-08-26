//
// Created by fulva on 2020/8/25.
//

#ifndef F446ZE_HARDWAREIMPL_H
#define F446ZE_HARDWAREIMPL_H

#include <mbed.h>
#include <vector>
#include <chrono>
#include <USBSerial.h>

//TODO change the implementation to adapt some protocols
USBSerial bufferedSerial{};
constexpr int BUFFER_SIZE = 20;

class Hardware {
private:
    Timer timer;
    char buffer[BUFFER_SIZE];
    int bufferBoundary{0};
    int readindex{0};
public:
    explicit Hardware() {

    }

    // any initialization code necessary to use the serial port
    void init() {
        bufferedSerial.init();
        bufferedSerial.set_blocking(false);
        timer.start();
    }

    // read a byte from the serial port. -1 = failure
    int read() {
        if (readindex >= bufferBoundary) {
            int avail = bufferedSerial.available();
            if (avail > BUFFER_SIZE) bufferBoundary = bufferedSerial.read(&buffer, BUFFER_SIZE);
            else bufferBoundary = bufferedSerial.read(&buffer, avail);
            if (bufferBoundary > 0) {
                readindex = 0;
            } else {
                return -1;
            }
        }
        uint8_t returnByte = buffer[readindex];
        ++readindex;
        return returnByte;
    }

    // write data to the connection to ROS
    void write(uint8_t *data, int length) {
        bufferedSerial.write(data, length);
    }

    // returns milliseconds since start of program
    unsigned long time() {
        return timer.elapsed_time().count() / 1000;
    }
};

#endif //F446ZE_HARDWAREIMPL_H
