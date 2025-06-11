#pragma once
#include "Date.h"
#include "Booking.h"

class Invoice
{
protected:
    int invoiceID;
    Booking* booking;
    Date issueDate;
    float amountDue;
    float amountPaid;

public:
    Invoice(int id = 0, Booking* b = nullptr, Date date = { 0, 0, 0 }, float due = 0.0f, float paid = 0.0f);
    void pay(float amt);
    void get_invoice_details();
};
