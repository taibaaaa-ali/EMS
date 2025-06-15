#ifndef PAYMENT_H
#define PAYMENT_H

#include "myString.h"
#include <iostream>
using namespace std;

class Payment
{
protected:
    int paymentID;
    float amount;
    myString method;

public:
    Payment();
    Payment(int id, float amt, myString m);
    virtual ~Payment() {}

    virtual void process_payment() const = 0;

    float getAmount() const { return amount; }
    myString getMethod() const { return method; }
    int getID() const { return paymentID; }
};

Payment::Payment()
    : paymentID(0), amount(0.0f), method("") {
}

Payment::Payment(int id, float amt, myString m)
    : paymentID(id), amount(amt), method(m) {
}

#endif
