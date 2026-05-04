#pragma once
#define _COM_NO_STANDARD_GUIDS_
#include "database.h"
#include "product.h"

namespace SUper {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Data::SqlClient;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    public ref class SearchProductForm : public Form {
    private:
        static Color NAVY;
        static Color NAVY_HOVER;
        static Color BG_LIGHT;
        static Color BORDER_GREY;
        static Color TEXT_DARK;
        static Color TEXT_MUTED;

        static SearchProductForm() {
            NAVY = Color::FromArgb(30, 58, 138);
            NAVY_HOVER = Color::FromArgb(45, 75, 165);
            BG_LIGHT = Color::FromArgb(248, 250, 252);
            BORDER_GREY = Color::FromArgb(229, 231, 235);
            TEXT_DARK = Color::FromArgb(30, 41, 59);
            TEXT_MUTED = Color::FromArgb(100, 116, 139);
        }

        TextBox^ txtSearchName;
        TextBox^ txtSearchID;
        Button^ btnSearchName;
        Button^ btnSearchID;
        Button^ btnClose;
        DataGridView^ dgvResults;
        Label^ lblResults;
        Label^ btnTopClose;
        Panel^ pnlSearchCard;
        Panel^ pnlGridCard;
        Panel^ pnlNameLine;
        Panel^ pnlIDLine;

        bool dragging;
        Point dragOffset;

    public:
        SearchProductForm() {
            InitializeComponent();
            ApplyModernStyle();
        }

    private:
        void InitializeComponent() {
            this->Text = "Search Products";
            this->ClientSize = System::Drawing::Size(780, 600);
            this->StartPosition = FormStartPosition::CenterParent;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->BackColor = BG_LIGHT;
            this->DoubleBuffered = true;

            // Header
            Panel^ pnlHeader = gcnew Panel();
            pnlHeader->Location = Point(0, 0);
            pnlHeader->Size = System::Drawing::Size(780, 75);
            pnlHeader->BackColor = Color::White;
            pnlHeader->Paint += gcnew PaintEventHandler(this, &SearchProductForm::pnlHeader_Paint);
            pnlHeader->MouseDown += gcnew MouseEventHandler(this, &SearchProductForm::Form_MouseDown);
            pnlHeader->MouseMove += gcnew MouseEventHandler(this, &SearchProductForm::Form_MouseMove);
            pnlHeader->MouseUp += gcnew MouseEventHandler(this, &SearchProductForm::Form_MouseUp);

            Label^ lblTitle = gcnew Label();
            lblTitle->Text = "Search Products";
            lblTitle->Font = gcnew System::Drawing::Font("Segoe UI", 16.0F, FontStyle::Bold);
            lblTitle->ForeColor = TEXT_DARK;
            lblTitle->BackColor = Color::Transparent;
            lblTitle->Location = Point(25, 18);
            lblTitle->AutoSize = true;

            Label^ lblSub = gcnew Label();
            lblSub->Text = "Find products by name or ID";
            lblSub->Font = gcnew System::Drawing::Font("Segoe UI", 9.0F);
            lblSub->ForeColor = TEXT_MUTED;
            lblSub->BackColor = Color::Transparent;
            lblSub->Location = Point(27, 47);
            lblSub->AutoSize = true;

            btnTopClose = gcnew Label();
            btnTopClose->Text = L"\u2715";
            btnTopClose->Font = gcnew System::Drawing::Font("Segoe UI", 12.0F, FontStyle::Bold);
            btnTopClose->ForeColor = TEXT_MUTED;
            btnTopClose->Location = Point(730, 20);
            btnTopClose->Size = System::Drawing::Size(35, 30);
            btnTopClose->TextAlign = ContentAlignment::MiddleCenter;
            btnTopClose->Cursor = Cursors::Hand;
            btnTopClose->Click += gcnew EventHandler(this, &SearchProductForm::btnClose_Click);
            btnTopClose->MouseEnter += gcnew EventHandler(this, &SearchProductForm::btnTopClose_MouseEnter);
            btnTopClose->MouseLeave += gcnew EventHandler(this, &SearchProductForm::btnTopClose_MouseLeave);

            pnlHeader->Controls->Add(lblTitle);
            pnlHeader->Controls->Add(lblSub);
            pnlHeader->Controls->Add(btnTopClose);

            // ===== SEARCH CARD =====
            pnlSearchCard = gcnew Panel();
            pnlSearchCard->Location = Point(20, 90);
            pnlSearchCard->Size = System::Drawing::Size(740, 110);
            pnlSearchCard->BackColor = Color::White;
            pnlSearchCard->Paint += gcnew PaintEventHandler(this, &SearchProductForm::pnlCard_Paint);

            // Search by name
            Label^ lblName = gcnew Label();
            lblName->Text = "BY NAME";
            lblName->Font = gcnew System::Drawing::Font("Segoe UI", 8.5F, FontStyle::Bold);
            lblName->ForeColor = TEXT_MUTED;
            lblName->Location = Point(20, 18);
            lblName->AutoSize = true;

            txtSearchName = gcnew TextBox();
            txtSearchName->BorderStyle = BorderStyle::None;
            txtSearchName->Font = gcnew System::Drawing::Font("Segoe UI", 11.0F);
            txtSearchName->ForeColor = TEXT_MUTED;
            txtSearchName->Text = "e.g. Milk, Soap...";
            txtSearchName->Location = Point(20, 40);
            txtSearchName->Size = System::Drawing::Size(310, 22);
            txtSearchName->Enter += gcnew EventHandler(this, &SearchProductForm::txtSearchName_Enter);
            txtSearchName->Leave += gcnew EventHandler(this, &SearchProductForm::txtSearchName_Leave);

            pnlNameLine = gcnew Panel();
            pnlNameLine->Location = Point(20, 67);
            pnlNameLine->Size = System::Drawing::Size(310, 2);
            pnlNameLine->BackColor = BORDER_GREY;

            btnSearchName = gcnew Button();
            btnSearchName->Text = "Search";
            btnSearchName->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F, FontStyle::Bold);
            btnSearchName->BackColor = NAVY;
            btnSearchName->ForeColor = Color::White;
            btnSearchName->FlatStyle = FlatStyle::Flat;
            btnSearchName->FlatAppearance->BorderSize = 0;
            btnSearchName->Location = Point(345, 38);
            btnSearchName->Size = System::Drawing::Size(90, 32);
            btnSearchName->Cursor = Cursors::Hand;
            btnSearchName->Click += gcnew EventHandler(this, &SearchProductForm::btnSearchName_Click);
            btnSearchName->MouseEnter += gcnew EventHandler(this, &SearchProductForm::btnSearchName_MouseEnter);
            btnSearchName->MouseLeave += gcnew EventHandler(this, &SearchProductForm::btnSearchName_MouseLeave);

            // Search by ID
            Label^ lblID = gcnew Label();
            lblID->Text = "BY ID";
            lblID->Font = gcnew System::Drawing::Font("Segoe UI", 8.5F, FontStyle::Bold);
            lblID->ForeColor = TEXT_MUTED;
            lblID->Location = Point(465, 18);
            lblID->AutoSize = true;

            txtSearchID = gcnew TextBox();
            txtSearchID->BorderStyle = BorderStyle::None;
            txtSearchID->Font = gcnew System::Drawing::Font("Segoe UI", 11.0F);
            txtSearchID->ForeColor = TEXT_MUTED;
            txtSearchID->Text = "e.g. 3";
            txtSearchID->Location = Point(465, 40);
            txtSearchID->Size = System::Drawing::Size(150, 22);
            txtSearchID->Enter += gcnew EventHandler(this, &SearchProductForm::txtSearchID_Enter);
            txtSearchID->Leave += gcnew EventHandler(this, &SearchProductForm::txtSearchID_Leave);

            pnlIDLine = gcnew Panel();
            pnlIDLine->Location = Point(465, 67);
            pnlIDLine->Size = System::Drawing::Size(150, 2);
            pnlIDLine->BackColor = BORDER_GREY;

            btnSearchID = gcnew Button();
            btnSearchID->Text = "Search";
            btnSearchID->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F, FontStyle::Bold);
            btnSearchID->BackColor = NAVY;
            btnSearchID->ForeColor = Color::White;
            btnSearchID->FlatStyle = FlatStyle::Flat;
            btnSearchID->FlatAppearance->BorderSize = 0;
            btnSearchID->Location = Point(625, 38);
            btnSearchID->Size = System::Drawing::Size(90, 32);
            btnSearchID->Cursor = Cursors::Hand;
            btnSearchID->Click += gcnew EventHandler(this, &SearchProductForm::btnSearchID_Click);
            btnSearchID->MouseEnter += gcnew EventHandler(this, &SearchProductForm::btnSearchID_MouseEnter);
            btnSearchID->MouseLeave += gcnew EventHandler(this, &SearchProductForm::btnSearchID_MouseLeave);

            pnlSearchCard->Controls->Add(lblName);
            pnlSearchCard->Controls->Add(txtSearchName);
            pnlSearchCard->Controls->Add(pnlNameLine);
            pnlSearchCard->Controls->Add(btnSearchName);
            pnlSearchCard->Controls->Add(lblID);
            pnlSearchCard->Controls->Add(txtSearchID);
            pnlSearchCard->Controls->Add(pnlIDLine);
            pnlSearchCard->Controls->Add(btnSearchID);

            // Results label
            lblResults = gcnew Label();
            lblResults->Text = "Enter a search term and click Search";
            lblResults->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F);
            lblResults->ForeColor = TEXT_MUTED;
            lblResults->Location = Point(25, 215);
            lblResults->AutoSize = true;

            // Grid card
            pnlGridCard = gcnew Panel();
            pnlGridCard->Location = Point(20, 245);
            pnlGridCard->Size = System::Drawing::Size(740, 280);
            pnlGridCard->BackColor = Color::White;
            pnlGridCard->Padding = System::Windows::Forms::Padding(1);
            pnlGridCard->Paint += gcnew PaintEventHandler(this, &SearchProductForm::pnlCard_Paint);

            dgvResults = gcnew DataGridView();
            StyleGrid(dgvResults);
            pnlGridCard->Controls->Add(dgvResults);

            // Close
            btnClose = gcnew Button();
            btnClose->Text = "Close";
            btnClose->Font = gcnew System::Drawing::Font("Segoe UI", 10.0F, FontStyle::Bold);
            btnClose->BackColor = Color::White;
            btnClose->ForeColor = TEXT_DARK;
            btnClose->FlatStyle = FlatStyle::Flat;
            btnClose->FlatAppearance->BorderSize = 1;
            btnClose->FlatAppearance->BorderColor = BORDER_GREY;
            btnClose->Location = Point(660, 545);
            btnClose->Size = System::Drawing::Size(100, 38);
            btnClose->Cursor = Cursors::Hand;
            btnClose->Click += gcnew EventHandler(this, &SearchProductForm::btnClose_Click);
            btnClose->MouseEnter += gcnew EventHandler(this, &SearchProductForm::btnClose_MouseEnter);
            btnClose->MouseLeave += gcnew EventHandler(this, &SearchProductForm::btnClose_MouseLeave);

            this->Controls->Add(pnlHeader);
            this->Controls->Add(pnlSearchCard);
            this->Controls->Add(lblResults);
            this->Controls->Add(pnlGridCard);
            this->Controls->Add(btnClose);

            this->MouseDown += gcnew MouseEventHandler(this, &SearchProductForm::Form_MouseDown);
            this->MouseMove += gcnew MouseEventHandler(this, &SearchProductForm::Form_MouseMove);
            this->MouseUp += gcnew MouseEventHandler(this, &SearchProductForm::Form_MouseUp);
            this->Paint += gcnew PaintEventHandler(this, &SearchProductForm::Form_Paint);
        }

        void StyleGrid(DataGridView^ grid) {
            grid->AllowUserToAddRows = false;
            grid->AllowUserToResizeRows = false;
            grid->ReadOnly = true;
            grid->BackgroundColor = Color::White;
            grid->BorderStyle = BorderStyle::None;
            grid->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
            grid->GridColor = BORDER_GREY;
            grid->RowHeadersVisible = false;
            grid->EnableHeadersVisualStyles = false;
            grid->ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle::None;
            grid->ColumnHeadersHeight = 42;
            grid->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
            grid->RowTemplate->Height = 36;
            grid->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            grid->MultiSelect = false;
            grid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            grid->Dock = DockStyle::Fill;

            DataGridViewCellStyle^ hs = gcnew DataGridViewCellStyle();
            hs->BackColor = NAVY;
            hs->ForeColor = Color::White;
            hs->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F, FontStyle::Bold);
            hs->Alignment = DataGridViewContentAlignment::MiddleLeft;
            hs->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
            hs->SelectionBackColor = NAVY;
            hs->SelectionForeColor = Color::White;
            grid->ColumnHeadersDefaultCellStyle = hs;

            DataGridViewCellStyle^ cs = gcnew DataGridViewCellStyle();
            cs->BackColor = Color::White;
            cs->ForeColor = TEXT_DARK;
            cs->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F);
            cs->Alignment = DataGridViewContentAlignment::MiddleLeft;
            cs->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
            cs->SelectionBackColor = Color::FromArgb(219, 234, 254);
            cs->SelectionForeColor = TEXT_DARK;
            grid->DefaultCellStyle = cs;

            DataGridViewCellStyle^ as_ = gcnew DataGridViewCellStyle();
            as_->BackColor = BG_LIGHT;
            as_->ForeColor = TEXT_DARK;
            as_->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F);
            as_->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
            as_->SelectionBackColor = Color::FromArgb(219, 234, 254);
            as_->SelectionForeColor = TEXT_DARK;
            grid->AlternatingRowsDefaultCellStyle = as_;
        }

        void ApplyModernStyle() {
            RoundControl(btnSearchName, 6);
            RoundControl(btnSearchID, 6);
            RoundControl(btnClose, 6);
            RoundControl(pnlSearchCard, 8);
            RoundControl(pnlGridCard, 8);
        }

        void RoundControl(Control^ ctrl, int radius) {
            GraphicsPath^ path = gcnew GraphicsPath();
            System::Drawing::Rectangle r = ctrl->ClientRectangle;
            path->AddArc(r.X, r.Y, radius, radius, 180, 90);
            path->AddArc(r.Right - radius, r.Y, radius, radius, 270, 90);
            path->AddArc(r.Right - radius, r.Bottom - radius, radius, radius, 0, 90);
            path->AddArc(r.X, r.Bottom - radius, radius, radius, 90, 90);
            path->CloseAllFigures();
            ctrl->Region = gcnew System::Drawing::Region(path);
        }

        void Form_Paint(Object^ s, PaintEventArgs^ e) {
            Pen^ pen = gcnew Pen(BORDER_GREY, 1);
            e->Graphics->DrawRectangle(pen, 0, 0, this->Width - 1, this->Height - 1);
        }
        void pnlHeader_Paint(Object^ sender, PaintEventArgs^ e) {
            Panel^ p = (Panel^)sender;
            Pen^ pen = gcnew Pen(BORDER_GREY, 1);
            e->Graphics->DrawLine(pen, 0, p->Height - 1, p->Width, p->Height - 1);
        }
        void pnlCard_Paint(Object^ sender, PaintEventArgs^ e) {
            Panel^ p = (Panel^)sender;
            Pen^ pen = gcnew Pen(BORDER_GREY, 1);
            e->Graphics->DrawRectangle(pen, 0, 0, p->Width - 1, p->Height - 1);
        }

        // Placeholder behavior
        void txtSearchName_Enter(Object^ s, EventArgs^ e) {
            if (txtSearchName->Text == "e.g. Milk, Soap...") {
                txtSearchName->Text = "";
                txtSearchName->ForeColor = TEXT_DARK;
            }
            pnlNameLine->BackColor = NAVY;
        }
        void txtSearchName_Leave(Object^ s, EventArgs^ e) {
            if (txtSearchName->Text->Trim() == "") {
                txtSearchName->Text = "e.g. Milk, Soap...";
                txtSearchName->ForeColor = TEXT_MUTED;
            }
            pnlNameLine->BackColor = BORDER_GREY;
        }
        void txtSearchID_Enter(Object^ s, EventArgs^ e) {
            if (txtSearchID->Text == "e.g. 3") {
                txtSearchID->Text = "";
                txtSearchID->ForeColor = TEXT_DARK;
            }
            pnlIDLine->BackColor = NAVY;
        }
        void txtSearchID_Leave(Object^ s, EventArgs^ e) {
            if (txtSearchID->Text->Trim() == "") {
                txtSearchID->Text = "e.g. 3";
                txtSearchID->ForeColor = TEXT_MUTED;
            }
            pnlIDLine->BackColor = BORDER_GREY;
        }

        // Drag
        void Form_MouseDown(Object^ s, MouseEventArgs^ e) {
            if (e->Button == System::Windows::Forms::MouseButtons::Left) {
                dragging = true;
                dragOffset = Point(
                    System::Windows::Forms::Cursor::Position.X - this->Location.X,
                    System::Windows::Forms::Cursor::Position.Y - this->Location.Y);
            }
        }
        void Form_MouseMove(Object^ s, MouseEventArgs^ e) {
            if (dragging) {
                this->Location = Point(
                    System::Windows::Forms::Cursor::Position.X - dragOffset.X,
                    System::Windows::Forms::Cursor::Position.Y - dragOffset.Y);
            }
        }
        void Form_MouseUp(Object^ s, MouseEventArgs^ e) { dragging = false; }

        // Hover
        void btnSearchName_MouseEnter(Object^ s, EventArgs^ e) { btnSearchName->BackColor = NAVY_HOVER; }
        void btnSearchName_MouseLeave(Object^ s, EventArgs^ e) { btnSearchName->BackColor = NAVY; }
        void btnSearchID_MouseEnter(Object^ s, EventArgs^ e) { btnSearchID->BackColor = NAVY_HOVER; }
        void btnSearchID_MouseLeave(Object^ s, EventArgs^ e) { btnSearchID->BackColor = NAVY; }
        void btnClose_MouseEnter(Object^ s, EventArgs^ e) { btnClose->BackColor = BG_LIGHT; }
        void btnClose_MouseLeave(Object^ s, EventArgs^ e) { btnClose->BackColor = Color::White; }
        void btnTopClose_MouseEnter(Object^ s, EventArgs^ e) {
            btnTopClose->BackColor = Color::FromArgb(239, 68, 68);
            btnTopClose->ForeColor = Color::White;
        }
        void btnTopClose_MouseLeave(Object^ s, EventArgs^ e) {
            btnTopClose->BackColor = Color::Transparent;
            btnTopClose->ForeColor = TEXT_MUTED;
        }

        // ===== ORIGINAL LOGIC =====
        void showResults(DataTable^ dt) {
            dgvResults->DataSource = dt;
            int count = dt->Rows->Count;
            lblResults->Text = count == 0 ? "No products found" : count + " product(s) found";
            lblResults->ForeColor = count == 0 ? Color::FromArgb(220, 38, 38)
                : Color::FromArgb(22, 163, 74);
        }

        void btnSearchName_Click(Object^ sender, EventArgs^ e) {
            String^ rawText = txtSearchName->Text == "e.g. Milk, Soap..." ? "" : txtSearchName->Text;
            String^ q = "%" + rawText->Trim() + "%";
            DataTable^ dt = SBS::Database::ExecuteQuery(
                "SELECT ProductID AS 'ID', Name, Category, Price AS 'Price (Rs.)', Stock "
                "FROM Products WHERE Name LIKE @q AND IsActive = 1",
                gcnew SqlParameter("@q", q));
            showResults(dt);
        }

        void btnSearchID_Click(Object^ sender, EventArgs^ e) {
            String^ rawText = txtSearchID->Text == "e.g. 3" ? "" : txtSearchID->Text;
            int id;
            if (!Int32::TryParse(rawText, id)) {
                MessageBox::Show("Please enter a valid numeric ID."); return;
            }
            DataTable^ dt = SBS::Database::ExecuteQuery(
                "SELECT ProductID AS 'ID', Name, Category, Price AS 'Price (Rs.)', Stock "
                "FROM Products WHERE ProductID = @id AND IsActive = 1",
                gcnew SqlParameter("@id", id));
            showResults(dt);
        }

        void btnClose_Click(Object^ sender, EventArgs^ e) { this->Close(); }
    };
}