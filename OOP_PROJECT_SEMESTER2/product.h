#ifndef PRODUCT_H
#define PRODUCT_H
#include "shared.h"
#include <vector>

class ProductManager
{
private:
    vector<Product> products;
    int nextID;

public:
    ProductManager();

    void addProduct(string name, string category, double price, int stock);
    void updateProduct(int id, string name, string category, double price);
    void deleteProduct(int id);
    void displayAll() const;
    void searchByName(string query) const;
    Product* searchByID(int id);

    void decreaseStock(int id, int quantity);   //Member 3 will call this
    void increaseStock(int id, int quantity);
    void checkLowStock() const;

    void saveToFile() const;
    void loadFromFile();
};

#endif
