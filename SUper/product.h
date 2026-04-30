#ifndef PRODUCT_H
#define PRODUCT_H
//MEMBER 2
//Declarations of class Product & ProductManager
#include <string>
using namespace std;

//Shared CLASS 01
class Product
{
private:
    int productID;
    string name;
    string category;    //like Electronics, Grocery, Dairy, Bakery, Pharmacy
    double price;
    int stock;          //quantity of a particular item
    bool isActive;      //true: Available for sale, false: Discontinued/Hidden/out of stock

public:
    //Constructor
    Product(int id, string name, string category, double price, int stock);

    //Getters
    int getID() const;
    string getName() const;
    string getCategory() const;
    double getPrice() const;
    int getStock() const;
    bool getIsActive() const;

    //Setters
    void setName(string name);
    void setCategory(string category);
    void setPrice(double price);
    void setStock(int stock);
    void setIsActive(bool status);

    //Utility
    void display() const;
    bool isLowStock(int threshold = 5) const;
};



class ProductManager
{
private:
    Product** products;    // pointer to array of Product pointers
    int count;             // how many products currently
    int capacity;          // total allocated size
    int nextID;       // add this back**********************************************

    void resize();         // doubles capacity when full

    string toLower(string str) const;//to deal with case sensitivity, we will convert the entered string by user into all lower

public:
    ProductManager();
    ~ProductManager();     // destructor — must free memory manually

    // ---- C++ Logic Functions ----
    void addProduct(string name, string category, double price, int stock);
    void updateProduct(int id, string name, string category, double price);
    void deleteProduct(int id);
    void displayAll() const;
    void searchByName(string query) const;
    Product* searchByID(int id);

    void decreaseStock(int id, int quantity);   //Member 3 will call this
    void increaseStock(int id, int quantity);
    void checkLowStock() const;

    // ---- DB Functions (add these) ----
    //The C++ functions stay as the internal backbone. The DB functions are the ones menu in testing.cpp calls.
    void loadFromDB();
    void addToDB(string name, string category, double price, int stock);
    void updateInDB(int id, string name, string category, double price);
    void deleteFromDB(int id);
    void decreaseStockInDB(int id, int qty);
    void increaseStockInDB(int id, int qty);
    void checkLowStockFromDB();
    void searchByNameFromDB(string query);
    void searchByIDFromDB(int id);
    void displayAllFromDB();

    //void saveToFile() const;***************************************************************************************
    //void loadFromFile();*******************************************************************************************
};

#endif
