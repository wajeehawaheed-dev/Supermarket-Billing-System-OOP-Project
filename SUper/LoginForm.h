#pragma once
#include "AdminDashboardForm.h"
#include "database.h"
#include "session.h"
namespace SUper {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Data::SqlClient;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class LoginForm : public System::Windows::Forms::Form
	{
	public:
		LoginForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LoginForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lblHead;
	protected:

	protected:
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ lblUsername;
	private: System::Windows::Forms::TextBox^ txtUsername;


	private: System::Windows::Forms::Label^ lblPassword;
	private: System::Windows::Forms::TextBox^ txtPassword;





	private: System::Windows::Forms::Button^ btnLogin;

	private: System::Windows::Forms::Label^ lblerror;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->lblHead = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->lblUsername = (gcnew System::Windows::Forms::Label());
			this->txtUsername = (gcnew System::Windows::Forms::TextBox());
			this->lblPassword = (gcnew System::Windows::Forms::Label());
			this->txtPassword = (gcnew System::Windows::Forms::TextBox());
			this->btnLogin = (gcnew System::Windows::Forms::Button());
			this->lblerror = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// lblHead
			// 
			this->lblHead->AutoSize = true;
			this->lblHead->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblHead->Location = System::Drawing::Point(195, 18);
			this->lblHead->Name = L"lblHead";
			this->lblHead->Size = System::Drawing::Size(146, 31);
			this->lblHead->TabIndex = 0;
			this->lblHead->Text = L"ValueMart";
			this->lblHead->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->lblHead->Click += gcnew System::EventHandler(this, &LoginForm::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(198, 49);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(0, 13);
			this->label2->TabIndex = 1;
			// 
			// lblUsername
			// 
			this->lblUsername->AutoSize = true;
			this->lblUsername->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblUsername->Location = System::Drawing::Point(154, 116);
			this->lblUsername->Name = L"lblUsername";
			this->lblUsername->Size = System::Drawing::Size(76, 16);
			this->lblUsername->TabIndex = 2;
			this->lblUsername->Text = L"Username: ";
			// 
			// txtUsername
			// 
			this->txtUsername->Location = System::Drawing::Point(236, 115);
			this->txtUsername->Name = L"txtUsername";
			this->txtUsername->Size = System::Drawing::Size(132, 20);
			this->txtUsername->TabIndex = 3;
			this->txtUsername->TextChanged += gcnew System::EventHandler(this, &LoginForm::textBox1_TextChanged);
			// 
			// lblPassword
			// 
			this->lblPassword->AutoSize = true;
			this->lblPassword->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblPassword->Location = System::Drawing::Point(157, 146);
			this->lblPassword->Name = L"lblPassword";
			this->lblPassword->Size = System::Drawing::Size(73, 16);
			this->lblPassword->TabIndex = 4;
			this->lblPassword->Text = L"Password: ";
			// 
			// txtPassword
			// 
			this->txtPassword->Location = System::Drawing::Point(236, 145);
			this->txtPassword->Name = L"txtPassword";
			this->txtPassword->PasswordChar = '*';
			this->txtPassword->Size = System::Drawing::Size(132, 20);
			this->txtPassword->TabIndex = 5;
			// 
			// btnLogin
			// 
			this->btnLogin->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnLogin->Location = System::Drawing::Point(221, 209);
			this->btnLogin->Name = L"btnLogin";
			this->btnLogin->Size = System::Drawing::Size(131, 39);
			this->btnLogin->TabIndex = 7;
			this->btnLogin->Text = L"Login";
			this->btnLogin->UseVisualStyleBackColor = true;
			this->btnLogin->Click += gcnew System::EventHandler(this, &LoginForm::btnLogin_Click);
			// 
			// lblerror
			// 
			this->lblerror->AutoSize = true;
			this->lblerror->ForeColor = System::Drawing::Color::Red;
			this->lblerror->Location = System::Drawing::Point(278, 270);
			this->lblerror->Name = L"lblerror";
			this->lblerror->Size = System::Drawing::Size(0, 13);
			this->lblerror->TabIndex = 8;
			// 
			// LoginForm
			// 
			this->AcceptButton = this->btnLogin;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(538, 343);
			this->Controls->Add(this->lblerror);
			this->Controls->Add(this->btnLogin);
			this->Controls->Add(this->txtPassword);
			this->Controls->Add(this->lblPassword);
			this->Controls->Add(this->txtUsername);
			this->Controls->Add(this->lblUsername);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->lblHead);
			this->Name = L"LoginForm";
			this->Text = L"ValueMart Login";
			this->Load += gcnew System::EventHandler(this, &LoginForm::LoginForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void LoginForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void btnLogin_Click(System::Object^ sender, System::EventArgs^ e) {
	lblerror->Text = "";

	String^ username = txtUsername->Text->Trim();
	String^ password = txtPassword->Text;

	if (String::IsNullOrEmpty(username) || String::IsNullOrEmpty(password)) {
		lblerror->Text = "Please enter username and password";
		return;
	}

	DataTable^ result = SBS::Database::ExecuteQuery(
		"SELECT UserID, Username, Role, IsActive FROM Users "
		"WHERE Username = @u AND Password = @p",
		gcnew SqlParameter("@u", username),
		gcnew SqlParameter("@p", password));

	if (result == nullptr || result->Rows->Count == 0) {
		lblerror->Text = "Invalid username or password";
		txtPassword->Clear();
		return;
	}

	DataRow^ row = result->Rows[0];

	bool isActive = Convert::ToBoolean(row["IsActive"]);
	if (!isActive) {
		lblerror->Text = "Account is deactivated. Contact admin.";
		return;
	}

	int userID = Convert::ToInt32(row["UserID"]);
	String^ uname = row["Username"]->ToString();
	String^ role = row["Role"]->ToString();

	SBS::Session::SetCurrentUser(userID, uname, role);

	this->Hide();

	if (SBS::Session::IsAdmin()) {
		AdminDashboardForm^ adminForm = gcnew AdminDashboardForm();
		adminForm->ShowDialog();
	}
	else {
		MessageBox::Show("Cashier menu coming soon.\nLogged in as: " + uname,
			"Cashier Login",
			MessageBoxButtons::OK,
			MessageBoxIcon::Information);
	}

	txtUsername->Clear();
	txtPassword->Clear();
	txtUsername->Focus();
	this->Show();
}
};
}
