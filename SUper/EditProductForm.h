#define WIN32_LEAN_AND_MEAN
#pragma once
#include "database.h"
#include "product.h"
#include <msclr/marshal_cppstd.h>

namespace SUper {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Data::SqlClient;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    public ref class EditProductForm : public Form {
    private:
        static Color NAVY;
        static Color NAVY_HOVER;
        static Color GREEN_BTN;
        static Color GREEN_BTN_HOVER;
        static Color BG_LIGHT;
        static Color BORDER_GREY;
        static Color TEXT_DARK;
        static Color TEXT_MUTED;

        static EditProductForm() {
            NAVY = Color::FromArgb(30, 58, 138);
            NAVY_HOVER = Color::FromArgb(45, 75, 165);
            GREEN_BTN = Color::FromArgb(34, 197, 94);
            GREEN_BTN_HOVER = Color::FromArgb(22, 163, 74);
            BG_LIGHT = Color::FromArgb(248, 250, 252);
            BORDER_GREY = Color::FromArgb(220, 224, 230);
            TEXT_DARK = Color::FromArgb(30, 41, 59);
            TEXT_MUTED = Color::FromArgb(100, 116, 139);
        }

        int productID;
        ProductManager^ pm;
        TextBox^ txtName;
        TextBox^ txtCategory;
        TextBox^ txtPrice;
        TextBox^ txtRestockQty;
        Panel^ pnlNameLine;
        Panel^ pnlCategoryLine;
        Panel^ pnlPriceLine;
        Panel^ pnlRestockLine;
        Panel^ pnlRestockCard;
        Button^ btnSave;
        Button^ btnRestock;
        Button^ btnCancel;
        Label^ btnTopClose;

        bool dragging;
        Point dragOffset;

    public:
        EditProductForm(int id) {
            productID = id;
            pm = gcnew ProductManager();
            InitializeComponent();
            ApplyModernStyle();
            loadData();
        }
        ~EditProductForm() {}

    private:
        void InitializeComponent() {
            this->Text = "Edit Product";
            this->ClientSize = System::Drawing::Size(440, 620);
            this->StartPosition = FormStartPosition::CenterParent;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->BackColor = Color::White;
            this->DoubleBuffered = true;

            Label^ lblTitle = gcnew Label();
            lblTitle->Text = "Edit Product";
            lblTitle->Font = gcnew System::Drawing::Font("Segoe UI", 16.0F, FontStyle::Bold);
            lblTitle->ForeColor = TEXT_DARK;
            lblTitle->Location = Point(30, 25);
            lblTitle->AutoSize = true;

            Label^ lblSub = gcnew Label();
            lblSub->Text = "Product ID: " + productID;
            lblSub->Font = gcnew System::Drawing::Font("Segoe UI", 9.0F);
            lblSub->ForeColor = TEXT_MUTED;
            lblSub->Location = Point(32, 55);
            lblSub->AutoSize = true;

            btnTopClose = gcnew Label();
            btnTopClose->Text = L"\u2715";
            btnTopClose->Font = gcnew System::Drawing::Font("Segoe UI", 12.0F, FontStyle::Bold);
            btnTopClose->ForeColor = TEXT_MUTED;
            btnTopClose->Location = Point(390, 22);
            btnTopClose->Size = System::Drawing::Size(35, 30);
            btnTopClose->TextAlign = ContentAlignment::MiddleCenter;
            btnTopClose->Cursor = Cursors::Hand;
            btnTopClose->Click += gcnew EventHandler(this, &EditProductForm::btnCancel_Click);
            btnTopClose->MouseEnter += gcnew EventHandler(this, &EditProductForm::btnTopClose_MouseEnter);
            btnTopClose->MouseLeave += gcnew EventHandler(this, &EditProductForm::btnTopClose_MouseLeave);

            CreateField("PRODUCT NAME", 100, txtName, pnlNameLine);
            CreateField("CATEGORY", 170, txtCategory, pnlCategoryLine);
            CreateField("PRICE (RS.)", 240, txtPrice, pnlPriceLine);

            // ---- Restock card ----
            pnlRestockCard = gcnew Panel();
            pnlRestockCard->Location = Point(35, 320);
            pnlRestockCard->Size = System::Drawing::Size(370, 130);
            pnlRestockCard->BackColor = Color::FromArgb(240, 253, 244);
            pnlRestockCard->Paint += gcnew PaintEventHandler(this, &EditProductForm::pnlRestockCard_Paint);

            Label^ lblRestockTitle = gcnew Label();
            lblRestockTitle->Text = L"\u2795  RESTOCK";
            lblRestockTitle->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F, FontStyle::Bold);
            lblRestockTitle->ForeColor = GREEN_BTN_HOVER;
            lblRestockTitle->BackColor = Color::Transparent;
            lblRestockTitle->Location = Point(15, 12);
            lblRestockTitle->AutoSize = true;

            Label^ lblRestockHint = gcnew Label();
            lblRestockHint->Text = "Add quantity to current stock";
            lblRestockHint->Font = gcnew System::Drawing::Font("Segoe UI", 8.5F);
            lblRestockHint->ForeColor = TEXT_MUTED;
            lblRestockHint->BackColor = Color::Transparent;
            lblRestockHint->Location = Point(15, 32);
            lblRestockHint->AutoSize = true;

            txtRestockQty = gcnew TextBox();
            txtRestockQty->BorderStyle = BorderStyle::None;
            txtRestockQty->Font = gcnew System::Drawing::Font("Segoe UI", 11.0F);
            txtRestockQty->ForeColor = TEXT_DARK;
            txtRestockQty->Location = Point(15, 75);
            txtRestockQty->Size = System::Drawing::Size(130, 22);
            txtRestockQty->Text = "0";

            pnlRestockLine = gcnew Panel();
            pnlRestockLine->Location = Point(15, 102);
            pnlRestockLine->Size = System::Drawing::Size(130, 2);
            pnlRestockLine->BackColor = BORDER_GREY;

            btnRestock = gcnew Button();
            btnRestock->Text = "+ Restock";
            btnRestock->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F, FontStyle::Bold);
            btnRestock->BackColor = GREEN_BTN;
            btnRestock->ForeColor = Color::White;
            btnRestock->FlatStyle = FlatStyle::Flat;
            btnRestock->FlatAppearance->BorderSize = 0;
            btnRestock->Location = Point(240, 70);
            btnRestock->Size = System::Drawing::Size(115, 36);
            btnRestock->Cursor = Cursors::Hand;
            btnRestock->Click += gcnew EventHandler(this, &EditProductForm::btnRestock_Click);
            btnRestock->MouseEnter += gcnew EventHandler(this, &EditProductForm::btnRestock_MouseEnter);
            btnRestock->MouseLeave += gcnew EventHandler(this, &EditProductForm::btnRestock_MouseLeave);

            pnlRestockCard->Controls->Add(lblRestockTitle);
            pnlRestockCard->Controls->Add(lblRestockHint);
            pnlRestockCard->Controls->Add(txtRestockQty);
            pnlRestockCard->Controls->Add(pnlRestockLine);
            pnlRestockCard->Controls->Add(btnRestock);

            // Bottom buttons
            btnSave = gcnew Button();
            btnSave->Text = "Save Changes";
            btnSave->Font = gcnew System::Drawing::Font("Segoe UI", 10.0F, FontStyle::Bold);
            btnSave->BackColor = NAVY;
            btnSave->ForeColor = Color::White;
            btnSave->FlatStyle = FlatStyle::Flat;
            btnSave->FlatAppearance->BorderSize = 0;
            btnSave->Location = Point(215, 530);
            btnSave->Size = System::Drawing::Size(190, 44);
            btnSave->Cursor = Cursors::Hand;
            btnSave->Click += gcnew EventHandler(this, &EditProductForm::btnSave_Click);
            btnSave->MouseEnter += gcnew EventHandler(this, &EditProductForm::btnSave_MouseEnter);
            btnSave->MouseLeave += gcnew EventHandler(this, &EditProductForm::btnSave_MouseLeave);

            btnCancel = gcnew Button();
            btnCancel->Text = "Cancel";
            btnCancel->Font = gcnew System::Drawing::Font("Segoe UI", 10.0F);
            btnCancel->BackColor = Color::White;
            btnCancel->ForeColor = TEXT_DARK;
            btnCancel->FlatStyle = FlatStyle::Flat;
            btnCancel->FlatAppearance->BorderSize = 1;
            btnCancel->FlatAppearance->BorderColor = BORDER_GREY;
            btnCancel->Location = Point(35, 530);
            btnCancel->Size = System::Drawing::Size(160, 44);
            btnCancel->Cursor = Cursors::Hand;
            btnCancel->Click += gcnew EventHandler(this, &EditProductForm::btnCancel_Click);
            btnCancel->MouseEnter += gcnew EventHandler(this, &EditProductForm::btnCancel_MouseEnter);
            btnCancel->MouseLeave += gcnew EventHandler(this, &EditProductForm::btnCancel_MouseLeave);

            this->Controls->Add(lblTitle);
            this->Controls->Add(lblSub);
            this->Controls->Add(btnTopClose);
            this->Controls->Add(pnlRestockCard);
            this->Controls->Add(btnSave);
            this->Controls->Add(btnCancel);

            this->MouseDown += gcnew MouseEventHandler(this, &EditProductForm::Form_MouseDown);
            this->MouseMove += gcnew MouseEventHandler(this, &EditProductForm::Form_MouseMove);
            this->MouseUp += gcnew MouseEventHandler(this, &EditProductForm::Form_MouseUp);
            this->Paint += gcnew PaintEventHandler(this, &EditProductForm::Form_Paint);
        }

        void CreateField(String^ label, int y, TextBox^% tb, Panel^% line) {
            Label^ lbl = gcnew Label();
            lbl->Text = label;
            lbl->Font = gcnew System::Drawing::Font("Segoe UI", 8.5F, FontStyle::Bold);
            lbl->ForeColor = TEXT_MUTED;
            lbl->Location = Point(35, y);
            lbl->AutoSize = true;

            tb = gcnew TextBox();
            tb->BorderStyle = BorderStyle::None;
            tb->Font = gcnew System::Drawing::Font("Segoe UI", 11.0F);
            tb->ForeColor = TEXT_DARK;
            tb->Location = Point(35, y + 22);
            tb->Size = System::Drawing::Size(370, 22);
            tb->Enter += gcnew EventHandler(this, &EditProductForm::Field_Enter);
            tb->Leave += gcnew EventHandler(this, &EditProductForm::Field_Leave);

            line = gcnew Panel();
            line->Location = Point(35, y + 49);
            line->Size = System::Drawing::Size(370, 2);
            line->BackColor = BORDER_GREY;

            this->Controls->Add(lbl);
            this->Controls->Add(tb);
            this->Controls->Add(line);
        }

        void ApplyModernStyle() {
            RoundControl(btnSave, 6);
            RoundControl(btnCancel, 6);
            RoundControl(btnRestock, 6);
            RoundControl(pnlRestockCard, 8);
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

        void Form_Paint(Object^ sender, PaintEventArgs^ e) {
            Pen^ pen = gcnew Pen(BORDER_GREY, 1);
            e->Graphics->DrawRectangle(pen, 0, 0, this->Width - 1, this->Height - 1);
        }
        void pnlRestockCard_Paint(Object^ sender, PaintEventArgs^ e) {
            Pen^ pen = gcnew Pen(Color::FromArgb(187, 247, 208), 1);
            e->Graphics->DrawRectangle(pen, 0, 0, pnlRestockCard->Width - 1, pnlRestockCard->Height - 1);
        }

        void Field_Enter(Object^ sender, EventArgs^ e) {
            TextBox^ tb = (TextBox^)sender;
            Panel^ line = nullptr;
            if (tb == txtName) line = pnlNameLine;
            else if (tb == txtCategory) line = pnlCategoryLine;
            else if (tb == txtPrice) line = pnlPriceLine;
            if (line != nullptr) line->BackColor = NAVY;
        }
        void Field_Leave(Object^ sender, EventArgs^ e) {
            TextBox^ tb = (TextBox^)sender;
            Panel^ line = nullptr;
            if (tb == txtName) line = pnlNameLine;
            else if (tb == txtCategory) line = pnlCategoryLine;
            else if (tb == txtPrice) line = pnlPriceLine;
            if (line != nullptr) line->BackColor = BORDER_GREY;
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
        void btnSave_MouseEnter(Object^ s, EventArgs^ e) { btnSave->BackColor = NAVY_HOVER; }
        void btnSave_MouseLeave(Object^ s, EventArgs^ e) { btnSave->BackColor = NAVY; }
        void btnRestock_MouseEnter(Object^ s, EventArgs^ e) { btnRestock->BackColor = GREEN_BTN_HOVER; }
        void btnRestock_MouseLeave(Object^ s, EventArgs^ e) { btnRestock->BackColor = GREEN_BTN; }
        void btnCancel_MouseEnter(Object^ s, EventArgs^ e) { btnCancel->BackColor = BG_LIGHT; }
        void btnCancel_MouseLeave(Object^ s, EventArgs^ e) { btnCancel->BackColor = Color::White; }
        void btnTopClose_MouseEnter(Object^ s, EventArgs^ e) {
            btnTopClose->BackColor = Color::FromArgb(239, 68, 68);
            btnTopClose->ForeColor = Color::White;
        }
        void btnTopClose_MouseLeave(Object^ s, EventArgs^ e) {
            btnTopClose->BackColor = Color::Transparent;
            btnTopClose->ForeColor = TEXT_MUTED;
        }

        // Original logic preserved
        void loadData() {
            DataTable^ dt = SBS::Database::ExecuteQuery(
                "SELECT * FROM Products WHERE ProductID = @id",
                gcnew SqlParameter("@id", productID));
            if (dt->Rows->Count > 0) {
                DataTableReader^ r = dt->CreateDataReader();
                if (r->Read()) {
                    txtName->Text = r->GetString(1);
                    txtCategory->Text = r->GetString(2);
                    txtPrice->Text = r->GetDecimal(3).ToString();
                }
                r->Close();
            }
        }

        void btnSave_Click(Object^ sender, EventArgs^ e) {
            if (txtName->Text->Trim() == "") { MessageBox::Show("Name cannot be empty."); return; }
            if (txtCategory->Text->Trim() == "") { MessageBox::Show("Category cannot be empty."); return; }
            double price;
            if (!Double::TryParse(txtPrice->Text, price) || price <= 0) {
                MessageBox::Show("Enter a valid price."); return;
            }
            pm->updateInDB(productID, txtName->Text->Trim(), txtCategory->Text->Trim(), price);
            MessageBox::Show("Product updated!", "Success",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
            this->Close();
        }

        void btnRestock_Click(Object^ sender, EventArgs^ e) {
            int qty;
            if (!Int32::TryParse(txtRestockQty->Text, qty) || qty <= 0) {
                MessageBox::Show("Enter a valid quantity."); return;
            }
            pm->increaseStockInDB(productID, qty);
            MessageBox::Show("Stock increased by " + qty + "!", "Restocked",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
            txtRestockQty->Text = "0";
        }

        void btnCancel_Click(Object^ sender, EventArgs^ e) { this->Close(); }
    };
}