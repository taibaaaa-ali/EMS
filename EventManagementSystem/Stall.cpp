#include "Stall.h"

Stall::Stall() : stallID(0), size(""), XCoord(0), YCoord(0), zoneType(""), basePrice(0), isBooked(false) {}

Stall::Stall(int id, string sz, int x, int y, string zone, float price): stallID(id), size(sz), XCoord(x), YCoord(y), zoneType(zone), basePrice(price), isBooked(false) {}

void Stall::book()
{
    isBooked = true;
}

void Stall::release()
{
    isBooked = false;
}

void Stall::stall_details()
{
    cout << "Stall ID: " << stallID << endl;
    cout << "Size: " << size << endl;
    cout << "Zone: " << zoneType << endl;
    cout << "Price: $" << basePrice << endl;
    cout << "Status: ";
    if (isBooked)
    {
        cout << "Booked";
    }
    else
    {
        cout << "Available";
    }
    cout << endl;
}