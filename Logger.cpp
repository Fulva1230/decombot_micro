//
// Created by fulva on 2020/9/1.
//
#include "Logger.h"

Logger &Logger::operator<<(endl_t endl) {
    string.data = _stream.str().c_str();
    _pub.get().publish(&string);
    _stream.str("");
    return *this;
}

