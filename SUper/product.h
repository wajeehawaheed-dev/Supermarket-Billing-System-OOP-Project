#ifndef PRODUCT_H
#define PRODUCT_H
//MEMBER 2
//Declarations of class Product & ProductManager
#include "database.h"

using namespace System;
using namespace System::Collections::Generic;

public ref class Product
{
private:
    int productID;
    String^ name;
    String^ category;
    double price;   //Encapsulation prevents invalid state, to prevent price from being negative
    int stock;
    bool isActive;

public:
    // Constructor
    Product(int id, String^ name, String^ category, double price, int stock);

    // Getters
    int getID();
    String^ getName();
    String^ getCategory();
    double getPrice();
    int getStock();
    bool getIsActive();

    // Setters
    void setName(String^ name);
    void setCategory(String^ category);
    void setPrice(double price);
    void setStock(int stock);
    void setIsActive(bool status);

    // Utility
    void display();
    bool isLowStock(int threshold);
    bool isLowStock();  // overload for default threshold
};

public ref class ProductManager //ABSTRACTION: The caller doesn't need to know HOW it's stored — just WHAT the operation does
{
private:
    List<Product^>^ products;  // managed list of product handles
    String^ toLower(String^ str);

public:
    ProductManager();
    // Destructor not needed - GC handles cleanup

    // ---- In-memory Logic Functions ----
    void addProduct(String^ name, String^ category, double price, int stock);
    void updateProduct(int id, String^ name, String^ category, double price);
    void deleteProduct(int id);
    void displayAll();
    void searchByName(String^ query);
    Product^ searchByID(int id);
    void decreaseStock(int id, int quantity);
    void increaseStock(int id, int quantity);
    void checkLowStock();

    // ---- DB Functions ----
    void loadFromDB();
    void addToDB(String^ name, String^ category, double price, int stock);
    void updateInDB(int id, String^ name, String^ category, double price);
    void deleteFromDB(int id);
    void decreaseStockInDB(int id, int qty);
    void increaseStockInDB(int id, int qty);
    void checkLowStockFromDB();
    void searchByNameFromDB(String^ query);
    void searchByIDFromDB(int id);
    void displayAllFromDB();
};

#endif