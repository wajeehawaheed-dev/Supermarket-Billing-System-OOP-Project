#pragma once
#include "database.h"

namespace SUper {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;
    using namespace System::Data;

    public ref class SearchForm : public Form
    {
    public:
        int SelectedProductID;
        String^ SelectedName;
        double SelectedPrice;
        int SelectedStock;
        int SelectedQty;

        SearchForm(void)
        {
            InitializeComponent();
            ApplyModernStyle();

            SelectedProductID = -1;
            SelectedName = "";
            SelectedPrice = 0;
            SelectedStock = 0;
            SelectedQty = 1;
        }

    protected:
        ~SearchForm() { if (components) delete components; }

    private:
        static Color NAVY;
        static Color NAVY_HOVER;
        static Color GREEN_PRIMARY;
        static Color GREEN_HOVER;
        static Color BG_LIGHT;
        static Color BORDER_GREY;
        static Color TEXT_DARK;
        static Color TEXT_MUTED;

        static SearchForm()
        {
            NAVY = Color::FromArgb(30, 58, 138);
            NAVY_HOVER = Color::FromArgb(45, 75, 165);
            GREEN_PRIMARY = Color::FromArgb(34, 197, 94);
            GREEN_HOVER = Color::FromArgb(22, 163, 74);
            BG_LIGHT = Color::FromArgb(248, 250, 252);
            BORDER_GREY = Color::FromArgb(229, 231, 235);
            TEXT_DARK = Color::FromArgb(30, 41, 59);
            TEXT_MUTED = Color::FromArgb(100, 116, 139);
        }

        System::ComponentModel::Container^ components;

        // Original control names preserved
        TextBox^ txtSearch;
        Button^ btnSearch;
        DataGridView^ resultGrid;
        Label^ lblStatus;
        Label^ lblQty;
        TextBox^ txtQty;
        Button^ btnAdd;
        Button^ btnCancel;
        DataGridViewTextBoxColumn^ c1;
        DataGridViewTextBoxColumn^ c2;
        DataGridViewTextBoxColumn^ c3;
        DataGridViewTextBoxColumn^ c4;

        // New
        Panel^ pnlHeader;
        Panel^ pnlGridCard;
        Label^ lblTitle;
        Label^ lblSubtitle;
        Label^ btnTopClose;
        Panel^ pnlSearchLine;
        Panel^ pnlQtyLine;

        bool dragging;
        Point dragOffset;

#pragma region InitializeComponent
        void InitializeComponent(void)
        {
            this->txtSearch = gcnew TextBox();
            this->btnSearch = gcnew Button();
            this->resultGrid = gcnew DataGridView();
            this->lblStatus = gcnew Label();
            this->lblQty = gcnew Label();
            this->txtQty = gcnew TextBox();
            this->btnAdd = gcnew Button();
            this->btnCancel = gcnew Button();
            this->c1 = gcnew DataGridViewTextBoxColumn();
            this->c2 = gcnew DataGridViewTextBoxColumn();
            this->c3 = gcnew DataGridViewTextBoxColumn();
            this->c4 = gcnew DataGridViewTextBoxColumn();
            this->pnlHeader = gcnew Panel();
            this->pnlGridCard = gcnew Panel();
            this->lblTitle = gcnew Label();
            this->lblSubtitle = gcnew Label();
            this->btnTopClose = gcnew Label();
            this->pnlSearchLine = gcnew Panel();
            this->pnlQtyLine = gcnew Panel();

            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->resultGrid))->BeginInit();
            this->SuspendLayout();

            // ===== FORM =====
            this->Text = "Search Product";
            this->ClientSize = Drawing::Size(640, 600);
            this->MaximizeBox = false;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->StartPosition = FormStartPosition::CenterParent;
            this->BackColor = BG_LIGHT;
            this->DoubleBuffered = true;

            // ===== HEADER =====
            pnlHeader->Location = Point(0, 0);
            pnlHeader->Size = Drawing::Size(640, 75);
            pnlHeader->BackColor = Color::White;
            pnlHeader->Paint += gcnew PaintEventHandler(this, &SearchForm::pnlHeader_Paint);
            pnlHeader->MouseDown += gcnew MouseEventHandler(this, &SearchForm::Form_MouseDown);
            pnlHeader->MouseMove += gcnew MouseEventHandler(this, &SearchForm::Form_MouseMove);
            pnlHeader->MouseUp += gcnew MouseEventHandler(this, &SearchForm::Form_MouseUp);

            lblTitle->Text = "Add Product to Cart";
            lblTitle->Font = gcnew Drawing::Font("Segoe UI", 16, FontStyle::Bold);
            lblTitle->ForeColor = TEXT_DARK;
            lblTitle->BackColor = Color::Transparent;
            lblTitle->Location = Point(25, 18);
            lblTitle->AutoSize = true;

            lblSubtitle->Text = "Search by product name and choose a quantity";
            lblSubtitle->Font = gcnew Drawing::Font("Segoe UI", 9);
            lblSubtitle->ForeColor = TEXT_MUTED;
            lblSubtitle->BackColor = Color::Transparent;
            lblSubtitle->Location = Point(27, 47);
            lblSubtitle->AutoSize = true;

            btnTopClose->Text = L"\u2715";
            btnTopClose->Font = gcnew Drawing::Font("Segoe UI", 12, FontStyle::Bold);
            btnTopClose->ForeColor = TEXT_MUTED;
            btnTopClose->BackColor = Color::Transparent;
            btnTopClose->Location = Point(590, 20);
            btnTopClose->Size = Drawing::Size(35, 30);
            btnTopClose->TextAlign = ContentAlignment::MiddleCenter;
            btnTopClose->Cursor = Cursors::Hand;
            btnTopClose->Click += gcnew EventHandler(this, &SearchForm::btnCancel_Click);
            btnTopClose->MouseEnter += gcnew EventHandler(this, &SearchForm::btnTopClose_MouseEnter);
            btnTopClose->MouseLeave += gcnew EventHandler(this, &SearchForm::btnTopClose_MouseLeave);

            pnlHeader->Controls->Add(lblTitle);
            pnlHeader->Controls->Add(lblSubtitle);
            pnlHeader->Controls->Add(btnTopClose);

            // ===== SEARCH BAR =====
            txtSearch->BorderStyle = BorderStyle::None;
            txtSearch->Font = gcnew Drawing::Font("Segoe UI", 12);
            txtSearch->ForeColor = TEXT_MUTED;
            txtSearch->Location = Point(25, 100);
            txtSearch->Size = Drawing::Size(450, 24);
            txtSearch->Text = L"\U0001F50D  Type product name...";
            txtSearch->Enter += gcnew EventHandler(this, &SearchForm::txtSearch_Enter);
            txtSearch->Leave += gcnew EventHandler(this, &SearchForm::txtSearch_Leave);

            pnlSearchLine->Location = Point(25, 130);
            pnlSearchLine->Size = Drawing::Size(450, 2);
            pnlSearchLine->BackColor = BORDER_GREY;

            btnSearch->Location = Point(490, 96);
            btnSearch->Size = Drawing::Size(125, 38);
            btnSearch->Text = "Search";
            btnSearch->Font = gcnew Drawing::Font("Segoe UI", 9.5F, FontStyle::Bold);
            btnSearch->BackColor = NAVY;
            btnSearch->ForeColor = Color::White;
            btnSearch->FlatStyle = FlatStyle::Flat;
            btnSearch->FlatAppearance->BorderSize = 0;
            btnSearch->Cursor = Cursors::Hand;
            btnSearch->Click += gcnew EventHandler(this, &SearchForm::btnSearch_Click);
            btnSearch->MouseEnter += gcnew EventHandler(this, &SearchForm::btnSearch_MouseEnter);
            btnSearch->MouseLeave += gcnew EventHandler(this, &SearchForm::btnSearch_MouseLeave);

            // ===== STATUS =====
            lblStatus->Location = Point(27, 145);
            lblStatus->Size = Drawing::Size(580, 22);
            lblStatus->Text = L"\u2139  Type a name and click Search";
            lblStatus->Font = gcnew Drawing::Font("Segoe UI", 9);
            lblStatus->ForeColor = TEXT_MUTED;

            // ===== GRID CARD =====
            pnlGridCard->Location = Point(20, 175);
            pnlGridCard->Size = Drawing::Size(600, 290);
            pnlGridCard->BackColor = Color::White;
            pnlGridCard->Padding = System::Windows::Forms::Padding(1);
            pnlGridCard->Paint += gcnew PaintEventHandler(this, &SearchForm::pnlCard_Paint);

            resultGrid->Dock = DockStyle::Fill;
            resultGrid->BackgroundColor = Color::White;
            resultGrid->BorderStyle = BorderStyle::None;
            resultGrid->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
            resultGrid->GridColor = BORDER_GREY;
            resultGrid->RowHeadersVisible = false;
            resultGrid->EnableHeadersVisualStyles = false;
            resultGrid->ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle::None;
            resultGrid->ColumnHeadersHeight = 42;
            resultGrid->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
            resultGrid->RowTemplate->Height = 36;
            resultGrid->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            resultGrid->MultiSelect = false;
            resultGrid->ReadOnly = true;
            resultGrid->AllowUserToAddRows = false;
            resultGrid->AllowUserToResizeRows = false;

            DataGridViewCellStyle^ hs = gcnew DataGridViewCellStyle();
            hs->BackColor = NAVY;
            hs->ForeColor = Color::White;
            hs->Font = gcnew Drawing::Font("Segoe UI", 9.5F, FontStyle::Bold);
            hs->Alignment = DataGridViewContentAlignment::MiddleLeft;
            hs->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
            hs->SelectionBackColor = NAVY;
            hs->SelectionForeColor = Color::White;
            resultGrid->ColumnHeadersDefaultCellStyle = hs;

            DataGridViewCellStyle^ cs = gcnew DataGridViewCellStyle();
            cs->BackColor = Color::White;
            cs->ForeColor = TEXT_DARK;
            cs->Font = gcnew Drawing::Font("Segoe UI", 9.5F);
            cs->Alignment = DataGridViewContentAlignment::MiddleLeft;
            cs->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
            cs->SelectionBackColor = Color::FromArgb(219, 234, 254);
            cs->SelectionForeColor = TEXT_DARK;
            resultGrid->DefaultCellStyle = cs;

            DataGridViewCellStyle^ as_ = gcnew DataGridViewCellStyle();
            as_->BackColor = BG_LIGHT;
            as_->ForeColor = TEXT_DARK;
            as_->Font = gcnew Drawing::Font("Segoe UI", 9.5F);
            as_->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
            as_->SelectionBackColor = Color::FromArgb(219, 234, 254);
            as_->SelectionForeColor = TEXT_DARK;
            resultGrid->AlternatingRowsDefaultCellStyle = as_;

            // ===== COLUMNS =====
            c1->HeaderText = "ID";    c1->Name = "rID";    c1->Width = 60;
            c1->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;
            c1->DefaultCellStyle->Font = gcnew Drawing::Font("Segoe UI", 9.5F, FontStyle::Bold);

            c2->HeaderText = "Product Name";   c2->Name = "rName";
            c2->AutoSizeMode = DataGridViewAutoSizeColumnMode::Fill;

            c3->HeaderText = "Price";  c3->Name = "rPrice";  c3->Width = 110;
            c3->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleRight;
            c3->DefaultCellStyle->Font = gcnew Drawing::Font("Segoe UI", 9.5F, FontStyle::Bold);

            c4->HeaderText = "Stock";  c4->Name = "rStock";  c4->Width = 90;
            c4->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;

            resultGrid->Columns->AddRange(gcnew cli::array<DataGridViewColumn^> { c1, c2, c3, c4 });

            pnlGridCard->Controls->Add(resultGrid);

            // ===== QUANTITY =====
            lblQty->Text = "QUANTITY";
            lblQty->Font = gcnew Drawing::Font("Segoe UI", 8.5F, FontStyle::Bold);
            lblQty->ForeColor = TEXT_MUTED;
            lblQty->Location = Point(27, 480);
            lblQty->AutoSize = true;

            txtQty->BorderStyle = BorderStyle::None;
            txtQty->Font = gcnew Drawing::Font("Segoe UI", 14, FontStyle::Bold);
            txtQty->ForeColor = TEXT_DARK;
            txtQty->Location = Point(27, 502);
            txtQty->Size = Drawing::Size(180, 28);
            txtQty->Text = "1";
            txtQty->TextAlign = HorizontalAlignment::Center;
            txtQty->Click += gcnew EventHandler(this, &SearchForm::txtQty_Click);

            pnlQtyLine->Location = Point(27, 535);
            pnlQtyLine->Size = Drawing::Size(180, 2);
            pnlQtyLine->BackColor = BORDER_GREY;

            // ===== BUTTONS =====
            btnAdd->Text = L"\u2795  Add to Cart  (F4)";
            btnAdd->Font = gcnew Drawing::Font("Segoe UI", 10, FontStyle::Bold);
            btnAdd->Location = Point(370, 490);
            btnAdd->Size = Drawing::Size(250, 50);
            btnAdd->BackColor = GREEN_PRIMARY;
            btnAdd->ForeColor = Color::White;
            btnAdd->FlatStyle = FlatStyle::Flat;
            btnAdd->FlatAppearance->BorderSize = 0;
            btnAdd->Cursor = Cursors::Hand;
            btnAdd->Click += gcnew EventHandler(this, &SearchForm::btnAdd_Click);
            btnAdd->MouseEnter += gcnew EventHandler(this, &SearchForm::btnAdd_MouseEnter);
            btnAdd->MouseLeave += gcnew EventHandler(this, &SearchForm::btnAdd_MouseLeave);

            btnCancel->Text = "Cancel  (Esc)";
            btnCancel->Font = gcnew Drawing::Font("Segoe UI", 10);
            btnCancel->Location = Point(240, 490);
            btnCancel->Size = Drawing::Size(115, 50);
            btnCancel->BackColor = Color::White;
            btnCancel->ForeColor = TEXT_DARK;
            btnCancel->FlatStyle = FlatStyle::Flat;
            btnCancel->FlatAppearance->BorderSize = 1;
            btnCancel->FlatAppearance->BorderColor = BORDER_GREY;
            btnCancel->Cursor = Cursors::Hand;
            btnCancel->Click += gcnew EventHandler(this, &SearchForm::btnCancel_Click);
            btnCancel->MouseEnter += gcnew EventHandler(this, &SearchForm::btnCancel_MouseEnter);
            btnCancel->MouseLeave += gcnew EventHandler(this, &SearchForm::btnCancel_MouseLeave);

            // ===== ADD CONTROLS =====
            this->Controls->Add(pnlHeader);
            this->Controls->Add(txtSearch);
            this->Controls->Add(pnlSearchLine);
            this->Controls->Add(btnSearch);
            this->Controls->Add(lblStatus);
            this->Controls->Add(pnlGridCard);
            this->Controls->Add(lblQty);
            this->Controls->Add(txtQty);
            this->Controls->Add(pnlQtyLine);
            this->Controls->Add(btnAdd);
            this->Controls->Add(btnCancel);

            this->KeyPreview = true;
            this->KeyDown += gcnew KeyEventHandler(this, &SearchForm::SearchForm_KeyDown);
            this->MouseDown += gcnew MouseEventHandler(this, &SearchForm::Form_MouseDown);
            this->MouseMove += gcnew MouseEventHandler(this, &SearchForm::Form_MouseMove);
            this->MouseUp += gcnew MouseEventHandler(this, &SearchForm::Form_MouseUp);
            this->Paint += gcnew PaintEventHandler(this, &SearchForm::Form_Paint);
            this->AcceptButton = btnSearch;

            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->resultGrid))->EndInit();
            this->ResumeLayout(false);
        }
#pragma endregion

        // ===== STYLE HELPERS =====
        void ApplyModernStyle() {
            RoundControl(btnSearch, 6);
            RoundControl(btnAdd, 8);
            RoundControl(btnCancel, 6);
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

        // ===== PAINT =====
        System::Void Form_Paint(Object^ sender, PaintEventArgs^ e) {
            Pen^ pen = gcnew Pen(BORDER_GREY, 1);
            e->Graphics->DrawRectangle(pen, 0, 0, this->Width - 1, this->Height - 1);
        }
        System::Void pnlHeader_Paint(Object^ sender, PaintEventArgs^ e) {
            Pen^ pen = gcnew Pen(BORDER_GREY, 1);
            e->Graphics->DrawLine(pen, 0, pnlHeader->Height - 1, pnlHeader->Width, pnlHeader->Height - 1);
        }
        System::Void pnlCard_Paint(Object^ sender, PaintEventArgs^ e) {
            Panel^ p = (Panel^)sender;
            Pen^ pen = gcnew Pen(BORDER_GREY, 1);
            e->Graphics->DrawRectangle(pen, 0, 0, p->Width - 1, p->Height - 1);
        }

        // ===== DRAG =====
        System::Void Form_MouseDown(Object^ s, MouseEventArgs^ e) {
            if (e->Button == System::Windows::Forms::MouseButtons::Left) {
                dragging = true;
                dragOffset = Point(
                    System::Windows::Forms::Cursor::Position.X - this->Location.X,
                    System::Windows::Forms::Cursor::Position.Y - this->Location.Y);
            }
        }
        System::Void Form_MouseMove(Object^ s, MouseEventArgs^ e) {
            if (dragging) {
                this->Location = Point(
                    System::Windows::Forms::Cursor::Position.X - dragOffset.X,
                    System::Windows::Forms::Cursor::Position.Y - dragOffset.Y);
            }
        }
        System::Void Form_MouseUp(Object^ s, MouseEventArgs^ e) { dragging = false; }

        // ===== HOVER =====
        System::Void btnTopClose_MouseEnter(Object^ s, EventArgs^ e) {
            btnTopClose->BackColor = Color::FromArgb(239, 68, 68);
            btnTopClose->ForeColor = Color::White;
        }
        System::Void btnTopClose_MouseLeave(Object^ s, EventArgs^ e) {
            btnTopClose->BackColor = Color::Transparent;
            btnTopClose->ForeColor = TEXT_MUTED;
        }
        System::Void btnSearch_MouseEnter(Object^ s, EventArgs^ e) { btnSearch->BackColor = NAVY_HOVER; }
        System::Void btnSearch_MouseLeave(Object^ s, EventArgs^ e) { btnSearch->BackColor = NAVY; }
        System::Void btnAdd_MouseEnter(Object^ s, EventArgs^ e) { btnAdd->BackColor = GREEN_HOVER; }
        System::Void btnAdd_MouseLeave(Object^ s, EventArgs^ e) { btnAdd->BackColor = GREEN_PRIMARY; }
        System::Void btnCancel_MouseEnter(Object^ s, EventArgs^ e) { btnCancel->BackColor = BG_LIGHT; }
        System::Void btnCancel_MouseLeave(Object^ s, EventArgs^ e) { btnCancel->BackColor = Color::White; }

        // ===== Placeholder handlers =====
        System::Void txtSearch_Enter(Object^ sender, EventArgs^ e) {
            if (txtSearch->Text == L"\U0001F50D  Type product name...") {
                txtSearch->Text = "";
                txtSearch->ForeColor = TEXT_DARK;
            }
            pnlSearchLine->BackColor = NAVY;
        }
        System::Void txtSearch_Leave(Object^ sender, EventArgs^ e) {
            if (String::IsNullOrWhiteSpace(txtSearch->Text)) {
                txtSearch->Text = L"\U0001F50D  Type product name...";
                txtSearch->ForeColor = TEXT_MUTED;
            }
            pnlSearchLine->BackColor = BORDER_GREY;
        }

        // ===== ORIGINAL HANDLERS (preserved logic) =====
        System::Void btnSearch_Click(Object^ sender, EventArgs^ e) {
            String^ rawText = (txtSearch->Text == L"\U0001F50D  Type product name...") ? "" : txtSearch->Text;

            if (rawText->Trim() == "") {
                lblStatus->Text = L"\u26A0  Enter a valid product name!";
                lblStatus->ForeColor = Color::FromArgb(220, 38, 38);
                return;
            }

            resultGrid->Rows->Clear();

            String^ sql = "SELECT ProductID, Name, Price, Stock FROM Products WHERE Name LIKE @q AND IsActive = 1 ORDER BY Name";
            DataTable^ results = SBS::Database::ExecuteQuery(sql,
                gcnew System::Data::SqlClient::SqlParameter("@q", "%" + rawText->Trim() + "%"));

            if (results == nullptr || results->Rows->Count == 0) {
                lblStatus->Text = L"\u2717  No products found";
                lblStatus->ForeColor = Color::FromArgb(220, 38, 38);
                return;
            }

            for (int i = 0; i < results->Rows->Count; i++) {
                DataRow^ row = results->Rows[i];
                resultGrid->Rows->Add(
                    row["ProductID"]->ToString(),
                    row["Name"]->ToString(),
                    "Rs " + Convert::ToDouble(row["Price"]).ToString("N2"),
                    row["Stock"]->ToString()
                );
            }

            lblStatus->Text = L"\u2713  Found " + results->Rows->Count + " result(s)";
            lblStatus->ForeColor = Color::FromArgb(22, 163, 74);
            resultGrid->Rows[0]->Selected = true;
        }

        System::Void btnAdd_Click(Object^ sender, EventArgs^ e) {
            if (resultGrid->SelectedRows->Count == 0) {
                MessageBox::Show("Select a product first!");
                return;
            }

            int qty;
            if (!Int32::TryParse(txtQty->Text, qty) || qty <= 0) {
                MessageBox::Show("Invalid quantity!");
                return;
            }

            int stock = Int32::Parse(resultGrid->SelectedRows[0]->Cells["rStock"]->Value->ToString()->Trim());
            if (qty > stock) {
                MessageBox::Show("Not enough stock!");
                return;
            }

            SelectedProductID = Convert::ToInt32(resultGrid->SelectedRows[0]->Cells["rID"]->Value);
            SelectedName = resultGrid->SelectedRows[0]->Cells["rName"]->Value->ToString();
            SelectedPrice = Convert::ToDouble(
                resultGrid->SelectedRows[0]->Cells["rPrice"]->Value->ToString()->Replace("Rs ", "")->Replace(",", "")
            );
            SelectedQty = qty;

            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
        }

        System::Void btnCancel_Click(Object^ sender, EventArgs^ e) {
            this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
            this->Close();
        }

        System::Void SearchForm_KeyDown(Object^ sender, KeyEventArgs^ e) {
            if (e->KeyCode == Keys::Escape) btnCancel->PerformClick();
            if (e->KeyCode == Keys::F4) btnAdd->PerformClick();
        }
        System::Void txtQty_Click(Object^ sender, EventArgs^ e) {
            txtQty->Focus();
            txtQty->SelectAll();
        }
    };
}