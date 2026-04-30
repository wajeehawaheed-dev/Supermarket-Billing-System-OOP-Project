//MEMBER 2 Product & ProductManager Class codes
#include "product.h"

using namespace System;
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::Windows::Forms;

//---Product class implementations---

Product::Product(int id, String^ n, String^ cat, double p, int s)
{
    productID = id;
    name = n;
    category = cat;
    price = p;
    stock = s;
    isActive = true;
}

void Product::display()
{
    // Show in MessageBox since this is a WinForms app, not console
    MessageBox::Show(
        "ID: " + productID +
        "\nName: " + name +
        "\nCategory: " + category +
        "\nPrice: Rs." + price +
        "\nStock: " + stock,
        "Product Details");
}

bool Product::isLowStock(int threshold)
{
    return stock < threshold;
}

bool Product::isLowStock()
{
    return stock < 5;  // default threshold
}

int Product::getID() { return productID; }
String^ Product::getName() { return name; }
String^ Product::getCategory() { return category; }
double Product::getPrice() { return price; }
int Product::getStock() { return stock; }
bool Product::getIsActive() { return isActive; }

void Product::setName(String^ n) { name = n; }
void Product::setCategory(String^ c) { category = c; }
void Product::setPrice(double p) { if (p > 0) price = p; }
void Product::setStock(int s) { if (s >= 0) stock = s; }
void Product::setIsActive(bool status) { isActive = status; }


//--- ProductManager implementations ---

ProductManager::ProductManager()
{
    products = gcnew List<Product^>();
}

// Add product (in-memory)
void ProductManager::addProduct(String^ name, String^ category, double price, int stock)
{
    if (price <= 0 || stock < 0) {
        MessageBox::Show("Invalid price or stock");
        return;
    }
    int newID = products->Count + 1;
    products->Add(gcnew Product(newID, name, category, price, stock));
}

void ProductManager::updateProduct(int id, String^ name, String^ category, double price)
{
    Product^ p = searchByID(id);
    if (p == nullptr) {
        MessageBox::Show("Product not found");
        return;
    }
    p->setName(name);
    p->setCategory(category);
    p->setPrice(price);
}

void ProductManager::deleteProduct(int id)
{
    Product^ p = searchByID(id);
    if (p == nullptr) {
        MessageBox::Show("Product not found");
        return;
    }
    p->setIsActive(false);
}

void ProductManager::displayAll()
{
    for each (Product ^ p in products) {
        if (p->getIsActive()) {
            p->display();
        }
    }
}

void ProductManager::searchByName(String^ query)
{
    String^ q = toLower(query);
    for each (Product ^ p in products) {
        if (p->getIsActive() && toLower(p->getName())->Contains(q)) {
            p->display();
        }
    }
}

Product^ ProductManager::searchByID(int id)
{
    for each (Product ^ p in products) {
        if (p->getID() == id && p->getIsActive()) {
            return p;
        }
    }
    return nullptr;
}

void ProductManager::decreaseStock(int id, int quantity)
{
    Product^ p = searchByID(id);
    if (p == nullptr) return;
    if (p->getStock() < quantity) {
        MessageBox::Show("Insufficient stock");
        return;
    }
    p->setStock(p->getStock() - quantity);
}

void ProductManager::increaseStock(int id, int quantity)
{
    Product^ p = searchByID(id);
    if (p == nullptr) return;
    p->setStock(p->getStock() + quantity);
}

void ProductManager::checkLowStock()
{
    for each (Product ^ p in products) {
        if (p->getIsActive() && p->isLowStock()) {
            MessageBox::Show("LOW: " + p->getName() + " | Stock: " + p->getStock());
        }
    }
}

String^ ProductManager::toLower(String^ str)
{
    return str->ToLower();
}


//-------------------- DB Methods --------------------

void ProductManager::loadFromDB()
{
    products->Clear();

    DataTable^ result = SBS::Database::ExecuteQuery(
        "SELECT ProductID, Name, Category, Price, Stock, IsActive FROM Products WHERE IsActive = 1 ORDER BY ProductID");

    if (result == nullptr) return;

    for each (DataRow ^ row in result->Rows) {
        int id = Convert::ToInt32(row["ProductID"]);
        String^ n = row["Name"]->ToString();
        String^ c = row["Category"]->ToString();
        double p = Convert::ToDouble(row["Price"]);
        int s = Convert::ToInt32(row["Stock"]);
        bool active = Convert::ToBoolean(row["IsActive"]);

        Product^ prod = gcnew Product(id, n, c, p, s);
        prod->setIsActive(active);
        products->Add(prod);
    }
}

void ProductManager::addToDB(String^ name, String^ category, double price, int stock)
{
    if (price <= 0 || stock < 0) return;
    SBS::Database::ExecuteNonQuery(
        "INSERT INTO Products (Name, Category, Price, Stock, IsActive) VALUES (@n, @c, @p, @s, 1)",
        gcnew SqlParameter("@n", name),
        gcnew SqlParameter("@c", category),
        gcnew SqlParameter("@p", price),
        gcnew SqlParameter("@s", stock));
    loadFromDB();
}

void ProductManager::updateInDB(int id, String^ name, String^ category, double price)
{
    if (price <= 0) return;
    SBS::Database::ExecuteNonQuery(
        "UPDATE Products SET Name = @n, Category = @c, Price = @p WHERE ProductID = @id",
        gcnew SqlParameter("@n", name),
        gcnew SqlParameter("@c", category),
        gcnew SqlParameter("@p", price),
        gcnew SqlParameter("@id", id));
    loadFromDB();
}

void ProductManager::deleteFromDB(int id)
{
    SBS::Database::ExecuteNonQuery(
        "UPDATE Products SET IsActive = 0 WHERE ProductID = @id",
        gcnew SqlParameter("@id", id));
    loadFromDB();
}

void ProductManager::decreaseStockInDB(int id, int qty)
{
    if (qty <= 0) return;
    Object^ stockObj = SBS::Database::ExecuteScalar(
        "SELECT Stock FROM Products WHERE ProductID = @id",
        gcnew SqlParameter("@id", id));
    if (stockObj == nullptr) return;
    int currentStock = Convert::ToInt32(stockObj);
    if (currentStock < qty) return;

    SBS::Database::ExecuteNonQuery(
        "UPDATE Products SET Stock = Stock - @q WHERE ProductID = @id",
        gcnew SqlParameter("@q", qty),
        gcnew SqlParameter("@id", id));
    loadFromDB();
}

void ProductManager::increaseStockInDB(int id, int qty)
{
    if (qty <= 0) return;
    SBS::Database::ExecuteNonQuery(
        "UPDATE Products SET Stock = Stock + @q WHERE ProductID = @id",
        gcnew SqlParameter("@q", qty),
        gcnew SqlParameter("@id", id));
    loadFromDB();
}

void ProductManager::checkLowStockFromDB() {
    // No-op; UI handles via DB query directly
}

void ProductManager::searchByNameFromDB(String^ query) {
    // No-op; UI handles via DB query directly
}

void ProductManager::searchByIDFromDB(int id) {
    // No-op; UI handles via DB query directly
}

void ProductManager::displayAllFromDB()
{
    loadFromDB();
}