#pragma once
#include "constants.h"
#include "BillingForm.h"
#include "SettingsForm.h"
#include "database.h"
#include "SearchForm.h"

namespace SUper {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;

	public ref class CartForm : public System::Windows::Forms::Form
	{
	public:
		CartForm(String^ role)
		{
			InitializeComponent();
			ApplyModernStyle();
			currentRole = role;

			lblRole->Text = L"Logged in as " + currentRole;

			if (currentRole->ToLower() != "admin") {
				btnSettings->Visible = false;
			}

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
		}

		// ===== Brand palette (matches AdminDashboardForm) =====
	private:
		static Color NAVY;
		static Color NAVY_DARK;
		static Color NAVY_HOVER;
		static Color GREEN_ACCENT;
		static Color RED_ACCENT;
		static Color ORANGE_ACCENT;
		static Color BG_LIGHT;
		static Color BORDER_GREY;
		static Color TEXT_DARK;
		static Color TEXT_MUTED;

		static CartForm()
		{
			NAVY = Color::FromArgb(30, 58, 138);
			NAVY_DARK = Color::FromArgb(15, 30, 90);
			NAVY_HOVER = Color::FromArgb(45, 75, 165);
			GREEN_ACCENT = Color::FromArgb(34, 197, 94);
			RED_ACCENT = Color::FromArgb(220, 38, 38);
			ORANGE_ACCENT = Color::FromArgb(249, 115, 22);
			BG_LIGHT = Color::FromArgb(248, 250, 252);
			BORDER_GREY = Color::FromArgb(229, 231, 235);
			TEXT_DARK = Color::FromArgb(30, 41, 59);
			TEXT_MUTED = Color::FromArgb(100, 116, 139);
		}

		// ===== Layout panels =====
	private: System::Windows::Forms::Panel^ pnlSidebar;
	private: System::Windows::Forms::Panel^ pnlContent;
	private: System::Windows::Forms::Panel^ pnlGridCard;
	private: System::Windows::Forms::Panel^ pnlSummary;

		   // ===== Sidebar controls =====
	private: System::Windows::Forms::PictureBox^ picLogo;
	private: System::Windows::Forms::Label^ lblBrand;
	private: System::Windows::Forms::Label^ lblRole;
	private: System::Windows::Forms::Label^ lblPanelLabel;

		   // ===== Action buttons (sidebar) =====
	private: System::Windows::Forms::Button^ btnAddItem;
	private: System::Windows::Forms::Button^ btnRemoveItem;
	private: System::Windows::Forms::Button^ btnClearCart;
	private: System::Windows::Forms::Button^ btnSettings;
	private: System::Windows::Forms::Button^ btnExit;

		   // ===== Content header =====
	private: System::Windows::Forms::Label^ lblHead;
	private: System::Windows::Forms::Label^ lblSubtitle;
	private: System::Windows::Forms::Label^ btnClose;
	private: System::Windows::Forms::Label^ btnMin;

		   // ===== Cart grid =====
	private: System::Windows::Forms::DataGridView^ cartGrid;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colID;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colName;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colPrice;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colQty;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colTotal;

		   // ===== Summary panel =====
	private: System::Windows::Forms::Label^ lblSummaryTitle;
	private: System::Windows::Forms::Label^ lblSubtotalCap;
	private: System::Windows::Forms::Label^ lblSubtotal;
	private: System::Windows::Forms::Label^ lblDiscountCap;
	private: System::Windows::Forms::Label^ lblDiscount;
	private: System::Windows::Forms::Label^ lblTaxCap;
	private: System::Windows::Forms::Label^ lblTax;
	private: System::Windows::Forms::Label^ lblGrandTotalCap;
	private: System::Windows::Forms::Label^ lblGrandTotal;
	private: System::Windows::Forms::Button^ btnBilling;

	private: String^ currentRole;
	private: bool dragging;
	private: Point dragOffset;
	private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->pnlSidebar = gcnew Panel();
			   this->pnlContent = gcnew Panel();
			   this->pnlGridCard = gcnew Panel();
			   this->pnlSummary = gcnew Panel();
			   this->picLogo = gcnew PictureBox();
			   this->lblBrand = gcnew Label();
			   this->lblRole = gcnew Label();
			   this->lblPanelLabel = gcnew Label();
			   this->btnAddItem = gcnew Button();
			   this->btnRemoveItem = gcnew Button();
			   this->btnClearCart = gcnew Button();
			   this->btnSettings = gcnew Button();
			   this->btnExit = gcnew Button();
			   this->lblHead = gcnew Label();
			   this->lblSubtitle = gcnew Label();
			   this->btnMin = gcnew Label();
			   this->btnClose = gcnew Label();
			   this->cartGrid = gcnew DataGridView();
			   this->colID = gcnew DataGridViewTextBoxColumn();
			   this->colName = gcnew DataGridViewTextBoxColumn();
			   this->colPrice = gcnew DataGridViewTextBoxColumn();
			   this->colQty = gcnew DataGridViewTextBoxColumn();
			   this->colTotal = gcnew DataGridViewTextBoxColumn();
			   this->lblSummaryTitle = gcnew Label();
			   this->lblSubtotalCap = gcnew Label();
			   this->lblSubtotal = gcnew Label();
			   this->lblDiscountCap = gcnew Label();
			   this->lblDiscount = gcnew Label();
			   this->lblTaxCap = gcnew Label();
			   this->lblTax = gcnew Label();
			   this->lblGrandTotalCap = gcnew Label();
			   this->lblGrandTotal = gcnew Label();
			   this->btnBilling = gcnew Button();
			   (cli::safe_cast<ISupportInitialize^>(this->cartGrid))->BeginInit();
			   this->SuspendLayout();

			   // ============ SIDEBAR ============
			   this->pnlSidebar->Location = Point(0, 0);
			   this->pnlSidebar->Size = System::Drawing::Size(240, 720);
			   this->pnlSidebar->BackColor = NAVY;
			   this->pnlSidebar->Paint += gcnew PaintEventHandler(this, &CartForm::pnlSidebar_Paint);
			   this->pnlSidebar->MouseDown += gcnew MouseEventHandler(this, &CartForm::Form_MouseDown);
			   this->pnlSidebar->MouseMove += gcnew MouseEventHandler(this, &CartForm::Form_MouseMove);
			   this->pnlSidebar->MouseUp += gcnew MouseEventHandler(this, &CartForm::Form_MouseUp);

			   // logo
			   this->picLogo->Location = Point(20, 25);
			   this->picLogo->Size = System::Drawing::Size(60, 60);
			   this->picLogo->SizeMode = PictureBoxSizeMode::Zoom;
			   this->picLogo->BackColor = Color::Transparent;

			   // brand
			   this->lblBrand->AutoSize = true;
			   this->lblBrand->Font = gcnew System::Drawing::Font(L"Segoe UI", 16.0F, FontStyle::Bold);
			   this->lblBrand->ForeColor = Color::White;
			   this->lblBrand->BackColor = Color::Transparent;
			   this->lblBrand->Location = Point(90, 35);
			   this->lblBrand->Text = L"ValueMart";

			   // role / welcome
			   this->lblRole->AutoSize = true;
			   this->lblRole->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F);
			   this->lblRole->ForeColor = Color::FromArgb(180, 200, 230);
			   this->lblRole->BackColor = Color::Transparent;
			   this->lblRole->Location = Point(90, 62);
			   this->lblRole->Text = L"Logged in";

			   // panel label
			   this->lblPanelLabel->AutoSize = true;
			   this->lblPanelLabel->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.0F, FontStyle::Bold);
			   this->lblPanelLabel->ForeColor = Color::FromArgb(140, 160, 200);
			   this->lblPanelLabel->BackColor = Color::Transparent;
			   this->lblPanelLabel->Location = Point(28, 120);
			   this->lblPanelLabel->Text = L"CART ACTIONS";

			   // sidebar action buttons
			   ConfigureSidebarButton(btnAddItem, L"Add Item  (F1)", 150);
			   ConfigureSidebarButton(btnRemoveItem, L"Remove Item  (F2)", 198);
			   ConfigureSidebarButton(btnClearCart, L"Clear Cart  (F3)", 246);
			   ConfigureSidebarButton(btnSettings, L"Settings  (F5)", 294);

			   btnAddItem->Click += gcnew EventHandler(this, &CartForm::btnAddItem_Click);
			   btnRemoveItem->Click += gcnew EventHandler(this, &CartForm::btnRemoveItem_Click);
			   btnClearCart->Click += gcnew EventHandler(this, &CartForm::btnClearCart_Click);
			   btnSettings->Click += gcnew EventHandler(this, &CartForm::btnSettings_Click);

			   // exit (bottom of sidebar) — styled like Logout
			   this->btnExit->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
			   this->btnExit->BackColor = NAVY;
			   this->btnExit->ForeColor = Color::FromArgb(255, 180, 180);
			   this->btnExit->FlatStyle = FlatStyle::Flat;
			   this->btnExit->FlatAppearance->BorderSize = 0;
			   this->btnExit->Location = Point(0, 652);
			   this->btnExit->Size = System::Drawing::Size(240, 48);
			   this->btnExit->Text = L"Exit";
			   this->btnExit->TextAlign = ContentAlignment::MiddleLeft;
			   this->btnExit->Padding = System::Windows::Forms::Padding(28, 0, 0, 0);
			   this->btnExit->Cursor = Cursors::Hand;
			   this->btnExit->TabStop = false;
			   this->btnExit->Click += gcnew EventHandler(this, &CartForm::btnExit_Click);
			   this->btnExit->MouseEnter += gcnew EventHandler(this, &CartForm::btnExit_MouseEnter);
			   this->btnExit->MouseLeave += gcnew EventHandler(this, &CartForm::btnExit_MouseLeave);

			   this->pnlSidebar->Controls->Add(this->picLogo);
			   this->pnlSidebar->Controls->Add(this->lblBrand);
			   this->pnlSidebar->Controls->Add(this->lblRole);
			   this->pnlSidebar->Controls->Add(this->lblPanelLabel);
			   this->pnlSidebar->Controls->Add(this->btnAddItem);
			   this->pnlSidebar->Controls->Add(this->btnRemoveItem);
			   this->pnlSidebar->Controls->Add(this->btnClearCart);
			   this->pnlSidebar->Controls->Add(this->btnSettings);
			   this->pnlSidebar->Controls->Add(this->btnExit);

			   // ============ CONTENT AREA ============
			   this->pnlContent->Location = Point(240, 0);
			   this->pnlContent->Size = System::Drawing::Size(1040, 720);
			   this->pnlContent->BackColor = BG_LIGHT;
			   this->pnlContent->MouseDown += gcnew MouseEventHandler(this, &CartForm::Form_MouseDown);
			   this->pnlContent->MouseMove += gcnew MouseEventHandler(this, &CartForm::Form_MouseMove);
			   this->pnlContent->MouseUp += gcnew MouseEventHandler(this, &CartForm::Form_MouseUp);

			   // header
			   this->lblHead->AutoSize = true;
			   this->lblHead->Font = gcnew System::Drawing::Font(L"Segoe UI", 22.0F, FontStyle::Bold);
			   this->lblHead->ForeColor = TEXT_DARK;
			   this->lblHead->BackColor = Color::Transparent;
			   this->lblHead->Location = Point(40, 40);
			   this->lblHead->Text = L"Shopping Cart";

			   // subtitle
			   this->lblSubtitle->AutoSize = true;
			   this->lblSubtitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F);
			   this->lblSubtitle->ForeColor = TEXT_MUTED;
			   this->lblSubtitle->BackColor = Color::Transparent;
			   this->lblSubtitle->Location = Point(42, 80);
			   this->lblSubtitle->Text = L"Add items, review your order, and proceed to billing";

			   // window controls
			   this->btnMin->Text = L"\u2013";
			   this->btnMin->Font = gcnew System::Drawing::Font(L"Segoe UI", 12.0F, FontStyle::Bold);
			   this->btnMin->ForeColor = TEXT_MUTED;
			   this->btnMin->BackColor = Color::Transparent;
			   this->btnMin->Location = Point(960, 15);
			   this->btnMin->Size = System::Drawing::Size(35, 30);
			   this->btnMin->TextAlign = ContentAlignment::MiddleCenter;
			   this->btnMin->Cursor = Cursors::Hand;
			   this->btnMin->Click += gcnew EventHandler(this, &CartForm::btnMin_Click);
			   this->btnMin->MouseEnter += gcnew EventHandler(this, &CartForm::btnMin_MouseEnter);
			   this->btnMin->MouseLeave += gcnew EventHandler(this, &CartForm::btnMin_MouseLeave);

			   this->btnClose->Text = L"\u2715";
			   this->btnClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 12.0F, FontStyle::Bold);
			   this->btnClose->ForeColor = TEXT_MUTED;
			   this->btnClose->BackColor = Color::Transparent;
			   this->btnClose->Location = Point(1000, 15);
			   this->btnClose->Size = System::Drawing::Size(35, 30);
			   this->btnClose->TextAlign = ContentAlignment::MiddleCenter;
			   this->btnClose->Cursor = Cursors::Hand;
			   this->btnClose->Click += gcnew EventHandler(this, &CartForm::btnClose_Click);
			   this->btnClose->MouseEnter += gcnew EventHandler(this, &CartForm::btnClose_MouseEnter);
			   this->btnClose->MouseLeave += gcnew EventHandler(this, &CartForm::btnClose_MouseLeave);

			   // ============ GRID CARD (centre) ============
			   this->pnlGridCard->Location = Point(40, 140);
			   this->pnlGridCard->Size = System::Drawing::Size(640, 540);
			   this->pnlGridCard->BackColor = Color::White;
			   this->pnlGridCard->Paint += gcnew PaintEventHandler(this, &CartForm::pnlCard_Paint);

			   // cartGrid inside grid card
			   this->cartGrid->Location = Point(15, 15);
			   this->cartGrid->Size = System::Drawing::Size(610, 510);
			   this->cartGrid->Name = L"cartGrid";
			   this->cartGrid->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			   this->cartGrid->Columns->AddRange(gcnew cli::array<DataGridViewColumn^>(5) {
				   this->colID, this->colName, this->colPrice, this->colQty, this->colTotal
			   });
			   this->cartGrid->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
			   this->cartGrid->RowHeadersVisible = false;
			   this->cartGrid->RowTemplate->Height = 32;
			   this->cartGrid->BackgroundColor = Color::White;
			   this->cartGrid->BorderStyle = BorderStyle::None;
			   this->cartGrid->GridColor = BORDER_GREY;
			   this->cartGrid->AllowUserToAddRows = true;
			   this->cartGrid->AllowUserToResizeRows = false;
			   this->cartGrid->TabIndex = 0;

			   this->cartGrid->EnableHeadersVisualStyles = false;
			   this->cartGrid->ColumnHeadersDefaultCellStyle->BackColor = NAVY;
			   this->cartGrid->ColumnHeadersDefaultCellStyle->ForeColor = Color::White;
			   this->cartGrid->ColumnHeadersDefaultCellStyle->Font =
				   gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
			   this->cartGrid->ColumnHeadersDefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleLeft;
			   this->cartGrid->ColumnHeadersDefaultCellStyle->Padding = System::Windows::Forms::Padding(6, 0, 0, 0);
			   this->cartGrid->ColumnHeadersHeight = 38;

			   this->cartGrid->DefaultCellStyle->SelectionBackColor = NAVY_HOVER;
			   this->cartGrid->DefaultCellStyle->SelectionForeColor = Color::White;
			   this->cartGrid->DefaultCellStyle->ForeColor = TEXT_DARK;
			   this->cartGrid->DefaultCellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
			   this->cartGrid->DefaultCellStyle->Padding = System::Windows::Forms::Padding(4, 0, 0, 0);
			   this->cartGrid->AlternatingRowsDefaultCellStyle->BackColor = BG_LIGHT;

			   this->cartGrid->CellContentClick += gcnew DataGridViewCellEventHandler(this, &CartForm::dataGridView1_CellContentClick);
			   this->cartGrid->KeyDown += gcnew KeyEventHandler(this, &CartForm::cartGrid_KeyDown);

			   // Columns
			   this->colID->HeaderText = L"Product ID"; this->colID->Name = L"colID";       this->colID->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;
			   this->colName->HeaderText = L"Name";      this->colName->Name = L"colName";   this->colName->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;
			   this->colPrice->HeaderText = L"Price";    this->colPrice->Name = L"colPrice"; this->colPrice->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;
			   this->colQty->HeaderText = L"Qty";        this->colQty->Name = L"colQty";     this->colQty->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;
			   this->colTotal->HeaderText = L"Total";    this->colTotal->Name = L"colTotal"; this->colTotal->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;

			   this->pnlGridCard->Controls->Add(this->cartGrid);

			   // ============ SUMMARY CARD (right) ============
			   this->pnlSummary->Location = Point(700, 140);
			   this->pnlSummary->Size = System::Drawing::Size(300, 540);
			   this->pnlSummary->BackColor = Color::White;
			   this->pnlSummary->Paint += gcnew PaintEventHandler(this, &CartForm::pnlSummary_Paint);

			   // summary title
			   this->lblSummaryTitle->AutoSize = true;
			   this->lblSummaryTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 14.0F, FontStyle::Bold);
			   this->lblSummaryTitle->ForeColor = TEXT_DARK;
			   this->lblSummaryTitle->BackColor = Color::Transparent;
			   this->lblSummaryTitle->Location = Point(25, 25);
			   this->lblSummaryTitle->Text = L"Order Summary";

			   // Subtotal row
			   ConfigureSummaryRow(lblSubtotalCap, lblSubtotal, L"Subtotal", L"Rs 0.00", 90);
			   ConfigureSummaryRow(lblDiscountCap, lblDiscount, L"Discount", L"Rs 0.00", 125);
			   ConfigureSummaryRow(lblTaxCap, lblTax, L"Tax", L"Rs 0.00", 160);

			   // Grand total caption
			   this->lblGrandTotalCap->AutoSize = true;
			   this->lblGrandTotalCap->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5F, FontStyle::Bold);
			   this->lblGrandTotalCap->ForeColor = TEXT_MUTED;
			   this->lblGrandTotalCap->BackColor = Color::Transparent;
			   this->lblGrandTotalCap->Location = Point(25, 230);
			   this->lblGrandTotalCap->Text = L"GRAND TOTAL";

			   // Grand total value (large, navy)
			   this->lblGrandTotal->AutoSize = true;
			   this->lblGrandTotal->Font = gcnew System::Drawing::Font(L"Segoe UI", 22.0F, FontStyle::Bold);
			   this->lblGrandTotal->ForeColor = NAVY;
			   this->lblGrandTotal->BackColor = Color::Transparent;
			   this->lblGrandTotal->Location = Point(23, 255);
			   this->lblGrandTotal->Text = L"Rs 0.00";

			   // Proceed to Billing button
			   this->btnBilling->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0F, FontStyle::Bold);
			   this->btnBilling->BackColor = NAVY;
			   this->btnBilling->ForeColor = Color::White;
			   this->btnBilling->FlatStyle = FlatStyle::Flat;
			   this->btnBilling->FlatAppearance->BorderSize = 0;
			   this->btnBilling->Location = Point(25, 460);
			   this->btnBilling->Size = System::Drawing::Size(250, 55);
			   this->btnBilling->Text = L"Proceed to Billing  (F4)";
			   this->btnBilling->Cursor = Cursors::Hand;
			   this->btnBilling->Click += gcnew EventHandler(this, &CartForm::btnBilling_Click);
			   this->btnBilling->MouseEnter += gcnew EventHandler(this, &CartForm::btnBilling_MouseEnter);
			   this->btnBilling->MouseLeave += gcnew EventHandler(this, &CartForm::btnBilling_MouseLeave);

			   this->pnlSummary->Controls->Add(this->lblSummaryTitle);
			   this->pnlSummary->Controls->Add(this->lblSubtotalCap);
			   this->pnlSummary->Controls->Add(this->lblSubtotal);
			   this->pnlSummary->Controls->Add(this->lblDiscountCap);
			   this->pnlSummary->Controls->Add(this->lblDiscount);
			   this->pnlSummary->Controls->Add(this->lblTaxCap);
			   this->pnlSummary->Controls->Add(this->lblTax);
			   this->pnlSummary->Controls->Add(this->lblGrandTotalCap);
			   this->pnlSummary->Controls->Add(this->lblGrandTotal);
			   this->pnlSummary->Controls->Add(this->btnBilling);

			   // assemble content
			   this->pnlContent->Controls->Add(this->lblHead);
			   this->pnlContent->Controls->Add(this->lblSubtitle);
			   this->pnlContent->Controls->Add(this->btnMin);
			   this->pnlContent->Controls->Add(this->btnClose);
			   this->pnlContent->Controls->Add(this->pnlGridCard);
			   this->pnlContent->Controls->Add(this->pnlSummary);

			   // ============ FORM ============
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1280, 720);
			   this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			   this->StartPosition = FormStartPosition::CenterScreen;
			   this->BackColor = Color::White;
			   this->DoubleBuffered = true;
			   this->KeyPreview = true;
			   this->KeyDown += gcnew KeyEventHandler(this, &CartForm::CartForm_KeyDown);
			   this->Controls->Add(this->pnlSidebar);
			   this->Controls->Add(this->pnlContent);
			   this->Name = L"CartForm";
			   this->Text = L"ValueMart - Cart";
			   this->MouseDown += gcnew MouseEventHandler(this, &CartForm::Form_MouseDown);
			   this->MouseMove += gcnew MouseEventHandler(this, &CartForm::Form_MouseMove);
			   this->MouseUp += gcnew MouseEventHandler(this, &CartForm::Form_MouseUp);

			   (cli::safe_cast<ISupportInitialize^>(this->cartGrid))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();
		   }
#pragma endregion

		   // ============ STYLE HELPERS ============
	private: void ConfigureSidebarButton(Button^ btn, String^ text, int y) {
		btn->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F);
		btn->BackColor = NAVY;
		btn->ForeColor = Color::FromArgb(220, 230, 245);
		btn->FlatStyle = FlatStyle::Flat;
		btn->FlatAppearance->BorderSize = 0;
		btn->Location = Point(0, y);
		btn->Size = System::Drawing::Size(240, 46);
		btn->Text = text;
		btn->TextAlign = ContentAlignment::MiddleLeft;
		btn->Padding = System::Windows::Forms::Padding(28, 0, 0, 0);
		btn->Cursor = Cursors::Hand;
		btn->TabStop = false;
		btn->MouseEnter += gcnew EventHandler(this, &CartForm::SidebarBtn_MouseEnter);
		btn->MouseLeave += gcnew EventHandler(this, &CartForm::SidebarBtn_MouseLeave);
	}

	private: void ConfigureSummaryRow(Label^ cap, Label^ val, String^ capText, String^ valText, int y) {
		cap->AutoSize = true;
		cap->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F);
		cap->ForeColor = TEXT_MUTED;
		cap->BackColor = Color::Transparent;
		cap->Location = Point(25, y);
		cap->Text = capText;

		val->AutoSize = false;
		val->Size = System::Drawing::Size(140, 22);
		val->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
		val->ForeColor = TEXT_DARK;
		val->BackColor = Color::Transparent;
		val->Location = Point(135, y);
		val->TextAlign = ContentAlignment::MiddleRight;
		val->Text = valText;
	}

	private: void ApplyModernStyle() {
		RoundControl(pnlGridCard, 10);
		RoundControl(pnlSummary, 10);
		RoundControl(btnBilling, 8);

		try {
			String^ exeDir = System::IO::Path::GetDirectoryName(
				System::Reflection::Assembly::GetExecutingAssembly()->Location);
			array<String^>^ candidates = { L"logo.png", L"logo.jpg", L"logo.jpeg" };
			for each (String ^ name in candidates) {
				String^ p = System::IO::Path::Combine(exeDir, name);
				if (System::IO::File::Exists(p)) {
					this->picLogo->Image = Image::FromFile(p);
					break;
				}
			}
		}
		catch (...) {}
	}

	private: void RoundControl(Control^ ctrl, int radius) {
		GraphicsPath^ path = gcnew GraphicsPath();
		System::Drawing::Rectangle r = ctrl->ClientRectangle;
		path->AddArc(r.X, r.Y, radius, radius, 180, 90);
		path->AddArc(r.Right - radius, r.Y, radius, radius, 270, 90);
		path->AddArc(r.Right - radius, r.Bottom - radius, radius, radius, 0, 90);
		path->AddArc(r.X, r.Bottom - radius, radius, radius, 90, 90);
		path->CloseAllFigures();
		ctrl->Region = gcnew System::Drawing::Region(path);
	}

		   // ============ PAINT HANDLERS ============
	private: System::Void pnlSidebar_Paint(Object^ sender, PaintEventArgs^ e) {
		e->Graphics->SmoothingMode = SmoothingMode::AntiAlias;
		LinearGradientBrush^ brush = gcnew LinearGradientBrush(
			pnlSidebar->ClientRectangle, NAVY, NAVY_DARK, 90.0f);
		e->Graphics->FillRectangle(brush, pnlSidebar->ClientRectangle);
		Pen^ pen = gcnew Pen(Color::FromArgb(50, 255, 255, 255));
		e->Graphics->DrawLine(pen, 20, 645, 220, 645);
	}

	private: System::Void pnlCard_Paint(Object^ sender, PaintEventArgs^ e) {
		Panel^ card = (Panel^)sender;
		e->Graphics->SmoothingMode = SmoothingMode::AntiAlias;
		Pen^ borderPen = gcnew Pen(BORDER_GREY, 1);
		e->Graphics->DrawRectangle(borderPen, 0, 0, card->Width - 1, card->Height - 1);
	}

	private: System::Void pnlSummary_Paint(Object^ sender, PaintEventArgs^ e) {
		Panel^ card = pnlSummary;
		e->Graphics->SmoothingMode = SmoothingMode::AntiAlias;
		Pen^ borderPen = gcnew Pen(BORDER_GREY, 1);
		e->Graphics->DrawRectangle(borderPen, 0, 0, card->Width - 1, card->Height - 1);

		// navy accent strip on top
		SolidBrush^ accentBrush = gcnew SolidBrush(NAVY);
		e->Graphics->FillRectangle(accentBrush, 0, 0, card->Width, 4);

		// divider above grand total
		Pen^ dividerPen = gcnew Pen(BORDER_GREY, 1);
		e->Graphics->DrawLine(dividerPen, 25, 210, card->Width - 25, 210);

		// divider above proceed button
		e->Graphics->DrawLine(dividerPen, 25, 440, card->Width - 25, 440);
	}

		   // ============ DRAG ============
	private: System::Void Form_MouseDown(Object^ sender, MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			dragging = true;
			dragOffset = Point(
				System::Windows::Forms::Cursor::Position.X - this->Location.X,
				System::Windows::Forms::Cursor::Position.Y - this->Location.Y);
		}
	}
	private: System::Void Form_MouseMove(Object^ sender, MouseEventArgs^ e) {
		if (dragging) {
			this->Location = Point(
				System::Windows::Forms::Cursor::Position.X - dragOffset.X,
				System::Windows::Forms::Cursor::Position.Y - dragOffset.Y);
		}
	}
	private: System::Void Form_MouseUp(Object^ sender, MouseEventArgs^ e) {
		dragging = false;
	}

		   // ============ HOVER HANDLERS ============
	private: System::Void SidebarBtn_MouseEnter(Object^ sender, EventArgs^ e) {
		Button^ b = (Button^)sender;
		b->BackColor = NAVY_HOVER;
		b->ForeColor = Color::White;
	}
	private: System::Void SidebarBtn_MouseLeave(Object^ sender, EventArgs^ e) {
		Button^ b = (Button^)sender;
		b->BackColor = NAVY;
		b->ForeColor = Color::FromArgb(220, 230, 245);
	}

	private: System::Void btnExit_MouseEnter(Object^ sender, EventArgs^ e) {
		btnExit->BackColor = RED_ACCENT;
		btnExit->ForeColor = Color::White;
	}
	private: System::Void btnExit_MouseLeave(Object^ sender, EventArgs^ e) {
		btnExit->BackColor = NAVY;
		btnExit->ForeColor = Color::FromArgb(255, 180, 180);
	}

	private: System::Void btnBilling_MouseEnter(Object^ sender, EventArgs^ e) {
		btnBilling->BackColor = NAVY_HOVER;
	}
	private: System::Void btnBilling_MouseLeave(Object^ sender, EventArgs^ e) {
		btnBilling->BackColor = NAVY;
	}

	private: System::Void btnClose_Click(Object^ sender, EventArgs^ e) { this->Close(); }
	private: System::Void btnClose_MouseEnter(Object^ sender, EventArgs^ e) {
		btnClose->BackColor = Color::FromArgb(239, 68, 68);
		btnClose->ForeColor = Color::White;
	}
	private: System::Void btnClose_MouseLeave(Object^ sender, EventArgs^ e) {
		btnClose->BackColor = Color::Transparent;
		btnClose->ForeColor = TEXT_MUTED;
	}

	private: System::Void btnMin_Click(Object^ sender, EventArgs^ e) {
		this->WindowState = FormWindowState::Minimized;
	}
	private: System::Void btnMin_MouseEnter(Object^ sender, EventArgs^ e) {
		btnMin->BackColor = Color::FromArgb(230, 230, 230);
	}
	private: System::Void btnMin_MouseLeave(Object^ sender, EventArgs^ e) {
		btnMin->BackColor = Color::Transparent;
	}

	private: System::Void btnExit_Click(Object^ sender, EventArgs^ e) {
		this->Close();
	}

		   // ============ CART LOGIC (preserved) ============
	private: System::Void dataGridView1_CellContentClick(System::Object^ sender, DataGridViewCellEventArgs^ e) {}

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

		lblSubtotal->Text = "Rs " + subtotal.ToString("F2");
		lblDiscount->Text = "Rs " + discount.ToString("F2");
		lblTaxCap->Text = "Tax (" + (TAX_RATE * 100).ToString("F0") + "%)";
		lblTax->Text = "Rs " + tax.ToString("F2");
		lblGrandTotal->Text = "Rs " + grandTotal.ToString("F2");
	}

	private: System::Void btnAddItem_Click(System::Object^ sender, System::EventArgs^ e) {
		SearchForm^ search = gcnew SearchForm();
		if (search->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			int     id = search->SelectedProductID;
			String^ name = search->SelectedName;
			double  price = search->SelectedPrice;
			int qty = search->SelectedQty;
			if (id == -1 || qty <= 0) return;
			double  total = price * qty;
			cartGrid->Rows->Add(id, name, price, qty, total);
			UpdateTotals();
		}
	}

	private: System::Void btnRemoveItem_Click(System::Object^ sender, System::EventArgs^ e) {
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

	private: System::Void btnClearCart_Click(System::Object^ sender, System::EventArgs^ e) {
		cartGrid->Rows->Clear();
		UpdateTotals();
	}

	private: System::Void btnBilling_Click(System::Object^ sender, System::EventArgs^ e) {
		if (cartGrid->Rows->Count <= 1) {
			MessageBox::Show("Cart is empty! Please add items first.", "Warning"); return;
		}
		BillingForm^ billingForm = gcnew BillingForm(cartGrid);
		billingForm->ShowDialog();
		cartGrid->Rows->Clear();

		// reset totals to zero
		lblSubtotal->Text = "Rs 0.00";
		lblDiscount->Text = "Rs 0.00";
		lblTax->Text = "Rs 0.00";
		lblGrandTotal->Text = "Rs 0.00";
	}

	private: System::Void btnSettings_Click(System::Object^ sender, System::EventArgs^ e) {
		if (currentRole->ToLower() != "admin") {
			MessageBox::Show("Access Denied! Admin only.", "Security"); return;
		}
		SettingsForm^ settings = gcnew SettingsForm();
		settings->ShowDialog();
		UpdateTotals();
	}

	private: System::Void cartGrid_KeyDown(System::Object^ sender, KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Delete) {
			if (cartGrid->SelectedRows->Count > 0) {
				int index = cartGrid->SelectedRows[0]->Index;
				if (!cartGrid->Rows[index]->IsNewRow) {
					cartGrid->Rows->RemoveAt(index);
					UpdateTotals();
				}
			}
		}
	}

	private: System::Void CartForm_KeyDown(System::Object^ sender, KeyEventArgs^ e) {
		if (e->KeyCode == Keys::F1) btnAddItem->PerformClick();
		if (e->KeyCode == Keys::F2) btnRemoveItem->PerformClick();
		if (e->KeyCode == Keys::F3) btnClearCart->PerformClick();
		if (e->KeyCode == Keys::F4) btnBilling->PerformClick();
		if (e->KeyCode == Keys::F5) btnSettings->PerformClick();
	}
	};
}