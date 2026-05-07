#pragma once
#include "AdminDashboardForm.h"
#include "database.h"
#include "session.h"
#include "CartForm.h"

namespace SUper {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Data::SqlClient;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    public ref class LoginForm : public System::Windows::Forms::Form
    {
    public:
        LoginForm(void)
        {
            InitializeComponent();
            ApplyModernStyle();
        }

    protected:
        ~LoginForm()
        {
            if (components) { delete components; }
        }

     //Brand palette
    private:
        static Color NAVY;
        static Color NAVY_DARK;
        static Color NAVY_HOVER;
        static Color GREEN_ACCENT;
        static Color BORDER_GREY;
        static Color TEXT_DARK;
        static Color TEXT_MUTED;

        static LoginForm()
        {
            NAVY = Color::FromArgb(30, 58, 138);
            NAVY_DARK = Color::FromArgb(15, 30, 90);
            NAVY_HOVER = Color::FromArgb(45, 75, 165);
            GREEN_ACCENT = Color::FromArgb(34, 197, 94);
            BORDER_GREY = Color::FromArgb(220, 224, 230);
            TEXT_DARK = Color::FromArgb(30, 41, 59);
            TEXT_MUTED = Color::FromArgb(100, 116, 139);
        }

        // ===== Controls =====
    private: System::Windows::Forms::Panel^ pnlLeft;
    private: System::Windows::Forms::Panel^ pnlRight;
    private: System::Windows::Forms::PictureBox^ picLogo;
    private: System::Windows::Forms::Label^ lblHead;
    private: System::Windows::Forms::Label^ label2;          // kept for back-compat (hidden)
    private: System::Windows::Forms::Label^ lblSubtitle;
    private: System::Windows::Forms::Label^ lblUsername;
    private: System::Windows::Forms::TextBox^ txtUsername;
    private: System::Windows::Forms::Panel^ pnlUsernameLine;
    private: System::Windows::Forms::Label^ lblPassword;
    private: System::Windows::Forms::TextBox^ txtPassword;
    private: System::Windows::Forms::Panel^ pnlPasswordLine;
    private: System::Windows::Forms::Button^ btnLogin;
    private: System::Windows::Forms::Label^ lblerror;
    private: System::Windows::Forms::Label^ btnClose;

    private:
        bool dragging;
        Point dragOffset;
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->pnlLeft = gcnew Panel();
            this->pnlRight = gcnew Panel();
            this->picLogo = gcnew PictureBox();
            this->lblHead = gcnew Label();
            this->label2 = gcnew Label();
            this->lblSubtitle = gcnew Label();
            this->lblUsername = gcnew Label();
            this->txtUsername = gcnew TextBox();
            this->pnlUsernameLine = gcnew Panel();
            this->lblPassword = gcnew Label();
            this->txtPassword = gcnew TextBox();
            this->pnlPasswordLine = gcnew Panel();
            this->btnLogin = gcnew Button();
            this->lblerror = gcnew Label();
            this->btnClose = gcnew Label();
            this->SuspendLayout();

            // -------- Left brand panel (navy gradient + logo) --------
            this->pnlLeft->Location = Point(0, 0);
            this->pnlLeft->Size = Drawing::Size(450, 560);
            this->pnlLeft->BackColor = NAVY;
            this->pnlLeft->Paint += gcnew PaintEventHandler(this, &LoginForm::pnlLeft_Paint);
            this->pnlLeft->MouseDown += gcnew MouseEventHandler(this, &LoginForm::Form_MouseDown);
            this->pnlLeft->MouseMove += gcnew MouseEventHandler(this, &LoginForm::Form_MouseMove);
            this->pnlLeft->MouseUp += gcnew MouseEventHandler(this, &LoginForm::Form_MouseUp);

            // -------- Logo --------
            this->picLogo->Location = Point(85, 130);
            this->picLogo->Size = Drawing::Size(280, 280);
            this->picLogo->SizeMode = PictureBoxSizeMode::Zoom;
            this->picLogo->BackColor = Color::Transparent;
            this->pnlLeft->Controls->Add(this->picLogo);

            // -------- Right form panel --------
            this->pnlRight->Location = Point(450, 0);
            this->pnlRight->Size = Drawing::Size(450, 560);
            this->pnlRight->BackColor = Color::White;
            this->pnlRight->MouseDown += gcnew MouseEventHandler(this, &LoginForm::Form_MouseDown);
            this->pnlRight->MouseMove += gcnew MouseEventHandler(this, &LoginForm::Form_MouseMove);
            this->pnlRight->MouseUp += gcnew MouseEventHandler(this, &LoginForm::Form_MouseUp);

            // -------- Close (X) button --------
            this->btnClose->Text = L"\u2715";   // ✕
            this->btnClose->Font = gcnew Drawing::Font(L"Segoe UI", 12.0F, FontStyle::Bold);
            this->btnClose->ForeColor = TEXT_MUTED;
            this->btnClose->BackColor = Color::Transparent;
            this->btnClose->Location = Point(400, 15);
            this->btnClose->Size = Drawing::Size(35, 35);
            this->btnClose->TextAlign = ContentAlignment::MiddleCenter;
            this->btnClose->Cursor = Cursors::Hand;
            this->btnClose->Click += gcnew EventHandler(this, &LoginForm::btnClose_Click);
            this->btnClose->MouseEnter += gcnew EventHandler(this, &LoginForm::btnClose_MouseEnter);
            this->btnClose->MouseLeave += gcnew EventHandler(this, &LoginForm::btnClose_MouseLeave);

            // -------- Heading --------
            this->lblHead->AutoSize = true;
            this->lblHead->Font = gcnew Drawing::Font(L"Segoe UI", 24.0F, FontStyle::Bold);
            this->lblHead->ForeColor = TEXT_DARK;
            this->lblHead->Location = Point(60, 90);
            this->lblHead->Text = L"Welcome Back";
            this->lblHead->BackColor = Color::Transparent;
            this->lblHead->Click += gcnew EventHandler(this, &LoginForm::label1_Click);

            // -------- Subtitle --------
            this->lblSubtitle->AutoSize = true;
            this->lblSubtitle->Font = gcnew Drawing::Font(L"Segoe UI", 10.0F);
            this->lblSubtitle->ForeColor = TEXT_MUTED;
            this->lblSubtitle->Location = Point(62, 138);
            this->lblSubtitle->Text = L"Sign in to continue to your account";
            this->lblSubtitle->BackColor = Color::Transparent;

            // -------- label2 (kept, hidden — preserves any external references) --------
            this->label2->AutoSize = true;
            this->label2->Visible = false;
            this->label2->Location = Point(0, 0);

            // -------- Username --------
            this->lblUsername->AutoSize = true;
            this->lblUsername->Font = gcnew Drawing::Font(L"Segoe UI", 8.5F, FontStyle::Bold);
            this->lblUsername->ForeColor = TEXT_MUTED;
            this->lblUsername->Location = Point(60, 200);
            this->lblUsername->Text = L"USERNAME";
            this->lblUsername->BackColor = Color::Transparent;

            this->txtUsername->BorderStyle = BorderStyle::None;
            this->txtUsername->Font = gcnew Drawing::Font(L"Segoe UI", 11.0F);
            this->txtUsername->ForeColor = TEXT_DARK;
            this->txtUsername->Location = Point(60, 225);
            this->txtUsername->Size = Drawing::Size(330, 22);
            this->txtUsername->TabIndex = 0;
            this->txtUsername->TextChanged += gcnew EventHandler(this, &LoginForm::textBox1_TextChanged);
            this->txtUsername->Enter += gcnew EventHandler(this, &LoginForm::txtUsername_Enter);
            this->txtUsername->Leave += gcnew EventHandler(this, &LoginForm::txtUsername_Leave);

            this->pnlUsernameLine->Location = Point(60, 252);
            this->pnlUsernameLine->Size = Drawing::Size(330, 2);
            this->pnlUsernameLine->BackColor = BORDER_GREY;

            // -------- Password --------
            this->lblPassword->AutoSize = true;
            this->lblPassword->Font = gcnew Drawing::Font(L"Segoe UI", 8.5F, FontStyle::Bold);
            this->lblPassword->ForeColor = TEXT_MUTED;
            this->lblPassword->Location = Point(60, 285);
            this->lblPassword->Text = L"PASSWORD";
            this->lblPassword->BackColor = Color::Transparent;

            this->txtPassword->BorderStyle = BorderStyle::None;
            this->txtPassword->Font = gcnew Drawing::Font(L"Segoe UI", 11.0F);
            this->txtPassword->ForeColor = TEXT_DARK;
            this->txtPassword->Location = Point(60, 310);
            this->txtPassword->Size = Drawing::Size(330, 22);
            this->txtPassword->PasswordChar = L'\u25CF';   // ●
            this->txtPassword->TabIndex = 1;
            this->txtPassword->Enter += gcnew EventHandler(this, &LoginForm::txtPassword_Enter);
            this->txtPassword->Leave += gcnew EventHandler(this, &LoginForm::txtPassword_Leave);

            this->pnlPasswordLine->Location = Point(60, 337);
            this->pnlPasswordLine->Size = Drawing::Size(330, 2);
            this->pnlPasswordLine->BackColor = BORDER_GREY;

            // -------- Error label --------
            this->lblerror->AutoSize = false;
            this->lblerror->Size = Drawing::Size(330, 20);
            this->lblerror->Font = gcnew Drawing::Font(L"Segoe UI", 8.5F);
            this->lblerror->ForeColor = Color::FromArgb(220, 38, 38);
            this->lblerror->Location = Point(60, 355);
            this->lblerror->BackColor = Color::Transparent;
            this->lblerror->TextAlign = ContentAlignment::MiddleLeft;

            // -------- Login button --------
            this->btnLogin->Font = gcnew Drawing::Font(L"Segoe UI", 11.0F, FontStyle::Bold);
            this->btnLogin->BackColor = NAVY;
            this->btnLogin->ForeColor = Color::White;
            this->btnLogin->FlatStyle = FlatStyle::Flat;
            this->btnLogin->FlatAppearance->BorderSize = 0;
            this->btnLogin->Location = Point(60, 390);
            this->btnLogin->Size = Drawing::Size(330, 48);
            this->btnLogin->Text = L"SIGN IN";
            this->btnLogin->Cursor = Cursors::Hand;
            this->btnLogin->TabIndex = 2;
            this->btnLogin->Click += gcnew EventHandler(this, &LoginForm::btnLogin_Click);
            this->btnLogin->MouseEnter += gcnew EventHandler(this, &LoginForm::btnLogin_MouseEnter);
            this->btnLogin->MouseLeave += gcnew EventHandler(this, &LoginForm::btnLogin_MouseLeave);

            // Add controls to right panel
            this->pnlRight->Controls->Add(this->btnClose);
            this->pnlRight->Controls->Add(this->lblHead);
            this->pnlRight->Controls->Add(this->lblSubtitle);
            this->pnlRight->Controls->Add(this->label2);
            this->pnlRight->Controls->Add(this->lblUsername);
            this->pnlRight->Controls->Add(this->txtUsername);
            this->pnlRight->Controls->Add(this->pnlUsernameLine);
            this->pnlRight->Controls->Add(this->lblPassword);
            this->pnlRight->Controls->Add(this->txtPassword);
            this->pnlRight->Controls->Add(this->pnlPasswordLine);
            this->pnlRight->Controls->Add(this->lblerror);
            this->pnlRight->Controls->Add(this->btnLogin);

            // -------- Form --------
            this->AcceptButton = this->btnLogin;
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = Drawing::Size(900, 560);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->StartPosition = FormStartPosition::CenterScreen;
            this->BackColor = Color::White;
            this->DoubleBuffered = true;
            this->Controls->Add(this->pnlRight);
            this->Controls->Add(this->pnlLeft);
            this->Name = L"LoginForm";
            this->Text = L"ValueMart Login";
            this->Load += gcnew EventHandler(this, &LoginForm::LoginForm_Load);
            this->MouseDown += gcnew MouseEventHandler(this, &LoginForm::Form_MouseDown);
            this->MouseMove += gcnew MouseEventHandler(this, &LoginForm::Form_MouseMove);
            this->MouseUp += gcnew MouseEventHandler(this, &LoginForm::Form_MouseUp);
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private: void ApplyModernStyle() {
        RoundControl(this->btnLogin, 8);

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
        catch (...) { /* logo missing — panel stays as gradient */ }
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

    private: System::Void pnlLeft_Paint(Object^ sender, PaintEventArgs^ e) {
        e->Graphics->SmoothingMode = SmoothingMode::AntiAlias;
        LinearGradientBrush^ brush = gcnew LinearGradientBrush(
            this->pnlLeft->ClientRectangle, NAVY, NAVY_DARK, 135.0f);
        e->Graphics->FillRectangle(brush, this->pnlLeft->ClientRectangle);
        // Subtle decorative bubbles
        SolidBrush^ bubble = gcnew SolidBrush(Color::FromArgb(20, 255, 255, 255));
        e->Graphics->FillEllipse(bubble, -120, -120, 260, 260);
        e->Graphics->FillEllipse(bubble, 320, 420, 220, 220);
    }

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

           // ============== Close button ==============
    private: System::Void btnClose_Click(Object^ sender, EventArgs^ e) {
        Application::Exit();
    }
    private: System::Void btnClose_MouseEnter(Object^ sender, EventArgs^ e) {
        btnClose->BackColor = Color::FromArgb(239, 68, 68);
        btnClose->ForeColor = Color::White;
    }
    private: System::Void btnClose_MouseLeave(Object^ sender, EventArgs^ e) {
        btnClose->BackColor = Color::Transparent;
        btnClose->ForeColor = TEXT_MUTED;
    }

           // ============== Button hover ==============
    private: System::Void btnLogin_MouseEnter(Object^ sender, EventArgs^ e) {
        btnLogin->BackColor = NAVY_HOVER;
    }
    private: System::Void btnLogin_MouseLeave(Object^ sender, EventArgs^ e) {
        btnLogin->BackColor = NAVY;
    }

           // ============== Underline focus highlight ==============
    private: System::Void txtUsername_Enter(Object^ sender, EventArgs^ e) {
        pnlUsernameLine->BackColor = NAVY;
        pnlUsernameLine->Height = 2;
    }
    private: System::Void txtUsername_Leave(Object^ sender, EventArgs^ e) {
        pnlUsernameLine->BackColor = BORDER_GREY;
    }
    private: System::Void txtPassword_Enter(Object^ sender, EventArgs^ e) {
        pnlPasswordLine->BackColor = NAVY;
        pnlPasswordLine->Height = 2;
    }
    private: System::Void txtPassword_Leave(Object^ sender, EventArgs^ e) {
        pnlPasswordLine->BackColor = BORDER_GREY;
    }

           // ============== Original handlers (preserved) ==============
    private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void LoginForm_Load(System::Object^ sender, System::EventArgs^ e) {
    }
    private: System::Void btnLogin_Click(System::Object^ sender, System::EventArgs^ e) {
        lblerror->Text = "";

        String^ username = txtUsername->Text->Trim();
        String^ password = txtPassword->Text;

        if (String::IsNullOrEmpty(username) || String::IsNullOrEmpty(password)) {
            lblerror->Text = "Please enter username and password";
            return;
        }

        DataTable^ result = SBS::Database::ExecuteQuery(
            "SELECT UserID, Username, Role, IsActive FROM Users "
            "WHERE Username = @u AND Password = @p",
            gcnew SqlParameter("@u", username),
            gcnew SqlParameter("@p", password));

        if (result == nullptr || result->Rows->Count == 0) {
            lblerror->Text = "Invalid username or password";
            txtPassword->Clear();
            return;
        }

        DataRow^ row = result->Rows[0];

        bool isActive = Convert::ToBoolean(row["IsActive"]);
        if (!isActive) {
            lblerror->Text = "Account is deactivated. Contact admin.";
            return;
        }

        int userID = Convert::ToInt32(row["UserID"]);
        String^ uname = row["Username"]->ToString();
        String^ role = row["Role"]->ToString();

        SBS::Session::SetCurrentUser(userID, uname, role);

        this->Hide();

        if (SBS::Session::IsAdmin()) {
            AdminDashboardForm^ adminForm = gcnew AdminDashboardForm();
            adminForm->ShowDialog();
        }
        else {
            CartForm^ cartForm = gcnew CartForm(role);
            cartForm->ShowDialog();
        }

        txtUsername->Clear();
        txtPassword->Clear();
        txtUsername->Focus();
        this->Show();
    }
    };
}