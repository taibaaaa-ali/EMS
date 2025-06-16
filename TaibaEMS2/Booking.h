#ifndef BOOKING_H
#define BOOKING_H

#include "Vendor.h"
#include "Stall.h"
#include "myString.h"
#include <iostream>
#include <fstream>
using namespace std;

class Booking
{
    int bookingID;
    Vendor* vendor;
    Stall* stall;
    myString status;

public:
    Booking();
    Booking(int id, Vendor* v);
    Booking(int id, Vendor* v, Stall* s, myString st);

    void assignStall(Stall* s);
    void confirmBookingAfterPayment();
    void cancelBooking();

    void get_booking_details() const;
    myString getStatus() const;
    Vendor* getVendor() const;
    Stall* getStall() const;
    int getID() const;

    void writeToFile(ofstream& out) const;
    bool readFromFile(ifstream& in, Vendor* vendors[], int vCount, Stall* stalls[], int sCount);

    void setStatus(const myString& st)
    {
        status = st;
    }
};

Booking::Booking() : bookingID(0), vendor(nullptr), stall(nullptr), status("Pending") {}

Booking::Booking(int id, Vendor* v) : bookingID(id), vendor(v), stall(nullptr), status("Pending") {}

Booking::Booking(int id, Vendor* v, Stall* s, myString st)
    : bookingID(id), vendor(v), stall(s), status(st)
{
}

void Booking::assignStall(Stall* s)
{
    if (s && !s->getIsBooked())
    {
        stall = s;
    }
}

void Booking::confirmBookingAfterPayment()
{
    if (stall)
    {
        stall->book();
        status = myString("Confirmed");
    }
}

void Booking::cancelBooking()
{
    if (stall)
    {
        stall->release();
    }
    status = myString("Cancelled");
}

void Booking::get_booking_details() const
{
    cout << "Booking ID: " << bookingID << endl;
    cout << "Status: ";
    status.print();
    cout << endl;

    if (vendor) vendor->print_details();
    if (stall) stall->stall_details();
}

myString Booking::getStatus() const
{
    return status;
}

Vendor* Booking::getVendor() const
{
    return vendor;
}

Stall* Booking::getStall() const
{
    return stall;
}

int Booking::getID() const
{
    return bookingID;
}

void Booking::writeToFile(ofstream& out) const
{
    out << bookingID << ",";
    out << (vendor ? vendor->getID() : -1) << ",";
    out << (stall ? stall->getID() : -1) << ",";
    for (int i = 0; i < status.length(); i++)
        out << status.charAt(i);
    out << "\n";
}

bool Booking::readFromFile(ifstream& in, Vendor* vendors[], int vCount, Stall* stalls[], int sCount)
{
    char line[200];
    if (!in.getline(line, 200))
        return false;

    int field = 0, i = 0, bufIdx = 0;
    char buffer[100], statusStr[50];
    int id = 0, vendorID = 0, stallID = -1;

    while (line[i] != '\0')
    {
        if (line[i] != ',' && line[i] != '\n')
        {
            buffer[bufIdx++] = line[i];
        }
        else
        {
            buffer[bufIdx] = '\0';

            if (field == 0) id = atoi(buffer);
            else if (field == 1) vendorID = atoi(buffer);
            else if (field == 2) stallID = atoi(buffer);
            else if (field == 3) for (int j = 0; j <= bufIdx; j++) statusStr[j] = buffer[j];

            field++;
            bufIdx = 0;
        }
        i++;
    }

    if (bufIdx > 0 && field == 3)
    {
        buffer[bufIdx] = '\0';
        for (int j = 0; j <= bufIdx; j++) statusStr[j] = buffer[j];
    }

    bookingID = id;
    status = myString(statusStr);

    vendor = nullptr;
    for (int i = 0; i < vCount; i++)
    {
        if (vendors[i] && vendors[i]->getID() == vendorID)
        {
            vendor = vendors[i];
            break;
        }
    }

    stall = nullptr;
    for (int i = 0; i < sCount; i++)
    {
        if (stalls[i] && stalls[i]->getID() == stallID)
        {
            stall = stalls[i];
            break;
        }
    }

    return vendor != nullptr;
}

#endif
