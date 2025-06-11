#pragma once
#include <iostream>
#include <string>
#include "Stall.h"
#include "Date.h"
using namespace std;

class Event
{
protected:
    string name;
    int id;
    string venue;
    Date date;
    string productCategory;
    Stall* stalls;
    int noOfStalls;

public:
    Event(string n = "", int eventId = 0, string v = "", Date d = { 0, 0, 0 }, string category = "", int stallCount = 0);
    void add_stall(Stall stall, int index);
    Stall* get_stall(int index);
    void show_event_details();
    void show_all_stalls();
    ~Event();
};
