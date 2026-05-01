#pragma once
#include "constants.h"
#include "database.h"
#include "session.h"
#include "PaymentForm.h"

namespace SUper {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Data::SqlClient;

    public ref class BillingForm : public System::Windows::Forms::Form
    {
    public:
        BillingForm(DataGridView^ cartGrid)
        {
            InitializeComponent();
            this->savedCartGrid = cartGrid;

            // Compute totals from the cart grid
            double subtotal = 0;
            int itemCount = 0;
            for (int i = 0; i < cartGrid->Rows->Count; i++) {
                if (!cartGrid->Rows[i]->IsNewRow) {
                    double total = Convert::ToDouble(cartGrid->Rows[i]->Cells["colTotal"]->Value);
                    subtotal += total;
                    itemCount++;
                }
            }

            double discount = 0;
            if (itemCount >= DISCOUNT_THRESHOLD_2)
                discount = subtotal * DISCOUNT_RATE_2;
            else if (itemCount >= DISCOUNT_THRESHOLD_1)
                discount = subtotal * DISCOUNT_RATE_1;

            double tax = (subtotal - discount) * TAX_RATE;
            double grandTotal = subtotal - discount + tax;

            this->totalSubtotal = subtotal;
            this->totalDiscount = discount;
            this->totalTax = tax;
            this->totalGrand = grandTotal;

            lblStoreName->Text = "ValueMart - Billing Summary";
            lblSubtotal->Text = "Subtotal:    Rs " + subtotal.ToString("F2");
            lblDiscount->Text = "Discount:    Rs " + discount.ToString("F2");
            lblTax->Text = "Tax (" + (TAX_RATE * 100).ToString("F0") + "%):   Rs " + tax.ToString("F2");
            lblGrandTotal->Text = "Grand Total: Rs " + grandTotal.ToString("F2");
        }

    protected:
        ~BillingForm() { if (components) delete components; }

    private:
        System::ComponentModel::Container^ components;
        DataGridView^ savedCartGrid;
        double totalSubtotal;
        double totalDiscount;
        double totalTax;
        double totalGrand;
        System::Windows::Forms::Label^ lblStoreName;
        System::Windows::Forms::Label^ lblSubtotal;
        System::Windows::Forms::Label^ lblDiscount;
        System::Windows::Forms::Label^ lblTax;
        System::Windows::Forms::Label^ lblGrandTotal;
        System::Windows::Forms::Button^ btnProceed;
        System::Windows::Forms::Panel^ divider;
        System::Windows::Forms::Button^ btnBack;

        void InitializeComponent(void)
        {
            this->lblStoreName = (gcnew System::Windows::Forms::Label());
            this->lblSubtotal = (gcnew System::Windows::Forms::Label());
            this->lblDiscount = (gcnew System::Windows::Forms::Label());
            this->lblTax = (gcnew System::Windows::Forms::Label());
            this->lblGrandTotal = (gcnew System::Windows::Forms::Label());
            this->btnProceed = (gcnew System::Windows::Forms::Button());
            this->btnBack = (gcnew System::Windows::Forms::Button());
            this->divider = (gcnew System::Windows::Forms::Panel());
            this->SuspendLayout();

            // lblStoreName
            this->lblStoreName->BackColor = System::Drawing::Color::FromArgb(27, 94, 32);
            this->lblStoreName->Font = (gcnew System::Drawing::Font(L"Arial", 16, System::Drawing::FontStyle::Bold));
            this->lblStoreName->ForeColor = System::Drawing::Color::White;
            this->lblStoreName->Location = System::Drawing::Point(0, 0);
            this->lblStoreName->Name = L"lblStoreName";
            this->lblStoreName->Size = System::Drawing::Size(500, 70);
            this->lblStoreName->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
            this->lblStoreName->TabIndex = 0;

            // lblSubtotal
            this->lblSubtotal->Font = (gcnew System::Drawing::Font(L"Arial", 11));
            this->lblSubtotal->ForeColor = System::Drawing::Color::FromArgb(33, 33, 33);
            this->lblSubtotal->Location = System::Drawing::Point(80, 110);
            this->lblSubtotal->Name = L"lblSubtotal";
            this->lblSubtotal->Size = System::Drawing::Size(340, 30);

            // lblDiscount
            this->lblDiscount->Font = (gcnew System::Drawing::Font(L"Arial", 11));
            this->lblDiscount->ForeColor = System::Drawing::Color::FromArgb(198, 40, 40);
            this->lblDiscount->Location = System::Drawing::Point(80, 150);
            this->lblDiscount->Name = L"lblDiscount";
            this->lblDiscount->Size = System::Drawing::Size(340, 30);

            // lblTax
            this->lblTax->Font = (gcnew System::Drawing::Font(L"Arial", 11));
            this->lblTax->ForeColor = System::Drawing::Color::FromArgb(33, 33, 33);
            this->lblTax->Location = System::Drawing::Point(80, 190);
            this->lblTax->Name = L"lblTax";
            this->lblTax->Size = System::Drawing::Size(340, 30);

            // lblGrandTotal
            this->lblGrandTotal->Font = (gcnew System::Drawing::Font(L"Arial", 14, System::Drawing::FontStyle::Bold));
            this->lblGrandTotal->ForeColor = System::Drawing::Color::FromArgb(27, 94, 32);
            this->lblGrandTotal->Location = System::Drawing::Point(80, 245);
            this->lblGrandTotal->Name = L"lblGrandTotal";
            this->lblGrandTotal->Size = System::Drawing::Size(340, 40);

            // btnProceed
            this->btnProceed->BackColor = System::Drawing::Color::FromArgb(27, 94, 32);
            this->btnProceed->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnProceed->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
            this->btnProceed->ForeColor = System::Drawing::Color::White;
            this->btnProceed->Location = System::Drawing::Point(260, 340);
            this->btnProceed->Anchor = static_cast<AnchorStyles>(AnchorStyles::Bottom | AnchorStyles::Left);
            this->btnProceed->Name = L"btnProceed";
            this->btnProceed->Size = System::Drawing::Size(210, 38);
            this->btnProceed->Text = L"Proceed to Payment (F4)";
            this->btnProceed->UseVisualStyleBackColor = false;
            this->btnProceed->Click += gcnew System::EventHandler(this, &BillingForm::btnProceed_Click);

            // btnBack
            this->btnBack->BackColor = System::Drawing::Color::FromArgb(66, 66, 66);
            this->btnBack->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnBack->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
            this->btnBack->ForeColor = System::Drawing::Color::White;
            this->btnBack->Location = System::Drawing::Point(30, 340);
            this->btnBack->Anchor = static_cast<AnchorStyles>(AnchorStyles::Bottom | AnchorStyles::Left);
            this->btnBack->Name = L"btnBack";
            this->btnBack->Size = System::Drawing::Size(160, 38);
            this->btnBack->Text = L"Back to Cart (esc)";
            this->btnBack->UseVisualStyleBackColor = false;
            this->btnBack->Click += gcnew System::EventHandler(this, &BillingForm::btnBack_Click);

            // divider
            this->divider->BackColor = System::Drawing::Color::FromArgb(27, 94, 32);
            this->divider->Location = System::Drawing::Point(80, 235);
            this->divider->Name = L"divider";
            this->divider->Size = System::Drawing::Size(340, 2);

            // BillingForm
            this->BackColor = System::Drawing::Color::WhiteSmoke;
            this->ClientSize = System::Drawing::Size(478, 394);
            this->MaximizeBox = false;
            this->WindowState = System::Windows::Forms::FormWindowState::Normal;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Controls->Add(this->lblStoreName);
            this->Controls->Add(this->lblSubtotal);
            this->Controls->Add(this->lblDiscount);
            this->Controls->Add(this->lblTax);
            this->Controls->Add(this->divider);
            this->Controls->Add(this->lblGrandTotal);
            this->Controls->Add(this->btnBack);
            this->Controls->Add(this->btnProceed);
            this->KeyPreview = true;
            this->Name = L"BillingForm";
            this->Text = L"ValueMart - Billing Summary";
            this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &BillingForm::BillingForm_KeyDown);
            this->ResumeLayout(false);
        }

    private:
        System::Void btnBack_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }

        System::Void btnProceed_Click(System::Object^ sender, System::EventArgs^ e) {
            // Save bill to DB using parameterized SQL
            int userID = SBS::Session::IsLoggedIn() ? SBS::Session::GetUserID() : 1;

            Object^ result = SBS::Database::ExecuteScalar(
                "INSERT INTO Bills (Date, UserID, Subtotal, Discount, Tax, Total) "
                "VALUES (GETDATE(), @uid, @sub, @disc, @tax, @tot); "
                "SELECT SCOPE_IDENTITY();",
                gcnew SqlParameter("@uid", userID),
                gcnew SqlParameter("@sub", totalSubtotal),
                gcnew SqlParameter("@disc", totalDiscount),
                gcnew SqlParameter("@tax", totalTax),
                gcnew SqlParameter("@tot", totalGrand));

            if (result == nullptr || result == System::DBNull::Value) {
                MessageBox::Show("Failed to save bill!", "Error");
                return;
            }

            int billNo = Convert::ToInt32(result);

            // Insert each item from cartGrid into BillItems and decrease stock
            for (int i = 0; i < savedCartGrid->Rows->Count; i++) {
                if (savedCartGrid->Rows[i]->IsNewRow) continue;

                int productID = Convert::ToInt32(savedCartGrid->Rows[i]->Cells["colID"]->Value);
                int qty = Convert::ToInt32(savedCartGrid->Rows[i]->Cells["colQty"]->Value);
                double price = Convert::ToDouble(savedCartGrid->Rows[i]->Cells["colPrice"]->Value);

                SBS::Database::ExecuteNonQuery(
                    "INSERT INTO BillItems (BillNo, ProductID, Quantity, Price) "
                    "VALUES (@bill, @prod, @qty, @price)",
                    gcnew SqlParameter("@bill", billNo),
                    gcnew SqlParameter("@prod", productID),
                    gcnew SqlParameter("@qty", qty),
                    gcnew SqlParameter("@price", price));

                SBS::Database::ExecuteNonQuery(
                    "UPDATE Products SET Stock = Stock - @qty WHERE ProductID = @prod",
                    gcnew SqlParameter("@qty", qty),
                    gcnew SqlParameter("@prod", productID));
            }

            PaymentForm^ paymentForm = gcnew PaymentForm(billNo, totalGrand);
            paymentForm->ShowDialog();
            this->Close();
        }

        System::Void BillingForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
            if (e->KeyCode == Keys::F4)     btnProceed->PerformClick();
            if (e->KeyCode == Keys::Escape) btnBack->PerformClick();
            e->Handled = true;
        }
    };
}