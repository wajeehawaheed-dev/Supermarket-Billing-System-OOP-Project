#define WIN32_LEAN_AND_MEAN
#pragma once
#include "database.h"
#include "product.h"
#include <msclr/marshal_cppstd.h>

namespace SUper {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Data::SqlClient;

    public ref class AddProductForm : public Form {
    private:
        ProductManager* pm;
        TextBox^ txtName;
        TextBox^ txtCategory;
        TextBox^ txtPrice;
        TextBox^ txtStock;
        Button^ btnSave;
        Button^ btnCancel;

    public:
        AddProductForm() {
            pm = new ProductManager();
            InitializeComponent();
        }
        ~AddProductForm() { delete pm; }

    private:
        void InitializeComponent() {
            this->Text = "Add New Product";
            this->Size = System::Drawing::Size(350, 300);
            this->StartPosition = FormStartPosition::CenterParent;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->BackColor = System::Drawing::Color::WhiteSmoke;

            Label^ lblName = gcnew Label();
            lblName->Text = "Name:";
            lblName->Location = System::Drawing::Point(20, 20);
            lblName->Size = System::Drawing::Size(100, 22);
            txtName = gcnew TextBox();
            txtName->Location = System::Drawing::Point(130, 18);
            txtName->Size = System::Drawing::Size(190, 26);
            txtName->Font = gcnew System::Drawing::Font("Segoe UI", 10);

            Label^ lblCategory = gcnew Label();
            lblCategory->Text = "Category:";
            lblCategory->Location = System::Drawing::Point(20, 58);
            lblCategory->Size = System::Drawing::Size(100, 22);
            txtCategory = gcnew TextBox();
            txtCategory->Location = System::Drawing::Point(130, 56);
            txtCategory->Size = System::Drawing::Size(190, 26);
            txtCategory->Font = gcnew System::Drawing::Font("Segoe UI", 10);

            Label^ lblPrice = gcnew Label();
            lblPrice->Text = "Price (Rs.):";
            lblPrice->Location = System::Drawing::Point(20, 96);
            lblPrice->Size = System::Drawing::Size(100, 22);
            txtPrice = gcnew TextBox();
            txtPrice->Location = System::Drawing::Point(130, 94);
            txtPrice->Size = System::Drawing::Size(190, 26);
            txtPrice->Font = gcnew System::Drawing::Font("Segoe UI", 10);

            Label^ lblStock = gcnew Label();
            lblStock->Text = "Stock:";
            lblStock->Location = System::Drawing::Point(20, 134);
            lblStock->Size = System::Drawing::Size(100, 22);
            txtStock = gcnew TextBox();
            txtStock->Location = System::Drawing::Point(130, 132);
            txtStock->Size = System::Drawing::Size(190, 26);
            txtStock->Font = gcnew System::Drawing::Font("Segoe UI", 10);

            btnSave = gcnew Button();
            btnSave->Text = "Add Product";
            btnSave->Location = System::Drawing::Point(50, 200);
            btnSave->Size = System::Drawing::Size(120, 36);
            btnSave->BackColor = System::Drawing::Color::SeaGreen;
            btnSave->ForeColor = System::Drawing::Color::White;
            btnSave->FlatStyle = FlatStyle::Flat;
            btnSave->Font = gcnew System::Drawing::Font("Segoe UI", 10, System::Drawing::FontStyle::Bold);
            btnSave->Click += gcnew EventHandler(this, &AddProductForm::btnSave_Click);

            btnCancel = gcnew Button();
            btnCancel->Text = "Cancel";
            btnCancel->Location = System::Drawing::Point(185, 200);
            btnCancel->Size = System::Drawing::Size(100, 36);
            btnCancel->BackColor = System::Drawing::Color::Crimson;
            btnCancel->ForeColor = System::Drawing::Color::White;
            btnCancel->FlatStyle = FlatStyle::Flat;
            btnCancel->Font = gcnew System::Drawing::Font("Segoe UI", 10);
            btnCancel->Click += gcnew EventHandler(this, &AddProductForm::btnCancel_Click);

            this->Controls->Add(lblName);     this->Controls->Add(txtName);
            this->Controls->Add(lblCategory); this->Controls->Add(txtCategory);
            this->Controls->Add(lblPrice);    this->Controls->Add(txtPrice);
            this->Controls->Add(lblStock);    this->Controls->Add(txtStock);
            this->Controls->Add(btnSave);
            this->Controls->Add(btnCancel);
        }

        void btnSave_Click(Object^ sender, EventArgs^ e) {
            if (txtName->Text->Trim() == "") { MessageBox::Show("Name cannot be empty."); return; }
            if (txtCategory->Text->Trim() == "") { MessageBox::Show("Category cannot be empty."); return; }
            double price;
            if (!Double::TryParse(txtPrice->Text, price) || price <= 0) {
                MessageBox::Show("Enter a valid price."); return;
            }
            int stock;
            if (!Int32::TryParse(txtStock->Text, stock) || stock < 0) {
                MessageBox::Show("Enter a valid stock quantity."); return;
            }
            string sName = msclr::interop::marshal_as<string>(txtName->Text->Trim());
            string sCat = msclr::interop::marshal_as<string>(txtCategory->Text->Trim());
            pm->addToDB(sName, sCat, price, stock);
            MessageBox::Show("Product added successfully!", "Success",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
            this->Close();
        }

        void btnCancel_Click(Object^ sender, EventArgs^ e) { this->Close(); }
    };
}