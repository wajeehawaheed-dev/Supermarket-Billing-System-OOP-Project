#include "ReceiptForm.h"

using namespace SUper;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Data::SqlClient;
using namespace System::Text;

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
    // 1. Get Bill + Cashier info
    System::Data::DataTable^ billDt = SBS::Database::ExecuteQuery(
        "SELECT b.BillNo, b.Date, b.Subtotal, b.Discount, b.Tax, b.Total, u.Username "
        "FROM Bills b LEFT JOIN Users u ON b.UserID = u.UserID "
        "WHERE b.BillNo = @b",
        gcnew SqlParameter("@b", billNo));

    if (billDt == nullptr || billDt->Rows->Count == 0) {
        MessageBox::Show("No bill found for Bill No: " + billNo);
        return;
    }

    System::Data::DataRow^ billRow = billDt->Rows[0];
    lblBillNo->Text = "Bill No: " + billRow["BillNo"]->ToString();
    lblDate->Text = "Date: " + billRow["Date"]->ToString();
    lblCashier->Text = "Cashier: " + billRow["Username"]->ToString();
    lblSubtotal->Text = "Subtotal:              Rs " + Convert::ToDouble(billRow["Subtotal"]).ToString("F2");
    lblDiscount->Text = "Discount:              Rs " + Convert::ToDouble(billRow["Discount"]).ToString("F2");
    lblTax->Text = "Tax:                   Rs " + Convert::ToDouble(billRow["Tax"]).ToString("F2");
    lblGrandTotal->Text = "GRAND TOTAL:           Rs " + Convert::ToDouble(billRow["Total"]).ToString("F2");

    // 2. Get items list
    System::Data::DataTable^ itemsDt = SBS::Database::ExecuteQuery(
        "SELECT p.Name, bi.Quantity, bi.Price, (bi.Quantity * bi.Price) AS LineTotal "
        "FROM BillItems bi LEFT JOIN Products p ON bi.ProductID = p.ProductID "
        "WHERE bi.BillNo = @b",
        gcnew SqlParameter("@b", billNo));

    System::Text::StringBuilder^ sb = gcnew System::Text::StringBuilder();
    sb->AppendLine("Item                 Qty   Price    Total");
    sb->AppendLine("----------------------------------------");

    if (itemsDt != nullptr) {
        for each (System::Data::DataRow ^ row in itemsDt->Rows) {
            String^ name = row["Name"]->ToString();
            // Truncate or pad name to 20 chars
            if (name->Length > 20) name = name->Substring(0, 20);
            else name = name->PadRight(20);

            String^ qty = Convert::ToInt32(row["Quantity"]).ToString()->PadLeft(4);
            String^ price = Convert::ToDouble(row["Price"]).ToString("F2")->PadLeft(8);
            String^ total = Convert::ToDouble(row["LineTotal"]).ToString("F2")->PadLeft(8);

            sb->AppendLine(name + " " + qty + " " + price + " " + total);
        }
    }
    lblItems->Text = sb->ToString();

    // 3. Get Payment info
    System::Data::DataTable^ payDt = SBS::Database::ExecuteQuery(
        "SELECT Method, AmountPaid, ChangeAmount FROM Payments WHERE BillNo = @b",
        gcnew SqlParameter("@b", billNo));

    if (payDt != nullptr && payDt->Rows->Count > 0) {
        System::Data::DataRow^ payRow = payDt->Rows[0];
        String^ method = payRow["Method"]->ToString();
        lblPayMethod->Text = "Payment Method:        " + method;
        lblAmountPaid->Text = "Amount Paid:           Rs " + Convert::ToDouble(payRow["AmountPaid"]).ToString("F2");

        if (method == "Card") {
            lblChange->Visible = false;
        }
        else {
            lblChange->Text = "Change:                Rs " + Convert::ToDouble(payRow["ChangeAmount"]).ToString("F2");
        }
    }
}

void ReceiptForm::btnPrint_Click(Object^ sender, EventArgs^ e) {
    MessageBox::Show("Printing receipt...");
}

void ReceiptForm::btnClose_Click(Object^ sender, EventArgs^ e) {
    this->Close();
}