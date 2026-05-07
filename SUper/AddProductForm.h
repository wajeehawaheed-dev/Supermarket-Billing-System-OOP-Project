#define WIN32_LEAN_AND_MEAN
#pragma once
#include "database.h"
#include "product.h"
#include <msclr/marshal_cppstd.h>

namespace SUper {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Data::SqlClient;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    public ref class AddProductForm : public Form {
    private:
        static Color NAVY;
        static Color NAVY_HOVER;
        static Color GREEN_BTN;
        static Color GREEN_BTN_HOVER;
        static Color BG_LIGHT;
        static Color BORDER_GREY;
        static Color TEXT_DARK;
        static Color TEXT_MUTED;

        static AddProductForm() {
            NAVY = Color::FromArgb(30, 58, 138);
            NAVY_HOVER = Color::FromArgb(45, 75, 165);
            GREEN_BTN = Color::FromArgb(34, 197, 94);
            GREEN_BTN_HOVER = Color::FromArgb(22, 163, 74);
            BG_LIGHT = Color::FromArgb(248, 250, 252);
            BORDER_GREY = Color::FromArgb(220, 224, 230);
            TEXT_DARK = Color::FromArgb(30, 41, 59);
            TEXT_MUTED = Color::FromArgb(100, 116, 139);
        }

        ProductManager^ pm;
        TextBox^ txtName;
        TextBox^ txtCategory;
        TextBox^ txtPrice;
        TextBox^ txtStock;
        Panel^ pnlNameLine;
        Panel^ pnlCategoryLine;
        Panel^ pnlPriceLine;
        Panel^ pnlStockLine;
        Button^ btnSave;
        Button^ btnCancel;
        Label^ btnTopClose;

        bool dragging;
        Point dragOffset;

    public:
        AddProductForm() {
            pm = gcnew ProductManager();
            InitializeComponent();
            ApplyModernStyle();
        }
        ~AddProductForm() {}

    private:
        void InitializeComponent() {
            this->Text = "Add New Product";
            this->ClientSize = System::Drawing::Size(420, 560);
            this->StartPosition = FormStartPosition::CenterParent;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->BackColor = Color::White;
            this->DoubleBuffered = true;

            // Title bar
            Label^ lblTitle = gcnew Label();
            lblTitle->Text = "Add New Product";
            lblTitle->Font = gcnew System::Drawing::Font("Segoe UI", 16.0F, FontStyle::Bold);
            lblTitle->ForeColor = TEXT_DARK;
            lblTitle->Location = Point(30, 25);
            lblTitle->AutoSize = true;

            Label^ lblSub = gcnew Label();
            lblSub->Text = "Fill in the product details below";
            lblSub->Font = gcnew System::Drawing::Font("Segoe UI", 9.0F);
            lblSub->ForeColor = TEXT_MUTED;
            lblSub->Location = Point(32, 55);
            lblSub->AutoSize = true;

            btnTopClose = gcnew Label();
            btnTopClose->Text = L"\u2715";
            btnTopClose->Font = gcnew System::Drawing::Font("Segoe UI", 12.0F, FontStyle::Bold);
            btnTopClose->ForeColor = TEXT_MUTED;
            btnTopClose->Location = Point(370, 22);
            btnTopClose->Size = System::Drawing::Size(35, 30);
            btnTopClose->TextAlign = ContentAlignment::MiddleCenter;
            btnTopClose->Cursor = Cursors::Hand;
            btnTopClose->Click += gcnew EventHandler(this, &AddProductForm::btnCancel_Click);
            btnTopClose->MouseEnter += gcnew EventHandler(this, &AddProductForm::btnTopClose_MouseEnter);
            btnTopClose->MouseLeave += gcnew EventHandler(this, &AddProductForm::btnTopClose_MouseLeave);

            // Form fields
            CreateField("PRODUCT NAME", 100, txtName, pnlNameLine);
            CreateField("CATEGORY", 170, txtCategory, pnlCategoryLine);
            CreateField("PRICE (RS.)", 240, txtPrice, pnlPriceLine);
            CreateField("INITIAL STOCK", 310, txtStock, pnlStockLine);

            // Buttons
            btnSave = gcnew Button();
            btnSave->Text = "Add Product";
            btnSave->Font = gcnew System::Drawing::Font("Segoe UI", 10.0F, FontStyle::Bold);
            btnSave->BackColor = GREEN_BTN;
            btnSave->ForeColor = Color::White;
            btnSave->FlatStyle = FlatStyle::Flat;
            btnSave->FlatAppearance->BorderSize = 0;
            btnSave->Location = Point(195, 470);
            btnSave->Size = System::Drawing::Size(190, 44);
            btnSave->Cursor = Cursors::Hand;
            btnSave->Click += gcnew EventHandler(this, &AddProductForm::btnSave_Click);
            btnSave->MouseEnter += gcnew EventHandler(this, &AddProductForm::btnSave_MouseEnter);
            btnSave->MouseLeave += gcnew EventHandler(this, &AddProductForm::btnSave_MouseLeave);

            btnCancel = gcnew Button();
            btnCancel->Text = "Cancel";
            btnCancel->Font = gcnew System::Drawing::Font("Segoe UI", 10.0F);
            btnCancel->BackColor = Color::White;
            btnCancel->ForeColor = TEXT_DARK;
            btnCancel->FlatStyle = FlatStyle::Flat;
            btnCancel->FlatAppearance->BorderSize = 1;
            btnCancel->FlatAppearance->BorderColor = BORDER_GREY;
            btnCancel->Location = Point(35, 470);
            btnCancel->Size = System::Drawing::Size(150, 44);
            btnCancel->Cursor = Cursors::Hand;
            btnCancel->Click += gcnew EventHandler(this, &AddProductForm::btnCancel_Click);
            btnCancel->MouseEnter += gcnew EventHandler(this, &AddProductForm::btnCancel_MouseEnter);
            btnCancel->MouseLeave += gcnew EventHandler(this, &AddProductForm::btnCancel_MouseLeave);

            this->Controls->Add(lblTitle);
            this->Controls->Add(lblSub);
            this->Controls->Add(btnTopClose);
            this->Controls->Add(btnSave);
            this->Controls->Add(btnCancel);

            this->MouseDown += gcnew MouseEventHandler(this, &AddProductForm::Form_MouseDown);
            this->MouseMove += gcnew MouseEventHandler(this, &AddProductForm::Form_MouseMove);
            this->MouseUp += gcnew MouseEventHandler(this, &AddProductForm::Form_MouseUp);
            this->Paint += gcnew PaintEventHandler(this, &AddProductForm::Form_Paint);
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
            tb->Size = System::Drawing::Size(350, 22);
            tb->Enter += gcnew EventHandler(this, &AddProductForm::Field_Enter);
            tb->Leave += gcnew EventHandler(this, &AddProductForm::Field_Leave);

            line = gcnew Panel();
            line->Location = Point(35, y + 49);
            line->Size = System::Drawing::Size(350, 2);
            line->BackColor = BORDER_GREY;

            this->Controls->Add(lbl);
            this->Controls->Add(tb);
            this->Controls->Add(line);
        }

        void ApplyModernStyle() {
            RoundControl(btnSave, 6);
            RoundControl(btnCancel, 6);
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

        void Field_Enter(Object^ sender, EventArgs^ e) {
            TextBox^ tb = (TextBox^)sender;
            Panel^ line = nullptr;
            if (tb == txtName) line = pnlNameLine;
            else if (tb == txtCategory) line = pnlCategoryLine;
            else if (tb == txtPrice) line = pnlPriceLine;
            else if (tb == txtStock) line = pnlStockLine;
            if (line != nullptr) line->BackColor = NAVY;
        }
        void Field_Leave(Object^ sender, EventArgs^ e) {
            TextBox^ tb = (TextBox^)sender;
            Panel^ line = nullptr;
            if (tb == txtName) line = pnlNameLine;
            else if (tb == txtCategory) line = pnlCategoryLine;
            else if (tb == txtPrice) line = pnlPriceLine;
            else if (tb == txtStock) line = pnlStockLine;
            if (line != nullptr) line->BackColor = BORDER_GREY;
        }

        // Drag
        void Form_MouseDown(Object^ sender, MouseEventArgs^ e) {
            if (e->Button == System::Windows::Forms::MouseButtons::Left) {
                dragging = true;
                dragOffset = Point(
                    System::Windows::Forms::Cursor::Position.X - this->Location.X,
                    System::Windows::Forms::Cursor::Position.Y - this->Location.Y);
            }
        }
        void Form_MouseMove(Object^ sender, MouseEventArgs^ e) {
            if (dragging) {
                this->Location = Point(
                    System::Windows::Forms::Cursor::Position.X - dragOffset.X,
                    System::Windows::Forms::Cursor::Position.Y - dragOffset.Y);
            }
        }
        void Form_MouseUp(Object^ sender, MouseEventArgs^ e) { dragging = false; }

        // Hover
        void btnSave_MouseEnter(Object^ s, EventArgs^ e) { btnSave->BackColor = GREEN_BTN_HOVER; }
        void btnSave_MouseLeave(Object^ s, EventArgs^ e) { btnSave->BackColor = GREEN_BTN; }
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

        // Original handlers
        void btnSave_Click(Object^ sender, EventArgs^ e) {
            if (txtName->Text->Trim() == "") { MessageBox::Show("Name cannot be empty."); return; }
            if (txtCategory->Text->Trim() == "") { MessageBox::Show("Category cannot be empty."); return; }
            double price;
            if (!Double::TryParse(txtPrice->Text, price) || price <= 0) {
                MessageBox::Show("Enter a valid price."); return;
            }
            int stock;
            if (!Int32::TryParse(txtStock->Text, stock) || stock < 0) {
                MessageBox::Show("Enter a valid stock quantity."); return;
            }
            pm->addToDB(txtName->Text->Trim(), txtCategory->Text->Trim(), price, stock);
            MessageBox::Show("Product added successfully!", "Success",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
            this->Close();
        }

        void btnCancel_Click(Object^ sender, EventArgs^ e) { this->Close(); }
    };
}