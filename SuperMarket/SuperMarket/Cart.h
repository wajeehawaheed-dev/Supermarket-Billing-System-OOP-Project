#pragma once
#include <string>
#include "constants.h"
#include "shared.h"
using namespace std;

class Cart {
    CartItem* items;
    int count;
    int capacity;

public:
    Cart() {
        capacity = 10;
        count = 0;
        items = new CartItem[capacity];
    }
    ~Cart() {
        delete[] items;
    }

    void addItem(int id, string name, double price, int qty) {
        // Resize if full
        if (count >= capacity) {
            capacity *= 2;
            CartItem* newItems = new CartItem[capacity];
            for (int i = 0; i < count; i++)
                newItems[i] = items[i];
            delete[] items;
            items = newItems;
        }
        if (count < capacity) {
            items[count].productID = id;
            items[count].name = name;
            items[count].price = price;
            items[count].quantity = qty;
            items[count].itemTotal = price * qty;
            count++;
        }
    }
    void clearCart() {
        count = 0;
    }
    CartItem* getItems() {
        return items;
    }
    int getCount() {
        return count;
    }
    double getSubTotal() {
        double sum = 0;
        for (int i = 0; i < count; i++)
            sum += items[i].itemTotal;
        return sum;
    }
    double calculateDiscount() {
        double subtotal = getSubTotal();
        if (count >= DISCOUNT_THRESHOLD_2) return subtotal * DISCOUNT_RATE_2;
        if (count >= DISCOUNT_THRESHOLD_1) return subtotal * DISCOUNT_RATE_1;
        return 0;
    }
    double calculateTax() {
        return (getSubTotal() - calculateDiscount()) * TAX_RATE;
    }
    double getGrandTotal() {
        return getSubTotal() - calculateDiscount() + calculateTax();
    }
};