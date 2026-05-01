#pragma once
#include "Users.h"
#include "UserDB.h"

namespace SUper
{

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class ChangePasswordForm : public Form
    {
    private:
        User^ loggedInUser;
        bool adminResetMode;
        Label^ lblTitle;
        Label^ lblOld;
        Label^ lblNew;
        Label^ lblConfirm;
        Label^ lblError;
        TextBox^ txtOld;
        TextBox^ txtNew;
        TextBox^ txtConfirm;
        Button^ btnChange;
        Button^ btnCancel;

    public:
        ChangePasswordForm(User^ user);                       // self-change (old password required)
        ChangePasswordForm(User^ user, bool adminReset);      // admin resetting another user (no old password)

    private:
        void InitializeComponent();
        void btnChange_Click(Object^ sender, EventArgs^ e);
        void btnCancel_Click(Object^ sender, EventArgs^ e);
    };
}