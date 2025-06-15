#ifndef STALL_H
#define STALL_H

#include "myString.h"
#include <iostream>
using namespace std;

class Stall
{
    int id;
    myString size;
    int x;
    int y;
    myString zone;
    float price;
    bool isBooked;

public:
    Stall();
    Stall(int sid, myString s, int _x, int _y, myString z, float p);

    void book();
    void release();
    bool getIsBooked() const;
    int getID() const;
    myString getSize() const;
    float getPrice() const;
    void stall_details() const;
};

Stall::Stall() : id(0), size("10x10"), x(0), y(0), zone("Default"), price(0.0f), isBooked(false) {}

Stall::Stall(int sid, myString s, int _x, int _y, myString z, float p)
    : id(sid), size(s), x(_x), y(_y), zone(z), price(p), isBooked(false) {
}

void Stall::book()
{
    isBooked = true;
}

void Stall::release()
{
    isBooked = false;
}

bool Stall::getIsBooked() const
{
    return isBooked;
}

int Stall::getID() const
{
    return id;
}

myString Stall::getSize() const
{
    return size;
}

float Stall::getPrice() const
{
    return price;
}

void Stall::stall_details() const
{
    cout << "Stall ID: " << id << ", Size: ";
    size.print();
    cout << ", Price: $" << price << ", Booked: " << (isBooked ? "Yes" : "No") << endl;
}

#endif
