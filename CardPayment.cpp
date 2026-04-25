
#include <iostream>
#include <string>
#include <ctime>      // time functions ke liye zaroori hai
#include "CardPayment.h"

	Cardpayment::Cardpayment(int billNo, double totalBill) :Payment(billNo, totalBill)
	{
		card_holder = "";
		card_no = "";
		expiry = "";
		cvv = "";
	}
	bool Cardpayment:: processpayment() 
	{
		cout << "Enter card holder name" << endl;
		cin >> card_holder;
		cout << "Enter card number" << endl;
		cin >> card_no;
		cout << "Enter expiry date of card" << endl;
		cin >> expiry;
		cout << "Enter security code" << endl;
		cin >> cvv;
		if (validateCard())
		{
			status = "Approved";
			paid_amount = total_bill;
			return true;
		}
		else
		{
			status = "Decline";
			return false;
		}

	}
	bool Cardpayment:: validateCard() {
		if (!validatecard_no())
			return false;
		if (!validateexpiry())
			return false;
		if (!validatecvv())
			return false;
		return true;
	}
	bool Cardpayment::validatecard_no()
	{
		if (card_no.length() != 16)
		{
			cout << "Error:Card is invalid" << endl;
			return false;
		}
		bool alldigits = true;
		for (int i = 0; i < card_no.length(); i++)
		{
			if (!isdigit(card_no[i]))
			{
				cout << "Card No. must contain digits only" << endl;
				return false;
			}

		}
		return true;

	}
	// expiry ka format check kia kah MM/YY hona chahiya is ke lia hum ne pehlay length check ki aur saath hi ye check kia kah 
	// 2nd index per / hai ya nahi 
	bool Cardpayment::validateexpiry() {
		tm timeInfo;
		time_t t = time(0);
		localtime_s(&timeInfo, &t);
		int currentyear = timeInfo.tm_year - 100;
		int currentmonth = timeInfo.tm_mon + 1;

		if (expiry.length() != 5 || expiry[2] != '/')
		{
			cout << "Error!Invalid Card" << endl;
			return false;
		}
		if (!isdigit(expiry[0]) || !isdigit(expiry[1]) ||
			!isdigit(expiry[3]) || !isdigit(expiry[4]))
		{
			cout << "Expiry date must contain digits only" << endl;
			return false;
		}
		//	// hum ne year aur month ko extract kia comparison ke lia 
		//	 10 se multiply kia tens place per move kernay kai lia 
		int year = (expiry[3] - '0') * 10 + (expiry[4] - '0');
		int month = (expiry[0] - '0') * 10 + (expiry[1] - '0');
		// hum ne card  ke year ko system ke year se compare kia he same for month
		if (year < currentyear || (year == currentyear && month < currentmonth))
		{
			cout << "Expired Card" << endl;
			return false;
		}
		return true;
	}
	bool Cardpayment:: validatecvv()
	{
		if (cvv.length() != 3)
		{
			cout << "Security Code is invalid" << endl;
			return false;
		}
		for (int i = 0; i < cvv.length(); i++)
		{
			if (!isdigit(cvv[i]))
			{
				cout << "Invalid!CVV must contain only digits" << endl;
				return false;

			}
		}
		return true;
	}
	void  Cardpayment::displaydetails()  {
		cout << "Card Details are:" << endl;
		cout << "Card Holder is:" << " " << card_holder << "\n";
		cout << "Status:" << " " << status << "\n";
		cout << "Bill No. is" << " " << billNo << "\n";
		cout << "Amount Paid:" << paid_amount << "\n";

	}