#include "LoginForm.h"
#include "database.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<System::String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    if (!SBS::Database::TestConnection()) {
        MessageBox::Show(
            "Cannot connect to SupermarketDB.\n\n"
            "Make sure SQL Server Express is running and schema.sql has been executed.",
            "Database Connection Failed",
            MessageBoxButtons::OK,
            MessageBoxIcon::Error);
        return 1;
    }

    Application::Run(gcnew SUper::LoginForm());
    return 0;
}