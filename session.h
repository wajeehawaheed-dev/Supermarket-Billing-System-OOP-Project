#pragma once

using namespace System;

namespace SBS {

    public ref class Session abstract sealed {
    private:
        static int      currentUserID = 0;
        static String^ currentUsername = "";
        static String^ currentRole = "";

    public:
        static void SetCurrentUser(int userID, String^ username, String^ role) {
            currentUserID = userID;
            currentUsername = username;
            currentRole = role;
        }

        static void Logout() {
            currentUserID = 0;
            currentUsername = "";
            currentRole = "";
        }

        static int      GetUserID() { 
            return currentUserID; 
        }
        static String^ GetUsername() {
            return currentUsername; 
        }
        static String^ GetRole() {
            return currentRole;
        }
        static bool     IsLoggedIn() { 
            return currentUserID > 0;
        }
        static bool     IsAdmin() { 
            return currentRole == "Admin";
        }
    };
}