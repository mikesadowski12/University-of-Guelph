CREATE OR REPLACE FUNCTION p1(cusname char) RETURNS table(VendorName char(2), Date date, Amount decimal(6,2)) AS $$
DECLARE
        vendorname char(2);
        thedate date;
        theamount decimal(6,2);
    BEGIN
       RETURN QUERY SELECT Vendor.Vname, Transaction.T_Date, Transaction.Amount
        FROM Vendor JOIN Transaction ON Vendor.Vno = Transaction.Vno JOIN Customer ON Customer.Account = Transaction.Account
        WHERE Customer.Cname = cusname;
    END; $$
LANGUAGE plpgsql;
