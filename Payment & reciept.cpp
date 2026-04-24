#include<iostream>
#include "database.h"
#include<ctime>
using namespace std;
class Payment {
protected:
	int paymentID;
	int billNo;
	double paid_amount;
	double total_bill;
	string status;
	string  date;
public:
	Payment() {
		paymentID = 0;
		billNo = 0;
		paid_amount = 0.0;
		total_bill = 0.0;
		status = "Pending";
		date = "";
	}
	Payment(int billNo, double total_bill) {
		paymentID = 0;
		paid_amount = 0.0;
		status = "Pending";
		date = "";
		this->billNo = billNo;
		this->total_bill = total_bill;
	}
	//----------------VIRTUAL------------------------
	//We made pure virtual objects Because every child will write its own logic 
	virtual void displaydetails() = 0;
	virtual bool processpayment() = 0;


	//-------------Getters------------------
	double getAmountPaid() {
		return paid_amount;
	}
	string getstatus() {
		return status;
	}
	bool checkstatus() {
		if (status == "Pending")
			return true;
		if (status == "Decline")
			return false;// already reject ho gya 
		else // approved ke case main
			return false;
	}
	void cancelPayment() {
		if (checkstatus())
		{
			status = "cancelled";
			cout << "Payment  cancelled successfully!" << endl;
		}
		else
			cout << " Payment can not be cancelled (May be declined or approved)" << endl;
	}
	virtual ~Payment() {

	}
};