#include<iostream>
#include<ctime>
#include "Payment.h"
using namespace std;

	Payment::Payment() {
		paymentID = 0;
		billNo = 0;
		paid_amount = 0.0;
		total_bill = 0.0;
		status = "Pending";
		date = "";
	}
	Payment::Payment(int billNo, double total_bill) {
		paymentID = 0;
		paid_amount = 0.0;
		status = "Pending";
		date = "";
		this->billNo = billNo;
		this->total_bill = total_bill;
	}

	//-------------Getters------------------
	double Payment::getAmountPaid() {
		return paid_amount;
	}
	string Payment:: getstatus() {
		return status;
	}
	bool Payment:: checkstatus() {
		if (status == "Pending")
			return true;
		if (status == "Decline")
			return false;// already reject ho gya 
		else // approved ke case main
			return false;
	}
	void Payment:: cancelPayment() {
		if (checkstatus())
		{
			status = "cancelled";
			cout << "Payment  cancelled successfully!" << endl;
		}
		else
			cout << " Payment can not be cancelled (May be declined or approved)" << endl;
	}
	void Payment::refundPayment() {
		if (status == "cancelled")
		{	isRefund = true;
		refundAmount = paid_amount;
	}
		else
		{
			isRefund = false;
			cout << "Cannot refund! Payment is not cancelled." << endl;
		}
	}
	double Payment::getRefund() {
		if (isRefund) {
			cout << "Rs." << " " << refundAmount << "  refunded successfully " << endl;
			return refundAmount;

		}
		else
		{
			cout << "No refund applicable here" << endl;
			return 0.0;
		}
	}
		
	
	Payment:: ~Payment() {
		
	}
