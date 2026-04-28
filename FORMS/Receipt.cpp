#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <vector>
#include "Receipt.h"
#include "Cart.h"
#include "Payment.h"
using namespace std;

Receipt::Receipt(int billNo, string cashierName, string storeNo,
    Cart* cart, Payment* payment, string method)
{
    if (cart == NULL || payment == NULL) {
        cout << "Error: Invalid cart or payment!" << endl;
        return;
    }
    if (billNo <= 0) {
        cout << "Error: Invalid bill number!" << endl;
        return;
    }
    if (cart->getGrandTotal() <= 0) {
        cout << "Error: Invalid grand total!" << endl;
        return;
    }

    this->billNo = billNo;
    this->paymentMethod = method;
    this->cashierName = cashierName.empty() ? "Unknown" : cashierName;
    this->storeNo = storeNo.empty() ? "N/A" : storeNo;
    this->items = cart->getItems();
    subtotal = cart->getSubTotal();
    discount = cart->calculateDiscount();
    tax = cart->calculateTax();
    grandTotal = cart->getGrandTotal();
    amountPaid = payment->getAmountPaid();
    if (payment->getstatus() != "Approved")
    change = (amountPaid < grandTotal) ? 0 : amountPaid - grandTotal;

    time_t t = time(0);
    tm timeInfo;
    char buf[20];
    localtime_s(&timeInfo, &t);
    strftime(buf, sizeof(buf), "%Y-%m-%d", &timeInfo);
    date = (strlen(buf) == 0) ? "N/A" : string(buf);

    cardLastDigits = "";
    approvalCode = "";
}

void Receipt::setCardInfo(string lastDigits, string approval) {
    cardLastDigits = lastDigits.empty() ? "N/A" : lastDigits;
    approvalCode = approval.empty() ? "N/A" : approval;
}

void Receipt::generateReceipt(Payment* payment) {
    if (payment == NULL) {
        cout << "Error: Invalid payment!" << endl;
        return;
    }
    if (payment->getstatus() != "Approved") {
        cout << "Payment was not successful!\nReceipt cannot be generated.\n";
        return;
    }

    cout << "========================================\n";
    cout << "         SUPERMARKET RECEIPT            \n";
    cout << "========================================\n";
    cout << "Store No  : " << storeNo << endl;
    cout << "Bill No   : " << billNo << endl;
    cout << "Date      : " << date << endl;
    cout << "Cashier   : " << cashierName << endl;
    cout << "----------------------------------------\n";
    cout << left << setw(20) << "Item"
        << setw(8) << "Qty"
        << setw(10) << "Price"
        << setw(10) << "Total" << endl;
    cout << "----------------------------------------\n";

    if (items.empty()) {
        cout << "No items purchased!\n";
    }
    else {
        for (const auto& item : items) {
            string name = item.name;
            if (name.length() > 18)
                name = name.substr(0, 18);
            cout << left << setw(20) << name
                << setw(8) << item.quantity
                << setw(10) << fixed << setprecision(2) << item.price
                << setw(10) << item.itemTotal << endl;
        }
    }

    cout << "----------------------------------------\n";
    cout << right << setw(35) << "Subtotal: Rs " << subtotal << endl;
    cout << right << setw(35) << "Discount: Rs " << discount << endl;
    cout << right << setw(35) << "Tax: Rs " << tax << endl;
    cout << right << setw(35) << "Grand Total: Rs " << grandTotal << endl;
    cout << "----------------------------------------\n";
    cout << "Payment Method: " << paymentMethod << endl;
    cout << "Amount Paid: Rs " << amountPaid << endl;

    if (paymentMethod == "Cash") {
        cout << "Change: Rs " << change << endl;
    }
    else if (paymentMethod == "Card") {
        cout << "Card ending: **** " << cardLastDigits << endl;
        cout << "Approval Code: " << approvalCode << endl;
    }

    cout << "========================================\n";
    cout << "       Thank you for shopping!          \n";
    cout << "========================================\n";
}

void Receipt::printCancelledReceipt(Payment* payment) {
    if (payment == NULL) {
        cout << "Error: Invalid payment!" << endl;
        return;
    }
    generateReceipt(payment);
    cout << "*** TRANSACTION CANCELLED ***\n";
    cout << "Refund of Rs " << grandTotal << " will be processed.\n";
    cout << "========================================\n";
}