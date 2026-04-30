#define WIN32_LEAN_AND_MEAN
#pragma once
#include "database.h"
#include "product.h"
#include <msclr/marshal_cppstd.h>

namespace SUper {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Data::SqlClient;

    public ref class EditProductForm : public Form {
    private:
        int             productID;
        ProductManager^ pm;
        TextBox^ txtName;
        TextBox^ txtCategory;
        TextBox^ txtPrice;
        TextBox^ txtRestockQty;
        Button^ btnSave;
        Button^ btnRestock;
        Button^ btnCancel;

    public:
        EditProductForm(int id) {
            productID = id;
            pm = gcnew ProductManager();
            InitializeComponent();
            loadData();
        }
        ~EditProductForm() { }

    private:
        void InitializeComponent() {
            this->Text = "Edit Product";
            this->Size = System::Drawing::Size(370, 340);
            this->StartPosition = FormStartPosition::CenterParent;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->BackColor = System::Drawing::Color::WhiteSmoke;

            Label^ lblName = gcnew Label();
            lblName->Text = "Name:"; lblName->Location = System::Drawing::Point(20, 20);
            lblName->Size = System::Drawing::Size(100, 22);
            txtName = gcnew TextBox();
            txtName->Location = System::Drawing::Point(130, 18);
            txtName->Size = System::Drawing::Size(210, 26);
            txtName->Font = gcnew System::Drawing::Font("Segoe UI", 10);

            Label^ lblCat = gcnew Label();
            lblCat->Text = "Category:"; lblCat->Location = System::Drawing::Point(20, 60);
            lblCat->Size = System::Drawing::Size(100, 22);
            txtCategory = gcnew TextBox();
            txtCategory->Location = System::Drawing::Point(130, 58);
            txtCategory->Size = System::Drawing::Size(210, 26);
            txtCategory->Font = gcnew System::Drawing::Font("Segoe UI", 10);

            Label^ lblPrice = gcnew Label();
            lblPrice->Text = "Price (Rs.):"; lblPrice->Location = System::Drawing::Point(20, 100);
            lblPrice->Size = System::Drawing::Size(100, 22);
            txtPrice = gcnew TextBox();
            txtPrice->Location = System::Drawing::Point(130, 98);
            txtPrice->Size = System::Drawing::Size(210, 26);
            txtPrice->Font = gcnew System::Drawing::Font("Segoe UI", 10);

            Label^ lblRestock = gcnew Label();
            lblRestock->Text = "Add Stock:";
            lblRestock->Location = System::Drawing::Point(20, 150);
            lblRestock->Size = System::Drawing::Size(100, 22);
            lblRestock->ForeColor = System::Drawing::Color::DarkGreen;
            lblRestock->Font = gcnew System::Drawing::Font("Segoe UI", 9, System::Drawing::FontStyle::Bold);

            txtRestockQty = gcnew TextBox();
            txtRestockQty->Location = System::Drawing::Point(130, 148);
            txtRestockQty->Size = System::Drawing::Size(100, 26);
            txtRestockQty->Font = gcnew System::Drawing::Font("Segoe UI", 10);
            txtRestockQty->Text = "0";

            btnRestock = gcnew Button();
            btnRestock->Text = "+ Restock";
            btnRestock->Location = System::Drawing::Point(240, 146);
            btnRestock->Size = System::Drawing::Size(100, 30);
            btnRestock->BackColor = System::Drawing::Color::SeaGreen;
            btnRestock->ForeColor = System::Drawing::Color::White;
            btnRestock->FlatStyle = FlatStyle::Flat;
            btnRestock->Click += gcnew EventHandler(this, &EditProductForm::btnRestock_Click);

            btnSave = gcnew Button();
            btnSave->Text = "Save Changes";
            btnSave->Location = System::Drawing::Point(50, 250);
            btnSave->Size = System::Drawing::Size(130, 36);
            btnSave->BackColor = System::Drawing::Color::SteelBlue;
            btnSave->ForeColor = System::Drawing::Color::White;
            btnSave->FlatStyle = FlatStyle::Flat;
            btnSave->Font = gcnew System::Drawing::Font("Segoe UI", 10, System::Drawing::FontStyle::Bold);
            btnSave->Click += gcnew EventHandler(this, &EditProductForm::btnSave_Click);

            btnCancel = gcnew Button();
            btnCancel->Text = "Cancel";
            btnCancel->Location = System::Drawing::Point(200, 250);
            btnCancel->Size = System::Drawing::Size(100, 36);
            btnCancel->BackColor = System::Drawing::Color::Crimson;
            btnCancel->ForeColor = System::Drawing::Color::White;
            btnCancel->FlatStyle = FlatStyle::Flat;
            btnCancel->Font = gcnew System::Drawing::Font("Segoe UI", 10);
            btnCancel->Click += gcnew EventHandler(this, &EditProductForm::btnCancel_Click);

            this->Controls->Add(lblName);    this->Controls->Add(txtName);
            this->Controls->Add(lblCat);     this->Controls->Add(txtCategory);
            this->Controls->Add(lblPrice);   this->Controls->Add(txtPrice);
            this->Controls->Add(lblRestock); this->Controls->Add(txtRestockQty);
            this->Controls->Add(btnRestock);
            this->Controls->Add(btnSave);
            this->Controls->Add(btnCancel);
        }

        void loadData() {
            DataTable^ dt = SBS::Database::ExecuteQuery(
                "SELECT * FROM Products WHERE ProductID = @id",
                gcnew SqlParameter("@id", productID));
            if (dt->Rows->Count > 0) {
                DataTableReader^ r = dt->CreateDataReader();
                if (r->Read()) {
                    txtName->Text = r->GetString(1);
                    txtCategory->Text = r->GetString(2);
                    txtPrice->Text = r->GetDecimal(3).ToString();
                }
                r->Close();
            }
        }

        void btnSave_Click(Object^ sender, EventArgs^ e) {
            if (txtName->Text->Trim() == "") { MessageBox::Show("Name cannot be empty."); return; }
            if (txtCategory->Text->Trim() == "") { MessageBox::Show("Category cannot be empty."); return; }
            double price;
            if (!Double::TryParse(txtPrice->Text, price) || price <= 0) {
                MessageBox::Show("Enter a valid price."); return;
            }
            pm->updateInDB(productID, txtName->Text->Trim(), txtCategory->Text->Trim(), price);
            MessageBox::Show("Product updated!", "Success",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
            this->Close();
        }

        void btnRestock_Click(Object^ sender, EventArgs^ e) {
            int qty;
            if (!Int32::TryParse(txtRestockQty->Text, qty) || qty <= 0) {
                MessageBox::Show("Enter a valid quantity."); return;
            }
            pm->increaseStockInDB(productID, qty);
            MessageBox::Show("Stock increased by " + qty + "!", "Restocked",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
            txtRestockQty->Text = "0";
        }

        void btnCancel_Click(Object^ sender, EventArgs^ e) { this->Close(); }
    };
}