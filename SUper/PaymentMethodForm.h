#pragma once
#include "database.h"

namespace SUper {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    public ref class PaymentMethodForm : public System::Windows::Forms::Form
    {
    public:
        PaymentMethodForm(void)
        {
            InitializeComponent();
            ApplyModernStyle();
            LoadReport();
        }

    protected:
        ~PaymentMethodForm()
        {
            if (components) { delete components; }
        }

    private:
        static Color NAVY;
        static Color NAVY_HOVER;
        static Color GREEN_ACCENT;
        static Color BG_LIGHT;
        static Color BORDER_GREY;
        static Color TEXT_DARK;
        static Color TEXT_MUTED;

        static PaymentMethodForm()
        {
            NAVY = Color::FromArgb(30, 58, 138);
            NAVY_HOVER = Color::FromArgb(45, 75, 165);
            GREEN_ACCENT = Color::FromArgb(34, 197, 94);
            BG_LIGHT = Color::FromArgb(248, 250, 252);
            BORDER_GREY = Color::FromArgb(229, 231, 235);
            TEXT_DARK = Color::FromArgb(30, 41, 59);
            TEXT_MUTED = Color::FromArgb(100, 116, 139);
        }

    private: System::Windows::Forms::Label^ lblTitle;
    private: System::Windows::Forms::Label^ lblSubtitle;
    private: System::Windows::Forms::DataGridView^ dgvPayments;
    private: System::Windows::Forms::Label^ lblTotal;
    private: System::Windows::Forms::Button^ btnRefresh;
    private: System::Windows::Forms::Button^ btnClose;

    private: System::Windows::Forms::Panel^ pnlHeader;
    private: System::Windows::Forms::Panel^ pnlGrid;
    private: System::Windows::Forms::Panel^ pnlSummary;
    private: System::Windows::Forms::Label^ lblTotalCaption;
    private: System::Windows::Forms::Label^ btnTopClose;

    private:
        bool dragging;
        Point dragOffset;
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->lblTitle = gcnew Label();
            this->lblSubtitle = gcnew Label();
            this->dgvPayments = gcnew DataGridView();
            this->lblTotal = gcnew Label();
            this->btnRefresh = gcnew Button();
            this->btnClose = gcnew Button();
            this->pnlHeader = gcnew Panel();
            this->pnlGrid = gcnew Panel();
            this->pnlSummary = gcnew Panel();
            this->lblTotalCaption = gcnew Label();
            this->btnTopClose = gcnew Label();
            (cli::safe_cast<ISupportInitialize^>(this->dgvPayments))->BeginInit();
            this->SuspendLayout();

            // ===== HEADER =====
            pnlHeader->Location = Point(0, 0);
            pnlHeader->Size = System::Drawing::Size(900, 80);
            pnlHeader->BackColor = Color::White;
            pnlHeader->Paint += gcnew PaintEventHandler(this, &PaymentMethodForm::pnlHeader_Paint);
            pnlHeader->MouseDown += gcnew MouseEventHandler(this, &PaymentMethodForm::Form_MouseDown);
            pnlHeader->MouseMove += gcnew MouseEventHandler(this, &PaymentMethodForm::Form_MouseMove);
            pnlHeader->MouseUp += gcnew MouseEventHandler(this, &PaymentMethodForm::Form_MouseUp);

            lblTitle->AutoSize = true;
            lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 18.0F, FontStyle::Bold);
            lblTitle->ForeColor = TEXT_DARK;
            lblTitle->BackColor = Color::Transparent;
            lblTitle->Location = Point(30, 18);
            lblTitle->Text = L"Payment Methods";

            lblSubtitle->AutoSize = true;
            lblSubtitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
            lblSubtitle->ForeColor = TEXT_MUTED;
            lblSubtitle->BackColor = Color::Transparent;
            lblSubtitle->Location = Point(32, 50);
            lblSubtitle->Text = L"Approved payments only — cancelled bills excluded";

            btnTopClose->Text = L"\u2715";
            btnTopClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 12.0F, FontStyle::Bold);
            btnTopClose->ForeColor = TEXT_MUTED;
            btnTopClose->BackColor = Color::Transparent;
            btnTopClose->Location = Point(848, 22);
            btnTopClose->Size = System::Drawing::Size(35, 35);
            btnTopClose->TextAlign = ContentAlignment::MiddleCenter;
            btnTopClose->Cursor = Cursors::Hand;
            btnTopClose->Click += gcnew EventHandler(this, &PaymentMethodForm::btnTopClose_Click);
            btnTopClose->MouseEnter += gcnew EventHandler(this, &PaymentMethodForm::btnTopClose_MouseEnter);
            btnTopClose->MouseLeave += gcnew EventHandler(this, &PaymentMethodForm::btnTopClose_MouseLeave);

            pnlHeader->Controls->Add(lblTitle);
            pnlHeader->Controls->Add(lblSubtitle);
            pnlHeader->Controls->Add(btnTopClose);

            // ===== GRID CARD =====
            pnlGrid->Location = Point(20, 95);
            pnlGrid->Size = System::Drawing::Size(860, 360);
            pnlGrid->BackColor = Color::White;
            pnlGrid->Padding = System::Windows::Forms::Padding(1);
            pnlGrid->Paint += gcnew PaintEventHandler(this, &PaymentMethodForm::pnlCard_Paint);

            dgvPayments->AllowUserToAddRows = false;
            dgvPayments->AllowUserToResizeRows = false;
            dgvPayments->ReadOnly = true;
            dgvPayments->BackgroundColor = Color::White;
            dgvPayments->BorderStyle = BorderStyle::None;
            dgvPayments->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
            dgvPayments->GridColor = BORDER_GREY;
            dgvPayments->RowHeadersVisible = false;
            dgvPayments->EnableHeadersVisualStyles = false;
            dgvPayments->ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle::None;
            dgvPayments->ColumnHeadersHeight = 45;
            dgvPayments->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
            dgvPayments->RowTemplate->Height = 38;
            dgvPayments->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            dgvPayments->MultiSelect = false;
            dgvPayments->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            dgvPayments->Dock = DockStyle::Fill;

            DataGridViewCellStyle^ hs = gcnew DataGridViewCellStyle();
            hs->BackColor = NAVY;
            hs->ForeColor = Color::White;
            hs->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
            hs->Alignment = DataGridViewContentAlignment::MiddleLeft;
            hs->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
            hs->SelectionBackColor = NAVY;
            hs->SelectionForeColor = Color::White;
            dgvPayments->ColumnHeadersDefaultCellStyle = hs;

            DataGridViewCellStyle^ cs = gcnew DataGridViewCellStyle();
            cs->BackColor = Color::White;
            cs->ForeColor = TEXT_DARK;
            cs->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
            cs->Alignment = DataGridViewContentAlignment::MiddleLeft;
            cs->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
            cs->SelectionBackColor = Color::FromArgb(219, 234, 254);
            cs->SelectionForeColor = TEXT_DARK;
            dgvPayments->DefaultCellStyle = cs;

            DataGridViewCellStyle^ as_ = gcnew DataGridViewCellStyle();
            as_->BackColor = BG_LIGHT;
            as_->ForeColor = TEXT_DARK;
            as_->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
            as_->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
            as_->SelectionBackColor = Color::FromArgb(219, 234, 254);
            as_->SelectionForeColor = TEXT_DARK;
            dgvPayments->AlternatingRowsDefaultCellStyle = as_;

            dgvPayments->DataBindingComplete +=
                gcnew DataGridViewBindingCompleteEventHandler(this, &PaymentMethodForm::dgv_DataBindingComplete);

            pnlGrid->Controls->Add(dgvPayments);

            // ===== SUMMARY FOOTER =====
            pnlSummary->Location = Point(20, 470);
            pnlSummary->Size = System::Drawing::Size(860, 75);
            pnlSummary->BackColor = Color::White;
            pnlSummary->Paint += gcnew PaintEventHandler(this, &PaymentMethodForm::pnlSummary_Paint);

            lblTotalCaption = gcnew Label();
            lblTotalCaption->AutoSize = true;
            lblTotalCaption->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5F, FontStyle::Bold);
            lblTotalCaption->ForeColor = TEXT_MUTED;
            lblTotalCaption->BackColor = Color::Transparent;
            lblTotalCaption->Location = Point(30, 15);
            lblTotalCaption->Text = L"TOTAL REVENUE";

            lblTotal->AutoSize = true;
            lblTotal->Font = gcnew System::Drawing::Font(L"Segoe UI", 18.0F, FontStyle::Bold);
            lblTotal->ForeColor = NAVY;
            lblTotal->BackColor = Color::Transparent;
            lblTotal->Location = Point(28, 35);
            lblTotal->Text = L"Rs 0.00";

            btnRefresh->Text = L"\u27F3  Refresh";
            btnRefresh->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
            btnRefresh->BackColor = NAVY;
            btnRefresh->ForeColor = Color::White;
            btnRefresh->FlatStyle = FlatStyle::Flat;
            btnRefresh->FlatAppearance->BorderSize = 0;
            btnRefresh->Location = Point(620, 22);
            btnRefresh->Size = System::Drawing::Size(110, 38);
            btnRefresh->Cursor = Cursors::Hand;
            btnRefresh->Click += gcnew EventHandler(this, &PaymentMethodForm::btnRefresh_Click);
            btnRefresh->MouseEnter += gcnew EventHandler(this, &PaymentMethodForm::btnRefresh_MouseEnter);
            btnRefresh->MouseLeave += gcnew EventHandler(this, &PaymentMethodForm::btnRefresh_MouseLeave);

            btnClose->Text = L"Close";
            btnClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
            btnClose->BackColor = Color::White;
            btnClose->ForeColor = TEXT_DARK;
            btnClose->FlatStyle = FlatStyle::Flat;
            btnClose->FlatAppearance->BorderSize = 1;
            btnClose->FlatAppearance->BorderColor = BORDER_GREY;
            btnClose->Location = Point(740, 22);
            btnClose->Size = System::Drawing::Size(100, 38);
            btnClose->Cursor = Cursors::Hand;
            btnClose->Click += gcnew EventHandler(this, &PaymentMethodForm::btnClose_Click);
            btnClose->MouseEnter += gcnew EventHandler(this, &PaymentMethodForm::btnClose_MouseEnter);
            btnClose->MouseLeave += gcnew EventHandler(this, &PaymentMethodForm::btnClose_MouseLeave);

            pnlSummary->Controls->Add(lblTotalCaption);
            pnlSummary->Controls->Add(lblTotal);
            pnlSummary->Controls->Add(btnRefresh);
            pnlSummary->Controls->Add(btnClose);

            // ===== FORM =====
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(900, 565);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->BackColor = BG_LIGHT;
            this->DoubleBuffered = true;
            this->Controls->Add(pnlHeader);
            this->Controls->Add(pnlGrid);
            this->Controls->Add(pnlSummary);
            this->Name = L"PaymentMethodForm";
            this->Text = L"Payment Methods - ValueMart";
            this->Load += gcnew EventHandler(this, &PaymentMethodForm::PaymentMethodForm_Load);
            this->MouseDown += gcnew MouseEventHandler(this, &PaymentMethodForm::Form_MouseDown);
            this->MouseMove += gcnew MouseEventHandler(this, &PaymentMethodForm::Form_MouseMove);
            this->MouseUp += gcnew MouseEventHandler(this, &PaymentMethodForm::Form_MouseUp);
            (cli::safe_cast<ISupportInitialize^>(this->dgvPayments))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private: void ApplyModernStyle() {
        RoundControl(btnRefresh, 6);
        RoundControl(btnClose, 6);
        RoundControl(pnlGrid, 8);
        RoundControl(pnlSummary, 8);
    }

    private: void RoundControl(Control^ ctrl, int radius) {
        GraphicsPath^ path = gcnew GraphicsPath();
        System::Drawing::Rectangle r = ctrl->ClientRectangle;
        path->AddArc(r.X, r.Y, radius, radius, 180, 90);
        path->AddArc(r.Right - radius, r.Y, radius, radius, 270, 90);
        path->AddArc(r.Right - radius, r.Bottom - radius, radius, radius, 0, 90);
        path->AddArc(r.X, r.Bottom - radius, radius, radius, 90, 90);
        path->CloseAllFigures();
        ctrl->Region = gcnew System::Drawing::Region(path);
    }

    private: System::Void pnlHeader_Paint(Object^ s, PaintEventArgs^ e) {
        Pen^ pen = gcnew Pen(BORDER_GREY, 1);
        e->Graphics->DrawLine(pen, 0, pnlHeader->Height - 1, pnlHeader->Width, pnlHeader->Height - 1);
    }
    private: System::Void pnlCard_Paint(Object^ sender, PaintEventArgs^ e) {
        Panel^ p = (Panel^)sender;
        Pen^ pen = gcnew Pen(BORDER_GREY, 1);
        e->Graphics->DrawRectangle(pen, 0, 0, p->Width - 1, p->Height - 1);
    }
    private: System::Void pnlSummary_Paint(Object^ sender, PaintEventArgs^ e) {
        Pen^ pen = gcnew Pen(BORDER_GREY, 1);
        e->Graphics->DrawRectangle(pen, 0, 0, pnlSummary->Width - 1, pnlSummary->Height - 1);
        SolidBrush^ accent = gcnew SolidBrush(GREEN_ACCENT);
        e->Graphics->FillRectangle(accent, 0, 0, 4, pnlSummary->Height);
    }

           // Drag
    private: System::Void Form_MouseDown(Object^ s, MouseEventArgs^ e) {
        if (e->Button == System::Windows::Forms::MouseButtons::Left) {
            dragging = true;
            dragOffset = Point(
                System::Windows::Forms::Cursor::Position.X - this->Location.X,
                System::Windows::Forms::Cursor::Position.Y - this->Location.Y);
        }
    }
    private: System::Void Form_MouseMove(Object^ s, MouseEventArgs^ e) {
        if (dragging) {
            this->Location = Point(
                System::Windows::Forms::Cursor::Position.X - dragOffset.X,
                System::Windows::Forms::Cursor::Position.Y - dragOffset.Y);
        }
    }
    private: System::Void Form_MouseUp(Object^ s, MouseEventArgs^ e) { dragging = false; }

           // Hover
    private: System::Void btnTopClose_Click(Object^ s, EventArgs^ e) { this->Close(); }
    private: System::Void btnTopClose_MouseEnter(Object^ s, EventArgs^ e) {
        btnTopClose->BackColor = Color::FromArgb(239, 68, 68);
        btnTopClose->ForeColor = Color::White;
    }
    private: System::Void btnTopClose_MouseLeave(Object^ s, EventArgs^ e) {
        btnTopClose->BackColor = Color::Transparent;
        btnTopClose->ForeColor = TEXT_MUTED;
    }
    private: System::Void btnRefresh_MouseEnter(Object^ s, EventArgs^ e) { btnRefresh->BackColor = NAVY_HOVER; }
    private: System::Void btnRefresh_MouseLeave(Object^ s, EventArgs^ e) { btnRefresh->BackColor = NAVY; }
    private: System::Void btnClose_MouseEnter(Object^ s, EventArgs^ e) { btnClose->BackColor = BG_LIGHT; }
    private: System::Void btnClose_MouseLeave(Object^ s, EventArgs^ e) { btnClose->BackColor = Color::White; }

           // Column formatting
    private: System::Void dgv_DataBindingComplete(Object^ sender, DataGridViewBindingCompleteEventArgs^ e) {
        array<String^>^ moneyCols = { L"TotalPaid", L"TotalChange", L"BillTotal" };
        for each (String ^ col in moneyCols) {
            if (dgvPayments->Columns->Contains(col)) {
                dgvPayments->Columns[col]->DefaultCellStyle->Format = L"N2";
                dgvPayments->Columns[col]->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleRight;
            }
        }
        if (dgvPayments->Columns->Contains(L"Method")) {
            dgvPayments->Columns[L"Method"]->HeaderText = L"Payment Method";
            dgvPayments->Columns[L"Method"]->DefaultCellStyle->Font =
                gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
        }
        if (dgvPayments->Columns->Contains(L"PaymentCount")) {
            dgvPayments->Columns[L"PaymentCount"]->HeaderText = L"Count";
            dgvPayments->Columns[L"PaymentCount"]->DefaultCellStyle->Alignment =
                DataGridViewContentAlignment::MiddleCenter;
        }
        if (dgvPayments->Columns->Contains(L"TotalPaid")) {
            dgvPayments->Columns[L"TotalPaid"]->HeaderText = L"Paid";
        }
        if (dgvPayments->Columns->Contains(L"TotalChange")) {
            dgvPayments->Columns[L"TotalChange"]->HeaderText = L"Change";
        }
        if (dgvPayments->Columns->Contains(L"BillTotal")) {
            dgvPayments->Columns[L"BillTotal"]->HeaderText = L"Revenue";
            dgvPayments->Columns[L"BillTotal"]->DefaultCellStyle->Font =
                gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
        }
    }

           // ===== ORIGINAL HANDLERS =====
    private: System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e) {
        LoadReport();
    }

    private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Close();
    }

           void LoadReport() {
               DataTable^ result = SBS::Database::ExecuteQuery(
                   "SELECT "
                   "  p.Method, "
                   "  COUNT(*)            AS PaymentCount, "
                   "  SUM(p.AmountPaid)   AS TotalPaid, "
                   "  SUM(p.ChangeAmount) AS TotalChange, "
                   "  SUM(b.Total)        AS BillTotal "
                   "FROM Payments p "
                   "JOIN Bills b ON b.BillNo = p.BillNo "
                   "WHERE p.Status = 'Approved' "
                   "  AND b.IsCancelled = 0 "
                   "GROUP BY p.Method "
                   "ORDER BY BillTotal DESC");

               dgvPayments->DataSource = result;

               if (result == nullptr || result->Rows->Count == 0) {
                   lblTotal->Text = "Rs 0.00";
                   return;
               }

               double total = 0.0;
               for each (DataRow ^ row in result->Rows) {
                   if (row["BillTotal"] != DBNull::Value) {
                       total += Convert::ToDouble(row["BillTotal"]);
                   }
               }
               lblTotal->Text = "Rs " + total.ToString("N2");
           }

    private: System::Void PaymentMethodForm_Load(System::Object^ sender, System::EventArgs^ e) {
    }
    };
}