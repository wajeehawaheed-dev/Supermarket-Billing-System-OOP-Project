#include "ChangePasswordForm.h"

namespace SUper
{
    using namespace System::Drawing::Drawing2D;

    static System::Drawing::Color CPF_NAVY() { return System::Drawing::Color::FromArgb(30, 58, 138); }
    static System::Drawing::Color CPF_PURPLE() { return System::Drawing::Color::FromArgb(124, 58, 237); }
    static System::Drawing::Color CPF_RED() { return System::Drawing::Color::FromArgb(220, 38, 38); }
    static System::Drawing::Color CPF_BORDER() { return System::Drawing::Color::FromArgb(229, 231, 235); }
    static System::Drawing::Color CPF_TEXT_DARK() { return System::Drawing::Color::FromArgb(30, 41, 59); }
    static System::Drawing::Color CPF_TEXT_MUTED() { return System::Drawing::Color::FromArgb(100, 116, 139); }

    static void CPF_RoundIt(System::Windows::Forms::Control^ ctrl, int radius)
    {
        GraphicsPath^ path = gcnew GraphicsPath();
        System::Drawing::Rectangle r = ctrl->ClientRectangle;
        path->AddArc(r.X, r.Y, radius, radius, 180, 90);
        path->AddArc(r.Right - radius, r.Y, radius, radius, 270, 90);
        path->AddArc(r.Right - radius, r.Bottom - radius, radius, radius, 0, 90);
        path->AddArc(r.X, r.Bottom - radius, radius, radius, 90, 90);
        path->CloseAllFigures();
        ctrl->Region = gcnew System::Drawing::Region(path);
    }

    ChangePasswordForm::ChangePasswordForm(User^ user)
    {
        loggedInUser = user;
        adminResetMode = false;
        InitializeComponent();
    }

    ChangePasswordForm::ChangePasswordForm(User^ user, bool adminReset)
    {
        loggedInUser = user;
        adminResetMode = adminReset;
        InitializeComponent();
    }

    void ChangePasswordForm::InitializeComponent()
    {
        this->Text = adminResetMode
            ? ("Reset Password - " + loggedInUser->getUsername())
            : "Change Password";
        this->StartPosition = FormStartPosition::CenterParent;
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
        this->BackColor = System::Drawing::Color::White;
        this->DoubleBuffered = true;

        // Form size depends on mode (no old password field in admin reset)
        int formHeight = adminResetMode ? 470 : 560;
        this->ClientSize = System::Drawing::Size(440, formHeight);

        // ----- TITLE -----
        lblTitle = gcnew System::Windows::Forms::Label();
        lblTitle->Text = adminResetMode ? "Reset Password" : "Change Password";
        lblTitle->Font = gcnew System::Drawing::Font("Segoe UI", 16, System::Drawing::FontStyle::Bold);
        lblTitle->ForeColor = CPF_TEXT_DARK();
        lblTitle->Location = System::Drawing::Point(30, 25);
        lblTitle->AutoSize = true;

        Label^ lblSub = gcnew System::Windows::Forms::Label();
        lblSub->Text = adminResetMode
            ? ("For user: " + loggedInUser->getUsername())
            : "Update your account password";
        lblSub->Font = gcnew System::Drawing::Font("Segoe UI", 9);
        lblSub->ForeColor = CPF_TEXT_MUTED();
        lblSub->Location = System::Drawing::Point(32, 55);
        lblSub->AutoSize = true;

        // ----- Close X -----
        Label^ btnTopClose = gcnew System::Windows::Forms::Label();
        btnTopClose->Text = L"\u2715";
        btnTopClose->Font = gcnew System::Drawing::Font("Segoe UI", 12, System::Drawing::FontStyle::Bold);
        btnTopClose->ForeColor = CPF_TEXT_MUTED();
        btnTopClose->BackColor = System::Drawing::Color::Transparent;
        btnTopClose->Location = System::Drawing::Point(390, 22);
        btnTopClose->Size = System::Drawing::Size(35, 30);
        btnTopClose->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
        btnTopClose->Cursor = System::Windows::Forms::Cursors::Hand;
        btnTopClose->Click += gcnew System::EventHandler(this, &ChangePasswordForm::btnCancel_Click);

        int yCursor = 100;

        // ----- CURRENT PASSWORD (self-change only) -----
        lblOld = gcnew System::Windows::Forms::Label();
        lblOld->Text = "CURRENT PASSWORD";
        lblOld->Font = gcnew System::Drawing::Font("Segoe UI", 8.5F, System::Drawing::FontStyle::Bold);
        lblOld->ForeColor = CPF_TEXT_MUTED();
        lblOld->Location = System::Drawing::Point(35, yCursor);
        lblOld->AutoSize = true;
        lblOld->Visible = !adminResetMode;

        txtOld = gcnew System::Windows::Forms::TextBox();
        txtOld->BorderStyle = System::Windows::Forms::BorderStyle::None;
        txtOld->Font = gcnew System::Drawing::Font("Segoe UI", 11);
        txtOld->ForeColor = CPF_TEXT_DARK();
        txtOld->Location = System::Drawing::Point(35, yCursor + 22);
        txtOld->Size = System::Drawing::Size(370, 22);
        txtOld->PasswordChar = L'\u25CF';
        txtOld->Visible = !adminResetMode;

        Panel^ pnlOldLine = gcnew System::Windows::Forms::Panel();
        pnlOldLine->Location = System::Drawing::Point(35, yCursor + 49);
        pnlOldLine->Size = System::Drawing::Size(370, 2);
        pnlOldLine->BackColor = CPF_BORDER();
        pnlOldLine->Visible = !adminResetMode;

        if (!adminResetMode) yCursor += 90;

        // ----- NEW PASSWORD -----
        lblNew = gcnew System::Windows::Forms::Label();
        lblNew->Text = "NEW PASSWORD";
        lblNew->Font = gcnew System::Drawing::Font("Segoe UI", 8.5F, System::Drawing::FontStyle::Bold);
        lblNew->ForeColor = CPF_TEXT_MUTED();
        lblNew->Location = System::Drawing::Point(35, yCursor);
        lblNew->AutoSize = true;

        txtNew = gcnew System::Windows::Forms::TextBox();
        txtNew->BorderStyle = System::Windows::Forms::BorderStyle::None;
        txtNew->Font = gcnew System::Drawing::Font("Segoe UI", 11);
        txtNew->ForeColor = CPF_TEXT_DARK();
        txtNew->Location = System::Drawing::Point(35, yCursor + 22);
        txtNew->Size = System::Drawing::Size(370, 22);
        txtNew->PasswordChar = L'\u25CF';

        Panel^ pnlNewLine = gcnew System::Windows::Forms::Panel();
        pnlNewLine->Location = System::Drawing::Point(35, yCursor + 49);
        pnlNewLine->Size = System::Drawing::Size(370, 2);
        pnlNewLine->BackColor = CPF_BORDER();

        Label^ lblHint = gcnew System::Windows::Forms::Label();
        lblHint->Text = "Min 8 characters with at least 1 number";
        lblHint->Font = gcnew System::Drawing::Font("Segoe UI", 8);
        lblHint->ForeColor = CPF_TEXT_MUTED();
        lblHint->Location = System::Drawing::Point(35, yCursor + 56);
        lblHint->AutoSize = true;

        yCursor += 90;

        // ----- CONFIRM -----
        lblConfirm = gcnew System::Windows::Forms::Label();
        lblConfirm->Text = "CONFIRM NEW PASSWORD";
        lblConfirm->Font = gcnew System::Drawing::Font("Segoe UI", 8.5F, System::Drawing::FontStyle::Bold);
        lblConfirm->ForeColor = CPF_TEXT_MUTED();
        lblConfirm->Location = System::Drawing::Point(35, yCursor);
        lblConfirm->AutoSize = true;

        txtConfirm = gcnew System::Windows::Forms::TextBox();
        txtConfirm->BorderStyle = System::Windows::Forms::BorderStyle::None;
        txtConfirm->Font = gcnew System::Drawing::Font("Segoe UI", 11);
        txtConfirm->ForeColor = CPF_TEXT_DARK();
        txtConfirm->Location = System::Drawing::Point(35, yCursor + 22);
        txtConfirm->Size = System::Drawing::Size(370, 22);
        txtConfirm->PasswordChar = L'\u25CF';

        Panel^ pnlConfirmLine = gcnew System::Windows::Forms::Panel();
        pnlConfirmLine->Location = System::Drawing::Point(35, yCursor + 49);
        pnlConfirmLine->Size = System::Drawing::Size(370, 2);
        pnlConfirmLine->BackColor = CPF_BORDER();

        yCursor += 75;

        // ----- ERROR -----
        lblError = gcnew System::Windows::Forms::Label();
        lblError->Text = "";
        lblError->Font = gcnew System::Drawing::Font("Segoe UI", 9);
        lblError->ForeColor = CPF_RED();
        lblError->Location = System::Drawing::Point(35, yCursor);
        lblError->Size = System::Drawing::Size(370, 22);

        // ----- BUTTONS -----
        // Use purple for admin-reset (matches the "Change Password" button in user list),
        // navy for self-change (more typical "save" action)
        System::Drawing::Color primaryColor = adminResetMode ? CPF_PURPLE() : CPF_NAVY();

        btnChange = gcnew System::Windows::Forms::Button();
        btnChange->Text = adminResetMode ? "Reset Password" : "Update Password";
        btnChange->Font = gcnew System::Drawing::Font("Segoe UI", 10, System::Drawing::FontStyle::Bold);
        btnChange->Size = System::Drawing::Size(220, 44);
        btnChange->Location = System::Drawing::Point(185, formHeight - 65);
        btnChange->BackColor = primaryColor;
        btnChange->ForeColor = System::Drawing::Color::White;
        btnChange->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnChange->FlatAppearance->BorderSize = 0;
        btnChange->Cursor = System::Windows::Forms::Cursors::Hand;
        btnChange->Click += gcnew System::EventHandler(this, &ChangePasswordForm::btnChange_Click);

        btnCancel = gcnew System::Windows::Forms::Button();
        btnCancel->Text = "Cancel";
        btnCancel->Font = gcnew System::Drawing::Font("Segoe UI", 10);
        btnCancel->Size = System::Drawing::Size(140, 44);
        btnCancel->Location = System::Drawing::Point(35, formHeight - 65);
        btnCancel->BackColor = System::Drawing::Color::White;
        btnCancel->ForeColor = CPF_TEXT_DARK();
        btnCancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnCancel->FlatAppearance->BorderSize = 1;
        btnCancel->FlatAppearance->BorderColor = CPF_BORDER();
        btnCancel->Cursor = System::Windows::Forms::Cursors::Hand;
        btnCancel->Click += gcnew System::EventHandler(this, &ChangePasswordForm::btnCancel_Click);

        // Add controls
        this->Controls->Add(lblTitle);
        this->Controls->Add(lblSub);
        this->Controls->Add(btnTopClose);
        this->Controls->Add(lblOld);
        this->Controls->Add(txtOld);
        this->Controls->Add(pnlOldLine);
        this->Controls->Add(lblNew);
        this->Controls->Add(txtNew);
        this->Controls->Add(pnlNewLine);
        this->Controls->Add(lblHint);
        this->Controls->Add(lblConfirm);
        this->Controls->Add(txtConfirm);
        this->Controls->Add(pnlConfirmLine);
        this->Controls->Add(lblError);
        this->Controls->Add(btnChange);
        this->Controls->Add(btnCancel);

        CPF_RoundIt(btnChange, 6);
        CPF_RoundIt(btnCancel, 6);
    }

    void ChangePasswordForm::btnChange_Click(System::Object^ sender, System::EventArgs^ e)
    {
        String^ newPass = txtNew->Text->Trim();
        String^ confirm = txtConfirm->Text->Trim();

        if (newPass == "" || confirm == "") {
            lblError->Text = "All fields are required.";
            return;
        }
        User^ temp = gcnew User();
        if (!temp->Passwordvalidation(newPass)) {
            lblError->Text = "Min 8 characters and 1 number required.";
            return;
        }
        if (newPass != confirm) {
            lblError->Text = "Passwords do not match.";
            return;
        }

        if (adminResetMode) {
            if (UserDB::adminResetPassword(loggedInUser->getUserID(), newPass)) {
                MessageBox::Show("Password reset for " + loggedInUser->getUsername() + ".");
                this->Close();
            }
        }
        else {
            String^ oldPass = txtOld->Text->Trim();
            if (oldPass == "") {
                lblError->Text = "Current password is required.";
                return;
            }
            if (newPass == oldPass) {
                lblError->Text = "New password must differ from current.";
                return;
            }
            if (UserDB::changePassword(loggedInUser->getUserID(), oldPass, newPass)) {
                MessageBox::Show("Password changed successfully.");
                this->Close();
            }
        }
    }

    void ChangePasswordForm::btnCancel_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->Close();
    }
}