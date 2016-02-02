CREATE OR REPLACE FUNCTION p4() RETURNS table(AccountNum char(2), CustomerName char(255), Amount decimal(6,2), VendorName char(255)) AS $$
DECLARE
        vendorname char(2);
        thedate date;
        theamount decimal(6,2);
    BEGIN
       RETURN QUERY SELECT Transaction.Account, Customer.Cname, Transaction.Amount, Vendor.Vname
        FROM Vendor JOIN Transaction ON Vendor.Vno = Transaction.Vno JOIN Customer ON Customer.Account = Transaction.Account
        WHERE Transaction.T_Date = (select max(T_Date) from Transaction);
    END; $$
LANGUAGE plpgsql;
