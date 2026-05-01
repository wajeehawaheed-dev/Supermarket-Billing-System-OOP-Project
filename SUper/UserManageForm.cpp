#include "UserManageForm.h"

namespace UserManagement
{

    CreateUserForm::CreateUserForm()
    {
        InitializeComponent();
    }

    void CreateUserForm::InitializeComponent()
    {
        this->Text = "Create New User";
        this->Size = System::Drawing::Size(380 , 430);
        this->StartPosition = FormStartPosition::CenterParent;
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->MaximizeBox = false;
        this->BackColor = System::Drawing::Color::White;

        lblTitle = gcnew System::Windows::Forms::Label();
        lblTitle->Text = "Create New User";
        lblTitle->Font = gcnew System::Drawing::Font("Segoe UI" , 13 , System::Drawing::FontStyle::Bold);
        lblTitle->Location = System::Drawing::Point(30 , 20);
        lblTitle->Size = System::Drawing::Size(300 , 28);

        lblUsername = gcnew System::Windows::Forms::Label();
        lblUsername->Text = "Username";
        lblUsername->Location = System::Drawing::Point(30 , 70);
        lblUsername->Size = System::Drawing::Size(100 , 20);

        txtUsername = gcnew System::Windows::Forms::TextBox();
        txtUsername->Location = System::Drawing::Point(30 , 92);
        txtUsername->Size = System::Drawing::Size(300 , 25);

        lblPassword = gcnew System::Windows::Forms::Label();
        lblPassword->Text = "Password";
        lblPassword->Location = System::Drawing::Point(30 , 130);
        lblPassword->Size = System::Drawing::Size(100 , 20);

        txtPassword = gcnew System::Windows::Forms::TextBox();
        txtPassword->Location = System::Drawing::Point(30 , 152);
        txtPassword->Size = System::Drawing::Size(300 , 25);
        txtPassword->PasswordChar = '*';

        lblConfirm = gcnew System::Windows::Forms::Label();
        lblConfirm->Text = "Confirm Password";
        lblConfirm->Location = System::Drawing::Point(30 , 190);
        lblConfirm->Size = System::Drawing::Size(150 , 20);

        txtConfirm = gcnew System::Windows::Forms::TextBox();
        txtConfirm->Location = System::Drawing::Point(30 , 212);
        txtConfirm->Size = System::Drawing::Size(300 , 25);
        txtConfirm->PasswordChar = '*';

        lblRole = gcnew System::Windows::Forms::Label();
        lblRole->Text = "Role";
        lblRole->Location = System::Drawing::Point(30 , 250);
        lblRole->Size = System::Drawing::Size(100 , 20);

        cmbRole = gcnew System::Windows::Forms::ComboBox();
        cmbRole->Location = System::Drawing::Point(30 , 272);
        cmbRole->Size = System::Drawing::Size(300 , 25);
        cmbRole->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
        cmbRole->Items->Add("Cashier");
        cmbRole->Items->Add("Admin");
        cmbRole->SelectedIndex = 0;

        lblError = gcnew System::Windows::Forms::Label();
        lblError->Text = "";
        lblError->ForeColor = System::Drawing::Color::Red;
        lblError->Location = System::Drawing::Point(30 , 308);
        lblError->Size = System::Drawing::Size(300 , 20);

        btnCreate = gcnew System::Windows::Forms::Button();
        btnCreate->Text = "Create";
        btnCreate->Size = System::Drawing::Size(140 , 38);
        btnCreate->Location = System::Drawing::Point(30 , 340);
        btnCreate->BackColor = System::Drawing::Color::FromArgb(0 , 120 , 215);
        btnCreate->ForeColor = System::Drawing::Color::White;
        btnCreate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnCreate->Click += gcnew System::EventHandler(this , &CreateUserForm::btnCreate_Click);

        btnCancel = gcnew System::Windows::Forms::Button();
        btnCancel->Text = "Cancel";
        btnCancel->Size = System::Drawing::Size(140 , 38);
        btnCancel->Location = System::Drawing::Point(190 , 340);
        btnCancel->BackColor = System::Drawing::Color::FromArgb(150 , 150 , 150);
        btnCancel->ForeColor = System::Drawing::Color::White;
        btnCancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnCancel->Click += gcnew System::EventHandler(this , &CreateUserForm::btnCancel_Click);

        this->Controls->Add(lblTitle);
        this->Controls->Add(lblUsername);
        this->Controls->Add(txtUsername);
        this->Controls->Add(lblPassword);
        this->Controls->Add(txtPassword);
        this->Controls->Add(lblConfirm);
        this->Controls->Add(txtConfirm);
        this->Controls->Add(lblRole);
        this->Controls->Add(cmbRole);
        this->Controls->Add(lblError);
        this->Controls->Add(btnCreate);
        this->Controls->Add(btnCancel);
    }

    void CreateUserForm::btnCreate_Click(Object^ sender , EventArgs^ e)
    {
        String^ username = txtUsername->Text->Trim();
        String^ password = txtPassword->Text->Trim();
        String^ confirm = txtConfirm->Text->Trim();
        String^ role = cmbRole->SelectedItem->ToString();

        if ( username == "" || password == "" || confirm == "" ) {
            lblError->Text = "All fields are required.";
            return;
        }
        User^ temp = gcnew User();
        if ( !temp->Passwordvalidation(password) ) {
            lblError->Text = "Min 8 characters and 1 number required.";
            return;
        }
        if ( password != confirm ) {
            lblError->Text = "Passwords do not match.";
            return;
        }
        if ( UserDB::createUser(username , password , role) ) {
            MessageBox::Show("User created successfully.");
            this->Close();
        }
    }

    void CreateUserForm::btnCancel_Click(Object^ sender , EventArgs^ e)
    {
        this->Close();
    }

    UserManagementForm::UserManagementForm(User^ user)
    {
        loggedInUser = user;
        InitializeComponent();
        loadUsers();
    }

    void UserManagementForm::InitializeComponent()
    {
        this->Text = "User Management";
        this->Size = System::Drawing::Size(750 , 520);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->BackColor = System::Drawing::Color::White;

        lblTitle = gcnew System::Windows::Forms::Label();
        lblTitle->Text = "Manage Users";
        lblTitle->Font = gcnew System::Drawing::Font("Segoe UI" , 14 , System::Drawing::FontStyle::Bold);
        lblTitle->Location = System::Drawing::Point(20 , 15);
        lblTitle->Size = System::Drawing::Size(300 , 30);

        dgvUsers = gcnew System::Windows::Forms::DataGridView();
        dgvUsers->Location = System::Drawing::Point(20 , 60);
        dgvUsers->Size = System::Drawing::Size(700 , 340);
        dgvUsers->ReadOnly = true;
        dgvUsers->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
        dgvUsers->MultiSelect = false;
        dgvUsers->AllowUserToAddRows = false;
        dgvUsers->BackgroundColor = System::Drawing::Color::White;
        dgvUsers->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;

        btnCreateUser = gcnew System::Windows::Forms::Button();
        btnCreateUser->Text = "Create User";
        btnCreateUser->Size = System::Drawing::Size(130 , 38);
        btnCreateUser->Location = System::Drawing::Point(20 , 420);
        btnCreateUser->BackColor = System::Drawing::Color::FromArgb(0 , 120 , 215);
        btnCreateUser->ForeColor = System::Drawing::Color::White;
        btnCreateUser->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnCreateUser->Click += gcnew System::EventHandler(this , &UserManagementForm::btnCreateUser_Click);

        btnDeleteUser = gcnew System::Windows::Forms::Button();
        btnDeleteUser->Text = "Delete User";
        btnDeleteUser->Size = System::Drawing::Size(130 , 38);
        btnDeleteUser->Location = System::Drawing::Point(165 , 420);
        btnDeleteUser->BackColor = System::Drawing::Color::FromArgb(200 , 50 , 50);
        btnDeleteUser->ForeColor = System::Drawing::Color::White;
        btnDeleteUser->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnDeleteUser->Click += gcnew System::EventHandler(this , &UserManagementForm::btnDeleteUser_Click);

        btnBlockUser = gcnew System::Windows::Forms::Button();
        btnBlockUser->Text = "Block User";
        btnBlockUser->Size = System::Drawing::Size(130 , 38);
        btnBlockUser->Location = System::Drawing::Point(310 , 420);
        btnBlockUser->BackColor = System::Drawing::Color::FromArgb(200 , 140 , 0);
        btnBlockUser->ForeColor = System::Drawing::Color::White;
        btnBlockUser->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnBlockUser->Click += gcnew System::EventHandler(this , &UserManagementForm::btnBlockUser_Click);

        btnUnblockUser = gcnew System::Windows::Forms::Button();
        btnUnblockUser->Text = "Unblock User";
        btnUnblockUser->Size = System::Drawing::Size(130 , 38);
        btnUnblockUser->Location = System::Drawing::Point(455 , 420);
        btnUnblockUser->BackColor = System::Drawing::Color::FromArgb(0 , 160 , 80);
        btnUnblockUser->ForeColor = System::Drawing::Color::White;
        btnUnblockUser->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnUnblockUser->Click += gcnew System::EventHandler(this , &UserManagementForm::btnUnblockUser_Click);

        btnRefresh = gcnew System::Windows::Forms::Button();
        btnRefresh->Text = "Refresh";
        btnRefresh->Size = System::Drawing::Size(130 , 38);
        btnRefresh->Location = System::Drawing::Point(590 , 420);
        btnRefresh->BackColor = System::Drawing::Color::FromArgb(80 , 80 , 80);
        btnRefresh->ForeColor = System::Drawing::Color::White;
        btnRefresh->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnRefresh->Click += gcnew System::EventHandler(this , &UserManagementForm::btnRefresh_Click);

        this->Controls->Add(lblTitle);
        this->Controls->Add(dgvUsers);
        this->Controls->Add(btnCreateUser);
        this->Controls->Add(btnDeleteUser);
        this->Controls->Add(btnBlockUser);
        this->Controls->Add(btnUnblockUser);
        this->Controls->Add(btnRefresh);
    }

    void UserManagementForm::loadUsers()
    {
        dgvUsers->Rows->Clear();
        dgvUsers->Columns->Clear();
        dgvUsers->Columns->Add("UserID" , "ID");
        dgvUsers->Columns->Add("Username" , "Username");
        dgvUsers->Columns->Add("Role" , "Role");
        dgvUsers->Columns->Add("Status" , "Status");

        List<User^>^ users = UserDB::getAllUsers();
        for each ( User ^ u in users ) {
            dgvUsers->Rows->Add(
                u->getUserID() ,
                u->getUsername() ,
                u->getRole() ,
                u->getIsActive() ? "Active" : "Blocked"
            );
        }
    }

    void UserManagementForm::btnCreateUser_Click(Object^ sender , EventArgs^ e)
    {
        CreateUserForm^ form = gcnew CreateUserForm();
        form->ShowDialog();
        loadUsers();
    }

    void UserManagementForm::btnDeleteUser_Click(Object^ sender , EventArgs^ e)
    {
        int id = getSelectedUserID();
        if ( id == -1 ) return;
        if ( id == loggedInUser->getUserID() ) {
            MessageBox::Show("You cannot delete your own account.");
            return;
        }
        String^ uname = getSelectedUsername();
        System::Windows::Forms::DialogResult result = MessageBox::Show(
            "Delete user '" + uname + "'?" ,
            "Confirm Delete" ,
            MessageBoxButtons::YesNo ,
            MessageBoxIcon::Warning
        );
        if ( result == System::Windows::Forms::DialogResult::Yes ) {
            if ( UserDB::deleteUser(id) )
                MessageBox::Show("User deleted.");
            loadUsers();
        }
    }

    void UserManagementForm::btnBlockUser_Click(Object^ sender , EventArgs^ e)
    {
        int id = getSelectedUserID();
        if ( id == -1 ) return;
        if ( id == loggedInUser->getUserID() ) {
            MessageBox::Show("You cannot block your own account.");
            return;
        }
        if ( UserDB::setUserActive(id , false) )
            MessageBox::Show("User blocked.");
        loadUsers();
    }

    void UserManagementForm::btnUnblockUser_Click(Object^ sender , EventArgs^ e)
    {
        int id = getSelectedUserID();
        if ( id == -1 ) return;
        if ( UserDB::setUserActive(id , true) )
            MessageBox::Show("User unblocked.");
        loadUsers();
    }

    void UserManagementForm::btnRefresh_Click(Object^ sender , EventArgs^ e)
    {
        loadUsers();
    }
}