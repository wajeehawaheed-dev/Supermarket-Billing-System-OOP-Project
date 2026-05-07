#include "PaymentForm.h"
#include "ReceiptForm.h"
using namespace SUper;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;
using namespace System::Data::SqlClient;

// ===== Brand palette =====
static Color PF_NAVY() { return Color::FromArgb(30, 58, 138); }
static Color PF_NAVY_DARK() { return Color::FromArgb(15, 30, 90); }
static Color PF_NAVY_HOVER() { return Color::FromArgb(45, 75, 165); }
static Color PF_GREEN() { return Color::FromArgb(34, 197, 94); }
static Color PF_GREEN_HOVER() { return Color::FromArgb(22, 163, 74); }
static Color PF_RED() { return Color::FromArgb(220, 38, 38); }
static Color PF_BG_LIGHT() { return Color::FromArgb(248, 250, 252); }
static Color PF_BORDER() { return Color::FromArgb(229, 231, 235); }
static Color PF_TEXT_DARK() { return Color::FromArgb(30, 41, 59); }
static Color PF_TEXT_MUTED() { return Color::FromArgb(100, 116, 139); }

static void PF_RoundIt(Control^ ctrl, int radius) {
    GraphicsPath^ path = gcnew GraphicsPath();
    System::Drawing::Rectangle r = ctrl->ClientRectangle;
    path->AddArc(r.X, r.Y, radius, radius, 180, 90);
    path->AddArc(r.Right - radius, r.Y, radius, radius, 270, 90);
    path->AddArc(r.Right - radius, r.Bottom - radius, radius, radius, 0, 90);
    path->AddArc(r.X, r.Bottom - radius, radius, radius, 90, 90);
    path->CloseAllFigures();
    ctrl->Region = gcnew System::Drawing::Region(path);
}

PaymentForm::PaymentForm(int billNo, double totalBill) {
    this->billNo = billNo;
    this->totalBill = totalBill;
    this->failedAttempts = 0;
    this->formLocked = false;
    this->secondsRemaining = 60;
    InitializeComponent();
}


bool PaymentForm::IsValidExpiryDate(int month, int year) {
    if (month < 1 || month > 12) return false;
    DateTime now = DateTime::Now;
    int currentYear = now.Year % 100;
    if (year > currentYear + 10) return false;
    return true;
}

void PaymentForm::InitializeComponent() {
    this->SuspendLayout();
    this->Text = "Payment";
    this->ClientSize = System::Drawing::Size(540, 720);
    this->StartPosition = FormStartPosition::CenterScreen;
    this->BackColor = PF_BG_LIGHT();
    this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
    this->DoubleBuffered = true;

    // ===== HEADER =====
    pnlHeader = gcnew Panel();
    pnlHeader->Location = System::Drawing::Point(0, 0);
    pnlHeader->Size = System::Drawing::Size(540, 100);
    pnlHeader->BackColor = PF_NAVY();

    lblTitle = gcnew Label();
    lblTitle->Text = "Payment";
    lblTitle->Font = gcnew System::Drawing::Font("Segoe UI", 18, FontStyle::Bold);
    lblTitle->ForeColor = Color::White;
    lblTitle->BackColor = Color::Transparent;
    lblTitle->Location = System::Drawing::Point(30, 22);
    lblTitle->AutoSize = true;

    lblBillNo = gcnew Label();
    lblBillNo->Text = "Bill No: " + billNo.ToString();
    lblBillNo->Font = gcnew System::Drawing::Font("Segoe UI", 9);
    lblBillNo->ForeColor = Color::FromArgb(180, 200, 230);
    lblBillNo->BackColor = Color::Transparent;
    lblBillNo->Location = System::Drawing::Point(32, 60);
    lblBillNo->AutoSize = true;

    lblTotal = gcnew Label();
    lblTotal->Text = "Rs " + totalBill.ToString("N2");
    lblTotal->Font = gcnew System::Drawing::Font("Segoe UI", 18, FontStyle::Bold);
    lblTotal->ForeColor = Color::White;
    lblTotal->BackColor = Color::Transparent;
    lblTotal->Location = System::Drawing::Point(330, 30);
    lblTotal->Size = System::Drawing::Size(180, 35);
    lblTotal->TextAlign = ContentAlignment::MiddleRight;

    Label^ lblTotalCap = gcnew Label();
    lblTotalCap->Text = "AMOUNT DUE";
    lblTotalCap->Font = gcnew System::Drawing::Font("Segoe UI", 8, FontStyle::Bold);
    lblTotalCap->ForeColor = Color::FromArgb(180, 200, 230);
    lblTotalCap->BackColor = Color::Transparent;
    lblTotalCap->Location = System::Drawing::Point(330, 65);
    lblTotalCap->Size = System::Drawing::Size(180, 18);
    lblTotalCap->TextAlign = ContentAlignment::MiddleRight;

    pnlHeader->Controls->Add(lblTitle);
    pnlHeader->Controls->Add(lblBillNo);
    pnlHeader->Controls->Add(lblTotal);
    pnlHeader->Controls->Add(lblTotalCap);

    // ===== METHOD TOGGLE (replaces radio buttons with two pill buttons) =====
    pnlMethod = gcnew Panel();
    pnlMethod->Location = System::Drawing::Point(30, 125);
    pnlMethod->Size = System::Drawing::Size(480, 90);
    pnlMethod->BackColor = Color::White;

    lblMethodTitle = gcnew Label();
    lblMethodTitle->Text = "PAYMENT METHOD";
    lblMethodTitle->Font = gcnew System::Drawing::Font("Segoe UI", 8.5F, FontStyle::Bold);
    lblMethodTitle->ForeColor = PF_TEXT_MUTED();
    lblMethodTitle->BackColor = Color::Transparent;
    lblMethodTitle->Location = System::Drawing::Point(20, 12);
    lblMethodTitle->AutoSize = true;

    // Cash/Card as RadioButtons styled like buttons (keeps original behavior)
    rbCash = gcnew RadioButton();
    rbCash->Text = L"\U0001F4B5  Cash";
    rbCash->Appearance = System::Windows::Forms::Appearance::Button;
    rbCash->FlatStyle = FlatStyle::Flat;
    rbCash->FlatAppearance->BorderSize = 1;
    rbCash->FlatAppearance->BorderColor = PF_NAVY();
    rbCash->FlatAppearance->CheckedBackColor = PF_NAVY();
    rbCash->BackColor = Color::White;
    rbCash->ForeColor = PF_TEXT_DARK();
    rbCash->Font = gcnew System::Drawing::Font("Segoe UI", 10, FontStyle::Bold);
    rbCash->Location = System::Drawing::Point(20, 38);
    rbCash->Size = System::Drawing::Size(220, 40);
    rbCash->TextAlign = ContentAlignment::MiddleCenter;
    rbCash->Cursor = Cursors::Hand;
    rbCash->Checked = true;
    rbCash->CheckedChanged += gcnew EventHandler(this, &PaymentForm::rbCash_Changed);

    rbCard = gcnew RadioButton();
    rbCard->Text = L"\U0001F4B3  Card";
    rbCard->Appearance = System::Windows::Forms::Appearance::Button;
    rbCard->FlatStyle = FlatStyle::Flat;
    rbCard->FlatAppearance->BorderSize = 1;
    rbCard->FlatAppearance->BorderColor = PF_NAVY();
    rbCard->FlatAppearance->CheckedBackColor = PF_NAVY();
    rbCard->BackColor = Color::White;
    rbCard->ForeColor = PF_TEXT_DARK();
    rbCard->Font = gcnew System::Drawing::Font("Segoe UI", 10, FontStyle::Bold);
    rbCard->Location = System::Drawing::Point(245, 38);
    rbCard->Size = System::Drawing::Size(220, 40);
    rbCard->TextAlign = ContentAlignment::MiddleCenter;
    rbCard->Cursor = Cursors::Hand;
    rbCard->CheckedChanged += gcnew EventHandler(this, &PaymentForm::rbCard_Changed);

    pnlMethod->Controls->Add(lblMethodTitle);
    pnlMethod->Controls->Add(rbCash);
    pnlMethod->Controls->Add(rbCard);

    // ===== CASH PANEL =====
    pnlCash = gcnew Panel();
    pnlCash->Location = System::Drawing::Point(30, 230);
    pnlCash->Size = System::Drawing::Size(480, 230);
    pnlCash->BackColor = Color::White;

    Label^ lblCashHeader = gcnew Label();
    lblCashHeader->Text = "Cash Payment";
    lblCashHeader->Font = gcnew System::Drawing::Font("Segoe UI", 12, FontStyle::Bold);
    lblCashHeader->ForeColor = PF_TEXT_DARK();
    lblCashHeader->Location = System::Drawing::Point(20, 18);
    lblCashHeader->AutoSize = true;

    lblCustName = gcnew Label();
    lblCustName->Text = "CUSTOMER NAME";
    lblCustName->Font = gcnew System::Drawing::Font("Segoe UI", 8.5F, FontStyle::Bold);
    lblCustName->ForeColor = PF_TEXT_MUTED();
    lblCustName->BackColor = Color::Transparent;
    lblCustName->Location = System::Drawing::Point(20, 60);
    lblCustName->AutoSize = true;

    txtCustName = gcnew TextBox();
    txtCustName->BorderStyle = BorderStyle::None;
    txtCustName->Font = gcnew System::Drawing::Font("Segoe UI", 11);
    txtCustName->ForeColor = PF_TEXT_DARK();
    txtCustName->Location = System::Drawing::Point(20, 82);
    txtCustName->Size = System::Drawing::Size(440, 22);

    Panel^ pnlCustNameLine = gcnew Panel();
    pnlCustNameLine->Location = System::Drawing::Point(20, 108);
    pnlCustNameLine->Size = System::Drawing::Size(440, 2);
    pnlCustNameLine->BackColor = PF_BORDER();

    lblCashAmount = gcnew Label();
    lblCashAmount->Text = "CASH AMOUNT (Rs)";
    lblCashAmount->Font = gcnew System::Drawing::Font("Segoe UI", 8.5F, FontStyle::Bold);
    lblCashAmount->ForeColor = PF_TEXT_MUTED();
    lblCashAmount->BackColor = Color::Transparent;
    lblCashAmount->Location = System::Drawing::Point(20, 130);
    lblCashAmount->AutoSize = true;

    txtCashAmount = gcnew TextBox();
    txtCashAmount->BorderStyle = BorderStyle::None;
    txtCashAmount->Font = gcnew System::Drawing::Font("Segoe UI", 11);
    txtCashAmount->ForeColor = PF_TEXT_DARK();
    txtCashAmount->Location = System::Drawing::Point(20, 152);
    txtCashAmount->Size = System::Drawing::Size(440, 22);

    Panel^ pnlCashAmtLine = gcnew Panel();
    pnlCashAmtLine->Location = System::Drawing::Point(20, 178);
    pnlCashAmtLine->Size = System::Drawing::Size(440, 2);
    pnlCashAmtLine->BackColor = PF_BORDER();

    Label^ lblCashHint = gcnew Label();
    lblCashHint->Text = L"\u2139  Must be at least Rs " + totalBill.ToString("N2");
    lblCashHint->Font = gcnew System::Drawing::Font("Segoe UI", 8.5F);
    lblCashHint->ForeColor = PF_TEXT_MUTED();
    lblCashHint->BackColor = Color::Transparent;
    lblCashHint->Location = System::Drawing::Point(20, 195);
    lblCashHint->AutoSize = true;

    pnlCash->Controls->Add(lblCashHeader);
    pnlCash->Controls->Add(lblCustName);
    pnlCash->Controls->Add(txtCustName);
    pnlCash->Controls->Add(pnlCustNameLine);
    pnlCash->Controls->Add(lblCashAmount);
    pnlCash->Controls->Add(txtCashAmount);
    pnlCash->Controls->Add(pnlCashAmtLine);
    pnlCash->Controls->Add(lblCashHint);

    // ===== CARD PANEL =====
    pnlCard = gcnew Panel();
    pnlCard->Location = System::Drawing::Point(30, 230);
    pnlCard->Size = System::Drawing::Size(480, 360);
    pnlCard->BackColor = Color::White;
    pnlCard->Visible = false;

    Label^ lblCardHeader = gcnew Label();
    lblCardHeader->Text = "Card Payment";
    lblCardHeader->Font = gcnew System::Drawing::Font("Segoe UI", 12, FontStyle::Bold);
    lblCardHeader->ForeColor = PF_TEXT_DARK();
    lblCardHeader->Location = System::Drawing::Point(20, 18);
    lblCardHeader->AutoSize = true;

    lblCardHolder = gcnew Label();
    lblCardHolder->Text = "CARD HOLDER";
    lblCardHolder->Font = gcnew System::Drawing::Font("Segoe UI", 8.5F, FontStyle::Bold);
    lblCardHolder->ForeColor = PF_TEXT_MUTED();
    lblCardHolder->BackColor = Color::Transparent;
    lblCardHolder->Location = System::Drawing::Point(20, 60);
    lblCardHolder->AutoSize = true;

    txtCardHolder = gcnew TextBox();
    txtCardHolder->BorderStyle = BorderStyle::None;
    txtCardHolder->Font = gcnew System::Drawing::Font("Segoe UI", 11);
    txtCardHolder->ForeColor = PF_TEXT_DARK();
    txtCardHolder->Location = System::Drawing::Point(20, 82);
    txtCardHolder->Size = System::Drawing::Size(440, 22);

    Panel^ pnlCardHolderLine = gcnew Panel();
    pnlCardHolderLine->Location = System::Drawing::Point(20, 108);
    pnlCardHolderLine->Size = System::Drawing::Size(440, 2);
    pnlCardHolderLine->BackColor = PF_BORDER();

    lblCardNo = gcnew Label();
    lblCardNo->Text = "CARD NUMBER";
    lblCardNo->Font = gcnew System::Drawing::Font("Segoe UI", 8.5F, FontStyle::Bold);
    lblCardNo->ForeColor = PF_TEXT_MUTED();
    lblCardNo->BackColor = Color::Transparent;
    lblCardNo->Location = System::Drawing::Point(20, 130);
    lblCardNo->AutoSize = true;

    txtCardNo = gcnew TextBox();
    txtCardNo->BorderStyle = BorderStyle::None;
    txtCardNo->Font = gcnew System::Drawing::Font("Consolas", 11);
    txtCardNo->ForeColor = PF_TEXT_DARK();
    txtCardNo->Location = System::Drawing::Point(20, 152);
    txtCardNo->Size = System::Drawing::Size(440, 22);
    txtCardNo->MaxLength = 16;

    Panel^ pnlCardNoLine = gcnew Panel();
    pnlCardNoLine->Location = System::Drawing::Point(20, 178);
    pnlCardNoLine->Size = System::Drawing::Size(440, 2);
    pnlCardNoLine->BackColor = PF_BORDER();

    lblExpiry = gcnew Label();
    lblExpiry->Text = "EXPIRY (MM/YY)";
    lblExpiry->Font = gcnew System::Drawing::Font("Segoe UI", 8.5F, FontStyle::Bold);
    lblExpiry->ForeColor = PF_TEXT_MUTED();
    lblExpiry->BackColor = Color::Transparent;
    lblExpiry->Location = System::Drawing::Point(20, 200);
    lblExpiry->AutoSize = true;

    txtExpiry = gcnew TextBox();
    txtExpiry->BorderStyle = BorderStyle::None;
    txtExpiry->Font = gcnew System::Drawing::Font("Consolas", 11);
    txtExpiry->ForeColor = PF_TEXT_DARK();
    txtExpiry->Location = System::Drawing::Point(20, 222);
    txtExpiry->Size = System::Drawing::Size(200, 22);
    txtExpiry->MaxLength = 5;

    Panel^ pnlExpiryLine = gcnew Panel();
    pnlExpiryLine->Location = System::Drawing::Point(20, 248);
    pnlExpiryLine->Size = System::Drawing::Size(200, 2);
    pnlExpiryLine->BackColor = PF_BORDER();

    lblCVV = gcnew Label();
    lblCVV->Text = "CVV";
    lblCVV->Font = gcnew System::Drawing::Font("Segoe UI", 8.5F, FontStyle::Bold);
    lblCVV->ForeColor = PF_TEXT_MUTED();
    lblCVV->BackColor = Color::Transparent;
    lblCVV->Location = System::Drawing::Point(260, 200);
    lblCVV->AutoSize = true;

    txtCVV = gcnew TextBox();
    txtCVV->BorderStyle = BorderStyle::None;
    txtCVV->Font = gcnew System::Drawing::Font("Consolas", 11);
    txtCVV->ForeColor = PF_TEXT_DARK();
    txtCVV->Location = System::Drawing::Point(260, 222);
    txtCVV->Size = System::Drawing::Size(200, 22);
    txtCVV->MaxLength = 3;
    txtCVV->PasswordChar = L'\u25CF';

    Panel^ pnlCVVLine = gcnew Panel();
    pnlCVVLine->Location = System::Drawing::Point(260, 248);
    pnlCVVLine->Size = System::Drawing::Size(200, 2);
    pnlCVVLine->BackColor = PF_BORDER();

    Label^ lblCardHint = gcnew Label();
    lblCardHint->Text = L"\U0001F512  Your card details are processed securely";
    lblCardHint->Font = gcnew System::Drawing::Font("Segoe UI", 8.5F);
    lblCardHint->ForeColor = PF_TEXT_MUTED();
    lblCardHint->BackColor = Color::Transparent;
    lblCardHint->Location = System::Drawing::Point(20, 290);
    lblCardHint->AutoSize = true;

    pnlCard->Controls->Add(lblCardHeader);
    pnlCard->Controls->Add(lblCardHolder);
    pnlCard->Controls->Add(txtCardHolder);
    pnlCard->Controls->Add(pnlCardHolderLine);
    pnlCard->Controls->Add(lblCardNo);
    pnlCard->Controls->Add(txtCardNo);
    pnlCard->Controls->Add(pnlCardNoLine);
    pnlCard->Controls->Add(lblExpiry);
    pnlCard->Controls->Add(txtExpiry);
    pnlCard->Controls->Add(pnlExpiryLine);
    pnlCard->Controls->Add(lblCVV);
    pnlCard->Controls->Add(txtCVV);
    pnlCard->Controls->Add(pnlCVVLine);
    pnlCard->Controls->Add(lblCardHint);

    // ===== LOCK MESSAGE =====
    lblLockMsg = gcnew Label();
    lblLockMsg->Text = "";
    lblLockMsg->Font = gcnew System::Drawing::Font("Segoe UI", 9, FontStyle::Bold);
    lblLockMsg->ForeColor = PF_RED();
    lblLockMsg->BackColor = Color::FromArgb(254, 226, 226);
    lblLockMsg->Location = System::Drawing::Point(30, 615);
    lblLockMsg->Size = System::Drawing::Size(480, 32);
    lblLockMsg->TextAlign = ContentAlignment::MiddleCenter;
    lblLockMsg->Visible = false;

    // ===== BUTTONS =====
    btnPay = gcnew Button();
    btnPay->Text = "Confirm Payment";
    btnPay->Font = gcnew System::Drawing::Font("Segoe UI", 11, FontStyle::Bold);
    btnPay->Location = System::Drawing::Point(220, 660);
    btnPay->Size = System::Drawing::Size(290, 50);
    btnPay->BackColor = PF_GREEN();
    btnPay->ForeColor = Color::White;
    btnPay->FlatStyle = FlatStyle::Flat;
    btnPay->FlatAppearance->BorderSize = 0;
    btnPay->Cursor = Cursors::Hand;
    btnPay->Click += gcnew EventHandler(this, &PaymentForm::btnPay_Click);

    btnCancel = gcnew Button();
    btnCancel->Text = "Cancel";
    btnCancel->Font = gcnew System::Drawing::Font("Segoe UI", 10);
    btnCancel->Location = System::Drawing::Point(30, 660);
    btnCancel->Size = System::Drawing::Size(170, 50);
    btnCancel->BackColor = Color::White;
    btnCancel->ForeColor = PF_TEXT_DARK();
    btnCancel->FlatStyle = FlatStyle::Flat;
    btnCancel->FlatAppearance->BorderSize = 1;
    btnCancel->FlatAppearance->BorderColor = PF_BORDER();
    btnCancel->Cursor = Cursors::Hand;
    btnCancel->Click += gcnew EventHandler(this, &PaymentForm::btnCancel_Click);

    // ===== TIMER =====
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

    // Round corners
    PF_RoundIt(btnPay, 8);
    PF_RoundIt(btnCancel, 8);
    PF_RoundIt(rbCash, 8);
    PF_RoundIt(rbCard, 8);
    PF_RoundIt(pnlMethod, 8);
    PF_RoundIt(pnlCash, 8);
    PF_RoundIt(pnlCard, 8);
    PF_RoundIt(lblLockMsg, 6);

    this->Load += gcnew System::EventHandler(this, &PaymentForm::PaymentForm_Load);
    this->ResumeLayout(false);
}

// ===== UNCHANGED LOGIC =====
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
        lblLockMsg->Text = L"\u26A0  Locked! Unlocks in " + secondsRemaining.ToString() + " second(s)...";
    }
}

void PaymentForm::rbCash_Changed(Object^ sender, EventArgs^ e) {
    if (rbCash->Checked) {
        rbCash->ForeColor = Color::White;
        rbCard->ForeColor = PF_TEXT_DARK();
        pnlCash->Visible = true;
        pnlCard->Visible = false;
    }
}

void PaymentForm::rbCard_Changed(Object^ sender, EventArgs^ e) {
    if (rbCard->Checked) {
        rbCard->ForeColor = Color::White;
        rbCash->ForeColor = PF_TEXT_DARK();
        pnlCash->Visible = false;
        pnlCard->Visible = true;
    }
}

void PaymentForm::btnPay_Click(Object^ sender, EventArgs^ e) {
    if (formLocked) {
        MessageBox::Show("Payment is locked! Please wait " + secondsRemaining.ToString() + " second(s).",
            "Locked", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return;
    }

    if (rbCash->Checked) {
        String^ errors = "";
        String^ custName = txtCustName->Text->Trim();
        if (custName->Length == 0) {
            errors += "- Customer Name is required.\n";
        }
        else {
            bool hasInvalidChar = false;
            for each (Char c in custName) {
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
        String^ errors = "";

        String^ holderName = txtCardHolder->Text->Trim();
        if (holderName->Length == 0) {
            errors += "- Card Holder name is required.\n";
        }
        else {
            bool hasInvalidChar = false;
            for each (Char c in holderName) {
                if (!Char::IsLetter(c) && c != ' ') { hasInvalidChar = true; break; }
            }
            if (hasInvalidChar)
                errors += "- Card Holder name must contain letters only (no numbers or symbols).\n";
        }

        if (txtCardNo->Text->Length != 16) {
            errors += "- Card number must be exactly 16 digits.\n";
        }
        else {
            bool allDigits = true;
            for each (Char c in txtCardNo->Text) {
                if (!Char::IsDigit(c)) { allDigits = false; break; }
            }
            if (!allDigits) errors += "- Card number must contain digits only.\n";
        }

        if (txtCVV->Text->Length != 3) {
            errors += "- CVV must be exactly 3 digits.\n";
        }
        else {
            bool allDigits = true;
            for each (Char c in txtCVV->Text) {
                if (!Char::IsDigit(c)) { allDigits = false; break; }
            }
            if (!allDigits) errors += "- CVV must contain digits only.\n";
        }

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
                errors += "- Expiry month must be between 01 and 12.\n";
            }
            else if (!IsValidExpiryDate(month, year)) {
                errors += "- Expiry year is unrealistic. Cards expire within 10 years.\n";
            }
            else {
                DateTime now = DateTime::Now;
                int currentMonth = now.Month;
                int currentYear = now.Year % 100;
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
                lblLockMsg->Text = L"\u26A0  Locked! Unlocks in 60 second(s)...";
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