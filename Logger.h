//
// Created by fulva on 2020/9/1.
//

#ifndef F446ZE_LOGGER_H
#define F446ZE_LOGGER_H

#include <sstream>
#include <functional>
#include "std_msgs/String.h"
#include "ros/node_handle.h"

constexpr size_t BUFFER_SIZE = 64;
typedef std::ostream &(*endl_t)(std::ostream &);

class Logger {
public:
    explicit Logger(ros::Publisher &pub) : _pub(pub) {
    }

    template<class T>
    Logger &operator<<(T &&arg);

    Logger &operator<<(endl_t endl);


private:
    std::reference_wrapper<ros::Publisher> _pub;
    std::ostringstream _stream;
    std_msgs::String string;
    char buffer[BUFFER_SIZE];
};

template<class T>
Logger &Logger::operator<<(T &&arg) {
    _stream << std::forward<T>(arg);
    return *this;
}


extern Logger *logger;
#endif //F446ZE_LOGGER_H
