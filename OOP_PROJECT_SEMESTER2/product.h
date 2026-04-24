#ifndef PRODUCT_H
#define PRODUCT_H
#include "shared.h"
#include <vector>

class ProductManager
{
private:
    Product** products;    //pointer to array of Product pointers
    int count;             //how many products currently
    int capacity;          //total allocated size

    void resize();         //doubles capacity when full

public:
    ProductManager();
    ~ProductManager();     // destructor — must free memory manually

    void addProduct(string name, string category, double price, int stock);
    void updateProduct(int id, string name, string category, double price);
    void deleteProduct(int id);
    void displayAll() const;
    void searchByName(string query) const;
    Product* searchByID(int id);

    void decreaseStock(int id, int quantity);   //Member 3 will call this
    void increaseStock(int id, int q);
    void checkLowStock() const;

    void saveToFile() const;
    void loadFromFile();
};

#endif
