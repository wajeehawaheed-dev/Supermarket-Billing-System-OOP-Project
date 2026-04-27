#using <System.dll>
#using <System.Data.dll>
#using <System.Windows.Forms.dll>

#include "database.h"
#include "shared.h"
#include "product.h"
#include <iostream>

using namespace std;
using namespace System;
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::Runtime::InteropServices;


//----------Admin (Shopkeeper) End---------------
//Full CRUD Access : Only the Admin should have access to addToDB, updateInDB, and deleteFromDB
//Manual Stock Control: The increaseStockInDB function is strictly for the Admin to record new shipments.
//Oversight: Only the Admin should receive the checkLowStockFromDB alerts to know what to reorder

//----------User (Customer/Cashier) End-----------
//Read-Only Access: Customers/Cashiers should only be able to use displayAllFromDB and searchByNameFromDB
//Auto-Updates: When a customer makes a purchase, your decreaseStockInDB function is triggered automatically behind the scenes.
//Filtering: You must ensure the Customer End only sees products where IsActive = 1 so they don't try to buy discontinued items.

// Converts .NET String^ to std::string safely
string toStdString(String^ s) {
    IntPtr ptr = Marshal::StringToHGlobalAnsi(s);
    string result = reinterpret_cast<const char*>(ptr.ToPointer());
    Marshal::FreeHGlobal(ptr);
    return result;
}

void ProductManager::addToDB(string name, string category, double price, int stock) {
    String^ n = gcnew String(name.c_str());
    String^ c = gcnew String(category.c_str());
    SBS::Database::ExecuteNonQuery(
        "INSERT INTO Products (Name, Category, Price, Stock, IsActive) VALUES (@n, @c, @pr, @s, 1)",
        gcnew SqlParameter("@n", n),
        gcnew SqlParameter("@c", c),
        gcnew SqlParameter("@pr", price),
        gcnew SqlParameter("@s", stock));
    cout << "Product added successfully!\n";
}

void ProductManager::loadFromDB() {
    DataTable^ dt = SBS::Database::ExecuteQuery("SELECT * FROM Products WHERE IsActive = 1");
    DataTableReader^ reader = dt->CreateDataReader();
    while (reader->Read()) {
        int    id = reader->GetInt32(0);
        String^ name = reader->GetString(1);
        String^ cat = reader->GetString(2);
        double price = Convert::ToDouble(reader->GetDecimal(3));
        int    stock = reader->GetInt32(4);
        if (count == capacity) resize();
        products[count] = new Product(id, toStdString(name), toStdString(cat), price, stock);
        count++;
    }
    reader->Close();
}

void ProductManager::updateInDB(int id, string name, string category, double price) {
    String^ n = gcnew String(name.c_str());
    String^ c = gcnew String(category.c_str());
    SBS::Database::ExecuteNonQuery(
        "UPDATE Products SET Name=@n, Category=@c, Price=@pr WHERE ProductID=@id AND IsActive=1",
        gcnew SqlParameter("@n", n),
        gcnew SqlParameter("@c", c),
        gcnew SqlParameter("@pr", price),
        gcnew SqlParameter("@id", id));
    cout << "Product updated successfully!\n";
}

void ProductManager::deleteFromDB(int id) {
    SBS::Database::ExecuteNonQuery(
        "UPDATE Products SET IsActive=0 WHERE ProductID=@id",
        gcnew SqlParameter("@id", id));
    cout << "Product deleted successfully!\n";
}

void ProductManager::decreaseStockInDB(int id, int qty) {
    int rows = SBS::Database::ExecuteNonQuery(
        "UPDATE Products SET Stock=Stock-@qty WHERE ProductID=@id AND Stock>=@qty AND IsActive=1",
        gcnew SqlParameter("@qty", qty),
        gcnew SqlParameter("@id", id));
    if (rows == 0)
        cout << "ERROR: Insufficient stock or product not found.\n";
    else {
        cout << "Stock decreased successfully.\n";
        checkLowStockFromDB();
    }
}

void ProductManager::increaseStockInDB(int id, int qty) {
    SBS::Database::ExecuteNonQuery(
        "UPDATE Products SET Stock=Stock+@qty WHERE ProductID=@id AND IsActive=1",
        gcnew SqlParameter("@qty", qty),
        gcnew SqlParameter("@id", id));
    cout << "Stock increased successfully.\n";
}

void ProductManager::checkLowStockFromDB() {
    // columns: [0]=ProductID [1]=Name [2]=Stock
    DataTable^ dt = SBS::Database::ExecuteQuery(
        "SELECT ProductID, Name, Stock FROM Products WHERE Stock < 5 AND IsActive = 1");
    cout << "\n--- Low Stock Alert ---\n";
    if (dt->Rows->Count == 0) { cout << "All products sufficiently stocked.\n"; return; }
    DataTableReader^ reader = dt->CreateDataReader();
    while (reader->Read()) {
        int    id = reader->GetInt32(0);
        string sName = toStdString(reader->GetString(1));
        int    stock = reader->GetInt32(2);
        cout << "LOW: ID=" << id << " | " << sName << " | Stock: " << stock << "\n";
    }
    reader->Close();
}

void ProductManager::searchByNameFromDB(string query) {
    String^ q = gcnew String(("%" + query + "%").c_str());
    DataTable^ dt = SBS::Database::ExecuteQuery(
        "SELECT * FROM Products WHERE Name LIKE @q AND IsActive = 1",
        gcnew SqlParameter("@q", q));
    cout << "\n--- Search Results ---\n";
    if (dt->Rows->Count == 0) { cout << "No products found.\n"; return; }
    DataTableReader^ reader = dt->CreateDataReader();
    while (reader->Read()) {
        int    id = reader->GetInt32(0);
        string sName = toStdString(reader->GetString(1));
        string sCat = toStdString(reader->GetString(2));
        double price = Convert::ToDouble(reader->GetDecimal(3));
        int    stock = reader->GetInt32(4);
        cout << "ID: " << id << " | " << sName << " | " << sCat
            << " | Rs." << price << " | Stock: " << stock << "\n";
    }
    reader->Close();
}

void ProductManager::searchByIDFromDB(int id) {
    DataTable^ dt = SBS::Database::ExecuteQuery(
        "SELECT * FROM Products WHERE ProductID=@id AND IsActive=1",
        gcnew SqlParameter("@id", id));
    cout << "\n--- Search Result ---\n";
    if (dt->Rows->Count == 0) { cout << "No product found.\n"; return; }
    DataTableReader^ reader = dt->CreateDataReader();
    if (reader->Read()) {
        string sName = toStdString(reader->GetString(1));
        string sCat = toStdString(reader->GetString(2));
        double price = Convert::ToDouble(reader->GetDecimal(3));
        int    stock = reader->GetInt32(4);
        cout << "ID: " << id << " | " << sName << " | " << sCat
            << " | Rs." << price << " | Stock: " << stock << "\n";
    }
    reader->Close();
}

void ProductManager::displayAllFromDB() {
    DataTable^ dt = SBS::Database::ExecuteQuery(
        "SELECT * FROM Products WHERE IsActive=1 ORDER BY ProductID ASC");
    cout << "\n--- All Products ---\n";
    if (dt->Rows->Count == 0) { cout << "No products found.\n"; return; }
    DataTableReader^ reader = dt->CreateDataReader();
    while (reader->Read()) {
        int    id = reader->GetInt32(0);
        string sName = toStdString(reader->GetString(1));
        string sCat = toStdString(reader->GetString(2));
        double price = Convert::ToDouble(reader->GetDecimal(3));
        int    stock = reader->GetInt32(4);
        cout << "ID: " << id << " | " << sName << " | " << sCat
            << " | Rs." << price << " | Stock: " << stock << "\n";
    }
    reader->Close();
}