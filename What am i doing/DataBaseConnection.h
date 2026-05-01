#pragma once

using namespace System;
using namespace System::Data::SqlClient;

ref class DatabaseConnection
{
public:
    static String^ connectionString =
        "Server=localhost\\SQLEXPRESS;"
        "Database=SupermarketDB;"
        "Integrated Security=True;"
        "TrustServerCertificate=True;";

    static SqlConnection^ getConnection()
    {
        return gcnew SqlConnection(connectionString);
    }
};
