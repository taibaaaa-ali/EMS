#pragma once
#include <iostream>
using namespace std;

struct Date
{
    int day;
    int month;
    int year;

    friend ostream& operator<<(ostream& os, const Date& d)
    {
        os << d.day << "/" << d.month << "/" << d.year;
        return os;
    }
    
};