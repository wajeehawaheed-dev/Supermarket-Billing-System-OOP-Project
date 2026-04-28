#pragma once
#ifndef RECEIPT_H
#define RECEIPT_H
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <vector>
#include "Cart.h"
using namespace std;
class Payment;

class Receipt {
private:
    string storeNo;
    int billNo;
    string date;
    string cashierName;
    vector<CartItem> items;
    double amountPaid;
    double subtotal;
    double discount;
    double tax;
    double grandTotal;
    string paymentMethod;
    double change;
    string cardLastDigits;
    string approvalCode;
public:
    Receipt(int billNo, string cashierName, string storeNo, Cart* cart, Payment* payment, string method);
    void setCardInfo(string lastDigits, string approval);
    void generateReceipt(Payment* payment);
    void printCancelledReceipt(Payment* payment);
};
#endif