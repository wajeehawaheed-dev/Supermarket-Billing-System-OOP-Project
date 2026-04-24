#pragma once
#include <vector>
#include <string>
using namespace std;
struct CartItem {
	int productID;
	string name;
	double price;
	int quantity;
	double total;
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
		item.total = price * qty;
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
			sum += item.total;
		}
		return sum;
	}
};
