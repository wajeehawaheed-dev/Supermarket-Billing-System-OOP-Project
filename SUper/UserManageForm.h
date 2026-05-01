#pragma once
#include "Users.h"
#include "UserDB.h"
#include "ChangePasswordForm.h"

namespace SUper
{

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    public ref class CreateUserForm : public Form
    {
    private:
        Label^ lblTitle;
        Label^ lblUsername;
        Label^ lblPassword;
        Label^ lblConfirm;
        Label^ lblRole;
        Label^ lblError;
        TextBox^ txtUsername;
        TextBox^ txtPassword;
        TextBox^ txtConfirm;
        ComboBox^ cmbRole;
        Button^ btnCreate;
        Button^ btnCancel;

    public:
        CreateUserForm();

    private:
        void InitializeComponent();
        void btnCreate_Click(Object^ sender , EventArgs^ e);
        void btnCancel_Click(Object^ sender , EventArgs^ e);
    };

    public ref class UserManagementForm : public Form
    {
    private:
        User^ loggedInUser;
        System::Windows::Forms::DataGridView^ dgvUsers;
        Button^ btnCreateUser;
        Button^ btnDeleteUser;
        Button^ btnBlockUser;
        Button^ btnUnblockUser;
        Button^ btnRefresh;
        Label^ lblTitle;

    public:
        UserManagementForm(User^ user);

    private:
        void InitializeComponent();
        void loadUsers();

        int getSelectedUserID()
        {
            if ( dgvUsers->SelectedRows->Count == 0 ) {
                MessageBox::Show("Please select a user first.");
                return -1;
            }
            return Int32::Parse(dgvUsers->Rows [dgvUsers->CurrentRow->Index]->Cells [0]->Value->ToString());
        }

        String^ getSelectedUsername()
        {
            if ( dgvUsers->SelectedRows->Count == 0 ) return "";
            return dgvUsers->Rows [dgvUsers->CurrentRow->Index]->Cells [1]->Value->ToString();
        }

        void btnCreateUser_Click(Object^ sender , EventArgs^ e);
        void btnChangePassword_Click(Object^ sender, EventArgs^ e);
        void btnDeleteUser_Click(Object^ sender , EventArgs^ e);
        void btnBlockUser_Click(Object^ sender , EventArgs^ e);
        void btnUnblockUser_Click(Object^ sender , EventArgs^ e);
        void btnRefresh_Click(Object^ sender , EventArgs^ e);
    };
}