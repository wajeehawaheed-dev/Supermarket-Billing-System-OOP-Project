#pragma once
#include "constants.h"
#include "database.h"

namespace SUper {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;
    using namespace System::Data;
    using namespace System::Data::SqlClient;

    public ref class SettingsForm : public System::Windows::Forms::Form
    {
    public:
        SettingsForm(void)
        {
            InitializeComponent();
            ApplyModernStyle();
            txtTax->Text = TAX_RATE.ToString();
            txtThreshold1->Text = DISCOUNT_THRESHOLD_1.ToString();
            txtDiscount1->Text = DISCOUNT_RATE_1.ToString();
            txtThreshold2->Text = DISCOUNT_THRESHOLD_2.ToString();
            txtDiscount2->Text = DISCOUNT_RATE_2.ToString();
        }

    protected:
        ~SettingsForm() { if (components) delete components; }

    private:
        static Color NAVY;
        static Color NAVY_HOVER;
        static Color BG_LIGHT;
        static Color BORDER_GREY;
        static Color TEXT_DARK;
        static Color TEXT_MUTED;
        static Color GROUP_BG;

        static SettingsForm()
        {
            NAVY = Color::FromArgb(30, 58, 138);
            NAVY_HOVER = Color::FromArgb(45, 75, 165);
            BG_LIGHT = Color::FromArgb(248, 250, 252);
            BORDER_GREY = Color::FromArgb(229, 231, 235);
            TEXT_DARK = Color::FromArgb(30, 41, 59);
            TEXT_MUTED = Color::FromArgb(100, 116, 139);
            GROUP_BG = Color::FromArgb(252, 253, 254);
        }

        System::ComponentModel::Container^ components;
        Label^ lblTitle;
        Label^ lblTax;
        Label^ lblDiscount1;
        Label^ lblDiscount2;
        Label^ lblThreshold1;
        Label^ lblThreshold2;
        TextBox^ txtTax;
        TextBox^ txtDiscount1;
        TextBox^ txtDiscount2;
        TextBox^ txtThreshold1;
        TextBox^ txtThreshold2;
        Button^ btnSave;
        Button^ btnCancel;

        Label^ btnTopClose;
        Panel^ pnlTaxCard;
        Panel^ pnlTier1Card;
        Panel^ pnlTier2Card;
        Panel^ pnlTaxLine;
        Panel^ pnlT1Line;
        Panel^ pnlD1Line;
        Panel^ pnlT2Line;
        Panel^ pnlD2Line;

        bool dragging;
        Point dragOffset;

        void InitializeComponent(void)
        {
            this->lblTitle = gcnew Label();
            this->lblTax = gcnew Label();
            this->lblDiscount1 = gcnew Label();
            this->lblDiscount2 = gcnew Label();
            this->lblThreshold1 = gcnew Label();
            this->lblThreshold2 = gcnew Label();
            this->txtTax = gcnew TextBox();
            this->txtDiscount1 = gcnew TextBox();
            this->txtDiscount2 = gcnew TextBox();
            this->txtThreshold1 = gcnew TextBox();
            this->txtThreshold2 = gcnew TextBox();
            this->btnSave = gcnew Button();
            this->btnCancel = gcnew Button();
            this->btnTopClose = gcnew Label();
            this->pnlTaxCard = gcnew Panel();
            this->pnlTier1Card = gcnew Panel();
            this->pnlTier2Card = gcnew Panel();
            this->pnlTaxLine = gcnew Panel();
            this->pnlT1Line = gcnew Panel();
            this->pnlD1Line = gcnew Panel();
            this->pnlT2Line = gcnew Panel();
            this->pnlD2Line = gcnew Panel();
            this->SuspendLayout();

            this->Text = "ValueMart - Admin Settings";
            this->ClientSize = System::Drawing::Size(560, 700);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->BackColor = Color::White;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->DoubleBuffered = true;

            // ===== TITLE =====
            lblTitle->Text = "Settings";
            lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 18.0F, FontStyle::Bold);
            lblTitle->ForeColor = TEXT_DARK;
            lblTitle->BackColor = Color::Transparent;
            lblTitle->Location = Point(35, 25);
            lblTitle->AutoSize = true;

            Label^ lblSub = gcnew Label();
            lblSub->Text = "Tax rate and discount tiers";
            lblSub->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
            lblSub->ForeColor = TEXT_MUTED;
            lblSub->BackColor = Color::Transparent;
            lblSub->Location = Point(37, 57);
            lblSub->AutoSize = true;

            btnTopClose->Text = L"\u2715";
            btnTopClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 12.0F, FontStyle::Bold);
            btnTopClose->ForeColor = TEXT_MUTED;
            btnTopClose->BackColor = Color::Transparent;
            btnTopClose->Location = Point(508, 22);
            btnTopClose->Size = System::Drawing::Size(35, 30);
            btnTopClose->TextAlign = ContentAlignment::MiddleCenter;
            btnTopClose->Cursor = Cursors::Hand;
            btnTopClose->Click += gcnew EventHandler(this, &SettingsForm::btnCancel_Click);
            btnTopClose->MouseEnter += gcnew EventHandler(this, &SettingsForm::btnTopClose_MouseEnter);
            btnTopClose->MouseLeave += gcnew EventHandler(this, &SettingsForm::btnTopClose_MouseLeave);

            // ===== TAX CARD =====
            pnlTaxCard->Location = Point(35, 105);
            pnlTaxCard->Size = System::Drawing::Size(490, 100);
            pnlTaxCard->BackColor = GROUP_BG;
            pnlTaxCard->Paint += gcnew PaintEventHandler(this, &SettingsForm::pnlCard_Paint);

            Label^ lblTaxGroup = gcnew Label();
            lblTaxGroup->Text = L"\U0001F4B0  TAX RATE";
            lblTaxGroup->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Bold);
            lblTaxGroup->ForeColor = NAVY;
            lblTaxGroup->BackColor = Color::Transparent;
            lblTaxGroup->Location = Point(20, 15);
            lblTaxGroup->AutoSize = true;

            lblTax->Text = "Applied to all bills (e.g. 0.17 = 17%)";
            lblTax->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5F);
            lblTax->ForeColor = TEXT_MUTED;
            lblTax->BackColor = Color::Transparent;
            lblTax->Location = Point(22, 38);
            lblTax->AutoSize = true;

            txtTax->BorderStyle = BorderStyle::None;
            txtTax->Font = gcnew System::Drawing::Font(L"Segoe UI", 12.0F);
            txtTax->ForeColor = TEXT_DARK;
            txtTax->BackColor = GROUP_BG;
            txtTax->Location = Point(22, 60);
            txtTax->Size = System::Drawing::Size(440, 24);
            txtTax->Enter += gcnew EventHandler(this, &SettingsForm::txtTax_Enter);
            txtTax->Leave += gcnew EventHandler(this, &SettingsForm::txtTax_Leave);

            pnlTaxLine->Location = Point(22, 87);
            pnlTaxLine->Size = System::Drawing::Size(445, 2);
            pnlTaxLine->BackColor = BORDER_GREY;

            pnlTaxCard->Controls->Add(lblTaxGroup);
            pnlTaxCard->Controls->Add(lblTax);
            pnlTaxCard->Controls->Add(txtTax);
            pnlTaxCard->Controls->Add(pnlTaxLine);

            // ===== TIER 1 DISCOUNT CARD =====
            pnlTier1Card->Location = Point(35, 220);
            pnlTier1Card->Size = System::Drawing::Size(490, 165);
            pnlTier1Card->BackColor = GROUP_BG;
            pnlTier1Card->Paint += gcnew PaintEventHandler(this, &SettingsForm::pnlCard_Paint);

            Label^ lblTier1Group = gcnew Label();
            lblTier1Group->Text = L"\U0001F3F7\uFE0F  TIER 1 DISCOUNT";
            lblTier1Group->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Bold);
            lblTier1Group->ForeColor = NAVY;
            lblTier1Group->BackColor = Color::Transparent;
            lblTier1Group->Location = Point(20, 15);
            lblTier1Group->AutoSize = true;

            // Threshold 1
            lblThreshold1->Text = "MIN ITEMS";
            lblThreshold1->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5F, FontStyle::Bold);
            lblThreshold1->ForeColor = TEXT_MUTED;
            lblThreshold1->BackColor = Color::Transparent;
            lblThreshold1->Location = Point(22, 45);
            lblThreshold1->AutoSize = true;

            txtThreshold1->BorderStyle = BorderStyle::None;
            txtThreshold1->Font = gcnew System::Drawing::Font(L"Segoe UI", 12.0F);
            txtThreshold1->ForeColor = TEXT_DARK;
            txtThreshold1->BackColor = GROUP_BG;
            txtThreshold1->Location = Point(22, 65);
            txtThreshold1->Size = System::Drawing::Size(200, 24);
            txtThreshold1->Enter += gcnew EventHandler(this, &SettingsForm::txtT1_Enter);
            txtThreshold1->Leave += gcnew EventHandler(this, &SettingsForm::txtT1_Leave);

            pnlT1Line->Location = Point(22, 92);
            pnlT1Line->Size = System::Drawing::Size(200, 2);
            pnlT1Line->BackColor = BORDER_GREY;

            // Discount 1
            lblDiscount1->Text = "DISCOUNT RATE";
            lblDiscount1->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5F, FontStyle::Bold);
            lblDiscount1->ForeColor = TEXT_MUTED;
            lblDiscount1->BackColor = Color::Transparent;
            lblDiscount1->Location = Point(255, 45);
            lblDiscount1->AutoSize = true;

            txtDiscount1->BorderStyle = BorderStyle::None;
            txtDiscount1->Font = gcnew System::Drawing::Font(L"Segoe UI", 12.0F);
            txtDiscount1->ForeColor = TEXT_DARK;
            txtDiscount1->BackColor = GROUP_BG;
            txtDiscount1->Location = Point(255, 65);
            txtDiscount1->Size = System::Drawing::Size(200, 24);
            txtDiscount1->Enter += gcnew EventHandler(this, &SettingsForm::txtD1_Enter);
            txtDiscount1->Leave += gcnew EventHandler(this, &SettingsForm::txtD1_Leave);

            pnlD1Line->Location = Point(255, 92);
            pnlD1Line->Size = System::Drawing::Size(212, 2);
            pnlD1Line->BackColor = BORDER_GREY;

            Label^ lblTier1Hint = gcnew Label();
            lblTier1Hint->Text = "When the cart has at least this many items, apply this rate (e.g. 0.10 = 10% off)";
            lblTier1Hint->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.0F);
            lblTier1Hint->ForeColor = TEXT_MUTED;
            lblTier1Hint->BackColor = Color::Transparent;
            lblTier1Hint->Location = Point(22, 120);
            lblTier1Hint->Size = System::Drawing::Size(450, 30);

            pnlTier1Card->Controls->Add(lblTier1Group);
            pnlTier1Card->Controls->Add(lblThreshold1);
            pnlTier1Card->Controls->Add(txtThreshold1);
            pnlTier1Card->Controls->Add(pnlT1Line);
            pnlTier1Card->Controls->Add(lblDiscount1);
            pnlTier1Card->Controls->Add(txtDiscount1);
            pnlTier1Card->Controls->Add(pnlD1Line);
            pnlTier1Card->Controls->Add(lblTier1Hint);

            // ===== TIER 2 DISCOUNT CARD =====
            pnlTier2Card->Location = Point(35, 400);
            pnlTier2Card->Size = System::Drawing::Size(490, 165);
            pnlTier2Card->BackColor = GROUP_BG;
            pnlTier2Card->Paint += gcnew PaintEventHandler(this, &SettingsForm::pnlCard_Paint);

            Label^ lblTier2Group = gcnew Label();
            lblTier2Group->Text = L"\U0001F3C6  TIER 2 DISCOUNT";
            lblTier2Group->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Bold);
            lblTier2Group->ForeColor = NAVY;
            lblTier2Group->BackColor = Color::Transparent;
            lblTier2Group->Location = Point(20, 15);
            lblTier2Group->AutoSize = true;

            lblThreshold2->Text = "MIN ITEMS";
            lblThreshold2->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5F, FontStyle::Bold);
            lblThreshold2->ForeColor = TEXT_MUTED;
            lblThreshold2->BackColor = Color::Transparent;
            lblThreshold2->Location = Point(22, 45);
            lblThreshold2->AutoSize = true;

            txtThreshold2->BorderStyle = BorderStyle::None;
            txtThreshold2->Font = gcnew System::Drawing::Font(L"Segoe UI", 12.0F);
            txtThreshold2->ForeColor = TEXT_DARK;
            txtThreshold2->BackColor = GROUP_BG;
            txtThreshold2->Location = Point(22, 65);
            txtThreshold2->Size = System::Drawing::Size(200, 24);
            txtThreshold2->Enter += gcnew EventHandler(this, &SettingsForm::txtT2_Enter);
            txtThreshold2->Leave += gcnew EventHandler(this, &SettingsForm::txtT2_Leave);

            pnlT2Line->Location = Point(22, 92);
            pnlT2Line->Size = System::Drawing::Size(200, 2);
            pnlT2Line->BackColor = BORDER_GREY;

            lblDiscount2->Text = "DISCOUNT RATE";
            lblDiscount2->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5F, FontStyle::Bold);
            lblDiscount2->ForeColor = TEXT_MUTED;
            lblDiscount2->BackColor = Color::Transparent;
            lblDiscount2->Location = Point(255, 45);
            lblDiscount2->AutoSize = true;

            txtDiscount2->BorderStyle = BorderStyle::None;
            txtDiscount2->Font = gcnew System::Drawing::Font(L"Segoe UI", 12.0F);
            txtDiscount2->ForeColor = TEXT_DARK;
            txtDiscount2->BackColor = GROUP_BG;
            txtDiscount2->Location = Point(255, 65);
            txtDiscount2->Size = System::Drawing::Size(200, 24);
            txtDiscount2->Enter += gcnew EventHandler(this, &SettingsForm::txtD2_Enter);
            txtDiscount2->Leave += gcnew EventHandler(this, &SettingsForm::txtD2_Leave);

            pnlD2Line->Location = Point(255, 92);
            pnlD2Line->Size = System::Drawing::Size(212, 2);
            pnlD2Line->BackColor = BORDER_GREY;

            Label^ lblTier2Hint = gcnew Label();
            lblTier2Hint->Text = "Higher tier — must be greater than Tier 1's threshold and rate";
            lblTier2Hint->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.0F);
            lblTier2Hint->ForeColor = TEXT_MUTED;
            lblTier2Hint->BackColor = Color::Transparent;
            lblTier2Hint->Location = Point(22, 120);
            lblTier2Hint->Size = System::Drawing::Size(450, 30);

            pnlTier2Card->Controls->Add(lblTier2Group);
            pnlTier2Card->Controls->Add(lblThreshold2);
            pnlTier2Card->Controls->Add(txtThreshold2);
            pnlTier2Card->Controls->Add(pnlT2Line);
            pnlTier2Card->Controls->Add(lblDiscount2);
            pnlTier2Card->Controls->Add(txtDiscount2);
            pnlTier2Card->Controls->Add(pnlD2Line);
            pnlTier2Card->Controls->Add(lblTier2Hint);

            // ===== BUTTONS =====
            btnSave->Text = "Save Settings  (F4)";
            btnSave->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
            btnSave->BackColor = NAVY;
            btnSave->ForeColor = Color::White;
            btnSave->FlatStyle = FlatStyle::Flat;
            btnSave->FlatAppearance->BorderSize = 0;
            btnSave->Location = Point(305, 615);
            btnSave->Size = System::Drawing::Size(220, 44);
            btnSave->Cursor = Cursors::Hand;
            btnSave->Click += gcnew EventHandler(this, &SettingsForm::btnSave_Click);
            btnSave->MouseEnter += gcnew EventHandler(this, &SettingsForm::btnSave_MouseEnter);
            btnSave->MouseLeave += gcnew EventHandler(this, &SettingsForm::btnSave_MouseLeave);

            btnCancel->Text = "Cancel  (Esc)";
            btnCancel->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F);
            btnCancel->BackColor = Color::White;
            btnCancel->ForeColor = TEXT_DARK;
            btnCancel->FlatStyle = FlatStyle::Flat;
            btnCancel->FlatAppearance->BorderSize = 1;
            btnCancel->FlatAppearance->BorderColor = BORDER_GREY;
            btnCancel->Location = Point(35, 615);
            btnCancel->Size = System::Drawing::Size(150, 44);
            btnCancel->Cursor = Cursors::Hand;
            btnCancel->Click += gcnew EventHandler(this, &SettingsForm::btnCancel_Click);
            btnCancel->MouseEnter += gcnew EventHandler(this, &SettingsForm::btnCancel_MouseEnter);
            btnCancel->MouseLeave += gcnew EventHandler(this, &SettingsForm::btnCancel_MouseLeave);

            // ===== ADD TO FORM =====
            this->Controls->Add(lblTitle);
            this->Controls->Add(lblSub);
            this->Controls->Add(btnTopClose);
            this->Controls->Add(pnlTaxCard);
            this->Controls->Add(pnlTier1Card);
            this->Controls->Add(pnlTier2Card);
            this->Controls->Add(btnSave);
            this->Controls->Add(btnCancel);

            this->KeyPreview = true;
            this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SettingsForm::SettingsForm_KeyDown);
            this->MouseDown += gcnew MouseEventHandler(this, &SettingsForm::Form_MouseDown);
            this->MouseMove += gcnew MouseEventHandler(this, &SettingsForm::Form_MouseMove);
            this->MouseUp += gcnew MouseEventHandler(this, &SettingsForm::Form_MouseUp);
            this->Paint += gcnew PaintEventHandler(this, &SettingsForm::Form_Paint);

            this->ResumeLayout(false);
        }

    private:
        void ApplyModernStyle() {
            RoundControl(btnSave, 6);
            RoundControl(btnCancel, 6);
            RoundControl(pnlTaxCard, 8);
            RoundControl(pnlTier1Card, 8);
            RoundControl(pnlTier2Card, 8);
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

        System::Void Form_Paint(Object^ sender, PaintEventArgs^ e) {
            Pen^ pen = gcnew Pen(BORDER_GREY, 1);
            e->Graphics->DrawRectangle(pen, 0, 0, this->Width - 1, this->Height - 1);
        }
        System::Void pnlCard_Paint(Object^ sender, PaintEventArgs^ e) {
            Panel^ p = (Panel^)sender;
            Pen^ pen = gcnew Pen(BORDER_GREY, 1);
            e->Graphics->DrawRectangle(pen, 0, 0, p->Width - 1, p->Height - 1);
        }

        // Drag
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

        // Field focus
        System::Void txtTax_Enter(Object^ s, EventArgs^ e) { pnlTaxLine->BackColor = NAVY; }
        System::Void txtTax_Leave(Object^ s, EventArgs^ e) { pnlTaxLine->BackColor = BORDER_GREY; }
        System::Void txtT1_Enter(Object^ s, EventArgs^ e) { pnlT1Line->BackColor = NAVY; }
        System::Void txtT1_Leave(Object^ s, EventArgs^ e) { pnlT1Line->BackColor = BORDER_GREY; }
        System::Void txtD1_Enter(Object^ s, EventArgs^ e) { pnlD1Line->BackColor = NAVY; }
        System::Void txtD1_Leave(Object^ s, EventArgs^ e) { pnlD1Line->BackColor = BORDER_GREY; }
        System::Void txtT2_Enter(Object^ s, EventArgs^ e) { pnlT2Line->BackColor = NAVY; }
        System::Void txtT2_Leave(Object^ s, EventArgs^ e) { pnlT2Line->BackColor = BORDER_GREY; }
        System::Void txtD2_Enter(Object^ s, EventArgs^ e) { pnlD2Line->BackColor = NAVY; }
        System::Void txtD2_Leave(Object^ s, EventArgs^ e) { pnlD2Line->BackColor = BORDER_GREY; }

        // Hover
        System::Void btnSave_MouseEnter(Object^ s, EventArgs^ e) { btnSave->BackColor = NAVY_HOVER; }
        System::Void btnSave_MouseLeave(Object^ s, EventArgs^ e) { btnSave->BackColor = NAVY; }
        System::Void btnCancel_MouseEnter(Object^ s, EventArgs^ e) { btnCancel->BackColor = BG_LIGHT; }
        System::Void btnCancel_MouseLeave(Object^ s, EventArgs^ e) { btnCancel->BackColor = Color::White; }
        System::Void btnTopClose_MouseEnter(Object^ s, EventArgs^ e) {
            btnTopClose->BackColor = Color::FromArgb(239, 68, 68);
            btnTopClose->ForeColor = Color::White;
        }
        System::Void btnTopClose_MouseLeave(Object^ s, EventArgs^ e) {
            btnTopClose->BackColor = Color::Transparent;
            btnTopClose->ForeColor = TEXT_MUTED;
        }

        // ===== ORIGINAL HANDLERS =====
        System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
            double tax, d1, d2;
            int t1, t2;

            if (!Double::TryParse(txtTax->Text, tax) || tax <= 0 || tax >= 1) {
                MessageBox::Show("Invalid tax rate! Must be between 0 and 1 (e.g. 0.17)", "Error"); return;
            }
            if (!Int32::TryParse(txtThreshold1->Text, t1) || t1 <= 0) {
                MessageBox::Show("Invalid Discount 1 threshold!", "Error"); return;
            }
            if (!Double::TryParse(txtDiscount1->Text, d1) || d1 <= 0 || d1 >= 1) {
                MessageBox::Show("Invalid Discount 1 rate! Must be between 0 and 1", "Error"); return;
            }
            if (!Int32::TryParse(txtThreshold2->Text, t2) || t2 <= t1) {
                MessageBox::Show("Discount 2 threshold must be greater than Discount 1!", "Error"); return;
            }
            if (!Double::TryParse(txtDiscount2->Text, d2) || d2 <= d1 || d2 >= 1) {
                MessageBox::Show("Discount 2 rate must be greater than Discount 1 and less than 1!", "Error"); return;
            }

            TAX_RATE = tax;
            DISCOUNT_THRESHOLD_1 = t1;
            DISCOUNT_RATE_1 = d1;
            DISCOUNT_THRESHOLD_2 = t2;
            DISCOUNT_RATE_2 = d2;

            SBS::Database::ExecuteNonQuery(
                "UPDATE Settings SET SettingValue = @v WHERE SettingName = @k",
                gcnew SqlParameter("@v", tax.ToString()),
                gcnew SqlParameter("@k", "TAX_RATE"));
            SBS::Database::ExecuteNonQuery(
                "UPDATE Settings SET SettingValue = @v WHERE SettingName = @k",
                gcnew SqlParameter("@v", t1.ToString()),
                gcnew SqlParameter("@k", "DISCOUNT_THRESHOLD_1"));
            SBS::Database::ExecuteNonQuery(
                "UPDATE Settings SET SettingValue = @v WHERE SettingName = @k",
                gcnew SqlParameter("@v", d1.ToString()),
                gcnew SqlParameter("@k", "DISCOUNT_RATE_1"));
            SBS::Database::ExecuteNonQuery(
                "UPDATE Settings SET SettingValue = @v WHERE SettingName = @k",
                gcnew SqlParameter("@v", t2.ToString()),
                gcnew SqlParameter("@k", "DISCOUNT_THRESHOLD_2"));
            SBS::Database::ExecuteNonQuery(
                "UPDATE Settings SET SettingValue = @v WHERE SettingName = @k",
                gcnew SqlParameter("@v", d2.ToString()),
                gcnew SqlParameter("@k", "DISCOUNT_RATE_2"));

            MessageBox::Show("Settings saved successfully!", "Success");
            this->Close();
        }

        System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }

    private: System::Void SettingsForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
        if (e->KeyCode == Keys::F4)     btnSave->PerformClick();
        if (e->KeyCode == Keys::Escape) btnCancel->PerformClick();
        e->Handled = true;
    }
    };
}