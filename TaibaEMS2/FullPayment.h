#ifndef FULLPAYMENT_H
#define FULLPAYMENT_H

#include "Payment.h"

class FullPayment : public Payment
{
public:
    FullPayment() : Payment() {}
    FullPayment(int id, float amt, myString m)
        : Payment(id, amt, m) {
    }

    void process_payment() const override
    {
        cout << "Full payment of $" << amount
            << " processed by method: ";
        method.print();
        cout << endl;
    }
};

#endif
