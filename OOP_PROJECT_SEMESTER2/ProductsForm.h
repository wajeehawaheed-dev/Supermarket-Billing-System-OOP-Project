#pragma once
#include "product.h"
#include "database.h"

namespace OOP_PROJECT_SEMESTER2 {
    ref class AddProductForm;
    ref class EditProductForm;
    ref class SearchProductForm;
}

namespace OOP_PROJECT_SEMESTER2 {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class ProductsForm : public System::Windows::Forms::Form
    {
    private:
        ProductManager* pm;
        DataTable^ dtProducts;

        System::Windows::Forms::DataGridView^ dgvProducts;
        System::Windows::Forms::Button^ btnAdd;
        System::Windows::Forms::Button^ btnEdit;
        System::Windows::Forms::Button^ btnSearch;
        System::Windows::Forms::Button^ btnDelete;
        System::Windows::Forms::Button^ btnRefresh;
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Label^ lblStockAlert;
        System::Windows::Forms::Panel^ pnlBottom;

    public:
        ProductsForm(void) {
            pm = new ProductManager();
            dtProducts = nullptr;
            InitializeComponent();
            loadGrid();
        }

    protected:
        ~ProductsForm() {
            if (pm) { delete pm; pm = nullptr; }
        }

    private:
        void InitializeComponent(void) {
            this->Text = L"Product Management System";
            this->Size = System::Drawing::Size(900, 600);
            this->StartPosition = FormStartPosition::CenterScreen;

            lblTitle = gcnew Label();
            lblTitle->Text = "Product & Stock Management";
            lblTitle->Font = gcnew System::Drawing::Font("Segoe UI", 14, FontStyle::Bold);
            lblTitle->Location = System::Drawing::Point(10, 10);
            lblTitle->AutoSize = true;

            lblStockAlert = gcnew Label();
            lblStockAlert->Text = "LOW STOCK DETECTED";
            lblStockAlert->ForeColor = Color::Red;
            lblStockAlert->Font = gcnew System::Drawing::Font("Segoe UI", 10, FontStyle::Bold);
            lblStockAlert->Location = System::Drawing::Point(650, 15);
            lblStockAlert->Visible = false;
            lblStockAlert->AutoSize = true;

            dgvProducts = gcnew DataGridView();
            dgvProducts->Location = System::Drawing::Point(15, 50);
            dgvProducts->Size = System::Drawing::Size(850, 430);
            dgvProducts->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            dgvProducts->MultiSelect = false;
            dgvProducts->ReadOnly = true;
            dgvProducts->RowHeadersVisible = false;
            dgvProducts->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;

            pnlBottom = gcnew Panel();
            pnlBottom->Dock = DockStyle::Bottom;
            pnlBottom->Height = 70;
            pnlBottom->BackColor = Color::LightGray;

            btnAdd = gcnew Button(); btnAdd->Text = "Add New";
            btnAdd->Location = Point(20, 15);
            btnAdd->Click += gcnew EventHandler(this, &ProductsForm::btnAdd_Click);

            btnEdit = gcnew Button(); btnEdit->Text = "Edit Item";
            btnEdit->Location = Point(120, 15);
            btnEdit->Click += gcnew EventHandler(this, &ProductsForm::btnEdit_Click);

            btnDelete = gcnew Button(); btnDelete->Text = "Delete";
            btnDelete->Location = Point(220, 15);
            btnDelete->Click += gcnew EventHandler(this, &ProductsForm::btnDelete_Click);

            btnSearch = gcnew Button(); btnSearch->Text = "Search";
            btnSearch->Location = Point(320, 15);
            btnSearch->Click += gcnew EventHandler(this, &ProductsForm::btnSearch_Click);

            btnRefresh = gcnew Button(); btnRefresh->Text = "Refresh";
            btnRefresh->Location = Point(420, 15);
            btnRefresh->Click += gcnew EventHandler(this, &ProductsForm::btnRefresh_Click);

            pnlBottom->Controls->Add(btnAdd);
            pnlBottom->Controls->Add(btnEdit);
            pnlBottom->Controls->Add(btnDelete);
            pnlBottom->Controls->Add(btnSearch);
            pnlBottom->Controls->Add(btnRefresh);

            this->Controls->Add(dgvProducts);
            this->Controls->Add(lblTitle);
            this->Controls->Add(lblStockAlert);
            this->Controls->Add(pnlBottom);
        }

        void loadGrid() {
            bool lowStockFound = false;
            try {
                dtProducts = SBS::Database::ExecuteQuery(
                    "SELECT ProductID AS 'ID', Name, Category, Price, Stock "
                    "FROM Products WHERE IsActive = 1");
                dgvProducts->DataSource = dtProducts;
                dgvProducts->Refresh();

                // check for low stock
                DataTableReader^ reader = dtProducts->CreateDataReader();
                while (reader->Read()) {
                    int stock = reader->GetInt32(4);
                    if (stock < 5) lowStockFound = true;
                }
                reader->Close();

                // color low stock rows using for each — no indexer
                DataTableReader^ r2 = dtProducts->CreateDataReader();
                for each (DataGridViewRow ^ row in dgvProducts->Rows) {
                    if (!row->IsNewRow && r2->Read()) {
                        int stock = r2->GetInt32(4);
                        if (stock < 5)
                            row->DefaultCellStyle->BackColor = Color::MistyRose;
                    }
                }
                r2->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading grid: " + ex->Message);
            }
            lblStockAlert->Visible = lowStockFound;
        }

        // get ID using DataTableReader — no indexer
        int getSelectedID() {
            int rowIndex = dgvProducts->CurrentCellAddress.Y;
            if (rowIndex < 0 || dtProducts == nullptr) return -1;
            DataTableReader^ r = dtProducts->CreateDataReader();
            int i = 0;
            int id = -1;
            while (r->Read()) {
                if (i == rowIndex) { id = r->GetInt32(0); break; }
                i++;
            }
            r->Close();
            return id;
        }

        void btnAdd_Click(Object^ sender, EventArgs^ e);
        void btnEdit_Click(Object^ sender, EventArgs^ e);
        void btnDelete_Click(Object^ sender, EventArgs^ e);
        void btnSearch_Click(Object^ sender, EventArgs^ e);
        void btnRefresh_Click(Object^ sender, EventArgs^ e);
    };
}