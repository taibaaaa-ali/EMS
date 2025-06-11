#include "Event.h"

Event::Event(string n, int eventId, string v, Date d, string category, int stallCount)
    : name(n), id(eventId), venue(v), date(d), productCategory(category), noOfStalls(stallCount)
{
    stalls = new Stall[noOfStalls];
}

void Event::add_stall(Stall stall, int index)
{
    if (index >= 0 && index < noOfStalls)
    {
        stalls[index] = stall;
    }
}

Stall* Event::get_stall(int index)
{
    if (index >= 0 && index < noOfStalls)
    {
        return &stalls[index];
    }
    return nullptr;
}

void Event::show_event_details()
{
    cout << "Event: " << name << endl;
    cout << "Event ID: " << id << endl;
    cout << "Venue: " << venue << endl;
    cout << "Date: ";
    date.display();
    cout << "Category: " << productCategory << endl;
}

void Event::show_all_stalls()
{
    for (int i = 0; i < noOfStalls; i++)
    {
        stalls[i].stall_details();
    }
}

Event::~Event()
{
    delete[] stalls;
}
