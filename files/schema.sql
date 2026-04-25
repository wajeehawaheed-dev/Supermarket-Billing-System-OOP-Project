IF NOT EXISTS (SELECT * FROM sys.databases WHERE name = 'SupermarketDB')
    CREATE DATABASE SupermarketDB;
GO

USE SupermarketDB;
GO

-- Drop tables in reverse dependency order (foreign keys first)
IF OBJECT_ID('BillItems', 'U')   IS NOT NULL DROP TABLE BillItems;
IF OBJECT_ID('Payments', 'U')    IS NOT NULL DROP TABLE Payments;
IF OBJECT_ID('Bills', 'U')       IS NOT NULL DROP TABLE Bills;
IF OBJECT_ID('SalesReport', 'U') IS NOT NULL DROP TABLE SalesReport;
IF OBJECT_ID('Products', 'U')    IS NOT NULL DROP TABLE Products;
IF OBJECT_ID('Users', 'U')       IS NOT NULL DROP TABLE Users;
GO

-- Users (Member 1)
CREATE TABLE Users (
    UserID      INT IDENTITY(1,1) PRIMARY KEY,
    Username    VARCHAR(50)  NOT NULL UNIQUE,
    Password    VARCHAR(100) NOT NULL,
    Role        VARCHAR(20)  NOT NULL DEFAULT 'Cashier',
    IsActive    BIT          NOT NULL DEFAULT 1
);

-- Products (Member 2)
CREATE TABLE Products (
    ProductID   INT IDENTITY(1,1) PRIMARY KEY,
    Name        VARCHAR(100)  NOT NULL,
    Category    VARCHAR(50),
    Price       DECIMAL(10,2) NOT NULL,
    Stock       INT           NOT NULL DEFAULT 0,
    IsActive    BIT           NOT NULL DEFAULT 1
);

-- Bills (Member 3)
-- Member 3 (Cart & Billing) Tables

CREATE TABLE Bills (
    BillNo      INT PRIMARY KEY IDENTITY,
    Date        DATETIME DEFAULT GETDATE(),
    UserID      INT,
    Subtotal    FLOAT,
    Discount    FLOAT,
    Tax         FLOAT,
    Total       FLOAT
);

CREATE TABLE BillItems (
    ItemID      INT PRIMARY KEY IDENTITY,
    BillNo      INT FOREIGN KEY REFERENCES Bills(BillNo),
    ProductID   INT,
    Quantity    INT,
    Price       FLOAT
);

CREATE TABLE Settings (
    SettingName  VARCHAR(50) PRIMARY KEY,
    SettingValue FLOAT
);

-- Default settings
INSERT INTO Settings VALUES ('TAX_RATE', 0.17);
INSERT INTO Settings VALUES ('DISCOUNT_THRESHOLD_1', 5);
INSERT INTO Settings VALUES ('DISCOUNT_RATE_1', 0.10);
INSERT INTO Settings VALUES ('DISCOUNT_THRESHOLD_2', 10);
INSERT INTO Settings VALUES ('DISCOUNT_RATE_2', 0.20);

-- Payments (Member 4)
CREATE TABLE Payments (
    PaymentID   INT IDENTITY(1,1) PRIMARY KEY,
    BillNo      INT           NOT NULL,
    Method      VARCHAR(10)   NOT NULL,
    AmountPaid  DECIMAL(10,2) NOT NULL,
    ChangeAmt   DECIMAL(10,2) NOT NULL DEFAULT 0,
    Status      VARCHAR(20)   NOT NULL,
    Date        DATETIME      NOT NULL DEFAULT GETDATE(),
    CardLast4   VARCHAR(4)    NULL,
    FOREIGN KEY (BillNo) REFERENCES Bills(BillNo)
);

-- SalesReport (Member 5 - YOU)
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
-- SEED DATA — so teammates have something to test with
-- ============================================================

-- Default accounts
INSERT INTO Users (Username, Password, Role) VALUES
    ('admin',   'admin123', 'Admin'),
    ('cashier', 'cashier1', 'Cashier');

-- Sample products (note: Biscuits has stock=3 to test low-stock alert)
INSERT INTO Products (Name, Category, Price, Stock) VALUES
    ('Milk 1L',        'Dairy',     250.00, 40),
    ('Bread',          'Bakery',    180.00, 25),
    ('Eggs (dozen)',   'Dairy',     360.00, 30),
    ('Rice 5kg',       'Grains',   1500.00, 20),
    ('Cooking Oil 1L', 'Grocery',   750.00, 15),
    ('Sugar 1kg',      'Grocery',   220.00, 50),
    ('Tea 500g',       'Beverages', 850.00,  8),
    ('Biscuits',       'Snacks',    120.00,  3),
    ('Shampoo 400ml',  'Personal',  650.00, 12),
    ('Toothpaste',     'Personal',  180.00, 18);

PRINT 'SupermarketDB created. 6 tables, 2 users, 10 products.';
GO