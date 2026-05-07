#include "UserManageForm.h"

namespace SUper
{
    using namespace System::Drawing::Drawing2D;

    // ===== Brand palette (file-local helpers) =====
    static System::Drawing::Color UMF_NAVY() { return System::Drawing::Color::FromArgb(30, 58, 138); }
    static System::Drawing::Color UMF_NAVY_HOVER() { return System::Drawing::Color::FromArgb(45, 75, 165); }
    static System::Drawing::Color UMF_GREEN() { return System::Drawing::Color::FromArgb(34, 197, 94); }
    static System::Drawing::Color UMF_GREEN_HOVER() { return System::Drawing::Color::FromArgb(22, 163, 74); }
    static System::Drawing::Color UMF_RED() { return System::Drawing::Color::FromArgb(220, 38, 38); }
    static System::Drawing::Color UMF_RED_HOVER() { return System::Drawing::Color::FromArgb(185, 28, 28); }
    static System::Drawing::Color UMF_AMBER() { return System::Drawing::Color::FromArgb(217, 119, 6); }
    static System::Drawing::Color UMF_AMBER_HOVER() { return System::Drawing::Color::FromArgb(180, 83, 9); }
    static System::Drawing::Color UMF_PURPLE() { return System::Drawing::Color::FromArgb(124, 58, 237); }
    static System::Drawing::Color UMF_PURPLE_HOVER() { return System::Drawing::Color::FromArgb(91, 33, 182); }
    static System::Drawing::Color UMF_BG_LIGHT() { return System::Drawing::Color::FromArgb(248, 250, 252); }
    static System::Drawing::Color UMF_BORDER() { return System::Drawing::Color::FromArgb(229, 231, 235); }
    static System::Drawing::Color UMF_TEXT_DARK() { return System::Drawing::Color::FromArgb(30, 41, 59); }
    static System::Drawing::Color UMF_TEXT_MUTED() { return System::Drawing::Color::FromArgb(100, 116, 139); }

    // ===== Round-corner helper =====
    static void RoundIt(System::Windows::Forms::Control^ ctrl, int radius)
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

    // ============================================================
    //                      CREATE USER FORM
    // ============================================================

    CreateUserForm::CreateUserForm()
    {
        InitializeComponent();
    }

    void CreateUserForm::InitializeComponent()
    {
        this->Text = "Create New User";
        this->ClientSize = System::Drawing::Size(440, 640);
        this->StartPosition = FormStartPosition::CenterParent;
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
        this->BackColor = System::Drawing::Color::White;
        this->DoubleBuffered = true;

        // ----- Title -----
        lblTitle = gcnew System::Windows::Forms::Label();
        lblTitle->Text = "Create New User";
        lblTitle->Font = gcnew System::Drawing::Font("Segoe UI", 16, System::Drawing::FontStyle::Bold);
        lblTitle->ForeColor = UMF_TEXT_DARK();
        lblTitle->Location = System::Drawing::Point(30, 25);
        lblTitle->AutoSize = true;

        Label^ lblSub = gcnew System::Windows::Forms::Label();
        lblSub->Text = "Add a new cashier or admin to the system";
        lblSub->Font = gcnew System::Drawing::Font("Segoe UI", 9);
        lblSub->ForeColor = UMF_TEXT_MUTED();
        lblSub->Location = System::Drawing::Point(32, 55);
        lblSub->AutoSize = true;

        // ----- Close X -----
        Label^ btnTopClose = gcnew System::Windows::Forms::Label();
        btnTopClose->Text = L"\u2715";
        btnTopClose->Font = gcnew System::Drawing::Font("Segoe UI", 12, System::Drawing::FontStyle::Bold);
        btnTopClose->ForeColor = UMF_TEXT_MUTED();
        btnTopClose->BackColor = System::Drawing::Color::Transparent;
        btnTopClose->Location = System::Drawing::Point(390, 22);
        btnTopClose->Size = System::Drawing::Size(35, 30);
        btnTopClose->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
        btnTopClose->Cursor = System::Windows::Forms::Cursors::Hand;
        btnTopClose->Click += gcnew System::EventHandler(this, &CreateUserForm::btnCancel_Click);
        
        // ----- USERNAME -----
        lblUsername = gcnew System::Windows::Forms::Label();
        lblUsername->Text = "USERNAME";
        lblUsername->Font = gcnew System::Drawing::Font("Segoe UI", 8.5F, System::Drawing::FontStyle::Bold);
        lblUsername->ForeColor = UMF_TEXT_MUTED();
        lblUsername->Location = System::Drawing::Point(35, 100);
        lblUsername->AutoSize = true;

        txtUsername = gcnew System::Windows::Forms::TextBox();
        txtUsername->BorderStyle = System::Windows::Forms::BorderStyle::None;
        txtUsername->Font = gcnew System::Drawing::Font("Segoe UI", 11);
        txtUsername->ForeColor = UMF_TEXT_DARK();
        txtUsername->Location = System::Drawing::Point(35, 122);
        txtUsername->Size = System::Drawing::Size(370, 22);

        Panel^ pnlUserLine = gcnew System::Windows::Forms::Panel();
        pnlUserLine->Location = System::Drawing::Point(35, 149);
        pnlUserLine->Size = System::Drawing::Size(370, 2);
        pnlUserLine->BackColor = UMF_BORDER();

        // ----- PASSWORD -----
        lblPassword = gcnew System::Windows::Forms::Label();
        lblPassword->Text = "PASSWORD";
        lblPassword->Font = gcnew System::Drawing::Font("Segoe UI", 8.5F, System::Drawing::FontStyle::Bold);
        lblPassword->ForeColor = UMF_TEXT_MUTED();
        lblPassword->Location = System::Drawing::Point(35, 170);
        lblPassword->AutoSize = true;

        txtPassword = gcnew System::Windows::Forms::TextBox();
        txtPassword->BorderStyle = System::Windows::Forms::BorderStyle::None;
        txtPassword->Font = gcnew System::Drawing::Font("Segoe UI", 11);
        txtPassword->ForeColor = UMF_TEXT_DARK();
        txtPassword->Location = System::Drawing::Point(35, 192);
        txtPassword->Size = System::Drawing::Size(370, 22);
        txtPassword->PasswordChar = L'\u25CF';

        Panel^ pnlPwdLine = gcnew System::Windows::Forms::Panel();
        pnlPwdLine->Location = System::Drawing::Point(35, 219);
        pnlPwdLine->Size = System::Drawing::Size(370, 2);
        pnlPwdLine->BackColor = UMF_BORDER();

        Label^ lblPwdHint = gcnew System::Windows::Forms::Label();
        lblPwdHint->Text = "Min 8 characters with at least 1 number";
        lblPwdHint->Font = gcnew System::Drawing::Font("Segoe UI", 8);
        lblPwdHint->ForeColor = UMF_TEXT_MUTED();
        lblPwdHint->Location = System::Drawing::Point(35, 225);
        lblPwdHint->AutoSize = true;

        // ----- CONFIRM -----
        lblConfirm = gcnew System::Windows::Forms::Label();
        lblConfirm->Text = "CONFIRM PASSWORD";
        lblConfirm->Font = gcnew System::Drawing::Font("Segoe UI", 8.5F, System::Drawing::FontStyle::Bold);
        lblConfirm->ForeColor = UMF_TEXT_MUTED();
        lblConfirm->Location = System::Drawing::Point(35, 260);
        lblConfirm->AutoSize = true;

        txtConfirm = gcnew System::Windows::Forms::TextBox();
        txtConfirm->BorderStyle = System::Windows::Forms::BorderStyle::None;
        txtConfirm->Font = gcnew System::Drawing::Font("Segoe UI", 11);
        txtConfirm->ForeColor = UMF_TEXT_DARK();
        txtConfirm->Location = System::Drawing::Point(35, 282);
        txtConfirm->Size = System::Drawing::Size(370, 22);
        txtConfirm->PasswordChar = L'\u25CF';

        Panel^ pnlConfirmLine = gcnew System::Windows::Forms::Panel();
        pnlConfirmLine->Location = System::Drawing::Point(35, 309);
        pnlConfirmLine->Size = System::Drawing::Size(370, 2);
        pnlConfirmLine->BackColor = UMF_BORDER();

        // ----- ROLE -----
        lblRole = gcnew System::Windows::Forms::Label();
        lblRole->Text = "ROLE";
        lblRole->Font = gcnew System::Drawing::Font("Segoe UI", 8.5F, System::Drawing::FontStyle::Bold);
        lblRole->ForeColor = UMF_TEXT_MUTED();
        lblRole->Location = System::Drawing::Point(35, 335);
        lblRole->AutoSize = true;

        cmbRole = gcnew System::Windows::Forms::ComboBox();
        cmbRole->Font = gcnew System::Drawing::Font("Segoe UI", 10.5F);
        cmbRole->ForeColor = UMF_TEXT_DARK();
        cmbRole->Location = System::Drawing::Point(35, 358);
        cmbRole->Size = System::Drawing::Size(370, 28);
        cmbRole->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        cmbRole->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
        cmbRole->Items->Add("Cashier");
        cmbRole->Items->Add("Admin");
        cmbRole->SelectedIndex = 0;

        // ----- ERROR -----
        lblError = gcnew System::Windows::Forms::Label();
        lblError->Text = "";
        lblError->Font = gcnew System::Drawing::Font("Segoe UI", 9);
        lblError->ForeColor = UMF_RED();
        lblError->Location = System::Drawing::Point(35, 410);
        lblError->Size = System::Drawing::Size(370, 20);

        // ----- BUTTONS -----
        btnCreate = gcnew System::Windows::Forms::Button();
        btnCreate->Text = "Create User";
        btnCreate->Font = gcnew System::Drawing::Font("Segoe UI", 10, System::Drawing::FontStyle::Bold);
        btnCreate->Size = System::Drawing::Size(220, 44);
        btnCreate->Location = System::Drawing::Point(185, 555);
        btnCreate->BackColor = UMF_GREEN();
        btnCreate->ForeColor = System::Drawing::Color::White;
        btnCreate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnCreate->FlatAppearance->BorderSize = 0;
        btnCreate->Cursor = System::Windows::Forms::Cursors::Hand;
        btnCreate->Click += gcnew System::EventHandler(this, &CreateUserForm::btnCreate_Click);

        btnCancel = gcnew System::Windows::Forms::Button();
        btnCancel->Text = "Cancel";
        btnCancel->Font = gcnew System::Drawing::Font("Segoe UI", 10);
        btnCancel->Size = System::Drawing::Size(140, 44);
        btnCancel->Location = System::Drawing::Point(35, 555);
        btnCancel->BackColor = System::Drawing::Color::White;
        btnCancel->ForeColor = UMF_TEXT_DARK();
        btnCancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnCancel->FlatAppearance->BorderSize = 1;
        btnCancel->FlatAppearance->BorderColor = UMF_BORDER();
        btnCancel->Cursor = System::Windows::Forms::Cursors::Hand;
        btnCancel->Click += gcnew System::EventHandler(this, &CreateUserForm::btnCancel_Click);

        // ----- Add controls -----
        this->Controls->Add(lblTitle);
        this->Controls->Add(lblSub);
        this->Controls->Add(btnTopClose);
        this->Controls->Add(lblUsername);
        this->Controls->Add(txtUsername);
        this->Controls->Add(pnlUserLine);
        this->Controls->Add(lblPassword);
        this->Controls->Add(txtPassword);
        this->Controls->Add(pnlPwdLine);
        this->Controls->Add(lblPwdHint);
        this->Controls->Add(lblConfirm);
        this->Controls->Add(txtConfirm);
        this->Controls->Add(pnlConfirmLine);
        this->Controls->Add(lblRole);
        this->Controls->Add(cmbRole);
        this->Controls->Add(lblError);
        this->Controls->Add(btnCreate);
        this->Controls->Add(btnCancel);

        // ----- Round corners -----
        RoundIt(btnCreate, 6);
        RoundIt(btnCancel, 6);

        
    }

    void CreateUserForm::btnCreate_Click(System::Object^ sender, System::EventArgs^ e)
    {
        String^ username = txtUsername->Text->Trim();
        String^ password = txtPassword->Text->Trim();
        String^ confirm = txtConfirm->Text->Trim();
        String^ role = cmbRole->SelectedItem->ToString();

        if (username == "" || password == "" || confirm == "") {
            lblError->Text = "All fields are required.";
            return;
        }
        User^ temp = gcnew User();
        if (!temp->Passwordvalidation(password)) {
            lblError->Text = "Min 8 characters and 1 number required.";
            return;
        }
        if (password != confirm) {
            lblError->Text = "Passwords do not match.";
            return;
        }
        if (UserDB::createUser(username, password, role)) {
            MessageBox::Show("User created successfully.");
            this->Close();
        }
    }

    void CreateUserForm::btnCancel_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->Close();
    }

    // ============================================================
    //                  USER MANAGEMENT FORM (LIST)
    // ============================================================

    UserManagementForm::UserManagementForm(User^ user)
    {
        loggedInUser = user;
        InitializeComponent();
        loadUsers();
    }

    void UserManagementForm::InitializeComponent()
    {
        this->Text = "User Management";
        this->ClientSize = System::Drawing::Size(1000, 620);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->BackColor = UMF_BG_LIGHT();
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
        this->DoubleBuffered = true;

        // ===== HEADER =====
        Panel^ pnlHeader = gcnew System::Windows::Forms::Panel();
        pnlHeader->Location = System::Drawing::Point(0, 0);
        pnlHeader->Size = System::Drawing::Size(1000, 80);
        pnlHeader->BackColor = System::Drawing::Color::White;

        lblTitle = gcnew System::Windows::Forms::Label();
        lblTitle->Text = "Manage Users";
        lblTitle->Font = gcnew System::Drawing::Font("Segoe UI", 18, System::Drawing::FontStyle::Bold);
        lblTitle->ForeColor = UMF_TEXT_DARK();
        lblTitle->BackColor = System::Drawing::Color::Transparent;
        lblTitle->Location = System::Drawing::Point(30, 18);
        lblTitle->AutoSize = true;

        Label^ lblSub = gcnew System::Windows::Forms::Label();
        lblSub->Text = "Create, block, or delete user accounts";
        lblSub->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F);
        lblSub->ForeColor = UMF_TEXT_MUTED();
        lblSub->BackColor = System::Drawing::Color::Transparent;
        lblSub->Location = System::Drawing::Point(32, 50);
        lblSub->AutoSize = true;

        Label^ btnTopClose = gcnew System::Windows::Forms::Label();
        btnTopClose->Text = L"\u2715";
        btnTopClose->Font = gcnew System::Drawing::Font("Segoe UI", 12, System::Drawing::FontStyle::Bold);
        btnTopClose->ForeColor = UMF_TEXT_MUTED();
        btnTopClose->BackColor = System::Drawing::Color::Transparent;
        btnTopClose->Location = System::Drawing::Point(948, 22);
        btnTopClose->Size = System::Drawing::Size(35, 35);
        btnTopClose->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
        btnTopClose->Cursor = System::Windows::Forms::Cursors::Hand;
        btnTopClose->Click += gcnew System::EventHandler(this, &UserManagementForm::btnTopClose_Click);

        pnlHeader->Controls->Add(lblTitle);
        pnlHeader->Controls->Add(lblSub);
        pnlHeader->Controls->Add(btnTopClose);

        // ===== GRID CARD =====
        Panel^ pnlGrid = gcnew System::Windows::Forms::Panel();
        pnlGrid->Location = System::Drawing::Point(20, 95);
        pnlGrid->Size = System::Drawing::Size(960, 390);
        pnlGrid->BackColor = System::Drawing::Color::White;
        pnlGrid->Padding = System::Windows::Forms::Padding(1);

        dgvUsers = gcnew System::Windows::Forms::DataGridView();
        dgvUsers->Dock = System::Windows::Forms::DockStyle::Fill;
        dgvUsers->ReadOnly = true;
        dgvUsers->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
        dgvUsers->MultiSelect = false;
        dgvUsers->AllowUserToAddRows = false;
        dgvUsers->AllowUserToResizeRows = false;
        dgvUsers->BackgroundColor = System::Drawing::Color::White;
        dgvUsers->BorderStyle = System::Windows::Forms::BorderStyle::None;
        dgvUsers->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::SingleHorizontal;
        dgvUsers->GridColor = UMF_BORDER();
        dgvUsers->RowHeadersVisible = false;
        dgvUsers->EnableHeadersVisualStyles = false;
        dgvUsers->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::None;
        dgvUsers->ColumnHeadersHeight = 45;
        dgvUsers->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
        dgvUsers->RowTemplate->Height = 38;
        dgvUsers->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;

        System::Windows::Forms::DataGridViewCellStyle^ hs = gcnew System::Windows::Forms::DataGridViewCellStyle();
        hs->BackColor = UMF_NAVY();
        hs->ForeColor = System::Drawing::Color::White;
        hs->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold);
        hs->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
        hs->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
        hs->SelectionBackColor = UMF_NAVY();
        hs->SelectionForeColor = System::Drawing::Color::White;
        dgvUsers->ColumnHeadersDefaultCellStyle = hs;

        System::Windows::Forms::DataGridViewCellStyle^ cs = gcnew System::Windows::Forms::DataGridViewCellStyle();
        cs->BackColor = System::Drawing::Color::White;
        cs->ForeColor = UMF_TEXT_DARK();
        cs->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F);
        cs->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
        cs->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
        cs->SelectionBackColor = System::Drawing::Color::FromArgb(219, 234, 254);
        cs->SelectionForeColor = UMF_TEXT_DARK();
        dgvUsers->DefaultCellStyle = cs;

        System::Windows::Forms::DataGridViewCellStyle^ as_ = gcnew System::Windows::Forms::DataGridViewCellStyle();
        as_->BackColor = UMF_BG_LIGHT();
        as_->ForeColor = UMF_TEXT_DARK();
        as_->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F);
        as_->Padding = System::Windows::Forms::Padding(10, 0, 10, 0);
        as_->SelectionBackColor = System::Drawing::Color::FromArgb(219, 234, 254);
        as_->SelectionForeColor = UMF_TEXT_DARK();
        dgvUsers->AlternatingRowsDefaultCellStyle = as_;

        dgvUsers->CellFormatting += gcnew System::Windows::Forms::DataGridViewCellFormattingEventHandler(
            this, &UserManagementForm::dgvUsers_CellFormatting);

        pnlGrid->Controls->Add(dgvUsers);

        // ===== ACTION BAR =====
        Panel^ pnlBottom = gcnew System::Windows::Forms::Panel();
        pnlBottom->Location = System::Drawing::Point(20, 505);
        pnlBottom->Size = System::Drawing::Size(960, 70);
        pnlBottom->BackColor = System::Drawing::Color::White;

        // Create User (primary, green)
        btnCreateUser = gcnew System::Windows::Forms::Button();
        btnCreateUser->Text = L"+  Create User";
        btnCreateUser->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold);
        btnCreateUser->Size = System::Drawing::Size(150, 38);
        btnCreateUser->Location = System::Drawing::Point(20, 16);
        btnCreateUser->BackColor = UMF_GREEN();
        btnCreateUser->ForeColor = System::Drawing::Color::White;
        btnCreateUser->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnCreateUser->FlatAppearance->BorderSize = 0;
        btnCreateUser->Cursor = System::Windows::Forms::Cursors::Hand;
        btnCreateUser->Click += gcnew System::EventHandler(this, &UserManagementForm::btnCreateUser_Click);

        // Block User (amber)
        btnBlockUser = gcnew System::Windows::Forms::Button();
        btnBlockUser->Text = "Block";
        btnBlockUser->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold);
        btnBlockUser->Size = System::Drawing::Size(100, 38);
        btnBlockUser->Location = System::Drawing::Point(185, 16);
        btnBlockUser->BackColor = UMF_AMBER();
        btnBlockUser->ForeColor = System::Drawing::Color::White;
        btnBlockUser->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnBlockUser->FlatAppearance->BorderSize = 0;
        btnBlockUser->Cursor = System::Windows::Forms::Cursors::Hand;
        btnBlockUser->Click += gcnew System::EventHandler(this, &UserManagementForm::btnBlockUser_Click);

        // Unblock User (navy outline-style — secondary)
        btnUnblockUser = gcnew System::Windows::Forms::Button();
        btnUnblockUser->Text = "Unblock";
        btnUnblockUser->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold);
        btnUnblockUser->Size = System::Drawing::Size(100, 38);
        btnUnblockUser->Location = System::Drawing::Point(295, 16);
        btnUnblockUser->BackColor = System::Drawing::Color::White;
        btnUnblockUser->ForeColor = UMF_TEXT_DARK();
        btnUnblockUser->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnUnblockUser->FlatAppearance->BorderSize = 1;
        btnUnblockUser->FlatAppearance->BorderColor = UMF_BORDER();
        btnUnblockUser->Cursor = System::Windows::Forms::Cursors::Hand;
        btnUnblockUser->Click += gcnew System::EventHandler(this, &UserManagementForm::btnUnblockUser_Click);

        // Change Password (purple)
        Button^ btnChangePassword = gcnew System::Windows::Forms::Button();
        btnChangePassword->Text = "Change Password";
        btnChangePassword->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold);
        btnChangePassword->Size = System::Drawing::Size(150, 38);
        btnChangePassword->Location = System::Drawing::Point(405, 16);
        btnChangePassword->BackColor = UMF_PURPLE();
        btnChangePassword->ForeColor = System::Drawing::Color::White;
        btnChangePassword->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnChangePassword->FlatAppearance->BorderSize = 0;
        btnChangePassword->Cursor = System::Windows::Forms::Cursors::Hand;
        btnChangePassword->Click += gcnew System::EventHandler(this, &UserManagementForm::btnChangePassword_Click);

        // Delete (red)
        btnDeleteUser = gcnew System::Windows::Forms::Button();
        btnDeleteUser->Text = "Delete";
        btnDeleteUser->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold);
        btnDeleteUser->Size = System::Drawing::Size(100, 38);
        btnDeleteUser->Location = System::Drawing::Point(565, 16);
        btnDeleteUser->BackColor = UMF_RED();
        btnDeleteUser->ForeColor = System::Drawing::Color::White;
        btnDeleteUser->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnDeleteUser->FlatAppearance->BorderSize = 0;
        btnDeleteUser->Cursor = System::Windows::Forms::Cursors::Hand;
        btnDeleteUser->Click += gcnew System::EventHandler(this, &UserManagementForm::btnDeleteUser_Click);

        // Refresh
        btnRefresh = gcnew System::Windows::Forms::Button();
        btnRefresh->Text = L"\u27F3  Refresh";
        btnRefresh->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold);
        btnRefresh->Size = System::Drawing::Size(110, 38);
        btnRefresh->Location = System::Drawing::Point(730, 16);
        btnRefresh->BackColor = System::Drawing::Color::White;
        btnRefresh->ForeColor = UMF_TEXT_DARK();
        btnRefresh->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnRefresh->FlatAppearance->BorderSize = 1;
        btnRefresh->FlatAppearance->BorderColor = UMF_BORDER();
        btnRefresh->Cursor = System::Windows::Forms::Cursors::Hand;
        btnRefresh->Click += gcnew System::EventHandler(this, &UserManagementForm::btnRefresh_Click);

        // Close
        Button^ btnClose = gcnew System::Windows::Forms::Button();
        btnClose->Text = "Close";
        btnClose->Font = gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold);
        btnClose->Size = System::Drawing::Size(90, 38);
        btnClose->Location = System::Drawing::Point(850, 16);
        btnClose->BackColor = System::Drawing::Color::White;
        btnClose->ForeColor = UMF_TEXT_DARK();
        btnClose->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        btnClose->FlatAppearance->BorderSize = 1;
        btnClose->FlatAppearance->BorderColor = UMF_BORDER();
        btnClose->Cursor = System::Windows::Forms::Cursors::Hand;
        btnClose->Click += gcnew System::EventHandler(this, &UserManagementForm::btnTopClose_Click);

        pnlBottom->Controls->Add(btnCreateUser);
        pnlBottom->Controls->Add(btnBlockUser);
        pnlBottom->Controls->Add(btnUnblockUser);
        pnlBottom->Controls->Add(btnChangePassword);
        pnlBottom->Controls->Add(btnDeleteUser);
        pnlBottom->Controls->Add(btnRefresh);
        pnlBottom->Controls->Add(btnClose);

        this->Controls->Add(pnlHeader);
        this->Controls->Add(pnlGrid);
        this->Controls->Add(pnlBottom);

        // Round corners
        RoundIt(btnCreateUser, 6);
        RoundIt(btnBlockUser, 6);
        RoundIt(btnUnblockUser, 6);
        RoundIt(btnChangePassword, 6);
        RoundIt(btnDeleteUser, 6);
        RoundIt(btnRefresh, 6);
        RoundIt(btnClose, 6);
        RoundIt(pnlGrid, 8);
        RoundIt(pnlBottom, 8);

        // Form drag
        pnlHeader->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &UserManagementForm::Form_MouseDown);
        pnlHeader->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &UserManagementForm::Form_MouseMove);
        pnlHeader->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &UserManagementForm::Form_MouseUp);
        this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &UserManagementForm::Form_MouseDown);
        this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &UserManagementForm::Form_MouseMove);
        this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &UserManagementForm::Form_MouseUp);
    }

    void UserManagementForm::loadUsers()
    {
        dgvUsers->Rows->Clear();
        dgvUsers->Columns->Clear();
        dgvUsers->Columns->Add("UserID", "ID");
        dgvUsers->Columns->Add("Username", "USERNAME");
        dgvUsers->Columns->Add("Role", "ROLE");
        dgvUsers->Columns->Add("Status", "STATUS");

        if (dgvUsers->Columns->Count > 0) {
            dgvUsers->Columns[0]->FillWeight = 40;
            dgvUsers->Columns[0]->DefaultCellStyle->Alignment =
                System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
            dgvUsers->Columns[0]->DefaultCellStyle->Font =
                gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold);
            dgvUsers->Columns[3]->DefaultCellStyle->Alignment =
                System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
            dgvUsers->Columns[3]->DefaultCellStyle->Font =
                gcnew System::Drawing::Font("Segoe UI", 9.5F, System::Drawing::FontStyle::Bold);
        }

        List<User^>^ users = UserDB::getAllUsers();
        for each (User ^ u in users) {
            dgvUsers->Rows->Add(
                u->getUserID(),
                u->getUsername(),
                u->getRole(),
                u->getIsActive() ? "Active" : "Blocked"
            );
        }
    }

    void UserManagementForm::btnCreateUser_Click(System::Object^ sender, System::EventArgs^ e)
    {
        CreateUserForm^ form = gcnew CreateUserForm();
        form->ShowDialog();
        loadUsers();
    }

    void UserManagementForm::btnDeleteUser_Click(System::Object^ sender, System::EventArgs^ e)
    {
        int id = getSelectedUserID();
        if (id == -1) return;
        if (id == loggedInUser->getUserID()) {
            MessageBox::Show("You cannot delete your own account.");
            return;
        }
        String^ uname = getSelectedUsername();
        System::Windows::Forms::DialogResult result = MessageBox::Show(
            "Delete user '" + uname + "'?",
            "Confirm Delete",
            MessageBoxButtons::YesNo,
            MessageBoxIcon::Warning
        );
        if (result == System::Windows::Forms::DialogResult::Yes) {
            if (UserDB::deleteUser(id))
                MessageBox::Show("User deleted.");
            loadUsers();
        }
    }

    void UserManagementForm::btnBlockUser_Click(System::Object^ sender, System::EventArgs^ e)
    {
        int id = getSelectedUserID();
        if (id == -1) return;
        if (id == loggedInUser->getUserID()) {
            MessageBox::Show("You cannot block your own account.");
            return;
        }
        if (UserDB::setUserActive(id, false))
            MessageBox::Show("User blocked.");
        loadUsers();
    }

    void UserManagementForm::btnUnblockUser_Click(System::Object^ sender, System::EventArgs^ e)
    {
        int id = getSelectedUserID();
        if (id == -1) return;
        if (UserDB::setUserActive(id, true))
            MessageBox::Show("User unblocked.");
        loadUsers();
    }

    void UserManagementForm::btnRefresh_Click(System::Object^ sender, System::EventArgs^ e)
    {
        loadUsers();
    }

    void UserManagementForm::btnChangePassword_Click(System::Object^ sender, System::EventArgs^ e)
    {
        int id = getSelectedUserID();
        if (id == -1) return;

        List<User^>^ users = UserDB::getAllUsers();
        User^ targetUser = nullptr;
        for each (User ^ u in users) {
            if (u->getUserID() == id) {
                targetUser = u;
                break;
            }
        }
        if (targetUser == nullptr) return;

        bool isSelf = (id == loggedInUser->getUserID());
        ChangePasswordForm^ form;
        if (isSelf) {
            form = gcnew ChangePasswordForm(targetUser);
        }
        else {
            form = gcnew ChangePasswordForm(targetUser, true);
        }
        form->ShowDialog();
        loadUsers();
    }

    void UserManagementForm::btnTopClose_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->Close();
    }

    void UserManagementForm::dgvUsers_CellFormatting(System::Object^ sender,
        System::Windows::Forms::DataGridViewCellFormattingEventArgs^ e)
    {
        if (e->RowIndex < 0) return;
        // Color the Status column
        if (dgvUsers->Columns[e->ColumnIndex]->Name == "Status") {
            System::Object^ v = e->Value;
            if (v != nullptr) {
                if (v->ToString() == "Active") {
                    e->CellStyle->ForeColor = System::Drawing::Color::FromArgb(22, 163, 74);
                }
                else {
                    e->CellStyle->ForeColor = UMF_RED();
                }
            }
        }
    }

    // Drag handlers
    void UserManagementForm::Form_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        if (e->Button == System::Windows::Forms::MouseButtons::Left) {
            dragging = true;
            dragOffset = System::Drawing::Point(
                System::Windows::Forms::Cursor::Position.X - this->Location.X,
                System::Windows::Forms::Cursor::Position.Y - this->Location.Y);
        }
    }
    void UserManagementForm::Form_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        if (dragging) {
            this->Location = System::Drawing::Point(
                System::Windows::Forms::Cursor::Position.X - dragOffset.X,
                System::Windows::Forms::Cursor::Position.Y - dragOffset.Y);
        }
    }
    void UserManagementForm::Form_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        dragging = false;
    }
}