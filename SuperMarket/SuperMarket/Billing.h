#pragma once
#include "Cart.h"
#include "constants.h"
class Billing {
private:
	double subtotal;
	double discount;
	double tax;
	double grandTotal;
	int itemCount;
public:
	Billing(Cart* cart) {
		subtotal = cart->getSubTotal();
		itemCount = cart->getCount();
		if(itemCount >= DISCOUNT_THRESHOLD_2) {
			discount = subtotal * DISCOUNT_RATE_2;
		}
		else if (itemCount >= DISCOUNT_THRESHOLD_1) {
			discount = subtotal * DISCOUNT_RATE_1;
		}
		else {
			discount = 0;
		}
		tax = (subtotal - discount) * TAX_RATE;
		grandTotal = subtotal - discount + tax;
	}
	double getSubtotal() {
		return subtotal;
	}
	double getDiscount() {
		return discount;
	}
	double getTax() {
		return tax;
	}
	double getGrandTotal() {
		return grandTotal;
	}
	int getItemCount() {
		return itemCount;
	}
};