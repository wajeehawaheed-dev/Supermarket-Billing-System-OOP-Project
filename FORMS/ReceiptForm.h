#pragma once
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>
#include "Database.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace SBS {
    public ref class ReceiptForm : public Form {
    private:
        Panel^ pnlHeader;
        Panel^ pnlBody;
        Label^ lblStoreName;
        Label^ lblReceipt;
        Label^ lblBillNo;
        Label^ lblDate;
        Label^ lblCashier;
        Label^ lblDivider1;
        Label^ lblItems;
        Label^ lblDivider2;
        Label^ lblSubtotal;
        Label^ lblDiscount;
        Label^ lblTax;
        Label^ lblDivider3;
        Label^ lblGrandTotal;
        Label^ lblDivider4;
        Label^ lblPayMethod;
        Label^ lblAmountPaid;
        Label^ lblChange;
        Label^ lblThankYou;
        Button^ btnPrint;
        Button^ btnClose;
        int billNo;

    public:
        ReceiptForm(int billNo);

    private:
        void InitializeComponent();
        void LoadReceiptData();
        void btnPrint_Click(Object^ sender, EventArgs^ e);
        void btnClose_Click(Object^ sender, EventArgs^ e);
    private: System::Void ReceiptForm_Load(System::Object^ sender, System::EventArgs^ e) {
    }
    };
}