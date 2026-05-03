#pragma once
#include "Users.h"

using namespace System;
using namespace System::Data::SqlClient;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;

ref class UserDB
{
public:
    static void defAdmin();
    static User^ loginUser(String^ username , String^ password);
    static bool createUser(String^ username , String^ password , String^ role);
    static bool deleteUser(int userID);
    static bool setUserActive(int userID , bool status);
    static bool changePassword(int userID , String^ oldPass , String^ newPass);
    static bool adminResetPassword(int userID, String^ newPass);
    static List<User^>^ getAllUsers();
    static bool usernameExists(String^ username);
};
