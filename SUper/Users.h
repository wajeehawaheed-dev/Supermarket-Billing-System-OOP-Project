#pragma once

using namespace System;

public ref class User
{
private:
    int userID;
    String^ userName;
    String^ password;
    String^ role;
    bool isActive;

public:
    User();
    User(int id , String^ uname , String^ pass , String^ r , bool active);

    int getUserID();
    String^ getUsername();
    String^ getPassword();
    String^ getRole();
    bool getIsActive();

    void setUsername(String^ u);
    void setPassword(String^ p);
    void setRole(String^ r);
    void setIsActive(bool s);

    bool isAdmin();
    bool isCashier();
    bool Passwordvalidation(String^ pass);
};