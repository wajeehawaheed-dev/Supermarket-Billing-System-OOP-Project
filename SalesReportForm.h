#pragma once
#include "database.h"

namespace SUper {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Data::SqlClient;
	using namespace System::Drawing;

	public ref class SalesReportForm : public System::Windows::Forms::Form
	{
	public:
		SalesReportForm(void)
		{
			InitializeComponent();
			dtpFrom->Value = DateTime::Now.AddDays(-30);
			dtpTo->Value = DateTime::Now;
			LoadReport();
		}

	protected:
		~SalesReportForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lblTitle;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::DateTimePicker^ dtpFrom;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::DateTimePicker^ dtpTo;
	private: System::Windows::Forms::Button^ btnGenerate;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::Label^ lblTotalRevenue;
	private: System::Windows::Forms::Button^ btnClose;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->lblTitle = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->dtpFrom = (gcnew System::Windows::Forms::DateTimePicker());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->dtpTo = (gcnew System::Windows::Forms::DateTimePicker());
			this->btnGenerate = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->lblTotalRevenue = (gcnew System::Windows::Forms::Label());
			this->btnClose = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// lblTitle
			// 
			this->lblTitle->AutoSize = true;
			this->lblTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTitle->Location = System::Drawing::Point(245, 9);
			this->lblTitle->Name = L"lblTitle";
			this->lblTitle->Size = System::Drawing::Size(173, 20);
			this->lblTitle->TabIndex = 0;
			this->lblTitle->Text = L"Sales Report by Day";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(45, 46);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(44, 16);
			this->label1->TabIndex = 1;
			this->label1->Text = L"From: ";
			// 
			// dtpFrom
			// 
			this->dtpFrom->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->dtpFrom->Location = System::Drawing::Point(95, 42);
			this->dtpFrom->Name = L"dtpFrom";
			this->dtpFrom->Size = System::Drawing::Size(200, 20);
			this->dtpFrom->TabIndex = 2;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(461, 46);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(30, 16);
			this->label2->TabIndex = 3;
			this->label2->Text = L"To: ";
			// 
			// dtpTo
			// 
			this->dtpTo->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->dtpTo->Location = System::Drawing::Point(497, 42);
			this->dtpTo->Name = L"dtpTo";
			this->dtpTo->Size = System::Drawing::Size(200, 20);
			this->dtpTo->TabIndex = 4;
			// 
			// btnGenerate
			// 
			this->btnGenerate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnGenerate->Location = System::Drawing::Point(308, 71);
			this->btnGenerate->Name = L"btnGenerate";
			this->btnGenerate->Size = System::Drawing::Size(100, 30);
			this->btnGenerate->TabIndex = 5;
			this->btnGenerate->Text = L"Generate";
			this->btnGenerate->UseVisualStyleBackColor = true;
			this->btnGenerate->Click += gcnew System::EventHandler(this, &SalesReportForm::btnGenerate_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Location = System::Drawing::Point(12, 107);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(700, 320);
			this->dataGridView1->TabIndex = 6;
			// 
			// lblTotalRevenue
			// 
			this->lblTotalRevenue->AutoSize = true;
			this->lblTotalRevenue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTotalRevenue->Location = System::Drawing::Point(91, 491);
			this->lblTotalRevenue->Name = L"lblTotalRevenue";
			this->lblTotalRevenue->Size = System::Drawing::Size(175, 20);
			this->lblTotalRevenue->TabIndex = 7;
			this->lblTotalRevenue->Text = L"Total Revenue: Rs 0.00";
			// 
			// btnClose
			// 
			this->btnClose->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnClose->Location = System::Drawing::Point(588, 488);
			this->btnClose->Name = L"btnClose";
			this->btnClose->Size = System::Drawing::Size(80, 30);
			this->btnClose->TabIndex = 8;
			this->btnClose->Text = L"Close";
			this->btnClose->UseVisualStyleBackColor = true;
			this->btnClose->Click += gcnew System::EventHandler(this, &SalesReportForm::btnClose_Click);
			// 
			// SalesReportForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 561);
			this->Controls->Add(this->btnClose);
			this->Controls->Add(this->lblTotalRevenue);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->btnGenerate);
			this->Controls->Add(this->dtpTo);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->dtpFrom);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->lblTitle);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"SalesReportForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Sales Report - ValueMart";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion

	private: System::Void btnGenerate_Click(System::Object^ sender, System::EventArgs^ e) {
		LoadReport();
	}

	private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}

		   void LoadReport() {
			   if (dtpFrom->Value.Date > dtpTo->Value.Date) {
				   MessageBox::Show("'From' date must be before or equal to 'To' date.",
					   "Invalid Date Range",
					   MessageBoxButtons::OK,
					   MessageBoxIcon::Warning);
				   return;
			   }

			   DataTable^ result = SBS::Database::ExecuteQuery(
				   "SELECT "
				   "  CAST(Date AS DATE)  AS SaleDate, "
				   "  COUNT(*)            AS TotalBills, "
				   "  SUM(Subtotal)       AS Subtotal, "
				   "  SUM(Discount)       AS TotalDiscount, "
				   "  SUM(Tax)            AS TotalTax, "
				   "  SUM(Total)          AS Revenue "
				   "FROM Bills "
				   "WHERE IsCancelled = 0 "
				   "  AND CAST(Date AS DATE) BETWEEN @StartDate AND @EndDate "
				   "GROUP BY CAST(Date AS DATE) "
				   "ORDER BY SaleDate DESC",
				   gcnew SqlParameter("@StartDate", dtpFrom->Value.Date),
				   gcnew SqlParameter("@EndDate", dtpTo->Value.Date));

			   dataGridView1->DataSource = result;

			   if (result == nullptr || result->Rows->Count == 0) {
				   lblTotalRevenue->Text = "Total Revenue: Rs 0.00 (no sales in this period)";
				   return;
			   }

			   double total = 0.0;
			   for each (DataRow ^ row in result->Rows) {
				   if (row["Revenue"] != DBNull::Value) {
					   total += Convert::ToDouble(row["Revenue"]);
				   }
			   }
			   lblTotalRevenue->Text = "Total Revenue: Rs " + total.ToString("N2");
		   }
	};
}