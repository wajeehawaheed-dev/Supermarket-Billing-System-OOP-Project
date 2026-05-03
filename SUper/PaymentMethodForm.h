#pragma once
#include "database.h"

namespace SUper {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class PaymentMethodForm : public System::Windows::Forms::Form
	{
	public:
		PaymentMethodForm(void)
		{
			InitializeComponent();
			LoadReport();
		}

	protected:
		~PaymentMethodForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ lblTitle;
	private: System::Windows::Forms::Label^ lblSubtitle;
	private: System::Windows::Forms::DataGridView^ dgvPayments;
	private: System::Windows::Forms::Label^ lblTotal;
	private: System::Windows::Forms::Button^ btnRefresh;
	private: System::Windows::Forms::Button^ btnClose;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->lblTitle = (gcnew System::Windows::Forms::Label());
			this->lblSubtitle = (gcnew System::Windows::Forms::Label());
			this->dgvPayments = (gcnew System::Windows::Forms::DataGridView());
			this->lblTotal = (gcnew System::Windows::Forms::Label());
			this->btnRefresh = (gcnew System::Windows::Forms::Button());
			this->btnClose = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvPayments))->BeginInit();
			this->SuspendLayout();
			// 
			// lblTitle
			// 
			this->lblTitle->AutoSize = true;
			this->lblTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTitle->Location = System::Drawing::Point(225, 9);
			this->lblTitle->Name = L"lblTitle";
			this->lblTitle->Size = System::Drawing::Size(265, 24);
			this->lblTitle->TabIndex = 0;
			this->lblTitle->Text = L"Revenue by Payment Method";
			// 
			// lblSubtitle
			// 
			this->lblSubtitle->AutoSize = true;
			this->lblSubtitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblSubtitle->Location = System::Drawing::Point(220, 38);
			this->lblSubtitle->Name = L"lblSubtitle";
			this->lblSubtitle->Size = System::Drawing::Size(280, 15);
			this->lblSubtitle->TabIndex = 1;
			this->lblSubtitle->Text = L"Approved payments only — cancelled bills excluded";
			// 
			// dgvPayments
			// 
			this->dgvPayments->AllowUserToAddRows = false;
			this->dgvPayments->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvPayments->Location = System::Drawing::Point(12, 75);
			this->dgvPayments->Name = L"dgvPayments";
			this->dgvPayments->ReadOnly = true;
			this->dgvPayments->Size = System::Drawing::Size(700, 300);
			this->dgvPayments->TabIndex = 2;
			// 
			// lblTotal
			// 
			this->lblTotal->AutoSize = true;
			this->lblTotal->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTotal->Location = System::Drawing::Point(20, 395);
			this->lblTotal->Name = L"lblTotal";
			this->lblTotal->Size = System::Drawing::Size(175, 20);
			this->lblTotal->TabIndex = 3;
			this->lblTotal->Text = L"Total Revenue: Rs 0.00";
			// 
			// btnRefresh
			// 
			this->btnRefresh->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnRefresh->Location = System::Drawing::Point(526, 395);
			this->btnRefresh->Name = L"btnRefresh";
			this->btnRefresh->Size = System::Drawing::Size(90, 30);
			this->btnRefresh->TabIndex = 4;
			this->btnRefresh->Text = L"⟳ Refresh";
			this->btnRefresh->UseVisualStyleBackColor = true;
			this->btnRefresh->Click += gcnew System::EventHandler(this, &PaymentMethodForm::btnRefresh_Click);
			// 
			// btnClose
			// 
			this->btnClose->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnClose->Location = System::Drawing::Point(622, 395);
			this->btnClose->Name = L"btnClose";
			this->btnClose->Size = System::Drawing::Size(90, 30);
			this->btnClose->TabIndex = 5;
			this->btnClose->Text = L"Close";
			this->btnClose->UseVisualStyleBackColor = true;
			this->btnClose->Click += gcnew System::EventHandler(this, &PaymentMethodForm::btnClose_Click);
			// 
			// PaymentMethodForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(734, 440);
			this->Controls->Add(this->btnClose);
			this->Controls->Add(this->btnRefresh);
			this->Controls->Add(this->lblTotal);
			this->Controls->Add(this->dgvPayments);
			this->Controls->Add(this->lblSubtitle);
			this->Controls->Add(this->lblTitle);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"PaymentMethodForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Payment Methods - ValueMart";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvPayments))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion

	private: System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e) {
		LoadReport();
	}

	private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}

		   void LoadReport() {
			   DataTable^ result = SBS::Database::ExecuteQuery(
				   "SELECT "
				   "  p.Method, "
				   "  COUNT(*)            AS PaymentCount, "
				   "  SUM(p.AmountPaid)   AS TotalPaid, "
				   "  SUM(p.ChangeAmount) AS TotalChange, "
				   "  SUM(b.Total)        AS BillTotal "
				   "FROM Payments p "
				   "JOIN Bills b ON b.BillNo = p.BillNo "
				   "WHERE p.Status = 'Approved' "
				   "  AND b.IsCancelled = 0 "
				   "GROUP BY p.Method "
				   "ORDER BY BillTotal DESC");

			   dgvPayments->DataSource = result;

			   if (result == nullptr || result->Rows->Count == 0) {
				   lblTotal->Text = "Total Revenue: Rs 0.00 (no approved payments)";
				   return;
			   }

			   double total = 0.0;
			   for each (DataRow ^ row in result->Rows) {
				   if (row["BillTotal"] != DBNull::Value) {
					   total += Convert::ToDouble(row["BillTotal"]);
				   }
			   }
			   lblTotal->Text = "Total Revenue: Rs " + total.ToString("N2");
		   }
	};
}