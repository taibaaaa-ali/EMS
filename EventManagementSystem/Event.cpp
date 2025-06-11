#include "Event.h"

Event::Event(string n, int eventId, string v, Date d, string category, int stallCount): name(n), id(eventId), venue(v), date(d), productCategory(category), noOfStalls(stallCount), noOfVendors(0)
{
    stalls = new Stall[noOfStalls];
    vendors = new Vendor * [noOfStalls];
}

Event::~Event()
{
    delete[] stalls;
    delete[] vendors;
}

void Event::show_event_details() const
{
    cout << "Event: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "Venue: " << venue << endl;
    cout << "Date: " << date << endl;
    cout << "Category: " << productCategory << endl;
}

void Event::show_all_stalls() const
{
    for (int i = 0; i < noOfStalls; i++)
    {
        stalls[i].stall_details();
    }
}

string Event::getProductCategory() const
{ 
    return productCategory;
}

Date Event::getDate() const 
{
    return date;
}

void Event::add_stall(const Stall& stall, int index)
{
    if (index >= 0 && index < noOfStalls)
    {
         stalls[index] = stall;
    }
}

Stall* Event::get_stall(int index) const
{
    if (index >= 0 && index < noOfStalls)
        return &stalls[index];
    return nullptr;
}

bool Event::hasAvailability() const
{ 
    return noOfVendors < noOfStalls;
}

void Event::addVendor(Vendor* v)
{
    if (noOfVendors < noOfStalls)
        vendors[noOfVendors++] = v;
}

void Event::listVendors() const
{
    cout << "-- Registered Vendors --" << endl;
    for (int i = 0; i < noOfVendors; i++)
    {
        vendors[i]->get_details();
    }

}
