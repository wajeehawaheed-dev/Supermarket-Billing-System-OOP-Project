#include "product.h"
#include <iostream>
#include <fstream>
using namespace std;

//---Product class implementations---

Product::Product(int id, string n, string cat, double p, int s) //Constructor
{
    productID = id;  name = n;  category = cat;
    price = p;  stock = s;  isActive = true;
}

//Utility
void Product::display() const 
{
    cout << "ID: " << productID;
    cout << " | Name: " << name;
    cout << " | Category: " << category;
    cout << " | Price (Rs." << price << ") ";
    cout << " | Stock: " << stock << endl;
}
bool Product::isLowStock(int threshold) const 
{                               //agar stock 5 se kam hua toh error message(value 5 hardcoded in shared.h)
    return stock < 5;
}

//Getters
int Product::getID() const { return productID; }
string Product::getName() const { return name; }
string Product::getCategory() const { return category; }
double Product::getPrice() const { return price; }
int Product::getStock() const { return stock; }
bool Product::getIsActive() const { return isActive; }

//Setters
void Product::setName(string n) 
{ 
    name = n; 
}
void Product::setCategory(string c)
{ 
    category = c;
}
void Product::setPrice(double p) 
{ 
    if (p > 0)
        price = p;
}
void Product::setStock(int s) 
{ 
    if (s >= 0) 
        stock = s; 
}
void Product::setIsActive(bool status) 
{ 
    isActive = status; 
}

//--- ProductManager implementations ---

ProductManager::ProductManager() //remove nextId becuse sql will handle it and it won't even reset everytime program runs
{ 
    nextID = 1;
}

