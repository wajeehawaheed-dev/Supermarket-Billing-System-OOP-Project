#ifndef CARDPAYMENT_H
#define CARDPAYMENT_H
#include "Payment.h"
#include <string>
using namespace std;

class Cardpayment :public Payment {
	// hum ne private kia becoz kisi child class nai is ko access nahi kerna tha  as cardpayment has no child class
private:
	string card_no;// 16 or 15 digits 
	string card_holder;//name 
	string expiry;//month & year 
	string cvv;// 3 or 4 digit 
	int attempts;
public:
	Cardpayment(int billNo, double totalBill);
	//virtual functions override 
	bool processpayment() override;
	void displaydetails() override;
	// Helper Validation functions
	bool validateCard();
	bool validatecard_no();
	bool validateexpiry();
	bool validatecvv();
};
#endif