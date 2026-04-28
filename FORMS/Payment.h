#ifndef PAYMENT_H
#define PAYMENT_H

#include <iostream>
#include <string>
#include "database.h"

using namespace std;

class Payment {
protected:
    int paymentID;
    int billNo;
    double paid_amount;
    double total_bill;
    string status;
    string date;
    double refundAmount;
    bool isRefund;

public:
    // Constructors
    Payment();
    Payment(int billNo, double total_bill);

    // Pure Virtual Functions
    virtual void displaydetails() = 0;
    virtual bool processpayment() = 0;

    // Getters and Other Methods
    double getAmountPaid();
    string getstatus();
    bool checkstatus();
    void cancelPayment();
    void refundPayment();
    double getRefund();

    // Virtual Destructor
    virtual ~Payment();
};
#endif