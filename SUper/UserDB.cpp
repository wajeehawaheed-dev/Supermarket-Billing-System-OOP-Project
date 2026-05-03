#include "UserDB.h"
#include "database.h"

using namespace System::Data;
using namespace System::Data::SqlClient;

void UserDB::defAdmin()
{
    // Idempotent: ensures admin exists. Schema seed already creates one,
    // but this handles the case where seed wasn't run.
    Object^ result = SBS::Database::ExecuteScalar(
        "SELECT COUNT(*) FROM Users WHERE Role = 'Admin'");
    int count = (result == nullptr) ? 0 : Convert::ToInt32(result);
    if (count == 0) {
        SBS::Database::ExecuteNonQuery(
            "INSERT INTO Users (Username, Password, Role, IsActive) "
            "VALUES (@u, @p, @r, @a)",
            gcnew SqlParameter("@u", "admin"),
            gcnew SqlParameter("@p", "admin123"),
            gcnew SqlParameter("@r", "Admin"),
            gcnew SqlParameter("@a", true));
    }
}

User^ UserDB::loginUser(String^ username, String^ password)
{
    // Note: LoginForm has its own login logic — this method is unused
    // but kept for API compatibility with UserDB.h
    DataTable^ result = SBS::Database::ExecuteQuery(
        "SELECT UserID, Username, Password, Role, IsActive "
        "FROM Users WHERE Username = @u AND Password = @p",
        gcnew SqlParameter("@u", username),
        gcnew SqlParameter("@p", password));

    if (result == nullptr || result->Rows->Count == 0)
        return nullptr;

    DataRow^ row = result->Rows[0];
    bool active = Convert::ToBoolean(row["IsActive"]);
    if (!active) {
        MessageBox::Show("This account has been blocked.");
        return nullptr;
    }
    return gcnew User(
        Convert::ToInt32(row["UserID"]),
        row["Username"]->ToString(),
        row["Password"]->ToString(),
        row["Role"]->ToString(),
        active);
}

bool UserDB::createUser(String^ username, String^ password, String^ role)
{
    if (username->Trim() == "" || password->Trim() == "") {
        MessageBox::Show("Fields cannot be empty.");
        return false;
    }
    if (usernameExists(username)) {
        MessageBox::Show("Username already taken.");
        return false;
    }
    SBS::Database::ExecuteNonQuery(
        "INSERT INTO Users (Username, Password, Role, IsActive) "
        "VALUES (@u, @p, @r, @a)",
        gcnew SqlParameter("@u", username->Trim()),
        gcnew SqlParameter("@p", password->Trim()),
        gcnew SqlParameter("@r", role),
        gcnew SqlParameter("@a", true));
    return true;
}

bool UserDB::deleteUser(int userID)
{
    SBS::Database::ExecuteNonQuery(
        "DELETE FROM Users WHERE UserID = @id",
        gcnew SqlParameter("@id", userID));
    return true;
}

bool UserDB::setUserActive(int userID, bool status)
{
    SBS::Database::ExecuteNonQuery(
        "UPDATE Users SET IsActive = @s WHERE UserID = @id",
        gcnew SqlParameter("@s", status),
        gcnew SqlParameter("@id", userID));
    return true;
}

bool UserDB::changePassword(int userID, String^ oldPass, String^ newPass)
{
    Object^ result = SBS::Database::ExecuteScalar(
        "SELECT COUNT(*) FROM Users WHERE UserID = @id AND Password = @old",
        gcnew SqlParameter("@id", userID),
        gcnew SqlParameter("@old", oldPass));

    int match = (result == nullptr) ? 0 : Convert::ToInt32(result);
    if (match == 0) {
        MessageBox::Show("Current password is incorrect.");
        return false;
    }

    SBS::Database::ExecuteNonQuery(
        "UPDATE Users SET Password = @new WHERE UserID = @id",
        gcnew SqlParameter("@new", newPass),
        gcnew SqlParameter("@id", userID));
    return true;
}

List<User^>^ UserDB::getAllUsers()
{
    List<User^>^ users = gcnew List<User^>();
    DataTable^ result = SBS::Database::ExecuteQuery(
        "SELECT UserID, Username, Password, Role, IsActive FROM Users");

    if (result == nullptr) return users;

    for each (DataRow ^ row in result->Rows) {
        users->Add(gcnew User(
            Convert::ToInt32(row["UserID"]),
            row["Username"]->ToString(),
            row["Password"]->ToString(),
            row["Role"]->ToString(),
            Convert::ToBoolean(row["IsActive"])));
    }
    return users;
}

bool UserDB::usernameExists(String^ username)
{
    Object^ result = SBS::Database::ExecuteScalar(
        "SELECT COUNT(*) FROM Users WHERE Username = @u",
        gcnew SqlParameter("@u", username->Trim()));
    return (result != nullptr) && (Convert::ToInt32(result) > 0);
}
bool UserDB::adminResetPassword(int userID, String^ newPass)
{
    SBS::Database::ExecuteNonQuery(
        "UPDATE Users SET Password = @new WHERE UserID = @id",
        gcnew SqlParameter("@new", newPass),
        gcnew SqlParameter("@id", userID));
    return true;
}