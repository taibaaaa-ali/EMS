#pragma once
#include <iostream>
#include <string>
#include "Vendor.h"
#include "Stall.h"
using namespace std;

class Booking
{
protected:
    int bookingID;
    Vendor* vendor;
    Stall* stall;
    string status;

public:
    Booking(int id = 0, Vendor* v = nullptr, Stall* s = nullptr, string st = "Pending");
    void confirm();
    void cancel();
    void get_booking_details() const;
};