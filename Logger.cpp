//
// Created by fulva on 2020/9/1.
//
#include "Logger.h"

constexpr uint8_t NUMERICAL_CONVERSION_BUF_SIZE = 20;

LoggerImpl &LoggerImpl::operator<<(endl_t endl) {
    uint8_t num_copy = _stringBuf.copy(_temp_before_publish_store, LOG_BUFFER_SIZE - 1);
    _temp_before_publish_store[num_copy] = '\0';
    _string.data = _temp_before_publish_store;
    _pub.get().publish(&_string);
    _stringBuf = "";
    return *this;
}

LoggerImpl &LoggerImpl::operator<<(const char *cstr) {
    _stringBuf.append(cstr);
    return *this;
}

LoggerImpl &LoggerImpl::operator<<(double arg) {
    char buf[NUMERICAL_CONVERSION_BUF_SIZE];
    snprintf(buf, NUMERICAL_CONVERSION_BUF_SIZE, "%f", arg);
    return *this << buf;
}

LoggerImpl &LoggerImpl::operator<<(int arg) {
    char buf[NUMERICAL_CONVERSION_BUF_SIZE];
    snprintf(buf, NUMERICAL_CONVERSION_BUF_SIZE, "%d", arg);
    return *this << buf;
}

Logger &NullLogger::operator<<(double arg) {
    return *this;
}

Logger &NullLogger::operator<<(int arg) {
    return *this;
}

Logger &NullLogger::operator<<(const char *cstr) {
    return *this;
}

Logger &NullLogger::operator<<(endl_t endl) {
    return *this;
}
