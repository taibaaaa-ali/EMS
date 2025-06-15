#ifndef EMS_H
#define EMS_H

#include <iostream>
#include <fstream>
#include "Date.h"
#include "Vendor.h"
#include "Stall.h"
#include "Booking.h"
#include "Invoice.h"
#include "Event.h"
#include "myString.h"
#include "Dynamic_array.h"
#include "Manager.h"
#include "FullPayment.h"
#include "InstallmentPayment.h"
#include "PendingStallSelection.h"
#include "stall_map_gui.h"

using namespace std;

class EMS
{
    Dynamic_array<Event> events;
    Dynamic_array<Vendor*> registeredVendors;
    Dynamic_array<Vendor> pendingRequests;
    Dynamic_array<Booking*> allBookings;
    Dynamic_array<Invoice*> allInvoices;
    Manager admin;

    Dynamic_array<PendingStallSelection> pendingStallSelections;

public:
    EMS();
    void run();

private:
    void vendorRegister();
    void vendorLogin();
    void vendorDashboard(Vendor* v);
    void vendorRegisterEventStall(Vendor* v);
    void vendorPayInvoices(Vendor* v);
    void vendorViewBookings(Vendor* v);
    void vendorRemoveBooking(Vendor* v);

    void vendorSelectStall(Vendor* v, Event* e);

    void managerLogin();
    void managerSession();
    Vendor* findVendorByID(int id);

    void approveVendor();
    void approveEventStallSelections();

    void managerRemoveEvent();
    void managerRemoveVendor();
    void managerRemoveBooking();

    void saveVendorsToFile();
    void loadVendorsFromFile();
    void savePendingVendorsToFile();
    void loadPendingVendorsFromFile();

    void savePendingStallSelectionsToFile();
    void loadPendingStallSelectionsFromFile();

    void loadEventsFromFile(const char* filename);
    void saveEventsToFile();
    void addNewEvent();

    void saveBookingsToFile();
    void loadBookingsFromFile();
    void saveInvoicesToFile();
    void loadInvoicesFromFile();

    void clearConsole();

    bool vendorHasBookingOrPendingForEvent(Vendor* v, int eventID)
    {
        // Pending stall selection for this event
        for (int i = 0; i < pendingStallSelections.size(); i++)
        {
            if (pendingStallSelections[i].vendorID == v->getID() &&
                pendingStallSelections[i].eventID == eventID)
            {
                return true;
            }
        }
        // Bookings for this event
        for (int i = 0; i < allBookings.size(); i++)
        {
            if (allBookings[i]->getVendor()->getID() == v->getID())
            {
                Stall* s = allBookings[i]->getStall();
                if (s != nullptr)
                {
                    // Does this stall belong to this event?
                    for (int j = 0; j < events.size(); j++)
                    {
                        if (events[j].getID() == eventID)
                        {
                            for (int k = 0; k < events[j].getNoOfStalls(); k++)
                            {
                                if (events[j].getStallByID(s->getID()) == s)
                                {
                                    if (!allBookings[i]->getStatus().equal(myString("Cancelled")))
                                        return true;
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    bool isStallBookedForEvent(int eventID, int stallID)
    {
        // Check bookings for THIS EVENT AND STALL
        for (int i = 0; i < allBookings.size(); i++)
        {
            Stall* s = allBookings[i]->getStall();
            if (s != nullptr && s->getID() == stallID)
            {
                // Only for the same event
                for (int j = 0; j < events.size(); j++)
                {
                    if (events[j].getID() == eventID)
                    {
                        if (events[j].getStallByID(stallID) == s)
                        {
                            if (allBookings[i]->getStatus().equal(myString("Paid")) ||
                                allBookings[i]->getStatus().equal(myString("Confirmed")))
                                return true;
                        }
                    }
                }
            }
        }
        // Check pending stall selection for this event/stall
        for (int i = 0; i < pendingStallSelections.size(); i++)
        {
            if (pendingStallSelections[i].eventID == eventID &&
                pendingStallSelections[i].stallID == stallID)
            {
                return true;
            }
        }
        return false;
    }

};

EMS::EMS()
{
    admin = Manager(myString("Admin"), 999, myString("admin@ems.com"), myString("1234567890"), myString("admin123"));
    loadEventsFromFile("events.txt");
    loadVendorsFromFile();
    loadPendingVendorsFromFile();
    loadBookingsFromFile();
    loadInvoicesFromFile();
    loadPendingStallSelectionsFromFile();
}

void EMS::clearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void EMS::run()
{
    while (true)
    {
        cout << "--- Welcome to EMS ---\n";
        cout << "1. Vendor Login\n";
        cout << "2. Vendor Register\n";
        cout << "3. Manager Login\n";
        cout << "0. Exit\n";
        cout << "Choose: ";

        int opt;
        cin >> opt;

        if (opt == 1)
        {
            vendorLogin();
        }
        else if (opt == 2)
        {
            vendorRegister();
        }
        else if (opt == 3)
        {
            managerLogin();
        }
        else if (opt == 0)
        {
            saveVendorsToFile();
            savePendingVendorsToFile();
            saveBookingsToFile();
            saveInvoicesToFile();
            savePendingStallSelectionsToFile();
            break;
        }
        else
        {
            cout << "Invalid option.\n";
        }
    }
}

void EMS::vendorRegister()
{
    char name_c[100], cat_c[100], contact_c[100], pass_c[100];
    int id;

    cin.ignore();
    cout << "\n-- Vendor Registration --\n";
    cout << "Name: "; cin.getline(name_c, 100);
    cout << "Vendor ID: "; cin >> id;
    cin.ignore();

    for (int i = 0; i < registeredVendors.size(); i++)
    {
        if (registeredVendors[i]->getID() == id)
        {
            cout << "Vendor ID already exists.\n";
            return;
        }
    }

    for (int i = 0; i < pendingRequests.size(); i++)
    {
        if (pendingRequests[i].getID() == id)
        {
            cout << "Vendor ID already in pending list.\n";
            return;
        }
    }

    cout << "Product Category: "; cin.getline(cat_c, 100);
    cout << "Contact Info: "; cin.getline(contact_c, 100);
    cout << "Password: "; cin.getline(pass_c, 100);

    Vendor v(myString(name_c), id, myString(cat_c), myString(contact_c), myString(pass_c));
    pendingRequests.push(v);

    cout << "Registration submitted. Awaiting manager approval.\n";
    savePendingVendorsToFile();
}

void EMS::vendorLogin()
{
    int id;
    char pass_c[100];
    cout << "\n-- Vendor Login --\n";
    cout << "Enter ID: "; cin >> id; cin.ignore();
    cout << "Enter Password: "; cin.getline(pass_c, 100);

    Vendor* v = findVendorByID(id);
    if (v == nullptr || !v->login(id, myString(pass_c)))
    {
        cout << "Invalid login or not approved yet.\n";
        return;
    }

    cout << "\nLogin successful.\n";
    v->print_details();

    vendorDashboard(v);
}

void EMS::vendorDashboard(Vendor* v)
{
    while (true)
    {
        cout << "\n--- Vendor Dashboard ---\n";
        cout << "1. Register for new event + stall\n";
        cout << "2. Pay your invoices\n";
        cout << "3. View your stall bookings\n";
        cout << "4. Remove/cancel your stall booking\n";
        cout << "0. Logout\n";
        cout << "Choose: ";
        int opt; cin >> opt;

        if (opt == 1)
        {
            vendorRegisterEventStall(v);
        }
        else if (opt == 2)
        {
            vendorPayInvoices(v);
        }
        else if (opt == 3)
        {
            vendorViewBookings(v);
        }
        else if (opt == 4)
        {
            vendorRemoveBooking(v);
        }
        else if (opt == 0)
        {
            return;
        }
        else
        {
            cout << "Invalid option.\n";
        }
    }
}

void EMS::vendorRegisterEventStall(Vendor* v)
{
    int availableCount = 0;
    for (int i = 0; i < events.size(); i++)
    {
        if (events[i].getProductCategory().equal(v->getProductCategory()))
        {
            cout << availableCount + 1 << ". ";
            events[i].show_event_details();
            availableCount++;
        }
    }
    if (availableCount == 0)
    {
        cout << "No events available to register for.\n";
        return;
    }
    cout << "Select Event Number to Register: ";
    int eNum;
    cin >> eNum;
    int idx = -1;
    for (int i = 0, c = 1; i < events.size(); i++)
    {
        if (events[i].getProductCategory().equal(v->getProductCategory()))
        {
            if (c == eNum)
            {
                idx = i;
                break;
            }
            c++;
        }
    }
    if (idx == -1)
    {
        cout << "Invalid selection.\n";
        return;
    }
    vendorSelectStall(v, &events[idx]);
}

void EMS::vendorPayInvoices(Vendor* v)
{
    bool found = false;
    for (int i = 0; i < allBookings.size(); i++)
    {
        if (allBookings[i]->getVendor()->getID() == v->getID() &&
            allBookings[i]->getStatus().equal(myString("Pending")))
        {
            Booking* booking = allBookings[i];
            for (int j = 0; j < allInvoices.size(); j++)
            {
                if (allInvoices[j]->getBooking() == booking)
                {
                    found = true;
                    Invoice* inv = allInvoices[j];
                    inv->get_invoice_details();
                    float due = inv->getAmountDue();
                    float paid = inv->getAmountPaid();

                    cout << "\nChoose Payment Method:\n"
                        << "1. Full Payment\n"
                        << "2. Installments\n"
                        << "Choice: ";
                    int method; cin >> method;

                    if (method == 1)
                    {
                        while (paid < due)
                        {
                            float amt = due - paid;
                            cout << "Pay $" << amt << "? (y/n): ";
                            char c; cin >> c;
                            if (c == 'y' || c == 'Y')
                            {
                                inv->pay(amt);
                                paid = inv->getAmountPaid();
                                cout << "Total Paid: " << paid << "\n";
                            }
                            else break;
                        }
                    }
                    else if (method == 2)
                    {
                        cout << "How many installments? ";
                        int n; cin >> n;
                        if (n < 1) n = 1;
                        float per = due / n;
                        int part = 1;

                        while (paid < due && part <= n)
                        {
                            cout << "\nInstallment " << part << " of " << n
                                << ": pay $" << per << "? (1=Yes,2=Exit): ";
                            int opt; cin >> opt;
                            if (opt == 1)
                            {
                                inv->pay(per);
                                paid = inv->getAmountPaid();
                                cout << "Paid: " << paid << " / " << due << "\n";
                                part++;
                            }
                            else break;
                        }
                    }
                    else
                    {
                        cout << "Invalid choice.\n";
                        return;
                    }

                    if (inv->getAmountPaid() >= inv->getAmountDue())
                    {
                        booking->setStatus(myString("Paid"));
                        cout << "\nPayment complete. Booking marked as Paid!\n";
                    }
                }
            }
        }
    }
    if (!found)
        cout << "No unpaid invoices found.\n";
}


void EMS::vendorViewBookings(Vendor* v)
{
    cout << "\n--- Your Bookings ---\n";
    for (int i = 0; i < allBookings.size(); i++)
    {
        if (allBookings[i]->getVendor()->getID() == v->getID())
        {
            allBookings[i]->get_booking_details();
            cout << endl;
        }
    }
}

void EMS::vendorRemoveBooking(Vendor* v)
{
    cout << "\n--- Your Bookings ---\n";
    int count = 0;
    for (int i = 0; i < allBookings.size(); i++)
    {
        if (allBookings[i]->getVendor()->getID() == v->getID() &&
            allBookings[i]->getStatus().equal(myString("Pending")))
        {
            cout << count + 1 << ". Booking ID: " << allBookings[i]->getID() << endl;
            allBookings[i]->get_booking_details();
            count++;
        }
    }
    if (count == 0)
    {
        cout << "No pending (unconfirmed) bookings to remove.\n";
        return;
    }
    cout << "Select Booking Number to Remove: ";
    int num; cin >> num;
    int idx = -1;
    for (int i = 0, c = 1; i < allBookings.size(); i++)
    {
        if (allBookings[i]->getVendor()->getID() == v->getID() &&
            allBookings[i]->getStatus().equal(myString("Pending")))
        {
            if (c == num)
            {
                idx = i;
                break;
            }
            c++;
        }
    }
    if (idx == -1)
    {
        cout << "Invalid selection.\n";
        return;
    }
    int bookingID = allBookings[idx]->getID();
    // Remove related invoice
    for (int j = 0; j < allInvoices.size(); j++)
    {
        if (allInvoices[j]->getBooking()->getID() == bookingID)
        {
            allInvoices.delete_at(j);
            break;
        }
    }
    allBookings.delete_at(idx);
    cout << "Booking removed.\n";
}

void EMS::vendorSelectStall(Vendor* v, Event* e)
{
    clearConsole();

    bool booked[7] = {}; // stalls 1-6

    // For this event, mark stalls as booked if:
    // 1. They are assigned to any booking (paid/confirmed)
    // 2. They are in any pending stall selection for this event
    for (int sid = 1; sid <= 6; sid++)
    {
        if (isStallBookedForEvent(e->getID(), sid))
        {
            booked[sid] = true;
        }
    }

    int stallID = showStallMapGUI(booked);

    if (stallID < 1 || stallID > 6 || booked[stallID])
    {
        cout << "Invalid or already selected stall. Try again next login.\n";
        return;
    }
    // Before adding, you could (optionally) double-check again:
    if (isStallBookedForEvent(e->getID(), stallID))
    {
        cout << "Stall just got booked by someone else. Try again.\n";
        return;
    }
    pendingStallSelections.push(PendingStallSelection(v->getID(), e->getID(), stallID));
    savePendingStallSelectionsToFile();
    cout << "Stall selection submitted. Await manager approval.\n";
}


void EMS::managerLogin()
{
    int id;
    char pass_c[100];
    cout << "Enter Manager ID: "; cin >> id; cin.ignore();
    cout << "Enter Password: "; cin.getline(pass_c, 100);

    if (admin.login(id, myString(pass_c)))
    {
        cout << "Login successful.\n";
        managerSession();
    }
    else
    {
        cout << "Access denied.\n";
    }
}

void EMS::managerSession()
{
    while (true)
    {
        cout << "\n--- Manager Panel ---\n";
        cout << "1. Approve Vendor Registration\n";
        cout << "2. Approve Event+Stall Selections\n";
        cout << "3. Remove Event\n";
        cout << "4. Remove Vendor\n";
        cout << "5. Remove Booking\n";
        cout << "6. Add New Event\n";
        cout << "0. Logout\n";
        cout << "Choose: ";

        int opt;
        cin >> opt;

        if (opt == 1)
        {
            approveVendor();
        }
        else if (opt == 2)
        {
            approveEventStallSelections();
        }
        else if (opt == 3)
        {
            managerRemoveEvent();
        }
        else if (opt == 4)
        {
            managerRemoveVendor();
        }
        else if (opt == 5)
        {
            managerRemoveBooking();
        }
        else if (opt == 6)
        {
            addNewEvent();
        }
        else if (opt == 0)
        {
            break;
        }
        else
        {
            cout << "Invalid option.\n";
        }
    }
}

Vendor* EMS::findVendorByID(int id)
{
    for (int i = 0; i < registeredVendors.size(); i++)
    {
        if (registeredVendors[i]->getID() == id)
        {
            return registeredVendors[i];
        }
    }
    return nullptr;
}

void EMS::approveVendor()
{
    cout << "\n--- Pending Vendor Requests ---\n";
    for (int i = 0; i < pendingRequests.size(); i++)
    {
        cout << i + 1 << ". ";
        pendingRequests[i].print_details();
        cout << endl;
    }

    cout << "Select Vendor to Approve: ";
    int vIdx;
    cin >> vIdx;
    if (vIdx < 1 || vIdx > pendingRequests.size()) return;

    Vendor* vendor = new Vendor(pendingRequests[vIdx - 1]);
    registeredVendors.push(vendor);
    pendingRequests.delete_at(vIdx - 1);

    cout << "Vendor approved. Vendor can now login and register to an event.\n";
}

void EMS::approveEventStallSelections()
{
    cout << "\n--- Pending Event+Stall Selections ---\n";
    if (pendingStallSelections.size() == 0)
    {
        cout << "No pending event+stall requests.\n";
        return;
    }
    for (int i = 0; i < pendingStallSelections.size(); i++)
    {
        int vendorID = pendingStallSelections[i].vendorID;
        int eventID = pendingStallSelections[i].eventID;
        int stallID = pendingStallSelections[i].stallID;
        Vendor* v = findVendorByID(vendorID);
        Event* e = nullptr;
        for (int j = 0; j < events.size(); j++)
        {
            if (events[j].getID() == eventID)
            {
                e = &events[j];
                break;
            }
        }
        cout << i + 1 << ". Vendor ID: " << vendorID << " | ";
        if (v) v->print_details(); else cout << "Vendor not found\n";
        cout << "   Event ID: " << eventID << " | ";
        if (e) e->show_event_details(); else cout << "Event not found\n";
        cout << "   Requested Stall: " << stallID << "\n";
    }
    cout << "Select request to process: ";
    int idx;
    cin >> idx;
    if (idx < 1 || idx > pendingStallSelections.size()) return;

    PendingStallSelection req = pendingStallSelections[idx - 1];
    cout << "Approve this request? (1=Approve, 2=Reject): ";
    int choice; cin >> choice;

    if (choice == 2)
    {
        pendingStallSelections.delete_at(idx - 1);
        savePendingStallSelectionsToFile();
        cout << "Request rejected. Vendor may try again.\n";
        return;
    }

    Vendor* v = findVendorByID(req.vendorID);
    Event* e = nullptr;
    for (int j = 0; j < events.size(); j++)
    {
        if (events[j].getID() == req.eventID)
        {
            e = &events[j];
            break;
        }
    }
    if (!v || !e)
    {
        cout << "Vendor or event not found.\n";
        return;
    }
    int bookingID = 500 + allBookings.size();
    Booking* booking = new Booking(bookingID, v);

    Stall* stall = e->getStallByID(req.stallID);
    if (stall)
    {
        booking->assignStall(stall);
    }
    allBookings.push(booking);
    e->addBooking(booking);

    int invoiceID = 600 + allInvoices.size();
    Invoice* invoice = new Invoice(invoiceID, booking, myString("Due in 7 days"), 1000);
    allInvoices.push(invoice);

    pendingStallSelections.delete_at(idx - 1);
    savePendingStallSelectionsToFile();

    cout << "Event+Stall approved, booking and invoice created. Vendor may now pay.\n";
}

void EMS::managerRemoveEvent()
{
    cout << "\n--- Remove Event ---\n";
    for (int i = 0; i < events.size(); i++)
    {
        cout << i + 1 << ". ";
        events[i].show_event_details();
    }
    cout << "Select Event to Remove: ";
    int eIdx; cin >> eIdx;
    if (eIdx < 1 || eIdx > events.size()) return;
    int eventID = events[eIdx - 1].getID();

    // Remove related bookings/invoices
    for (int i = allBookings.size() - 1; i >= 0; i--)
    {
        if (allBookings[i]->getStall() && allBookings[i]->getStall()->getID() == eventID)
        {
            int bookingID = allBookings[i]->getID();
            for (int j = allInvoices.size() - 1; j >= 0; j--)
            {
                if (allInvoices[j]->getBooking()->getID() == bookingID)
                    allInvoices.delete_at(j);
            }
            allBookings.delete_at(i);
        }
    }
    // Remove related pending stall selections
    for (int i = pendingStallSelections.size() - 1; i >= 0; i--)
    {
        if (pendingStallSelections[i].eventID == eventID)
            pendingStallSelections.delete_at(i);
    }
    events.delete_at(eIdx - 1);

    saveEventsToFile(); // <--- ENSURES FILE IS UPDATED
    cout << "Event removed (and all related bookings/invoices/pending stalls).\n";
}


void EMS::managerRemoveVendor()
{
    cout << "\n--- Remove Vendor ---\n";
    for (int i = 0; i < registeredVendors.size(); i++)
    {
        cout << i + 1 << ". ";
        registeredVendors[i]->print_details();
    }
    cout << "Select Vendor to Remove: ";
    int vIdx; cin >> vIdx;
    if (vIdx < 1 || vIdx > registeredVendors.size()) return;
    int vendorID = registeredVendors[vIdx - 1]->getID();

    // Remove bookings/invoices
    for (int i = allBookings.size() - 1; i >= 0; i--)
    {
        if (allBookings[i]->getVendor()->getID() == vendorID)
        {
            int bookingID = allBookings[i]->getID();
            for (int j = allInvoices.size() - 1; j >= 0; j--)
            {
                if (allInvoices[j]->getBooking()->getID() == bookingID)
                    allInvoices.delete_at(j);
            }
            allBookings.delete_at(i);
        }
    }
    // Remove pending stall selections
    for (int i = pendingStallSelections.size() - 1; i >= 0; i--)
    {
        if (pendingStallSelections[i].vendorID == vendorID)
            pendingStallSelections.delete_at(i);
    }
    registeredVendors.delete_at(vIdx - 1);
    cout << "Vendor and all related data removed.\n";
}

void EMS::managerRemoveBooking()
{
    cout << "\n--- Remove Booking ---\n";
    for (int i = 0; i < allBookings.size(); i++)
    {
        cout << i + 1 << ". ";
        allBookings[i]->get_booking_details();
    }
    cout << "Select Booking to Remove: ";
    int bIdx; cin >> bIdx;
    if (bIdx < 1 || bIdx > allBookings.size()) return;
    int bookingID = allBookings[bIdx - 1]->getID();
    // Remove related invoice
    for (int j = allInvoices.size() - 1; j >= 0; j--)
    {
        if (allInvoices[j]->getBooking()->getID() == bookingID)
            allInvoices.delete_at(j);
    }
    allBookings.delete_at(bIdx - 1);
    cout << "Booking (and its invoice) removed.\n";
}

void EMS::saveVendorsToFile()
{
    ofstream out("vendors.txt");
    for (int i = 0; i < registeredVendors.size(); i++)
    {
        registeredVendors[i]->writeToFile(out);
    }
    out.close();
}

void EMS::loadVendorsFromFile()
{
    ifstream in("vendors.txt");
    while (in)
    {
        Vendor* v = new Vendor();
        if (v->readFromFile(in))
        {
            registeredVendors.push(v);
        }
        else
        {
            delete v;
        }
    }
    in.close();
}

void EMS::savePendingVendorsToFile()
{
    ofstream out("pending_vendors.txt");
    for (int i = 0; i < pendingRequests.size(); i++)
    {
        pendingRequests[i].writeToFile(out);
    }
    out.close();
}
void EMS::loadPendingVendorsFromFile()
{
    ifstream in("pending_vendors.txt");
    while (in)
    {
        Vendor v;
        if (v.readFromFile(in))
        {
            pendingRequests.push(v);
        }
    }
    in.close();
}

void EMS::savePendingStallSelectionsToFile()
{
    ofstream out("pending_stall_selections.txt");
    for (int i = 0; i < pendingStallSelections.size(); i++)
    {
        pendingStallSelections[i].writeToFile(out);
    }
    out.close();
}
void EMS::loadPendingStallSelectionsFromFile()
{
    ifstream in("pending_stall_selections.txt");
    while (in)
    {
        PendingStallSelection req;
        if (req.readFromFile(in))
        {
            pendingStallSelections.push(req);
        }
    }
    in.close();
}

void EMS::loadEventsFromFile(const char* filename)
{
    ifstream in(filename);
    if (!in.is_open())
    {
        cout << "Error opening events file.\n";
        return;
    }

    while (true)
    {
        Event e;
        if (!e.readFromFile(in))
        {
            break;
        }
        events.push(e);
    }

    in.close();
}

void EMS::saveEventsToFile()
{
    ofstream out("events.txt");
    for (int i = 0; i < events.size(); i++)
    {
        events[i].writeToFile(out);
    }
    out.close();
}

void EMS::addNewEvent()
{
    int id, d, m, y, stallCount;
    char name[100], venue[100], cat[100];

    cout << "\n--- Add New Event ---\n";
    cout << "Event ID: "; cin >> id; cin.ignore();
    cout << "Name: "; cin.getline(name, 100);
    cout << "Venue: "; cin.getline(venue, 100);
    cout << "Day: "; cin >> d;
    cout << "Month: "; cin >> m;
    cout << "Year: "; cin >> y; cin.ignore();
    cout << "Category: "; cin.getline(cat, 100);
    cout << "Stall Count: "; cin >> stallCount;

    Event e(myString(name), id, myString(venue), Date{ d, m, y }, myString(cat), stallCount);
    events.push(e);

    saveEventsToFile(); // <--- ENSURES FILE IS ALWAYS IN SYNC
    cout << "Event added successfully.\n";
}

void EMS::saveBookingsToFile()
{
    ofstream out("bookings.txt");
    for (int i = 0; i < allBookings.size(); i++)
    {
        allBookings[i]->writeToFile(out);
    }
    out.close();
}

void EMS::loadBookingsFromFile()
{
    ifstream in("bookings.txt");
    if (!in.is_open())
    {
        cout << "Error opening bookings.txt\n";
        return;
    }

    Vendor* vLookup[100];
    for (int i = 0; i < registeredVendors.size(); i++)
        vLookup[i] = registeredVendors[i];

    const int MAX_STALLS = 1000;
    Stall* sLookup[MAX_STALLS];
    int sCount = 0;

    for (int i = 0; i < events.size(); i++)
    {
        events[i].collectAllStalls(sLookup, sCount);
    }

    while (true)
    {
        Booking* b = new Booking();
        if (!b->readFromFile(in, vLookup, registeredVendors.size(), sLookup, sCount))
        {
            delete b;
            break;
        }

        allBookings.push(b);

        for (int i = 0; i < events.size(); i++)
        {
            if (events[i].getProductCategory().equal(b->getVendor()->getProductCategory()))
            {
                events[i].addBooking(b);
                break;
            }
        }
    }

    in.close();
}

void EMS::saveInvoicesToFile()
{
    ofstream out("invoices.txt");
    for (int i = 0; i < allInvoices.size(); i++)
    {
        allInvoices[i]->writeToFile(out);
    }
    out.close();
}

void EMS::loadInvoicesFromFile()
{
    ifstream in("invoices.txt");
    Booking* bLookup[500];
    for (int i = 0; i < allBookings.size(); i++)
        bLookup[i] = allBookings[i];

    while (in)
    {
        Invoice* inv = new Invoice();
        if (inv->readFromFile(in, bLookup, allBookings.size()))
        {
            allInvoices.push(inv);
        }
        else
        {
            delete inv;
        }
    }
    in.close();
}

#endif
