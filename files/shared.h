#ifndef SHARED_H
#define SHARED_H

#include <string>
using namespace std;
struct Product
{
    int    productID;
    string name;
    string category;   // Electronics, Grocery, Dairy, Bakery, Pharmacy
    double price;
    int    stock;      // quantity on hand
    bool   isActive;   // true = available, false = discontinued/hidden
};
//User (Member 1)
struct User
{
    int    userID;
    string username;
    string password;
    string role;       // "Admin" or "Cashier"
    bool   isActive;
};

// Cart Item (Member 3)
struct CartItem
{
    int    productID;
    string name;
    double price;
    int    quantity;
    double itemTotal;  // price * quantity
};

// Bill Record (Member 3 writes, Members 4 & 5 read)
#include <vector>
struct BillRecord
{
    int                   billNo;
    string                date;      // "YYYY-MM-DD HH:MM:SS"
    int                   userID;    // cashier who made the sale
    double                subtotal;
    double                discount;
    double                tax;
    double                total;
    vector<CartItem>      items;
};

// Payment (Member 4)
struct Payment
{
    int    paymentID;
    int    billNo;
    string method;     // "Cash" or "Card"
    double amountPaid;
    double change;
    string status;     // "Approved", "Declined", "Cancelled"
    string date;
    string cardNumber; // empty if cash
    string cardHolder;
    string expiryDate;
};

//Sales Report (Member 5)
struct SalesReport
{
    int    reportID;
    string date;
    int    totalBills;
    double totalCash;
    double totalCard;
    double revenue;
};
#endif