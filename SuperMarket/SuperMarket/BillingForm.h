#pragma once
#include "Billing.h"
#include "database.h"
#include <vector>
using namespace std;
namespace SuperMarket {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class BillingForm : public System::Windows::Forms::Form
    {
    public:
        BillingForm(Cart* cart)
        {
            InitializeComponent();
            Billing* billing = new Billing(cart);
            this->savedCart = cart;
            this->totalSubtotal = billing->getSubtotal();
            this->totalDiscount = billing->getDiscount();
            this->totalTax = billing->getTax();
            this->totalGrand = billing->getGrandTotal();
            lblStoreName->Text = "ValueMart- Billing Summary";
            lblSubtotal->Text = "Subtotal:    Rs " + billing->getSubtotal().ToString("F2");
            lblDiscount->Text = "Discount:    Rs " + billing->getDiscount().ToString("F2");
            lblTax->Text = "Tax (" + (TAX_RATE * 100).ToString("F0") + "%):   Rs " + billing->getTax().ToString("F2");
            lblGrandTotal->Text = "Grand Total: Rs " + billing->getGrandTotal().ToString("F2");

            delete billing;
        }

    protected:
        ~BillingForm() { if (components) delete components; }

    private:
        System::ComponentModel::Container^ components;
		Cart* savedCart;
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
            this->SuspendLayout();

            // Form
            this->Text = "ValueMart - Billing Summary";
            this->Size = System::Drawing::Size(500, 450);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->BackColor = System::Drawing::Color::WhiteSmoke;

            // Store Name
            this->lblStoreName->Location = System::Drawing::Point(0, 0);
            this->lblStoreName->Size = System::Drawing::Size(500, 70);
            this->lblStoreName->Font = (gcnew System::Drawing::Font(L"Arial", 16, System::Drawing::FontStyle::Bold));
            this->lblStoreName->ForeColor = System::Drawing::Color::White;
            this->lblStoreName->BackColor = System::Drawing::Color::FromArgb(27, 94, 32);
            this->lblStoreName->TextAlign = ContentAlignment::MiddleCenter;

            // Subtotal
            this->lblSubtotal->Location = System::Drawing::Point(80, 110);
            this->lblSubtotal->Size = System::Drawing::Size(340, 30);
            this->lblSubtotal->Font = (gcnew System::Drawing::Font(L"Arial", 11));
            this->lblSubtotal->ForeColor = System::Drawing::Color::FromArgb(33, 33, 33);

            // Discount
            this->lblDiscount->Location = System::Drawing::Point(80, 150);
            this->lblDiscount->Size = System::Drawing::Size(340, 30);
            this->lblDiscount->Font = (gcnew System::Drawing::Font(L"Arial", 11));
            this->lblDiscount->ForeColor = System::Drawing::Color::FromArgb(198, 40, 40);

            // Tax
            this->lblTax->Location = System::Drawing::Point(80, 190);
            this->lblTax->Size = System::Drawing::Size(340, 30);
            this->lblTax->Font = (gcnew System::Drawing::Font(L"Arial", 11));
            this->lblTax->ForeColor = System::Drawing::Color::FromArgb(33, 33, 33);

            // Divider panel
            System::Windows::Forms::Panel^ divider = gcnew System::Windows::Forms::Panel();
            divider->Location = System::Drawing::Point(80, 235);
            divider->Size = System::Drawing::Size(340, 2);
            divider->BackColor = System::Drawing::Color::FromArgb(27, 94, 32);

            // Grand Total
            this->lblGrandTotal->Location = System::Drawing::Point(80, 245);
            this->lblGrandTotal->Size = System::Drawing::Size(340, 40);
            this->lblGrandTotal->Font = (gcnew System::Drawing::Font(L"Arial", 14, System::Drawing::FontStyle::Bold));
            this->lblGrandTotal->ForeColor = System::Drawing::Color::FromArgb(27, 94, 32);

            // Back Button
            this->btnBack->Location = System::Drawing::Point(80, 340);
            this->btnBack->Size = System::Drawing::Size(120, 38);
            this->btnBack->Text = L"Back to Cart";
            this->btnBack->BackColor = System::Drawing::Color::FromArgb(66, 66, 66);
            this->btnBack->ForeColor = System::Drawing::Color::White;
            this->btnBack->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnBack->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
            this->btnBack->Click += gcnew System::EventHandler(this, &BillingForm::btnBack_Click);

            // Proceed Button
            this->btnProceed->Location = System::Drawing::Point(290, 340);
            this->btnProceed->Size = System::Drawing::Size(150, 38);
            this->btnProceed->Text = L"Proceed to Payment";
            this->btnProceed->BackColor = System::Drawing::Color::FromArgb(27, 94, 32);
            this->btnProceed->ForeColor = System::Drawing::Color::White;
            this->btnProceed->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnProceed->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
            this->btnProceed->Click += gcnew System::EventHandler(this, &BillingForm::btnProceed_Click);

            // Add controls
            this->Controls->Add(this->lblStoreName);
            this->Controls->Add(this->lblSubtotal);
            this->Controls->Add(this->lblDiscount);
            this->Controls->Add(this->lblTax);
            this->Controls->Add(divider);
            this->Controls->Add(this->lblGrandTotal);
            this->Controls->Add(this->btnBack);
            this->Controls->Add(this->btnProceed);

            this->ResumeLayout(false);
        }

    private:
        System::Void btnBack_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }
        System::Void btnProceed_Click(System::Object^ sender, System::EventArgs^ e) {
            // Insert into Bills table
            String^ billSQL = String::Format(
                "INSERT INTO Bills (Date, UserID, Subtotal, Discount, Tax, Total) "
                "VALUES (GETDATE(), 1, {0}, {1}, {2}, {3}); "
                "SELECT SCOPE_IDENTITY();",
                totalSubtotal, totalDiscount, totalTax, totalGrand);

            Object^ result = SBS::Database::ExecuteScalar(billSQL);

            if (result == nullptr || result == System::DBNull::Value) {
                MessageBox::Show("Failed to save bill!", "Error");
                return;
            }

            int billNo = Convert::ToInt32(result);

            // Insert each item into BillItems
            vector<CartItem> items = savedCart->getItems();
            for (int i = 0; i < items.size(); i++) {
                String^ itemSQL = String::Format(
                    "INSERT INTO BillItems (BillNo, ProductID, Quantity, Price) "
                    "VALUES ({0}, {1}, {2}, {3})",
                    billNo, items[i].productID,
                    items[i].quantity, items[i].price);
                SBS::Database::ExecuteNonQuery(itemSQL);
                // Decrease stock
                String^ stockSQL = String::Format(
                    "UPDATE Products SET Stock = Stock - {0} WHERE ProductID = {1}",
                    items[i].quantity, items[i].productID);
                SBS::Database::ExecuteNonQuery(stockSQL);
            }

            MessageBox::Show("Bill saved successfully! Bill No: " + billNo, "Success");
            // Member 4's PaymentForm will open here
        }
    };
}