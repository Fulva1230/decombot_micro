//
// Created by fulva on 2020/9/1.
//
#include "Logger.h"

Logger &Logger::operator<<(endl_t endl) {
    uint8_t num_copy = _stream.str().copy(buffer, LOG_BUFFER_SIZE - 1);
    buffer[num_copy] = '\0';
    string.data = buffer;
    _pub.get().publish(&string);
    _stream.str("");
    return *this;
}

