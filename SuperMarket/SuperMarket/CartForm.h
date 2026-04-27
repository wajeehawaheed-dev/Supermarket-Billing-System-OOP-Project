#pragma once
#include "Cart.h"
#include "constants.h"
#include "BillingForm.h"
#include "SettingsForm.h"
#include "database.h"

namespace SuperMarket {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class CartForm : public System::Windows::Forms::Form
	{
	public:
		CartForm(String^ role)
		{
			InitializeComponent();
			cart = new Cart();
			currentRole = role;
			// Hide Settings if not Admin
			if (currentRole->ToLower() != "admin") {
				btnSettings->Visible = false;
			}

			// Load settings from DB
			DataTable^ settings = SBS::Database::ExecuteQuery(
				"SELECT SettingName, SettingValue FROM Settings");
			for (int i = 0; i < settings->Rows->Count; i++) {
				String^ name = settings->Rows[i]["SettingName"]->ToString();
				String^ value = settings->Rows[i]["SettingValue"]->ToString();
				if (name == "TAX_RATE")             TAX_RATE = Double::Parse(value);
				if (name == "DISCOUNT_THRESHOLD_1") DISCOUNT_THRESHOLD_1 = Int32::Parse(value);
				if (name == "DISCOUNT_RATE_1")      DISCOUNT_RATE_1 = Double::Parse(value);
				if (name == "DISCOUNT_THRESHOLD_2") DISCOUNT_THRESHOLD_2 = Int32::Parse(value);
				if (name == "DISCOUNT_RATE_2")      DISCOUNT_RATE_2 = Double::Parse(value);
			}
			UpdateTotals();
		}

	protected:
		~CartForm()
		{
			if (components) delete components;
			delete cart;
		}

	private: System::Windows::Forms::Panel^ headerPanel;
	private: String^ currentRole;
	private: System::Windows::Forms::Label^ lblHeader;
	private: System::Windows::Forms::DataGridView^ cartGrid;
	private: Cart* cart;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ btnBilling;
	private: System::Windows::Forms::Button^ btnSettings;
	private: System::Windows::Forms::Label^ lblSubtotal;
	private: System::Windows::Forms::Label^ lblDiscount;
	private: System::Windows::Forms::Label^ lblTax;
	private: System::Windows::Forms::Label^ lblGrandTotal;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colID;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colName;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colPrice;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colQty;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colTotal;
	private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->headerPanel = (gcnew System::Windows::Forms::Panel());
			   this->lblHeader = (gcnew System::Windows::Forms::Label());
			   this->cartGrid = (gcnew System::Windows::Forms::DataGridView());
			   this->colID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->colName = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->colPrice = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->colQty = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->colTotal = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->button3 = (gcnew System::Windows::Forms::Button());
			   this->btnBilling = (gcnew System::Windows::Forms::Button());
			   this->btnSettings = (gcnew System::Windows::Forms::Button());
			   this->lblSubtotal = (gcnew System::Windows::Forms::Label());
			   this->lblDiscount = (gcnew System::Windows::Forms::Label());
			   this->lblTax = (gcnew System::Windows::Forms::Label());
			   this->lblGrandTotal = (gcnew System::Windows::Forms::Label());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cartGrid))->BeginInit();
			   this->SuspendLayout();

			   // Header Panel
			   this->headerPanel->Location = System::Drawing::Point(0, 0);
			   this->headerPanel->Size = System::Drawing::Size(1751, 70);
			   this->headerPanel->BackColor = System::Drawing::Color::FromArgb(27, 94, 32);
			   this->headerPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(
				   System::Windows::Forms::AnchorStyles::Top |
				   System::Windows::Forms::AnchorStyles::Left |
				   System::Windows::Forms::AnchorStyles::Right);

			   // Header Label
			   this->lblHeader->Text = L"ValueMart - Billing System";
			   this->lblHeader->Font = (gcnew System::Drawing::Font(L"Arial", 20, System::Drawing::FontStyle::Bold));
			   this->lblHeader->ForeColor = System::Drawing::Color::White;
			   this->lblHeader->Location = System::Drawing::Point(0, 0);
			   this->lblHeader->Size = System::Drawing::Size(1751, 70);
			   this->lblHeader->TextAlign = ContentAlignment::MiddleCenter;
			   this->headerPanel->Controls->Add(this->lblHeader);

			   // cartGrid
			   this->cartGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			   this->cartGrid->Columns->AddRange(gcnew cli::array<System::Windows::Forms::DataGridViewColumn^>(5) {
				   this->colID, this->colName, this->colPrice, this->colQty, this->colTotal
			   });
			   this->cartGrid->Location = System::Drawing::Point(1, 71);
			   this->cartGrid->Size = System::Drawing::Size(1751, 550);
			   this->cartGrid->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(
				   System::Windows::Forms::AnchorStyles::Top |
				   System::Windows::Forms::AnchorStyles::Left |
				   System::Windows::Forms::AnchorStyles::Right |
				   System::Windows::Forms::AnchorStyles::Bottom);
			   this->cartGrid->Name = L"cartGrid";
			   this->cartGrid->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
			   this->cartGrid->RowHeadersWidth = 62;
			   this->cartGrid->RowTemplate->Height = 28;
			   this->cartGrid->BackgroundColor = System::Drawing::Color::White;
			   this->cartGrid->BorderStyle = System::Windows::Forms::BorderStyle::None;
			   this->cartGrid->GridColor = System::Drawing::Color::FromArgb(200, 230, 201);
			   this->cartGrid->TabIndex = 0;
			   this->cartGrid->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &CartForm::dataGridView1_CellContentClick);
			   this->cartGrid->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &CartForm::cartGrid_KeyDown);

			   // Columns
			   this->colID->HeaderText = L"Product ID"; this->colID->Name = L"colID";    this->colID->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;
			   this->colName->HeaderText = L"Name";       this->colName->Name = L"colName";  this->colName->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;
			   this->colPrice->HeaderText = L"Price";      this->colPrice->Name = L"colPrice"; this->colPrice->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;
			   this->colQty->HeaderText = L"Quantity";   this->colQty->Name = L"colQty";   this->colQty->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;
			   this->colTotal->HeaderText = L"Total";      this->colTotal->Name = L"colTotal"; this->colTotal->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;

			   // button1 - Add Item
			   this->button1->Location = System::Drawing::Point(12, 640);
			   this->button1->Size = System::Drawing::Size(160, 35);
			   this->button1->Text = L"Add Item (F1)";
			   this->button1->BackColor = System::Drawing::Color::FromArgb(46, 125, 50);
			   this->button1->ForeColor = System::Drawing::Color::White;
			   this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->button1->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			   this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(
				   System::Windows::Forms::AnchorStyles::Bottom |
				   System::Windows::Forms::AnchorStyles::Left);
			   this->button1->Click += gcnew System::EventHandler(this, &CartForm::button1_Click);

			   // button2 - Remove Item
			   this->button2->Location = System::Drawing::Point(182, 640);
			   this->button2->Size = System::Drawing::Size(190, 35);
			   this->button2->Text = L"Remove Item (F2)";
			   this->button2->BackColor = System::Drawing::Color::FromArgb(198, 40, 40);
			   this->button2->ForeColor = System::Drawing::Color::White;
			   this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->button2->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			   this->button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(
				   System::Windows::Forms::AnchorStyles::Bottom |
				   System::Windows::Forms::AnchorStyles::Left);
			   this->button2->Click += gcnew System::EventHandler(this, &CartForm::button2_Click);

			   // button3 - Clear Cart
			   this->button3->Location = System::Drawing::Point(382, 640);
			   this->button3->Size = System::Drawing::Size(160, 35);
			   this->button3->Text = L"Clear Cart (F3)";
			   this->button3->BackColor = System::Drawing::Color::FromArgb(230, 81, 0);
			   this->button3->ForeColor = System::Drawing::Color::White;
			   this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->button3->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			   this->button3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(
				   System::Windows::Forms::AnchorStyles::Bottom |
				   System::Windows::Forms::AnchorStyles::Left);
			   this->button3->Click += gcnew System::EventHandler(this, &CartForm::button3_Click);

			   // btnBilling
			   this->btnBilling->Location = System::Drawing::Point(552, 640);
			   this->btnBilling->Size = System::Drawing::Size(210, 35);
			   this->btnBilling->Text = L"Proceed to Billing (F4)";
			   this->btnBilling->BackColor = System::Drawing::Color::FromArgb(27, 94, 32);
			   this->btnBilling->ForeColor = System::Drawing::Color::White;
			   this->btnBilling->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->btnBilling->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			   this->btnBilling->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(
				   System::Windows::Forms::AnchorStyles::Bottom |
				   System::Windows::Forms::AnchorStyles::Left);
			   this->btnBilling->Click += gcnew System::EventHandler(this, &CartForm::btnBilling_Click);

			   // btnSettings
			   this->btnSettings->Location = System::Drawing::Point(772, 640);
			   this->btnSettings->Size = System::Drawing::Size(150, 35);
			   this->btnSettings->Text = L"Settings (F5)";
			   this->btnSettings->BackColor = System::Drawing::Color::FromArgb(66, 66, 66);
			   this->btnSettings->ForeColor = System::Drawing::Color::White;
			   this->btnSettings->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->btnSettings->Font = (gcnew System::Drawing::Font(L"Arial", 9, System::Drawing::FontStyle::Bold));
			   this->btnSettings->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(
				   System::Windows::Forms::AnchorStyles::Bottom |
				   System::Windows::Forms::AnchorStyles::Left);
			   this->btnSettings->Click += gcnew System::EventHandler(this, &CartForm::btnSettings_Click);

			   // Labels
			   this->lblSubtotal->Location = System::Drawing::Point(12, 690);
			   this->lblSubtotal->Size = System::Drawing::Size(300, 30);
			   this->lblSubtotal->Text = L"Subtotal: Rs 0";
			   this->lblSubtotal->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			   this->lblSubtotal->ForeColor = System::Drawing::Color::FromArgb(27, 94, 32);
			   this->lblSubtotal->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(
				   System::Windows::Forms::AnchorStyles::Bottom |
				   System::Windows::Forms::AnchorStyles::Left);

			   this->lblDiscount->Location = System::Drawing::Point(12, 720);
			   this->lblDiscount->Size = System::Drawing::Size(300, 30);
			   this->lblDiscount->Text = L"Discount: Rs 0";
			   this->lblDiscount->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			   this->lblDiscount->ForeColor = System::Drawing::Color::FromArgb(27, 94, 32);
			   this->lblDiscount->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(
				   System::Windows::Forms::AnchorStyles::Bottom |
				   System::Windows::Forms::AnchorStyles::Left);

			   this->lblTax->Location = System::Drawing::Point(12, 750);
			   this->lblTax->Size = System::Drawing::Size(300, 30);
			   this->lblTax->Text = L"Tax (17%): Rs 0";
			   this->lblTax->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			   this->lblTax->ForeColor = System::Drawing::Color::FromArgb(27, 94, 32);
			   this->lblTax->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(
				   System::Windows::Forms::AnchorStyles::Bottom |
				   System::Windows::Forms::AnchorStyles::Left);

			   this->lblGrandTotal->Location = System::Drawing::Point(12, 780);
			   this->lblGrandTotal->Size = System::Drawing::Size(300, 30);
			   this->lblGrandTotal->Text = L"Grand Total: Rs 0";
			   this->lblGrandTotal->Font = (gcnew System::Drawing::Font(L"Arial", 11, System::Drawing::FontStyle::Bold));
			   this->lblGrandTotal->ForeColor = System::Drawing::Color::FromArgb(27, 94, 32);
			   this->lblGrandTotal->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(
				   System::Windows::Forms::AnchorStyles::Bottom |
				   System::Windows::Forms::AnchorStyles::Left);

			   // Form
			   this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1760, 830);
			   this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			   this->BackColor = System::Drawing::Color::WhiteSmoke;
			   this->KeyPreview = true;
			   this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &CartForm::CartForm_KeyDown);
			   this->Name = L"CartForm";
			   this->Text = L"ValueMart - Billing System";

			   this->Controls->Add(this->headerPanel);
			   this->Controls->Add(this->cartGrid);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->button2);
			   this->Controls->Add(this->button3);
			   this->Controls->Add(this->btnBilling);
			   this->Controls->Add(this->btnSettings);
			   this->Controls->Add(this->lblSubtotal);
			   this->Controls->Add(this->lblDiscount);
			   this->Controls->Add(this->lblTax);
			   this->Controls->Add(this->lblGrandTotal);

			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cartGrid))->EndInit();
			   this->ResumeLayout(false);
		   }
#pragma endregion

	private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {}

	private: void UpdateTotals() {
		double subtotal = 0;
		for (int i = 0; i < cartGrid->Rows->Count; i++) {
			if (!cartGrid->Rows[i]->IsNewRow) {
				double val = Double::Parse(cartGrid->Rows[i]->Cells["colTotal"]->Value->ToString());
				subtotal += val;
			}
		}
		int itemCount = cartGrid->Rows->Count - 1;
		double discount = 0;
		if (itemCount >= DISCOUNT_THRESHOLD_2)
			discount = subtotal * DISCOUNT_RATE_2;
		else if (itemCount >= DISCOUNT_THRESHOLD_1)
			discount = subtotal * DISCOUNT_RATE_1;
		double tax = (subtotal - discount) * TAX_RATE;
		double grandTotal = subtotal - discount + tax;
		lblSubtotal->Text = "Subtotal: Rs " + subtotal.ToString("F2");
		lblDiscount->Text = "Discount: Rs " + discount.ToString("F2");
		lblTax->Text = "Tax (" + (TAX_RATE * 100).ToString("F0") + "%): Rs " + tax.ToString("F2");
		lblGrandTotal->Text = "Grand Total: Rs " + grandTotal.ToString("F2");
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		Form^ searchForm = gcnew Form();
		searchForm->Text = "Add Item";
		searchForm->Size = System::Drawing::Size(350, 180);
		searchForm->StartPosition = FormStartPosition::CenterParent;
		searchForm->BackColor = System::Drawing::Color::WhiteSmoke;

		Label^ lblName = gcnew Label();
		lblName->Text = "Product Name:";
		lblName->Location = System::Drawing::Point(20, 20);
		lblName->Size = System::Drawing::Size(110, 25);

		TextBox^ txtName = gcnew TextBox();
		txtName->Location = System::Drawing::Point(140, 20);
		txtName->Size = System::Drawing::Size(150, 25);

		Label^ lblQty = gcnew Label();
		lblQty->Text = "Quantity:";
		lblQty->Location = System::Drawing::Point(20, 60);
		lblQty->Size = System::Drawing::Size(110, 25);

		TextBox^ txtQty = gcnew TextBox();
		txtQty->Location = System::Drawing::Point(140, 60);
		txtQty->Size = System::Drawing::Size(80, 25);

		Button^ btnOK = gcnew Button();
		btnOK->Text = "Add to Cart";
		btnOK->Location = System::Drawing::Point(140, 100);
		btnOK->Size = System::Drawing::Size(150, 30);
		btnOK->BackColor = System::Drawing::Color::FromArgb(27, 94, 32);
		btnOK->ForeColor = System::Drawing::Color::White;
		btnOK->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;

		searchForm->Controls->Add(lblName);
		searchForm->Controls->Add(txtName);
		searchForm->Controls->Add(lblQty);
		searchForm->Controls->Add(txtQty);
		searchForm->Controls->Add(btnOK);
		searchForm->AcceptButton = btnOK;

		if (searchForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			if (txtName->Text == "" || txtQty->Text == "") {
				MessageBox::Show("Please fill all fields!", "Error"); return;
			}
			int qty;
			if (!Int32::TryParse(txtQty->Text, qty) || qty <= 0) {
				MessageBox::Show("Quantity must be a valid number greater than 0!", "Error"); return;
			}
			String^ sql = "SELECT ProductID, Name, Price, Stock FROM Products WHERE Name LIKE '%" + txtName->Text + "%' AND IsActive = 1";
			DataTable^ result = SBS::Database::ExecuteQuery(sql);
			if (result->Rows->Count == 0) {
				MessageBox::Show("Product not found in database!", "Error"); return;
			}
			int stock = Convert::ToInt32(result->Rows[0]["Stock"]);
			if (qty > stock) {
				MessageBox::Show("Not enough stock! Available: " + stock, "Error"); return;
			}
			int id = Convert::ToInt32(result->Rows[0]["ProductID"]);
			String^ name = result->Rows[0]["Name"]->ToString();
			double price = Convert::ToDouble(result->Rows[0]["Price"]);
			double total = price * qty;
			cartGrid->Rows->Add(id, name, price, qty, total);
			std::string stdName = "";
			for (int i = 0; i < name->Length; i++) stdName += (char)name[i];
			cart->addItem(id, stdName, price, qty);
			UpdateTotals();
		}
	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		if (cartGrid->SelectedRows->Count > 0) {
			int index = cartGrid->SelectedRows[0]->Index;
			if (!cartGrid->Rows[index]->IsNewRow) {
				cartGrid->Rows->RemoveAt(index);
				UpdateTotals();
			}
			else MessageBox::Show("Cannot remove an empty row!", "Warning");
		}
		else MessageBox::Show("Please select a row to remove!", "Warning");
	}

	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		cartGrid->Rows->Clear();
		cart->clearCart();
		UpdateTotals();
	}

	private: System::Void btnBilling_Click(System::Object^ sender, System::EventArgs^ e) {
		if (cartGrid->Rows->Count <= 1) {
			MessageBox::Show("Cart is empty! Please add items first.", "Warning"); return;
		}
		BillingForm^ billingForm = gcnew BillingForm(cart);
		billingForm->ShowDialog();
	}

	private: System::Void btnSettings_Click(System::Object^ sender, System::EventArgs^ e) {
		if (currentRole->ToLower() != "admin") {
			MessageBox::Show("Access Denied! Admin only.", "Security");
			return;
		}

		SettingsForm^ settings = gcnew SettingsForm();
		settings->ShowDialog();
		UpdateTotals();
	}

	private: System::Void cartGrid_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Delete) {
			if (cartGrid->SelectedRows->Count > 0) {
				int index = cartGrid->SelectedRows[0]->Index;
				if (!cartGrid->Rows[index]->IsNewRow) {
					cartGrid->Rows->RemoveAt(index);
					cart->clearCart();
					for (int i = 0; i < cartGrid->Rows->Count; i++) {
						if (!cartGrid->Rows[i]->IsNewRow) {
							int id = Convert::ToInt32(cartGrid->Rows[i]->Cells["colID"]->Value);
							double price = Convert::ToDouble(cartGrid->Rows[i]->Cells["colPrice"]->Value);
							int qty = Convert::ToInt32(cartGrid->Rows[i]->Cells["colQty"]->Value);
							String^ name = cartGrid->Rows[i]->Cells["colName"]->Value->ToString();
							std::string stdName = "";
							for (int j = 0; j < name->Length; j++) stdName += (char)name[j];
							cart->addItem(id, stdName, price, qty);
						}
					}
					UpdateTotals();
				}
			}
		}
	}

	private: System::Void CartForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::F1) button1->PerformClick();
		if (e->KeyCode == Keys::F2) button2->PerformClick();
		if (e->KeyCode == Keys::F3) button3->PerformClick();
		if (e->KeyCode == Keys::F4) btnBilling->PerformClick();
		if (e->KeyCode == Keys::F5) btnSettings->PerformClick();
	}
	};
}