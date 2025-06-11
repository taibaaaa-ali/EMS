#pragma once
#include "Invoice.h"

class Payment
{
protected:
    int paymentID;
    Invoice* invoice;
    Date paymentDate;
    float amount;
    string method;

public:
    Payment(int id = 0, Invoice* inv = nullptr, Date date = { 0, 0, 0 }, float amt = 0.0f, string m = "");
    void apply();
    void get_payment_info();
};
