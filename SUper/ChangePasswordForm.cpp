#include "ChangePasswordForm.h"

namespace SUper
{

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
        this->Size = System::Drawing::Size(370, 360);
        this->StartPosition = FormStartPosition::CenterParent;
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->MaximizeBox = false;
        this->BackColor = System::Drawing::Color::White;

        lblTitle = gcnew System::Windows::Forms::Label();
        lblTitle->Text = adminResetMode
            ? ("Reset password for: " + loggedInUser->getUsername())
            : "Change Password";
        lblTitle->Font = gcnew System::Drawing::Font("Segoe UI", 13, System::Drawing::FontStyle::Bold);
        lblTitle->Location = System::Drawing::Point(30, 20);
        lblTitle->Size = System::Drawing::Size(310, 28);

        // Old password (only in self-change mode)
        lblOld = gcnew System::Windows::Forms::Label();
        lblOld->Text = "Current Password";
        lblOld->Location = System::Drawing::Point(30, 70);
        lblOld->Size = System::Drawing::Size(150, 20);
        lblOld->Visible = !adminResetMode;

        txtOld = gcnew System::Windows::Forms::TextBox();
        txtOld->Location = System::Drawing::Point(30, 92);
        txtOld->Size = System::Drawing::Size(290, 25);
        txtOld->PasswordChar = '*';
        txtOld->Visible = !adminResetMode;

        // Position offset for admin-reset mode (since old password is hidden)
        int yOffset = adminResetMode ? -65 : 0;

        lblNew = gcnew System::Windows::Forms::Label();
        lblNew->Text = "New Password";
        lblNew->Location = System::Drawing::Point(30, 130 + yOffset);
        lblNew->Size = System::Drawing::Size(150, 20);

        txtNew = gcnew System::Windows::Forms::TextBox();
        txtNew->Location = System::Drawing::Point(30, 152 + yOffset);
        txtNew->Size = System::Drawing::Size(290, 25);
        txtNew->PasswordChar = '*';

        lblConfirm = gcnew System::Windows::Forms::Label();
        lblConfirm->Text = "Confirm New Password";
        lblConfirm->Location = System::Drawing::Point(30, 190 + yOffset);
        lblConfirm->Size = System::Drawing::Size(180, 20);

        txtConfirm = gcnew System::Windows::Forms::TextBox();
        txtConfirm->Location = System::Drawing::Point(30, 212 + yOffset);
        txtConfirm->Size = System::Drawing::Size(290, 25);
        txtConfirm->PasswordChar = '*';

        lblError = gcnew System::Windows::Forms::Label();
        lblError->Text = "";
        lblError->ForeColor = System::Drawing::Color::Red;
        lblError->Location = System::Drawing::Point(30, 248 + yOffset);
        lblError->Size = System::Drawing::Size(290, 20);

        btnChange = gcnew System::Windows::Forms::Button();
        btnChange->Text = adminResetMode ? "Reset Password" : "Change Password";
        btnChange->Size = System::Drawing::Size(135, 38);
        btnChange->Location = System::Drawing::Point(30, 275 + yOffset);
        btnChange->BackColor = System::Drawing::Color::FromArgb(0, 120, 215);
        btnChange->ForeColor = System::Drawing::Color::White;
        btnChange->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnChange->Click += gcnew System::EventHandler(this, &ChangePasswordForm::btnChange_Click);

        btnCancel = gcnew System::Windows::Forms::Button();
        btnCancel->Text = "Cancel";
        btnCancel->Size = System::Drawing::Size(135, 38);
        btnCancel->Location = System::Drawing::Point(185, 275 + yOffset);
        btnCancel->BackColor = System::Drawing::Color::FromArgb(150, 150, 150);
        btnCancel->ForeColor = System::Drawing::Color::White;
        btnCancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnCancel->Click += gcnew System::EventHandler(this, &ChangePasswordForm::btnCancel_Click);

        this->Controls->Add(lblTitle);
        this->Controls->Add(lblOld);
        this->Controls->Add(txtOld);
        this->Controls->Add(lblNew);
        this->Controls->Add(txtNew);
        this->Controls->Add(lblConfirm);
        this->Controls->Add(txtConfirm);
        this->Controls->Add(lblError);
        this->Controls->Add(btnChange);
        this->Controls->Add(btnCancel);

        // Resize form smaller in admin-reset mode (no old password field)
        if (adminResetMode) {
            this->Size = System::Drawing::Size(370, 295);
        }
    }

    void ChangePasswordForm::btnChange_Click(Object^ sender, EventArgs^ e)
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
            // Admin resetting someone else's password — no old password check
            if (UserDB::adminResetPassword(loggedInUser->getUserID(), newPass)) {
                MessageBox::Show("Password reset for " + loggedInUser->getUsername() + ".");
                this->Close();
            }
        }
        else {
            // Self-change — old password required
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

    void ChangePasswordForm::btnCancel_Click(Object^ sender, EventArgs^ e)
    {
        this->Close();
    }
}