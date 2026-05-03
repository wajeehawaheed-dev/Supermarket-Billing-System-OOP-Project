USE SupermarketDB;
GO

-- ============================================================
-- Wipe old test transactions (keeps Users/Products/Settings)
-- ============================================================
DELETE FROM Payments;
DELETE FROM BillItems;
DELETE FROM Bills;
DBCC CHECKIDENT ('Bills',     RESEED, 0);
DBCC CHECKIDENT ('BillItems', RESEED, 0);
DBCC CHECKIDENT ('Payments',  RESEED, 0);
GO

-- ============================================================
-- 15 Bills spread across the last 30 days
-- Mix of cashier (UserID=2) and admin (UserID=1)
-- One bill is cancelled
-- ============================================================
INSERT INTO Bills (Date, UserID, Subtotal, Discount, Tax, Total, IsCancelled) VALUES
(DATEADD(day, -28, GETDATE()), 2, 750.00,  0.00,    127.50,  877.50, 0),
(DATEADD(day, -27, GETDATE()), 2, 1980.00, 198.00,  302.94, 2084.94, 0),
(DATEADD(day, -25, GETDATE()), 2, 430.00,  0.00,    73.10,   503.10, 0),
(DATEADD(day, -22, GETDATE()), 2, 2150.00, 215.00,  328.95, 2263.95, 0),
(DATEADD(day, -20, GETDATE()), 2, 360.00,  0.00,    61.20,   421.20, 0),
(DATEADD(day, -18, GETDATE()), 2, 3050.00, 610.00,  414.80, 2854.80, 0),  -- 20% discount
(DATEADD(day, -15, GETDATE()), 2, 1200.00, 120.00,  183.60, 1263.60, 0),
(DATEADD(day, -12, GETDATE()), 2, 580.00,  0.00,    98.60,   678.60, 0),
(DATEADD(day, -10, GETDATE()), 2, 2400.00, 240.00,  367.20, 2527.20, 0),
(DATEADD(day,  -8, GETDATE()), 2, 950.00,  0.00,    161.50, 1111.50, 0),
(DATEADD(day,  -6, GETDATE()), 2, 1750.00, 175.00,  267.75, 1842.75, 1),  -- CANCELLED
(DATEADD(day,  -5, GETDATE()), 2, 4200.00, 840.00,  571.20, 3931.20, 0),  -- 20% discount
(DATEADD(day,  -3, GETDATE()), 2, 1100.00, 110.00,  168.30, 1158.30, 0),
(DATEADD(day,  -1, GETDATE()), 2, 720.00,  0.00,    122.40,  842.40, 0),
(GETDATE(),                    2, 2800.00, 280.00,  428.40, 2948.40, 0);
GO

-- ============================================================
-- BillItems — distributed across products so best-sellers report shows variety
-- Heavy hitters: Milk (1), Bread (2), Sugar (6), Tea (7)
-- ============================================================
INSERT INTO BillItems (BillNo, ProductID, Quantity, Price) VALUES
-- Bill 1
(1, 1, 2, 250.00),
(1, 2, 1, 180.00),
(1, 8, 1, 120.00),
-- Bill 2 (5+ items, 10% discount applied)
(2, 1, 3, 250.00),
(2, 4, 1, 1500.00),
(2, 6, 1, 220.00),
-- Bill 3
(3, 2, 1, 180.00),
(3, 8, 2, 120.00),
-- Bill 4 (5+ items)
(4, 4, 1, 1500.00),
(4, 5, 1, 750.00),
-- Bill 5
(5, 3, 1, 360.00),
-- Bill 6 (10+ items, 20% discount)
(6, 1, 4, 250.00),
(6, 2, 3, 180.00),
(6, 6, 5, 220.00),
(6, 7, 1, 850.00),
-- Bill 7 (5+ items)
(7, 1, 2, 250.00),
(7, 2, 2, 180.00),
(7, 6, 1, 220.00),
(7, 9, 1, 650.00),
-- Bill 8
(8, 2, 1, 180.00),
(8, 6, 1, 220.00),
(8, 8, 1, 120.00),
-- Bill 9 (5+ items)
(9, 4, 1, 1500.00),
(9, 5, 1, 750.00),
(9, 6, 1, 220.00),
-- Bill 10
(10, 7, 1, 850.00),
(10, 6, 1, 220.00),
-- Bill 11 (cancelled)
(11, 1, 3, 250.00),
(11, 7, 1, 850.00),
-- Bill 12 (10+ items)
(12, 1, 5, 250.00),
(12, 2, 4, 180.00),
(12, 6, 3, 220.00),
(12, 7, 2, 850.00),
(12, 9, 1, 650.00),
-- Bill 13 (5+ items)
(13, 2, 1, 180.00),
(13, 5, 1, 750.00),
(13, 10, 1, 180.00),
-- Bill 14
(14, 1, 1, 250.00),
(14, 8, 2, 120.00),
(14, 10, 1, 180.00),
-- Bill 15 (5+ items)
(15, 1, 4, 250.00),
(15, 6, 2, 220.00),
(15, 4, 1, 1500.00);
GO

-- ============================================================
-- Payments — mix of Cash and Card, mostly Approved, one Cancelled
-- ============================================================
INSERT INTO Payments (BillNo, Method, AmountPaid, ChangeAmount, Status, PayDate) VALUES
(1,  'Cash', 1000.00, 122.50, 'Approved', DATEADD(day, -28, GETDATE())),
(2,  'Card', 2084.94,   0.00, 'Approved', DATEADD(day, -27, GETDATE())),
(3,  'Cash',  600.00,  96.90, 'Approved', DATEADD(day, -25, GETDATE())),
(4,  'Card', 2263.95,   0.00, 'Approved', DATEADD(day, -22, GETDATE())),
(5,  'Cash',  500.00,  78.80, 'Approved', DATEADD(day, -20, GETDATE())),
(6,  'Card', 2854.80,   0.00, 'Approved', DATEADD(day, -18, GETDATE())),
(7,  'Cash', 1500.00, 236.40, 'Approved', DATEADD(day, -15, GETDATE())),
(8,  'Card',  678.60,   0.00, 'Approved', DATEADD(day, -12, GETDATE())),
(9,  'Card', 2527.20,   0.00, 'Approved', DATEADD(day, -10, GETDATE())),
(10, 'Cash', 1200.00,  88.50, 'Approved', DATEADD(day,  -8, GETDATE())),
(11, 'Card', 1842.75,   0.00, 'Cancelled', DATEADD(day,  -6, GETDATE())),
(12, 'Card', 3931.20,   0.00, 'Approved', DATEADD(day,  -5, GETDATE())),
(13, 'Cash', 1500.00, 341.70, 'Approved', DATEADD(day,  -3, GETDATE())),
(14, 'Cash', 1000.00, 157.60, 'Approved', DATEADD(day,  -1, GETDATE())),
(15, 'Card', 2948.40,   0.00, 'Approved', GETDATE());
GO

PRINT 'Test data inserted: 15 bills, ~40 items, 15 payments. 1 bill cancelled.';
GO