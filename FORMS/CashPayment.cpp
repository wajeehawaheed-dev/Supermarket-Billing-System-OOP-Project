#include<iostream>
#include"CashPayment.h"
using namespace std;
	CashPayment::CashPayment(int billNO, double Amount) : Payment(billNO, Amount)
	{
		cashgiven = 0.0;
		change = 0.0;
	}
	bool CashPayment:: processpayment() 
	{
		do {
			cout << "Enter cash amount:" << endl;
			cin >> cashgiven;
			
			if (cashgiven <= 0)
			{
				cout << "Invalid Account!Enter a valid Amount" << endl;
			}
		} while (cashgiven <= 0);
		if (cashgiven < total_bill)
		{
			cout << "Insufficient Amount! Bill is" << total_bill << endl;
			status = "Decline";
			return false;
		}
		else
		{
			calculatechange();
			status = "Approved";
			paid_amount = cashgiven;
			return true;
		}

	}
	void  CashPayment::calculatechange() {
		if (cashgiven == total_bill)
			change = 0;
		else
		{
			change = cashgiven - total_bill;
			cout << "Change to return is:" << change << endl;

		}
	}
	void  CashPayment::displaydetails() {
		cout << "Cash Payemnt is" << endl;
		cout << "Bill No is : " << billNo << endl;
		cout << "Total Bill is : " << total_bill << endl;
		cout << "Cash Given is : " << cashgiven << endl;
		cout << "Change is: " << change << endl;
		cout << "Status: " << status << endl;
	}