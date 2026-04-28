
#include <iostream>
#include <string>
#include <ctime>
#include "CardPayment.h"

using namespace std;

Cardpayment::Cardpayment(int billNo, double totalBill) : Payment(billNo, totalBill)
{
    card_holder = "";
    card_no = "";
    expiry = "";
    cvv = "";
}
void Cardpayment::removespaces() {
    string result = "";
    for (int i = 0; i < card_no.length(); i++) {
        if (card_no[i] != ' ') {
            result += card_no[i];
        }
    }
    card_no = result;
}

bool isOnlySpaces(const string& s) {
    for (char c : s) {
        if (c != ' ')
            return false;
    }
    return true;
}

bool Cardpayment::processpayment()
{
    int attempts = 0;

    do {
        cout << "Enter card holder name: ";
        cin.ignore();
        getline(cin, card_holder);

        cout << "Enter card number: ";
        getline(cin, card_no);

        cout << "Enter expiry date (MM/YY): ";
        getline(cin, expiry);

        cout << "Enter CVV: ";
        getline(cin, cvv);
        attempts++;

        if (card_holder.empty() || card_no.empty() || cvv.empty() || expiry.empty() || isOnlySpaces(card_holder) || isOnlySpaces(card_no) || isOnlySpaces(cvv) || isOnlySpaces(expiry)) {

            cout << "Error: Fields cannot be empty or only spaces!\n";
            continue;
        }
        removespaces();//function call to remove spaces for enteries like John Smith 
        if (validateCard())
        {
            status = "Approved";
            paid_amount = total_bill;
            return true;
        }
        else
        {
            cout << "Invalid card details!\n";
            status = "Decline";
        }

    } while (attempts < 3);

    cout << "Attempts finished. Try again later.\n";
    status = "Decline";
    return false;
}

// ---------------- VALIDATION ----------------

bool Cardpayment::validateCard()
{
    if (!validatecard_no())
        return false;
    if (!validateexpiry())
        return false;
    if (!validatecvv())
        return false;

    return true;
}

// ---------------- CARD NUMBER ----------------

bool Cardpayment::validatecard_no()
{
    if (card_no.length() != 16)
    {
        cout << "Error: Card number must be 16 digits\n";
        return false;
    }

    for (int i = 0; i < card_no.length(); i++)
    {
        if (!isdigit(card_no[i]))
        {
            cout << "Card number must contain digits only\n";
            return false;
        }
    }

    return true;
}

// ---------------- EXPIRY ----------------

bool Cardpayment::validateexpiry()
{
    tm timeInfo;
    time_t t = time(0);
    localtime_s(&timeInfo, &t);

    int currentyear = timeInfo.tm_year - 100;
    int currentmonth = timeInfo.tm_mon + 1;

    if (expiry.length() != 5 || expiry[2] != '/')
    {
        cout << "Invalid format! Use MM/YY \n";
        return false;
    }
    //hum nai month aur year ka format check kernai kai lia specific indexes check kia 
    if (!isdigit(expiry[0]) || !isdigit(expiry[1]) || !isdigit(expiry[3]) || !isdigit(expiry[4]))
    {
        cout << "Expiry must contain digits only\n";
        return false;
    }
    //hum ne 10 se multiply kia so it can move to ten's place 
    int month = (expiry[0] - '0') * 10 + (expiry[1] - '0');
    int year = (expiry[3] - '0') * 10 + (expiry[4] - '0');
    //check for month range
    if (month < 1 || month > 12)
    {
        cout << "Invalid month in expiry date!\n";
        return false;
    }

    //  EXPIRY CHECK
    //we compared system's year with card's year same for month  
    if (year < currentyear || (year == currentyear && month < currentmonth))
    {
        cout << "Card expired!\n";
        return false;
    }

    return true;
}

// ---------------- CVV ----------------

bool Cardpayment::validatecvv()
{
    if (cvv.length() != 3)
    {
        cout << "CVV must be 3 digits\n";
        return false;
    }

    for (int i = 0; i < cvv.length(); i++)
    {
        if (!isdigit(cvv[i]))
        {
            cout << "CVV must contain digits only\n";
            return false;
        }
    }

    return true;
}

// ---------------- DISPLAY ----------------

void Cardpayment::displaydetails()
{
    cout << "\n--- Card Details ---\n";
    cout << "Card Holder: " << card_holder << "\n";
    cout << "Status: " << status << "\n";
    cout << "Bill No: " << billNo << "\n";
    cout << "Amount Paid: " << paid_amount << "\n";
}
