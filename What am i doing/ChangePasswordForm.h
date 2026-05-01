#pragma once
#include "Users.h"
#include "UserDB.h"

namespace UserManagement
{

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class ChangePasswordForm : public Form
    {
    private:
        User^ loggedInUser;
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
        ChangePasswordForm(User^ user);

    private:
        void InitializeComponent();
        void btnChange_Click(Object^ sender , EventArgs^ e);
        void btnCancel_Click(Object^ sender , EventArgs^ e);
    };
}