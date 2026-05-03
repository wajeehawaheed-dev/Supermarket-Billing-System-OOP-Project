#pragma once
#include "database.h"

namespace SUper {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Data::SqlClient;
    using namespace System::Drawing;

    public ref class UserProductView : public System::Windows::Forms::Form
    {
    private:
        DataTable^ dtProducts;

        System::Windows::Forms::DataGridView^ dgvProducts;
        System::Windows::Forms::TextBox^ txtSearchName;
        System::Windows::Forms::TextBox^ txtSearchID;
        System::Windows::Forms::Button^ btnSearchName;
        System::Windows::Forms::Button^ btnSearchID;
        System::Windows::Forms::Button^ btnShowAll;
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Label^ lblSubtitle;
        System::Windows::Forms::Label^ lblSearchName;
        System::Windows::Forms::Label^ lblSearchID;
        System::Windows::Forms::Label^ lblResultCount;
        System::Windows::Forms::Panel^ pnlTop;
        System::Windows::Forms::Panel^ pnlSearch;

    public:
        UserProductView(void) {
            dtProducts = nullptr;
            InitializeComponent();
            loadAllProducts();
        }

    private:
        void InitializeComponent(void) {
            this->Text = "Browse Products";
            this->Size = System::Drawing::Size(900, 620);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->BackColor = Color::White;

            // --- Top panel ---
            pnlTop = gcnew Panel();
            pnlTop->Dock = DockStyle::Top;
            pnlTop->Height = 70;
            pnlTop->BackColor = Color::DarkSlateBlue;

            lblTitle = gcnew Label();
            lblTitle->Text = "SuperMart — Product Catalog";
            lblTitle->Font = gcnew System::Drawing::Font("Segoe UI", 16, FontStyle::Bold);
            lblTitle->ForeColor = Color::White;
            lblTitle->Location = System::Drawing::Point(15, 10);
            lblTitle->AutoSize = true;

            lblSubtitle = gcnew Label();
            lblSubtitle->Text = "Browse our products, check prices and availability";
            lblSubtitle->Font = gcnew System::Drawing::Font("Segoe UI", 9);
            lblSubtitle->ForeColor = Color::LightSteelBlue;
            lblSubtitle->Location = System::Drawing::Point(15, 42);
            lblSubtitle->AutoSize = true;

            pnlTop->Controls->Add(lblTitle);
            pnlTop->Controls->Add(lblSubtitle);

            // --- Search panel ---
            pnlSearch = gcnew Panel();
            pnlSearch->Location = System::Drawing::Point(0, 70);
            pnlSearch->Size = System::Drawing::Size(900, 55);
            pnlSearch->BackColor = Color::WhiteSmoke;

            lblSearchName = gcnew Label();
            lblSearchName->Text = "Search by Name:";
            lblSearchName->Location = System::Drawing::Point(15, 18);
            lblSearchName->AutoSize = true;

            txtSearchName = gcnew TextBox();
            txtSearchName->Location = System::Drawing::Point(120, 15);
            txtSearchName->Size = System::Drawing::Size(200, 26);
            txtSearchName->Font = gcnew System::Drawing::Font("Segoe UI", 10);

            btnSearchName = gcnew Button();
            btnSearchName->Text = "Search";
            btnSearchName->Location = System::Drawing::Point(330, 13);
            btnSearchName->Size = System::Drawing::Size(80, 30);
            btnSearchName->BackColor = Color::DarkSlateBlue;
            btnSearchName->ForeColor = Color::White;
            btnSearchName->FlatStyle = FlatStyle::Flat;
            btnSearchName->Click += gcnew EventHandler(this, &UserProductView::btnSearchName_Click);

            lblSearchID = gcnew Label();
            lblSearchID->Text = "Search by ID:";
            lblSearchID->Location = System::Drawing::Point(440, 18);
            lblSearchID->AutoSize = true;

            txtSearchID = gcnew TextBox();
            txtSearchID->Location = System::Drawing::Point(530, 15);
            txtSearchID->Size = System::Drawing::Size(80, 26);
            txtSearchID->Font = gcnew System::Drawing::Font("Segoe UI", 10);

            btnSearchID = gcnew Button();
            btnSearchID->Text = "Search";
            btnSearchID->Location = System::Drawing::Point(620, 13);
            btnSearchID->Size = System::Drawing::Size(80, 30);
            btnSearchID->BackColor = Color::DarkSlateBlue;
            btnSearchID->ForeColor = Color::White;
            btnSearchID->FlatStyle = FlatStyle::Flat;
            btnSearchID->Click += gcnew EventHandler(this, &UserProductView::btnSearchID_Click);

            btnShowAll = gcnew Button();
            btnShowAll->Text = "Show All";
            btnShowAll->Location = System::Drawing::Point(720, 13);
            btnShowAll->Size = System::Drawing::Size(80, 30);
            btnShowAll->BackColor = Color::SeaGreen;
            btnShowAll->ForeColor = Color::White;
            btnShowAll->FlatStyle = FlatStyle::Flat;
            btnShowAll->Click += gcnew EventHandler(this, &UserProductView::btnShowAll_Click);

            pnlSearch->Controls->Add(lblSearchName);
            pnlSearch->Controls->Add(txtSearchName);
            pnlSearch->Controls->Add(btnSearchName);
            pnlSearch->Controls->Add(lblSearchID);
            pnlSearch->Controls->Add(txtSearchID);
            pnlSearch->Controls->Add(btnSearchID);
            pnlSearch->Controls->Add(btnShowAll);

            // --- Result count label ---
            lblResultCount = gcnew Label();
            lblResultCount->Location = System::Drawing::Point(15, 130);
            lblResultCount->AutoSize = true;
            lblResultCount->ForeColor = Color::DimGray;
            lblResultCount->Font = gcnew System::Drawing::Font("Segoe UI", 9);

            // --- DataGridView (read only) ---
            dgvProducts = gcnew DataGridView();
            dgvProducts->Location = System::Drawing::Point(10, 150);
            dgvProducts->Size = System::Drawing::Size(865, 420);
            dgvProducts->ReadOnly = true;
            dgvProducts->AllowUserToAddRows = false;
            dgvProducts->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            dgvProducts->MultiSelect = false;
            dgvProducts->RowHeadersVisible = false;
            dgvProducts->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            dgvProducts->BackgroundColor = Color::White;
            dgvProducts->BorderStyle = BorderStyle::None;
            dgvProducts->Font = gcnew System::Drawing::Font("Segoe UI", 10);
            dgvProducts->ColumnHeadersDefaultCellStyle->Font =
                gcnew System::Drawing::Font("Segoe UI", 10, FontStyle::Bold);
            dgvProducts->ColumnHeadersDefaultCellStyle->BackColor = Color::DarkSlateBlue;
            dgvProducts->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
            dgvProducts->EnableHeadersVisualStyles = false;
            dgvProducts->AlternatingRowsDefaultCellStyle->BackColor = Color::AliceBlue;
            dgvProducts->RowTemplate->Height = 35;

            this->Controls->Add(pnlTop);
            this->Controls->Add(pnlSearch);
            this->Controls->Add(lblResultCount);
            this->Controls->Add(dgvProducts);
        }

        void loadAllProducts() {
            try {
                dtProducts = SBS::Database::ExecuteQuery(
                    "SELECT ProductID AS 'ID', Name AS 'Product Name', "
                    "Category, Price AS 'Price (Rs.)', "
                    "CASE WHEN Stock > 0 THEN CAST(Stock AS NVARCHAR) "
                    "ELSE 'Out of Stock' END AS 'Availability' "
                    "FROM Products WHERE IsActive = 1 ORDER BY ProductID ASC");
                dgvProducts->DataSource = dtProducts;

                // color out of stock rows red
                DataTableReader^ r = dtProducts->CreateDataReader();
                for each (DataGridViewRow ^ row in dgvProducts->Rows) {
                    if (!row->IsNewRow && r->Read()) {
                        int stock = r->GetInt32(4);  // raw stock value
                        if (stock == 0)
                            row->DefaultCellStyle->ForeColor = Color::Red;
                    }
                }
                r->Close();

                lblResultCount->Text = dtProducts->Rows->Count + " product(s) available";
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error: " + ex->Message);
            }
        }

        void showResults(DataTable^ dt) {
            dgvProducts->DataSource = dt;
            lblResultCount->Text = dt->Rows->Count + " product(s) found";
            if (dt->Rows->Count == 0)
                lblResultCount->ForeColor = Color::Red;
            else
                lblResultCount->ForeColor = Color::DarkGreen;
        }

        void btnSearchName_Click(Object^ sender, EventArgs^ e) {
            String^ q = "%" + txtSearchName->Text->Trim() + "%";
            DataTable^ dt = SBS::Database::ExecuteQuery(
                "SELECT ProductID AS 'ID', Name AS 'Product Name', "
                "Category, Price AS 'Price (Rs.)', "
                "CASE WHEN Stock > 0 THEN CAST(Stock AS NVARCHAR) "
                "ELSE 'Out of Stock' END AS 'Availability' "
                "FROM Products WHERE Name LIKE @q AND IsActive = 1",
                gcnew SqlParameter("@q", q));
            showResults(dt);
        }

        void btnSearchID_Click(Object^ sender, EventArgs^ e) {
            int id;
            if (!Int32::TryParse(txtSearchID->Text, id)) {
                MessageBox::Show("Please enter a valid ID number.");
                return;
            }
            DataTable^ dt = SBS::Database::ExecuteQuery(
                "SELECT ProductID AS 'ID', Name AS 'Product Name', "
                "Category, Price AS 'Price (Rs.)', "
                "CASE WHEN Stock > 0 THEN CAST(Stock AS NVARCHAR) "
                "ELSE 'Out of Stock' END AS 'Availability' "
                "FROM Products WHERE ProductID = @id AND IsActive = 1",
                gcnew SqlParameter("@id", id));
            showResults(dt);
        }

        void btnShowAll_Click(Object^ sender, EventArgs^ e) {
            txtSearchName->Text = "";
            txtSearchID->Text = "";
            lblResultCount->ForeColor = Color::DimGray;
            loadAllProducts();
        }
    };
}