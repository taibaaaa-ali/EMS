#pragma once
#include <iostream>
#include <string>
#include "Date.h"
#include "Stall.h"
#include "Vendor.h"
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
    Vendor** vendors;
    int noOfVendors;

public:
    Event(string n = "", int eventId = 0, string v = "", Date d = { 0,0,0 }, string category = "", int stallCount = 0);
    ~Event();

    void show_event_details() const;
    void show_all_stalls() const;
    string getProductCategory() const;
    Date getDate() const;
    void add_stall(const Stall& stall, int index);
    Stall* get_stall(int index) const;
    bool hasAvailability() const;
    void addVendor(Vendor* v);
    void listVendors() const;

    int getNoOfStalls() const
    {
        return noOfStalls;
    }
};
