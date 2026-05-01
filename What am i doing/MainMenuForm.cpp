#include "MainMenuForm.h"
#include "UserManageForm.h"
#include "ChangePasswordForm.h"
#include "LoginForm.h"

namespace UserManagement
{

    MainMenuForm::MainMenuForm(User^ user)
    {
        loggedInUser = user;
        InitializeComponent();
        setupForRole();
    }

    void MainMenuForm::InitializeComponent()
    {
        this->Text = "Main Menu";
        this->Size = System::Drawing::Size(450 , 400);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
        this->MaximizeBox = false;
        this->BackColor = System::Drawing::Color::White;

        lblWelcome = gcnew System::Windows::Forms::Label();
        lblWelcome->Font = gcnew System::Drawing::Font("Segoe UI" , 14 , System::Drawing::FontStyle::Bold);
        lblWelcome->Location = System::Drawing::Point(50 , 30);
        lblWelcome->Size = System::Drawing::Size(350 , 30);

        lblRole = gcnew System::Windows::Forms::Label();
        lblRole->Font = gcnew System::Drawing::Font("Segoe UI" , 10);
        lblRole->ForeColor = System::Drawing::Color::Gray;
        lblRole->Location = System::Drawing::Point(50 , 65);
        lblRole->Size = System::Drawing::Size(350 , 20);

        adminPanel = gcnew System::Windows::Forms::Panel();
        adminPanel->Location = System::Drawing::Point(50 , 110);
        adminPanel->Size = System::Drawing::Size(340 , 55);
        adminPanel->Visible = false;

        btnManageUsers = gcnew System::Windows::Forms::Button();
        btnManageUsers->Text = "Manage Users";
        btnManageUsers->Size = System::Drawing::Size(340 , 45);
        btnManageUsers->Location = System::Drawing::Point(0 , 0);
        btnManageUsers->BackColor = System::Drawing::Color::FromArgb(0 , 120 , 215);
        btnManageUsers->ForeColor = System::Drawing::Color::White;
        btnManageUsers->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnManageUsers->Font = gcnew System::Drawing::Font("Segoe UI" , 10);
        btnManageUsers->Click += gcnew System::EventHandler(this , &MainMenuForm::btnManageUsers_Click);
        adminPanel->Controls->Add(btnManageUsers);

        btnChangePassword = gcnew System::Windows::Forms::Button();
        btnChangePassword->Text = "Change Password";
        btnChangePassword->Size = System::Drawing::Size(340 , 45);
        btnChangePassword->BackColor = System::Drawing::Color::FromArgb(0 , 180 , 100);
        btnChangePassword->ForeColor = System::Drawing::Color::White;
        btnChangePassword->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnChangePassword->Font = gcnew System::Drawing::Font("Segoe UI" , 10);
        btnChangePassword->Click += gcnew System::EventHandler(this , &MainMenuForm::btnChangePassword_Click);

        btnLogout = gcnew System::Windows::Forms::Button();
        btnLogout->Text = "Logout";
        btnLogout->Size = System::Drawing::Size(340 , 45);
        btnLogout->BackColor = System::Drawing::Color::FromArgb(200 , 50 , 50);
        btnLogout->ForeColor = System::Drawing::Color::White;
        btnLogout->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnLogout->Font = gcnew System::Drawing::Font("Segoe UI" , 10);
        btnLogout->Click += gcnew System::EventHandler(this , &MainMenuForm::btnLogout_Click);

        this->Controls->Add(lblWelcome);
        this->Controls->Add(lblRole);
        this->Controls->Add(adminPanel);
        this->Controls->Add(btnChangePassword);
        this->Controls->Add(btnLogout);
    }

    void MainMenuForm::setupForRole()
    {
        lblWelcome->Text = "Hello, " + loggedInUser->getUsername() + "!";
        lblRole->Text = "Role: " + loggedInUser->getRole();
        if ( loggedInUser->isAdmin() ) {
            adminPanel->Visible = true;
            btnChangePassword->Location = System::Drawing::Point(50 , 185);
            btnLogout->Location = System::Drawing::Point(50 , 250);
        }
        else {
            adminPanel->Visible = false;
            btnChangePassword->Location = System::Drawing::Point(50 , 130);
            btnLogout->Location = System::Drawing::Point(50 , 195);
        }
    }

    void MainMenuForm::btnManageUsers_Click(Object^ sender , EventArgs^ e)
    {
        UserManagementForm^ form = gcnew UserManagementForm(loggedInUser);
        form->Show();
    }

    void MainMenuForm::btnChangePassword_Click(Object^ sender , EventArgs^ e)
    {
        ChangePasswordForm^ form = gcnew ChangePasswordForm(loggedInUser);
        form->ShowDialog();
    }

    void MainMenuForm::btnLogout_Click(Object^ sender , EventArgs^ e)
    {
        System::Windows::Forms::DialogResult result = MessageBox::Show(
            "Are you sure you want to logout?" ,
            "Logout" ,
            MessageBoxButtons::YesNo ,
            MessageBoxIcon::Question
        );
        if ( result == System::Windows::Forms::DialogResult::Yes ) {
            LoginForm^ login = gcnew LoginForm();
            login->Show();
            this->Close();
        }
    }
}