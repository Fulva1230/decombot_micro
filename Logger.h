//
// Created by fulva on 2020/9/1.
//

#ifndef F446ZE_LOGGER_H
#define F446ZE_LOGGER_H

#include <sstream>
#include <functional>
#include "std_msgs/String.h"
#include "ros/node_handle.h"

class Logger {
public:
    explicit Logger(ros::Publisher pub) : _pub(pub) {
    }

    template<class T>
    Logger &operator<<(T &&arg);

private:
    std::ostringstream _stream;
    std::reference_wrapper<ros::Publisher> _pub;
    std_msgs::String string;
};

template<class T>
Logger &Logger::operator<<(T &&arg) {
    _stream << std::forward<T>(arg);
    string.data = _stream.str().c_str();
    _pub.get().publish(&string);
    return *this;
}

#endif //F446ZE_LOGGER_H
