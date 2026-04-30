#include "PaymentForm.h"
#include "ReceiptForm.h" 
using namespace SBS;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Data::SqlClient;

PaymentForm::PaymentForm(int billNo, double totalBill) {
    this->billNo = billNo;
    this->totalBill = totalBill;
    this->failedAttempts = 0;
    this->formLocked = false;
    this->secondsRemaining = 60;
    InitializeComponent();
}


bool PaymentForm::IsValidExpiryDate(int month, int year) {
    // month must be 1-12
    if (month < 1 || month > 12) return false;
    DateTime now = DateTime::Now;
    int currentYear = now.Year % 100;
    if (year > currentYear + 10) return false;
    return true;
}

void PaymentForm::InitializeComponent() {
    // Colors 
    Color darkGreen = Color::FromArgb(27, 94, 32);
    Color medGreen = Color::FromArgb(46, 125, 50);
    Color lightGreen = Color::FromArgb(232, 245, 233);
    Color accentGreen = Color::FromArgb(76, 175, 80);
    Color white = Color::White;

    this->SuspendLayout();
    this->Text = "Payment";
    this->Size = System::Drawing::Size(480, 640);
    this->StartPosition = FormStartPosition::CenterScreen;
    this->BackColor = lightGreen;
    this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
    this->MaximizeBox = false;

   
    pnlHeader = gcnew Panel();
    pnlHeader->Location = System::Drawing::Point(0, 0);
    pnlHeader->Size = System::Drawing::Size(480, 90);
    pnlHeader->BackColor = darkGreen;

    lblTitle = gcnew Label();
    lblTitle->Text = "PAYMENT";
    lblTitle->Font = gcnew System::Drawing::Font("Georgia", 20, FontStyle::Bold);
    lblTitle->ForeColor = white;
    lblTitle->Location = System::Drawing::Point(0, 10);
    lblTitle->Size = System::Drawing::Size(480, 40);
    lblTitle->TextAlign = ContentAlignment::MiddleCenter;
    lblTitle->BackColor = Color::Transparent;

    lblBillNo = gcnew Label();
    lblBillNo->Text = "Bill No: " + billNo.ToString();
    lblBillNo->Font = gcnew System::Drawing::Font("Courier New", 9);
    lblBillNo->ForeColor = Color::FromArgb(200, 255, 200);
    lblBillNo->Location = System::Drawing::Point(20, 58);
    lblBillNo->Size = System::Drawing::Size(200, 20);
    lblBillNo->BackColor = Color::Transparent;

    lblTotal = gcnew Label();
    lblTotal->Text = "Total: Rs " + totalBill.ToString("F2");
    lblTotal->Font = gcnew System::Drawing::Font("Courier New", 9, FontStyle::Bold);
    lblTotal->ForeColor = Color::FromArgb(200, 255, 200);
    lblTotal->Location = System::Drawing::Point(280, 58);
    lblTotal->Size = System::Drawing::Size(180, 20);
    lblTotal->TextAlign = ContentAlignment::MiddleRight;
    lblTotal->BackColor = Color::Transparent;

    pnlHeader->Controls->Add(lblTitle);
    pnlHeader->Controls->Add(lblBillNo);
    pnlHeader->Controls->Add(lblTotal);

    // ── Payment Method 
    pnlMethod = gcnew Panel();
    pnlMethod->Location = System::Drawing::Point(20, 105);
    pnlMethod->Size = System::Drawing::Size(440, 55);
    pnlMethod->BackColor = white;

    lblMethodTitle = gcnew Label();
    lblMethodTitle->Text = "Payment Method:";
    lblMethodTitle->Font = gcnew System::Drawing::Font("Georgia", 10, FontStyle::Bold);
    lblMethodTitle->ForeColor = darkGreen;
    lblMethodTitle->Location = System::Drawing::Point(15, 15);
    lblMethodTitle->Size = System::Drawing::Size(150, 25);
    lblMethodTitle->BackColor = Color::Transparent;

    rbCash = gcnew RadioButton();
    rbCash->Text = "Cash";
    rbCash->Font = gcnew System::Drawing::Font("Georgia", 10);
    rbCash->ForeColor = darkGreen;
    rbCash->Location = System::Drawing::Point(180, 15);
    rbCash->Size = System::Drawing::Size(80, 25);
    rbCash->Checked = true;
    rbCash->BackColor = Color::Transparent;
    rbCash->CheckedChanged += gcnew EventHandler(this, &PaymentForm::rbCash_Changed);

    rbCard = gcnew RadioButton();
    rbCard->Text = "Card";
    rbCard->Font = gcnew System::Drawing::Font("Georgia", 10);
    rbCard->ForeColor = darkGreen;
    rbCard->Location = System::Drawing::Point(290, 15);
    rbCard->Size = System::Drawing::Size(80, 25);
    rbCard->BackColor = Color::Transparent;
    rbCard->CheckedChanged += gcnew EventHandler(this, &PaymentForm::rbCard_Changed);

    pnlMethod->Controls->Add(lblMethodTitle);
    pnlMethod->Controls->Add(rbCash);
    pnlMethod->Controls->Add(rbCard);

    // ── Cash Panel 
    pnlCash = gcnew Panel();
    pnlCash->Location = System::Drawing::Point(20, 170);
    pnlCash->Size = System::Drawing::Size(440, 110);
    pnlCash->BackColor = white;

    lblCustName = gcnew Label();
    lblCustName->Text = "Customer Name:";
    lblCustName->Font = gcnew System::Drawing::Font("Georgia", 10);
    lblCustName->ForeColor = darkGreen;
    lblCustName->Location = System::Drawing::Point(15, 15);
    lblCustName->Size = System::Drawing::Size(155, 25);
    lblCustName->BackColor = Color::Transparent;

    txtCustName = gcnew TextBox();
    txtCustName->Location = System::Drawing::Point(180, 15);
    txtCustName->Size = System::Drawing::Size(230, 25);
    txtCustName->Font = gcnew System::Drawing::Font("Courier New", 10);

    lblCashAmount = gcnew Label();
    lblCashAmount->Text = "Cash Amount (Rs):";
    lblCashAmount->Font = gcnew System::Drawing::Font("Georgia", 10);
    lblCashAmount->ForeColor = darkGreen;
    lblCashAmount->Location = System::Drawing::Point(15, 55);
    lblCashAmount->Size = System::Drawing::Size(155, 25);
    lblCashAmount->BackColor = Color::Transparent;

    txtCashAmount = gcnew TextBox();
    txtCashAmount->Location = System::Drawing::Point(180, 55);
    txtCashAmount->Size = System::Drawing::Size(230, 25);
    txtCashAmount->Font = gcnew System::Drawing::Font("Courier New", 10);

    pnlCash->Controls->Add(lblCustName);
    pnlCash->Controls->Add(txtCustName);
    pnlCash->Controls->Add(lblCashAmount);
    pnlCash->Controls->Add(txtCashAmount);

    // ── Card Panel 
    pnlCard = gcnew Panel();
    pnlCard->Location = System::Drawing::Point(20, 170);
    pnlCard->Size = System::Drawing::Size(440, 220);
    pnlCard->BackColor = white;
    pnlCard->Visible = false;

    lblCardHolder = gcnew Label();
    lblCardHolder->Text = "Card Holder:";
    lblCardHolder->Font = gcnew System::Drawing::Font("Georgia", 10);
    lblCardHolder->ForeColor = darkGreen;
    lblCardHolder->Location = System::Drawing::Point(15, 15);
    lblCardHolder->Size = System::Drawing::Size(155, 25);
    lblCardHolder->BackColor = Color::Transparent;

    txtCardHolder = gcnew TextBox();
    txtCardHolder->Location = System::Drawing::Point(180, 15);
    txtCardHolder->Size = System::Drawing::Size(230, 25);
    txtCardHolder->Font = gcnew System::Drawing::Font("Courier New", 10);

    lblCardNo = gcnew Label();
    lblCardNo->Text = "Card Number:";
    lblCardNo->Font = gcnew System::Drawing::Font("Georgia", 10);
    lblCardNo->ForeColor = darkGreen;
    lblCardNo->Location = System::Drawing::Point(15, 55);
    lblCardNo->Size = System::Drawing::Size(155, 25);
    lblCardNo->BackColor = Color::Transparent;

    txtCardNo = gcnew TextBox();
    txtCardNo->Location = System::Drawing::Point(180, 55);
    txtCardNo->Size = System::Drawing::Size(230, 25);
    txtCardNo->Font = gcnew System::Drawing::Font("Courier New", 10);
    txtCardNo->MaxLength = 16;

    lblExpiry = gcnew Label();
    lblExpiry->Text = "Expiry (MM/YY):";
    lblExpiry->Font = gcnew System::Drawing::Font("Georgia", 10);
    lblExpiry->ForeColor = darkGreen;
    lblExpiry->Location = System::Drawing::Point(15, 95);
    lblExpiry->Size = System::Drawing::Size(155, 25);
    lblExpiry->BackColor = Color::Transparent;

    txtExpiry = gcnew TextBox();
    txtExpiry->Location = System::Drawing::Point(180, 95);
    txtExpiry->Size = System::Drawing::Size(100, 25);
    txtExpiry->Font = gcnew System::Drawing::Font("Courier New", 10);
    txtExpiry->MaxLength = 5;

    lblCVV = gcnew Label();
    lblCVV->Text = "CVV:";
    lblCVV->Font = gcnew System::Drawing::Font("Georgia", 10);
    lblCVV->ForeColor = darkGreen;
    lblCVV->Location = System::Drawing::Point(15, 135);
    lblCVV->Size = System::Drawing::Size(155, 25);
    lblCVV->BackColor = Color::Transparent;

    txtCVV = gcnew TextBox();
    txtCVV->Location = System::Drawing::Point(180, 135);
    txtCVV->Size = System::Drawing::Size(80, 25);
    txtCVV->Font = gcnew System::Drawing::Font("Courier New", 10);
    txtCVV->MaxLength = 3;
    txtCVV->PasswordChar = '*';

    pnlCard->Controls->Add(lblCardHolder);
    pnlCard->Controls->Add(txtCardHolder);
    pnlCard->Controls->Add(lblCardNo);
    pnlCard->Controls->Add(txtCardNo);
    pnlCard->Controls->Add(lblExpiry);
    pnlCard->Controls->Add(txtExpiry);
    pnlCard->Controls->Add(lblCVV);
    pnlCard->Controls->Add(txtCVV);

    // ── Lock Message
    lblLockMsg = gcnew Label();
    lblLockMsg->Text = "";
    lblLockMsg->Font = gcnew System::Drawing::Font("Georgia", 9, FontStyle::Bold);
    lblLockMsg->ForeColor = Color::Red;
    lblLockMsg->Location = System::Drawing::Point(20, 415);
    lblLockMsg->Size = System::Drawing::Size(440, 25);
    lblLockMsg->TextAlign = ContentAlignment::MiddleCenter;
    lblLockMsg->BackColor = Color::Transparent;
    lblLockMsg->Visible = false;

    btnPay = gcnew Button();
    btnPay->Text = "Proceed to Payment";
    btnPay->Font = gcnew System::Drawing::Font("Georgia", 10, FontStyle::Bold);
    btnPay->Location = System::Drawing::Point(270, 470);
    btnPay->Size = System::Drawing::Size(170, 40);
    btnPay->BackColor = darkGreen;
    btnPay->ForeColor = white;
    btnPay->FlatStyle = FlatStyle::Flat;
    btnPay->FlatAppearance->BorderSize = 0;
    btnPay->Click += gcnew EventHandler(this, &PaymentForm::btnPay_Click);

    btnCancel = gcnew Button();
    btnCancel->Text = "Back to Cart";
    btnCancel->Font = gcnew System::Drawing::Font("Georgia", 10);
    btnCancel->Location = System::Drawing::Point(40, 470);
    btnCancel->Size = System::Drawing::Size(140, 40);
    btnCancel->BackColor = Color::FromArgb(198, 40, 40);
    btnCancel->ForeColor = white;
    btnCancel->FlatStyle = FlatStyle::Flat;
    btnCancel->FlatAppearance->BorderSize = 0;
    btnCancel->Click += gcnew EventHandler(this, &PaymentForm::btnCancel_Click);

    // ── Timer ─
    unlockTimer = gcnew System::Windows::Forms::Timer();
    unlockTimer->Interval = 1000;
    unlockTimer->Tick += gcnew EventHandler(this, &PaymentForm::unlockTimer_Tick);

   
    this->Controls->Add(pnlHeader);
    this->Controls->Add(pnlMethod);
    this->Controls->Add(pnlCash);
    this->Controls->Add(pnlCard);
    this->Controls->Add(lblLockMsg);
    this->Controls->Add(btnPay);
    this->Controls->Add(btnCancel);

    this->Load += gcnew System::EventHandler(this, &PaymentForm::PaymentForm_Load);
    this->ResumeLayout(false);
}

//  1-min countdown then unlock 
void PaymentForm::unlockTimer_Tick(Object^ sender, EventArgs^ e) {
    secondsRemaining--;
    if (secondsRemaining <= 0) {
        unlockTimer->Stop();
        formLocked = false;
        failedAttempts = 0;
        secondsRemaining = 60;
        btnPay->Enabled = true;
        lblLockMsg->Visible = false;
        MessageBox::Show("Payment unlocked! You can try again.", "Unlocked",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
    else {
        lblLockMsg->Text = "Locked! Unlocks in " + secondsRemaining.ToString() + " second(s)...";
    }
}

void PaymentForm::rbCash_Changed(Object^ sender, EventArgs^ e) {
    if (!rbCash->Checked) return;
    pnlCash->Visible = true;
    pnlCard->Visible = false;
}

void PaymentForm::rbCard_Changed(Object^ sender, EventArgs^ e) {
    if (!rbCard->Checked) return;
    pnlCash->Visible = false;
    pnlCard->Visible = true;
}

void PaymentForm::btnPay_Click(Object^ sender, EventArgs^ e) {
    if (formLocked) {
        MessageBox::Show("Payment is locked! Please wait " + secondsRemaining.ToString() + " second(s).",
            "Locked", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return;
    }

    if (rbCash->Checked) {
        // CASH VALIDATION 
        String^ errors = "";

        String^ custName = txtCustName->Text->Trim();
        if (custName->Length == 0) {
            errors += "- Customer Name is required.\n";
        }
        else {
            bool hasInvalidChar = false;
            for each(Char c in custName) {
                if (!Char::IsLetter(c) && c != ' ') { hasInvalidChar = true; break; }
            }
            if (hasInvalidChar)
                errors += "- Customer Name must contain letters only (no numbers or symbols).\n";
        }

        double cashGiven = 0.0;
        bool amountOk = false;
        try {
            cashGiven = Convert::ToDouble(txtCashAmount->Text);
            amountOk = true;
        }
        catch (...) {
            errors += "- Please enter a valid cash amount.\n";
        }
        if (amountOk && cashGiven < totalBill)
            errors += "- Insufficient amount! You need at least Rs " + totalBill.ToString("F2") + ".\n";

        if (errors->Length > 0) {
            MessageBox::Show("Please fix the following errors:\n\n" + errors,
                "Validation Errors", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        double change = cashGiven - totalBill;
        SBS::Database::ExecuteNonQuery(
            "INSERT INTO Payments (BillNo, Method, CustomerName, AmountPaid, ChangeAmount) VALUES (@b, @m, @n, @a, @c)",
            gcnew SqlParameter("@b", billNo),
            gcnew SqlParameter("@m", "Cash"),
            gcnew SqlParameter("@n", custName),
            gcnew SqlParameter("@a", cashGiven),
            gcnew SqlParameter("@c", change));
        SBS::Database::ExecuteNonQuery(
            "UPDATE Payments SET Status = @s WHERE BillNo = @b",
            gcnew SqlParameter("@s", "Approved"),
            gcnew SqlParameter("@b", billNo));
        MessageBox::Show("Payment Successful!\nCustomer: " + custName + "\nChange: Rs " + change.ToString("F2"),
            "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
        ReceiptForm^ receipt = gcnew ReceiptForm(billNo);
        receipt->ShowDialog();
        this->Close();
    }
    else {
        // CARD VALIDATION 
        String^ errors = "";

        // Card Holder Check
        String^ holderName = txtCardHolder->Text->Trim();
        if (holderName->Length == 0) {
            errors += "- Card Holder name is required.\n";
        }
        else {
            bool hasInvalidChar = false;
            for each(Char c in holderName) {
                if (!Char::IsLetter(c) && c != ' ') { hasInvalidChar = true; break; }
            }
            if (hasInvalidChar)
                errors += "- Card Holder name must contain letters only (no numbers or symbols).\n";
        }

        // Card Number check
        if (txtCardNo->Text->Length != 16) {
            errors += "- Card number must be exactly 16 digits.\n";
        }
        else {
            bool allDigits = true;
            for each(Char c in txtCardNo->Text) {
                if (!Char::IsDigit(c)) { allDigits = false; break; }
            }
            if (!allDigits) errors += "- Card number must contain digits only.\n";
        }

        // CVV: 3 digits
        if (txtCVV->Text->Length != 3) {
            errors += "- CVV must be exactly 3 digits.\n";
        }
        else {
            bool allDigits = true;
            for each(Char c in txtCVV->Text) {
                if (!Char::IsDigit(c)) { allDigits = false; break; }
            }
            if (!allDigits) errors += "- CVV must contain digits only.\n";
        }

        // Expiry check 
        String^ expiry = txtExpiry->Text->Trim();
        if (expiry->Length != 5 || expiry[2] != '/') {
            errors += "- Invalid expiry format! Use MM/YY (e.g. 03/28).\n";
        }
        else {
            int month = 0, year = 0;
            bool parseOk = Int32::TryParse(expiry->Substring(0, 2), month) &&
                Int32::TryParse(expiry->Substring(3, 2), year);
            if (!parseOk) {
                errors += "- Expiry date must contain numbers only.\n";
            }
            else if (month < 1 || month > 12) {
               //month check
                errors += "- Expiry month must be between 01 and 12.\n";
            }
            else if (!IsValidExpiryDate(month, year)) {
                //year check
                errors += "- Expiry year is unrealistic. Cards expire within 10 years.\n";
            }
            else {
                DateTime now = DateTime::Now;
                int currentMonth = now.Month;
                int currentYear = now.Year % 100;
                // FIX: card expired check
                if (year < currentYear || (year == currentYear && month < currentMonth)) {
                    errors += "- Card is expired! (Entered: " + expiry + ")\n";
                }
            }
        }

        if (errors->Length > 0) {
            failedAttempts++;
            int remaining = 3 - failedAttempts;
            String^ message = "Please fix the following errors:\n\n" + errors;
            if (remaining > 0)
                message += "\nAttempts remaining: " + remaining.ToString();
            else {
                formLocked = true;
                btnPay->Enabled = false;
                secondsRemaining = 60;
                lblLockMsg->Text = "Locked! Unlocks in 60 second(s)...";
                lblLockMsg->Visible = true;
                unlockTimer->Start();
                message += "\nNo attempts remaining. Payment locked for 1 minute!";
            }
            MessageBox::Show(message, "Validation Errors",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        SBS::Database::ExecuteNonQuery(
            "INSERT INTO Payments (BillNo, Method, CustomerName, AmountPaid, ChangeAmount) VALUES (@b, @m, @n, @a, @c)",
            gcnew SqlParameter("@b", billNo),
            gcnew SqlParameter("@m", "Card"),
            gcnew SqlParameter("@n", holderName),
            gcnew SqlParameter("@a", totalBill),
            gcnew SqlParameter("@c", (double)0.0));
        SBS::Database::ExecuteNonQuery(
            "UPDATE Payments SET Status = @s WHERE BillNo = @b",
            gcnew SqlParameter("@s", "Approved"),
            gcnew SqlParameter("@b", billNo));
        MessageBox::Show("Card Payment Successful!\nCustomer: " + holderName,
            "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
        ReceiptForm^ receipt = gcnew ReceiptForm(billNo);
        receipt->ShowDialog();
        this->Close();
    }
}

void PaymentForm::btnCancel_Click(Object^ sender, EventArgs^ e) {
    SBS::Database::ExecuteNonQuery(
        "UPDATE Payments SET Status = @s WHERE BillNo = @b",
        gcnew SqlParameter("@s", "Cancelled"),
        gcnew SqlParameter("@b", billNo));
    MessageBox::Show("Payment Cancelled!", "Cancelled",
        MessageBoxButtons::OK, MessageBoxIcon::Information);
    this->Close();
}