#include "EMS.h"
#include <iostream>
using namespace std;

EMS::EMS()
{
    eventCount = 2;
    events = new Event * [eventCount];

    events[0] = new Event("Comic Expo", 301, "Hall A", Date{ 11, 6, 2025 }, "Anime", 2);

    events[1] = new Event("Gadget Fair", 302, "Hall B", Date{ 20, 7, 2025 }, "Electronics", 3);

    for (int i = 0; i < eventCount; ++i)
    {
        int stallsToAdd = events[i]->getNoOfStalls();
        for (int j = 0; j < stallsToAdd; j++)
        {
            Stall s(j + 1,"10x10", j, j,events[i]->getProductCategory(), 500 + 200 * j);
            events[i]->add_stall(s, j);
        }
    }
}

EMS::~EMS()
{
    for (int i = 0; i < eventCount; i++)
    {
        delete events[i];
    }
    delete[] events;
}

void EMS::run()
{
    cout << "Enter vendor name: ";
    string vName;
    getline(cin, vName);

    cout << "Enter vendor ID: ";
    int vId;
    cin >> vId;
    cin.ignore();

    cout << "Enter product category: ";
    string vCat;
    getline(cin, vCat);

    cout << "Enter contact info: ";
    string vContact;
    getline(cin, vContact);

    Vendor vendor(vName, vId, vCat, vContact);

    cout << "\nAvailable Events:\n";
    for (int i = 0; i < eventCount; i++)
    {
        cout << (i + 1) << ". ";
        events[i]->show_event_details();
        cout << endl;
    }

    cout << "Select event number: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice < 1 || choice > eventCount)
    {
        cout << "Invalid event selection.\n";
        return;
    }

    Event* evt = events[choice - 1];

    if (vendor.getProductCategory() != evt->getProductCategory())
    {
        cout << "Sorry we can’t book you for this event as your product category does't match theme of our event :( \n";
        return;
    }

    Package packages[2] = 
    {
        Package("Standard", 101, "10x10",  800),
        Package("Premium",  102, "15x15", 1200)
    };

    cout << "\nAvailable Packages:\n";
    for (int i = 0; i < 2; i++)
    {
        cout << (i + 1) << ". ";
        packages[i].get_package_details();
        cout << endl;
    }

    cout << "Select package number: ";
    cin >> choice;
    cin.ignore();

    if (choice < 1 || choice > 2)
    {
        cout << "Invalid package selection.\n";
        return;
    }

    Package& pkg = packages[choice - 1];

    cout << "\nStalls for this event:\n";
    evt->show_all_stalls();

    cout << "Select stall index (1-" << evt->getNoOfStalls() << "): ";
    int stallIdx;
    cin >> stallIdx;
    cin.ignore();

    if (stallIdx < 1 || stallIdx > evt->getNoOfStalls())
    {
        cout << "Invalid stall selection.\n";
        return;
    }

    Stall* stall = evt->get_stall(stallIdx - 1);

    Booking booking(501, &vendor, stall);
    Date evtDate = evt->getDate();
    Date dueDate = { evtDate.day - 7, evtDate.month, evtDate.year };

    Invoice invoice(601, &booking, dueDate, pkg.getPrice());

    cout << "\nInvoice Due Date: ";
    dueDate;

    cout << "\nPay in full or installments? (1=Full, 2=Installments): ";
    int payOpt;
    cin >> payOpt;
    cin.ignore();

    if (payOpt == 2)
    {
        cout << "Number of installments: ";
        int n;
        cin >> n;
        cin.ignore();

        if (n < 1) n = 1;
        float perInstallment = invoice.getAmountDue() / n;

        for (int i = 1; i <= n; i++)
        {
            cout << "Pay installment " << i << " (" << perInstallment << "): ";
            float amt;
            cin >> amt;
            cin.ignore();
            invoice.pay(amt);
        }
    }
    else
    {
        invoice.pay(invoice.getAmountDue());
    }

    booking.confirm();
    evt->addVendor(&vendor);

    cout << "\nBOOKING CONFIRMED\n";

    cout << "\nVENDOR DETAILS\n";
    vendor.get_details();

    cout << "\nEVENT DETAILS\n";
    evt->show_event_details();

    cout << "\nSTALL ASSIGNED\n";
    stall->stall_details();

    cout << "\nINVOICE DETAILS\n";
    invoice.get_invoice_details();

    cout << "\nREGISTERED VENDORS IN EVENT\n";
    evt->listVendors();
}
