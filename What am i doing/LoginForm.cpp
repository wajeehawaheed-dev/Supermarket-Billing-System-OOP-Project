#include "LoginForm.h"
#include "MainMenuForm.h"

namespace UserManagement
{

    LoginForm::LoginForm()
    {
        InitializeComponent();
        UserDB::defAdmin();
    }

    void LoginForm::InitializeComponent()
    {
        this->Text = "Supermarket Management System";
        this->Size = System::Drawing::Size(400 , 350);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
        this->MaximizeBox = false;
        this->BackColor = System::Drawing::Color::White;

        lblTitle = gcnew System::Windows::Forms::Label();
        lblTitle->Text = "Welcome";
        lblTitle->Font = gcnew System::Drawing::Font("Segoe UI" , 16 , System::Drawing::FontStyle::Bold);
        lblTitle->Location = System::Drawing::Point(100 , 30);
        lblTitle->Size = System::Drawing::Size(220 , 35);

        lblUsername = gcnew System::Windows::Forms::Label();
        lblUsername->Text = "Username";
        lblUsername->Location = System::Drawing::Point(80 , 100);
        lblUsername->Size = System::Drawing::Size(80 , 20);

        txtUsername = gcnew System::Windows::Forms::TextBox();
        txtUsername->Location = System::Drawing::Point(80 , 125);
        txtUsername->Size = System::Drawing::Size(220 , 25);

        lblPassword = gcnew System::Windows::Forms::Label();
        lblPassword->Text = "Password";
        lblPassword->Location = System::Drawing::Point(80 , 165);
        lblPassword->Size = System::Drawing::Size(80 , 20);

        txtPassword = gcnew System::Windows::Forms::TextBox();
        txtPassword->Location = System::Drawing::Point(80 , 190);
        txtPassword->Size = System::Drawing::Size(220 , 25);
        txtPassword->PasswordChar = '*';

        btnLogin = gcnew System::Windows::Forms::Button();
        btnLogin->Text = "Login";
        btnLogin->Location = System::Drawing::Point(80 , 235);
        btnLogin->Size = System::Drawing::Size(220 , 35);
        btnLogin->BackColor = System::Drawing::Color::FromArgb(0 , 120 , 215);
        btnLogin->ForeColor = System::Drawing::Color::White;
        btnLogin->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnLogin->Click += gcnew System::EventHandler(this , &LoginForm::btnLogin_Click);

        lblError = gcnew System::Windows::Forms::Label();
        lblError->Text = "";
        lblError->ForeColor = System::Drawing::Color::Red;
        lblError->Location = System::Drawing::Point(80 , 280);
        lblError->Size = System::Drawing::Size(220 , 20);

        this->Controls->Add(lblTitle);
        this->Controls->Add(lblUsername);
        this->Controls->Add(txtUsername);
        this->Controls->Add(lblPassword);
        this->Controls->Add(txtPassword);
        this->Controls->Add(btnLogin);
        this->Controls->Add(lblError);
    }

    void LoginForm::btnLogin_Click(Object^ sender , EventArgs^ e)
    {
        String^ username = txtUsername->Text->Trim();
        String^ password = txtPassword->Text->Trim();

        if ( username == "" || password == "" ) {
            lblError->Text = "Please fill in all fields.";
            return;
        }

        User^ user = UserDB::loginUser(username , password);
        if ( user == nullptr ) {
            lblError->Text = "Invalid username or password.";
            return;
        }

        MainMenuForm^ menu = gcnew MainMenuForm(user);
        menu->Show();
        this->Hide();
    }
}