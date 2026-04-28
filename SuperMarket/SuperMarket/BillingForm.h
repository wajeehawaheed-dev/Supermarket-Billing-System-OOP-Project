#pragma once
#include "Billing.h"
#include "database.h"
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
	private: System::Windows::Forms::Panel^ divider;
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
			// 
			// lblStoreName
			// 
			this->lblStoreName->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(27)), static_cast<System::Int32>(static_cast<System::Byte>(94)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)));
			this->lblStoreName->Font = (gcnew System::Drawing::Font(L"Arial", 16, System::Drawing::FontStyle::Bold));
			this->lblStoreName->ForeColor = System::Drawing::Color::White;
			this->lblStoreName->Location = System::Drawing::Point(0, 0);
			this->lblStoreName->Name = L"lblStoreName";
			this->lblStoreName->Size = System::Drawing::Size(500, 70);
			this->lblStoreName->TabIndex = 0;
			// 
			// lblSubtotal
			// 
			this->lblSubtotal->Font = (gcnew System::Drawing::Font(L"Arial", 11));
			this->lblSubtotal->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(33)), static_cast<System::Int32>(static_cast<System::Byte>(33)),
				static_cast<System::Int32>(static_cast<System::Byte>(33)));
			this->lblSubtotal->Location = System::Drawing::Point(80, 110);
			this->lblSubtotal->Name = L"lblSubtotal";
			this->lblSubtotal->Size = System::Drawing::Size(340, 30);
			this->lblSubtotal->TabIndex = 1;
			// 
			// lblDiscount
			// 
			this->lblDiscount->Font = (gcnew System::Drawing::Font(L"Arial", 11));
			this->lblDiscount->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(198)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->lblDiscount->Location = System::Drawing::Point(80, 150);
			this->lblDiscount->Name = L"lblDiscount";
			this->lblDiscount->Size = System::Drawing::Size(340, 30);
			this->lblDiscount->TabIndex = 2;
			// 
			// lblTax
			// 
			this->lblTax->Font = (gcnew System::Drawing::Font(L"Arial", 11));
			this->lblTax->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(33)), static_cast<System::Int32>(static_cast<System::Byte>(33)),
				static_cast<System::Int32>(static_cast<System::Byte>(33)));
			this->lblTax->Location = System::Drawing::Point(80, 190);
			this->lblTax->Name = L"lblTax";
			this->lblTax->Size = System::Drawing::Size(340, 30);
			this->lblTax->TabIndex = 3;
			this->lblTax->Click += gcnew System::EventHandler(this, &BillingForm::lblTax_Click);
			// 
			// lblGrandTotal
			// 
			this->lblGrandTotal->Font = (gcnew System::Drawing::Font(L"Arial", 14, System::Drawing::FontStyle::Bold));
			this->lblGrandTotal->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(27)), static_cast<System::Int32>(static_cast<System::Byte>(94)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)));
			this->lblGrandTotal->Location = System::Drawing::Point(80, 245);
			this->lblGrandTotal->Name = L"lblGrandTotal";
			this->lblGrandTotal->Size = System::Drawing::Size(340, 40);
			this->lblGrandTotal->TabIndex = 5;
			// 
			// btnProceed
			// 
			this->btnProceed->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(27)), static_cast<System::Int32>(static_cast<System::Byte>(94)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)));
			this->btnProceed->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnProceed->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->btnProceed->ForeColor = System::Drawing::Color::White;
			this->btnProceed->Location = System::Drawing::Point(260, 340);
			this->btnProceed->Name = L"btnProceed";
			this->btnProceed->Size = System::Drawing::Size(210, 38);
			this->btnProceed->TabIndex = 7;
			this->btnProceed->Text = L"Proceed to Payment (F4)";
			this->btnProceed->UseVisualStyleBackColor = false;
			this->btnProceed->Click += gcnew System::EventHandler(this, &BillingForm::btnProceed_Click);
			// 
			// btnBack
			// 
			this->btnBack->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(66)), static_cast<System::Int32>(static_cast<System::Byte>(66)),
				static_cast<System::Int32>(static_cast<System::Byte>(66)));
			this->btnBack->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnBack->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			this->btnBack->ForeColor = System::Drawing::Color::White;
			this->btnBack->Location = System::Drawing::Point(30, 340);
			this->btnBack->Name = L"btnBack";
			this->btnBack->Size = System::Drawing::Size(160, 38);
			this->btnBack->TabIndex = 6;
			this->btnBack->Text = L"Back to Cart (esc)";
			this->btnBack->UseVisualStyleBackColor = false;
			this->btnBack->Click += gcnew System::EventHandler(this, &BillingForm::btnBack_Click);
			// 
			// divider
			// 
			this->divider->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(27)), static_cast<System::Int32>(static_cast<System::Byte>(94)),
				static_cast<System::Int32>(static_cast<System::Byte>(32)));
			this->divider->Location = System::Drawing::Point(80, 235);
			this->divider->Name = L"divider";
			this->divider->Size = System::Drawing::Size(340, 2);
			this->divider->TabIndex = 4;
			// 
			// BillingForm
			// 
			this->BackColor = System::Drawing::Color::WhiteSmoke;
			this->ClientSize = System::Drawing::Size(478, 394);
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
			CartItem* items = savedCart->getItems();
			int itemCount = savedCart->getCount();
			for (int i = 0; i < itemCount; i++) {
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
	private: System::Void BillingForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::F4)     btnProceed->PerformClick();  // F4 = Proceed to Payment
		if (e->KeyCode == Keys::Escape) btnBack->PerformClick();     // Escape = Back to Cart
		e->Handled = true;
	}
	private: System::Void lblTax_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}