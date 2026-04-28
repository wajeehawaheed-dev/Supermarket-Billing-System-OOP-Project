#ifndef CASHPAYMENT_H
#define CASHPAYMENT_H
#include "Payment.h"
class CashPayment : public Payment {
private:
    double cashgiven;
    double change;
public:
    CashPayment(int billNO, double Amount);

bool processpayment ( ) override;
void displaydetails() override;
void calculatechange();
};

#endif