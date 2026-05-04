#pragma once
#include "constants.h"
#include "BillingForm.h"
#include "SettingsForm.h"
#include "database.h"
#include "SearchForm.h"
#include "session.h"

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
            this->Activated += gcnew EventHandler(this, &CartForm::CartForm_Activated);
        }

    protected:
        ~CartForm()
        {
            if (components) delete components;
        }

        // ===== Brand palette =====
    private:
        static Color NAVY;
        static Color NAVY_DARK;
        static Color NAVY_HOVER;
        static Color GREEN_PRIMARY;
        static Color GREEN_HOVER;
        static Color RED_DANGER;
        static Color RED_HOVER;
        static Color ORANGE;
        static Color ORANGE_HOVER;
        static Color BG_LIGHT;
        static Color BORDER_GREY;
        static Color TEXT_DARK;
        static Color TEXT_MUTED;

        static CartForm()
        {
            NAVY = Color::FromArgb(30, 58, 138);
            NAVY_DARK = Color::FromArgb(15, 30, 90);
            NAVY_HOVER = Color::FromArgb(45, 75, 165);
            GREEN_PRIMARY = Color::FromArgb(34, 197, 94);
            GREEN_HOVER = Color::FromArgb(22, 163, 74);
            RED_DANGER = Color::FromArgb(220, 38, 38);
            RED_HOVER = Color::FromArgb(185, 28, 28);
            ORANGE = Color::FromArgb(249, 115, 22);
            ORANGE_HOVER = Color::FromArgb(217, 95, 12);
            BG_LIGHT = Color::FromArgb(248, 250, 252);
            BORDER_GREY = Color::FromArgb(229, 231, 235);
            TEXT_DARK = Color::FromArgb(30, 41, 59);
            TEXT_MUTED = Color::FromArgb(100, 116, 139);
        }

        // ===== ORIGINAL CONTROL NAMES PRESERVED =====
    private: System::Windows::Forms::Panel^ headerPanel;
    private: System::Windows::Forms::Label^ lblHeader;
    private: System::Windows::Forms::DataGridView^ cartGrid;
    private: String^ currentRole;
    private: System::Windows::Forms::Button^ button1;     // Add Item
    private: System::Windows::Forms::Button^ button2;     // Remove Item
    private: System::Windows::Forms::Button^ button3;     // Clear Cart
    private: System::Windows::Forms::Button^ btnBilling;  // Proceed to Billing
    private: System::Windows::Forms::Button^ btnSettings;
    private: System::Windows::Forms::Button^ btnLogout;
    private: System::Windows::Forms::Label^ lblSubtotal;
    private: System::Windows::Forms::Label^ lblDiscount;
    private: System::Windows::Forms::Label^ lblTax;
    private: System::Windows::Forms::Label^ lblGrandTotal;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ colID;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ colName;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ colPrice;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ colQty;
    private: System::Windows::Forms::DataGridViewTextBoxColumn^ colTotal;

           // ===== NEW LAYOUT CONTROLS =====
    private: System::Windows::Forms::Panel^ pnlSidebar;
    private: System::Windows::Forms::Panel^ pnlMain;
    private: System::Windows::Forms::Panel^ pnlGridCard;
    private: System::Windows::Forms::Panel^ pnlTotalsCard;
    private: System::Windows::Forms::PictureBox^ picLogo;
    private: System::Windows::Forms::Label^ lblBrand;
    private: System::Windows::Forms::Label^ lblRoleInfo;
    private: System::Windows::Forms::Label^ lblCartTitle;
    private: System::Windows::Forms::Label^ lblCartSubtitle;
    private: System::Windows::Forms::Label^ lblTotalsTitle;
    private: System::Windows::Forms::Label^ lblSubCaption;
    private: System::Windows::Forms::Label^ lblDiscCaption;
    private: System::Windows::Forms::Label^ lblTaxCaption;
    private: System::Windows::Forms::Label^ lblGrandCaption;
    private: System::Windows::Forms::Panel^ pnlDivider;
    private: System::Windows::Forms::Label^ btnMin;
    private: System::Windows::Forms::Label^ btnMax;
    private: System::Windows::Forms::Label^ btnClose;

    private: System::ComponentModel::Container^ components;

    private:
        bool dragging;
        Point dragOffset;
        bool isMaximized;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->headerPanel = gcnew Panel();
            this->lblHeader = gcnew Label();
            this->cartGrid = gcnew DataGridView();
            this->colID = gcnew DataGridViewTextBoxColumn();
            this->colName = gcnew DataGridViewTextBoxColumn();
            this->colPrice = gcnew DataGridViewTextBoxColumn();
            this->colQty = gcnew DataGridViewTextBoxColumn();
            this->colTotal = gcnew DataGridViewTextBoxColumn();
            this->button1 = gcnew Button();
            this->button2 = gcnew Button();
            this->button3 = gcnew Button();
            this->btnLogout = gcnew Button();
            this->btnBilling = gcnew Button();
            this->btnSettings = gcnew Button();
            this->lblSubtotal = gcnew Label();
            this->lblDiscount = gcnew Label();
            this->lblTax = gcnew Label();
            this->lblGrandTotal = gcnew Label();
            this->pnlSidebar = gcnew Panel();
            this->pnlMain = gcnew Panel();
            this->pnlGridCard = gcnew Panel();
            this->pnlTotalsCard = gcnew Panel();
            this->picLogo = gcnew PictureBox();
            this->lblBrand = gcnew Label();
            this->lblRoleInfo = gcnew Label();
            this->lblCartTitle = gcnew Label();
            this->lblCartSubtitle = gcnew Label();
            this->lblTotalsTitle = gcnew Label();
            this->lblSubCaption = gcnew Label();
            this->lblDiscCaption = gcnew Label();
            this->lblTaxCaption = gcnew Label();
            this->lblGrandCaption = gcnew Label();
            this->pnlDivider = gcnew Panel();
            this->btnMin = gcnew Label();
            this->btnMax = gcnew Label();
            this->btnClose = gcnew Label();
            (cli::safe_cast<ISupportInitialize^>(this->cartGrid))->BeginInit();
            this->SuspendLayout();

            // ===== HEADER PANEL (kept for compat, drag handle) =====
            this->headerPanel->Location = Point(0, 0);
            this->headerPanel->Size = System::Drawing::Size(1760, 60);
            this->headerPanel->BackColor = NAVY;
            this->headerPanel->Anchor = static_cast<AnchorStyles>(
                AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
            this->headerPanel->Paint += gcnew PaintEventHandler(this, &CartForm::headerPanel_Paint);
            this->headerPanel->MouseDown += gcnew MouseEventHandler(this, &CartForm::Form_MouseDown);
            this->headerPanel->MouseMove += gcnew MouseEventHandler(this, &CartForm::Form_MouseMove);
            this->headerPanel->MouseUp += gcnew MouseEventHandler(this, &CartForm::Form_MouseUp);

            this->lblHeader->Text = L"ValueMart - Billing System";
            this->lblHeader->Font = gcnew System::Drawing::Font(L"Segoe UI", 13, FontStyle::Bold);
            this->lblHeader->ForeColor = Color::White;
            this->lblHeader->BackColor = Color::Transparent;
            this->lblHeader->Location = Point(280, 18);
            this->lblHeader->AutoSize = true;

            // Window controls (top right)
            this->btnMin->Text = L"\u2013";
            this->btnMin->Font = gcnew System::Drawing::Font(L"Segoe UI", 12, FontStyle::Bold);
            this->btnMin->ForeColor = Color::FromArgb(180, 200, 230);
            this->btnMin->BackColor = Color::Transparent;
            this->btnMin->Location = Point(1660, 12);
            this->btnMin->Size = System::Drawing::Size(35, 35);
            this->btnMin->TextAlign = ContentAlignment::MiddleCenter;
            this->btnMin->Cursor = Cursors::Hand;
            this->btnMin->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);
            this->btnMin->Click += gcnew EventHandler(this, &CartForm::btnMin_Click);
            this->btnMin->MouseEnter += gcnew EventHandler(this, &CartForm::btnMin_MouseEnter);
            this->btnMin->MouseLeave += gcnew EventHandler(this, &CartForm::btnMin_MouseLeave);

            this->btnMax->Text = L"\u25A1";
            this->btnMax->Font = gcnew System::Drawing::Font(L"Segoe UI", 11);
            this->btnMax->ForeColor = Color::FromArgb(180, 200, 230);
            this->btnMax->BackColor = Color::Transparent;
            this->btnMax->Location = Point(1697, 12);
            this->btnMax->Size = System::Drawing::Size(35, 35);
            this->btnMax->TextAlign = ContentAlignment::MiddleCenter;
            this->btnMax->Cursor = Cursors::Hand;
            this->btnMax->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);
            this->btnMax->Click += gcnew EventHandler(this, &CartForm::btnMax_Click);
            this->btnMax->MouseEnter += gcnew EventHandler(this, &CartForm::btnMax_MouseEnter);
            this->btnMax->MouseLeave += gcnew EventHandler(this, &CartForm::btnMax_MouseLeave);

            this->btnClose->Text = L"\u2715";
            this->btnClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 12, FontStyle::Bold);
            this->btnClose->ForeColor = Color::FromArgb(180, 200, 230);
            this->btnClose->BackColor = Color::Transparent;
            this->btnClose->Location = Point(1722, 12);
            this->btnClose->Size = System::Drawing::Size(35, 35);
            this->btnClose->TextAlign = ContentAlignment::MiddleCenter;
            this->btnClose->Cursor = Cursors::Hand;
            this->btnClose->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);
            this->btnClose->Click += gcnew EventHandler(this, &CartForm::btnTopClose_Click);
            this->btnClose->MouseEnter += gcnew EventHandler(this, &CartForm::btnClose_MouseEnter);
            this->btnClose->MouseLeave += gcnew EventHandler(this, &CartForm::btnClose_MouseLeave);

            this->headerPanel->Controls->Add(this->lblHeader);
            this->headerPanel->Controls->Add(this->btnMin);
            this->headerPanel->Controls->Add(this->btnMax);
            this->headerPanel->Controls->Add(this->btnClose);

            // ===== SIDEBAR (LEFT) =====
            this->pnlSidebar->Location = Point(0, 60);
            this->pnlSidebar->Size = System::Drawing::Size(260, 770);
            this->pnlSidebar->BackColor = NAVY;
            this->pnlSidebar->Anchor = static_cast<AnchorStyles>(
                AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Bottom);
            this->pnlSidebar->Paint += gcnew PaintEventHandler(this, &CartForm::pnlSidebar_Paint);

            this->picLogo->Location = Point(20, 25);
            this->picLogo->Size = System::Drawing::Size(60, 60);
            this->picLogo->SizeMode = PictureBoxSizeMode::Zoom;
            this->picLogo->BackColor = Color::Transparent;

            this->lblBrand->Text = L"ValueMart";
            this->lblBrand->Font = gcnew System::Drawing::Font(L"Segoe UI", 16, FontStyle::Bold);
            this->lblBrand->ForeColor = Color::White;
            this->lblBrand->BackColor = Color::Transparent;
            this->lblBrand->Location = Point(90, 35);
            this->lblBrand->AutoSize = true;

            this->lblRoleInfo->Text = L"Cashier Terminal";
            this->lblRoleInfo->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);
            this->lblRoleInfo->ForeColor = Color::FromArgb(180, 200, 230);
            this->lblRoleInfo->BackColor = Color::Transparent;
            this->lblRoleInfo->Location = Point(90, 62);
            this->lblRoleInfo->AutoSize = true;

            // Section heading
            Label^ lblActionsHeader = gcnew Label();
            lblActionsHeader->Text = L"CART ACTIONS";
            lblActionsHeader->Font = gcnew System::Drawing::Font(L"Segoe UI", 8, FontStyle::Bold);
            lblActionsHeader->ForeColor = Color::FromArgb(140, 160, 200);
            lblActionsHeader->BackColor = Color::Transparent;
            lblActionsHeader->Location = Point(28, 130);
            lblActionsHeader->AutoSize = true;

            // button1 - Add Item
            ConfigureSidebarBtn(button1, L"+   Add Item   (F1)", 160, GREEN_PRIMARY);
            button1->Click += gcnew EventHandler(this, &CartForm::button1_Click);

            // button2 - Remove Item
            ConfigureSidebarBtn(button2, L"\u2212   Remove Item   (F2)", 215, NAVY);
            button2->Click += gcnew EventHandler(this, &CartForm::button2_Click);

            // button3 - Clear Cart
            ConfigureSidebarBtn(button3, L"Clear Cart   (F3)", 270, ORANGE);
            button3->Click += gcnew EventHandler(this, &CartForm::button3_Click);

            // Section heading
            Label^ lblAdminHeader = gcnew Label();
            lblAdminHeader->Text = L"ADMIN";
            lblAdminHeader->Font = gcnew System::Drawing::Font(L"Segoe UI", 8, FontStyle::Bold);
            lblAdminHeader->ForeColor = Color::FromArgb(140, 160, 200);
            lblAdminHeader->BackColor = Color::Transparent;
            lblAdminHeader->Location = Point(28, 350);
            lblAdminHeader->AutoSize = true;

            // btnSettings
            ConfigureSidebarBtn(btnSettings, L"\u2699   Settings   (F5)", 380, NAVY);
            btnSettings->Click += gcnew EventHandler(this, &CartForm::btnSettings_Click);

            // btnLogout — pinned to bottom of sidebar
            btnLogout->Text = L"\u23FB   Log Out";
            btnLogout->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
            btnLogout->BackColor = NAVY;
            btnLogout->ForeColor = Color::FromArgb(255, 180, 180);
            btnLogout->FlatStyle = FlatStyle::Flat;
            btnLogout->FlatAppearance->BorderSize = 0;
            btnLogout->Location = Point(0, 700);
            btnLogout->Size = System::Drawing::Size(260, 50);
            btnLogout->TextAlign = ContentAlignment::MiddleLeft;
            btnLogout->Padding = System::Windows::Forms::Padding(35, 0, 0, 0);
            btnLogout->Cursor = Cursors::Hand;
            btnLogout->TabStop = false;
            btnLogout->Anchor = static_cast<AnchorStyles>(
                AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
            btnLogout->Click += gcnew EventHandler(this, &CartForm::btnLogout_Click);
            btnLogout->MouseEnter += gcnew EventHandler(this, &CartForm::btnLogout_MouseEnter);
            btnLogout->MouseLeave += gcnew EventHandler(this, &CartForm::btnLogout_MouseLeave);

            this->pnlSidebar->Controls->Add(this->picLogo);
            this->pnlSidebar->Controls->Add(this->lblBrand);
            this->pnlSidebar->Controls->Add(this->lblRoleInfo);
            this->pnlSidebar->Controls->Add(lblActionsHeader);
            this->pnlSidebar->Controls->Add(this->button1);
            this->pnlSidebar->Controls->Add(this->button2);
            this->pnlSidebar->Controls->Add(this->button3);
            this->pnlSidebar->Controls->Add(lblAdminHeader);
            this->pnlSidebar->Controls->Add(this->btnSettings);
            this->pnlSidebar->Controls->Add(this->btnLogout);

            // ===== MAIN AREA =====
            this->pnlMain->Location = Point(260, 60);
            this->pnlMain->Size = System::Drawing::Size(1500, 770);
            this->pnlMain->BackColor = BG_LIGHT;
            this->pnlMain->Anchor = static_cast<AnchorStyles>(
                AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right | AnchorStyles::Bottom);

            this->lblCartTitle->Text = L"Current Cart";
            this->lblCartTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 18, FontStyle::Bold);
            this->lblCartTitle->ForeColor = TEXT_DARK;
            this->lblCartTitle->BackColor = Color::Transparent;
            this->lblCartTitle->Location = Point(30, 25);
            this->lblCartTitle->AutoSize = true;

            this->lblCartSubtitle->Text = L"Scan or search for products to add them to the cart";
            this->lblCartSubtitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F);
            this->lblCartSubtitle->ForeColor = TEXT_MUTED;
            this->lblCartSubtitle->BackColor = Color::Transparent;
            this->lblCartSubtitle->Location = Point(32, 60);
            this->lblCartSubtitle->AutoSize = true;

            // ===== GRID CARD =====
            this->pnlGridCard->Location = Point(30, 100);
            this->pnlGridCard->Size = System::Drawing::Size(720, 640);
            this->pnlGridCard->BackColor = Color::White;
            this->pnlGridCard->Padding = System::Windows::Forms::Padding(1);
            this->pnlGridCard->Anchor = static_cast<AnchorStyles>(
                AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Bottom);
            this->pnlGridCard->Paint += gcnew PaintEventHandler(this, &CartForm::pnlCard_Paint);

            // Cart Grid
            this->cartGrid->Columns->AddRange(gcnew cli::array<DataGridViewColumn^>(5) {
                this->colID, this->colName, this->colPrice, this->colQty, this->colTotal
            });
            this->cartGrid->Dock = DockStyle::Fill;
            this->cartGrid->Name = L"cartGrid";
            this->cartGrid->BackgroundColor = Color::White;
            this->cartGrid->BorderStyle = BorderStyle::None;
            this->cartGrid->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
            this->cartGrid->GridColor = BORDER_GREY;
            this->cartGrid->RowHeadersVisible = false;
            this->cartGrid->EnableHeadersVisualStyles = false;
            this->cartGrid->ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle::None;
            this->cartGrid->ColumnHeadersHeight = 50;
            this->cartGrid->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
            this->cartGrid->RowTemplate->Height = 44;
            this->cartGrid->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            this->cartGrid->MultiSelect = false;
            this->cartGrid->AllowUserToAddRows = false;
            this->cartGrid->AllowUserToResizeRows = false;
            this->cartGrid->TabIndex = 0;
            this->cartGrid->CellContentClick +=
                gcnew DataGridViewCellEventHandler(this, &CartForm::dataGridView1_CellContentClick);
            this->cartGrid->KeyDown +=
                gcnew KeyEventHandler(this, &CartForm::cartGrid_KeyDown);

            DataGridViewCellStyle^ hs = gcnew DataGridViewCellStyle();
            hs->BackColor = NAVY;
            hs->ForeColor = Color::White;
            hs->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
            hs->Alignment = DataGridViewContentAlignment::MiddleLeft;
            hs->Padding = System::Windows::Forms::Padding(15, 0, 15, 0);
            hs->SelectionBackColor = NAVY;
            hs->SelectionForeColor = Color::White;
            this->cartGrid->ColumnHeadersDefaultCellStyle = hs;

            DataGridViewCellStyle^ cs = gcnew DataGridViewCellStyle();
            cs->BackColor = Color::White;
            cs->ForeColor = TEXT_DARK;
            cs->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
            cs->Alignment = DataGridViewContentAlignment::MiddleLeft;
            cs->Padding = System::Windows::Forms::Padding(15, 0, 15, 0);
            cs->SelectionBackColor = Color::FromArgb(219, 234, 254);
            cs->SelectionForeColor = TEXT_DARK;
            this->cartGrid->DefaultCellStyle = cs;

            DataGridViewCellStyle^ as_ = gcnew DataGridViewCellStyle();
            as_->BackColor = BG_LIGHT;
            as_->ForeColor = TEXT_DARK;
            as_->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
            as_->Padding = System::Windows::Forms::Padding(15, 0, 15, 0);
            as_->SelectionBackColor = Color::FromArgb(219, 234, 254);
            as_->SelectionForeColor = TEXT_DARK;
            this->cartGrid->AlternatingRowsDefaultCellStyle = as_;

            // Columns
            this->colID->HeaderText = L"Product ID";
            this->colID->Name = L"colID";
            this->colID->FillWeight = 70;
            this->colID->DefaultCellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
            this->colID->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;

            this->colName->HeaderText = L"Product Name";
            this->colName->Name = L"colName";
            this->colName->FillWeight = 180;
            this->colName->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;

            this->colPrice->HeaderText = L"Price";
            this->colPrice->Name = L"colPrice";
            this->colPrice->FillWeight = 80;
            this->colPrice->DefaultCellStyle->Format = L"N2";
            this->colPrice->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleRight;
            this->colPrice->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;

            this->colQty->HeaderText = L"Quantity";
            this->colQty->Name = L"colQty";
            this->colQty->FillWeight = 70;
            this->colQty->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;
            this->colQty->DefaultCellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
            this->colQty->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;

            this->colTotal->HeaderText = L"Total";
            this->colTotal->Name = L"colTotal";
            this->colTotal->FillWeight = 100;
            this->colTotal->DefaultCellStyle->Format = L"N2";
            this->colTotal->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleRight;
            this->colTotal->DefaultCellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
            this->colTotal->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;

            this->pnlGridCard->Controls->Add(this->cartGrid);

            // ===== TOTALS CARD (RIGHT) =====
            this->pnlTotalsCard->Location = Point(760, 100);
            this->pnlTotalsCard->Size = System::Drawing::Size(320, 640);
            this->pnlTotalsCard->BackColor = Color::White;
            this->pnlTotalsCard->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Bottom);
            this->pnlTotalsCard->Paint += gcnew PaintEventHandler(this, &CartForm::pnlCard_Paint);

            this->lblTotalsTitle->Text = L"Order Summary";
            this->lblTotalsTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 13, FontStyle::Bold);
            this->lblTotalsTitle->ForeColor = TEXT_DARK;
            this->lblTotalsTitle->BackColor = Color::Transparent;
            this->lblTotalsTitle->Location = Point(25, 25);
            this->lblTotalsTitle->AutoSize = true;

            // Subtotal row
            this->lblSubCaption->Text = L"Subtotal";
            this->lblSubCaption->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
            this->lblSubCaption->ForeColor = TEXT_MUTED;
            this->lblSubCaption->BackColor = Color::Transparent;
            this->lblSubCaption->Location = Point(25, 80);
            this->lblSubCaption->AutoSize = true;

            this->lblSubtotal->Text = L"Rs 0.00";
            this->lblSubtotal->Font = gcnew System::Drawing::Font(L"Segoe UI", 11, FontStyle::Bold);
            this->lblSubtotal->ForeColor = TEXT_DARK;
            this->lblSubtotal->BackColor = Color::Transparent;
            this->lblSubtotal->Location = Point(180, 80);
            this->lblSubtotal->Size = System::Drawing::Size(135, 22);
            this->lblSubtotal->TextAlign = ContentAlignment::MiddleRight;

            // Discount row
            this->lblDiscCaption->Text = L"Discount";
            this->lblDiscCaption->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
            this->lblDiscCaption->ForeColor = TEXT_MUTED;
            this->lblDiscCaption->BackColor = Color::Transparent;
            this->lblDiscCaption->Location = Point(25, 120);
            this->lblDiscCaption->AutoSize = true;

            this->lblDiscount->Text = L"- Rs 0.00";
            this->lblDiscount->Font = gcnew System::Drawing::Font(L"Segoe UI", 11, FontStyle::Bold);
            this->lblDiscount->ForeColor = GREEN_HOVER;
            this->lblDiscount->BackColor = Color::Transparent;
            this->lblDiscount->Location = Point(180, 120);
            this->lblDiscount->Size = System::Drawing::Size(135, 22);
            this->lblDiscount->TextAlign = ContentAlignment::MiddleRight;

            // Tax row
            this->lblTaxCaption->Text = L"Tax";
            this->lblTaxCaption->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
            this->lblTaxCaption->ForeColor = TEXT_MUTED;
            this->lblTaxCaption->BackColor = Color::Transparent;
            this->lblTaxCaption->Location = Point(25, 160);
            this->lblTaxCaption->AutoSize = true;

            this->lblTax->Text = L"Rs 0.00";
            this->lblTax->Font = gcnew System::Drawing::Font(L"Segoe UI", 11, FontStyle::Bold);
            this->lblTax->ForeColor = TEXT_DARK;
            this->lblTax->BackColor = Color::Transparent;
            this->lblTax->Location = Point(180, 160);
            this->lblTax->Size = System::Drawing::Size(135, 22);
            this->lblTax->TextAlign = ContentAlignment::MiddleRight;

            // Divider
            this->pnlDivider->Location = Point(25, 210);
            this->pnlDivider->Size = System::Drawing::Size(290, 1);
            this->pnlDivider->BackColor = BORDER_GREY;

            // Grand Total
            this->lblGrandCaption->Text = L"GRAND TOTAL";
            this->lblGrandCaption->Font = gcnew System::Drawing::Font(L"Segoe UI", 9, FontStyle::Bold);
            this->lblGrandCaption->ForeColor = TEXT_MUTED;
            this->lblGrandCaption->BackColor = Color::Transparent;
            this->lblGrandCaption->Location = Point(25, 235);
            this->lblGrandCaption->AutoSize = true;

            this->lblGrandTotal->Text = L"Rs 0.00";
            this->lblGrandTotal->Font = gcnew System::Drawing::Font(L"Segoe UI", 22, FontStyle::Bold);
            this->lblGrandTotal->ForeColor = NAVY;
            this->lblGrandTotal->BackColor = Color::Transparent;
            this->lblGrandTotal->Location = Point(25, 260);
            this->lblGrandTotal->Size = System::Drawing::Size(290, 50);
            this->lblGrandTotal->TextAlign = ContentAlignment::MiddleLeft;

            // Big Proceed to Billing button
            this->btnBilling->Text = L"Proceed to Billing  (F4)";
            this->btnBilling->Font = gcnew System::Drawing::Font(L"Segoe UI", 12, FontStyle::Bold);
            this->btnBilling->BackColor = GREEN_PRIMARY;
            this->btnBilling->ForeColor = Color::White;
            this->btnBilling->FlatStyle = FlatStyle::Flat;
            this->btnBilling->FlatAppearance->BorderSize = 0;
            this->btnBilling->Location = Point(25, 555);
            this->btnBilling->Size = System::Drawing::Size(290, 60);
            this->btnBilling->Cursor = Cursors::Hand;
            this->btnBilling->Anchor = static_cast<AnchorStyles>(
                AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
            this->btnBilling->Click += gcnew EventHandler(this, &CartForm::btnBilling_Click);
            this->btnBilling->MouseEnter += gcnew EventHandler(this, &CartForm::btnBilling_MouseEnter);
            this->btnBilling->MouseLeave += gcnew EventHandler(this, &CartForm::btnBilling_MouseLeave);

            this->pnlTotalsCard->Controls->Add(this->lblTotalsTitle);
            this->pnlTotalsCard->Controls->Add(this->lblSubCaption);
            this->pnlTotalsCard->Controls->Add(this->lblSubtotal);
            this->pnlTotalsCard->Controls->Add(this->lblDiscCaption);
            this->pnlTotalsCard->Controls->Add(this->lblDiscount);
            this->pnlTotalsCard->Controls->Add(this->lblTaxCaption);
            this->pnlTotalsCard->Controls->Add(this->lblTax);
            this->pnlTotalsCard->Controls->Add(this->pnlDivider);
            this->pnlTotalsCard->Controls->Add(this->lblGrandCaption);
            this->pnlTotalsCard->Controls->Add(this->lblGrandTotal);
            this->pnlTotalsCard->Controls->Add(this->btnBilling);

            this->pnlMain->Controls->Add(this->lblCartTitle);
            this->pnlMain->Controls->Add(this->lblCartSubtitle);
            this->pnlMain->Controls->Add(this->pnlGridCard);
            this->pnlMain->Controls->Add(this->pnlTotalsCard);

            // ===== FORM =====
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1760, 830);
            this->WindowState = FormWindowState::Maximized;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->BackColor = BG_LIGHT;
            this->KeyPreview = true;
            this->KeyDown += gcnew KeyEventHandler(this, &CartForm::CartForm_KeyDown);
            this->Name = L"CartForm";
            this->Text = L"ValueMart - Billing System";
            this->DoubleBuffered = true;

            this->Controls->Add(this->headerPanel);
            this->Controls->Add(this->pnlSidebar);
            this->Controls->Add(this->pnlMain);

            (cli::safe_cast<ISupportInitialize^>(this->cartGrid))->EndInit();
            this->ResumeLayout(false);
        }
#pragma endregion

        // ===== STYLE HELPERS =====
    private: void ConfigureSidebarBtn(Button^ btn, String^ text, int y, Color bg) {
        btn->Text = text;
        btn->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
        btn->BackColor = bg;
        btn->ForeColor = Color::White;
        btn->FlatStyle = FlatStyle::Flat;
        btn->FlatAppearance->BorderSize = 0;
        btn->Location = Point(20, y);
        btn->Size = System::Drawing::Size(220, 44);
        btn->TextAlign = ContentAlignment::MiddleLeft;
        btn->Padding = System::Windows::Forms::Padding(15, 0, 0, 0);
        btn->Cursor = Cursors::Hand;
        btn->Tag = bg;
        btn->MouseEnter += gcnew EventHandler(this, &CartForm::SidebarBtn_MouseEnter);
        btn->MouseLeave += gcnew EventHandler(this, &CartForm::SidebarBtn_MouseLeave);
    }

    private: void ApplyModernStyle() {
        RoundControl(button1, 6);
        RoundControl(button2, 6);
        RoundControl(button3, 6);
        RoundControl(btnSettings, 6);
        RoundControl(btnBilling, 8);
        RoundControl(pnlGridCard, 8);
        RoundControl(pnlTotalsCard, 8);

        // Logo
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

           // ===== PAINT =====
    private: System::Void headerPanel_Paint(Object^ sender, PaintEventArgs^ e) {
        e->Graphics->SmoothingMode = SmoothingMode::AntiAlias;
        LinearGradientBrush^ brush = gcnew LinearGradientBrush(
            headerPanel->ClientRectangle, NAVY, NAVY_DARK, 0.0f);
        e->Graphics->FillRectangle(brush, headerPanel->ClientRectangle);
    }
    private: System::Void pnlSidebar_Paint(Object^ sender, PaintEventArgs^ e) {
        e->Graphics->SmoothingMode = SmoothingMode::AntiAlias;
        LinearGradientBrush^ brush = gcnew LinearGradientBrush(
            pnlSidebar->ClientRectangle, NAVY, NAVY_DARK, 90.0f);
        e->Graphics->FillRectangle(brush, pnlSidebar->ClientRectangle);
    }
    private: System::Void pnlCard_Paint(Object^ sender, PaintEventArgs^ e) {
        Panel^ p = (Panel^)sender;
        Pen^ pen = gcnew Pen(BORDER_GREY, 1);
        e->Graphics->DrawRectangle(pen, 0, 0, p->Width - 1, p->Height - 1);
    }

           // ===== DRAG =====
    private: System::Void Form_MouseDown(Object^ s, MouseEventArgs^ e) {
        if (e->Button == System::Windows::Forms::MouseButtons::Left
            && this->WindowState == FormWindowState::Normal) {
            dragging = true;
            dragOffset = Point(
                System::Windows::Forms::Cursor::Position.X - this->Location.X,
                System::Windows::Forms::Cursor::Position.Y - this->Location.Y);
        }
    }
    private: System::Void Form_MouseMove(Object^ s, MouseEventArgs^ e) {
        if (dragging) {
            this->Location = Point(
                System::Windows::Forms::Cursor::Position.X - dragOffset.X,
                System::Windows::Forms::Cursor::Position.Y - dragOffset.Y);
        }
    }
    private: System::Void Form_MouseUp(Object^ s, MouseEventArgs^ e) { dragging = false; }

           // ===== HOVER HANDLERS =====
    private: System::Void SidebarBtn_MouseEnter(Object^ s, EventArgs^ e) {
        Button^ b = (Button^)s;
        Color base_ = (Color)b->Tag;
        b->BackColor = Color::FromArgb(
            Math::Min(255, base_.R + 25),
            Math::Min(255, base_.G + 25),
            Math::Min(255, base_.B + 25));
    }
    private: System::Void SidebarBtn_MouseLeave(Object^ s, EventArgs^ e) {
        Button^ b = (Button^)s;
        b->BackColor = (Color)b->Tag;
    }

    private: System::Void btnBilling_MouseEnter(Object^ s, EventArgs^ e) { btnBilling->BackColor = GREEN_HOVER; }
    private: System::Void btnBilling_MouseLeave(Object^ s, EventArgs^ e) { btnBilling->BackColor = GREEN_PRIMARY; }

    private: System::Void btnTopClose_Click(Object^ s, EventArgs^ e) { this->Close(); }
    private: System::Void btnClose_MouseEnter(Object^ s, EventArgs^ e) {
        btnClose->BackColor = RED_DANGER;
        btnClose->ForeColor = Color::White;
    }
    private: System::Void btnClose_MouseLeave(Object^ s, EventArgs^ e) {
        btnClose->BackColor = Color::Transparent;
        btnClose->ForeColor = Color::FromArgb(180, 200, 230);
    }

    private: System::Void btnMin_Click(Object^ s, EventArgs^ e) {
        this->WindowState = FormWindowState::Minimized;
    }
    private: System::Void btnMin_MouseEnter(Object^ s, EventArgs^ e) {
        btnMin->BackColor = Color::FromArgb(60, 80, 140);
    }
    private: System::Void btnMin_MouseLeave(Object^ s, EventArgs^ e) {
        btnMin->BackColor = Color::Transparent;
    }

    private: System::Void btnMax_Click(Object^ s, EventArgs^ e) {
        if (this->WindowState == FormWindowState::Maximized)
            this->WindowState = FormWindowState::Normal;
        else
            this->WindowState = FormWindowState::Maximized;
    }
    private: System::Void btnMax_MouseEnter(Object^ s, EventArgs^ e) {
        btnMax->BackColor = Color::FromArgb(60, 80, 140);
    }
    private: System::Void btnMax_MouseLeave(Object^ s, EventArgs^ e) {
        btnMax->BackColor = Color::Transparent;
    }

           // ===== ORIGINAL HANDLERS (preserved) =====
    private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {}

    private: void UpdateTotals() {
        double subtotal = 0;
        for (int i = 0; i < cartGrid->Rows->Count; i++) {
            if (!cartGrid->Rows[i]->IsNewRow) {
                double val = Double::Parse(cartGrid->Rows[i]->Cells["colTotal"]->Value->ToString());
                subtotal += val;
            }
        }
        int itemCount = cartGrid->Rows->Count;   // Now that AllowUserToAddRows = false, no -1 needed
        double discount = 0;
        if (itemCount >= DISCOUNT_THRESHOLD_2)
            discount = subtotal * DISCOUNT_RATE_2;
        else if (itemCount >= DISCOUNT_THRESHOLD_1)
            discount = subtotal * DISCOUNT_RATE_1;
        double tax = (subtotal - discount) * TAX_RATE;
        double grandTotal = subtotal - discount + tax;

        lblSubtotal->Text = "Rs " + subtotal.ToString("N2");
        lblDiscount->Text = "- Rs " + discount.ToString("N2");
        lblTaxCaption->Text = "Tax (" + (TAX_RATE * 100).ToString("F0") + "%)";
        lblTax->Text = "Rs " + tax.ToString("N2");
        lblGrandTotal->Text = "Rs " + grandTotal.ToString("N2");
    }

    private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
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
        UpdateTotals();
    }

    private: System::Void btnBilling_Click(System::Object^ sender, System::EventArgs^ e) {
        if (cartGrid->Rows->Count == 0) {
            MessageBox::Show("Cart is empty! Please add items first.", "Warning"); return;
        }
        BillingForm^ billingForm = gcnew BillingForm(cartGrid);
        billingForm->ShowDialog();
    }

    private: System::Void btnSettings_Click(System::Object^ sender, System::EventArgs^ e) {
        if (currentRole->ToLower() != "admin") {
            MessageBox::Show("Access Denied! Admin only.", "Security"); return;
        }
        SettingsForm^ settings = gcnew SettingsForm();
        settings->ShowDialog();
        UpdateTotals();
    }

     private: System::Void btnLogout_Click(System::Object^ sender, System::EventArgs^ e) {
         System::Windows::Forms::DialogResult result = MessageBox::Show(
             "Are you sure you want to log out?",
             "Confirm Logout",
             MessageBoxButtons::YesNo,
             MessageBoxIcon::Question);

         if (result == System::Windows::Forms::DialogResult::Yes) {
             SBS::Session::Logout();
             this->Close();
         }
     }

    private: System::Void btnLogout_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
        btnLogout->BackColor = Color::FromArgb(220, 38, 38);
        btnLogout->ForeColor = Color::White;
    }

    private: System::Void btnLogout_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
        btnLogout->BackColor = NAVY;
        btnLogout->ForeColor = Color::FromArgb(255, 180, 180);
    }

    private: System::Void cartGrid_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
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
    private: System::Void CartForm_Activated(System::Object^ sender, System::EventArgs^ e) {
        UpdateTotals();
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