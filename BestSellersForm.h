#pragma once
#include "database.h"

namespace SUper {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class BestSellersForm : public System::Windows::Forms::Form
	{
	public:
		BestSellersForm(void)
		{
			InitializeComponent();
			LoadReport();
		}

	protected:
		~BestSellersForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ lblTitle;
	private: System::Windows::Forms::Label^ lblSubtitle;
	private: System::Windows::Forms::DataGridView^ dgvBestSellers;
	private: System::Windows::Forms::Button^ btnRefresh;
	private: System::Windows::Forms::Button^ btnClose;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->lblTitle = (gcnew System::Windows::Forms::Label());
			this->lblSubtitle = (gcnew System::Windows::Forms::Label());
			this->dgvBestSellers = (gcnew System::Windows::Forms::DataGridView());
			this->btnRefresh = (gcnew System::Windows::Forms::Button());
			this->btnClose = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvBestSellers))->BeginInit();
			this->SuspendLayout();
			// 
			// lblTitle
			// 
			this->lblTitle->AutoSize = true;
			this->lblTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTitle->Location = System::Drawing::Point(250, 9);
			this->lblTitle->Name = L"lblTitle";
			this->lblTitle->Size = System::Drawing::Size(209, 24);
			this->lblTitle->TabIndex = 0;
			this->lblTitle->Text = L"Best-Selling Products";
			// 
			// lblSubtitle
			// 
			this->lblSubtitle->AutoSize = true;
			this->lblSubtitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblSubtitle->Location = System::Drawing::Point(242, 54);
			this->lblSubtitle->Name = L"lblSubtitle";
			this->lblSubtitle->Size = System::Drawing::Size(261, 15);
			this->lblSubtitle->TabIndex = 1;
			this->lblSubtitle->Text = L"Ranked by units sold (excludes cancelled bills)";
			// 
			// dgvBestSellers
			// 
			this->dgvBestSellers->AllowUserToAddRows = false;
			this->dgvBestSellers->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvBestSellers->Location = System::Drawing::Point(12, 82);
			this->dgvBestSellers->Name = L"dgvBestSellers";
			this->dgvBestSellers->ReadOnly = true;
			this->dgvBestSellers->Size = System::Drawing::Size(700, 334);
			this->dgvBestSellers->TabIndex = 3;
			// 
			// btnRefresh
			// 
			this->btnRefresh->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnRefresh->Location = System::Drawing::Point(526, 426);
			this->btnRefresh->Name = L"btnRefresh";
			this->btnRefresh->Size = System::Drawing::Size(90, 30);
			this->btnRefresh->TabIndex = 4;
			this->btnRefresh->Text = L"⟳ Refresh";
			this->btnRefresh->UseVisualStyleBackColor = true;
			this->btnRefresh->Click += gcnew System::EventHandler(this, &BestSellersForm::btnRefresh_Click);
			// 
			// btnClose
			// 
			this->btnClose->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnClose->Location = System::Drawing::Point(622, 426);
			this->btnClose->Name = L"btnClose";
			this->btnClose->Size = System::Drawing::Size(90, 30);
			this->btnClose->TabIndex = 5;
			this->btnClose->Text = L"Close";
			this->btnClose->UseVisualStyleBackColor = true;
			this->btnClose->Click += gcnew System::EventHandler(this, &BestSellersForm::btnClose_Click);
			// 
			// BestSellersForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(734, 461);
			this->Controls->Add(this->btnClose);
			this->Controls->Add(this->btnRefresh);
			this->Controls->Add(this->dgvBestSellers);
			this->Controls->Add(this->lblSubtitle);
			this->Controls->Add(this->lblTitle);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"BestSellersForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Best Sellers - ValueMart";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvBestSellers))->EndInit();
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
				   "  p.Name           AS ProductName, "
				   "  p.Category, "
				   "  SUM(bi.Quantity) AS UnitsSold, "
				   "  SUM(bi.Quantity * bi.Price) AS Revenue, "
				   "  COUNT(DISTINCT bi.BillNo)   AS BillCount "
				   "FROM BillItems bi "
				   "JOIN Products p ON p.ProductID = bi.ProductID "
				   "JOIN Bills b    ON b.BillNo    = bi.BillNo "
				   "WHERE b.IsCancelled = 0 "
				   "GROUP BY p.ProductID, p.Name, p.Category "
				   "ORDER BY UnitsSold DESC");

			   dgvBestSellers->DataSource = result;
		   }
	};
}