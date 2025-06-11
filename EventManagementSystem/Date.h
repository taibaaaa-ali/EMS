#pragma once
#include <iostream>
using namespace std;

struct Date
{
    int day;
    int month;
    int year;

    void display()
    {
        cout << day << "/" << month << "/" << year << endl;
    }
};
