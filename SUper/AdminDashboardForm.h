#pragma once
#include "session.h"
#include "database.h"
#include "SalesReportForm.h"
#include "BestSellersForm.h"
#include "PaymentMethodForm.h"
#include "SettingsForm.h"
#include "ProductsForm.h"
#include "UserManageForm.h"
#include "BillHistoryForm.h"

namespace SUper {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    public ref class AdminDashboardForm : public System::Windows::Forms::Form
    {
    public:
        AdminDashboardForm(void)
        {
            InitializeComponent();
            ApplyModernStyle();
        }

    protected:
        ~AdminDashboardForm()
        {
            if (components) { delete components; }
        }

        // ===== Brand palette =====
    private:
        static Color NAVY;
        static Color NAVY_DARK;
        static Color NAVY_HOVER;
        static Color GREEN_ACCENT;
        static Color BLUE_ACCENT;
        static Color ORANGE_ACCENT;
        static Color PURPLE_ACCENT;
        static Color BG_LIGHT;
        static Color BORDER_GREY;
        static Color TEXT_DARK;
        static Color TEXT_MUTED;

        static AdminDashboardForm()
        {
            NAVY = Color::FromArgb(30, 58, 138);
            NAVY_DARK = Color::FromArgb(15, 30, 90);
            NAVY_HOVER = Color::FromArgb(45, 75, 165);
            GREEN_ACCENT = Color::FromArgb(34, 197, 94);
            BLUE_ACCENT = Color::FromArgb(59, 130, 246);
            ORANGE_ACCENT = Color::FromArgb(249, 115, 22);
            PURPLE_ACCENT = Color::FromArgb(168, 85, 247);
            BG_LIGHT = Color::FromArgb(248, 250, 252);
            BORDER_GREY = Color::FromArgb(229, 231, 235);
            TEXT_DARK = Color::FromArgb(30, 41, 59);
            TEXT_MUTED = Color::FromArgb(100, 116, 139);
        }

        // ===== Original controls (names preserved) =====
    private: System::Windows::Forms::Label^ lblHead;
    private: System::Windows::Forms::Label^ lblWelcome;
    private: System::Windows::Forms::Button^ btnReports;
    private: System::Windows::Forms::Button^ btnLogout;
    private: System::Windows::Forms::Button^ btnSettings;
    private: System::Windows::Forms::Button^ btnPayments;
    private: System::Windows::Forms::Button^ btnBestSellers;
    private: System::Windows::Forms::Button^ btnRefresh;
    private: System::Windows::Forms::Label^ lblTodayCaption;
    private: System::Windows::Forms::Label^ lblTodayValue;
    private: System::Windows::Forms::Label^ lblWeekCaption;
    private: System::Windows::Forms::Label^ lblWeekValue;
    private: System::Windows::Forms::Label^ lblMonthCaption;
    private: System::Windows::Forms::Label^ lblMonthValue;
    private: System::Windows::Forms::Label^ lblAllTimeCaption;
    private: System::Windows::Forms::Label^ lblAllTimeValue;
    private: System::Windows::Forms::Button^ btnUsers;
    private: System::Windows::Forms::Button^ btnProducts;
    private: System::Windows::Forms::Button^ btnBillHistory;

           // ===== New layout controls =====
    private: System::Windows::Forms::Panel^ pnlSidebar;
    private: System::Windows::Forms::Panel^ pnlContent;
    private: System::Windows::Forms::PictureBox^ picLogo;
    private: System::Windows::Forms::Label^ lblBrand;
    private: System::Windows::Forms::Label^ lblPanelLabel;
    private: System::Windows::Forms::Label^ lblSubtitle;
    private: System::Windows::Forms::Panel^ pnlCardToday;
    private: System::Windows::Forms::Panel^ pnlCardWeek;
    private: System::Windows::Forms::Panel^ pnlCardMonth;
    private: System::Windows::Forms::Panel^ pnlCardAllTime;
    private: System::Windows::Forms::Panel^ pnlInfoCard;
    private: System::Windows::Forms::Label^ lblInfoTitle;
    private: System::Windows::Forms::Label^ lblInfoText;
    private: System::Windows::Forms::Label^ btnClose;
    private: System::Windows::Forms::Label^ btnMin;

    private:
        bool dragging;
        Point dragOffset;
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->lblHead = gcnew Label();
            this->lblWelcome = gcnew Label();
            this->btnReports = gcnew Button();
            this->btnLogout = gcnew Button();
            this->btnSettings = gcnew Button();
            this->btnPayments = gcnew Button();
            this->btnBestSellers = gcnew Button();
            this->btnRefresh = gcnew Button();
            this->lblTodayCaption = gcnew Label();
            this->lblTodayValue = gcnew Label();
            this->lblWeekCaption = gcnew Label();
            this->lblWeekValue = gcnew Label();
            this->lblMonthCaption = gcnew Label();
            this->lblMonthValue = gcnew Label();
            this->lblAllTimeCaption = gcnew Label();
            this->lblAllTimeValue = gcnew Label();
            this->btnUsers = gcnew Button();
            this->btnProducts = gcnew Button();
            this->btnBillHistory = gcnew Button();
            this->pnlSidebar = gcnew Panel();
            this->pnlContent = gcnew Panel();
            this->picLogo = gcnew PictureBox();
            this->lblBrand = gcnew Label();
            this->lblPanelLabel = gcnew Label();
            this->lblSubtitle = gcnew Label();
            this->pnlCardToday = gcnew Panel();
            this->pnlCardWeek = gcnew Panel();
            this->pnlCardMonth = gcnew Panel();
            this->pnlCardAllTime = gcnew Panel();
            this->pnlInfoCard = gcnew Panel();
            this->lblInfoTitle = gcnew Label();
            this->lblInfoText = gcnew Label();
            this->btnClose = gcnew Label();
            this->btnMin = gcnew Label();
            this->SuspendLayout();

            // ============ SIDEBAR ============
            this->pnlSidebar->Location = Point(0, 0);
            this->pnlSidebar->Size = System::Drawing::Size(240, 680);
            this->pnlSidebar->BackColor = NAVY;
            this->pnlSidebar->Paint += gcnew PaintEventHandler(this, &AdminDashboardForm::pnlSidebar_Paint);
            this->pnlSidebar->MouseDown += gcnew MouseEventHandler(this, &AdminDashboardForm::Form_MouseDown);
            this->pnlSidebar->MouseMove += gcnew MouseEventHandler(this, &AdminDashboardForm::Form_MouseMove);
            this->pnlSidebar->MouseUp += gcnew MouseEventHandler(this, &AdminDashboardForm::Form_MouseUp);

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

            // welcome (now in sidebar)
            this->lblWelcome->AutoSize = true;
            this->lblWelcome->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0F);
            this->lblWelcome->ForeColor = Color::FromArgb(180, 200, 230);
            this->lblWelcome->BackColor = Color::Transparent;
            this->lblWelcome->Location = Point(90, 62);
            this->lblWelcome->Text = L"Welcome, Admin";

            // panel label
            this->lblPanelLabel->AutoSize = true;
            this->lblPanelLabel->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.0F, FontStyle::Bold);
            this->lblPanelLabel->ForeColor = Color::FromArgb(140, 160, 200);
            this->lblPanelLabel->BackColor = Color::Transparent;
            this->lblPanelLabel->Location = Point(28, 120);
            this->lblPanelLabel->Text = L"ADMIN PANEL";

            // sidebar nav buttons
            ConfigureSidebarButton(btnReports, L"Sales Reports", 150);
            ConfigureSidebarButton(btnBestSellers, L"Best Sellers", 198);
            ConfigureSidebarButton(btnBillHistory, L"Bill History", 246);
            ConfigureSidebarButton(btnProducts, L"Products", 294);
            ConfigureSidebarButton(btnUsers, L"Users", 342);
            ConfigureSidebarButton(btnPayments, L"Payment Methods", 390);
            ConfigureSidebarButton(btnSettings, L"Settings", 438);

            btnReports->Click += gcnew EventHandler(this, &AdminDashboardForm::btnReports_Click);
            btnBestSellers->Click += gcnew EventHandler(this, &AdminDashboardForm::btnBills_Click);
            btnBillHistory->Click += gcnew EventHandler(this, &AdminDashboardForm::btnBillHistory_Click);
            btnProducts->Click += gcnew EventHandler(this, &AdminDashboardForm::btnProducts_Click);
            btnUsers->Click += gcnew EventHandler(this, &AdminDashboardForm::btnUsers_Click);
            btnPayments->Click += gcnew EventHandler(this, &AdminDashboardForm::btnPayments_Click);
            btnSettings->Click += gcnew EventHandler(this, &AdminDashboardForm::btnSettings_Click);

            // logout (bottom of sidebar)
            this->btnLogout->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
            this->btnLogout->BackColor = NAVY;
            this->btnLogout->ForeColor = Color::FromArgb(255, 180, 180);
            this->btnLogout->FlatStyle = FlatStyle::Flat;
            this->btnLogout->FlatAppearance->BorderSize = 0;
            this->btnLogout->Location = Point(0, 612);
            this->btnLogout->Size = System::Drawing::Size(240, 48);
            this->btnLogout->Text = L"Log Out";
            this->btnLogout->TextAlign = ContentAlignment::MiddleLeft;
            this->btnLogout->Padding = System::Windows::Forms::Padding(28, 0, 0, 0);
            this->btnLogout->Cursor = Cursors::Hand;
            this->btnLogout->TabStop = false;
            this->btnLogout->Click += gcnew EventHandler(this, &AdminDashboardForm::btnLogout_Click);
            this->btnLogout->MouseEnter += gcnew EventHandler(this, &AdminDashboardForm::btnLogout_MouseEnter);
            this->btnLogout->MouseLeave += gcnew EventHandler(this, &AdminDashboardForm::btnLogout_MouseLeave);

            this->pnlSidebar->Controls->Add(this->picLogo);
            this->pnlSidebar->Controls->Add(this->lblBrand);
            this->pnlSidebar->Controls->Add(this->lblWelcome);
            this->pnlSidebar->Controls->Add(this->lblPanelLabel);
            this->pnlSidebar->Controls->Add(this->btnReports);
            this->pnlSidebar->Controls->Add(this->btnBestSellers);
            this->pnlSidebar->Controls->Add(this->btnBillHistory);
            this->pnlSidebar->Controls->Add(this->btnProducts);
            this->pnlSidebar->Controls->Add(this->btnUsers);
            this->pnlSidebar->Controls->Add(this->btnPayments);
            this->pnlSidebar->Controls->Add(this->btnSettings);
            this->pnlSidebar->Controls->Add(this->btnLogout);

            // ============ CONTENT AREA ============
            this->pnlContent->Location = Point(240, 0);
            this->pnlContent->Size = System::Drawing::Size(960, 680);
            this->pnlContent->BackColor = BG_LIGHT;
            this->pnlContent->MouseDown += gcnew MouseEventHandler(this, &AdminDashboardForm::Form_MouseDown);
            this->pnlContent->MouseMove += gcnew MouseEventHandler(this, &AdminDashboardForm::Form_MouseMove);
            this->pnlContent->MouseUp += gcnew MouseEventHandler(this, &AdminDashboardForm::Form_MouseUp);

            // header
            this->lblHead->AutoSize = true;
            this->lblHead->Font = gcnew System::Drawing::Font(L"Segoe UI", 22.0F, FontStyle::Bold);
            this->lblHead->ForeColor = TEXT_DARK;
            this->lblHead->BackColor = Color::Transparent;
            this->lblHead->Location = Point(40, 40);
            this->lblHead->Text = L"Dashboard";

            // subtitle
            this->lblSubtitle->AutoSize = true;
            this->lblSubtitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F);
            this->lblSubtitle->ForeColor = TEXT_MUTED;
            this->lblSubtitle->BackColor = Color::Transparent;
            this->lblSubtitle->Location = Point(42, 80);
            this->lblSubtitle->Text = L"Sales overview and quick stats";

            // refresh
            this->btnRefresh->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5F, FontStyle::Bold);
            this->btnRefresh->BackColor = NAVY;
            this->btnRefresh->ForeColor = Color::White;
            this->btnRefresh->FlatStyle = FlatStyle::Flat;
            this->btnRefresh->FlatAppearance->BorderSize = 0;
            this->btnRefresh->Location = Point(700, 50);
            this->btnRefresh->Size = System::Drawing::Size(130, 40);
            this->btnRefresh->Text = L"\u27F3  Refresh";
            this->btnRefresh->Cursor = Cursors::Hand;
            this->btnRefresh->Click += gcnew EventHandler(this, &AdminDashboardForm::btnRefresh_Click);
            this->btnRefresh->MouseEnter += gcnew EventHandler(this, &AdminDashboardForm::btnRefresh_MouseEnter);
            this->btnRefresh->MouseLeave += gcnew EventHandler(this, &AdminDashboardForm::btnRefresh_MouseLeave);

            // window controls
            this->btnMin->Text = L"\u2013";   // –
            this->btnMin->Font = gcnew System::Drawing::Font(L"Segoe UI", 12.0F, FontStyle::Bold);
            this->btnMin->ForeColor = TEXT_MUTED;
            this->btnMin->BackColor = Color::Transparent;
            this->btnMin->Location = Point(870, 15);
            this->btnMin->Size = System::Drawing::Size(35, 30);
            this->btnMin->TextAlign = ContentAlignment::MiddleCenter;
            this->btnMin->Cursor = Cursors::Hand;
            this->btnMin->Click += gcnew EventHandler(this, &AdminDashboardForm::btnMin_Click);
            this->btnMin->MouseEnter += gcnew EventHandler(this, &AdminDashboardForm::btnMin_MouseEnter);
            this->btnMin->MouseLeave += gcnew EventHandler(this, &AdminDashboardForm::btnMin_MouseLeave);

            this->btnClose->Text = L"\u2715";   // ✕
            this->btnClose->Font = gcnew System::Drawing::Font(L"Segoe UI", 12.0F, FontStyle::Bold);
            this->btnClose->ForeColor = TEXT_MUTED;
            this->btnClose->BackColor = Color::Transparent;
            this->btnClose->Location = Point(910, 15);
            this->btnClose->Size = System::Drawing::Size(35, 30);
            this->btnClose->TextAlign = ContentAlignment::MiddleCenter;
            this->btnClose->Cursor = Cursors::Hand;
            this->btnClose->Click += gcnew EventHandler(this, &AdminDashboardForm::btnClose_Click);
            this->btnClose->MouseEnter += gcnew EventHandler(this, &AdminDashboardForm::btnClose_MouseEnter);
            this->btnClose->MouseLeave += gcnew EventHandler(this, &AdminDashboardForm::btnClose_MouseLeave);

            // KPI cards
            ConfigureKPICard(pnlCardToday, Point(40, 140), GREEN_ACCENT);
            ConfigureKPICard(pnlCardWeek, Point(270, 140), BLUE_ACCENT);
            ConfigureKPICard(pnlCardMonth, Point(500, 140), ORANGE_ACCENT);
            ConfigureKPICard(pnlCardAllTime, Point(730, 140), PURPLE_ACCENT);

            ConfigureKPILabels(lblTodayCaption, lblTodayValue, pnlCardToday, L"TODAY", L"Rs 0.00");
            ConfigureKPILabels(lblWeekCaption, lblWeekValue, pnlCardWeek, L"LAST 7 DAYS", L"Rs 0.00");
            ConfigureKPILabels(lblMonthCaption, lblMonthValue, pnlCardMonth, L"LAST 30 DAYS", L"Rs 0.00");
            ConfigureKPILabels(lblAllTimeCaption, lblAllTimeValue, pnlCardAllTime, L"BILLS (ALL TIME)", L"0");

            // info card
            this->pnlInfoCard->Location = Point(40, 290);
            this->pnlInfoCard->Size = System::Drawing::Size(880, 340);
            this->pnlInfoCard->BackColor = Color::White;
            this->pnlInfoCard->Paint += gcnew PaintEventHandler(this, &AdminDashboardForm::pnlInfoCard_Paint);
            this->pnlInfoCard->MouseDown += gcnew MouseEventHandler(this, &AdminDashboardForm::Form_MouseDown);
            this->pnlInfoCard->MouseMove += gcnew MouseEventHandler(this, &AdminDashboardForm::Form_MouseMove);
            this->pnlInfoCard->MouseUp += gcnew MouseEventHandler(this, &AdminDashboardForm::Form_MouseUp);

            this->lblInfoTitle->AutoSize = true;
            this->lblInfoTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 14.0F, FontStyle::Bold);
            this->lblInfoTitle->ForeColor = TEXT_DARK;
            this->lblInfoTitle->BackColor = Color::Transparent;
            this->lblInfoTitle->Location = Point(30, 25);
            this->lblInfoTitle->Text = L"Quick Tips";

            this->lblInfoText->AutoSize = false;
            this->lblInfoText->Size = System::Drawing::Size(820, 250);
            this->lblInfoText->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F);
            this->lblInfoText->ForeColor = TEXT_MUTED;
            this->lblInfoText->BackColor = Color::Transparent;
            this->lblInfoText->Location = Point(30, 70);
            this->lblInfoText->Text =
                L"\u2022   Use the sidebar to navigate to any management section.\r\n\r\n"
                L"\u2022   Tap Refresh in the top right to update the stats above.\r\n\r\n"
                L"\u2022   Sales totals exclude cancelled bills.\r\n\r\n"
                L"\u2022   Today's revenue resets at midnight (server time).";

            this->pnlInfoCard->Controls->Add(this->lblInfoTitle);
            this->pnlInfoCard->Controls->Add(this->lblInfoText);

            this->pnlContent->Controls->Add(this->lblHead);
            this->pnlContent->Controls->Add(this->lblSubtitle);
            this->pnlContent->Controls->Add(this->btnRefresh);
            this->pnlContent->Controls->Add(this->btnMin);
            this->pnlContent->Controls->Add(this->btnClose);
            this->pnlContent->Controls->Add(this->pnlCardToday);
            this->pnlContent->Controls->Add(this->pnlCardWeek);
            this->pnlContent->Controls->Add(this->pnlCardMonth);
            this->pnlContent->Controls->Add(this->pnlCardAllTime);
            this->pnlContent->Controls->Add(this->pnlInfoCard);

            // ============ FORM ============
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1200, 680);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->BackColor = Color::White;
            this->DoubleBuffered = true;
            this->Controls->Add(this->pnlSidebar);
            this->Controls->Add(this->pnlContent);
            this->Name = L"AdminDashboardForm";
            this->Text = L"Admin Dashboard - ValueMart";
            this->Load += gcnew EventHandler(this, &AdminDashboardForm::AdminDashboardForm_Load);
            this->MouseDown += gcnew MouseEventHandler(this, &AdminDashboardForm::Form_MouseDown);
            this->MouseMove += gcnew MouseEventHandler(this, &AdminDashboardForm::Form_MouseMove);
            this->MouseUp += gcnew MouseEventHandler(this, &AdminDashboardForm::Form_MouseUp);
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
        btn->MouseEnter += gcnew EventHandler(this, &AdminDashboardForm::SidebarBtn_MouseEnter);
        btn->MouseLeave += gcnew EventHandler(this, &AdminDashboardForm::SidebarBtn_MouseLeave);
    }

    private: void ConfigureKPICard(Panel^ card, Point loc, Color accent) {
        card->Location = loc;
        card->Size = System::Drawing::Size(210, 120);
        card->BackColor = Color::White;
        card->Tag = accent;
        card->Paint += gcnew PaintEventHandler(this, &AdminDashboardForm::Card_Paint);
        card->MouseDown += gcnew MouseEventHandler(this, &AdminDashboardForm::Form_MouseDown);
        card->MouseMove += gcnew MouseEventHandler(this, &AdminDashboardForm::Form_MouseMove);
        card->MouseUp += gcnew MouseEventHandler(this, &AdminDashboardForm::Form_MouseUp);
    }

    private: void ConfigureKPILabels(Label^ caption, Label^ value, Panel^ parent,
        String^ capText, String^ valText) {
        caption->AutoSize = true;
        caption->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5F, FontStyle::Bold);
        caption->ForeColor = TEXT_MUTED;
        caption->BackColor = Color::Transparent;
        caption->Location = Point(25, 30);
        caption->Text = capText;

        value->AutoSize = true;
        value->Font = gcnew System::Drawing::Font(L"Segoe UI", 19.0F, FontStyle::Bold);
        value->ForeColor = TEXT_DARK;
        value->BackColor = Color::Transparent;
        value->Location = Point(25, 60);
        value->Text = valText;

        parent->Controls->Add(caption);
        parent->Controls->Add(value);
    }

    private: void ApplyModernStyle() {
        RoundControl(btnRefresh, 6);
        RoundControl(pnlCardToday, 10);
        RoundControl(pnlCardWeek, 10);
        RoundControl(pnlCardMonth, 10);
        RoundControl(pnlCardAllTime, 10);
        RoundControl(pnlInfoCard, 10);

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
        e->Graphics->DrawLine(pen, 20, 605, 220, 605);
    }

    private: System::Void Card_Paint(Object^ sender, PaintEventArgs^ e) {
        Panel^ card = (Panel^)sender;
        Color accent = safe_cast<Color>(card->Tag);
        e->Graphics->SmoothingMode = SmoothingMode::AntiAlias;
        Pen^ borderPen = gcnew Pen(BORDER_GREY, 1);
        e->Graphics->DrawRectangle(borderPen, 0, 0, card->Width - 1, card->Height - 1);
        SolidBrush^ accentBrush = gcnew SolidBrush(accent);
        e->Graphics->FillRectangle(accentBrush, 0, 0, card->Width, 4);
        e->Graphics->FillEllipse(accentBrush, card->Width - 22, 18, 8, 8);
    }

    private: System::Void pnlInfoCard_Paint(Object^ sender, PaintEventArgs^ e) {
        Pen^ borderPen = gcnew Pen(BORDER_GREY, 1);
        e->Graphics->DrawRectangle(borderPen, 0, 0, pnlInfoCard->Width - 1, pnlInfoCard->Height - 1);
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

    private: System::Void btnLogout_MouseEnter(Object^ sender, EventArgs^ e) {
        btnLogout->BackColor = Color::FromArgb(220, 38, 38);
        btnLogout->ForeColor = Color::White;
    }
    private: System::Void btnLogout_MouseLeave(Object^ sender, EventArgs^ e) {
        btnLogout->BackColor = NAVY;
        btnLogout->ForeColor = Color::FromArgb(255, 180, 180);
    }

    private: System::Void btnRefresh_MouseEnter(Object^ sender, EventArgs^ e) {
        btnRefresh->BackColor = NAVY_HOVER;
    }
    private: System::Void btnRefresh_MouseLeave(Object^ sender, EventArgs^ e) {
        btnRefresh->BackColor = NAVY;
    }

    private: System::Void btnClose_Click(Object^ sender, EventArgs^ e) {
        this->Close();
    }
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

           // ============ ORIGINAL HANDLERS (preserved exactly) ============
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

    private: System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e) {
        LoadDashboardTiles();
    }

    private: System::Void btnProducts_Click(System::Object^ sender, System::EventArgs^ e) {
        ProductsForm^ form = gcnew ProductsForm();
        form->ShowDialog();
        LoadDashboardTiles();
    }

    private: System::Void btnUsers_Click(System::Object^ sender, System::EventArgs^ e) {
        User^ adminUser = gcnew User(
            SBS::Session::GetUserID(),
            SBS::Session::GetUsername(),
            "",
            SBS::Session::GetRole(),
            true);
        UserManagementForm^ form = gcnew UserManagementForm(adminUser);
        form->ShowDialog();
    }

    private: System::Void btnBillHistory_Click(System::Object^ sender, System::EventArgs^ e) {
        BillHistoryForm^ form = gcnew BillHistoryForm();
        form->ShowDialog();
        LoadDashboardTiles();
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
    };
}