#pragma once

using namespace System;
using namespace System::Data;
using namespace System::Data::SqlClient;

namespace SBS {

    public ref class Database {
    public:
        static String^ GetConnectionString() {
            return "Server=.\\SQLEXPRESS;"
                "Database=SupermarketDB;"
                "Integrated Security=True;";
        }

        static int ExecuteNonQuery(String^ sql) {
            return ExecuteNonQuery(sql, nullptr);
        }

        static int ExecuteNonQuery(String^ sql, ... array<SqlParameter^>^ params) {
            SqlConnection^ conn = gcnew SqlConnection(GetConnectionString());
            try {
                conn->Open();
                SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
                if (params != nullptr) {
                    for each (SqlParameter ^ p in params) {
                        cmd->Parameters->Add(p);
                    }
                }
                return cmd->ExecuteNonQuery();
            }
            catch (Exception^ e) {
                System::Windows::Forms::MessageBox::Show(
                    "Database error: " + e->Message);
                return -1;
            }
            finally {
                if (conn->State == ConnectionState::Open) conn->Close();
            }
        }

        static DataTable^ ExecuteQuery(String^ sql) {
            return ExecuteQuery(sql, nullptr);
        }

        static DataTable^ ExecuteQuery(String^ sql, ... array<SqlParameter^>^ params) {
            DataTable^ table = gcnew DataTable();
            SqlConnection^ conn = gcnew SqlConnection(GetConnectionString());
            try {
                conn->Open();
                SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
                if (params != nullptr) {
                    for each (SqlParameter ^ p in params) {
                        cmd->Parameters->Add(p);
                    }
                }
                SqlDataAdapter^ adapter = gcnew SqlDataAdapter(cmd);
                adapter->Fill(table);
            }
            catch (Exception^ e) {
                System::Windows::Forms::MessageBox::Show(
                    "Database error: " + e->Message);
            }
            finally {
                if (conn->State == ConnectionState::Open) conn->Close();
            }
            return table;
        }

        static Object^ ExecuteScalar(String^ sql) {
            return ExecuteScalar(sql, nullptr);
        }

        static Object^ ExecuteScalar(String^ sql, ... array<SqlParameter^>^ params) {
            Object^ result = nullptr;
            SqlConnection^ conn = gcnew SqlConnection(GetConnectionString());
            try {
                conn->Open();
                SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
                if (params != nullptr) {
                    for each (SqlParameter ^ p in params) {
                        cmd->Parameters->Add(p);
                    }
                }
                result = cmd->ExecuteScalar();
            }
            catch (Exception^ e) {
                System::Windows::Forms::MessageBox::Show(
                    "Database error: " + e->Message);
            }
            finally {
                if (conn->State == ConnectionState::Open) conn->Close();
            }
            return result;
        }

        static bool TestConnection() {
            SqlConnection^ conn = gcnew SqlConnection(GetConnectionString());
            try {
                conn->Open();
                return true;
            }
            catch (...) {
                return false;
            }
            finally {
                if (conn->State == ConnectionState::Open) conn->Close();
            }
        }
    };
}