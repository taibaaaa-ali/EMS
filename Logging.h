#ifndef LOGGING_H
#define LOGGING_H

#include "myString.h"
#include <iostream>

// Simple console logger: prints [LEVEL] Message
inline void log_message(const myString& level, const myString& msg)
{
    std::cout << "[";
    level.print();
    std::cout << "] ";
    msg.print();
    std::cout << std::endl;
}

#endif
