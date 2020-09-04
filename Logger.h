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
    virtual Logger &operator<<(double arg) = 0;

    virtual Logger &operator<<(int arg) = 0;

    virtual Logger &operator<<(const char *cstr) = 0;

    virtual Logger &operator<<(endl_t endl) = 0;
};

class LoggerImpl : public Logger {
public:
    explicit LoggerImpl(ros::Publisher &pub) : _pub(pub) {
    }

    LoggerImpl &operator<<(double arg) override;

    LoggerImpl &operator<<(int arg) override;

    LoggerImpl &operator<<(const char *cstr) override;

    LoggerImpl &operator<<(endl_t endl) override;


private:
    std::reference_wrapper<ros::Publisher> _pub;
    std_msgs::String _string;
    std::string _stringBuf;
    char _temp_before_publish_store[LOG_BUFFER_SIZE]{};
};

class NullLogger : public Logger {
public:
    Logger &operator<<(double arg) override;

    Logger &operator<<(int arg) override;

    Logger &operator<<(const char *cstr) override;

    Logger &operator<<(endl_t endl) override;
};


extern Logger *logger;
#endif //F446ZE_LOGGER_H
