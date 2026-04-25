#pragma once
#include "Cart.h"
#include "constants.h"
#include "BillingForm.h"
#include "SettingsForm.h"
namespace SuperMarket {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for CartForm
	/// </summary>
	public ref class CartForm : public System::Windows::Forms::Form
	{
	public:
		CartForm(void)
		{
			InitializeComponent();
			cart = new Cart();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CartForm()
		{
			if (components)
			{
				delete components;
			}
			delete cart;
		}
	private: System::Windows::Forms::DataGridView^ cartGrid;
	private: Cart* cart;
	protected:

	private: System::Windows::Forms::Button^ button1; // Add Item button
	private: System::Windows::Forms::Button^ button2; // Remove Item button
	private: System::Windows::Forms::Button^ button3; // Clear Cart button
	private: System::Windows::Forms::Button^ btnBilling; // Proceed to Billing button
	private: System::Windows::Forms::Button^ btnSettings; // Settings button
	private: System::Windows::Forms::Label^ lblSubtotal; // Subtotal label
	private: System::Windows::Forms::Label^ lblDiscount; // Discount label
	private: System::Windows::Forms::Label^ lblTax; // Tax label
	private: System::Windows::Forms::Label^ lblGrandTotal; // Grand Total label
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colID; // Product ID column
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colName; // Name column
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colPrice; // Price column
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colQty; // Quantity column
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colTotal; // Total column
	protected:

	protected:




	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		/// Initializes all the controls on the form, sets their properties, and adds them to the form's control collection.
		void InitializeComponent(void)
		{
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
			// 
			// cartGrid
			// 
			this->cartGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->cartGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
				this->colID, this->colName,
					this->colPrice, this->colQty, this->colTotal
			});
			this->cartGrid->Location = System::Drawing::Point(1, 1);
			this->cartGrid->Name = L"cartGrid";
			this->cartGrid->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
			this->cartGrid->RowHeadersWidth = 62;
			this->cartGrid->RowTemplate->Height = 28;
			this->cartGrid->Size = System::Drawing::Size(1751, 550);
			this->cartGrid->TabIndex = 0;
			this->cartGrid->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &CartForm::dataGridView1_CellContentClick);
			// 
			// colID
			// 
			this->colID->HeaderText = L"Product ID";
			this->colID->MinimumWidth = 8;
			this->colID->Name = L"colID";
			this->colID->Width = 150;
			// 
			// colName
			// 
			this->colName->HeaderText = L"Name";
			this->colName->MinimumWidth = 8;
			this->colName->Name = L"colName";
			this->colName->Width = 150;
			// 
			// colPrice
			// 
			this->colPrice->HeaderText = L"Price";
			this->colPrice->MinimumWidth = 8;
			this->colPrice->Name = L"colPrice";
			this->colPrice->Width = 150;
			// 
			// colQty
			// 
			this->colQty->HeaderText = L"Quantity";
			this->colQty->MinimumWidth = 8;
			this->colQty->Name = L"colQty";
			this->colQty->Width = 150;
			// 
			// colTotal
			// 
			this->colTotal->HeaderText = L"Total";
			this->colTotal->MinimumWidth = 8;
			this->colTotal->Name = L"colTotal";
			this->colTotal->Width = 150;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 570);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(143, 31);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Add Item";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &CartForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(173, 570);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(143, 29);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Remove Item";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &CartForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(340, 570);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(152, 31);
			this->button3->TabIndex = 3;
			this->button3->Text = L"Clear Cart";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &CartForm::button3_Click);
			//
			// btnBilling
			//
			this->btnBilling->Location = System::Drawing::Point(510, 570);
			this->btnBilling->Size = System::Drawing::Size(180, 31);
			this->btnBilling->Text = L"Proceed to Billing";
			this->btnBilling->Click += gcnew System::EventHandler(this, &CartForm::btnBilling_Click);
			//
			// btnSettings
			// 
			this->btnSettings->Location = System::Drawing::Point(710, 570);
			this->btnSettings->Size = System::Drawing::Size(130, 31);
			this->btnSettings->Text = L"Settings";
			this->btnSettings->Click += gcnew System::EventHandler(this, &CartForm::btnSettings_Click);
			// 
			// lblSubtotal
			//
			this->lblSubtotal->Location = System::Drawing::Point(12, 615);
			this->lblSubtotal->Size = System::Drawing::Size(300, 30);
			this->lblSubtotal->Text = L"Subtotal: Rs 0";
			//
			// lblDiscount
			//
			this->lblDiscount->Location = System::Drawing::Point(12, 645);
			this->lblDiscount->Size = System::Drawing::Size(300, 30);
			this->lblDiscount->Text = L"Discount: Rs 0";
			//
			// lblTax
			//
			this->lblTax->Location = System::Drawing::Point(12, 675);
			this->lblTax->Size = System::Drawing::Size(300, 30);
			this->lblTax->Text = L"Tax (17%): Rs 0";
			//
			// lblGrandTotal
			//
			this->lblGrandTotal->Location = System::Drawing::Point(12, 705);
			this->lblGrandTotal->Size = System::Drawing::Size(300, 30);
			this->lblGrandTotal->Font = (gcnew System::Drawing::Font(L"Arial", 11, System::Drawing::FontStyle::Bold));
			this->lblGrandTotal->Text = L"Grand Total: Rs 0";
			// 
			// CartForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1751, 750);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->lblSubtotal);
			this->Controls->Add(this->lblDiscount);
			this->Controls->Add(this->lblTax);
			this->Controls->Add(this->lblGrandTotal);
			this->Controls->Add(this->cartGrid);
			this->Controls->Add(this->btnBilling);
			this->Controls->Add(this->btnSettings);
			this->Name = L"CartForm";
			this->Text = L"CartForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->cartGrid))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
	}
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
		if(itemCount >= DISCOUNT_THRESHOLD_2) {
			discount = subtotal * DISCOUNT_RATE_2;
		}
		else if(itemCount >= DISCOUNT_THRESHOLD_1) {
			discount = subtotal * DISCOUNT_RATE_1;
		}
		double tax = (subtotal - discount) * TAX_RATE;
		double grandTotal = subtotal - discount + tax;
		lblSubtotal->Text = "Subtotal: Rs " + subtotal.ToString("F2");
		lblDiscount->Text = "Discount: Rs " + discount.ToString("F2");
		lblTax->Text = "Tax (" + (TAX_RATE * 100).ToString("F0") + "%): Rs " + tax.ToString("F2");
		lblGrandTotal->Text = "Grand Total: Rs " + grandTotal.ToString("F2");
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		//creating Input Form
		Form^ inputForm = gcnew Form();
		inputForm->Text = "Add Item";
		inputForm->Size = System::Drawing::Size(300, 250);
		inputForm->StartPosition = FormStartPosition::CenterParent;
		Label^ lblID = gcnew Label();
		lblID->Text = "Product ID:";
		lblID->Location = System::Drawing::Point(20, 20);
		TextBox^ txtID = gcnew TextBox();
		txtID->Location = System::Drawing::Point(130, 20);
		Label^ lblName = gcnew Label();
		lblName->Text = "Product Name:";
		lblName->Location = System::Drawing::Point(20, 60);
		TextBox^ txtName = gcnew TextBox();
		txtName->Location = System::Drawing::Point(130, 60);
		Label^ lblPrice = gcnew Label();
		lblPrice->Text = "Price:";
		lblPrice->Location = System::Drawing::Point(20, 100);
		TextBox^ txtPrice = gcnew TextBox();
		txtPrice->Location = System::Drawing::Point(130, 100);
		Label^ lblQty = gcnew Label();
		lblQty->Text = "Quantity:";
		lblQty->Location = System::Drawing::Point(20, 140);
		TextBox^ txtQty = gcnew TextBox();
		txtQty->Location = System::Drawing::Point(130, 140);
		Button^ btnOK = gcnew Button();
		btnOK->Text = "Add";
		btnOK->Location = System::Drawing::Point(100, 180);
		btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
		inputForm->Controls->Add(lblID);
		inputForm->Controls->Add(txtID);
		inputForm->Controls->Add(lblName);
		inputForm->Controls->Add(txtName);
		inputForm->Controls->Add(lblPrice);
		inputForm->Controls->Add(txtPrice);
		inputForm->Controls->Add(lblQty);
		inputForm->Controls->Add(txtQty);
		inputForm->Controls->Add(btnOK);
		inputForm->AcceptButton = btnOK;
		// Show the input form and process the result
		if (inputForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			// Check nothing is empty
			if (txtID->Text == "" || txtName->Text == "" ||
				txtPrice->Text == "" || txtQty->Text == "") {
				MessageBox::Show("Please fill all fields!", "Error");
				return;
			}
			// Check ID and Qty are valid numbers
			int id, qty;
			double price;
			if (!Int32::TryParse(txtID->Text, id)) {
				MessageBox::Show("Product ID must be a number!", "Error");
				return;
			}
			if (!Double::TryParse(txtPrice->Text, price)) {
				MessageBox::Show("Price must be a number!", "Error");
				return;
			}
			if (!Int32::TryParse(txtQty->Text, qty)) {
				MessageBox::Show("Quantity must be a number!", "Error");
				return;
			}
			String^ name = txtName->Text;
			double total = price * qty;
			cartGrid->Rows->Add(id, name, price, qty, total);
			std::string stdName = "";
			for (int i = 0; i < name->Length; i++)
				stdName += (char)name[i];
			cart->addItem(id, stdName, price, qty);
			UpdateTotals();
		}
	}
	// Click Handlers
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		if(cartGrid->SelectedRows->Count > 0) {
			int index = cartGrid->SelectedRows[0]->Index;
			if(!cartGrid->Rows[index]->IsNewRow) {
				cartGrid->Rows->RemoveAt(index);
				UpdateTotals();
			}
			else {
				MessageBox::Show("Cannot remove an empty row!","Warning");
			}
		}
		else {
			MessageBox::Show("Please select a row to remove!","Warning");
		}
	}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	cartGrid->Rows->Clear();
	UpdateTotals();
}
private: System::Void btnBilling_Click(System::Object^ sender, System::EventArgs^ e) {
	if (cartGrid->Rows->Count <= 1) {
		MessageBox::Show("Cart is empty! Please add items before proceeding to billing.", "Warning");
		return;
	}
	BillingForm^ billingForm = gcnew BillingForm(cart);
	billingForm->ShowDialog();
}
	   private: System::Void btnSettings_Click(System::Object^ sender, System::EventArgs^ e) {
		   SettingsForm^ settings = gcnew SettingsForm();
		   settings->ShowDialog();
		   UpdateTotals(); // Recalculate totals in case settings changed
	   }
};
}

