CREATE OR REPLACE FUNCTION p2(venname char) RETURNS table(Account char(2), CustomerName char(255), Province char(255)) AS $$
DECLARE
        vendorname char(2);
        thedate date;
        theamount decimal(6,2);
    BEGIN
        RETURN QUERY SELECT Customer.Account, Customer.Cname, Customer.Province
        FROM Vendor JOIN Transaction ON Vendor.Vno = Transaction.Vno JOIN Customer ON Customer.Account = Transaction.Account
        WHERE Vendor.Vname = venname;
    END; $$
LANGUAGE plpgsql;




