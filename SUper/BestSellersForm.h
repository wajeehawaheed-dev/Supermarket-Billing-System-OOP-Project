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

    public ref class BestSellersForm : public System::Windows::Forms::Form
    {
    public:
        BestSellersForm(void)
        {
            InitializeComponent();
            ApplyModernStyle();
            LoadReport();
        }

    protected:
        ~BestSellersForm()
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

        static BestSellersForm()
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
    private: System::Windows::Forms::DataGridView^ dgvBestSellers;
    private: System::Windows::Forms::Button^ btnRefresh;
    private: System::Windows::Forms::Button^ btnClose;

    private: System::Windows::Forms::Panel^ pnlHeader;
    private: System::Windows::Forms::Panel^ pnlGrid;
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
            this->dgvBestSellers = gcnew DataGridView();
            this->btnRefresh = gcnew Button();
            this->btnClose = gcnew Button();
            this->pnlHeader = gcnew Panel();
            this->pnlGrid = gcnew Panel();
            this->btnTopClose = gcnew Label();
            (cli::safe_cast<ISupportInitialize^>(this->dgvBestSellers))->BeginInit();
            this->SuspendLayout();

            // ===== HEADER =====
            this->pnlHeader->Location = Point(0, 0);
            this->pnlHeader->Size = System::Drawing::Size(900, 80);
            this->pnlHeader->BackColor = Color::White;
            this->pnlHeader->Paint += gcnew PaintEventHandler(this, &BestSellersForm::pnlHeader_Paint);
            this->pnlHeader->MouseDown += gcnew MouseEventHandler(this, &BestSellersForm::Form_MouseDown);
            this->pnlHeader->MouseMove += gcnew MouseEventHandler(this, &BestSellersForm::Form_MouseMove);
            this->pnlHeader->MouseUp += gcnew MouseEventHandler(this, &BestSellersForm::Form_MouseUp);

            this->lblTitle->AutoSize = true;
            this->lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 18.0F, FontStyle::Bold);
            this->lblTitle->ForeColor = TEXT_DARK;
            this->lblTitle->BackColor = Color::Transparent;
            this->lblTitle->Location = Point(30, 18);
            this->lblTitle->Text = L"Best Sellers";

            this->lblSubtitle->AutoSize = true;
            this->lblSubtitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
            this->lblSubtitle->ForeColor = TEXT_MUTED;
            this->lblSubtitle->BackColor = Color::Transparent;
            this->lblSubtitle->Location = Point(32, 50);
            this->lblSubtitle->Text = L"Ranked by units sold (excludes cancelled bills)";

            this->btnTopClose->Text = L"\u2715";
            this->btnTopClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 12.0F, FontStyle::Bold);
            this->btnTopClose->ForeColor = TEXT_MUTED;
            this->btnTopClose->BackColor = Color::Transparent;
            this->btnTopClose->Location = Point(848, 22);
            this->btnTopClose->Size = System::Drawing::Size(35, 35);
            this->btnTopClose->TextAlign = ContentAlignment::MiddleCenter;
            this->btnTopClose->Cursor = Cursors::Hand;
            this->btnTopClose->Click += gcnew EventHandler(this, &BestSellersForm::btnTopClose_Click);
            this->btnTopClose->MouseEnter += gcnew EventHandler(this, &BestSellersForm::btnTopClose_MouseEnter);
            this->btnTopClose->MouseLeave += gcnew EventHandler(this, &BestSellersForm::btnTopClose_MouseLeave);

            this->pnlHeader->Controls->Add(this->lblTitle);
            this->pnlHeader->Controls->Add(this->lblSubtitle);
            this->pnlHeader->Controls->Add(this->btnTopClose);

            // ===== GRID CARD =====
            this->pnlGrid->Location = Point(20, 95);
            this->pnlGrid->Size = System::Drawing::Size(860, 410);
            this->pnlGrid->BackColor = Color::White;
            this->pnlGrid->Padding = System::Windows::Forms::Padding(1);
            this->pnlGrid->Paint += gcnew PaintEventHandler(this, &BestSellersForm::pnlCard_Paint);

            StyleGrid(this->dgvBestSellers);
            this->dgvBestSellers->DataBindingComplete +=
                gcnew DataGridViewBindingCompleteEventHandler(this, &BestSellersForm::dgv_DataBindingComplete);
            this->pnlGrid->Controls->Add(this->dgvBestSellers);

            // ===== BUTTONS =====
            this->btnRefresh->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
            this->btnRefresh->BackColor = NAVY;
            this->btnRefresh->ForeColor = Color::White;
            this->btnRefresh->FlatStyle = FlatStyle::Flat;
            this->btnRefresh->FlatAppearance->BorderSize = 0;
            this->btnRefresh->Location = Point(660, 525);
            this->btnRefresh->Size = System::Drawing::Size(110, 38);
            this->btnRefresh->Text = L"\u27F3  Refresh";
            this->btnRefresh->Cursor = Cursors::Hand;
            this->btnRefresh->Click += gcnew EventHandler(this, &BestSellersForm::btnRefresh_Click);
            this->btnRefresh->MouseEnter += gcnew EventHandler(this, &BestSellersForm::btnRefresh_MouseEnter);
            this->btnRefresh->MouseLeave += gcnew EventHandler(this, &BestSellersForm::btnRefresh_MouseLeave);

            this->btnClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
            this->btnClose->BackColor = Color::White;
            this->btnClose->ForeColor = TEXT_DARK;
            this->btnClose->FlatStyle = FlatStyle::Flat;
            this->btnClose->FlatAppearance->BorderSize = 1;
            this->btnClose->FlatAppearance->BorderColor = BORDER_GREY;
            this->btnClose->Location = Point(780, 525);
            this->btnClose->Size = System::Drawing::Size(100, 38);
            this->btnClose->Text = L"Close";
            this->btnClose->Cursor = Cursors::Hand;
            this->btnClose->Click += gcnew EventHandler(this, &BestSellersForm::btnClose_Click);
            this->btnClose->MouseEnter += gcnew EventHandler(this, &BestSellersForm::btnClose_MouseEnter);
            this->btnClose->MouseLeave += gcnew EventHandler(this, &BestSellersForm::btnClose_MouseLeave);

            // ===== FORM =====
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(900, 580);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->BackColor = BG_LIGHT;
            this->DoubleBuffered = true;
            this->Controls->Add(this->pnlHeader);
            this->Controls->Add(this->pnlGrid);
            this->Controls->Add(this->btnRefresh);
            this->Controls->Add(this->btnClose);
            this->Name = L"BestSellersForm";
            this->Text = L"Best Sellers - ValueMart";
            this->Load += gcnew EventHandler(this, &BestSellersForm::BestSellersForm_Load);
            this->MouseDown += gcnew MouseEventHandler(this, &BestSellersForm::Form_MouseDown);
            this->MouseMove += gcnew MouseEventHandler(this, &BestSellersForm::Form_MouseMove);
            this->MouseUp += gcnew MouseEventHandler(this, &BestSellersForm::Form_MouseUp);
            (cli::safe_cast<ISupportInitialize^>(this->dgvBestSellers))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private: void StyleGrid(DataGridView^ grid) {
        grid->AllowUserToAddRows = false;
        grid->AllowUserToResizeRows = false;
        grid->ReadOnly = true;
        grid->BackgroundColor = Color::White;
        grid->BorderStyle = BorderStyle::None;
        grid->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
        grid->GridColor = BORDER_GREY;
        grid->RowHeadersVisible = false;
        grid->EnableHeadersVisualStyles = false;
        grid->ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle::None;
        grid->ColumnHeadersHeight = 45;
        grid->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
        grid->RowTemplate->Height = 38;
        grid->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
        grid->MultiSelect = false;
        grid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
        grid->Dock = DockStyle::Fill;

        DataGridViewCellStyle^ headerStyle = gcnew DataGridViewCellStyle();
        headerStyle->BackColor = NAVY;
        headerStyle->ForeColor = Color::White;
        headerStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
        headerStyle->Alignment = DataGridViewContentAlignment::MiddleLeft;
        headerStyle->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
        headerStyle->SelectionBackColor = NAVY;
        headerStyle->SelectionForeColor = Color::White;
        grid->ColumnHeadersDefaultCellStyle = headerStyle;

        DataGridViewCellStyle^ cellStyle = gcnew DataGridViewCellStyle();
        cellStyle->BackColor = Color::White;
        cellStyle->ForeColor = TEXT_DARK;
        cellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
        cellStyle->Alignment = DataGridViewContentAlignment::MiddleLeft;
        cellStyle->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
        cellStyle->SelectionBackColor = Color::FromArgb(219, 234, 254);
        cellStyle->SelectionForeColor = TEXT_DARK;
        grid->DefaultCellStyle = cellStyle;

        DataGridViewCellStyle^ altStyle = gcnew DataGridViewCellStyle();
        altStyle->BackColor = BG_LIGHT;
        altStyle->ForeColor = TEXT_DARK;
        altStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
        altStyle->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
        altStyle->SelectionBackColor = Color::FromArgb(219, 234, 254);
        altStyle->SelectionForeColor = TEXT_DARK;
        grid->AlternatingRowsDefaultCellStyle = altStyle;
    }

    private: void ApplyModernStyle() {
        RoundControl(btnRefresh, 6);
        RoundControl(btnClose, 6);
        RoundControl(pnlGrid, 8);
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

    private: System::Void pnlHeader_Paint(Object^ sender, PaintEventArgs^ e) {
        Pen^ pen = gcnew Pen(BORDER_GREY, 1);
        e->Graphics->DrawLine(pen, 0, pnlHeader->Height - 1, pnlHeader->Width, pnlHeader->Height - 1);
    }

    private: System::Void pnlCard_Paint(Object^ sender, PaintEventArgs^ e) {
        Panel^ p = (Panel^)sender;
        Pen^ pen = gcnew Pen(BORDER_GREY, 1);
        e->Graphics->DrawRectangle(pen, 0, 0, p->Width - 1, p->Height - 1);
    }

    private: System::Void Form_MouseDown(Object^ sender, MouseEventArgs^ e) {
        if (e->Button == System::Windows::Forms::MouseButtons::Left) {
            dragging = true;
            dragOffset = Point(
                System::Windows::Forms::Cursor::Position.X - this->Location.X,
                System::Windows::Forms::Cursor::Position.Y - this->Location.Y);
        }
    }
    private: System::Void Form_MouseMove(Object^ sender, MouseEventArgs^ e) {
        if (dragging) {
            this->Location = Point(
                System::Windows::Forms::Cursor::Position.X - dragOffset.X,
                System::Windows::Forms::Cursor::Position.Y - dragOffset.Y);
        }
    }
    private: System::Void Form_MouseUp(Object^ sender, MouseEventArgs^ e) {
        dragging = false;
    }

    private: System::Void btnTopClose_Click(Object^ sender, EventArgs^ e) { this->Close(); }
    private: System::Void btnTopClose_MouseEnter(Object^ sender, EventArgs^ e) {
        btnTopClose->BackColor = Color::FromArgb(239, 68, 68);
        btnTopClose->ForeColor = Color::White;
    }
    private: System::Void btnTopClose_MouseLeave(Object^ sender, EventArgs^ e) {
        btnTopClose->BackColor = Color::Transparent;
        btnTopClose->ForeColor = TEXT_MUTED;
    }
    private: System::Void btnRefresh_MouseEnter(Object^ sender, EventArgs^ e) {
        btnRefresh->BackColor = NAVY_HOVER;
    }
    private: System::Void btnRefresh_MouseLeave(Object^ sender, EventArgs^ e) {
        btnRefresh->BackColor = NAVY;
    }
    private: System::Void btnClose_MouseEnter(Object^ sender, EventArgs^ e) {
        btnClose->BackColor = BG_LIGHT;
    }
    private: System::Void btnClose_MouseLeave(Object^ sender, EventArgs^ e) {
        btnClose->BackColor = Color::White;
    }

    private: System::Void dgv_DataBindingComplete(Object^ sender, DataGridViewBindingCompleteEventArgs^ e) {
        if (dgvBestSellers->Columns->Contains(L"ProductName")) {
            dgvBestSellers->Columns[L"ProductName"]->HeaderText = L"Product";
        }
        if (dgvBestSellers->Columns->Contains(L"Category")) {
            dgvBestSellers->Columns[L"Category"]->HeaderText = L"Category";
        }
        if (dgvBestSellers->Columns->Contains(L"UnitsSold")) {
            dgvBestSellers->Columns[L"UnitsSold"]->HeaderText = L"Units Sold";
            dgvBestSellers->Columns[L"UnitsSold"]->DefaultCellStyle->Alignment =
                DataGridViewContentAlignment::MiddleCenter;
            dgvBestSellers->Columns[L"UnitsSold"]->DefaultCellStyle->Font =
                gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
        }
        if (dgvBestSellers->Columns->Contains(L"Revenue")) {
            dgvBestSellers->Columns[L"Revenue"]->HeaderText = L"Revenue";
            dgvBestSellers->Columns[L"Revenue"]->DefaultCellStyle->Format = L"N2";
            dgvBestSellers->Columns[L"Revenue"]->DefaultCellStyle->Alignment =
                DataGridViewContentAlignment::MiddleRight;
        }
        if (dgvBestSellers->Columns->Contains(L"BillCount")) {
            dgvBestSellers->Columns[L"BillCount"]->HeaderText = L"Bills";
            dgvBestSellers->Columns[L"BillCount"]->DefaultCellStyle->Alignment =
                DataGridViewContentAlignment::MiddleCenter;
        }
    }

           // ===== ORIGINAL HANDLERS (preserved) =====
    private: System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e) {
        LoadReport();
    }

    private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Close();
    }

           void LoadReport() {
               DataTable^ result = SBS::Database::ExecuteQuery(
                   "SELECT "
                   "  p.Name           AS ProductName, "
                   "  p.Category, "
                   "  SUM(bi.Quantity) AS UnitsSold, "
                   "  SUM(bi.Quantity * bi.Price) AS Revenue, "
                   "  COUNT(DISTINCT bi.BillNo)   AS BillCount "
                   "FROM BillItems bi "
                   "JOIN Products p ON p.ProductID = bi.ProductID "
                   "JOIN Bills b    ON b.BillNo    = bi.BillNo "
                   "WHERE b.IsCancelled = 0 "
                   "GROUP BY p.ProductID, p.Name, p.Category "
                   "ORDER BY UnitsSold DESC");

               dgvBestSellers->DataSource = result;
           }

    private: System::Void BestSellersForm_Load(System::Object^ sender, System::EventArgs^ e) {
    }
    };
}