#ifndef LOGGING_H
#define LOGGING_H

#include <fstream>
#include <ctime>
#include "myString.h"
using namespace std;

inline void log_message(const myString& level, const myString& msg)
{
    ofstream log("ems_log.txt", ios_base::app);

    time_t now = time(0);
    char dt[30];
#if defined(_MSC_VER)
    ctime_s(dt, sizeof(dt), &now);
#else
    strncpy(dt, ctime(&now), sizeof(dt));
#endif

    cout << "[";
    level.print();
    cout << "] " << dt;
    msg.print();
    cout << endl;

    if (log.is_open())
    {
        log << "[";
        for (int i = 0; i < level.length(); i++)
            log << level.charAt(i);
        log << "] " << dt;
        for (int i = 0; i < msg.length(); i++)
            log << msg.charAt(i);
        log << endl;
    }
}

#endif
