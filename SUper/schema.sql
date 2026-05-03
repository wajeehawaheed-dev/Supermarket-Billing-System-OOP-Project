IF NOT EXISTS (SELECT * FROM sys.databases WHERE name = 'SupermarketDB')
    CREATE DATABASE SupermarketDB;
GO

USE SupermarketDB;
GO

-- Drop tables in reverse dependency order (foreign keys first)
IF OBJECT_ID('BillItems', 'U')   IS NOT NULL DROP TABLE BillItems;
IF OBJECT_ID('Payments', 'U')    IS NOT NULL DROP TABLE Payments;
IF OBJECT_ID('Bills', 'U')       IS NOT NULL DROP TABLE Bills;
IF OBJECT_ID('Settings', 'U')    IS NOT NULL DROP TABLE Settings;
IF OBJECT_ID('SalesReport', 'U') IS NOT NULL DROP TABLE SalesReport;
IF OBJECT_ID('Products', 'U')    IS NOT NULL DROP TABLE Products;
IF OBJECT_ID('Users', 'U')       IS NOT NULL DROP TABLE Users;
GO

-- Users (Member 1)
CREATE TABLE Users (
    UserID    INT IDENTITY(1,1) PRIMARY KEY,
    Username  NVARCHAR(50)  NOT NULL UNIQUE,
    Password  NVARCHAR(100) NOT NULL,
    Role      NVARCHAR(20)  NOT NULL DEFAULT 'Cashier',
    IsActive  BIT           NOT NULL DEFAULT 1
);

-- Products (Member 2)
CREATE TABLE Products (
    ProductID  INT IDENTITY(1,1) PRIMARY KEY,
    Name       NVARCHAR(100) NOT NULL,
    Category   NVARCHAR(50),
    Price      DECIMAL(10,2) NOT NULL,
    Stock      INT           NOT NULL DEFAULT 0,
    IsActive   BIT           NOT NULL DEFAULT 1
);

-- Bills (Member 3)
CREATE TABLE Bills (
    BillNo       INT IDENTITY(1,1) PRIMARY KEY,
    Date         DATETIME      NOT NULL DEFAULT GETDATE(),
    UserID       INT FOREIGN KEY REFERENCES Users(UserID),
    Subtotal     DECIMAL(10,2),
    Discount     DECIMAL(10,2),
    Tax          DECIMAL(10,2),
    Total        DECIMAL(10,2),
    IsCancelled  BIT           NOT NULL DEFAULT 0
);

CREATE TABLE BillItems (
    ItemID     INT IDENTITY(1,1) PRIMARY KEY,
    BillNo     INT FOREIGN KEY REFERENCES Bills(BillNo),
    ProductID  INT FOREIGN KEY REFERENCES Products(ProductID),
    Quantity   INT,
    Price      DECIMAL(10,2)
);

-- Settings (admin-configurable values)
CREATE TABLE Settings (
    SettingName   NVARCHAR(50)  PRIMARY KEY,
    SettingValue  NVARCHAR(200) NOT NULL,
    Description   NVARCHAR(500)
);

INSERT INTO Settings (SettingName, SettingValue, Description) VALUES
('TAX_RATE',             '0.17',      'GST applied on subtotal after discount'),
('DISCOUNT_THRESHOLD_1', '5',         'Item count for first-tier discount'),
('DISCOUNT_RATE_1',      '0.10',      'First-tier discount percentage'),
('DISCOUNT_THRESHOLD_2', '10',        'Item count for second-tier discount'),
('DISCOUNT_RATE_2',      '0.20',      'Second-tier discount percentage'),
('LOW_STOCK_THRESHOLD',  '5',         'Stock level that triggers low-stock alert'),
('STORE_NAME',           'ValueMart', 'Name shown on receipts');

-- Payments (Member 4)
CREATE TABLE Payments (
    PaymentID    INT IDENTITY(1,1) PRIMARY KEY,
    BillNo       INT           NOT NULL FOREIGN KEY REFERENCES Bills(BillNo),
    CustomerName NVARCHAR(100) NULL,
    Method       NVARCHAR(10)  NOT NULL,
    AmountPaid   DECIMAL(10,2) NOT NULL,
    ChangeAmount DECIMAL(10,2) NOT NULL DEFAULT 0,
    Status       NVARCHAR(20)  NOT NULL DEFAULT 'Pending',
    PayDate      DATETIME      NOT NULL DEFAULT GETDATE()
);

-- SalesReport (Member 5)
CREATE TABLE SalesReport (
    ReportID    INT IDENTITY(1,1) PRIMARY KEY,
    Date        DATE          NOT NULL,
    TotalBills  INT           NOT NULL DEFAULT 0,
    TotalCash   DECIMAL(12,2) NOT NULL DEFAULT 0,
    TotalCard   DECIMAL(12,2) NOT NULL DEFAULT 0,
    Revenue     DECIMAL(12,2) NOT NULL DEFAULT 0
);
GO

-- ============================================================
-- SEED DATA
-- ============================================================
INSERT INTO Users (Username, Password, Role) VALUES
    ('admin',   'admin123', 'Admin'),
    ('cashier', 'cashier1', 'Cashier');



PRINT 'SupermarketDB created. 7 tables, 2 users, 10 products, 7 settings.';
GO