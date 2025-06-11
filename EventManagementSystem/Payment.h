#pragma once
#include "Invoice.h"
#include <string>
using namespace std;

class Payment
{
protected:
    int paymentID;
    Invoice* invoice;
    Date paymentDate;
    float amount;
    string method;

public:
    Payment(int id = 0, Invoice* inv = nullptr, Date date = { 0,0,0 }, float amt = 0.0, string m = "");
    void apply();
    void get_payment_info() const;
};