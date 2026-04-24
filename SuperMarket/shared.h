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