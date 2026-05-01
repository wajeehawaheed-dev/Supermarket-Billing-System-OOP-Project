#pragma once
#include "Users.h"

namespace UserManagement
{

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    ref class LoginForm;

    public ref class MainMenuForm : public Form
    {
    private:
        User^ loggedInUser;
        Label^ lblWelcome;
        Label^ lblRole;
        Panel^ adminPanel;
        Button^ btnManageUsers;
        Button^ btnChangePassword;
        Button^ btnLogout;

    public:
        MainMenuForm(User^ user);

    private:
        void InitializeComponent();
        void setupForRole();
        void btnManageUsers_Click(Object^ sender , EventArgs^ e);
        void btnChangePassword_Click(Object^ sender , EventArgs^ e);
        void btnLogout_Click(Object^ sender , EventArgs^ e);
    };
}