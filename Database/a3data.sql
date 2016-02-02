CREATE TABLE Vendor (Vno char(2), Vname char(255), City char(255), Vbalance decimal(6,2));
CREATE TABLE Customer (Account char(2), Cname char(255), Province char(255), Cbalance decimal(6,2), Crlimit int);
CREATE TABLE Transaction (Tno char(2), Vno char(2), Account char(2), T_Date date, Amount decimal(6,2));

INSERT INTO Vendor VALUES ('V1', 'Sears', 'Toronto', 200.00),
('V2', 'Walmart', 'Waterloo', 671.05),
('V3', 'Esso', 'Windsor', 0.00),
('V4', 'Esso', 'Waterloo', 225.00);

INSERT INTO Customer VALUES 
('A1', 'Smith', 'ONT', 2515.00, 2000),
('A2', 'Jones', 'BC', 2014.00, 2500),
('A3', 'Doc', 'ONT', 150.00, 1000);

INSERT INTO Transaction VALUES 
('T1', 'V2', 'A1', '2015-07-15', 1325.00),
('T2', 'V2', 'A3', '2014-12-16', 1900.00),
('T3', 'V3', 'A1', '2015-09-01', 2500.00),
('T4', 'V4', 'A2', '2015-03-20', 1613.00),
('T5', 'V4', 'A3', '2015-07-31', 3312.00);

