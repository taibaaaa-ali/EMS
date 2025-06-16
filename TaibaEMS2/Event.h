#ifndef EVENT_H
#define EVENT_H

#include "myString.h"
#include "Stall.h"
#include "Vendor.h"
#include "Booking.h"
#include "Dynamic_array.h"
#include "Date.h"
#include <iostream>
#include <fstream>
using namespace std;

class Event
{
    myString name;
    int id;
    myString venue;
    Date date;
    myString productCategory;

    Dynamic_array<Stall> stalls;
    Dynamic_array<Vendor*> vendors;
    Dynamic_array<Booking*> bookings;

public:
    Event();
    Event(myString n, int eventId, myString v, Date d, myString category, int stallCount);
    ~Event();

    void show_event_details() const;
    void show_all_stalls() const;

    void add_stall(const Stall& stall);
    Stall* get_available_stall();
    int getNoOfStalls() const;

    myString getProductCategory() const;
    Date getDate() const;
    int getID() const;

    void addBooking(Booking* booking);
    void assignStallToBooking(int bookingID);
    Booking* getBookingByID(int bookingID) const;

    void listBookings() const;
    void listVendors() const;

    void writeToFile(ofstream& out) const;
    bool readFromFile(ifstream& in);
    void collectAllStalls(Stall* all[], int& index) const;

    Stall* getStallByID(int sid)
    {
        for (int i = 0; i < stalls.size(); i++)
        {
            if (stalls[i].getID() == sid)
                return &stalls[i];
        }
        return nullptr;
    }
};

Event::Event() : name(""), id(0), venue(""), date(), productCategory("") {}

Event::Event(myString n, int eventId, myString v, Date d, myString category, int stallCount)
    : name(n), id(eventId), venue(v), date(d), productCategory(category)
{
    for (int i = 0; i < stallCount; ++i)
    {
        int stallID = i + 1;
        myString size = myString("10x10");
        float price = 500.0f + 200.0f * i;
        stalls.push(Stall(stallID, size, i, 0, category, price));
    }
}

Event::~Event() {}

void Event::show_event_details() const
{
    cout << "Event: ";
    name.print();
    cout << "\nID: " << id << "\nVenue: ";
    venue.print();
    cout << "\nDate: " << date << "\nCategory: ";
    productCategory.print();
    cout << "\n";
}

void Event::show_all_stalls() const
{
    for (int i = 0; i < stalls.size(); i++)
    {
        stalls[i].stall_details();
        cout << endl;
    }
}

void Event::add_stall(const Stall& stall)
{
    stalls.push(stall);
}

Stall* Event::get_available_stall()
{
    for (int i = 0; i < stalls.size(); i++)
    {
        if (!stalls[i].getIsBooked())
        {
            return &stalls[i];
        }
    }
    return nullptr;
}

int Event::getNoOfStalls() const
{
    return stalls.size();
}

myString Event::getProductCategory() const
{
    return productCategory;
}

Date Event::getDate() const
{
    return date;
}

int Event::getID() const
{
    return id;
}

void Event::addBooking(Booking* booking)
{
    bookings.push(booking);
}

Booking* Event::getBookingByID(int bookingID) const
{
    for (int i = 0; i < bookings.size(); i++)
    {
        if (bookings[i]->getID() == bookingID)
        {
            return bookings[i];
        }
    }
    return nullptr;
}

void Event::assignStallToBooking(int bookingID)
{
    Booking* booking = getBookingByID(bookingID);
    if (booking != nullptr && booking->getStall() == nullptr)
    {
        cout << "Available Stalls:\n";
        for (int i = 0; i < stalls.size(); i++)
        {
            if (!stalls[i].getIsBooked())
            {
                cout << "ID: " << stalls[i].getID() << ", Size: ";
                stalls[i].getSize().print();
                cout << ", Price: " << stalls[i].getPrice() << endl;
            }
        }

        cout << "Enter Stall ID to assign: ";
        int sid;
        cin >> sid;

        for (int i = 0; i < stalls.size(); i++)
        {
            if (stalls[i].getID() == sid && !stalls[i].getIsBooked())
            {
                booking->assignStall(&stalls[i]);
                booking->confirmBookingAfterPayment();
                vendors.push(booking->getVendor());
                cout << "Stall assigned successfully.\n";
                return;
            }
        }

        cout << "Invalid or already booked Stall ID.\n";
    }
    else
    {
        cout << "Booking not found or already has stall.\n";
    }
}

void Event::listBookings() const
{
    cout << "-- Bookings in Event --" << endl;
    for (int i = 0; i < bookings.size(); i++)
    {
        bookings[i]->get_booking_details();
        cout << endl;
    }
}

void Event::listVendors() const
{
    cout << "-- Registered Vendors (Paid) --" << endl;
    for (int i = 0; i < vendors.size(); i++)
    {
        vendors[i]->print_details();
        cout << endl;
    }
}

void Event::writeToFile(ofstream& out) const
{
    out << id << ",";
    for (int i = 0; i < name.length(); i++) out << name.charAt(i); out << ",";
    for (int i = 0; i < venue.length(); i++) out << venue.charAt(i); out << ",";
    out << date.day << "," << date.month << "," << date.year << ",";
    for (int i = 0; i < productCategory.length(); i++) out << productCategory.charAt(i); out << ",";
    out << stalls.size() << "\n";
}

bool Event::readFromFile(ifstream& in)
{
    char line[300];
    if (!in.getline(line, 300)) return false;

    int i = 0, field = 0, bufIdx = 0;
    char buffer[100];
    int eid = 0, d = 0, m = 0, y = 0, stallCount = 0;
    char nameBuf[100] = {}, venueBuf[100] = {}, catBuf[100] = {};

    while (line[i] != '\0')
    {
        if (line[i] != ',' && line[i] != '\n')
        {
            buffer[bufIdx++] = line[i];
        }
        else
        {
            buffer[bufIdx] = '\0';
            if (field == 0) eid = atoi(buffer);
            else if (field == 1) for (int j = 0; j <= bufIdx; j++) nameBuf[j] = buffer[j];
            else if (field == 2) for (int j = 0; j <= bufIdx; j++) venueBuf[j] = buffer[j];
            else if (field == 3) d = atoi(buffer);
            else if (field == 4) m = atoi(buffer);
            else if (field == 5) y = atoi(buffer);
            else if (field == 6) for (int j = 0; j <= bufIdx; j++) catBuf[j] = buffer[j];
            else if (field == 7) stallCount = atoi(buffer);
            field++;
            bufIdx = 0;
        }
        i++;
    }

    id = eid;
    name = myString(nameBuf);
    venue = myString(venueBuf);
    productCategory = myString(catBuf);
    date = { d, m, y };

    for (int i = 0; i < stallCount; ++i)
    {
        int sid = i + 1;
        myString size = myString("10x10");
        float price = 500.0f + 200.0f * i;
        stalls.push(Stall(sid, size, i, 0, productCategory, price));
    }

    return true;
}

void Event::collectAllStalls(Stall* all[], int& index) const
{
    for (int i = 0; i < stalls.size(); i++)
    {
        all[index++] = const_cast<Stall*>(&stalls[i]);
    }
}

#endif
