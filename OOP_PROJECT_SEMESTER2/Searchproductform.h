#pragma once
#define _COM_NO_STANDARD_GUIDS_
#include "database.h"
#include "product.h"

namespace OOP_PROJECT_SEMESTER2 {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Data::SqlClient;

    public ref class SearchProductForm : public Form {
    private:
        TextBox^ txtSearchName;
        TextBox^ txtSearchID;
        Button^ btnSearchName;
        Button^ btnSearchID;
        Button^ btnClose;
        DataGridView^ dgvResults;
        Label^ lblResults;

    public:
        SearchProductForm() { InitializeComponent(); }

    private:
        void InitializeComponent() {
            this->Text = "Search Products";
            this->Size = System::Drawing::Size(700, 430);
            this->StartPosition = FormStartPosition::CenterParent;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->BackColor = System::Drawing::Color::WhiteSmoke;

            // Search by Name row
            Label^ lblName = gcnew Label();
            lblName->Text = "Search by Name:";
            lblName->Location = System::Drawing::Point(20, 20);
            lblName->Size = System::Drawing::Size(120, 22);

            txtSearchName = gcnew TextBox();
            txtSearchName->Location = System::Drawing::Point(150, 18);
            txtSearchName->Size = System::Drawing::Size(250, 26);
            txtSearchName->Font = gcnew System::Drawing::Font("Segoe UI", 10);
            txtSearchName->Text = "e.g. Milk, Soap...";
            txtSearchName->ForeColor = System::Drawing::Color::Gray;//fix

            

            btnSearchName = gcnew Button();
            btnSearchName->Text = "Search";
            btnSearchName->Location = System::Drawing::Point(415, 16);
            btnSearchName->Size = System::Drawing::Size(90, 30);
            btnSearchName->BackColor = System::Drawing::Color::DarkOrange;
            btnSearchName->ForeColor = System::Drawing::Color::White;
            btnSearchName->FlatStyle = FlatStyle::Flat;
            btnSearchName->Click += gcnew EventHandler(this, &SearchProductForm::btnSearchName_Click);

            // Search by ID row
            Label^ lblID = gcnew Label();
            lblID->Text = "Search by ID:";
            lblID->Location = System::Drawing::Point(20, 58);
            lblID->Size = System::Drawing::Size(120, 22);

            txtSearchID = gcnew TextBox();
            txtSearchID->Location = System::Drawing::Point(150, 56);
            txtSearchID->Size = System::Drawing::Size(100, 26);
            txtSearchID->Font = gcnew System::Drawing::Font("Segoe UI", 10);
            txtSearchID->Text = "e.g. 3";
            txtSearchID->ForeColor = System::Drawing::Color::Gray;//fix

            btnSearchID = gcnew Button();
            btnSearchID->Text = "Search";
            btnSearchID->Location = System::Drawing::Point(265, 54);
            btnSearchID->Size = System::Drawing::Size(90, 30);
            btnSearchID->BackColor = System::Drawing::Color::DarkOrange;
            btnSearchID->ForeColor = System::Drawing::Color::White;
            btnSearchID->FlatStyle = FlatStyle::Flat;
            btnSearchID->Click += gcnew EventHandler(this, &SearchProductForm::btnSearchID_Click);

            // Results label
            lblResults = gcnew Label();
            lblResults->Text = "Results will appear here...";
            lblResults->Location = System::Drawing::Point(20, 95);
            lblResults->Size = System::Drawing::Size(300, 20);
            lblResults->ForeColor = System::Drawing::Color::DimGray;

            // Results Grid
            dgvResults = gcnew DataGridView();
            dgvResults->Location = System::Drawing::Point(10, 118);
            dgvResults->Size = System::Drawing::Size(665, 250);
            dgvResults->ReadOnly = true;
            dgvResults->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            dgvResults->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            dgvResults->AllowUserToAddRows = false;
            dgvResults->RowHeadersVisible = false;
            dgvResults->BackgroundColor = System::Drawing::Color::White;
            dgvResults->Font = gcnew System::Drawing::Font("Segoe UI", 9);

            // Close button
            btnClose = gcnew Button();
            btnClose->Text = "Close";
            btnClose->Location = System::Drawing::Point(570, 378);
            btnClose->Size = System::Drawing::Size(100, 32);
            btnClose->BackColor = System::Drawing::Color::DimGray;
            btnClose->ForeColor = System::Drawing::Color::White;
            btnClose->FlatStyle = FlatStyle::Flat;
            btnClose->Click += gcnew EventHandler(this, &SearchProductForm::btnClose_Click);

            this->Controls->Add(lblName);       this->Controls->Add(txtSearchName);
            this->Controls->Add(btnSearchName);
            this->Controls->Add(lblID);         this->Controls->Add(txtSearchID);
            this->Controls->Add(btnSearchID);
            this->Controls->Add(lblResults);
            this->Controls->Add(dgvResults);
            this->Controls->Add(btnClose);
        }

        void showResults(DataTable^ dt) {
            dgvResults->DataSource = dt;
            int count = dt->Rows->Count;
            lblResults->Text = count == 0 ? "No products found." : count + " product(s) found.";
            lblResults->ForeColor = count == 0 ? System::Drawing::Color::Red
                : System::Drawing::Color::DarkGreen;
        }

        void btnSearchName_Click(Object^ sender, EventArgs^ e) {
            String^ q = "%" + txtSearchName->Text->Trim() + "%";
            DataTable^ dt = SBS::Database::ExecuteQuery(
                "SELECT ProductID AS 'ID', Name, Category, Price AS 'Price (Rs.)', Stock "
                "FROM Products WHERE Name LIKE @q AND IsActive = 1",
                gcnew SqlParameter("@q", q));
            showResults(dt);
        }

        void btnSearchID_Click(Object^ sender, EventArgs^ e) {
            int id;
            if (!Int32::TryParse(txtSearchID->Text, id)) {
                MessageBox::Show("Please enter a valid numeric ID."); return;
            }
            DataTable^ dt = SBS::Database::ExecuteQuery(
                "SELECT ProductID AS 'ID', Name, Category, Price AS 'Price (Rs.)', Stock "
                "FROM Products WHERE ProductID = @id AND IsActive = 1",
                gcnew SqlParameter("@id", id));
            showResults(dt);
        }

        void btnClose_Click(Object^ sender, EventArgs^ e) { this->Close(); }
    };
}