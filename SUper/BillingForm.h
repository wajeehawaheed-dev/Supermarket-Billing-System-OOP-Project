#pragma once
#include "constants.h"
#include "database.h"
#include "session.h"
#include "PaymentForm.h"

namespace SUper {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;
    using namespace System::Data::SqlClient;

    public ref class BillingForm : public System::Windows::Forms::Form
    {
    public:
        BillingForm(DataGridView^ cartGrid)
        {
            InitializeComponent();
            ApplyModernStyle();
            this->savedCartGrid = cartGrid;

            // Compute totals from the cart grid
            double subtotal = 0;
            int itemCount = 0;
            for (int i = 0; i < cartGrid->Rows->Count; i++) {
                if (!cartGrid->Rows[i]->IsNewRow) {
                    double total = Convert::ToDouble(cartGrid->Rows[i]->Cells["colTotal"]->Value);
                    subtotal += total;
                    itemCount++;
                }
            }

            double discount = 0;
            if (itemCount >= DISCOUNT_THRESHOLD_2)
                discount = subtotal * DISCOUNT_RATE_2;
            else if (itemCount >= DISCOUNT_THRESHOLD_1)
                discount = subtotal * DISCOUNT_RATE_1;

            double tax = (subtotal - discount) * TAX_RATE;
            double grandTotal = subtotal - discount + tax;

            this->totalSubtotal = subtotal;
            this->totalDiscount = discount;
            this->totalTax = tax;
            this->totalGrand = grandTotal;

            // Update labels
            lblItemCount->Text = itemCount.ToString() + " item" + (itemCount == 1 ? "" : "s") + " in cart";
            lblSubtotal->Text = "Rs " + subtotal.ToString("N2");
            lblDiscount->Text = discount > 0 ? ("- Rs " + discount.ToString("N2")) : "Rs 0.00";
            lblTaxCaption->Text = "Tax (" + (TAX_RATE * 100).ToString("F0") + "%)";
            lblTax->Text = "Rs " + tax.ToString("N2");
            lblGrandTotal->Text = "Rs " + grandTotal.ToString("N2");
        }

    protected:
        ~BillingForm() { if (components) delete components; }

    private:
        static Color NAVY;
        static Color NAVY_DARK;
        static Color NAVY_HOVER;
        static Color GREEN_PRIMARY;
        static Color GREEN_HOVER;
        static Color BG_LIGHT;
        static Color BORDER_GREY;
        static Color TEXT_DARK;
        static Color TEXT_MUTED;

        static BillingForm()
        {
            NAVY = Color::FromArgb(30, 58, 138);
            NAVY_DARK = Color::FromArgb(15, 30, 90);
            NAVY_HOVER = Color::FromArgb(45, 75, 165);
            GREEN_PRIMARY = Color::FromArgb(34, 197, 94);
            GREEN_HOVER = Color::FromArgb(22, 163, 74);
            BG_LIGHT = Color::FromArgb(248, 250, 252);
            BORDER_GREY = Color::FromArgb(229, 231, 235);
            TEXT_DARK = Color::FromArgb(30, 41, 59);
            TEXT_MUTED = Color::FromArgb(100, 116, 139);
        }

        System::ComponentModel::Container^ components;
        DataGridView^ savedCartGrid;
        double totalSubtotal;
        double totalDiscount;
        double totalTax;
        double totalGrand;

        // Original control names preserved
        System::Windows::Forms::Label^ lblStoreName;
        System::Windows::Forms::Label^ lblSubtotal;
        System::Windows::Forms::Label^ lblDiscount;
        System::Windows::Forms::Label^ lblTax;
        System::Windows::Forms::Label^ lblGrandTotal;
        System::Windows::Forms::Button^ btnProceed;
        System::Windows::Forms::Panel^ divider;
        System::Windows::Forms::Button^ btnBack;

        // New
        System::Windows::Forms::Panel^ pnlHeader;
        System::Windows::Forms::Panel^ pnlSummaryCard;
        System::Windows::Forms::Label^ lblHeaderSub;
        System::Windows::Forms::Label^ lblItemCount;
        System::Windows::Forms::Label^ lblSubCaption;
        System::Windows::Forms::Label^ lblDiscCaption;
        System::Windows::Forms::Label^ lblTaxCaption;
        System::Windows::Forms::Label^ lblGrandCaption;
        System::Windows::Forms::Label^ btnTopClose;

        bool dragging;
        Point dragOffset;

        void InitializeComponent(void)
        {
            this->lblStoreName = gcnew Label();
            this->lblSubtotal = gcnew Label();
            this->lblDiscount = gcnew Label();
            this->lblTax = gcnew Label();
            this->lblGrandTotal = gcnew Label();
            this->btnProceed = gcnew Button();
            this->btnBack = gcnew Button();
            this->divider = gcnew Panel();
            this->pnlHeader = gcnew Panel();
            this->pnlSummaryCard = gcnew Panel();
            this->lblHeaderSub = gcnew Label();
            this->lblItemCount = gcnew Label();
            this->lblSubCaption = gcnew Label();
            this->lblDiscCaption = gcnew Label();
            this->lblTaxCaption = gcnew Label();
            this->lblGrandCaption = gcnew Label();
            this->btnTopClose = gcnew Label();
            this->SuspendLayout();

            // ===== HEADER =====
            pnlHeader->Location = Point(0, 0);
            pnlHeader->Size = System::Drawing::Size(520, 90);
            pnlHeader->BackColor = NAVY;
            pnlHeader->Paint += gcnew PaintEventHandler(this, &BillingForm::pnlHeader_Paint);
            pnlHeader->MouseDown += gcnew MouseEventHandler(this, &BillingForm::Form_MouseDown);
            pnlHeader->MouseMove += gcnew MouseEventHandler(this, &BillingForm::Form_MouseMove);
            pnlHeader->MouseUp += gcnew MouseEventHandler(this, &BillingForm::Form_MouseUp);

            lblStoreName->Text = "Order Summary";
            lblStoreName->Font = gcnew System::Drawing::Font(L"Segoe UI", 16, FontStyle::Bold);
            lblStoreName->ForeColor = Color::White;
            lblStoreName->BackColor = Color::Transparent;
            lblStoreName->Location = Point(30, 22);
            lblStoreName->AutoSize = true;

            lblHeaderSub->Text = "Review your bill before payment";
            lblHeaderSub->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
            lblHeaderSub->ForeColor = Color::FromArgb(180, 200, 230);
            lblHeaderSub->BackColor = Color::Transparent;
            lblHeaderSub->Location = Point(32, 53);
            lblHeaderSub->AutoSize = true;

            btnTopClose->Text = L"\u2715";
            btnTopClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 12, FontStyle::Bold);
            btnTopClose->ForeColor = Color::FromArgb(180, 200, 230);
            btnTopClose->BackColor = Color::Transparent;
            btnTopClose->Location = Point(470, 22);
            btnTopClose->Size = System::Drawing::Size(35, 35);
            btnTopClose->TextAlign = ContentAlignment::MiddleCenter;
            btnTopClose->Cursor = Cursors::Hand;
            btnTopClose->Click += gcnew EventHandler(this, &BillingForm::btnBack_Click);
            btnTopClose->MouseEnter += gcnew EventHandler(this, &BillingForm::btnTopClose_MouseEnter);
            btnTopClose->MouseLeave += gcnew EventHandler(this, &BillingForm::btnTopClose_MouseLeave);

            pnlHeader->Controls->Add(lblStoreName);
            pnlHeader->Controls->Add(lblHeaderSub);
            pnlHeader->Controls->Add(btnTopClose);

            // ===== SUMMARY CARD =====
            pnlSummaryCard->Location = Point(30, 110);
            pnlSummaryCard->Size = System::Drawing::Size(460, 360);
            pnlSummaryCard->BackColor = Color::White;
            pnlSummaryCard->Paint += gcnew PaintEventHandler(this, &BillingForm::pnlCard_Paint);

            // Item count
            lblItemCount->Text = "0 items in cart";
            lblItemCount->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
            lblItemCount->ForeColor = TEXT_MUTED;
            lblItemCount->BackColor = Color::Transparent;
            lblItemCount->Location = Point(30, 25);
            lblItemCount->AutoSize = true;

            // Subtotal row
            lblSubCaption->Text = "Subtotal";
            lblSubCaption->Font = gcnew System::Drawing::Font(L"Segoe UI", 11);
            lblSubCaption->ForeColor = TEXT_MUTED;
            lblSubCaption->BackColor = Color::Transparent;
            lblSubCaption->Location = Point(30, 70);
            lblSubCaption->AutoSize = true;

            lblSubtotal->Text = "Rs 0.00";
            lblSubtotal->Font = gcnew System::Drawing::Font(L"Segoe UI", 12, FontStyle::Bold);
            lblSubtotal->ForeColor = TEXT_DARK;
            lblSubtotal->BackColor = Color::Transparent;
            lblSubtotal->Location = Point(280, 70);
            lblSubtotal->Size = System::Drawing::Size(155, 25);
            lblSubtotal->TextAlign = ContentAlignment::MiddleRight;

            // Discount row
            lblDiscCaption->Text = "Discount";
            lblDiscCaption->Font = gcnew System::Drawing::Font(L"Segoe UI", 11);
            lblDiscCaption->ForeColor = TEXT_MUTED;
            lblDiscCaption->BackColor = Color::Transparent;
            lblDiscCaption->Location = Point(30, 115);
            lblDiscCaption->AutoSize = true;

            lblDiscount->Text = "Rs 0.00";
            lblDiscount->Font = gcnew System::Drawing::Font(L"Segoe UI", 12, FontStyle::Bold);
            lblDiscount->ForeColor = GREEN_HOVER;
            lblDiscount->BackColor = Color::Transparent;
            lblDiscount->Location = Point(280, 115);
            lblDiscount->Size = System::Drawing::Size(155, 25);
            lblDiscount->TextAlign = ContentAlignment::MiddleRight;

            // Tax row
            lblTaxCaption->Text = "Tax";
            lblTaxCaption->Font = gcnew System::Drawing::Font(L"Segoe UI", 11);
            lblTaxCaption->ForeColor = TEXT_MUTED;
            lblTaxCaption->BackColor = Color::Transparent;
            lblTaxCaption->Location = Point(30, 160);
            lblTaxCaption->AutoSize = true;

            lblTax->Text = "Rs 0.00";
            lblTax->Font = gcnew System::Drawing::Font(L"Segoe UI", 12, FontStyle::Bold);
            lblTax->ForeColor = TEXT_DARK;
            lblTax->BackColor = Color::Transparent;
            lblTax->Location = Point(280, 160);
            lblTax->Size = System::Drawing::Size(155, 25);
            lblTax->TextAlign = ContentAlignment::MiddleRight;

            // Divider
            divider->Location = Point(30, 215);
            divider->Size = System::Drawing::Size(400, 1);
            divider->BackColor = BORDER_GREY;

            // Grand Total
            lblGrandCaption->Text = "GRAND TOTAL";
            lblGrandCaption->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
            lblGrandCaption->ForeColor = TEXT_MUTED;
            lblGrandCaption->BackColor = Color::Transparent;
            lblGrandCaption->Location = Point(30, 240);
            lblGrandCaption->AutoSize = true;

            lblGrandTotal->Text = "Rs 0.00";
            lblGrandTotal->Font = gcnew System::Drawing::Font(L"Segoe UI", 26, FontStyle::Bold);
            lblGrandTotal->ForeColor = NAVY;
            lblGrandTotal->BackColor = Color::Transparent;
            lblGrandTotal->Location = Point(28, 268);
            lblGrandTotal->Size = System::Drawing::Size(405, 60);
            lblGrandTotal->TextAlign = ContentAlignment::MiddleLeft;

            pnlSummaryCard->Controls->Add(lblItemCount);
            pnlSummaryCard->Controls->Add(lblSubCaption);
            pnlSummaryCard->Controls->Add(lblSubtotal);
            pnlSummaryCard->Controls->Add(lblDiscCaption);
            pnlSummaryCard->Controls->Add(lblDiscount);
            pnlSummaryCard->Controls->Add(lblTaxCaption);
            pnlSummaryCard->Controls->Add(lblTax);
            pnlSummaryCard->Controls->Add(divider);
            pnlSummaryCard->Controls->Add(lblGrandCaption);
            pnlSummaryCard->Controls->Add(lblGrandTotal);

            // ===== BUTTONS =====
            btnBack->Text = L"\u2190  Back to Cart  (Esc)";
            btnBack->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
            btnBack->BackColor = Color::White;
            btnBack->ForeColor = TEXT_DARK;
            btnBack->FlatStyle = FlatStyle::Flat;
            btnBack->FlatAppearance->BorderSize = 1;
            btnBack->FlatAppearance->BorderColor = BORDER_GREY;
            btnBack->Location = Point(30, 490);
            btnBack->Size = System::Drawing::Size(180, 50);
            btnBack->Cursor = Cursors::Hand;
            btnBack->Click += gcnew EventHandler(this, &BillingForm::btnBack_Click);
            btnBack->MouseEnter += gcnew EventHandler(this, &BillingForm::btnBack_MouseEnter);
            btnBack->MouseLeave += gcnew EventHandler(this, &BillingForm::btnBack_MouseLeave);

            btnProceed->Text = L"Proceed to Payment  (F4)  \u2192";
            btnProceed->Font = gcnew System::Drawing::Font(L"Segoe UI", 11, FontStyle::Bold);
            btnProceed->BackColor = GREEN_PRIMARY;
            btnProceed->ForeColor = Color::White;
            btnProceed->FlatStyle = FlatStyle::Flat;
            btnProceed->FlatAppearance->BorderSize = 0;
            btnProceed->Location = Point(225, 490);
            btnProceed->Size = System::Drawing::Size(265, 50);
            btnProceed->Cursor = Cursors::Hand;
            btnProceed->Click += gcnew EventHandler(this, &BillingForm::btnProceed_Click);
            btnProceed->MouseEnter += gcnew EventHandler(this, &BillingForm::btnProceed_MouseEnter);
            btnProceed->MouseLeave += gcnew EventHandler(this, &BillingForm::btnProceed_MouseLeave);

            // ===== FORM =====
            this->BackColor = BG_LIGHT;
            this->ClientSize = System::Drawing::Size(520, 570);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->StartPosition = FormStartPosition::CenterScreen;
            this->DoubleBuffered = true;
            this->KeyPreview = true;
            this->Controls->Add(pnlHeader);
            this->Controls->Add(pnlSummaryCard);
            this->Controls->Add(btnBack);
            this->Controls->Add(btnProceed);
            this->Name = L"BillingForm";
            this->Text = L"ValueMart - Billing Summary";
            this->KeyDown += gcnew KeyEventHandler(this, &BillingForm::BillingForm_KeyDown);
            this->MouseDown += gcnew MouseEventHandler(this, &BillingForm::Form_MouseDown);
            this->MouseMove += gcnew MouseEventHandler(this, &BillingForm::Form_MouseMove);
            this->MouseUp += gcnew MouseEventHandler(this, &BillingForm::Form_MouseUp);
            this->Paint += gcnew PaintEventHandler(this, &BillingForm::Form_Paint);
            this->ResumeLayout(false);
        }

        // ===== STYLE HELPERS =====
        void ApplyModernStyle() {
            RoundControl(btnBack, 8);
            RoundControl(btnProceed, 8);
            RoundControl(pnlSummaryCard, 8);
        }

        void RoundControl(Control^ ctrl, int radius) {
            GraphicsPath^ path = gcnew GraphicsPath();
            System::Drawing::Rectangle r = ctrl->ClientRectangle;
            path->AddArc(r.X, r.Y, radius, radius, 180, 90);
            path->AddArc(r.Right - radius, r.Y, radius, radius, 270, 90);
            path->AddArc(r.Right - radius, r.Bottom - radius, radius, radius, 0, 90);
            path->AddArc(r.X, r.Bottom - radius, radius, radius, 90, 90);
            path->CloseAllFigures();
            ctrl->Region = gcnew System::Drawing::Region(path);
        }

        // ===== PAINT =====
        System::Void Form_Paint(Object^ sender, PaintEventArgs^ e) {
            Pen^ pen = gcnew Pen(BORDER_GREY, 1);
            e->Graphics->DrawRectangle(pen, 0, 0, this->Width - 1, this->Height - 1);
        }
        System::Void pnlHeader_Paint(Object^ sender, PaintEventArgs^ e) {
            e->Graphics->SmoothingMode = SmoothingMode::AntiAlias;
            LinearGradientBrush^ brush = gcnew LinearGradientBrush(
                pnlHeader->ClientRectangle, NAVY, NAVY_DARK, 90.0f);
            e->Graphics->FillRectangle(brush, pnlHeader->ClientRectangle);
        }
        System::Void pnlCard_Paint(Object^ sender, PaintEventArgs^ e) {
            Panel^ p = (Panel^)sender;
            Pen^ pen = gcnew Pen(BORDER_GREY, 1);
            e->Graphics->DrawRectangle(pen, 0, 0, p->Width - 1, p->Height - 1);
        }

        // ===== DRAG =====
        System::Void Form_MouseDown(Object^ s, MouseEventArgs^ e) {
            if (e->Button == System::Windows::Forms::MouseButtons::Left) {
                dragging = true;
                dragOffset = Point(
                    System::Windows::Forms::Cursor::Position.X - this->Location.X,
                    System::Windows::Forms::Cursor::Position.Y - this->Location.Y);
            }
        }
        System::Void Form_MouseMove(Object^ s, MouseEventArgs^ e) {
            if (dragging) {
                this->Location = Point(
                    System::Windows::Forms::Cursor::Position.X - dragOffset.X,
                    System::Windows::Forms::Cursor::Position.Y - dragOffset.Y);
            }
        }
        System::Void Form_MouseUp(Object^ s, MouseEventArgs^ e) { dragging = false; }

        // ===== HOVER =====
        System::Void btnTopClose_MouseEnter(Object^ s, EventArgs^ e) {
            btnTopClose->BackColor = Color::FromArgb(220, 38, 38);
            btnTopClose->ForeColor = Color::White;
        }
        System::Void btnTopClose_MouseLeave(Object^ s, EventArgs^ e) {
            btnTopClose->BackColor = Color::Transparent;
            btnTopClose->ForeColor = Color::FromArgb(180, 200, 230);
        }
        System::Void btnBack_MouseEnter(Object^ s, EventArgs^ e) { btnBack->BackColor = BG_LIGHT; }
        System::Void btnBack_MouseLeave(Object^ s, EventArgs^ e) { btnBack->BackColor = Color::White; }
        System::Void btnProceed_MouseEnter(Object^ s, EventArgs^ e) { btnProceed->BackColor = GREEN_HOVER; }
        System::Void btnProceed_MouseLeave(Object^ s, EventArgs^ e) { btnProceed->BackColor = GREEN_PRIMARY; }

        // ===== ORIGINAL HANDLERS =====
        System::Void btnBack_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }

        System::Void btnProceed_Click(System::Object^ sender, System::EventArgs^ e) {
            int userID = SBS::Session::IsLoggedIn() ? SBS::Session::GetUserID() : 1;

            Object^ result = SBS::Database::ExecuteScalar(
                "INSERT INTO Bills (Date, UserID, Subtotal, Discount, Tax, Total) "
                "VALUES (GETDATE(), @uid, @sub, @disc, @tax, @tot); "
                "SELECT SCOPE_IDENTITY();",
                gcnew SqlParameter("@uid", userID),
                gcnew SqlParameter("@sub", totalSubtotal),
                gcnew SqlParameter("@disc", totalDiscount),
                gcnew SqlParameter("@tax", totalTax),
                gcnew SqlParameter("@tot", totalGrand));

            if (result == nullptr || result == System::DBNull::Value) {
                MessageBox::Show("Failed to save bill!", "Error");
                return;
            }

            int billNo = Convert::ToInt32(result);

            for (int i = 0; i < savedCartGrid->Rows->Count; i++) {
                if (savedCartGrid->Rows[i]->IsNewRow) continue;

                int productID = Convert::ToInt32(savedCartGrid->Rows[i]->Cells["colID"]->Value);
                int qty = Convert::ToInt32(savedCartGrid->Rows[i]->Cells["colQty"]->Value);
                double price = Convert::ToDouble(savedCartGrid->Rows[i]->Cells["colPrice"]->Value);

                SBS::Database::ExecuteNonQuery(
                    "INSERT INTO BillItems (BillNo, ProductID, Quantity, Price) "
                    "VALUES (@bill, @prod, @qty, @price)",
                    gcnew SqlParameter("@bill", billNo),
                    gcnew SqlParameter("@prod", productID),
                    gcnew SqlParameter("@qty", qty),
                    gcnew SqlParameter("@price", price));

                SBS::Database::ExecuteNonQuery(
                    "UPDATE Products SET Stock = Stock - @qty WHERE ProductID = @prod",
                    gcnew SqlParameter("@qty", qty),
                    gcnew SqlParameter("@prod", productID));
            }

            savedCartGrid->Rows->Clear();

            PaymentForm^ paymentForm = gcnew PaymentForm(billNo, totalGrand);
            paymentForm->ShowDialog();
            this->Close();
        }

        System::Void BillingForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
            if (e->KeyCode == Keys::F4)     btnProceed->PerformClick();
            if (e->KeyCode == Keys::Escape) btnBack->PerformClick();
            e->Handled = true;
        }
    };
}