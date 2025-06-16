#ifndef INSTALLMENTPAYMENT_H
#define INSTALLMENTPAYMENT_H

#include "Payment.h"

class InstallmentPayment : public Payment
{
    int installments;

public:
    InstallmentPayment()
        : Payment(), installments(1) {
    }
    InstallmentPayment(int id, float amt, myString m, int n)
        : Payment(id, amt, m),
        installments(n > 0 ? n : 1) {
    }

    void process_payment() const override
    {
        float per = amount / installments;
        cout << "Installment payment: " << installments
            << " installments of $" << per
            << " processed by method: ";
        method.print();
        cout << endl;
    }
};

#endif
