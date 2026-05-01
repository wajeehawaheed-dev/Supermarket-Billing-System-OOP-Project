#pragma once
#include "UserDB.h"
#include "Users.h"

namespace UserManagement
{

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class LoginForm : public Form
    {
    private:
        Label^ lblTitle;
        Label^ lblUsername;
        Label^ lblPassword;
        Label^ lblError;
        TextBox^ txtUsername;
        TextBox^ txtPassword;
        Button^ btnLogin;

    public:
        LoginForm();

    private:
        void InitializeComponent();
        void btnLogin_Click(Object^ sender , EventArgs^ e);
    };
}