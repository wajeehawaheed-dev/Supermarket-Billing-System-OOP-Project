#pragma once
#include "constants.h"
#include "database.h"

namespace SuperMarket {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class SettingsForm : public System::Windows::Forms::Form
	{
	public:
		SettingsForm(void)
		{
			InitializeComponent();
			// Load current values into textboxes
			txtTax->Text = TAX_RATE.ToString();
			txtThreshold1->Text = DISCOUNT_THRESHOLD_1.ToString();
			txtDiscount1->Text = DISCOUNT_RATE_1.ToString();
			txtThreshold2->Text = DISCOUNT_THRESHOLD_2.ToString();
			txtDiscount2->Text = DISCOUNT_RATE_2.ToString();
		}

	protected:
		~SettingsForm() { if (components) delete components; }

	private:
		System::ComponentModel::Container^ components;
		System::Windows::Forms::Label^ lblTitle;
		System::Windows::Forms::Label^ lblTax;
		System::Windows::Forms::Label^ lblDiscount1;
		System::Windows::Forms::Label^ lblDiscount2;
		System::Windows::Forms::Label^ lblThreshold1;
		System::Windows::Forms::Label^ lblThreshold2;
		System::Windows::Forms::TextBox^ txtTax;
		System::Windows::Forms::TextBox^ txtDiscount1;
		System::Windows::Forms::TextBox^ txtDiscount2;
		System::Windows::Forms::TextBox^ txtThreshold1;
		System::Windows::Forms::TextBox^ txtThreshold2;
		System::Windows::Forms::Button^ btnSave;
		System::Windows::Forms::Button^ btnCancel;

		void InitializeComponent(void)
		{
			this->lblTitle = (gcnew System::Windows::Forms::Label());
			this->lblTax = (gcnew System::Windows::Forms::Label());
			this->lblDiscount1 = (gcnew System::Windows::Forms::Label());
			this->lblDiscount2 = (gcnew System::Windows::Forms::Label());
			this->lblThreshold1 = (gcnew System::Windows::Forms::Label());
			this->lblThreshold2 = (gcnew System::Windows::Forms::Label());
			this->txtTax = (gcnew System::Windows::Forms::TextBox());
			this->txtDiscount1 = (gcnew System::Windows::Forms::TextBox());
			this->txtDiscount2 = (gcnew System::Windows::Forms::TextBox());
			this->txtThreshold1 = (gcnew System::Windows::Forms::TextBox());
			this->txtThreshold2 = (gcnew System::Windows::Forms::TextBox());
			this->btnSave = (gcnew System::Windows::Forms::Button());
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();

			// Form
			this->Text = "ValueMart - Admin Settings";
			this->Size = System::Drawing::Size(480, 480);
			this->StartPosition = FormStartPosition::CenterScreen;
			this->BackColor = System::Drawing::Color::WhiteSmoke;

			// Title Header
			this->lblTitle->Location = System::Drawing::Point(0, 0);
			this->lblTitle->Size = System::Drawing::Size(480, 65);
			this->lblTitle->Font = (gcnew System::Drawing::Font(L"Arial", 15, System::Drawing::FontStyle::Bold));
			this->lblTitle->ForeColor = System::Drawing::Color::White;
			this->lblTitle->BackColor = System::Drawing::Color::FromArgb(27, 94, 32);
			this->lblTitle->Text = "Admin Settings";
			this->lblTitle->TextAlign = ContentAlignment::MiddleCenter;

			// Tax Rate
			this->lblTax->Text = "Tax Rate (e.g. 0.17):";
			this->lblTax->Location = System::Drawing::Point(30, 100);
			this->lblTax->Size = System::Drawing::Size(200, 25);
			this->lblTax->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->txtTax->Location = System::Drawing::Point(260, 100);
			this->txtTax->Size = System::Drawing::Size(150, 25);
			this->txtTax->Font = (gcnew System::Drawing::Font(L"Arial", 10));

			// Threshold 1
			this->lblThreshold1->Text = "Discount 1 - Min Items:";
			this->lblThreshold1->Location = System::Drawing::Point(30, 150);
			this->lblThreshold1->Size = System::Drawing::Size(200, 25);
			this->lblThreshold1->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->txtThreshold1->Location = System::Drawing::Point(260, 150);
			this->txtThreshold1->Size = System::Drawing::Size(150, 25);
			this->txtThreshold1->Font = (gcnew System::Drawing::Font(L"Arial", 10));

			// Discount Rate 1
			this->lblDiscount1->Text = "Discount 1 - Rate (e.g. 0.10):";
			this->lblDiscount1->Location = System::Drawing::Point(30, 200);
			this->lblDiscount1->Size = System::Drawing::Size(200, 25);
			this->lblDiscount1->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->txtDiscount1->Location = System::Drawing::Point(260, 200);
			this->txtDiscount1->Size = System::Drawing::Size(150, 25);
			this->txtDiscount1->Font = (gcnew System::Drawing::Font(L"Arial", 10));

			// Threshold 2
			this->lblThreshold2->Text = "Discount 2 - Min Items:";
			this->lblThreshold2->Location = System::Drawing::Point(30, 250);
			this->lblThreshold2->Size = System::Drawing::Size(200, 25);
			this->lblThreshold2->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->txtThreshold2->Location = System::Drawing::Point(260, 250);
			this->txtThreshold2->Size = System::Drawing::Size(150, 25);
			this->txtThreshold2->Font = (gcnew System::Drawing::Font(L"Arial", 10));

			// Discount Rate 2
			this->lblDiscount2->Text = "Discount 2 - Rate (e.g. 0.20):";
			this->lblDiscount2->Location = System::Drawing::Point(30, 300);
			this->lblDiscount2->Size = System::Drawing::Size(200, 25);
			this->lblDiscount2->Font = (gcnew System::Drawing::Font(L"Arial", 10));
			this->txtDiscount2->Location = System::Drawing::Point(260, 300);
			this->txtDiscount2->Size = System::Drawing::Size(150, 25);
			this->txtDiscount2->Font = (gcnew System::Drawing::Font(L"Arial", 10));

			// Save Button
			this->btnSave->Text = "Save Settings (F4)";
			this->btnSave->Location = System::Drawing::Point(260, 390);
			this->btnSave->Size = System::Drawing::Size(150, 38);
			this->btnSave->BackColor = System::Drawing::Color::FromArgb(27, 94, 32);
			this->btnSave->ForeColor = System::Drawing::Color::White;
			this->btnSave->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnSave->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->btnSave->Click += gcnew System::EventHandler(this, &SettingsForm::btnSave_Click);

			// Cancel Button
			this->btnCancel->Text = "Cancel (esc)";
			this->btnCancel->Location = System::Drawing::Point(60, 390);
			this->btnCancel->Size = System::Drawing::Size(120, 38);
			this->btnCancel->BackColor = System::Drawing::Color::FromArgb(66, 66, 66);
			this->btnCancel->ForeColor = System::Drawing::Color::White;
			this->btnCancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnCancel->Font = (gcnew System::Drawing::Font(L"Arial", 10, System::Drawing::FontStyle::Bold));
			this->btnCancel->Click += gcnew System::EventHandler(this, &SettingsForm::btnCancel_Click);

			// Add controls
			this->Controls->Add(this->lblTitle);
			this->Controls->Add(this->lblTax);
			this->Controls->Add(this->txtTax);
			this->Controls->Add(this->lblThreshold1);
			this->Controls->Add(this->txtThreshold1);
			this->Controls->Add(this->lblDiscount1);
			this->Controls->Add(this->txtDiscount1);
			this->Controls->Add(this->lblThreshold2);
			this->Controls->Add(this->txtThreshold2);
			this->Controls->Add(this->lblDiscount2);
			this->Controls->Add(this->txtDiscount2);
			this->Controls->Add(this->btnSave);
			this->Controls->Add(this->btnCancel);
			this->KeyPreview = true;
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &SettingsForm::SettingsForm_KeyDown);

			this->ResumeLayout(false);
		}

	private:
		System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
			double tax, d1, d2;
			int t1, t2;

			if (!Double::TryParse(txtTax->Text, tax) || tax <= 0) {
				MessageBox::Show("Invalid tax rate!", "Error"); return;
			}
			if (!Int32::TryParse(txtThreshold1->Text, t1) || t1 <= 0) {
				MessageBox::Show("Invalid Discount 1 threshold!", "Error"); return;
			}
			if (!Double::TryParse(txtDiscount1->Text, d1) || d1 <= 0) {
				MessageBox::Show("Invalid Discount 1 rate!", "Error"); return;
			}
			if (!Int32::TryParse(txtThreshold2->Text, t2) || t2 <= t1) {
				MessageBox::Show("Discount 2 threshold must be greater than Discount 1!", "Error"); return;
			}
			if (!Double::TryParse(txtDiscount2->Text, d2) || d2 <= d1) {
				MessageBox::Show("Discount 2 rate must be greater than Discount 1!", "Error"); return;
			}

			TAX_RATE = tax;
			DISCOUNT_THRESHOLD_1 = t1;
			DISCOUNT_RATE_1 = d1;
			DISCOUNT_THRESHOLD_2 = t2;
			DISCOUNT_RATE_2 = d2;

			SBS::Database::ExecuteNonQuery("UPDATE Settings SET SettingValue = '" + tax.ToString() + "' WHERE SettingName = 'TAX_RATE'");
			SBS::Database::ExecuteNonQuery("UPDATE Settings SET SettingValue = '" + t1.ToString() + "' WHERE SettingName = 'DISCOUNT_THRESHOLD_1'");
			SBS::Database::ExecuteNonQuery("UPDATE Settings SET SettingValue = '" + d1.ToString() + "' WHERE SettingName = 'DISCOUNT_RATE_1'");
			SBS::Database::ExecuteNonQuery("UPDATE Settings SET SettingValue = '" + t2.ToString() + "' WHERE SettingName = 'DISCOUNT_THRESHOLD_2'");
			SBS::Database::ExecuteNonQuery("UPDATE Settings SET SettingValue = '" + d2.ToString() + "' WHERE SettingName = 'DISCOUNT_RATE_2'");

			MessageBox::Show("Settings saved successfully!", "Success");
			this->Close();
		}

		System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e) {
			this->Close();
		}
	private: System::Void SettingsForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::F4)     btnSave->PerformClick();     // F4 = Save
		if (e->KeyCode == Keys::Escape) btnCancel->PerformClick();   // Escape = Cancel
		e->Handled = true;
	}
	};
}