//
// Created by fulva on 2020/9/1.
//

#include "Logger.h"

template<class T>
Logger &Logger::operator<<(T &&arg) {
    _stream << std::forward<T>(arg);
    string.data = _stream.str().c_str();
    _pub.get().publish(&string);
}