//
// Created by fulva on 2020/9/1.
//

#ifndef F446ZE_LOGGER_H
#define F446ZE_LOGGER_H

#include <functional>
#include "std_msgs/String.h"
#include "ros/node_handle.h"

constexpr size_t LOG_BUFFER_SIZE = 64;

typedef std::ostream &(*endl_t)(std::ostream &);

class Logger {
public:
    explicit Logger(ros::Publisher &pub) : _pub(pub) {
    }

    Logger &operator<<(double arg);

    Logger &operator<<(int arg);

    Logger &operator<<(char *cstr);

    Logger &operator<<(endl_t endl);


private:
    std::reference_wrapper<ros::Publisher> _pub;
    std_msgs::String _string;
    std::string _stringBuf;
    char _temp_before_publish_store[LOG_BUFFER_SIZE];
};


extern Logger *logger;
#endif //F446ZE_LOGGER_H
