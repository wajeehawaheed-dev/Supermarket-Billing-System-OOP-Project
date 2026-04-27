#pragma once
#include "session.h"
#include "database.h"
#include "SalesReportForm.h"
#include "BestSellersForm.h"
#include "PaymentMethodForm.h"
#include "SettingsForm.h"
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
		}

	protected:
		~AdminDashboardForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lblHead;
	private: System::Windows::Forms::Label^ lblWelcome;
	private: System::Windows::Forms::Button^ btnReports;
	private: System::Windows::Forms::Button^ btnLogout;
	private: System::Windows::Forms::Button^ btnSettings;
	private: System::Windows::Forms::Button^ btnPayments;
	private: System::Windows::Forms::Button^ btnBestSellers;


	private: System::Windows::Forms::Button^ btnRefresh;

		   // Dashboard tiles - captions and values
	private: System::Windows::Forms::Label^ lblTodayCaption;
	private: System::Windows::Forms::Label^ lblTodayValue;
	private: System::Windows::Forms::Label^ lblWeekCaption;
	private: System::Windows::Forms::Label^ lblWeekValue;
	private: System::Windows::Forms::Label^ lblMonthCaption;
	private: System::Windows::Forms::Label^ lblMonthValue;
	private: System::Windows::Forms::Label^ lblAllTimeCaption;
	private: System::Windows::Forms::Label^ lblAllTimeValue;
	private: System::Windows::Forms::Button^ btnUsers;


	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->lblHead = ( gcnew System::Windows::Forms::Label() );
			this->lblWelcome = ( gcnew System::Windows::Forms::Label() );
			this->btnReports = ( gcnew System::Windows::Forms::Button() );
			this->btnLogout = ( gcnew System::Windows::Forms::Button() );
			this->btnSettings = ( gcnew System::Windows::Forms::Button() );
			this->btnPayments = ( gcnew System::Windows::Forms::Button() );
			this->btnBestSellers = ( gcnew System::Windows::Forms::Button() );
			this->lblTodayCaption = ( gcnew System::Windows::Forms::Label() );
			this->lblTodayValue = ( gcnew System::Windows::Forms::Label() );
			this->lblWeekCaption = ( gcnew System::Windows::Forms::Label() );
			this->lblWeekValue = ( gcnew System::Windows::Forms::Label() );
			this->lblMonthCaption = ( gcnew System::Windows::Forms::Label() );
			this->lblMonthValue = ( gcnew System::Windows::Forms::Label() );
			this->lblAllTimeCaption = ( gcnew System::Windows::Forms::Label() );
			this->lblAllTimeValue = ( gcnew System::Windows::Forms::Label() );
			this->btnRefresh = ( gcnew System::Windows::Forms::Button() );
			this->btnUsers = ( gcnew System::Windows::Forms::Button() );
			this->SuspendLayout();
			// 
			// lblHead
			// 
			this->lblHead->AutoSize = true;
			this->lblHead->Font = ( gcnew System::Drawing::Font(L"Microsoft Sans Serif" , 18 , System::Drawing::FontStyle::Bold , System::Drawing::GraphicsUnit::Point ,
				static_cast< System::Byte >( 0 )) );
			this->lblHead->Location = System::Drawing::Point(253 , 11);
			this->lblHead->Margin = System::Windows::Forms::Padding(4 , 0 , 4 , 0);
			this->lblHead->Name = L"lblHead";
			this->lblHead->Size = System::Drawing::Size(423 , 36);
			this->lblHead->TabIndex = 1;
			this->lblHead->Text = L"ValueMart Admin Dashboard";
			// 
			// lblWelcome
			// 
			this->lblWelcome->AutoSize = true;
			this->lblWelcome->Font = ( gcnew System::Drawing::Font(L"Microsoft Sans Serif" , 11.25F , System::Drawing::FontStyle::Regular , System::Drawing::GraphicsUnit::Point ,
				static_cast< System::Byte >( 0 )) );
			this->lblWelcome->Location = System::Drawing::Point(413 , 62);
			this->lblWelcome->Margin = System::Windows::Forms::Padding(4 , 0 , 4 , 0);
			this->lblWelcome->Name = L"lblWelcome";
			this->lblWelcome->Size = System::Drawing::Size(151 , 24);
			this->lblWelcome->TabIndex = 2;
			this->lblWelcome->Text = L"Welcome Admin";
			// 
			// btnReports
			// 
			this->btnReports->Font = ( gcnew System::Drawing::Font(L"Microsoft Sans Serif" , 9.75F) );
			this->btnReports->Location = System::Drawing::Point(320 , 222);
			this->btnReports->Margin = System::Windows::Forms::Padding(4 , 4 , 4 , 4);
			this->btnReports->Name = L"btnReports";
			this->btnReports->Size = System::Drawing::Size(333 , 49);
			this->btnReports->TabIndex = 3;
			this->btnReports->Text = L"Sales Reports";
			this->btnReports->UseVisualStyleBackColor = true;
			this->btnReports->Click += gcnew System::EventHandler(this , &AdminDashboardForm::btnReports_Click);
			// 
			// btnLogout
			// 
			this->btnLogout->ForeColor = System::Drawing::Color::Red;
			this->btnLogout->Location = System::Drawing::Point(813 , 505);
			this->btnLogout->Margin = System::Windows::Forms::Padding(4 , 4 , 4 , 4);
			this->btnLogout->Name = L"btnLogout";
			this->btnLogout->Size = System::Drawing::Size(160 , 43);
			this->btnLogout->TabIndex = 7;
			this->btnLogout->Text = L"Log Out";
			this->btnLogout->UseVisualStyleBackColor = true;
			this->btnLogout->Click += gcnew System::EventHandler(this , &AdminDashboardForm::btnLogout_Click);
			// 
			// btnSettings
			// 
			this->btnSettings->Font = ( gcnew System::Drawing::Font(L"Microsoft Sans Serif" , 9.75F) );
			this->btnSettings->Location = System::Drawing::Point(320 , 283);
			this->btnSettings->Margin = System::Windows::Forms::Padding(4 , 4 , 4 , 4);
			this->btnSettings->Name = L"btnSettings";
			this->btnSettings->Size = System::Drawing::Size(333 , 49);
			this->btnSettings->TabIndex = 8;
			this->btnSettings->Text = L"Manage Settings";
			this->btnSettings->UseVisualStyleBackColor = true;
			this->btnSettings->Click += gcnew System::EventHandler(this , &AdminDashboardForm::btnSettings_Click);
			// 
			// btnPayments
			// 
			this->btnPayments->Font = ( gcnew System::Drawing::Font(L"Microsoft Sans Serif" , 9.75F) );
			this->btnPayments->Location = System::Drawing::Point(320 , 345);
			this->btnPayments->Margin = System::Windows::Forms::Padding(4 , 4 , 4 , 4);
			this->btnPayments->Name = L"btnPayments";
			this->btnPayments->Size = System::Drawing::Size(333 , 49);
			this->btnPayments->TabIndex = 9;
			this->btnPayments->Text = L"Payment Methods";
			this->btnPayments->UseVisualStyleBackColor = true;
			this->btnPayments->Click += gcnew System::EventHandler(this , &AdminDashboardForm::btnPayments_Click);
			// 
			// btnBestSellers
			// 
			this->btnBestSellers->Font = ( gcnew System::Drawing::Font(L"Microsoft Sans Serif" , 9.75F) );
			this->btnBestSellers->Location = System::Drawing::Point(320 , 406);
			this->btnBestSellers->Margin = System::Windows::Forms::Padding(4 , 4 , 4 , 4);
			this->btnBestSellers->Name = L"btnBestSellers";
			this->btnBestSellers->Size = System::Drawing::Size(333 , 49);
			this->btnBestSellers->TabIndex = 10;
			this->btnBestSellers->Text = L"Best Sellers";
			this->btnBestSellers->UseVisualStyleBackColor = true;
			this->btnBestSellers->Click += gcnew System::EventHandler(this , &AdminDashboardForm::btnBills_Click);
			// 
			// lblTodayCaption
			// 
			this->lblTodayCaption->AutoSize = true;
			this->lblTodayCaption->Font = ( gcnew System::Drawing::Font(L"Microsoft Sans Serif" , 9) );
			this->lblTodayCaption->Location = System::Drawing::Point(53 , 117);
			this->lblTodayCaption->Margin = System::Windows::Forms::Padding(4 , 0 , 4 , 0);
			this->lblTodayCaption->Name = L"lblTodayCaption";
			this->lblTodayCaption->Size = System::Drawing::Size(49 , 18);
			this->lblTodayCaption->TabIndex = 18;
			this->lblTodayCaption->Text = L"Today";
			// 
			// lblTodayValue
			// 
			this->lblTodayValue->AutoSize = true;
			this->lblTodayValue->Font = ( gcnew System::Drawing::Font(L"Microsoft Sans Serif" , 14 , System::Drawing::FontStyle::Bold) );
			this->lblTodayValue->Location = System::Drawing::Point(53 , 142);
			this->lblTodayValue->Margin = System::Windows::Forms::Padding(4 , 0 , 4 , 0);
			this->lblTodayValue->Name = L"lblTodayValue";
			this->lblTodayValue->Size = System::Drawing::Size(100 , 29);
			this->lblTodayValue->TabIndex = 17;
			this->lblTodayValue->Text = L"Rs 0.00";
			// 
			// lblWeekCaption
			// 
			this->lblWeekCaption->AutoSize = true;
			this->lblWeekCaption->Font = ( gcnew System::Drawing::Font(L"Microsoft Sans Serif" , 9) );
			this->lblWeekCaption->Location = System::Drawing::Point(293 , 117);
			this->lblWeekCaption->Margin = System::Windows::Forms::Padding(4 , 0 , 4 , 0);
			this->lblWeekCaption->Name = L"lblWeekCaption";
			this->lblWeekCaption->Size = System::Drawing::Size(86 , 18);
			this->lblWeekCaption->TabIndex = 16;
			this->lblWeekCaption->Text = L"Last 7 Days";
			// 
			// lblWeekValue
			// 
			this->lblWeekValue->AutoSize = true;
			this->lblWeekValue->Font = ( gcnew System::Drawing::Font(L"Microsoft Sans Serif" , 14 , System::Drawing::FontStyle::Bold) );
			this->lblWeekValue->Location = System::Drawing::Point(293 , 142);
			this->lblWeekValue->Margin = System::Windows::Forms::Padding(4 , 0 , 4 , 0);
			this->lblWeekValue->Name = L"lblWeekValue";
			this->lblWeekValue->Size = System::Drawing::Size(100 , 29);
			this->lblWeekValue->TabIndex = 15;
			this->lblWeekValue->Text = L"Rs 0.00";
			// 
			// lblMonthCaption
			// 
			this->lblMonthCaption->AutoSize = true;
			this->lblMonthCaption->Font = ( gcnew System::Drawing::Font(L"Microsoft Sans Serif" , 9) );
			this->lblMonthCaption->Location = System::Drawing::Point(533 , 117);
			this->lblMonthCaption->Margin = System::Windows::Forms::Padding(4 , 0 , 4 , 0);
			this->lblMonthCaption->Name = L"lblMonthCaption";
			this->lblMonthCaption->Size = System::Drawing::Size(94 , 18);
			this->lblMonthCaption->TabIndex = 14;
			this->lblMonthCaption->Text = L"Last 30 Days";
			// 
			// lblMonthValue
			// 
			this->lblMonthValue->AutoSize = true;
			this->lblMonthValue->Font = ( gcnew System::Drawing::Font(L"Microsoft Sans Serif" , 14 , System::Drawing::FontStyle::Bold) );
			this->lblMonthValue->Location = System::Drawing::Point(533 , 142);
			this->lblMonthValue->Margin = System::Windows::Forms::Padding(4 , 0 , 4 , 0);
			this->lblMonthValue->Name = L"lblMonthValue";
			this->lblMonthValue->Size = System::Drawing::Size(100 , 29);
			this->lblMonthValue->TabIndex = 13;
			this->lblMonthValue->Text = L"Rs 0.00";
			// 
			// lblAllTimeCaption
			// 
			this->lblAllTimeCaption->AutoSize = true;
			this->lblAllTimeCaption->Font = ( gcnew System::Drawing::Font(L"Microsoft Sans Serif" , 9) );
			this->lblAllTimeCaption->Location = System::Drawing::Point(773 , 117);
			this->lblAllTimeCaption->Margin = System::Windows::Forms::Padding(4 , 0 , 4 , 0);
			this->lblAllTimeCaption->Name = L"lblAllTimeCaption";
			this->lblAllTimeCaption->Size = System::Drawing::Size(101 , 18);
			this->lblAllTimeCaption->TabIndex = 12;
			this->lblAllTimeCaption->Text = L"Bills (All Time)";
			// 
			// lblAllTimeValue
			// 
			this->lblAllTimeValue->AutoSize = true;
			this->lblAllTimeValue->Font = ( gcnew System::Drawing::Font(L"Microsoft Sans Serif" , 14 , System::Drawing::FontStyle::Bold) );
			this->lblAllTimeValue->Location = System::Drawing::Point(773 , 142);
			this->lblAllTimeValue->Margin = System::Windows::Forms::Padding(4 , 0 , 4 , 0);
			this->lblAllTimeValue->Name = L"lblAllTimeValue";
			this->lblAllTimeValue->Size = System::Drawing::Size(27 , 29);
			this->lblAllTimeValue->TabIndex = 11;
			this->lblAllTimeValue->Text = L"0";
			// 
			// btnRefresh
			// 
			this->btnRefresh->Font = ( gcnew System::Drawing::Font(L"Microsoft Sans Serif" , 9) );
			this->btnRefresh->Location = System::Drawing::Point(853 , 62);
			this->btnRefresh->Margin = System::Windows::Forms::Padding(4 , 4 , 4 , 4);
			this->btnRefresh->Name = L"btnRefresh";
			this->btnRefresh->Size = System::Drawing::Size(120 , 37);
			this->btnRefresh->TabIndex = 11;
			this->btnRefresh->Text = L"⟳ Refresh";
			this->btnRefresh->UseVisualStyleBackColor = true;
			this->btnRefresh->Click += gcnew System::EventHandler(this , &AdminDashboardForm::btnRefresh_Click);
			// 
			// btnUsers
			// 
			this->btnUsers->Font = ( gcnew System::Drawing::Font(L"Microsoft Sans Serif" , 9.75F) );
			this->btnUsers->Location = System::Drawing::Point(320 , 463);
			this->btnUsers->Margin = System::Windows::Forms::Padding(4);
			this->btnUsers->Name = L"btnUsers";
			this->btnUsers->Size = System::Drawing::Size(333 , 49);
			this->btnUsers->TabIndex = 19;
			this->btnUsers->Text = L"Manage Users";
			this->btnUsers->UseVisualStyleBackColor = true;
			// 
			// AdminDashboardForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8 , 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1000 , 566);
			this->Controls->Add(this->btnUsers);
			this->Controls->Add(this->btnLogout);
			this->Controls->Add(this->btnBestSellers);
			this->Controls->Add(this->btnPayments);
			this->Controls->Add(this->btnSettings);
			this->Controls->Add(this->btnReports);
			this->Controls->Add(this->lblAllTimeValue);
			this->Controls->Add(this->lblAllTimeCaption);
			this->Controls->Add(this->lblMonthValue);
			this->Controls->Add(this->lblMonthCaption);
			this->Controls->Add(this->lblWeekValue);
			this->Controls->Add(this->lblWeekCaption);
			this->Controls->Add(this->lblTodayValue);
			this->Controls->Add(this->lblTodayCaption);
			this->Controls->Add(this->btnRefresh);
			this->Controls->Add(this->lblWelcome);
			this->Controls->Add(this->lblHead);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Margin = System::Windows::Forms::Padding(4 , 4 , 4 , 4);
			this->MaximizeBox = false;
			this->Name = L"AdminDashboardForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Admin Dashboard - ValueMart";
			this->Load += gcnew System::EventHandler(this , &AdminDashboardForm::AdminDashboardForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion

	private: System::Void btnReports_Click(System::Object^ sender, System::EventArgs^ e) {
		SalesReportForm^ form = gcnew SalesReportForm();
		form->ShowDialog();
		LoadDashboardTiles();
	}

	private: System::Void btnSettings_Click(System::Object^ sender, System::EventArgs^ e) {
		SettingsForm^ form = gcnew SettingsForm();
		form->ShowDialog();
	}

	private: System::Void btnPayments_Click(System::Object^ sender, System::EventArgs^ e) {
		PaymentMethodForm^ form = gcnew PaymentMethodForm();
		form->ShowDialog();
	}

	private: System::Void btnBills_Click(System::Object^ sender, System::EventArgs^ e) {
		BestSellersForm^ form = gcnew BestSellersForm();
		form->ShowDialog();
	}

	private: System::Void btnLogout_Click(System::Object^ sender, System::EventArgs^ e) {
		SBS::Session::Logout();
		this->Close();
	}

	private: System::Void AdminDashboardForm_Load(System::Object^ sender, System::EventArgs^ e) {
		lblWelcome->Text = "Welcome, " + SBS::Session::GetUsername();
		LoadDashboardTiles();
	}

		   void LoadDashboardTiles() {
			   System::Data::DataTable^ result = SBS::Database::ExecuteQuery(
				   "SELECT "
				   "  SUM(CASE WHEN CAST(Date AS DATE) = CAST(GETDATE() AS DATE) THEN Total ELSE 0 END) AS Today, "
				   "  SUM(CASE WHEN Date >= DATEADD(day, -7, GETDATE())  THEN Total ELSE 0 END)         AS Last7, "
				   "  SUM(CASE WHEN Date >= DATEADD(day, -30, GETDATE()) THEN Total ELSE 0 END)         AS Last30, "
				   "  COUNT(*)                                                                          AS BillCount "
				   "FROM Bills "
				   "WHERE IsCancelled = 0");

			   if (result == nullptr || result->Rows->Count == 0) {
				   lblTodayValue->Text = "Rs 0.00";
				   lblWeekValue->Text = "Rs 0.00";
				   lblMonthValue->Text = "Rs 0.00";
				   lblAllTimeValue->Text = "0";
				   return;
			   }

			   System::Data::DataRow^ row = result->Rows[0];

			   lblTodayValue->Text = "Rs " + FormatMoney(row["Today"]);
			   lblWeekValue->Text = "Rs " + FormatMoney(row["Last7"]);
			   lblMonthValue->Text = "Rs " + FormatMoney(row["Last30"]);
			   lblAllTimeValue->Text = row["BillCount"]->ToString();
		   }

		   System::String^ FormatMoney(System::Object^ value) {
			   if (value == nullptr || value == System::DBNull::Value) {
				   return "0.00";
			   }
			   double v = System::Convert::ToDouble(value);
			   return v.ToString("N2");
		   }
		   private: System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e) {
			   LoadDashboardTiles();
		   }
	};
}