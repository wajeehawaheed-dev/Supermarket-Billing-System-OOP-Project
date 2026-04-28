#pragma once
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>
#include "Database.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace SBS {
    public ref class PaymentForm : public Form {
    private:
        Label^ lblTitle;
        Label^ lblBillNo;
        Label^ lblTotal;
        RadioButton^ rbCash;
        RadioButton^ rbCard;
        Label^ lblCashAmount;
        TextBox^ txtCashAmount;
        Label^ lblCardHolder;
        TextBox^ txtCardHolder;
        Label^ lblCardNo;
        TextBox^ txtCardNo;
        Label^ lblExpiry;
        TextBox^ txtExpiry;
        Label^ lblCVV;
        TextBox^ txtCVV;
        Button^ btnPay;
        Button^ btnCancel;
        int billNo;
        double totalBill;

    public:
        PaymentForm(int billNo, double totalBill);

    private:
        void InitializeComponent();
        void rbCash_Changed(Object^ sender, EventArgs^ e);
        void rbCard_Changed(Object^ sender, EventArgs^ e);
        void btnPay_Click(Object^ sender, EventArgs^ e);
        void btnCancel_Click(Object^ sender, EventArgs^ e);
    };
}