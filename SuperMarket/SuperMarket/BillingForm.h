#pragma once
#include "Billing.h"

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

            lblStoreName->Text = "SuperMarket Billing Summary";
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
            this->Text = "Billing Summary";
            this->Size = System::Drawing::Size(500, 400);
            this->StartPosition = FormStartPosition::CenterScreen;

            // Store Name
            this->lblStoreName->Location = System::Drawing::Point(100, 30);
            this->lblStoreName->Size = System::Drawing::Size(300, 35);
            this->lblStoreName->Font = (gcnew System::Drawing::Font(L"Arial", 14, System::Drawing::FontStyle::Bold));
            this->lblStoreName->TextAlign = ContentAlignment::MiddleCenter;

            // Subtotal
            this->lblSubtotal->Location = System::Drawing::Point(80, 100);
            this->lblSubtotal->Size = System::Drawing::Size(300, 30);
            this->lblSubtotal->Font = (gcnew System::Drawing::Font(L"Arial", 11));

            // Discount
            this->lblDiscount->Location = System::Drawing::Point(80, 140);
            this->lblDiscount->Size = System::Drawing::Size(300, 30);
            this->lblDiscount->Font = (gcnew System::Drawing::Font(L"Arial", 11));

            // Tax
            this->lblTax->Location = System::Drawing::Point(80, 180);
            this->lblTax->Size = System::Drawing::Size(300, 30);
            this->lblTax->Font = (gcnew System::Drawing::Font(L"Arial", 11));

            // Grand Total
            this->lblGrandTotal->Location = System::Drawing::Point(80, 230);
            this->lblGrandTotal->Size = System::Drawing::Size(300, 35);
            this->lblGrandTotal->Font = (gcnew System::Drawing::Font(L"Arial", 13, System::Drawing::FontStyle::Bold));

            // Proceed Button
            this->btnProceed->Location = System::Drawing::Point(280, 300);
            this->btnProceed->Size = System::Drawing::Size(150, 35);
            this->btnProceed->Text = L"Proceed to Payment";
            this->btnProceed->Click += gcnew System::EventHandler(this, &BillingForm::btnProceed_Click);

            // Back Button
            this->btnBack->Location = System::Drawing::Point(80, 300);
            this->btnBack->Size = System::Drawing::Size(100, 35);
            this->btnBack->Text = L"Back to Cart";
            this->btnBack->Click += gcnew System::EventHandler(this, &BillingForm::btnBack_Click);

            // Add controls
            this->Controls->Add(this->lblStoreName);
            this->Controls->Add(this->lblSubtotal);
            this->Controls->Add(this->lblDiscount);
            this->Controls->Add(this->lblTax);
            this->Controls->Add(this->lblGrandTotal);
            this->Controls->Add(this->btnProceed);
            this->Controls->Add(this->btnBack);

            this->ResumeLayout(false);
        }

    private:
        System::Void btnBack_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }
        System::Void btnProceed_Click(System::Object^ sender, System::EventArgs^ e) {
            MessageBox::Show("Proceeding to Payment...", "Payment");
            // Member 4's PaymentForm will be opened here
        }
    };
}