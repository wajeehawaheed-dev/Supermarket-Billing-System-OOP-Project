#pragma once
ref class ReceiptForm;
#using <System.dll>
#using <System.Data.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>
#include "database.h"
#include "ReceiptForm.h"
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace SUper {
    public ref class PaymentForm : public Form {
    private:
        // Header Panel
        Panel^ pnlHeader;
        Label^ lblTitle;
        Label^ lblBillNo;
        Label^ lblTotal;

        // Payment Method
        Panel^ pnlMethod;
        Label^ lblMethodTitle;
        RadioButton^ rbCash;
        RadioButton^ rbCard;

        // Cash Panel
        Panel^ pnlCash;
        Label^ lblCustName;
        TextBox^ txtCustName;
        Label^ lblCashAmount;
        TextBox^ txtCashAmount;

        // Card Panel
        Panel^ pnlCard;
        Label^ lblCardHolder;
        TextBox^ txtCardHolder;
        Label^ lblCardNo;
        TextBox^ txtCardNo;
        Label^ lblExpiry;
        TextBox^ txtExpiry;
        Label^ lblCVV;
        TextBox^ txtCVV;

        // Lock + Buttons
        Label^ lblLockMsg;
        Button^ btnPay;
        Button^ btnCancel;
        System::Windows::Forms::Timer^ unlockTimer;

        int billNo;
        double totalBill;
        int failedAttempts;
        bool formLocked;
        int secondsRemaining;

    public:
        PaymentForm(int billNo, double totalBill);

    private:
        void InitializeComponent();
        void rbCash_Changed(Object^ sender, EventArgs^ e);
        void rbCard_Changed(Object^ sender, EventArgs^ e);
        void btnPay_Click(Object^ sender, EventArgs^ e);
        void btnCancel_Click(Object^ sender, EventArgs^ e);
        void unlockTimer_Tick(Object^ sender, EventArgs^ e);
        System::Void PaymentForm_Load(System::Object^ sender, System::EventArgs^ e) {}

        // Helper: check if day is valid for given month/year
        bool IsValidExpiryDate(int month, int year);
    };
}