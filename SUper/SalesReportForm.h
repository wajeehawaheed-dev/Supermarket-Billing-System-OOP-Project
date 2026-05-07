#pragma once
#include "database.h"

namespace SUper {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Data::SqlClient;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    public ref class SalesReportForm : public System::Windows::Forms::Form
    {
    public:
        SalesReportForm(void)
        {
            InitializeComponent();
            ApplyModernStyle();
            dtpFrom->Value = DateTime::Now.AddDays(-30);
            dtpTo->Value = DateTime::Now;
            LoadReport();
        }

    protected:
        ~SalesReportForm()
        {
            if (components) { delete components; }
        }

        // ===== Brand palette =====
    private:
        static Color NAVY;
        static Color NAVY_DARK;
        static Color NAVY_HOVER;
        static Color GREEN_ACCENT;
        static Color BG_LIGHT;
        static Color BG_HEADER;
        static Color BORDER_GREY;
        static Color TEXT_DARK;
        static Color TEXT_MUTED;

        static SalesReportForm()
        {
            NAVY = Color::FromArgb(30, 58, 138);
            NAVY_DARK = Color::FromArgb(15, 30, 90);
            NAVY_HOVER = Color::FromArgb(45, 75, 165);
            GREEN_ACCENT = Color::FromArgb(34, 197, 94);
            BG_LIGHT = Color::FromArgb(248, 250, 252);
            BG_HEADER = Color::FromArgb(241, 245, 249);
            BORDER_GREY = Color::FromArgb(229, 231, 235);
            TEXT_DARK = Color::FromArgb(30, 41, 59);
            TEXT_MUTED = Color::FromArgb(100, 116, 139);
        }

        // ===== Original controls (names preserved) =====
    private: System::Windows::Forms::Label^ lblTitle;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::DateTimePicker^ dtpFrom;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::DateTimePicker^ dtpTo;
    private: System::Windows::Forms::Button^ btnGenerate;
    private: System::Windows::Forms::DataGridView^ dataGridView1;
    private: System::Windows::Forms::Label^ lblTotalRevenue;
    private: System::Windows::Forms::Button^ btnClose;

           // ===== New layout controls =====
    private: System::Windows::Forms::Panel^ pnlHeader;
    private: System::Windows::Forms::Panel^ pnlFilter;
    private: System::Windows::Forms::Panel^ pnlGrid;
    private: System::Windows::Forms::Panel^ pnlSummary;
    private: System::Windows::Forms::Label^ lblSubtitle;
    private: System::Windows::Forms::Label^ lblRevenueCaption;
    private: System::Windows::Forms::Label^ btnTopClose;

    private:
        bool dragging;
        Point dragOffset;
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->lblTitle = gcnew Label();
            this->label1 = gcnew Label();
            this->dtpFrom = gcnew DateTimePicker();
            this->label2 = gcnew Label();
            this->dtpTo = gcnew DateTimePicker();
            this->btnGenerate = gcnew Button();
            this->dataGridView1 = gcnew DataGridView();
            this->lblTotalRevenue = gcnew Label();
            this->btnClose = gcnew Button();
            this->pnlHeader = gcnew Panel();
            this->pnlFilter = gcnew Panel();
            this->pnlGrid = gcnew Panel();
            this->pnlSummary = gcnew Panel();
            this->lblSubtitle = gcnew Label();
            this->lblRevenueCaption = gcnew Label();
            this->btnTopClose = gcnew Label();
            (cli::safe_cast<ISupportInitialize^>(this->dataGridView1))->BeginInit();
            this->SuspendLayout();

            // ============ HEADER BAR ============
            this->pnlHeader->Location = Point(0, 0);
            this->pnlHeader->Size = System::Drawing::Size(900, 80);
            this->pnlHeader->BackColor = Color::White;
            this->pnlHeader->Paint += gcnew PaintEventHandler(this, &SalesReportForm::pnlHeader_Paint);
            this->pnlHeader->MouseDown += gcnew MouseEventHandler(this, &SalesReportForm::Form_MouseDown);
            this->pnlHeader->MouseMove += gcnew MouseEventHandler(this, &SalesReportForm::Form_MouseMove);
            this->pnlHeader->MouseUp += gcnew MouseEventHandler(this, &SalesReportForm::Form_MouseUp);

            this->lblTitle->AutoSize = true;
            this->lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 18.0F, FontStyle::Bold);
            this->lblTitle->ForeColor = TEXT_DARK;
            this->lblTitle->BackColor = Color::Transparent;
            this->lblTitle->Location = Point(30, 18);
            this->lblTitle->Text = L"Sales Reports";

            this->lblSubtitle->AutoSize = true;
            this->lblSubtitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
            this->lblSubtitle->ForeColor = TEXT_MUTED;
            this->lblSubtitle->BackColor = Color::Transparent;
            this->lblSubtitle->Location = Point(32, 50);
            this->lblSubtitle->Text = L"Daily breakdown of sales activity";

            this->btnTopClose->Text = L"\u2715";
            this->btnTopClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 12.0F, FontStyle::Bold);
            this->btnTopClose->ForeColor = TEXT_MUTED;
            this->btnTopClose->BackColor = Color::Transparent;
            this->btnTopClose->Location = Point(848, 22);
            this->btnTopClose->Size = System::Drawing::Size(35, 35);
            this->btnTopClose->TextAlign = ContentAlignment::MiddleCenter;
            this->btnTopClose->Cursor = Cursors::Hand;
            this->btnTopClose->Click += gcnew EventHandler(this, &SalesReportForm::btnTopClose_Click);
            this->btnTopClose->MouseEnter += gcnew EventHandler(this, &SalesReportForm::btnTopClose_MouseEnter);
            this->btnTopClose->MouseLeave += gcnew EventHandler(this, &SalesReportForm::btnTopClose_MouseLeave);

            this->pnlHeader->Controls->Add(this->lblTitle);
            this->pnlHeader->Controls->Add(this->lblSubtitle);
            this->pnlHeader->Controls->Add(this->btnTopClose);

            // ============ FILTER CARD ============
            this->pnlFilter->Location = Point(20, 95);
            this->pnlFilter->Size = System::Drawing::Size(860, 75);
            this->pnlFilter->BackColor = Color::White;
            this->pnlFilter->Paint += gcnew PaintEventHandler(this, &SalesReportForm::pnlCard_Paint);

            // From
            this->label1->AutoSize = true;
            this->label1->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5F, FontStyle::Bold);
            this->label1->ForeColor = TEXT_MUTED;
            this->label1->Location = Point(25, 15);
            this->label1->Text = L"FROM";

            this->dtpFrom->Format = DateTimePickerFormat::Custom;
            this->dtpFrom->CustomFormat = L"MMM dd, yyyy";
            this->dtpFrom->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F);
            this->dtpFrom->Location = Point(25, 35);
            this->dtpFrom->Size = System::Drawing::Size(200, 24);
            this->dtpFrom->CalendarFont = gcnew System::Drawing::Font(L"Segoe UI", 9.0F);

            // To
            this->label2->AutoSize = true;
            this->label2->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5F, FontStyle::Bold);
            this->label2->ForeColor = TEXT_MUTED;
            this->label2->Location = Point(255, 15);
            this->label2->Text = L"TO";

            this->dtpTo->Format = DateTimePickerFormat::Custom;
            this->dtpTo->CustomFormat = L"MMM dd, yyyy";
            this->dtpTo->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F);
            this->dtpTo->Location = Point(255, 35);
            this->dtpTo->Size = System::Drawing::Size(200, 24);
            this->dtpTo->CalendarFont = gcnew System::Drawing::Font(L"Segoe UI", 9.0F);

            // Generate
            this->btnGenerate->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
            this->btnGenerate->BackColor = NAVY;
            this->btnGenerate->ForeColor = Color::White;
            this->btnGenerate->FlatStyle = FlatStyle::Flat;
            this->btnGenerate->FlatAppearance->BorderSize = 0;
            this->btnGenerate->Location = Point(720, 30);
            this->btnGenerate->Size = System::Drawing::Size(120, 38);
            this->btnGenerate->Text = L"Generate";
            this->btnGenerate->Cursor = Cursors::Hand;
            this->btnGenerate->Click += gcnew EventHandler(this, &SalesReportForm::btnGenerate_Click);
            this->btnGenerate->MouseEnter += gcnew EventHandler(this, &SalesReportForm::btnGenerate_MouseEnter);
            this->btnGenerate->MouseLeave += gcnew EventHandler(this, &SalesReportForm::btnGenerate_MouseLeave);

            this->pnlFilter->Controls->Add(this->label1);
            this->pnlFilter->Controls->Add(this->dtpFrom);
            this->pnlFilter->Controls->Add(this->label2);
            this->pnlFilter->Controls->Add(this->dtpTo);
            this->pnlFilter->Controls->Add(this->btnGenerate);

            // ============ DATA GRID CARD ============
            this->pnlGrid->Location = Point(20, 185);
            this->pnlGrid->Size = System::Drawing::Size(860, 320);
            this->pnlGrid->BackColor = Color::White;
            this->pnlGrid->Padding = System::Windows::Forms::Padding(1);
            this->pnlGrid->Paint += gcnew PaintEventHandler(this, &SalesReportForm::pnlCard_Paint);

            this->dataGridView1->AllowUserToAddRows = false;
            this->dataGridView1->AllowUserToResizeRows = false;
            this->dataGridView1->ReadOnly = true;
            this->dataGridView1->BackgroundColor = Color::White;
            this->dataGridView1->BorderStyle = BorderStyle::None;
            this->dataGridView1->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
            this->dataGridView1->GridColor = BORDER_GREY;
            this->dataGridView1->RowHeadersVisible = false;
            this->dataGridView1->EnableHeadersVisualStyles = false;
            this->dataGridView1->ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle::None;
            this->dataGridView1->ColumnHeadersHeight = 45;
            this->dataGridView1->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
            this->dataGridView1->RowTemplate->Height = 38;
            this->dataGridView1->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            this->dataGridView1->MultiSelect = false;
            this->dataGridView1->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            this->dataGridView1->Dock = DockStyle::Fill;

            // Header style
            DataGridViewCellStyle^ headerStyle = gcnew DataGridViewCellStyle();
            headerStyle->BackColor = NAVY;
            headerStyle->ForeColor = Color::White;
            headerStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
            headerStyle->Alignment = DataGridViewContentAlignment::MiddleLeft;
            headerStyle->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
            headerStyle->SelectionBackColor = NAVY;
            headerStyle->SelectionForeColor = Color::White;
            this->dataGridView1->ColumnHeadersDefaultCellStyle = headerStyle;

            // Cell style
            DataGridViewCellStyle^ cellStyle = gcnew DataGridViewCellStyle();
            cellStyle->BackColor = Color::White;
            cellStyle->ForeColor = TEXT_DARK;
            cellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
            cellStyle->Alignment = DataGridViewContentAlignment::MiddleLeft;
            cellStyle->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
            cellStyle->SelectionBackColor = Color::FromArgb(219, 234, 254);
            cellStyle->SelectionForeColor = TEXT_DARK;
            this->dataGridView1->DefaultCellStyle = cellStyle;

            // Alternating rows
            DataGridViewCellStyle^ altStyle = gcnew DataGridViewCellStyle();
            altStyle->BackColor = BG_LIGHT;
            altStyle->ForeColor = TEXT_DARK;
            altStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
            altStyle->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
            altStyle->SelectionBackColor = Color::FromArgb(219, 234, 254);
            altStyle->SelectionForeColor = TEXT_DARK;
            this->dataGridView1->AlternatingRowsDefaultCellStyle = altStyle;

            // Auto-format columns when data is bound
            this->dataGridView1->DataBindingComplete +=
                gcnew DataGridViewBindingCompleteEventHandler(this, &SalesReportForm::dataGridView1_DataBindingComplete);

            this->pnlGrid->Controls->Add(this->dataGridView1);

            // ============ SUMMARY FOOTER ============
            this->pnlSummary->Location = Point(20, 520);
            this->pnlSummary->Size = System::Drawing::Size(860, 75);
            this->pnlSummary->BackColor = Color::White;
            this->pnlSummary->Paint += gcnew PaintEventHandler(this, &SalesReportForm::pnlSummary_Paint);

            this->lblRevenueCaption->AutoSize = true;
            this->lblRevenueCaption->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5F, FontStyle::Bold);
            this->lblRevenueCaption->ForeColor = TEXT_MUTED;
            this->lblRevenueCaption->BackColor = Color::Transparent;
            this->lblRevenueCaption->Location = Point(30, 15);
            this->lblRevenueCaption->Text = L"TOTAL REVENUE";

            this->lblTotalRevenue->AutoSize = true;
            this->lblTotalRevenue->Font = gcnew System::Drawing::Font(L"Segoe UI", 18.0F, FontStyle::Bold);
            this->lblTotalRevenue->ForeColor = NAVY;
            this->lblTotalRevenue->BackColor = Color::Transparent;
            this->lblTotalRevenue->Location = Point(28, 35);
            this->lblTotalRevenue->Text = L"Rs 0.00";

            this->btnClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
            this->btnClose->BackColor = Color::White;
            this->btnClose->ForeColor = TEXT_DARK;
            this->btnClose->FlatStyle = FlatStyle::Flat;
            this->btnClose->FlatAppearance->BorderSize = 1;
            this->btnClose->FlatAppearance->BorderColor = BORDER_GREY;
            this->btnClose->Location = Point(740, 22);
            this->btnClose->Size = System::Drawing::Size(100, 38);
            this->btnClose->Text = L"Close";
            this->btnClose->Cursor = Cursors::Hand;
            this->btnClose->Click += gcnew EventHandler(this, &SalesReportForm::btnClose_Click);
            this->btnClose->MouseEnter += gcnew EventHandler(this, &SalesReportForm::btnClose_MouseEnter);
            this->btnClose->MouseLeave += gcnew EventHandler(this, &SalesReportForm::btnClose_MouseLeave);

            this->pnlSummary->Controls->Add(this->lblRevenueCaption);
            this->pnlSummary->Controls->Add(this->lblTotalRevenue);
            this->pnlSummary->Controls->Add(this->btnClose);

            // ============ FORM ============
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(900, 615);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->BackColor = BG_LIGHT;
            this->DoubleBuffered = true;
            this->Controls->Add(this->pnlHeader);
            this->Controls->Add(this->pnlFilter);
            this->Controls->Add(this->pnlGrid);
            this->Controls->Add(this->pnlSummary);
            this->Name = L"SalesReportForm";
            this->Text = L"Sales Report - ValueMart";
            this->MouseDown += gcnew MouseEventHandler(this, &SalesReportForm::Form_MouseDown);
            this->MouseMove += gcnew MouseEventHandler(this, &SalesReportForm::Form_MouseMove);
            this->MouseUp += gcnew MouseEventHandler(this, &SalesReportForm::Form_MouseUp);
            this->Load += gcnew EventHandler(this, &SalesReportForm::SalesReportForm_Load);
            (cli::safe_cast<ISupportInitialize^>(this->dataGridView1))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

        // ============ STYLE HELPERS ============
    private: void ApplyModernStyle() {
        RoundControl(btnGenerate, 6);
        RoundControl(btnClose, 6);
        RoundControl(pnlFilter, 8);
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

           // ============ PAINT ============
    private: System::Void pnlHeader_Paint(Object^ sender, PaintEventArgs^ e) {
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
        // Green accent bar on left
        SolidBrush^ accent = gcnew SolidBrush(GREEN_ACCENT);
        e->Graphics->FillRectangle(accent, 0, 0, 4, pnlSummary->Height);
    }

           // ============ DRAG ============
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

           // ============ HOVER HANDLERS ============
    private: System::Void btnTopClose_Click(Object^ sender, EventArgs^ e) {
        this->Close();
    }
    private: System::Void btnTopClose_MouseEnter(Object^ sender, EventArgs^ e) {
        btnTopClose->BackColor = Color::FromArgb(239, 68, 68);
        btnTopClose->ForeColor = Color::White;
    }
    private: System::Void btnTopClose_MouseLeave(Object^ sender, EventArgs^ e) {
        btnTopClose->BackColor = Color::Transparent;
        btnTopClose->ForeColor = TEXT_MUTED;
    }

    private: System::Void btnGenerate_MouseEnter(Object^ sender, EventArgs^ e) {
        btnGenerate->BackColor = NAVY_HOVER;
    }
    private: System::Void btnGenerate_MouseLeave(Object^ sender, EventArgs^ e) {
        btnGenerate->BackColor = NAVY;
    }

    private: System::Void btnClose_MouseEnter(Object^ sender, EventArgs^ e) {
        btnClose->BackColor = BG_LIGHT;
    }
    private: System::Void btnClose_MouseLeave(Object^ sender, EventArgs^ e) {
        btnClose->BackColor = Color::White;
    }

           // ============ AUTO-FORMAT GRID COLUMNS ============
    private: System::Void dataGridView1_DataBindingComplete(Object^ sender, DataGridViewBindingCompleteEventArgs^ e) {
        array<String^>^ moneyCols = { L"Subtotal", L"TotalDiscount", L"TotalTax", L"Revenue" };
        for each (String ^ col in moneyCols) {
            if (dataGridView1->Columns->Contains(col)) {
                dataGridView1->Columns[col]->DefaultCellStyle->Format = L"N2";
                dataGridView1->Columns[col]->DefaultCellStyle->Alignment =
                    DataGridViewContentAlignment::MiddleRight;
            }
        }
        if (dataGridView1->Columns->Contains(L"SaleDate")) {
            dataGridView1->Columns[L"SaleDate"]->DefaultCellStyle->Format = L"MMM dd, yyyy";
            dataGridView1->Columns[L"SaleDate"]->HeaderText = L"Date";
        }
        if (dataGridView1->Columns->Contains(L"TotalBills")) {
            dataGridView1->Columns[L"TotalBills"]->DefaultCellStyle->Alignment =
                DataGridViewContentAlignment::MiddleCenter;
            dataGridView1->Columns[L"TotalBills"]->HeaderText = L"Bills";
        }
        if (dataGridView1->Columns->Contains(L"TotalDiscount")) {
            dataGridView1->Columns[L"TotalDiscount"]->HeaderText = L"Discount";
        }
        if (dataGridView1->Columns->Contains(L"TotalTax")) {
            dataGridView1->Columns[L"TotalTax"]->HeaderText = L"Tax";
        }
    }

           // ============ ORIGINAL HANDLERS (preserved) ============
    private: System::Void btnGenerate_Click(System::Object^ sender, System::EventArgs^ e) {
        LoadReport();
    }

    private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Close();
    }

           void LoadReport() {
               if (dtpFrom->Value.Date > dtpTo->Value.Date) {
                   MessageBox::Show("'From' date must be before or equal to 'To' date.",
                       "Invalid Date Range",
                       MessageBoxButtons::OK,
                       MessageBoxIcon::Warning);
                   return;
               }

               DataTable^ result = SBS::Database::ExecuteQuery(
                   "SELECT "
                   "  CAST(Date AS DATE)  AS SaleDate, "
                   "  COUNT(*)            AS TotalBills, "
                   "  SUM(Subtotal)       AS Subtotal, "
                   "  SUM(Discount)       AS TotalDiscount, "
                   "  SUM(Tax)            AS TotalTax, "
                   "  SUM(Total)          AS Revenue "
                   "FROM Bills "
                   "WHERE IsCancelled = 0 "
                   "  AND CAST(Date AS DATE) BETWEEN @StartDate AND @EndDate "
                   "GROUP BY CAST(Date AS DATE) "
                   "ORDER BY SaleDate DESC",
                   gcnew SqlParameter("@StartDate", dtpFrom->Value.Date),
                   gcnew SqlParameter("@EndDate", dtpTo->Value.Date));

               dataGridView1->DataSource = result;

               if (result == nullptr || result->Rows->Count == 0) {
                   lblTotalRevenue->Text = "Rs 0.00";
                   return;
               }

               double total = 0.0;
               for each (DataRow ^ row in result->Rows) {
                   if (row["Revenue"] != DBNull::Value) {
                       total += Convert::ToDouble(row["Revenue"]);
                   }
               }
               lblTotalRevenue->Text = "Rs " + total.ToString("N2");
           }

    private: System::Void SalesReportForm_Load(System::Object^ sender, System::EventArgs^ e) {
    }
    };
}