-- Report 1: Sales by Day (with date range filter)
-- For C++: this is parameterized — @StartDate and @EndDate come from form date pickers
DECLARE @StartDate DATE = DATEADD(day, -30, GETDATE());
DECLARE @EndDate   DATE = GETDATE();

SELECT
    CAST(Date AS DATE)        AS SaleDate,
    COUNT(*)                  AS TotalBills,
    SUM(Subtotal)             AS Subtotal,
    SUM(Discount)             AS TotalDiscount,
    SUM(Tax)                  AS TotalTax,
    SUM(Total)                AS Revenue
FROM Bills
WHERE IsCancelled = 0
  AND CAST(Date AS DATE) BETWEEN @StartDate AND @EndDate
GROUP BY CAST(Date AS DATE)
ORDER BY SaleDate DESC;


    -- Report 2: Best-Selling Products
SELECT
    p.ProductID,
    p.Name                                   AS ProductName,
    p.Category,
    SUM(bi.Quantity)                         AS UnitsSold,
    SUM(bi.Quantity * bi.Price)              AS Revenue,
    COUNT(DISTINCT bi.BillNo)                AS BillCount
FROM BillItems bi
JOIN Products p   ON p.ProductID = bi.ProductID
JOIN Bills b      ON b.BillNo    = bi.BillNo
WHERE b.IsCancelled = 0
GROUP BY p.ProductID, p.Name, p.Category
ORDER BY UnitsSold DESC;

-- Report 3: Revenue by Payment Method
SELECT
    p.Method,
    COUNT(*)                  AS PaymentCount,
    SUM(p.AmountPaid)          AS TotalPaid,
    SUM(p.ChangeAmount)        AS TotalChange,
    SUM(b.Total)               AS BillTotal
FROM Payments p
JOIN Bills b ON b.BillNo = p.BillNo
WHERE p.Status = 'Approved'
  AND b.IsCancelled = 0
GROUP BY p.Method
ORDER BY BillTotal DESC;