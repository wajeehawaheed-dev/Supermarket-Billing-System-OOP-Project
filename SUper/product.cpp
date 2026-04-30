//MEMBER 2 Product & ProductManager Class codes
#include "product.h"
#include <iostream>
//#include <fstream> no need for file handling test, since DBMS is integrated
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
{                               //agar stock 5 se kam hua toh error message(value 5 hardcoded in product.h)
    return stock < threshold;
}

//Getters
int Product::getID() const { return productID; }
string Product::getName() const { return name; }
string Product::getCategory() const { return category; }
double Product::getPrice() const { return price; }
int Product::getStock() const { return stock; }
bool Product::getIsActive() const { return isActive; }

// setters
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
ProductManager::ProductManager() //constructors
{
    capacity = 10;                        //start with space for 10 products
    count = 0;
    //nextID = 1;       // always starts at 1**************************************************************

    products = new Product * [capacity];    //allocate array of pointers
    for (int i = 0; i < capacity; i++)
        products[i] = nullptr;    // critical — set all to nullptr for dealing with ID:0 problem
}

ProductManager::~ProductManager() //Destructor
{
    for (int i = 0; i < count; i++)
        delete products[i];       //delete each Product object
    delete[] products;            //delete the array itself
}

void ProductManager::resize()
{
    capacity *= 2;
    Product** newArr = new Product * [capacity];   //allocate bigger array

    for (int i = 0; i < capacity; i++)
        newArr[i] = nullptr;      // initialize new slots too, dealing with ID:0 problem
    for (int i = 0; i < count; i++)
        newArr[i] = products[i];                 //copy pointers over

    delete[] products;                           //free old array
    products = newArr;                           //point to new array
}




//•	Add new product to the system
void ProductManager::addProduct(string name, string category, double price, int stock)
{
    if (price <= 0 || stock < 0)    //price / stock 0 se kam nahi hosaktay
    {
        cout << "INVALID price or stock";
        return;
    }
    if (count == capacity)
        resize();                                //regrow if full
    products[count] = new Product(count + 1, name, category, price, stock);//nextID ki jagah count+1************************
    count++;
    cout << "Product added successfully!" << endl;
}


//•	Update existing product (name, price, category)
void ProductManager::updateProduct(int id, string name, string category, double price)
{
    Product* p = searchByID(id);
    if (p == nullptr)
    {
        cout << "ERROR: Product not found!";
        return;
    }
    p->setName(name);
    p->setCategory(category);
    p->setPrice(price);
    cout << "Product updated successfully!" << endl;
}


//•	Delete/deactivate product
void ProductManager::deleteProduct(int id)
{
    Product* p = searchByID(id);
    if (p == nullptr)
    {
        cout << "ERROR: Product not found!";
        return;
    }
    p->setIsActive(false);   //soft delete, memory stays allocated
    cout << "Product removed successfully" << endl;
}


//Display Function
void ProductManager::displayAll() const
{
    cout << "\n--- All Products ---\n";
    bool check = false;
    for (int i = 0; i < count; i++)
        if (products[i] != nullptr && products[i]->getIsActive())
        {
            products[i]->display();
            check = true;
        }
    if (!check)
        cout << "No products available!" << endl;
}


//•	Search product by name or ID
void ProductManager::searchByName(string query) const
{
    cout << "\n--- Search Results ---\n";
    bool found = false;
    for (int i = 0; i < count; i++)
    {
        if (products[i] != nullptr && products[i]->getIsActive() && toLower(products[i]->getName()).find(toLower(query)) != string::npos)
        {
            products[i]->display();
            found = true;
        }
    }
    if (!found)
        cout << "No products found" << endl;
}
Product* ProductManager::searchByID(int id)
{
    for (int i = 0; i < count; i++) //handle the display in main() because it's causing errors here
    {
        if (products[i]->getID() == id && products[i]->getIsActive())
        {
            return products[i];    //return immediately when found
        }
    }
    return nullptr;                //only reaches here if not found
}


//•	Auto stock update after every sale(decrease by quantity sold)
void ProductManager::decreaseStock(int id, int quantity)
{
    Product* p = searchByID(id);
    if (p == nullptr)
    {
        cout << "ERROR: Product not found!" << endl;
        return;
    }
    if (p->getStock() < quantity)
    {
        cout << "Insufficient stock!" << endl;
        return;
    }
    p->setStock(p->getStock() - quantity);

    if (p->isLowStock())
        cout << "WARNING: Low stock on " << p->getName() << "!" << endl;
}

//•	Manual stock update by admin
void ProductManager::increaseStock(int id, int quantity)
{
    Product* p = searchByID(id);
    if (p == nullptr)
    {
        cout << "ERROR: Product not found!" << endl;
        return;
    }
    p->setStock(p->getStock() + quantity);
    cout << "Stock updated successfully!" << endl;
}

//•	Low stock alert — warning when stock falls below 5
void ProductManager::checkLowStock() const
{
    cout << "\n--- Low Stock Alert ---\n";
    for (int i = 0; i < count; i++)
    {
        if (products[i]->getIsActive() && products[i]->isLowStock())
            cout << "LOW: " << products[i]->getName() << " | Stock: " << products[i]->getStock() << endl;
    }
}


string ProductManager::toLower(string str) const //to deal with case sensitivity
{
    for (int i = 0; i < str.length(); i++)
        str[i] = tolower(str[i]);
    return str;
}



/*DBMS integrated, Temporary File Handling should be removed
void ProductManager::saveToFile() const
{
    ofstream f("products.txt");

    f << nextID << "\n";      // save nextID*******************************************************
    f << count << "\n";                // save count 

    for (int i = 0; i < count; i++)
        f << products[i]->getID() << ","
        << products[i]->getName() << ","
        << products[i]->getCategory() << ","
        << products[i]->getPrice() << ","
        << products[i]->getStock() << ","
        << products[i]->getIsActive() << "\n";
    f.close();
}

void ProductManager::loadFromFile() {

    ifstream f("products.txt");
    if (!f.is_open()) return;

    int total = 0;
    f >> nextID;               // read nextID first************************************
    f >> total;
    if (total <= 0) {   // if reading fails or file is empty
        f.close();
        return;                           // stop — nothing to load
    }
    f.ignore();



    for (int i = 0; i < total; i++) {
        int id, stock, active;
        string name, category;
        double price;

        if (!(f >> id)) break;    // stop if reading fails mid-file

        f >> id;       f.ignore();
        getline(f, name, ',');
        getline(f, category, ',');
        f >> price;    f.ignore();
        f >> stock;    f.ignore();
        f >> active;

        if (count == capacity)
            resize();                              // grow array if full

        products[count] = new Product(id, name, category, price, stock);
        products[count]->setIsActive(active);
        count++;


    }
    f.close();
}
*/


/*
products[i].display();   // wrong — products[i] is a pointer, not an object
products[i]->display();  // correct — -> dereferences the pointer then calls method
// these two are identical:
products[i]->display();
(*products[i]).display();
*/