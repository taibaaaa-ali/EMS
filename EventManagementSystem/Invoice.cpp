#include "Invoice.h"

Invoice::Invoice(int id, Booking* b, Date date, float due, float paid): invoiceID(id), booking(b), issueDate(date), amountDue(due), amountPaid(paid){}

void Invoice::pay(float amt)
{
    amountPaid += amt;
}

void Invoice::get_invoice_details() const
{
    cout << "Invoice ID: " << invoiceID << endl;
    cout << "Issue Date: "; issueDate;
    cout << "Amount Due: $" << amountDue << endl;
    cout << "Amount Paid: $" << amountPaid << endl;
    cout << "Balance: $" << (amountDue - amountPaid) << endl;
}

float Invoice::getAmountDue() const
{
    return amountDue;
}