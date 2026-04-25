#pragma once
#include <vector>
#include <string>
#include "constants.h"
using namespace std;

struct CartItem {
    int productID;
    string name;
    double price;
    int quantity;
    double itemTotal;
};

class Cart {
    vector<CartItem> items;
public:
    void addItem(int id, string name, double price, int qty) {
        CartItem item;
        item.productID = id;
        item.name = name;
        item.price = price;
        item.quantity = qty;
        item.itemTotal = price * qty;
        items.push_back(item);
    }
    void clearCart() {
        items.clear();
    }
    vector<CartItem> getItems() {
        return items;
    }
    double getSubTotal() {
        double sum = 0;
        for (const auto& item : items) {
            sum += item.itemTotal;
        }
        return sum;
    }
    double calculateDiscount() {
        int itemCount = items.size();
        double subtotal = getSubTotal();
        if (itemCount >= DISCOUNT_THRESHOLD_2)
            return subtotal * DISCOUNT_RATE_2;
        else if (itemCount >= DISCOUNT_THRESHOLD_1)
            return subtotal * DISCOUNT_RATE_1;
        return 0;
    }
    double calculateTax() {
        double subtotal = getSubTotal();
        double discount = calculateDiscount();
        return (subtotal - discount) * TAX_RATE;
    }
    double getGrandTotal() {
        return getSubTotal() - calculateDiscount() + calculateTax();
    }
};