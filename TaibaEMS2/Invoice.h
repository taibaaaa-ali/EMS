#ifndef INVOICE_H
#define INVOICE_H

#include <iostream>
#include <fstream>
using namespace std;

#include "Booking.h"
#include "myString.h"

class Invoice
{
    int invoiceID;
    Booking* booking;
    myString issueDate;
    float amountDue;
    float amountPaid;
public:
    Invoice();
    Invoice(int id, Booking* b, myString date, float due, float paid = 0.0f);
    void pay(float amt);
    void get_invoice_details() const;
    float getAmountDue() const;
    float getAmountPaid() const;
    Booking* getBooking() const;
    bool isPaidInFull() const;

    void writeToFile(ofstream& out) const;
    bool readFromFile(ifstream& in, Booking* bookings[], int count);
};

Invoice::Invoice() : invoiceID(0), booking(nullptr), issueDate(""), amountDue(0.0f), amountPaid(0.0f) {}

Invoice::Invoice(int id, Booking* b, myString date, float due, float paid)
    : invoiceID(id), booking(b), issueDate(date), amountDue(due), amountPaid(paid)
{
}

void Invoice::pay(float amt)
{
    amountPaid += amt;
}


void Invoice::get_invoice_details() const
{
    cout << "Invoice ID: " << invoiceID << endl;
    cout << "Issue Date: ";
    issueDate.print();
    cout << endl;
    cout << "Amount Due: $" << amountDue << endl;
    cout << "Amount Paid: $" << amountPaid << endl;
    cout << "Balance: $" << (amountDue - amountPaid) << endl;
}

float Invoice::getAmountDue() const
{
    return amountDue;
}

float Invoice::getAmountPaid() const
{
    return amountPaid;
}

Booking* Invoice::getBooking() const
{
    return booking;
}

bool Invoice::isPaidInFull() const
{
    return amountPaid >= amountDue;
}

void Invoice::writeToFile(ofstream& out) const
{
    out << invoiceID << ",";
    out << (booking ? booking->getID() : -1) << ",";
    for (int i = 0; i < issueDate.length(); i++)
        out << issueDate.charAt(i);
    out << ",";
    out << amountDue << "," << amountPaid << "\n";
}

bool Invoice::readFromFile(ifstream& in, Booking* bookings[], int count)
{
    char line[200];
    if (!in.getline(line, 200))
        return false;

    int field = 0, i = 0, bufIdx = 0;
    char buffer[100], dateStr[100];
    int invID = 0, bookID = 0;
    float amtDue = 0, amtPaid = 0;

    while (line[i] != '\0')
    {
        if (line[i] != ',' && line[i] != '\n')
        {
            buffer[bufIdx++] = line[i];
        }
        else
        {
            buffer[bufIdx] = '\0';

            if (field == 0) invID = atoi(buffer);
            else if (field == 1) bookID = atoi(buffer);
            else if (field == 2) for (int j = 0; j <= bufIdx; j++) dateStr[j] = buffer[j];
            else if (field == 3) amtDue = atof(buffer);
            else if (field == 4) amtPaid = atof(buffer);

            field++;
            bufIdx = 0;
        }
        i++;
    }

    if (bufIdx > 0 && field == 4)
    {
        buffer[bufIdx] = '\0';
        amtPaid = atof(buffer);
    }

    invoiceID = invID;
    issueDate = myString(dateStr);
    amountDue = amtDue;
    amountPaid = amtPaid;

    booking = nullptr;
    for (int i = 0; i < count; i++)
    {
        if (bookings[i] && bookings[i]->getID() == bookID)
        {
            booking = bookings[i];
            break;
        }
    }

    return booking != nullptr;
}

#endif
