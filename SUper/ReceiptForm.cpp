#include "ReceiptForm.h"

using namespace SUper;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;
using namespace System::Data::SqlClient;
using namespace System::Drawing::Printing;
using namespace System::Text;

// ===== Brand palette =====
static Color RF_NAVY() { return Color::FromArgb(30, 58, 138); }
static Color RF_NAVY_DARK() { return Color::FromArgb(15, 30, 90); }
static Color RF_NAVY_HOVER() { return Color::FromArgb(45, 75, 165); }
static Color RF_GREEN() { return Color::FromArgb(34, 197, 94); }
static Color RF_GREEN_HOVER() { return Color::FromArgb(22, 163, 74); }
static Color RF_BG_LIGHT() { return Color::FromArgb(248, 250, 252); }
static Color RF_BORDER() { return Color::FromArgb(229, 231, 235); }
static Color RF_TEXT_DARK() { return Color::FromArgb(30, 41, 59); }
static Color RF_TEXT_MUTED() { return Color::FromArgb(100, 116, 139); }

static void RF_RoundIt(Control^ ctrl, int radius) {
    GraphicsPath^ path = gcnew GraphicsPath();
    System::Drawing::Rectangle r = ctrl->ClientRectangle;
    path->AddArc(r.X, r.Y, radius, radius, 180, 90);
    path->AddArc(r.Right - radius, r.Y, radius, radius, 270, 90);
    path->AddArc(r.Right - radius, r.Bottom - radius, radius, radius, 0, 90);
    path->AddArc(r.X, r.Bottom - radius, radius, radius, 90, 90);
    path->CloseAllFigures();
    ctrl->Region = gcnew System::Drawing::Region(path);
}

ReceiptForm::ReceiptForm(int billNo) {
    this->billNo = billNo;
    InitializeComponent();
    LoadReceiptData();
}

void ReceiptForm::InitializeComponent() {
    this->Text = "Receipt";
    this->ClientSize = System::Drawing::Size(460, 760);
    this->StartPosition = FormStartPosition::CenterScreen;
    this->BackColor = RF_BG_LIGHT();
    this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
    this->MaximizeBox = false;
    this->DoubleBuffered = true;

    // ===== HEADER =====
    pnlHeader = gcnew Panel();
    pnlHeader->Location = System::Drawing::Point(0, 0);
    pnlHeader->Size = System::Drawing::Size(460, 90);
    pnlHeader->BackColor = RF_NAVY();

    lblStoreName = gcnew Label();
    lblStoreName->Text = "ValueMart";
    lblStoreName->Font = gcnew System::Drawing::Font("Segoe UI", 18, FontStyle::Bold);
    lblStoreName->ForeColor = Color::White;
    lblStoreName->BackColor = Color::Transparent;
    lblStoreName->Location = System::Drawing::Point(0, 18);
    lblStoreName->Size = System::Drawing::Size(460, 32);
    lblStoreName->TextAlign = ContentAlignment::MiddleCenter;

    lblReceipt = gcnew Label();
    lblReceipt->Text = L"\u2713  PAYMENT SUCCESSFUL";
    lblReceipt->Font = gcnew System::Drawing::Font("Segoe UI", 9, FontStyle::Bold);
    lblReceipt->ForeColor = Color::FromArgb(180, 230, 200);
    lblReceipt->BackColor = Color::Transparent;
    lblReceipt->Location = System::Drawing::Point(0, 53);
    lblReceipt->Size = System::Drawing::Size(460, 22);
    lblReceipt->TextAlign = ContentAlignment::MiddleCenter;

    pnlHeader->Controls->Add(lblStoreName);
    pnlHeader->Controls->Add(lblReceipt);

    // ===== RECEIPT CARD (the paper-receipt body) =====
    pnlBody = gcnew Panel();
    pnlBody->Location = System::Drawing::Point(20, 105);
    pnlBody->Size = System::Drawing::Size(420, 560);
    pnlBody->BackColor = Color::White;
    pnlBody->BorderStyle = System::Windows::Forms::BorderStyle::None;

    // Bill metadata
    lblBillNo = gcnew Label();
    lblBillNo->Text = "Bill No: --";
    lblBillNo->Font = gcnew System::Drawing::Font("Consolas", 9);
    lblBillNo->Location = System::Drawing::Point(20, 20);
    lblBillNo->Size = System::Drawing::Size(180, 20);
    lblBillNo->ForeColor = RF_TEXT_DARK();

    lblDate = gcnew Label();
    lblDate->Text = "Date: --";
    lblDate->Font = gcnew System::Drawing::Font("Consolas", 9);
    lblDate->Location = System::Drawing::Point(210, 20);
    lblDate->Size = System::Drawing::Size(190, 20);
    lblDate->TextAlign = ContentAlignment::MiddleRight;
    lblDate->ForeColor = RF_TEXT_DARK();

    lblCashier = gcnew Label();
    lblCashier->Text = "Cashier: --";
    lblCashier->Font = gcnew System::Drawing::Font("Consolas", 9);
    lblCashier->Location = System::Drawing::Point(20, 43);
    lblCashier->Size = System::Drawing::Size(380, 20);
    lblCashier->ForeColor = RF_TEXT_DARK();

    lblDivider1 = gcnew Label();
    lblDivider1->Text = "----------------------------------------";
    lblDivider1->Font = gcnew System::Drawing::Font("Consolas", 9);
    lblDivider1->Location = System::Drawing::Point(20, 67);
    lblDivider1->Size = System::Drawing::Size(380, 20);
    lblDivider1->ForeColor = RF_BORDER();

    // Items list
    lblItems = gcnew Label();
    lblItems->Text = "Item                 Qty   Price    Total\r\n----------------------------------------";
    lblItems->Font = gcnew System::Drawing::Font("Consolas", 9, FontStyle::Bold);
    lblItems->Location = System::Drawing::Point(20, 90);
    lblItems->Size = System::Drawing::Size(380, 200);
    lblItems->ForeColor = RF_TEXT_DARK();
    lblItems->AutoSize = false;

    lblDivider2 = gcnew Label();
    lblDivider2->Text = "----------------------------------------";
    lblDivider2->Font = gcnew System::Drawing::Font("Consolas", 9);
    lblDivider2->Location = System::Drawing::Point(20, 295);
    lblDivider2->Size = System::Drawing::Size(380, 20);
    lblDivider2->ForeColor = RF_BORDER();

    // Totals
    lblSubtotal = gcnew Label();
    lblSubtotal->Text = "Subtotal:              Rs --";
    lblSubtotal->Font = gcnew System::Drawing::Font("Consolas", 9);
    lblSubtotal->Location = System::Drawing::Point(20, 320);
    lblSubtotal->Size = System::Drawing::Size(380, 20);
    lblSubtotal->ForeColor = RF_TEXT_DARK();

    lblDiscount = gcnew Label();
    lblDiscount->Text = "Discount:              Rs --";
    lblDiscount->Font = gcnew System::Drawing::Font("Consolas", 9);
    lblDiscount->Location = System::Drawing::Point(20, 343);
    lblDiscount->Size = System::Drawing::Size(380, 20);
    lblDiscount->ForeColor = RF_GREEN_HOVER();

    lblTax = gcnew Label();
    lblTax->Text = "Tax:                   Rs --";
    lblTax->Font = gcnew System::Drawing::Font("Consolas", 9);
    lblTax->Location = System::Drawing::Point(20, 366);
    lblTax->Size = System::Drawing::Size(380, 20);
    lblTax->ForeColor = RF_TEXT_DARK();

    lblDivider3 = gcnew Label();
    lblDivider3->Text = "========================================";
    lblDivider3->Font = gcnew System::Drawing::Font("Consolas", 9);
    lblDivider3->Location = System::Drawing::Point(20, 389);
    lblDivider3->Size = System::Drawing::Size(380, 20);
    lblDivider3->ForeColor = RF_NAVY();

    lblGrandTotal = gcnew Label();
    lblGrandTotal->Text = "GRAND TOTAL:           Rs --";
    lblGrandTotal->Font = gcnew System::Drawing::Font("Consolas", 12, FontStyle::Bold);
    lblGrandTotal->Location = System::Drawing::Point(20, 412);
    lblGrandTotal->Size = System::Drawing::Size(380, 25);
    lblGrandTotal->ForeColor = RF_NAVY();

    lblDivider4 = gcnew Label();
    lblDivider4->Text = "========================================";
    lblDivider4->Font = gcnew System::Drawing::Font("Consolas", 9);
    lblDivider4->Location = System::Drawing::Point(20, 440);
    lblDivider4->Size = System::Drawing::Size(380, 20);
    lblDivider4->ForeColor = RF_NAVY();

    // Payment info
    lblPayMethod = gcnew Label();
    lblPayMethod->Text = "Payment Method:        --";
    lblPayMethod->Font = gcnew System::Drawing::Font("Consolas", 9);
    lblPayMethod->Location = System::Drawing::Point(20, 465);
    lblPayMethod->Size = System::Drawing::Size(380, 20);
    lblPayMethod->ForeColor = RF_TEXT_DARK();

    lblAmountPaid = gcnew Label();
    lblAmountPaid->Text = "Amount Paid:           Rs --";
    lblAmountPaid->Font = gcnew System::Drawing::Font("Consolas", 9);
    lblAmountPaid->Location = System::Drawing::Point(20, 488);
    lblAmountPaid->Size = System::Drawing::Size(380, 20);
    lblAmountPaid->ForeColor = RF_TEXT_DARK();

    lblChange = gcnew Label();
    lblChange->Text = "Change:                Rs --";
    lblChange->Font = gcnew System::Drawing::Font("Consolas", 9, FontStyle::Bold);
    lblChange->Location = System::Drawing::Point(20, 511);
    lblChange->Size = System::Drawing::Size(380, 20);
    lblChange->ForeColor = RF_GREEN_HOVER();

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

    // Custom border drawn via Paint (avoids the FixedSingle look)
    pnlBody->Paint += gcnew PaintEventHandler(this, &ReceiptForm::pnlBody_Paint);

    // Thank-you message
    lblThankYou = gcnew Label();
    lblThankYou->Text = L"Thank you for shopping with us!";
    lblThankYou->Font = gcnew System::Drawing::Font("Segoe UI", 10, FontStyle::Italic);
    lblThankYou->ForeColor = RF_TEXT_MUTED();
    lblThankYou->BackColor = Color::Transparent;
    lblThankYou->Location = System::Drawing::Point(0, 675);
    lblThankYou->Size = System::Drawing::Size(460, 22);
    lblThankYou->TextAlign = ContentAlignment::MiddleCenter;

    // ===== BUTTONS =====
    btnPrint = gcnew Button();
    btnPrint->Text = L"\U0001F5A8  Print";
    btnPrint->Font = gcnew System::Drawing::Font("Segoe UI", 10, FontStyle::Bold);
    btnPrint->Location = System::Drawing::Point(310, 710);
    btnPrint->Size = System::Drawing::Size(130, 40);
    btnPrint->BackColor = RF_GREEN();
    btnPrint->ForeColor = Color::White;
    btnPrint->FlatStyle = FlatStyle::Flat;
    btnPrint->FlatAppearance->BorderSize = 0;
    btnPrint->Cursor = Cursors::Hand;
    btnPrint->Click += gcnew EventHandler(this, &ReceiptForm::btnPrint_Click);
    btnPrint->MouseEnter += gcnew EventHandler(this, &ReceiptForm::btnPrint_MouseEnter);
    btnPrint->MouseLeave += gcnew EventHandler(this, &ReceiptForm::btnPrint_MouseLeave);

    btnPreview = gcnew Button();
    btnPreview->Text = "Preview";
    btnPreview->Font = gcnew System::Drawing::Font("Segoe UI", 10, FontStyle::Bold);
    btnPreview->Location = System::Drawing::Point(170, 710);
    btnPreview->Size = System::Drawing::Size(130, 40);
    btnPreview->BackColor = RF_NAVY();
    btnPreview->ForeColor = Color::White;
    btnPreview->FlatStyle = FlatStyle::Flat;
    btnPreview->FlatAppearance->BorderSize = 0;
    btnPreview->Cursor = Cursors::Hand;
    btnPreview->Click += gcnew EventHandler(this, &ReceiptForm::btnPreview_Click);
    btnPreview->MouseEnter += gcnew EventHandler(this, &ReceiptForm::btnPreview_MouseEnter);
    btnPreview->MouseLeave += gcnew EventHandler(this, &ReceiptForm::btnPreview_MouseLeave);

    btnClose = gcnew Button();
    btnClose->Text = "Close";
    btnClose->Font = gcnew System::Drawing::Font("Segoe UI", 10);
    btnClose->Location = System::Drawing::Point(20, 710);
    btnClose->Size = System::Drawing::Size(130, 40);
    btnClose->BackColor = Color::White;
    btnClose->ForeColor = RF_TEXT_DARK();
    btnClose->FlatStyle = FlatStyle::Flat;
    btnClose->FlatAppearance->BorderSize = 1;
    btnClose->FlatAppearance->BorderColor = RF_BORDER();
    btnClose->Cursor = Cursors::Hand;
    btnClose->Click += gcnew EventHandler(this, &ReceiptForm::btnClose_Click);
    btnClose->MouseEnter += gcnew EventHandler(this, &ReceiptForm::btnClose_MouseEnter);
    btnClose->MouseLeave += gcnew EventHandler(this, &ReceiptForm::btnClose_MouseLeave);

    // PrintDocument (unchanged)
    printDoc = gcnew PrintDocument();
    printDoc->PrintPage += gcnew PrintPageEventHandler(this, &ReceiptForm::OnPrintPage);

    this->Controls->Add(pnlHeader);
    this->Controls->Add(pnlBody);
    this->Controls->Add(lblThankYou);
    this->Controls->Add(btnPrint);
    this->Controls->Add(btnPreview);
    this->Controls->Add(btnClose);

    RF_RoundIt(btnPrint, 6);
    RF_RoundIt(btnPreview, 6);
    RF_RoundIt(btnClose, 6);
    RF_RoundIt(pnlBody, 8);
}

// ===== PAINT =====
void ReceiptForm::pnlBody_Paint(Object^ sender, PaintEventArgs^ e) {
    Pen^ pen = gcnew Pen(RF_BORDER(), 1);
    e->Graphics->DrawRectangle(pen, 0, 0, pnlBody->Width - 1, pnlBody->Height - 1);
}

// ===== HOVER HANDLERS =====
void ReceiptForm::btnPrint_MouseEnter(Object^ s, EventArgs^ e) { btnPrint->BackColor = RF_GREEN_HOVER(); }
void ReceiptForm::btnPrint_MouseLeave(Object^ s, EventArgs^ e) { btnPrint->BackColor = RF_GREEN(); }
void ReceiptForm::btnPreview_MouseEnter(Object^ s, EventArgs^ e) { btnPreview->BackColor = RF_NAVY_HOVER(); }
void ReceiptForm::btnPreview_MouseLeave(Object^ s, EventArgs^ e) { btnPreview->BackColor = RF_NAVY(); }
void ReceiptForm::btnClose_MouseEnter(Object^ s, EventArgs^ e) { btnClose->BackColor = RF_BG_LIGHT(); }
void ReceiptForm::btnClose_MouseLeave(Object^ s, EventArgs^ e) { btnClose->BackColor = Color::White; }

// ===== ORIGINAL LOGIC (unchanged) =====
void ReceiptForm::LoadReceiptData() {
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
            if (name->Length > 20) name = name->Substring(0, 20);
            else name = name->PadRight(20);

            String^ qty = Convert::ToInt32(row["Quantity"]).ToString()->PadLeft(4);
            String^ price = Convert::ToDouble(row["Price"]).ToString("F2")->PadLeft(8);
            String^ total = Convert::ToDouble(row["LineTotal"]).ToString("F2")->PadLeft(8);

            sb->AppendLine(name + " " + qty + " " + price + " " + total);
        }
    }
    lblItems->Text = sb->ToString();

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
    PrintDialog^ dialog = gcnew PrintDialog();
    dialog->Document = printDoc;
    if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
        try {
            printDoc->Print();
        }
        catch (Exception^ ex) {
            MessageBox::Show("Printing failed: " + ex->Message,
                "Print Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
}

void ReceiptForm::btnPreview_Click(Object^ sender, EventArgs^ e) {
    PrintPreviewDialog^ preview = gcnew PrintPreviewDialog();
    preview->Document = printDoc;
    preview->Width = 800;
    preview->Height = 700;
    preview->ShowDialog();
}

void ReceiptForm::OnPrintPage(Object^ sender, PrintPageEventArgs^ e) {
    Graphics^ g = e->Graphics;
    System::Drawing::Font^ headerFont = gcnew System::Drawing::Font("Arial", 16, FontStyle::Bold);
    System::Drawing::Font^ subHeaderFont = gcnew System::Drawing::Font("Arial", 10, FontStyle::Italic);
    System::Drawing::Font^ bodyFont = gcnew System::Drawing::Font("Courier New", 10);
    System::Drawing::Font^ boldFont = gcnew System::Drawing::Font("Courier New", 10, FontStyle::Bold);
    System::Drawing::Font^ totalFont = gcnew System::Drawing::Font("Courier New", 12, FontStyle::Bold);

    int x = 50;
    int y = 50;
    int pageWidth = e->MarginBounds.Width;

    StringFormat^ centerFormat = gcnew StringFormat();
    centerFormat->Alignment = StringAlignment::Center;
    System::Drawing::Rectangle headerRect = System::Drawing::Rectangle(x, y, pageWidth, 30);
    g->DrawString("ValueMart", headerFont, Brushes::Black, headerRect, centerFormat);
    y += 35;
    System::Drawing::Rectangle subRect = System::Drawing::Rectangle(x, y, pageWidth, 20);
    g->DrawString("OFFICIAL RECEIPT", subHeaderFont, Brushes::Black, subRect, centerFormat);
    y += 30;

    g->DrawLine(Pens::Black, x, y, x + pageWidth, y);
    y += 10;

    g->DrawString(lblBillNo->Text, bodyFont, Brushes::Black, x, y);
    g->DrawString(lblDate->Text, bodyFont, Brushes::Black, x + 250, y);
    y += 20;
    g->DrawString(lblCashier->Text, bodyFont, Brushes::Black, x, y);
    y += 25;

    g->DrawLine(Pens::Black, x, y, x + pageWidth, y);
    y += 10;

    g->DrawString("Item                 Qty   Price    Total", boldFont, Brushes::Black, x, y);
    y += 18;
    g->DrawLine(Pens::Black, x, y, x + pageWidth, y);
    y += 5;

    array<String^>^ lines = lblItems->Text->Split('\n');
    for (int i = 2; i < lines->Length; i++) {
        String^ line = lines[i]->TrimEnd();
        if (line == "" || line == "\r") continue;
        g->DrawString(line, bodyFont, Brushes::Black, x, y);
        y += 18;
    }

    y += 10;
    g->DrawLine(Pens::Black, x, y, x + pageWidth, y);
    y += 10;

    g->DrawString(lblSubtotal->Text, bodyFont, Brushes::Black, x, y);
    y += 20;
    g->DrawString(lblDiscount->Text, bodyFont, Brushes::Black, x, y);
    y += 20;
    g->DrawString(lblTax->Text, bodyFont, Brushes::Black, x, y);
    y += 20;

    g->DrawLine(Pens::Black, x, y, x + pageWidth, y);
    y += 10;

    g->DrawString(lblGrandTotal->Text, totalFont, Brushes::Black, x, y);
    y += 30;

    g->DrawLine(Pens::Black, x, y, x + pageWidth, y);
    y += 10;

    g->DrawString(lblPayMethod->Text, bodyFont, Brushes::Black, x, y);
    y += 20;
    g->DrawString(lblAmountPaid->Text, bodyFont, Brushes::Black, x, y);
    y += 20;
    if (lblChange->Visible) {
        g->DrawString(lblChange->Text, bodyFont, Brushes::Black, x, y);
        y += 20;
    }

    y += 20;

    System::Drawing::Rectangle thanksRect = System::Drawing::Rectangle(x, y, pageWidth, 25);
    g->DrawString("Thank you for shopping with us!", subHeaderFont, Brushes::Black, thanksRect, centerFormat);

    e->HasMorePages = false;
}

void ReceiptForm::btnClose_Click(Object^ sender, EventArgs^ e) {
    this->Close();
}