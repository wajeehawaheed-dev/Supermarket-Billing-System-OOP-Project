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
            txtDiscount1->Text = DISCOUNT_RATE_1.ToString();
            txtDiscount2->Text = DISCOUNT_RATE_2.ToString();
            txtThreshold1->Text = DISCOUNT_THRESHOLD_1.ToString();
            txtThreshold2->Text = DISCOUNT_THRESHOLD_2.ToString();
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
            this->Text = "Admin Settings";
            this->Size = System::Drawing::Size(400, 400);
            this->StartPosition = FormStartPosition::CenterScreen;

            // Title
            this->lblTitle->Text = "Billing Settings";
            this->lblTitle->Location = System::Drawing::Point(100, 20);
            this->lblTitle->Size = System::Drawing::Size(200, 30);
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Arial", 13, System::Drawing::FontStyle::Bold));
            this->lblTitle->TextAlign = ContentAlignment::MiddleCenter;

            // Tax Rate
            this->lblTax->Text = "Tax Rate (e.g. 0.17):";
            this->lblTax->Location = System::Drawing::Point(30, 80);
            this->lblTax->Size = System::Drawing::Size(180, 25);
            this->txtTax->Location = System::Drawing::Point(220, 80);
            this->txtTax->Size = System::Drawing::Size(100, 25);

            // Discount Threshold 1
            this->lblThreshold1->Text = "Discount 1 - Min Items:";
            this->lblThreshold1->Location = System::Drawing::Point(30, 130);
            this->lblThreshold1->Size = System::Drawing::Size(180, 25);
            this->txtThreshold1->Location = System::Drawing::Point(220, 130);
            this->txtThreshold1->Size = System::Drawing::Size(100, 25);

            // Discount Rate 1
            this->lblDiscount1->Text = "Discount 1 - Rate (e.g. 0.10):";
            this->lblDiscount1->Location = System::Drawing::Point(30, 180);
            this->lblDiscount1->Size = System::Drawing::Size(180, 25);
            this->txtDiscount1->Location = System::Drawing::Point(220, 180);
            this->txtDiscount1->Size = System::Drawing::Size(100, 25);

            // Discount Threshold 2
            this->lblThreshold2->Text = "Discount 2 - Min Items:";
            this->lblThreshold2->Location = System::Drawing::Point(30, 230);
            this->lblThreshold2->Size = System::Drawing::Size(180, 25);
            this->txtThreshold2->Location = System::Drawing::Point(220, 230);
            this->txtThreshold2->Size = System::Drawing::Size(100, 25);

            // Discount Rate 2
            this->lblDiscount2->Text = "Discount 2 - Rate (e.g. 0.20):";
            this->lblDiscount2->Location = System::Drawing::Point(30, 280);
            this->lblDiscount2->Size = System::Drawing::Size(180, 25);
            this->txtDiscount2->Location = System::Drawing::Point(220, 280);
            this->txtDiscount2->Size = System::Drawing::Size(100, 25);

            // Save Button
            this->btnSave->Text = "Save Settings";
            this->btnSave->Location = System::Drawing::Point(220, 320);
            this->btnSave->Size = System::Drawing::Size(120, 35);
            this->btnSave->Click += gcnew System::EventHandler(this, &SettingsForm::btnSave_Click);

            // Cancel Button
            this->btnCancel->Text = "Cancel";
            this->btnCancel->Location = System::Drawing::Point(80, 320);
            this->btnCancel->Size = System::Drawing::Size(100, 35);
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

            this->ResumeLayout(false);
        }

    private:
        System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
            double tax, d1, d2;
            int t1, t2;

            // Validate all fields
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

            // Update constants
            TAX_RATE = tax;
            DISCOUNT_THRESHOLD_1 = t1;
            DISCOUNT_RATE_1 = d1;
            DISCOUNT_THRESHOLD_2 = t2;
            DISCOUNT_RATE_2 = d2;

            // Save to DB
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
    };
}