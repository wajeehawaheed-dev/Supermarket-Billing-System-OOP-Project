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