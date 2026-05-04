#pragma once
#include "product.h"
#include "database.h"

namespace SUper {
    ref class AddProductForm;
    ref class EditProductForm;
    ref class SearchProductForm;
}

namespace SUper {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    public ref class ProductsForm : public System::Windows::Forms::Form
    {
    private:
        static Color NAVY;
        static Color NAVY_HOVER;
        static Color GREEN_BTN;
        static Color GREEN_BTN_HOVER;
        static Color RED_DANGER;
        static Color RED_DANGER_HOVER;
        static Color WARN_BG;
        static Color WARN_BORDER;
        static Color WARN_TEXT;
        static Color LOW_STOCK_TINT;
        static Color BG_LIGHT;
        static Color BORDER_GREY;
        static Color TEXT_DARK;
        static Color TEXT_MUTED;

        static ProductsForm() {
            NAVY = Color::FromArgb(30, 58, 138);
            NAVY_HOVER = Color::FromArgb(45, 75, 165);
            GREEN_BTN = Color::FromArgb(34, 197, 94);
            GREEN_BTN_HOVER = Color::FromArgb(22, 163, 74);
            RED_DANGER = Color::FromArgb(220, 38, 38);
            RED_DANGER_HOVER = Color::FromArgb(185, 28, 28);
            WARN_BG = Color::FromArgb(254, 243, 199);
            WARN_BORDER = Color::FromArgb(252, 211, 77);
            WARN_TEXT = Color::FromArgb(146, 64, 14);
            LOW_STOCK_TINT = Color::FromArgb(254, 243, 199);
            BG_LIGHT = Color::FromArgb(248, 250, 252);
            BORDER_GREY = Color::FromArgb(229, 231, 235);
            TEXT_DARK = Color::FromArgb(30, 41, 59);
            TEXT_MUTED = Color::FromArgb(100, 116, 139);
        }

        ProductManager^ pm;
        DataTable^ dtProducts;

        // ===== Original control names preserved =====
        System::Windows::Forms::DataGridView^ dgvProducts;
        System::Windows::Forms::Button^ btnAdd;
        System::Windows::Forms::Button^ btnEdit;
        System::Windows::Forms::Button^ btnSearch;
        System::Windows::Forms::Button^ btnDelete;
        System::Windows::Forms::Button^ btnRefresh;
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Label^ lblStockAlert;
        System::Windows::Forms::Panel^ pnlBottom;

        // ===== New layout controls =====
        System::Windows::Forms::Panel^ pnlHeader;
        System::Windows::Forms::Panel^ pnlWarning;
        System::Windows::Forms::Panel^ pnlGrid;
        System::Windows::Forms::Label^ lblSubtitle;
        System::Windows::Forms::Label^ btnTopClose;
        System::Windows::Forms::Button^ btnClose;

        bool dragging;
        Point dragOffset;

    public:
        ProductsForm(void) {
            pm = gcnew ProductManager();
            dtProducts = nullptr;
            InitializeComponent();
            ApplyModernStyle();
            loadGrid();
        }

    protected:
        ~ProductsForm() {}

    private:
        void InitializeComponent(void) {
            this->Text = L"Product Management - ValueMart";
            this->ClientSize = System::Drawing::Size(1100, 680);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->BackColor = BG_LIGHT;
            this->DoubleBuffered = true;

            // ===== HEADER =====
            pnlHeader = gcnew Panel();
            pnlHeader->Location = Point(0, 0);
            pnlHeader->Size = System::Drawing::Size(1100, 80);
            pnlHeader->BackColor = Color::White;
            pnlHeader->Paint += gcnew PaintEventHandler(this, &ProductsForm::pnlHeader_Paint);
            pnlHeader->MouseDown += gcnew MouseEventHandler(this, &ProductsForm::Form_MouseDown);
            pnlHeader->MouseMove += gcnew MouseEventHandler(this, &ProductsForm::Form_MouseMove);
            pnlHeader->MouseUp += gcnew MouseEventHandler(this, &ProductsForm::Form_MouseUp);

            lblTitle = gcnew Label();
            lblTitle->Text = "Products";
            lblTitle->Font = gcnew System::Drawing::Font("Segoe UI", 18.0F, FontStyle::Bold);
            lblTitle->ForeColor = TEXT_DARK;
            lblTitle->BackColor = Color::Transparent;
            lblTitle->Location = Point(30, 18);
            lblTitle->AutoSize = true;

            lblSubtitle = gcnew Label();
            lblSubtitle->Text = "Manage your product catalog and inventory";
            lblSubtitle->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F);
            lblSubtitle->ForeColor = TEXT_MUTED;
            lblSubtitle->BackColor = Color::Transparent;
            lblSubtitle->Location = Point(32, 50);
            lblSubtitle->AutoSize = true;

            btnTopClose = gcnew Label();
            btnTopClose->Text = L"\u2715";
            btnTopClose->Font = gcnew System::Drawing::Font("Segoe UI", 12.0F, FontStyle::Bold);
            btnTopClose->ForeColor = TEXT_MUTED;
            btnTopClose->BackColor = Color::Transparent;
            btnTopClose->Location = Point(1048, 22);
            btnTopClose->Size = System::Drawing::Size(35, 35);
            btnTopClose->TextAlign = ContentAlignment::MiddleCenter;
            btnTopClose->Cursor = Cursors::Hand;
            btnTopClose->Click += gcnew EventHandler(this, &ProductsForm::btnTopClose_Click);
            btnTopClose->MouseEnter += gcnew EventHandler(this, &ProductsForm::btnTopClose_MouseEnter);
            btnTopClose->MouseLeave += gcnew EventHandler(this, &ProductsForm::btnTopClose_MouseLeave);

            pnlHeader->Controls->Add(lblTitle);
            pnlHeader->Controls->Add(lblSubtitle);
            pnlHeader->Controls->Add(btnTopClose);

            // ===== LOW STOCK WARNING BANNER =====
            pnlWarning = gcnew Panel();
            pnlWarning->Location = Point(20, 95);
            pnlWarning->Size = System::Drawing::Size(1060, 44);
            pnlWarning->BackColor = WARN_BG;
            pnlWarning->Visible = false;
            pnlWarning->Paint += gcnew PaintEventHandler(this, &ProductsForm::pnlWarning_Paint);

            lblStockAlert = gcnew Label();
            lblStockAlert->Text = L"\u26A0  Low stock detected — some products are running low";
            lblStockAlert->Font = gcnew System::Drawing::Font("Segoe UI", 10.0F, FontStyle::Bold);
            lblStockAlert->ForeColor = WARN_TEXT;
            lblStockAlert->BackColor = Color::Transparent;
            lblStockAlert->Location = Point(20, 12);
            lblStockAlert->AutoSize = true;
            pnlWarning->Controls->Add(lblStockAlert);

            // ===== GRID CARD =====
            pnlGrid = gcnew Panel();
            pnlGrid->Location = Point(20, 150);
            pnlGrid->Size = System::Drawing::Size(1060, 410);
            pnlGrid->BackColor = Color::White;
            pnlGrid->Padding = System::Windows::Forms::Padding(1);
            pnlGrid->Paint += gcnew PaintEventHandler(this, &ProductsForm::pnlCard_Paint);

            dgvProducts = gcnew DataGridView();
            StyleGrid(dgvProducts);
            dgvProducts->DataBindingComplete +=
                gcnew DataGridViewBindingCompleteEventHandler(this, &ProductsForm::dgv_DataBindingComplete);
            pnlGrid->Controls->Add(dgvProducts);

            // ===== BOTTOM ACTION BAR =====
            pnlBottom = gcnew Panel();
            pnlBottom->Location = Point(20, 580);
            pnlBottom->Size = System::Drawing::Size(1060, 70);
            pnlBottom->BackColor = Color::White;
            pnlBottom->Paint += gcnew PaintEventHandler(this, &ProductsForm::pnlCard_Paint);

            btnAdd = gcnew Button();
            ConfigurePrimaryButton(btnAdd, L"+  Add Product", Point(20, 16), 150, GREEN_BTN, GREEN_BTN_HOVER);
            btnAdd->Click += gcnew EventHandler(this, &ProductsForm::btnAdd_Click);

            btnEdit = gcnew Button();
            ConfigureSecondaryButton(btnEdit, "Edit", Point(185, 16), 100);
            btnEdit->Click += gcnew EventHandler(this, &ProductsForm::btnEdit_Click);

            btnDelete = gcnew Button();
            ConfigureDangerButton(btnDelete, "Delete", Point(295, 16), 100);
            btnDelete->Click += gcnew EventHandler(this, &ProductsForm::btnDelete_Click);

            btnSearch = gcnew Button();
            ConfigureSecondaryButton(btnSearch, L"\U0001F50D  Search", Point(405, 16), 110);
            btnSearch->Click += gcnew EventHandler(this, &ProductsForm::btnSearch_Click);

            btnRefresh = gcnew Button();
            ConfigureSecondaryButton(btnRefresh, L"\u27F3  Refresh", Point(525, 16), 110);
            btnRefresh->Click += gcnew EventHandler(this, &ProductsForm::btnRefresh_Click);

            btnClose = gcnew Button();
            ConfigureSecondaryButton(btnClose, "Close", Point(940, 16), 100);
            btnClose->Click += gcnew EventHandler(this, &ProductsForm::btnTopClose_Click);

            pnlBottom->Controls->Add(btnAdd);
            pnlBottom->Controls->Add(btnEdit);
            pnlBottom->Controls->Add(btnDelete);
            pnlBottom->Controls->Add(btnSearch);
            pnlBottom->Controls->Add(btnRefresh);
            pnlBottom->Controls->Add(btnClose);

            // ===== FORM =====
            this->Controls->Add(pnlHeader);
            this->Controls->Add(pnlWarning);
            this->Controls->Add(pnlGrid);
            this->Controls->Add(pnlBottom);
            this->MouseDown += gcnew MouseEventHandler(this, &ProductsForm::Form_MouseDown);
            this->MouseMove += gcnew MouseEventHandler(this, &ProductsForm::Form_MouseMove);
            this->MouseUp += gcnew MouseEventHandler(this, &ProductsForm::Form_MouseUp);
        }

        // ===== STYLE HELPERS =====
        void ConfigurePrimaryButton(Button^ btn, String^ text, Point loc, int width, Color bg, Color hover) {
            btn->Text = text;
            btn->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F, FontStyle::Bold);
            btn->BackColor = bg;
            btn->ForeColor = Color::White;
            btn->FlatStyle = FlatStyle::Flat;
            btn->FlatAppearance->BorderSize = 0;
            btn->Location = loc;
            btn->Size = System::Drawing::Size(width, 38);
            btn->Cursor = Cursors::Hand;
            btn->Tag = bg;  // store base color
            btn->MouseEnter += gcnew EventHandler(this, &ProductsForm::PrimaryBtn_MouseEnter);
            btn->MouseLeave += gcnew EventHandler(this, &ProductsForm::PrimaryBtn_MouseLeave);
            // Save hover color in a way we can retrieve — use a Hashtable lookup keyed by the button
            hoverMap[btn] = hover;
        }

        void ConfigureSecondaryButton(Button^ btn, String^ text, Point loc, int width) {
            btn->Text = text;
            btn->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F, FontStyle::Bold);
            btn->BackColor = Color::White;
            btn->ForeColor = TEXT_DARK;
            btn->FlatStyle = FlatStyle::Flat;
            btn->FlatAppearance->BorderSize = 1;
            btn->FlatAppearance->BorderColor = BORDER_GREY;
            btn->Location = loc;
            btn->Size = System::Drawing::Size(width, 38);
            btn->Cursor = Cursors::Hand;
            btn->MouseEnter += gcnew EventHandler(this, &ProductsForm::SecondaryBtn_MouseEnter);
            btn->MouseLeave += gcnew EventHandler(this, &ProductsForm::SecondaryBtn_MouseLeave);
        }

        void ConfigureDangerButton(Button^ btn, String^ text, Point loc, int width) {
            btn->Text = text;
            btn->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F, FontStyle::Bold);
            btn->BackColor = RED_DANGER;
            btn->ForeColor = Color::White;
            btn->FlatStyle = FlatStyle::Flat;
            btn->FlatAppearance->BorderSize = 0;
            btn->Location = loc;
            btn->Size = System::Drawing::Size(width, 38);
            btn->Cursor = Cursors::Hand;
            btn->MouseEnter += gcnew EventHandler(this, &ProductsForm::DangerBtn_MouseEnter);
            btn->MouseLeave += gcnew EventHandler(this, &ProductsForm::DangerBtn_MouseLeave);
        }

        // map button -> hover color (since C++/CLI can't easily attach extra fields per button)
        System::Collections::Hashtable^ hoverMap = gcnew System::Collections::Hashtable();

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
            grid->ColumnHeadersHeight = 45;
            grid->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
            grid->RowTemplate->Height = 38;
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
        }

        void ApplyModernStyle() {
            RoundControl(btnAdd, 6);
            RoundControl(btnEdit, 6);
            RoundControl(btnDelete, 6);
            RoundControl(btnSearch, 6);
            RoundControl(btnRefresh, 6);
            RoundControl(btnClose, 6);
            RoundControl(pnlGrid, 8);
            RoundControl(pnlBottom, 8);
            RoundControl(pnlWarning, 6);
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

        // ===== PAINT =====
        void pnlHeader_Paint(Object^ sender, PaintEventArgs^ e) {
            Pen^ pen = gcnew Pen(BORDER_GREY, 1);
            e->Graphics->DrawLine(pen, 0, pnlHeader->Height - 1, pnlHeader->Width, pnlHeader->Height - 1);
        }
        void pnlCard_Paint(Object^ sender, PaintEventArgs^ e) {
            Panel^ p = (Panel^)sender;
            Pen^ pen = gcnew Pen(BORDER_GREY, 1);
            e->Graphics->DrawRectangle(pen, 0, 0, p->Width - 1, p->Height - 1);
        }
        void pnlWarning_Paint(Object^ sender, PaintEventArgs^ e) {
            Pen^ pen = gcnew Pen(WARN_BORDER, 1);
            e->Graphics->DrawRectangle(pen, 0, 0, pnlWarning->Width - 1, pnlWarning->Height - 1);
            // amber accent strip on left
            SolidBrush^ accent = gcnew SolidBrush(WARN_BORDER);
            e->Graphics->FillRectangle(accent, 0, 0, 4, pnlWarning->Height);
        }

        // ===== DRAG =====
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

        // ===== HOVER =====
        void btnTopClose_Click(Object^ s, EventArgs^ e) { this->Close(); }
        void btnTopClose_MouseEnter(Object^ s, EventArgs^ e) {
            btnTopClose->BackColor = RED_DANGER;
            btnTopClose->ForeColor = Color::White;
        }
        void btnTopClose_MouseLeave(Object^ s, EventArgs^ e) {
            btnTopClose->BackColor = Color::Transparent;
            btnTopClose->ForeColor = TEXT_MUTED;
        }
        void PrimaryBtn_MouseEnter(Object^ s, EventArgs^ e) {
            Button^ b = (Button^)s;
            b->BackColor = (Color)hoverMap[b];
        }
        void PrimaryBtn_MouseLeave(Object^ s, EventArgs^ e) {
            Button^ b = (Button^)s;
            b->BackColor = (Color)b->Tag;
        }
        void SecondaryBtn_MouseEnter(Object^ s, EventArgs^ e) {
            ((Button^)s)->BackColor = BG_LIGHT;
        }
        void SecondaryBtn_MouseLeave(Object^ s, EventArgs^ e) {
            ((Button^)s)->BackColor = Color::White;
        }
        void DangerBtn_MouseEnter(Object^ s, EventArgs^ e) {
            ((Button^)s)->BackColor = RED_DANGER_HOVER;
        }
        void DangerBtn_MouseLeave(Object^ s, EventArgs^ e) {
            ((Button^)s)->BackColor = RED_DANGER;
        }

        // ===== COLUMN FORMATTING =====
        void dgv_DataBindingComplete(Object^ sender, DataGridViewBindingCompleteEventArgs^ e) {
            if (dgvProducts->Columns->Contains("ID")) {
                dgvProducts->Columns["ID"]->DefaultCellStyle->Alignment =
                    DataGridViewContentAlignment::MiddleCenter;
                dgvProducts->Columns["ID"]->DefaultCellStyle->Font =
                    gcnew System::Drawing::Font("Segoe UI", 9.5F, FontStyle::Bold);
                dgvProducts->Columns["ID"]->FillWeight = 50;
            }
            if (dgvProducts->Columns->Contains("Price")) {
                dgvProducts->Columns["Price"]->DefaultCellStyle->Format = "N2";
                dgvProducts->Columns["Price"]->DefaultCellStyle->Alignment =
                    DataGridViewContentAlignment::MiddleRight;
                dgvProducts->Columns["Price"]->HeaderText = "Price (Rs.)";
            }
            if (dgvProducts->Columns->Contains("Stock")) {
                dgvProducts->Columns["Stock"]->DefaultCellStyle->Alignment =
                    DataGridViewContentAlignment::MiddleCenter;
                dgvProducts->Columns["Stock"]->DefaultCellStyle->Font =
                    gcnew System::Drawing::Font("Segoe UI", 9.5F, FontStyle::Bold);
            }
        }

        // ===== ORIGINAL LOGIC PRESERVED =====
        void loadGrid() {
            bool lowStockFound = false;
            int lowStockCount = 0;
            try {
                dtProducts = SBS::Database::ExecuteQuery(
                    "SELECT ProductID AS 'ID', Name, Category, Price, Stock "
                    "FROM Products WHERE IsActive = 1");
                dgvProducts->DataSource = dtProducts;
                dgvProducts->Refresh();

                DataTableReader^ reader = dtProducts->CreateDataReader();
                while (reader->Read()) {
                    int stock = reader->GetInt32(4);
                    if (stock < 5) { lowStockFound = true; lowStockCount++; }
                }
                reader->Close();

                DataTableReader^ r2 = dtProducts->CreateDataReader();
                for each (DataGridViewRow ^ row in dgvProducts->Rows) {
                    if (!row->IsNewRow && r2->Read()) {
                        int stock = r2->GetInt32(4);
                        if (stock < 5) {
                            row->DefaultCellStyle->BackColor = LOW_STOCK_TINT;
                            row->DefaultCellStyle->ForeColor = WARN_TEXT;
                        }
                    }
                }
                r2->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading grid: " + ex->Message);
            }

            if (lowStockFound) {
                lblStockAlert->Text = L"\u26A0  " + lowStockCount + " product(s) running low on stock";
                pnlWarning->Visible = true;
            }
            else {
                pnlWarning->Visible = false;
            }
        }

        int getSelectedID() {
            int rowIndex = dgvProducts->CurrentCellAddress.Y;
            if (rowIndex < 0 || dtProducts == nullptr) return -1;
            DataTableReader^ r = dtProducts->CreateDataReader();
            int i = 0;
            int id = -1;
            while (r->Read()) {
                if (i == rowIndex) { id = r->GetInt32(0); break; }
                i++;
            }
            r->Close();
            return id;
        }

        // Implementations stay in ProductsForm.cpp — signatures unchanged
        void btnAdd_Click(Object^ sender, EventArgs^ e);
        void btnEdit_Click(Object^ sender, EventArgs^ e);
        void btnDelete_Click(Object^ sender, EventArgs^ e);
        void btnSearch_Click(Object^ sender, EventArgs^ e);
        void btnRefresh_Click(Object^ sender, EventArgs^ e);
    };
}