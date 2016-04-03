CREATE OR REPLACE FUNCTION p3(newacc char(2), newname char(255), newprov char(255), newcrlimit int) RETURNS VOID AS $$
DECLARE
        vendorname char(2);
        thedate date;
        theamount decimal(6,2);
    BEGIN
        INSERT INTO Customer VALUES (newacc, newname, newprov, 0, newcrlimit);
    END; $$
LANGUAGE plpgsql;
