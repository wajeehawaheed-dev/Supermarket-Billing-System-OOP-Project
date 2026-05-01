#include "ReceiptForm.h"

using namespace SUper;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Data::SqlClient;

ReceiptForm::ReceiptForm(int billNo) {
    this->billNo = billNo;
    InitializeComponent();
    LoadReceiptData();
}

void ReceiptForm::InitializeComponent() {
    this->Text = "Receipt";
    this->Size = System::Drawing::Size(420, 700);
    this->StartPosition = FormStartPosition::CenterScreen;
    this->BackColor = Color::FromArgb(240, 255, 240);

    // Header Panel
    pnlHeader = gcnew Panel();
    pnlHeader->Location = System::Drawing::Point(0, 0);
    pnlHeader->Size = System::Drawing::Size(420, 100);
    pnlHeader->BackColor = Color::FromArgb(34, 139, 34);

    lblStoreName = gcnew Label();
    lblStoreName->Text = "SUPERMARKET";
    lblStoreName->Font = gcnew System::Drawing::Font("Georgia", 20, FontStyle::Bold);
    lblStoreName->ForeColor = Color::White;
    lblStoreName->Location = System::Drawing::Point(0, 15);
    lblStoreName->Size = System::Drawing::Size(420, 40);
    lblStoreName->TextAlign = ContentAlignment::MiddleCenter;

    lblReceipt = gcnew Label();
    lblReceipt->Text = "OFFICIAL RECEIPT";
    lblReceipt->Font = gcnew System::Drawing::Font("Georgia", 10, FontStyle::Italic);
    lblReceipt->ForeColor = Color::FromArgb(200, 255, 200);
    lblReceipt->Location = System::Drawing::Point(0, 60);
    lblReceipt->Size = System::Drawing::Size(420, 25);
    lblReceipt->TextAlign = ContentAlignment::MiddleCenter;

    pnlHeader->Controls->Add(lblStoreName);
    pnlHeader->Controls->Add(lblReceipt);

    // Body Panel
    pnlBody = gcnew Panel();
    pnlBody->Location = System::Drawing::Point(10, 110);
    pnlBody->Size = System::Drawing::Size(400, 480);
    pnlBody->BackColor = Color::White;
    pnlBody->BorderStyle = BorderStyle::FixedSingle;

    lblBillNo = gcnew Label();
    lblBillNo->Text = "Bill No: --";
    lblBillNo->Font = gcnew System::Drawing::Font("Courier New", 9);
    lblBillNo->Location = System::Drawing::Point(15, 15);
    lblBillNo->Size = System::Drawing::Size(180, 20);
    lblBillNo->ForeColor = Color::FromArgb(34, 100, 34);

    lblDate = gcnew Label();
    lblDate->Text = "Date: --";
    lblDate->Font = gcnew System::Drawing::Font("Courier New", 9);
    lblDate->Location = System::Drawing::Point(200, 15);
    lblDate->Size = System::Drawing::Size(180, 20);
    lblDate->ForeColor = Color::FromArgb(34, 100, 34);

    lblCashier = gcnew Label();
    lblCashier->Text = "Cashier: --";
    lblCashier->Font = gcnew System::Drawing::Font("Courier New", 9);
    lblCashier->Location = System::Drawing::Point(15, 38);
    lblCashier->Size = System::Drawing::Size(370, 20);
    lblCashier->ForeColor = Color::FromArgb(34, 100, 34);

    lblDivider1 = gcnew Label();
    lblDivider1->Text = "----------------------------------------";
    lblDivider1->Font = gcnew System::Drawing::Font("Courier New", 9);
    lblDivider1->Location = System::Drawing::Point(15, 62);
    lblDivider1->Size = System::Drawing::Size(370, 20);
    lblDivider1->ForeColor = Color::FromArgb(34, 139, 34);

    lblItems = gcnew Label();
    lblItems->Text = "Item                 Qty   Price    Total\r\n----------------------------------------";
    lblItems->Font = gcnew System::Drawing::Font("Courier New", 9, FontStyle::Bold);
    lblItems->Location = System::Drawing::Point(15, 85);
    lblItems->Size = System::Drawing::Size(370, 200);
    lblItems->ForeColor = Color::FromArgb(20, 80, 20);
    lblItems->AutoSize = false;

    lblDivider2 = gcnew Label();
    lblDivider2->Text = "----------------------------------------";
    lblDivider2->Font = gcnew System::Drawing::Font("Courier New", 9);
    lblDivider2->Location = System::Drawing::Point(15, 290);
    lblDivider2->Size = System::Drawing::Size(370, 20);
    lblDivider2->ForeColor = Color::FromArgb(34, 139, 34);

    lblSubtotal = gcnew Label();
    lblSubtotal->Text = "Subtotal:              Rs --";
    lblSubtotal->Font = gcnew System::Drawing::Font("Courier New", 9);
    lblSubtotal->Location = System::Drawing::Point(15, 315);
    lblSubtotal->Size = System::Drawing::Size(370, 20);
    lblSubtotal->ForeColor = Color::FromArgb(34, 100, 34);

    lblDiscount = gcnew Label();
    lblDiscount->Text = "Discount:              Rs --";
    lblDiscount->Font = gcnew System::Drawing::Font("Courier New", 9);
    lblDiscount->Location = System::Drawing::Point(15, 338);
    lblDiscount->Size = System::Drawing::Size(370, 20);
    lblDiscount->ForeColor = Color::FromArgb(34, 100, 34);

    lblTax = gcnew Label();
    lblTax->Text = "Tax:                   Rs --";
    lblTax->Font = gcnew System::Drawing::Font("Courier New", 9);
    lblTax->Location = System::Drawing::Point(15, 361);
    lblTax->Size = System::Drawing::Size(370, 20);
    lblTax->ForeColor = Color::FromArgb(34, 100, 34);

    lblDivider3 = gcnew Label();
    lblDivider3->Text = "----------------------------------------";
    lblDivider3->Font = gcnew System::Drawing::Font("Courier New", 9);
    lblDivider3->Location = System::Drawing::Point(15, 384);
    lblDivider3->Size = System::Drawing::Size(370, 20);
    lblDivider3->ForeColor = Color::FromArgb(34, 139, 34);

    lblGrandTotal = gcnew Label();
    lblGrandTotal->Text = "GRAND TOTAL:           Rs --";
    lblGrandTotal->Font = gcnew System::Drawing::Font("Courier New", 11, FontStyle::Bold);
    lblGrandTotal->Location = System::Drawing::Point(15, 407);
    lblGrandTotal->Size = System::Drawing::Size(370, 25);
    lblGrandTotal->ForeColor = Color::FromArgb(0, 100, 0);

    lblDivider4 = gcnew Label();
    lblDivider4->Text = "----------------------------------------";
    lblDivider4->Font = gcnew System::Drawing::Font("Courier New", 9);
    lblDivider4->Location = System::Drawing::Point(15, 435);
    lblDivider4->Size = System::Drawing::Size(370, 20);
    lblDivider4->ForeColor = Color::FromArgb(34, 139, 34);

    lblPayMethod = gcnew Label();
    lblPayMethod->Text = "Payment Method:        --";
    lblPayMethod->Font = gcnew System::Drawing::Font("Courier New", 9);
    lblPayMethod->Location = System::Drawing::Point(15, 458);
    lblPayMethod->Size = System::Drawing::Size(370, 20);
    lblPayMethod->ForeColor = Color::FromArgb(34, 100, 34);

    lblAmountPaid = gcnew Label();
    lblAmountPaid->Text = "Amount Paid:           Rs --";
    lblAmountPaid->Font = gcnew System::Drawing::Font("Courier New", 9);
    lblAmountPaid->Location = System::Drawing::Point(15, 481);
    lblAmountPaid->Size = System::Drawing::Size(370, 20);
    lblAmountPaid->ForeColor = Color::FromArgb(34, 100, 34);

    lblChange = gcnew Label();
    lblChange->Text = "Change:                Rs --";
    lblChange->Font = gcnew System::Drawing::Font("Courier New", 9);
    lblChange->Location = System::Drawing::Point(15, 504);
    lblChange->Size = System::Drawing::Size(370, 20);
    lblChange->ForeColor = Color::FromArgb(34, 100, 34);

    pnlBody->Controls->Add(lblBillNo);
    pnlBody->Controls->Add(lblDate);
    pnlBody->Controls->Add(lblCashier);
    pnlBody->Controls->Add(lblDivider1);
    pnlBody->Controls->Add(lblItems);
    pnlBody->Controls->Add(lblDivider2);
    pnlBody->Controls->Add(lblSubtotal);
    pnlBody->Controls->Add(lblDiscount);
    pnlBody->Controls->Add(lblTax);
    pnlBody->Controls->Add(lblDivider3);
    pnlBody->Controls->Add(lblGrandTotal);
    pnlBody->Controls->Add(lblDivider4);
    pnlBody->Controls->Add(lblPayMethod);
    pnlBody->Controls->Add(lblAmountPaid);
    pnlBody->Controls->Add(lblChange);

    lblThankYou = gcnew Label();
    lblThankYou->Text = "Thank you for shopping with us!";
    lblThankYou->Font = gcnew System::Drawing::Font("Georgia", 10, FontStyle::Italic);
    lblThankYou->ForeColor = Color::FromArgb(34, 139, 34);
    lblThankYou->Location = System::Drawing::Point(0, 600);
    lblThankYou->Size = System::Drawing::Size(420, 25);
    lblThankYou->TextAlign = ContentAlignment::MiddleCenter;

    btnPrint = gcnew Button();
    btnPrint->Text = "Print";
    btnPrint->Location = System::Drawing::Point(240, 630);
    btnPrint->Size = System::Drawing::Size(100, 35);
    btnPrint->BackColor = Color::FromArgb(34, 139, 34);
    btnPrint->ForeColor = Color::White;
    btnPrint->FlatStyle = FlatStyle::Flat;
    btnPrint->Click += gcnew EventHandler(this, &ReceiptForm::btnPrint_Click);

    btnClose = gcnew Button();
    btnClose->Text = "Close";
    btnClose->Location = System::Drawing::Point(60, 630);
    btnClose->Size = System::Drawing::Size(100, 35);
    btnClose->BackColor = Color::FromArgb(200, 255, 200);
    btnClose->ForeColor = Color::FromArgb(34, 100, 34);
    btnClose->FlatStyle = FlatStyle::Flat;
    btnClose->Click += gcnew EventHandler(this, &ReceiptForm::btnClose_Click);

    this->Controls->Add(pnlHeader);
    this->Controls->Add(pnlBody);
    this->Controls->Add(lblThankYou);
    this->Controls->Add(btnPrint);
    this->Controls->Add(btnClose);
}

void ReceiptForm::LoadReceiptData() {
    System::Data::DataTable^ dt = SBS::Database::ExecuteQuery(
        "SELECT * FROM Payments WHERE BillNo = @b",
        gcnew SqlParameter("@b", billNo));

    if (dt->Rows->Count > 0) {
        System::Data::DataRow^ row = dt->Rows[0];
        lblBillNo->Text = "Bill No: " + row["BillNo"]->ToString();
        lblDate->Text = "Date: " + row["PayDate"]->ToString();
        lblPayMethod->Text = "Payment Method:        " + row["Method"]->ToString();
        lblAmountPaid->Text = "Amount Paid:           Rs " + row["AmountPaid"]->ToString();
        lblChange->Text = "Change:                Rs " + row["ChangeAmount"]->ToString();
        lblGrandTotal->Text = "GRAND TOTAL:           Rs " + row["AmountPaid"]->ToString();

        if (row["Method"]->ToString() == "Card") {
            lblChange->Visible = false;
        }
    }
    else {
        MessageBox::Show("No receipt found for Bill No: " + billNo);
    }
}

void ReceiptForm::btnPrint_Click(Object^ sender, EventArgs^ e) {
    MessageBox::Show("Printing receipt...");
}

void ReceiptForm::btnClose_Click(Object^ sender, EventArgs^ e) {
    this->Close();
}