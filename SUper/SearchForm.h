#pragma once
#include "database.h"

namespace SuperMarket {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Data;

    public ref class SearchForm : public Form
    {
    public:
        int SelectedProductID;
        String^ SelectedName;
        double SelectedPrice;
        int SelectedStock;
        int SelectedQty;

        SearchForm(void)
        {
            InitializeComponent();

            SelectedProductID = -1;
            SelectedName = "";
            SelectedPrice = 0;
            SelectedStock = 0;
            SelectedQty = 1;
        }

    protected:
        ~SearchForm() { if (components) delete components; }

    private:
        System::ComponentModel::Container^ components;
        TextBox^ txtSearch;
        Button^ btnSearch;
        DataGridView^ resultGrid;
        Label^ lblStatus;
        Label^ lblQty;
        TextBox^ txtQty;
        Button^ btnAdd;
        Button^ btnCancel;

        DataGridViewTextBoxColumn^ c1;
        DataGridViewTextBoxColumn^ c2;
        DataGridViewTextBoxColumn^ c3;
        DataGridViewTextBoxColumn^ c4;

#pragma region InitializeComponent
        void InitializeComponent(void)
        {
            this->txtSearch = gcnew TextBox();
            this->btnSearch = gcnew Button();
            this->resultGrid = gcnew DataGridView();
            this->lblStatus = gcnew Label();
            this->lblQty = gcnew Label();
            this->txtQty = gcnew TextBox();
            this->btnAdd = gcnew Button();
            this->btnCancel = gcnew Button();

            this->c1 = gcnew DataGridViewTextBoxColumn();
            this->c2 = gcnew DataGridViewTextBoxColumn();
            this->c3 = gcnew DataGridViewTextBoxColumn();
            this->c4 = gcnew DataGridViewTextBoxColumn();

            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->resultGrid))->BeginInit();
            this->SuspendLayout();

            // FORM
            this->Text = "Search Product";
            this->Size = Drawing::Size(560, 440);
            this->MaximizeBox = false;
            this->StartPosition = FormStartPosition::CenterParent;
            this->BackColor = Color::WhiteSmoke;

            // SEARCH BOX
            txtSearch->Location = Point(20, 20);
            txtSearch->Size = Drawing::Size(300, 28);
            txtSearch->Font = gcnew Drawing::Font("Arial", 10);
            txtSearch->Text = "Type product name...";
            txtSearch->ForeColor = Color::Gray;

            txtSearch->Enter += gcnew EventHandler(this, &SearchForm::txtSearch_Enter);
            txtSearch->Leave += gcnew EventHandler(this, &SearchForm::txtSearch_Leave);

            // SEARCH BUTTON
            btnSearch->Location = Point(330, 20);
            btnSearch->Size = Drawing::Size(100, 28);
            btnSearch->Text = "Search";
            btnSearch->BackColor = Color::FromArgb(46, 125, 50);
            btnSearch->ForeColor = Color::White;
            btnSearch->FlatStyle = FlatStyle::Flat;
            btnSearch->Click += gcnew EventHandler(this, &SearchForm::btnSearch_Click);

            // STATUS
            lblStatus->Location = Point(20, 55);
            lblStatus->Size = Drawing::Size(500, 20);
            lblStatus->Text = "Type a name and click Search";

            // GRID
            resultGrid->Location = Point(20, 80);
            resultGrid->Size = Drawing::Size(510, 230);
            resultGrid->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            resultGrid->MultiSelect = false;
            resultGrid->ReadOnly = true;
            resultGrid->AllowUserToAddRows = false;
            resultGrid->RowHeadersVisible = false;

            // COLUMNS
            c1->HeaderText = "ID"; c1->Name = "rID"; c1->Width = 50;
            c2->HeaderText = "Name"; c2->Name = "rName"; c2->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;
            c3->HeaderText = "Price"; c3->Name = "rPrice"; c3->Width = 100;
            c4->HeaderText = "Stock"; c4->Name = "rStock"; c4->Width = 80;

            resultGrid->Columns->AddRange(gcnew cli::array<DataGridViewColumn^> { c1, c2, c3, c4 });

            // QTY
            lblQty->Text = "Quantity:";
            lblQty->Location = Point(20, 325);
			lblQty->AutoSize = true;
            txtQty->Location = Point(lblQty->PreferredWidth + 25, 325);
            txtQty->Size = Drawing::Size(170, 25);
            txtQty->Text = "1";
            txtQty->Click += gcnew EventHandler(this, &SearchForm::txtQty_Click);

            // ADD BUTTON
            btnAdd->Text = "Add to Cart";
            btnAdd->Location = Point(110, 365);
            btnAdd->Size = Drawing::Size(160, 35);
            btnAdd->BackColor = Color::FromArgb(27, 94, 32);
            btnAdd->ForeColor = Color::White;
            btnAdd->FlatStyle = FlatStyle::Flat;
            btnAdd->Click += gcnew EventHandler(this, &SearchForm::btnAdd_Click);

            // CANCEL
            btnCancel->Text = "Cancel (Esc)";
            btnCancel->Location = Point(290, 365);
            btnCancel->Size = Drawing::Size(120, 35);
            btnCancel->BackColor = Color::FromArgb(66, 66, 66);
            btnCancel->ForeColor = Color::White;
            btnCancel->FlatStyle = FlatStyle::Flat;
            btnCancel->Click += gcnew EventHandler(this, &SearchForm::btnCancel_Click);

            // ADD CONTROLS
            this->Controls->Add(txtSearch);
            this->Controls->Add(btnSearch);
            this->Controls->Add(lblStatus);
            this->Controls->Add(resultGrid);
            this->Controls->Add(lblQty);
            this->Controls->Add(txtQty);
            this->Controls->Add(btnAdd);
            this->Controls->Add(btnCancel);

            this->KeyPreview = true;
            this->KeyDown += gcnew KeyEventHandler(this, &SearchForm::SearchForm_KeyDown);
            this->AcceptButton = btnSearch;

            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->resultGrid))->EndInit();
            this->ResumeLayout(false);
        }
#pragma endregion

        // ===== Placeholder handlers =====
    private:
        System::Void txtSearch_Enter(Object^ sender, EventArgs^ e) {
            if (txtSearch->Text == "Type product name...") {
                txtSearch->Text = "";
                txtSearch->ForeColor = Color::Black;
            }
        }

        System::Void txtSearch_Leave(Object^ sender, EventArgs^ e) {
            if (String::IsNullOrWhiteSpace(txtSearch->Text)) {
                txtSearch->Text = "Type product name...";
                txtSearch->ForeColor = Color::Gray;
            }
        }

        // ===== Search =====
    private:
        System::Void btnSearch_Click(Object^ sender, EventArgs^ e) {

            if (txtSearch->Text->Trim() == "" || txtSearch->Text == "Type product name...") {
                lblStatus->Text = "Enter a valid product name!";
                return;
            }

            resultGrid->Rows->Clear();

            String^ sql =
                "SELECT ProductID, Name, Price, Stock FROM Products WHERE Name LIKE '%"
                + txtSearch->Text->Trim() + "%' AND IsActive = 1 ORDER BY Name";

            DataTable^ results = SBS::Database::ExecuteQuery(sql);

            for (int i = 0; i < results->Rows->Count; i++) {
                DataRow^ row = results->Rows[i];

                resultGrid->Rows->Add(
                    row["ProductID"]->ToString(),
                    row["Name"]->ToString(),
                    "Rs " + row["Price"]->ToString(),
                    row["Stock"]->ToString()
                );
            }

            if (results->Rows->Count > 0)
                resultGrid->Rows[0]->Selected = true;
        }

        // ===== Add =====
    private:
        System::Void btnAdd_Click(Object^ sender, EventArgs^ e) {

            if (resultGrid->SelectedRows->Count == 0) {
                MessageBox::Show("Select a product first!");
                return;
            }

            int qty;
            if (!Int32::TryParse(txtQty->Text, qty) || qty <= 0) {
                MessageBox::Show("Invalid quantity!");
                return;
            }

            int stock = Int32::Parse(resultGrid->SelectedRows[0]->Cells["rStock"]->Value->ToString()->Trim());
            if (qty > stock) {
                MessageBox::Show("Not enough stock!");
                return;
            }

            SelectedProductID = Convert::ToInt32(resultGrid->SelectedRows[0]->Cells["rID"]->Value);
            SelectedName = resultGrid->SelectedRows[0]->Cells["rName"]->Value->ToString();

            SelectedPrice = Convert::ToDouble(
                resultGrid->SelectedRows[0]->Cells["rPrice"]->Value->ToString()->Replace("Rs ", "")
            );

            SelectedQty = qty;

            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
        }

        // ===== Cancel =====
    private:
        System::Void btnCancel_Click(Object^ sender, EventArgs^ e) {
            this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            this->Close();
        }

        // ===== Keys =====
    private:
        System::Void SearchForm_KeyDown(Object^ sender, KeyEventArgs^ e) {
            if (e->KeyCode == Keys::Escape) btnCancel->PerformClick();
            if (e->KeyCode == Keys::F4) btnAdd->PerformClick();
        }
        System::Void txtQty_Click(Object^ sender, EventArgs^ e) {
            txtQty->Focus();
            txtQty->SelectAll();
        }
    };
}