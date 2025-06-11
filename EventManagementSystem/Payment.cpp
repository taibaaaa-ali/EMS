#include "Payment.h"

Payment::Payment(int id, Invoice* inv, Date date, float amt, string m): paymentID(id), invoice(inv), paymentDate(date), amount(amt), method(m) {}

void Payment::apply()
{
    if (invoice)
    {
        invoice->pay(amount);
    }
}

void Payment::get_payment_info() const
{
    cout << "Payment ID: " << paymentID << endl;
    cout << "Date: "; paymentDate;
    cout << "Method: " << method << endl;
    cout << "Amount: $" << amount << endl;
}
