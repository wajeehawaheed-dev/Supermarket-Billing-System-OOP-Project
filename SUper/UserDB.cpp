#include "UserDB.h"

void UserDB::defAdmin()
{
    SqlConnection^ conn = DatabaseConnection::getConnection();
    try {
        conn->Open();
        SqlCommand^ checkCmd = gcnew SqlCommand(
            "SELECT COUNT(*) FROM Users WHERE Role = 'Admin'" , conn);
        int count = ( int ) checkCmd->ExecuteScalar();
        if ( count == 0 ) {
            SqlCommand^ cmd = gcnew SqlCommand(
                "INSERT INTO Users (Username, Password, Role, IsActive) "
                "VALUES (@u, @p, @r, @a)" , conn);
            cmd->Parameters->AddWithValue("@u" , "admin");
            cmd->Parameters->AddWithValue("@p" , "admin123");
            cmd->Parameters->AddWithValue("@r" , "Admin");
            cmd->Parameters->AddWithValue("@a" , true);
            cmd->ExecuteNonQuery();
        }
    }
    catch ( Exception^ ex ) {
        MessageBox::Show("Seed error: " + ex->Message);
    }
    finally { conn->Close(); }
}

User^ UserDB::loginUser(String^ username , String^ password)
{
    SqlConnection^ conn = DatabaseConnection::getConnection();
    try {
        conn->Open();
        SqlCommand^ cmd = gcnew SqlCommand(
            "SELECT UserID, Username, Password, Role, IsActive "
            "FROM Users WHERE Username = @u AND Password = @p" , conn);
        cmd->Parameters->AddWithValue("@u" , username);
        cmd->Parameters->AddWithValue("@p" , password);
        SqlDataReader^ reader = cmd->ExecuteReader();
        if ( reader->Read() ) {
            bool active = ( bool ) reader ["IsActive"];
            if ( !active ) {
                MessageBox::Show("This account has been blocked.");
                return nullptr;
            }
            return gcnew User(
                ( int ) reader ["UserID"] ,
                reader ["Username"]->ToString() ,
                reader ["Password"]->ToString() ,
                reader ["Role"]->ToString() ,
                active
            );
        }
        return nullptr;
    }
    catch ( Exception^ ex ) {
        MessageBox::Show("Login error: " + ex->Message);
        return nullptr;
    }
    finally { conn->Close(); }
}

bool UserDB::createUser(String^ username , String^ password , String^ role)
{
    if ( username->Trim() == "" || password->Trim() == "" ) {
        MessageBox::Show("Fields cannot be empty.");
        return false;
    }
    if ( usernameExists(username) ) {
        MessageBox::Show("Username already taken.");
        return false;
    }
    SqlConnection^ conn = DatabaseConnection::getConnection();
    try {
        conn->Open();
        SqlCommand^ cmd = gcnew SqlCommand(
            "INSERT INTO Users (Username, Password, Role, IsActive) "
            "VALUES (@u, @p, @r, @a)" , conn);
        cmd->Parameters->AddWithValue("@u" , username->Trim());
        cmd->Parameters->AddWithValue("@p" , password->Trim());
        cmd->Parameters->AddWithValue("@r" , role);
        cmd->Parameters->AddWithValue("@a" , true);
        cmd->ExecuteNonQuery();
        return true;
    }
    catch ( Exception^ ex ) {
        MessageBox::Show("Create error: " + ex->Message);
        return false;
    }
    finally { conn->Close(); }
}

bool UserDB::deleteUser(int userID)
{
    SqlConnection^ conn = DatabaseConnection::getConnection();
    try {
        conn->Open();
        SqlCommand^ cmd = gcnew SqlCommand(
            "DELETE FROM Users WHERE UserID = @id" , conn);
        cmd->Parameters->AddWithValue("@id" , userID);
        cmd->ExecuteNonQuery();
        return true;
    }
    catch ( Exception^ ex ) {
        MessageBox::Show("Delete error: " + ex->Message);
        return false;
    }
    finally { conn->Close(); }
}

bool UserDB::setUserActive(int userID , bool status)
{
    SqlConnection^ conn = DatabaseConnection::getConnection();
    try {
        conn->Open();
        SqlCommand^ cmd = gcnew SqlCommand(
            "UPDATE Users SET IsActive = @s WHERE UserID = @id" , conn);
        cmd->Parameters->AddWithValue("@s" , status);
        cmd->Parameters->AddWithValue("@id" , userID);
        cmd->ExecuteNonQuery();
        return true;
    }
    catch ( Exception^ ex ) {
        MessageBox::Show("Block error: " + ex->Message);
        return false;
    }
    finally { conn->Close(); }
}

bool UserDB::changePassword(int userID , String^ oldPass , String^ newPass)
{
    SqlConnection^ conn = DatabaseConnection::getConnection();
    try {
        conn->Open();
        SqlCommand^ checkCmd = gcnew SqlCommand(
            "SELECT COUNT(*) FROM Users WHERE UserID = @id AND Password = @old" , conn);
        checkCmd->Parameters->AddWithValue("@id" , userID);
        checkCmd->Parameters->AddWithValue("@old" , oldPass);
        int match = ( int ) checkCmd->ExecuteScalar();
        if ( match == 0 ) {
            MessageBox::Show("Current password is incorrect.");
            return false;
        }
        SqlCommand^ cmd = gcnew SqlCommand(
            "UPDATE Users SET Password = @new WHERE UserID = @id" , conn);
        cmd->Parameters->AddWithValue("@new" , newPass);
        cmd->Parameters->AddWithValue("@id" , userID);
        cmd->ExecuteNonQuery();
        return true;
    }
    catch ( Exception^ ex ) {
        MessageBox::Show("Password error: " + ex->Message);
        return false;
    }
    finally { conn->Close(); }
}

List<User^>^ UserDB::getAllUsers()
{
    List<User^>^ users = gcnew List<User^>();
    SqlConnection^ conn = DatabaseConnection::getConnection();
    try {
        conn->Open();
        SqlCommand^ cmd = gcnew SqlCommand(
            "SELECT UserID, Username, Password, Role, IsActive FROM Users" , conn);
        SqlDataReader^ reader = cmd->ExecuteReader();
        while ( reader->Read() ) {
            users->Add(gcnew User(
                ( int ) reader ["UserID"] ,
                reader ["Username"]->ToString() ,
                reader ["Password"]->ToString() ,
                reader ["Role"]->ToString() ,
                ( bool ) reader ["IsActive"]
            ));
        }
    }
    catch ( Exception^ ex ) {
        MessageBox::Show("Fetch error: " + ex->Message);
    }
    finally { conn->Close(); }
    return users;
}

bool UserDB::usernameExists(String^ username)
{
    SqlConnection^ conn = DatabaseConnection::getConnection();
    try {
        conn->Open();
        SqlCommand^ cmd = gcnew SqlCommand(
            "SELECT COUNT(*) FROM Users WHERE Username = @u" , conn);
        cmd->Parameters->AddWithValue("@u" , username->Trim());
        return ( int ) cmd->ExecuteScalar() > 0;
    }
    catch ( Exception^ ex ) {
        MessageBox::Show("Check error: " + ex->Message);
        return false;
    }
    finally { conn->Close(); }
}