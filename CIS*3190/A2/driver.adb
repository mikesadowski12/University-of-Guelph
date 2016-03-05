-- UNBOUNDED INTEGERS
-- CIS*3190 - Assignment 2
-- Mike Sadowski

-- This program allows users to perform calculations that would otherwise cause 'int$
-- It allows factorial, multiplication, addition and subtraction calculations of any$
-- using linked lists to represent the resulting values to avoid the overflow

-- Program works by getting the user to input the operands as strings, then turning $
-- If the lists are different sizes, the smaller list is padded with zero's to make $
-- Addition works by running through the lists, adding up each single digit. If the $
-- Subtraction works the similar to addition, except the larger number is always sub$
-- Multiplication works by
-- Factorial works by

------------------------------------------------------------------------------------$

with ada.Text_IO; use Ada.Text_IO;
with ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with ada.Float_Text_IO; use ada.Float_Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with calculator; use calculator;

procedure driver is

        package SU renames Ada.Strings.Unbounded;
        package T_IO renames Ada.Text_IO;

        operator : character; -- the operator used on the 2 operands
        operand1, operand2 : String (1 .. 100); -- the operands
        o1size, o2size : integer; --the length of the operands

        operand1List: Node_Ptr;              -- Head of the operand 1 list.
        operand2List: Node_Ptr;              -- Head of the operand 2 list.
        resultList: Node_Ptr;                -- Head of result list
        --New_Node: Node_Ptr;                  -- Created node.
	flag: Integer;

-- FUnction to pad the smaller list with zeros so that both lists are same size
-- param is not used, just couldn't figure out how to make it not take any parameters
        function balanceList(param : Integer) return Integer is

        op1Count : Integer := 0;
        op2Count : Integer := 0;
        Scan_Ptr1: Node_Ptr;                  -- Scan the list.
        Scan_Ptr2: Node_Ptr;                  -- Scan the list.

        begin

                Scan_Ptr1 := operand1List;
                Scan_Ptr2 := operand2List;

                -- Get size of operand1 list
                op1Count := countList(Scan_Ptr1);

                -- Get size of operand2 list
                op2Count := countList(Scan_Ptr2);

                --pad the smaller list with zeros in the amount of the difference between the 2 lists
                if op1Count > op2Count then
                        operand2List := balance(operand2List, op1Count-op2Count);
                elsif op1Count < op2Count then
                        operand1List := balance(operand1List, op2Count-op1Count);
                else
                        return 1;
                end if;

                return 1;
        end balanceList;	

--Function to calculate the result of operand1 and operand2 using the operator
        function calculateResult (operand1 : Node_Ptr; operand2 : Node_Ptr; o1size : Integer) return Node_Ptr is
        Head: Node_Ptr;
        begin
                Head := null;

                if operator = '+' then
                        Head := addition(operand1, operand2);
                elsif operator = '-' then
                        Head := subtraction(operand1, operand2);
                elsif operator = '*' then
                        Head := multiplication(operand1, operand2);
                elsif operator = '!' then
                        Head := factorial(operand1);
			--put_line("hello");
                 else
                        put("Incorrect operator. Please try again.");
                        return null;
                end if;

                return Head;
        end calculateResult;

begin
        new_line;
        new_line;
        --Get all required information from the user for the calculation
        put_line("> Enter first operand: ");
        get_line(operand1, o1size);

        put_line("> Enter operation: + , - , * or !");
        get(operator);

        put_line("> Enter second operand: ");
        get_line(operand2, o2size);
        get_line(operand2, o2size);

        --Build the 2 Lists, each node contains 1 digit of the number
        operand1List := createList(operand1, o1size);
        operand2List := createList(operand2, o2size);

	if operator /= '*' then
                --Pad 0's to the smaller list to make lists equal in node count
                flag := balanceList(1);
        end if;

	new_line;
	new_line;
	put("OP1: ");
	operand1List := printList(operand1List);
        new_line;
	put("OP2: ");
        operand2List := printList(operand2List);
	new_line;

        --Build the result list
        resultList := calculateResult(operand1List, operand2List, o1size);

        --Print the result list
        new_line;
        if resultList /= null then
                put_line("The result is: ");
                resultList := printList(resultList);
        end if;
        new_line;
        new_line;
end driver;



