#include "Users.h"

User::User()
{
    userID = 0;
    userName = "";
    password = "";
    role = "Cashier";
    isActive = true;
}

User::User(int id , String^ uname , String^ pass , String^ r , bool active)
{
    userID = id;
    userName = uname;
    password = pass;
    role = r;
    isActive = active;
}

int User::getUserID() { return userID; }
String^ User::getUsername() { return userName; }
String^ User::getPassword() { return password; }
String^ User::getRole() { return role; }
bool User::getIsActive() { return isActive; }

void User::setUsername(String^ u) { userName = u; }
void User::setPassword(String^ p) { password = p; }
void User::setRole(String^ r) { role = r; }
void User::setIsActive(bool s) { isActive = s; }

bool User::isAdmin() { return role == "Admin"; }
bool User::isCashier() { return role == "Cashier"; }

bool User::Passwordvalidation(String^ pass)
{
    if ( pass->Length < 8 ) return false;
    bool hasNumber = false;
    for each ( Char c in pass ) {
        if ( Char::IsDigit(c) ) {
            hasNumber = true;
            break;
        }
    }
    return hasNumber;
}