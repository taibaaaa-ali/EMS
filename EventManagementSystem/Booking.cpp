#include "Booking.h"

Booking::Booking(int id, Vendor* v, Stall* s, string st): bookingID(id), vendor(v), stall(s), status(st) {}

void Booking::confirm()
{
    if (stall)
    {
        stall->book();
        status = "Confirmed";
    }
       
}

void Booking::cancel()
{
    if (stall)
    {
        status = "Cancelled";
    }
        stall->release();
}

void Booking::get_booking_details() const
{
    cout << "Booking ID: " << bookingID << endl;
    cout << "Status: " << status << endl;
}