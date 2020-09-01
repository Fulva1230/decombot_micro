//
// Created by fulva on 2020/9/1.
//

#ifndef F446ZE_LOGGER_H
#define F446ZE_LOGGER_H

#include <sstream>
#include <functional>
#include "std_msgs/String.h"
#include "ros/node_handle.h"

class Logger : public std::ostringstream {
public:
    explicit Logger(ros::Publisher pub) : _pub(pub) {

    }

    template<class T>
    Logger &operator<<(T &&arg);

private:
    std::stringstream _stream;
    std::reference_wrapper<ros::Publisher> _pub;
    std_msgs::String string;
};

Logger *logger;


#endif //F446ZE_LOGGER_H
