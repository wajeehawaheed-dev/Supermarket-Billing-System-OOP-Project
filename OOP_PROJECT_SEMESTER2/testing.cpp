//Testing main for member 2 only
#include "database.h"
#include "product.h"
#include <iostream>
using namespace std;
using namespace System;

int main()
{
    //cout << "Looking for file in: ";//temppp****************************
    //system("cd");       // prints current working directory

    //-----------------------------------------------------------------------------------------------
    //DATABASE Testing Code
    /*if (SBS::Database::TestConnection())
        cout << "Connected!\n";
    else
        cout << "Failed!\n";
    return 0;*/

    //-----------------------------------------------------------------------------------------------


    ProductManager pm;
    //pm.loadFromDB();   // this instead of file handling functions, remove this line — DB functions query directly, no need to load into memory

    int choice;
    do {
        cout << "\n1. Add Product\n2. Update Product\n3. Delete Product\n"
            << "4. Display All\n5. Search by Name\n6. Search by ID\n"
            << "7. Decrease Stock\n8. Increase Stock\n9. Low Stock Alert\n0. Exit\n\n"
            << "Choice: ";
        cin >> choice;
        cin.ignore();          //put it HERE — clears buffer after every choice input

        if (choice == 1)
        {
            string name, cat;
            double price;
            int stock;
            cout << "Name: "; getline(cin, name);
            cout << "Category: ";  getline(cin, cat);//yahan par cin.ignore use nahi karna, only once at the beginning
            cout << "Price: "; cin >> price;
            cout << "Stock: "; cin >> stock;
            pm.addToDB(name, cat, price, stock);//all functions of DATABASE 
        }
        else if (choice == 2) 
        {
            int id;
            string name, cat;
            double price;
            cout << "ID: "; cin >> id;
            cin.ignore();          //clears leftover newline after reading id
            cout << "New Name: "; getline(cin, name);
            cout << "New Category: "; getline(cin, cat);
            cout << "New Price: "; cin >> price;
            pm.updateInDB(id, name, cat, price);
        }
        else if (choice == 3) 
        {
            int id; cout << "ID to delete: "; cin >> id;
            pm.deleteFromDB(id);
        }
        else if (choice == 4)
        {
            pm.displayAllFromDB();
        }
        else if (choice == 5)
        {
            string q; cout << "Search name: "; getline(cin, q);
            pm.searchByNameFromDB(q);
        }
        else if (choice == 6)
        {
            int id;
            cout << "Search ID: ";
            cin >> id;
            pm.searchByIDFromDB(id);    //replaces the old searchByID block entirely, it no longer searches in array as data is now stored in DBMS
        }
        else if (choice == 7)
        {
            int id, quantity;
            cout << "ID: "; cin >> id;
            cout << "Quantity to decrease: "; cin >> quantity;
            pm.decreaseStockInDB(id, quantity);
        }
        else if (choice == 8) 
        {
            int id, quantity;
            cout << "ID: "; cin >> id;
            cout << "Qty to increase: "; cin >> quantity;
            pm.increaseStockInDB(id, quantity);
        }
        else if (choice == 9)
        {
            pm.checkLowStockFromDB();
        }

        cin.ignore();
    } while (choice != 0);


    //pm.saveToFile(); sql saves automatically
    cout << "Data saved. Goodbye!" << endl;
    return 0;
}