#pragma once
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <string>
//handles
SQLHENV hEnv;//for setup of ODBC
SQLHDBC hDbc;// connection 
SQLHSTMT hStmt;
//connection
bool connectDB() {  // handle type  //Parent Class   // Data will be stored here 
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc); // connection 
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    // W represents unicode 
    SQLWCHAR connStr[] =
        L"DRIVER={ODBC Driver 17 for SQL Server};"
        L"SERVER=.\\SQLEXPRESS;"
        L"DATABASE=SuperMarket Database;"
        L"Trusted_Connection=yes;";
    // return value check 
    SQLRETURN ret = SQLDriverConnectW(hDbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);

    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        cout << "Database Connected!" << std::endl;
        return true;
    }
    cout << " OOPs Connection Failed!" << std::endl;
    return false;
}

void disconnectDB()
{
    SQLDisconnect(hDbc);//ends connection 
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);//frees connection memory 
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv); // Frees Environment memory 
}
// INSERT PAYMENT

//C++ naming 
bool insertPayment(int billNo, string method, double amountPaid, double changeAmt, string status, string date) {
    // for every query we made hStmt 
    SQLHSTMT hStmt;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    //PayDate is reserved word for 
    SQLWCHAR query[] =
        L"INSERT INTO Payments "
        L"(BillNo, Method, AmountPaid, ChangeAmount, Status, PayDate) "
        L"VALUES (?, ?, ?, ?, ?, ?)";// ? for place handler
    SQLPrepareW(hStmt, query, SQL_NTS);
    // copied C++ data in SQL Table 
    SQLINTEGER billParam = billNo;
    SQLDOUBLE amountParam = amountPaid;
    SQLDOUBLE changeParam = changeAmt;
    //copied C++ String into SQL wstring
    //method.string&end tells string to copy in wstring 
    wstring methodW(method.begin(), method.end());
    wstring statusW(status.begin(), status.end());
    wstring dateW(date.begin(), date.end());
    // 1 for BillNo 
    //2 for Method
    // 3 for Amount Paid
    //4 Change Amount
    // 5 for Status 
    //6 PayDate                                 //C++    // SQL 

    SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &billParam, 0, NULL);
    SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 10, 0, (SQLWCHAR*)methodW.c_str(), 0, NULL);
    SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_FLOAT, 0, 0, &amountParam, 0, NULL);
    SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_FLOAT, 0, 0, &changeParam, 0, NULL);
    SQLBindParameter(hStmt, 5, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 20, 0, (SQLWCHAR*)statusW.c_str(), 0, NULL);
    SQLBindParameter(hStmt, 6, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 20, 0,
        (SQLWCHAR*)dateW.c_str(), 0, NULL);
    // after hStmt executes it returns to query SQL server 

    SQLRETURN ret = SQLExecute(hStmt);
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        cout << "Payment saved successfully " << endl;
        return true;
    }
    cout << "Insert Failed!" << endl;
    return false;
}#pragma once
