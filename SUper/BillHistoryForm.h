#pragma once
#include "database.h"

namespace SUper {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Data::SqlClient;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    public ref class BillHistoryForm : public Form
    {
    public:
        BillHistoryForm(void)
        {
            InitializeComponent();
            ApplyModernStyle();
            LoadBills();
        }

    protected:
        ~BillHistoryForm()
        {
            if (components) delete components;
        }

    private:
        static Color NAVY;
        static Color NAVY_HOVER;
        static Color RED_DANGER;
        static Color RED_DANGER_HOVER;
        static Color BG_LIGHT;
        static Color BORDER_GREY;
        static Color TEXT_DARK;
        static Color TEXT_MUTED;

        static BillHistoryForm()
        {
            NAVY = Color::FromArgb(30, 58, 138);
            NAVY_HOVER = Color::FromArgb(45, 75, 165);
            RED_DANGER = Color::FromArgb(220, 38, 38);
            RED_DANGER_HOVER = Color::FromArgb(185, 28, 28);
            BG_LIGHT = Color::FromArgb(248, 250, 252);
            BORDER_GREY = Color::FromArgb(229, 231, 235);
            TEXT_DARK = Color::FromArgb(30, 41, 59);
            TEXT_MUTED = Color::FromArgb(100, 116, 139);
        }

        System::ComponentModel::Container^ components;
        Label^ lblTitle;
        Label^ lblSubtitle;
        DataGridView^ dgvBills;
        Button^ btnCancel;
        Button^ btnRefresh;
        Button^ btnClose;
        Panel^ pnlHeader;
        Panel^ pnlGrid;
        Label^ btnTopClose;

        bool dragging;
        Point dragOffset;

        void InitializeComponent(void)
        {
            this->pnlHeader = gcnew Panel();
            this->pnlGrid = gcnew Panel();
            this->lblTitle = gcnew Label();
            this->lblSubtitle = gcnew Label();
            this->dgvBills = gcnew DataGridView();
            this->btnCancel = gcnew Button();
            this->btnRefresh = gcnew Button();
            this->btnClose = gcnew Button();
            this->btnTopClose = gcnew Label();
            (cli::safe_cast<ISupportInitialize^>(this->dgvBills))->BeginInit();
            this->SuspendLayout();

            // ===== HEADER =====
            pnlHeader->Location = Point(0, 0);
            pnlHeader->Size = System::Drawing::Size(1000, 80);
            pnlHeader->BackColor = Color::White;
            pnlHeader->Paint += gcnew PaintEventHandler(this, &BillHistoryForm::pnlHeader_Paint);
            pnlHeader->MouseDown += gcnew MouseEventHandler(this, &BillHistoryForm::Form_MouseDown);
            pnlHeader->MouseMove += gcnew MouseEventHandler(this, &BillHistoryForm::Form_MouseMove);
            pnlHeader->MouseUp += gcnew MouseEventHandler(this, &BillHistoryForm::Form_MouseUp);

            lblTitle->AutoSize = true;
            lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 18.0F, FontStyle::Bold);
            lblTitle->ForeColor = TEXT_DARK;
            lblTitle->BackColor = Color::Transparent;
            lblTitle->Location = Point(30, 18);
            lblTitle->Text = L"Bill History";

            lblSubtitle->AutoSize = true;
            lblSubtitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
            lblSubtitle->ForeColor = TEXT_MUTED;
            lblSubtitle->BackColor = Color::Transparent;
            lblSubtitle->Location = Point(32, 50);
            lblSubtitle->Text = L"Review past transactions and cancel bills if needed";

            btnTopClose->Text = L"\u2715";
            btnTopClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 12.0F, FontStyle::Bold);
            btnTopClose->ForeColor = TEXT_MUTED;
            btnTopClose->BackColor = Color::Transparent;
            btnTopClose->Location = Point(948, 22);
            btnTopClose->Size = System::Drawing::Size(35, 35);
            btnTopClose->TextAlign = ContentAlignment::MiddleCenter;
            btnTopClose->Cursor = Cursors::Hand;
            btnTopClose->Click += gcnew EventHandler(this, &BillHistoryForm::btnTopClose_Click);
            btnTopClose->MouseEnter += gcnew EventHandler(this, &BillHistoryForm::btnTopClose_MouseEnter);
            btnTopClose->MouseLeave += gcnew EventHandler(this, &BillHistoryForm::btnTopClose_MouseLeave);

            pnlHeader->Controls->Add(lblTitle);
            pnlHeader->Controls->Add(lblSubtitle);
            pnlHeader->Controls->Add(btnTopClose);

            // ===== GRID =====
            pnlGrid->Location = Point(20, 95);
            pnlGrid->Size = System::Drawing::Size(960, 460);
            pnlGrid->BackColor = Color::White;
            pnlGrid->Padding = System::Windows::Forms::Padding(1);
            pnlGrid->Paint += gcnew PaintEventHandler(this, &BillHistoryForm::pnlCard_Paint);

            dgvBills->AllowUserToAddRows = false;
            dgvBills->AllowUserToResizeRows = false;
            dgvBills->ReadOnly = true;
            dgvBills->BackgroundColor = Color::White;
            dgvBills->BorderStyle = BorderStyle::None;
            dgvBills->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
            dgvBills->GridColor = BORDER_GREY;
            dgvBills->RowHeadersVisible = false;
            dgvBills->EnableHeadersVisualStyles = false;
            dgvBills->ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle::None;
            dgvBills->ColumnHeadersHeight = 45;
            dgvBills->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
            dgvBills->RowTemplate->Height = 38;
            dgvBills->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            dgvBills->MultiSelect = false;
            dgvBills->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            dgvBills->Dock = DockStyle::Fill;

            DataGridViewCellStyle^ headerStyle = gcnew DataGridViewCellStyle();
            headerStyle->BackColor = NAVY;
            headerStyle->ForeColor = Color::White;
            headerStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
            headerStyle->Alignment = DataGridViewContentAlignment::MiddleLeft;
            headerStyle->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
            headerStyle->SelectionBackColor = NAVY;
            headerStyle->SelectionForeColor = Color::White;
            dgvBills->ColumnHeadersDefaultCellStyle = headerStyle;

            DataGridViewCellStyle^ cellStyle = gcnew DataGridViewCellStyle();
            cellStyle->BackColor = Color::White;
            cellStyle->ForeColor = TEXT_DARK;
            cellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
            cellStyle->Alignment = DataGridViewContentAlignment::MiddleLeft;
            cellStyle->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
            cellStyle->SelectionBackColor = Color::FromArgb(219, 234, 254);
            cellStyle->SelectionForeColor = TEXT_DARK;
            dgvBills->DefaultCellStyle = cellStyle;

            DataGridViewCellStyle^ altStyle = gcnew DataGridViewCellStyle();
            altStyle->BackColor = BG_LIGHT;
            altStyle->ForeColor = TEXT_DARK;
            altStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
            altStyle->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
            altStyle->SelectionBackColor = Color::FromArgb(219, 234, 254);
            altStyle->SelectionForeColor = TEXT_DARK;
            dgvBills->AlternatingRowsDefaultCellStyle = altStyle;

            dgvBills->CellFormatting +=
                gcnew DataGridViewCellFormattingEventHandler(this, &BillHistoryForm::dgvBills_CellFormatting);
            dgvBills->DataBindingComplete +=
                gcnew DataGridViewBindingCompleteEventHandler(this, &BillHistoryForm::dgv_DataBindingComplete);

            pnlGrid->Controls->Add(dgvBills);

            // ===== BUTTONS =====
            btnCancel->Text = L"Cancel Bill";
            btnCancel->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
            btnCancel->BackColor = RED_DANGER;
            btnCancel->ForeColor = Color::White;
            btnCancel->FlatStyle = FlatStyle::Flat;
            btnCancel->FlatAppearance->BorderSize = 0;
            btnCancel->Location = Point(20, 575);
            btnCancel->Size = System::Drawing::Size(140, 40);
            btnCancel->Cursor = Cursors::Hand;
            btnCancel->Click += gcnew EventHandler(this, &BillHistoryForm::btnCancel_Click);
            btnCancel->MouseEnter += gcnew EventHandler(this, &BillHistoryForm::btnCancel_MouseEnter);
            btnCancel->MouseLeave += gcnew EventHandler(this, &BillHistoryForm::btnCancel_MouseLeave);

            btnRefresh->Text = L"\u27F3  Refresh";
            btnRefresh->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
            btnRefresh->BackColor = NAVY;
            btnRefresh->ForeColor = Color::White;
            btnRefresh->FlatStyle = FlatStyle::Flat;
            btnRefresh->FlatAppearance->BorderSize = 0;
            btnRefresh->Location = Point(170, 575);
            btnRefresh->Size = System::Drawing::Size(120, 40);
            btnRefresh->Cursor = Cursors::Hand;
            btnRefresh->Click += gcnew EventHandler(this, &BillHistoryForm::btnRefresh_Click);
            btnRefresh->MouseEnter += gcnew EventHandler(this, &BillHistoryForm::btnRefresh_MouseEnter);
            btnRefresh->MouseLeave += gcnew EventHandler(this, &BillHistoryForm::btnRefresh_MouseLeave);

            btnClose->Text = L"Close";
            btnClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
            btnClose->BackColor = Color::White;
            btnClose->ForeColor = TEXT_DARK;
            btnClose->FlatStyle = FlatStyle::Flat;
            btnClose->FlatAppearance->BorderSize = 1;
            btnClose->FlatAppearance->BorderColor = BORDER_GREY;
            btnClose->Location = Point(880, 575);
            btnClose->Size = System::Drawing::Size(100, 40);
            btnClose->Cursor = Cursors::Hand;
            btnClose->Click += gcnew EventHandler(this, &BillHistoryForm::btnClose_Click);
            btnClose->MouseEnter += gcnew EventHandler(this, &BillHistoryForm::btnClose_MouseEnter);
            btnClose->MouseLeave += gcnew EventHandler(this, &BillHistoryForm::btnClose_MouseLeave);

            // ===== FORM =====
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1000, 635);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->StartPosition = FormStartPosition::CenterScreen;
            this->BackColor = BG_LIGHT;
            this->DoubleBuffered = true;
            this->Text = L"Bill History - ValueMart";
            this->Controls->Add(pnlHeader);
            this->Controls->Add(pnlGrid);
            this->Controls->Add(btnCancel);
            this->Controls->Add(btnRefresh);
            this->Controls->Add(btnClose);
            this->MouseDown += gcnew MouseEventHandler(this, &BillHistoryForm::Form_MouseDown);
            this->MouseMove += gcnew MouseEventHandler(this, &BillHistoryForm::Form_MouseMove);
            this->MouseUp += gcnew MouseEventHandler(this, &BillHistoryForm::Form_MouseUp);
            (cli::safe_cast<ISupportInitialize^>(this->dgvBills))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        // ===== STYLE HELPERS =====
        void ApplyModernStyle() {
            RoundControl(btnCancel, 6);
            RoundControl(btnRefresh, 6);
            RoundControl(btnClose, 6);
            RoundControl(pnlGrid, 8);
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

        void pnlHeader_Paint(Object^ sender, PaintEventArgs^ e) {
            Pen^ pen = gcnew Pen(BORDER_GREY, 1);
            e->Graphics->DrawLine(pen, 0, pnlHeader->Height - 1, pnlHeader->Width, pnlHeader->Height - 1);
        }

        void pnlCard_Paint(Object^ sender, PaintEventArgs^ e) {
            Panel^ p = (Panel^)sender;
            Pen^ pen = gcnew Pen(BORDER_GREY, 1);
            e->Graphics->DrawRectangle(pen, 0, 0, p->Width - 1, p->Height - 1);
        }

        // ===== DRAG =====
        void Form_MouseDown(Object^ sender, MouseEventArgs^ e) {
            if (e->Button == System::Windows::Forms::MouseButtons::Left) {
                dragging = true;
                dragOffset = Point(
                    System::Windows::Forms::Cursor::Position.X - this->Location.X,
                    System::Windows::Forms::Cursor::Position.Y - this->Location.Y);
            }
        }
        void Form_MouseMove(Object^ sender, MouseEventArgs^ e) {
            if (dragging) {
                this->Location = Point(
                    System::Windows::Forms::Cursor::Position.X - dragOffset.X,
                    System::Windows::Forms::Cursor::Position.Y - dragOffset.Y);
            }
        }
        void Form_MouseUp(Object^ sender, MouseEventArgs^ e) {
            dragging = false;
        }

        // ===== HOVER =====
        void btnTopClose_Click(Object^ sender, EventArgs^ e) { this->Close(); }
        void btnTopClose_MouseEnter(Object^ sender, EventArgs^ e) {
            btnTopClose->BackColor = RED_DANGER;
            btnTopClose->ForeColor = Color::White;
        }
        void btnTopClose_MouseLeave(Object^ sender, EventArgs^ e) {
            btnTopClose->BackColor = Color::Transparent;
            btnTopClose->ForeColor = TEXT_MUTED;
        }
        void btnCancel_MouseEnter(Object^ sender, EventArgs^ e) {
            btnCancel->BackColor = RED_DANGER_HOVER;
        }
        void btnCancel_MouseLeave(Object^ sender, EventArgs^ e) {
            btnCancel->BackColor = RED_DANGER;
        }
        void btnRefresh_MouseEnter(Object^ sender, EventArgs^ e) {
            btnRefresh->BackColor = NAVY_HOVER;
        }
        void btnRefresh_MouseLeave(Object^ sender, EventArgs^ e) {
            btnRefresh->BackColor = NAVY;
        }
        void btnClose_MouseEnter(Object^ sender, EventArgs^ e) {
            btnClose->BackColor = BG_LIGHT;
        }
        void btnClose_MouseLeave(Object^ sender, EventArgs^ e) {
            btnClose->BackColor = Color::White;
        }

        // ===== COLUMN FORMATTING =====
        void dgv_DataBindingComplete(Object^ sender, DataGridViewBindingCompleteEventArgs^ e) {
            array<String^>^ moneyCols = { L"Subtotal", L"Discount", L"Tax", L"Total" };
            for each (String ^ col in moneyCols) {
                if (dgvBills->Columns->Contains(col)) {
                    dgvBills->Columns[col]->DefaultCellStyle->Format = L"N2";
                    dgvBills->Columns[col]->DefaultCellStyle->Alignment =
                        DataGridViewContentAlignment::MiddleRight;
                }
            }
            if (dgvBills->Columns->Contains(L"Date")) {
                dgvBills->Columns[L"Date"]->DefaultCellStyle->Format = L"MMM dd, yyyy  hh:mm tt";
            }
            if (dgvBills->Columns->Contains(L"BillNo")) {
                dgvBills->Columns[L"BillNo"]->DefaultCellStyle->Alignment =
                    DataGridViewContentAlignment::MiddleCenter;
                dgvBills->Columns[L"BillNo"]->DefaultCellStyle->Font =
                    gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
            }
            if (dgvBills->Columns->Contains(L"Status")) {
                dgvBills->Columns[L"Status"]->DefaultCellStyle->Alignment =
                    DataGridViewContentAlignment::MiddleCenter;
                dgvBills->Columns[L"Status"]->DefaultCellStyle->Font =
                    gcnew System::Drawing::Font(L"Segoe UI", 9.0F, FontStyle::Bold);
            }
        }

        // ===== ORIGINAL: cell coloring + actions (preserved logic) =====
        void LoadBills() {
            DataTable^ result = SBS::Database::ExecuteQuery(
                "SELECT b.BillNo, b.Date, ISNULL(u.Username, '(unknown)') AS Cashier, "
                "       b.Subtotal, b.Discount, b.Tax, b.Total, "
                "       CASE WHEN b.IsCancelled = 1 THEN 'CANCELLED' ELSE 'Active' END AS Status "
                "FROM Bills b LEFT JOIN Users u ON b.UserID = u.UserID "
                "ORDER BY b.BillNo DESC");

            dgvBills->DataSource = result;

            if (result != nullptr && result->Columns->Count > 0) {
                if (result->Columns->Contains("BillNo"))   dgvBills->Columns["BillNo"]->HeaderText = "Bill #";
                if (result->Columns->Contains("Date"))     dgvBills->Columns["Date"]->HeaderText = "Date/Time";
                if (result->Columns->Contains("Cashier"))  dgvBills->Columns["Cashier"]->HeaderText = "Cashier";
                if (result->Columns->Contains("Subtotal")) dgvBills->Columns["Subtotal"]->HeaderText = "Subtotal";
                if (result->Columns->Contains("Discount")) dgvBills->Columns["Discount"]->HeaderText = "Discount";
                if (result->Columns->Contains("Tax"))      dgvBills->Columns["Tax"]->HeaderText = "Tax";
                if (result->Columns->Contains("Total"))    dgvBills->Columns["Total"]->HeaderText = "Total";
                if (result->Columns->Contains("Status"))   dgvBills->Columns["Status"]->HeaderText = "Status";
            }
        }

        void dgvBills_CellFormatting(Object^ sender, DataGridViewCellFormattingEventArgs^ e) {
            if (e->RowIndex >= 0 && e->RowIndex < dgvBills->Rows->Count) {
                Object^ statusVal = dgvBills->Rows[e->RowIndex]->Cells["Status"]->Value;
                if (statusVal != nullptr && statusVal->ToString() == "CANCELLED") {
                    e->CellStyle->ForeColor = Color::FromArgb(150, 150, 150);
                    e->CellStyle->BackColor = Color::FromArgb(245, 245, 245);
                    e->CellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Italic);
                }
                else if (e->ColumnIndex >= 0 &&
                    dgvBills->Columns[e->ColumnIndex]->Name == "Status") {
                    // Color the "Active" status green
                    e->CellStyle->ForeColor = Color::FromArgb(22, 163, 74);
                }
            }
        }

        void btnCancel_Click(Object^ sender, EventArgs^ e) {
            if (dgvBills->SelectedRows->Count == 0) {
                MessageBox::Show("Select a bill to cancel.", "No Selection",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
                return;
            }

            DataGridViewRow^ row = dgvBills->SelectedRows[0];
            int billNo = Convert::ToInt32(row->Cells["BillNo"]->Value);
            String^ status = row->Cells["Status"]->Value->ToString();

            if (status == "CANCELLED") {
                MessageBox::Show("Bill #" + billNo + " is already cancelled.",
                    "Already Cancelled", MessageBoxButtons::OK, MessageBoxIcon::Information);
                return;
            }

            double total = Convert::ToDouble(row->Cells["Total"]->Value);
            System::Windows::Forms::DialogResult result = MessageBox::Show(
                "Cancel Bill #" + billNo + " (Total: Rs " + total.ToString("F2") + ")?\n\n"
                "This will:\n"
                " - Mark the bill as cancelled\n"
                " - Restore stock for all items in this bill\n\n"
                "This action cannot be undone.",
                "Confirm Cancellation",
                MessageBoxButtons::YesNo,
                MessageBoxIcon::Warning);

            if (result != System::Windows::Forms::DialogResult::Yes) return;

            try {
                SBS::Database::ExecuteNonQuery(
                    "UPDATE Bills SET IsCancelled = 1 WHERE BillNo = @b",
                    gcnew SqlParameter("@b", billNo));

                SBS::Database::ExecuteNonQuery(
                    "UPDATE p SET Stock = Stock + bi.Quantity "
                    "FROM Products p INNER JOIN BillItems bi ON p.ProductID = bi.ProductID "
                    "WHERE bi.BillNo = @b",
                    gcnew SqlParameter("@b", billNo));

                MessageBox::Show("Bill #" + billNo + " cancelled. Stock restored.",
                    "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                LoadBills();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error cancelling bill: " + ex->Message,
                    "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void btnRefresh_Click(Object^ sender, EventArgs^ e) {
            LoadBills();
        }

        void btnClose_Click(Object^ sender, EventArgs^ e) {
            this->Close();
        }
    };
}