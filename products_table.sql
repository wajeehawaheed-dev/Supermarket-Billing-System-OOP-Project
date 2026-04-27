USE SupermarketDB;
GO

IF NOT EXISTS (SELECT * FROM sys.tables WHERE name = 'Products')
BEGIN
    CREATE TABLE Products (
        ProductID   INT IDENTITY(1,1) PRIMARY KEY,
        Name        NVARCHAR(100)  NOT NULL,
        Category    NVARCHAR(50)   NOT NULL,
        Price       DECIMAL(10,2)  NOT NULL,
        Stock       INT            NOT NULL,
        IsActive    BIT            DEFAULT 1
    );
   
END
GO

-- For Resetting the DataBase permanent table containing data of products, execute the query once with the following 2 lines of code, and then Visual Studio.
DELETE FROM Products;
DBCC CHECKIDENT ('Products', RESEED, 0);