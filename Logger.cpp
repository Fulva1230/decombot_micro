//
// Created by fulva on 2020/9/1.
//
#include "Logger.h"

constexpr uint8_t NUMERICAL_CONVERSION_BUF_SIZE = 20;

Logger &Logger::operator<<(endl_t endl) {
    uint8_t num_copy = _stringBuf.copy(_temp_before_publish_store, LOG_BUFFER_SIZE - 1);
    _temp_before_publish_store[num_copy] = '\0';
    _string.data = _temp_before_publish_store;
    _pub.get().publish(&_string);
    _stringBuf = "";
    return *this;
}

Logger &Logger::operator<<(const char *cstr) {
    _stringBuf.append(cstr);
    return *this;
}

Logger &Logger::operator<<(double arg) {
    char buf[NUMERICAL_CONVERSION_BUF_SIZE];
    snprintf(buf, NUMERICAL_CONVERSION_BUF_SIZE, "%f", arg);
    return *this << buf;
}

Logger &Logger::operator<<(int arg) {
    char buf[NUMERICAL_CONVERSION_BUF_SIZE];
    snprintf(buf, NUMERICAL_CONVERSION_BUF_SIZE, "%d", arg);
    return *this << buf;
}

