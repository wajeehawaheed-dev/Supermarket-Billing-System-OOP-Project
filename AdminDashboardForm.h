#pragma once
#include "session.h"

namespace SUper {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for AdminDashboardForm
	/// </summary>
	public ref class AdminDashboardForm : public System::Windows::Forms::Form
	{
	public:
		AdminDashboardForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AdminDashboardForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lblHead;
	protected:

	private: System::Windows::Forms::Label^ lblWelcome;
	protected:

	private: System::Windows::Forms::Button^ btnReports;
	private: System::Windows::Forms::Button^ btnLogout;





	private: System::Windows::Forms::Button^ btnSettings;
	private: System::Windows::Forms::Button^ btnUsers;
	private: System::Windows::Forms::Button^ btnBills;





	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->lblHead = (gcnew System::Windows::Forms::Label());
			this->lblWelcome = (gcnew System::Windows::Forms::Label());
			this->btnReports = (gcnew System::Windows::Forms::Button());
			this->btnLogout = (gcnew System::Windows::Forms::Button());
			this->btnSettings = (gcnew System::Windows::Forms::Button());
			this->btnUsers = (gcnew System::Windows::Forms::Button());
			this->btnBills = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// lblHead
			// 
			this->lblHead->AutoSize = true;
			this->lblHead->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblHead->Location = System::Drawing::Point(123, 9);
			this->lblHead->Name = L"lblHead";
			this->lblHead->Size = System::Drawing::Size(344, 29);
			this->lblHead->TabIndex = 1;
			this->lblHead->Text = L"ValueMart Admin Dashboard";
			// 
			// lblWelcome
			// 
			this->lblWelcome->AutoSize = true;
			this->lblWelcome->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblWelcome->Location = System::Drawing::Point(247, 57);
			this->lblWelcome->Name = L"lblWelcome";
			this->lblWelcome->Size = System::Drawing::Size(117, 18);
			this->lblWelcome->TabIndex = 2;
			this->lblWelcome->Text = L"Welcome Admin";
			// 
			// btnReports
			// 
			this->btnReports->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnReports->Location = System::Drawing::Point(174, 99);
			this->btnReports->Name = L"btnReports";
			this->btnReports->Size = System::Drawing::Size(250, 40);
			this->btnReports->TabIndex = 3;
			this->btnReports->Text = L"Sales Reports";
			this->btnReports->UseVisualStyleBackColor = true;
			this->btnReports->Click += gcnew System::EventHandler(this, &AdminDashboardForm::btnReports_Click);
			// 
			// btnLogout
			// 
			this->btnLogout->ForeColor = System::Drawing::Color::Red;
			this->btnLogout->Location = System::Drawing::Point(452, 318);
			this->btnLogout->Name = L"btnLogout";
			this->btnLogout->Size = System::Drawing::Size(120, 35);
			this->btnLogout->TabIndex = 7;
			this->btnLogout->Text = L"Log Out";
			this->btnLogout->UseVisualStyleBackColor = true;
			this->btnLogout->Click += gcnew System::EventHandler(this, &AdminDashboardForm::btnLogout_Click);
			// 
			// btnSettings
			// 
			this->btnSettings->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnSettings->Location = System::Drawing::Point(174, 145);
			this->btnSettings->Name = L"btnSettings";
			this->btnSettings->Size = System::Drawing::Size(250, 40);
			this->btnSettings->TabIndex = 8;
			this->btnSettings->Text = L"Manage Settings";
			this->btnSettings->UseVisualStyleBackColor = true;
			this->btnSettings->Click += gcnew System::EventHandler(this, &AdminDashboardForm::btnSettings_Click);
			// 
			// btnUsers
			// 
			this->btnUsers->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnUsers->Location = System::Drawing::Point(174, 191);
			this->btnUsers->Name = L"btnUsers";
			this->btnUsers->Size = System::Drawing::Size(250, 40);
			this->btnUsers->TabIndex = 9;
			this->btnUsers->Text = L"Manage Users";
			this->btnUsers->UseVisualStyleBackColor = true;
			this->btnUsers->Click += gcnew System::EventHandler(this, &AdminDashboardForm::btnUsers_Click);
			// 
			// btnBills
			// 
			this->btnBills->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnBills->Location = System::Drawing::Point(174, 237);
			this->btnBills->Name = L"btnBills";
			this->btnBills->Size = System::Drawing::Size(250, 40);
			this->btnBills->TabIndex = 10;
			this->btnBills->Text = L"View All Bills";
			this->btnBills->UseVisualStyleBackColor = true;
			this->btnBills->Click += gcnew System::EventHandler(this, &AdminDashboardForm::btnBills_Click);
			// 
			// AdminDashboardForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(584, 411);
			this->Controls->Add(this->btnBills);
			this->Controls->Add(this->btnUsers);
			this->Controls->Add(this->btnSettings);
			this->Controls->Add(this->btnLogout);
			this->Controls->Add(this->btnReports);
			this->Controls->Add(this->lblWelcome);
			this->Controls->Add(this->lblHead);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"AdminDashboardForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Admin Dashboard - ValueMart";
			this->Load += gcnew System::EventHandler(this, &AdminDashboardForm::AdminDashboardForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnReports_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show("Reports form coming soon.",
			"Coming Soon",
			MessageBoxButtons::OK,
			MessageBoxIcon::Information);
	}
private: System::Void btnSettings_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("Settings form coming soon.",
		"Coming Soon",
		MessageBoxButtons::OK,
		MessageBoxIcon::Information);
}
private: System::Void btnUsers_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("User management coming soon.",
		"Coming Soon",
		MessageBoxButtons::OK,
		MessageBoxIcon::Information);
}
private: System::Void btnBills_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBox::Show("Bills view coming soon.",
		"Coming Soon",
		MessageBoxButtons::OK,
		MessageBoxIcon::Information);
}
private: System::Void btnLogout_Click(System::Object^ sender, System::EventArgs^ e) {
	SBS::Session::Logout();
	this->Close();
}
private: System::Void AdminDashboardForm_Load(System::Object^ sender, System::EventArgs^ e) {
	lblWelcome->Text = "Welcome, " + SBS::Session::GetUsername();
}
};
}
