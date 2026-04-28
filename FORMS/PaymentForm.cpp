#include "PaymentForm.h"

using namespace SBS;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Data::SqlClient;

PaymentForm::PaymentForm(int billNo, double totalBill) {
    this->billNo = billNo;
    this->totalBill = totalBill;
    InitializeComponent();
}

void PaymentForm::InitializeComponent() {
    this->Text = "Payment";
    this->Size = System::Drawing::Size(450, 500);
    this->StartPosition = FormStartPosition::CenterScreen;

    lblTitle = gcnew Label();
    lblTitle->Text = "PAYMENT";
    lblTitle->Font = gcnew System::Drawing::Font("Arial", 16, FontStyle::Bold);
    lblTitle->Location = System::Drawing::Point(150, 20);
    lblTitle->Size = System::Drawing::Size(200, 35);

    lblBillNo = gcnew Label();
    lblBillNo->Text = "Bill No: " + billNo.ToString();
    lblBillNo->Location = System::Drawing::Point(30, 70);
    lblBillNo->Size = System::Drawing::Size(200, 25);

    lblTotal = gcnew Label();
    lblTotal->Text = "Total: Rs " + totalBill.ToString("F2");
    lblTotal->Font = gcnew System::Drawing::Font("Arial", 11, FontStyle::Bold);
    lblTotal->Location = System::Drawing::Point(30, 100);
    lblTotal->Size = System::Drawing::Size(200, 25);

    rbCash = gcnew RadioButton();
    rbCash->Text = "Cash";
    rbCash->Location = System::Drawing::Point(30, 140);
    rbCash->Checked = true;
    rbCash->CheckedChanged += gcnew EventHandler(this, &PaymentForm::rbCash_Changed);

    rbCard = gcnew RadioButton();
    rbCard->Text = "Card";
    rbCard->Location = System::Drawing::Point(120, 140);
    rbCard->CheckedChanged += gcnew EventHandler(this, &PaymentForm::rbCard_Changed);

    lblCashAmount = gcnew Label();
    lblCashAmount->Text = "Cash Amount:";
    lblCashAmount->Location = System::Drawing::Point(30, 190);
    lblCashAmount->Size = System::Drawing::Size(120, 25);

    txtCashAmount = gcnew TextBox();
    txtCashAmount->Location = System::Drawing::Point(160, 190);
    txtCashAmount->Size = System::Drawing::Size(200, 25);

    lblCardHolder = gcnew Label();
    lblCardHolder->Text = "Card Holder:";
    lblCardHolder->Location = System::Drawing::Point(30, 190);
    lblCardHolder->Size = System::Drawing::Size(120, 25);
    lblCardHolder->Visible = false;

    txtCardHolder = gcnew TextBox();
    txtCardHolder->Location = System::Drawing::Point(160, 190);
    txtCardHolder->Size = System::Drawing::Size(200, 25);
    txtCardHolder->Visible = false;

    lblCardNo = gcnew Label();
    lblCardNo->Text = "Card Number:";
    lblCardNo->Location = System::Drawing::Point(30, 230);
    lblCardNo->Size = System::Drawing::Size(120, 25);
    lblCardNo->Visible = false;

    txtCardNo = gcnew TextBox();
    txtCardNo->Location = System::Drawing::Point(160, 230);
    txtCardNo->Size = System::Drawing::Size(200, 25);
    txtCardNo->Visible = false;

    lblExpiry = gcnew Label();
    lblExpiry->Text = "Expiry (MM/YY):";
    lblExpiry->Location = System::Drawing::Point(30, 270);
    lblExpiry->Size = System::Drawing::Size(120, 25);
    lblExpiry->Visible = false;

    txtExpiry = gcnew TextBox();
    txtExpiry->Location = System::Drawing::Point(160, 270);
    txtExpiry->Size = System::Drawing::Size(200, 25);
    txtExpiry->Visible = false;

    lblCVV = gcnew Label();
    lblCVV->Text = "CVV:";
    lblCVV->Location = System::Drawing::Point(30, 310);
    lblCVV->Size = System::Drawing::Size(120, 25);
    lblCVV->Visible = false;

    txtCVV = gcnew TextBox();
    txtCVV->Location = System::Drawing::Point(160, 310);
    txtCVV->Size = System::Drawing::Size(200, 25);
    txtCVV->Visible = false;

    btnPay = gcnew Button();
    btnPay->Text = "Pay Now";
    btnPay->Location = System::Drawing::Point(240, 400);
    btnPay->Size = System::Drawing::Size(100, 35);
    btnPay->Click += gcnew EventHandler(this, &PaymentForm::btnPay_Click);

    btnCancel = gcnew Button();
    btnCancel->Text = "Cancel";
    btnCancel->Location = System::Drawing::Point(30, 400);
    btnCancel->Size = System::Drawing::Size(100, 35);
    btnCancel->Click += gcnew EventHandler(this, &PaymentForm::btnCancel_Click);

    this->Controls->Add(lblTitle);
    this->Controls->Add(lblBillNo);
    this->Controls->Add(lblTotal);
    this->Controls->Add(rbCash);
    this->Controls->Add(rbCard);
    this->Controls->Add(lblCashAmount);
    this->Controls->Add(txtCashAmount);
    this->Controls->Add(lblCardHolder);
    this->Controls->Add(txtCardHolder);
    this->Controls->Add(lblCardNo);
    this->Controls->Add(txtCardNo);
    this->Controls->Add(lblExpiry);
    this->Controls->Add(txtExpiry);
    this->Controls->Add(lblCVV);
    this->Controls->Add(txtCVV);
    this->Controls->Add(btnPay);
    this->Controls->Add(btnCancel);
}

void PaymentForm::rbCash_Changed(Object^ sender, EventArgs^ e) {
    lblCashAmount->Visible = true;
    txtCashAmount->Visible = true;
    lblCardHolder->Visible = false;
    txtCardHolder->Visible = false;
    lblCardNo->Visible = false;
    txtCardNo->Visible = false;
    lblExpiry->Visible = false;
    txtExpiry->Visible = false;
    lblCVV->Visible = false;
    txtCVV->Visible = false;
}

void PaymentForm::rbCard_Changed(Object^ sender, EventArgs^ e) {
    lblCashAmount->Visible = false;
    txtCashAmount->Visible = false;
    lblCardHolder->Visible = true;
    txtCardHolder->Visible = true;
    lblCardNo->Visible = true;
    txtCardNo->Visible = true;
    lblExpiry->Visible = true;
    txtExpiry->Visible = true;
    lblCVV->Visible = true;
    txtCVV->Visible = true;
}

void PaymentForm::btnPay_Click(Object^ sender, EventArgs^ e) {
    if (rbCash->Checked) {
        double cashGiven = Convert::ToDouble(txtCashAmount->Text);
        if (cashGiven < totalBill) {
            MessageBox::Show("Insufficient amount!");
            return;
        }
        double change = cashGiven - totalBill;
        SBS::Database::ExecuteNonQuery(
            "INSERT INTO Payments (BillNo, Method, AmountPaid, ChangeAmount) VALUES (@b, @m, @a, @c)",
            gcnew SqlParameter("@b", billNo),
            gcnew SqlParameter("@m", "Cash"),
            gcnew SqlParameter("@a", cashGiven),
            gcnew SqlParameter("@c", change));
        SBS::Database::ExecuteNonQuery(
            "UPDATE Payments SET Status = @s WHERE BillNo = @b",
            gcnew SqlParameter("@s", "Approved"),
            gcnew SqlParameter("@b", billNo));
        MessageBox::Show("Payment Successful! Change: Rs " + change.ToString("F2"));
    }
    else {
        int cardLen = txtCardNo->Text->Length;
        int cvvLen = txtCVV->Text->Length;

        if (cardLen != 16) {
            MessageBox::Show("Card number must be 16 digits!");
            return;
        }
        if (cvvLen != 3) {
            MessageBox::Show("CVV must be 3 digits!");
            return;
        }
        SBS::Database::ExecuteNonQuery(
            "INSERT INTO Payments (BillNo, Method, AmountPaid, ChangeAmount) VALUES (@b, @m, @a, @c)",
            gcnew SqlParameter("@b", billNo),
            gcnew SqlParameter("@m", "Card"),
            gcnew SqlParameter("@a", totalBill),
            gcnew SqlParameter("@c", 0));
        SBS::Database::ExecuteNonQuery(
            "UPDATE Payments SET Status = @s WHERE BillNo = @b",
            gcnew SqlParameter("@s", "Approved"),
            gcnew SqlParameter("@b", billNo));
        MessageBox::Show("Card Payment Successful!");
    }
}

void PaymentForm::btnCancel_Click(Object^ sender, EventArgs^ e) {
    SBS::Database::ExecuteNonQuery(
        "UPDATE Payments SET Status = @s WHERE BillNo = @b",
        gcnew SqlParameter("@s", "Cancelled"),
        gcnew SqlParameter("@b", billNo));
    MessageBox::Show("Payment Cancelled! Refund will be processed.");
    this->Close();
}