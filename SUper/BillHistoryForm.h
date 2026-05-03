#pragma once
#include "database.h"

namespace SUper {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Data::SqlClient;
    using namespace System::Drawing;

    public ref class BillHistoryForm : public Form
    {
    public:
        BillHistoryForm(void)
        {
            InitializeComponent();
            LoadBills();
        }

    protected:
        ~BillHistoryForm()
        {
            if (components) delete components;
        }

    private:
        System::ComponentModel::Container^ components;
        Label^ lblTitle;
        DataGridView^ dgvBills;
        Button^ btnCancel;
        Button^ btnRefresh;
        Button^ btnClose;

        void InitializeComponent(void)
        {
            this->Text = "Bill History - ValueMart";
            this->Size = System::Drawing::Size(900, 600);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->BackColor = Color::White;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;

            lblTitle = gcnew Label();
            lblTitle->Text = "All Bills";
            lblTitle->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 14, FontStyle::Bold);
            lblTitle->Location = System::Drawing::Point(20, 15);
            lblTitle->Size = System::Drawing::Size(300, 30);

            dgvBills = gcnew DataGridView();
            dgvBills->Location = System::Drawing::Point(20, 60);
            dgvBills->Size = System::Drawing::Size(840, 420);
            dgvBills->ReadOnly = true;
            dgvBills->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            dgvBills->MultiSelect = false;
            dgvBills->AllowUserToAddRows = false;
            dgvBills->BackgroundColor = Color::White;
            dgvBills->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            dgvBills->RowHeadersVisible = false;
            dgvBills->CellFormatting += gcnew DataGridViewCellFormattingEventHandler(this, &BillHistoryForm::dgvBills_CellFormatting);

            btnCancel = gcnew Button();
            btnCancel->Text = "Cancel Bill";
            btnCancel->Size = System::Drawing::Size(140, 38);
            btnCancel->Location = System::Drawing::Point(20, 500);
            btnCancel->BackColor = Color::FromArgb(200, 50, 50);
            btnCancel->ForeColor = Color::White;
            btnCancel->FlatStyle = FlatStyle::Flat;
            btnCancel->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 9, FontStyle::Bold);
            btnCancel->Click += gcnew EventHandler(this, &BillHistoryForm::btnCancel_Click);

            btnRefresh = gcnew Button();
            btnRefresh->Text = "Refresh";
            btnRefresh->Size = System::Drawing::Size(120, 38);
            btnRefresh->Location = System::Drawing::Point(180, 500);
            btnRefresh->BackColor = Color::FromArgb(80, 80, 80);
            btnRefresh->ForeColor = Color::White;
            btnRefresh->FlatStyle = FlatStyle::Flat;
            btnRefresh->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 9, FontStyle::Bold);
            btnRefresh->Click += gcnew EventHandler(this, &BillHistoryForm::btnRefresh_Click);

            btnClose = gcnew Button();
            btnClose->Text = "Close";
            btnClose->Size = System::Drawing::Size(100, 38);
            btnClose->Location = System::Drawing::Point(760, 500);
            btnClose->BackColor = Color::FromArgb(180, 180, 180);
            btnClose->ForeColor = Color::Black;
            btnClose->FlatStyle = FlatStyle::Flat;
            btnClose->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 9, FontStyle::Bold);
            btnClose->Click += gcnew EventHandler(this, &BillHistoryForm::btnClose_Click);

            this->Controls->Add(lblTitle);
            this->Controls->Add(dgvBills);
            this->Controls->Add(btnCancel);
            this->Controls->Add(btnRefresh);
            this->Controls->Add(btnClose);
        }

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
            // Gray out cancelled bill rows
            if (e->RowIndex >= 0 && e->RowIndex < dgvBills->Rows->Count) {
                Object^ statusVal = dgvBills->Rows[e->RowIndex]->Cells["Status"]->Value;
                if (statusVal != nullptr && statusVal->ToString() == "CANCELLED") {
                    e->CellStyle->ForeColor = Color::Gray;
                    e->CellStyle->BackColor = Color::FromArgb(245, 245, 245);
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
                // 1. Mark bill as cancelled
                SBS::Database::ExecuteNonQuery(
                    "UPDATE Bills SET IsCancelled = 1 WHERE BillNo = @b",
                    gcnew SqlParameter("@b", billNo));

                // 2. Restore stock for each item in this bill
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