-- UNBOUNDED INTEGERS
-- CIS*3190 - Assignment 2
-- Mike Sadowski

-- This program allows users to perform calculations that would otherwise cause 'integer overflow'
-- It allows factorial, multiplication, addition and subtraction calculations of any numbers
-- using linked lists to represent the resulting values to avoid the overflow

-- Program works by getting the user to input the operands as strings, then turning the string into linked lists to represend the entire number
-- If the lists are different sizes, the smaller list is padded with zero's to make them equal so that calculations are easily performed
-- Addition works by running through the lists, adding up each single digit. If the value is > 10, a carry is performed to provide the correct result
-- Subtraction works the similar to addition, except the larger number is always subtracting the smaller. Result is negative if the numbers need to be switched
-- Multiplication works by
-- Factorial works by

-----------------------------------------------------------------------------------------------------------------------------------------

with ada.Text_IO; use Ada.Text_IO;
with ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with ada.Float_Text_IO; use ada.Float_Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;

package body calculator is

	New_Node : Node_Ptr := null;  --New node to add to a list

-- Name: addition()
-- Description: Adds the 2 linked lists digit by digit, using borrows and carries as needed (just like if you were doing addition on paper)
-- Paramters: op1 = operand 1, op2 = operand 2
-- Return: The result as a linked list
        function addition (op1 : Node_Ptr; op2 : Node_Ptr) return Node_Ptr is
        Head: Node_Ptr;
        Scan_Ptr1: Node_Ptr;                  -- Scan the list.
        Scan_Ptr2: Node_Ptr;                  -- Scan the list.
        result : integer;
        carry : integer;
	borrow: Integer;

        begin
                Scan_Ptr1 := op1;
                Scan_Ptr2 := op2;
                Head := null;
                carry := 0;
		borrow := 0;

		--put("Scan1: "); 
		--Scan_Ptr1 := printList(Scan_Ptr1);
		--new_line;
		--put("Scan2: ");
		--Scan_Ptr2 := printList(Scan_Ptr2);
		--new_line;
		
                loop
                        -- If the list is entirely empty, bail out now.
                        exit when Scan_Ptr1 = null;
                        exit when Scan_Ptr2 = null;

			--put(Scan_Ptr1.Data);
			--put("+");
			--put(Scan_Ptr2.Data);
			--put("+");
			--put(carry);
			--put("+");
			--put(borrow);
			--new_line;
			--new_line;

			--Add the digits together, and the carry from the previous digits if the exceeded 10
                        result := Scan_Ptr1.Data + Scan_Ptr2.Data + carry - borrow;

                        --If there is a carry, subtract 10 and add a carry for the next number
                        if result >= 10 then
                                carry := 1;
                                result := result - 10;
			else
				carry := 0;
                        end if;

			--If the result is negative, and there is a next number, add 10 to the result and add a borrow
			-- to subtract from the next calculator
			if result < 0 and Scan_Ptr1.Next /= null then
                                borrow := 1;
				result := result + 10;
			else
				borrow := 0;
			end if;

                        --Add node to list
                        New_Node := new Node'(result, null);
                        New_Node.Next := Head;
                        Head := New_Node;

                        --Go to next element in the list
                        Scan_Ptr1 := Scan_Ptr1.Next;
                        Scan_Ptr2 := Scan_Ptr2.Next;

                        -- If there is no next, we are done.
                        exit when Scan_Ptr1 = null;
                end loop;

		--If a carry was left over, add a node for it
                if carry = 1 then
                        New_Node := new Node'(carry, null);
                        New_Node.Next := Head;
                        Head := New_Node;			
                end if;

		--new_line;
		--put("FINAL: ");
		--put(result);
		--new_line;

                -- if the result is negative, make entire list negative
                if Head /= null then
                        if Head.Data < 0 then
                                Scan_Ptr1 := Head.Next;

                        loop
                                Scan_Ptr1.Data := Scan_Ptr1.Data * (-1);
                                Scan_Ptr1 := Scan_Ptr1.Next;

                                exit when Scan_Ptr1 = null;
                        end loop;
                end if;
                end if;

                --return the result value in a linked list
                return Head;
        end addition;

-- Name: subtraction()
-- Description: Subtracts the two linked lists, using the addition() function and negating the second list (op2 * -1)
-- Paramters: op1 = operand 1, op2 = operand 2
-- Return: The result as a linked list
        function subtraction (operand1 : Node_Ptr; operand2 : Node_Ptr) return Node_Ptr is
	Head: Node_Ptr;
        Scan_Ptr1: Node_Ptr;                  -- Scan the list.
        Scan_Ptr2: Node_Ptr;                  -- Scan the list.

	begin
		Scan_Ptr1 := operand1;
		Scan_Ptr2 := operand2;

		--Make operand 2 negative, so that addition with a negative number will produce subtraction function
		loop
			Scan_Ptr2.Data := Scan_Ptr2.Data * (-1);

			Scan_Ptr2 := Scan_Ptr2.Next;
			exit when Scan_Ptr2 = null;
		end loop;
		
		-- Reset the pointer to top of list again
		Scan_Ptr2 := operand2;

		--Perform addition, but with the negated list. This will be a subtraction technically
		Head := addition(Scan_Ptr1, Scan_Ptr2);

		-- Reset the pointer to top of list again
                Scan_Ptr2 := operand2;

		-- Make the list positive again, crucial for factorial function
		loop
                        Scan_Ptr2.Data := Scan_Ptr2.Data * (-1);

                        Scan_Ptr2 := Scan_Ptr2.Next;
                        exit when Scan_Ptr2 = null;
                end loop;

		return Head;
	end subtraction;

-- Name: multiplication()
-- Description: Multiplies the 2 linked lists together digit by digit, using carries as needed. Uses addition() function to calculator final result
-- Paramters: operand1 = operand 1, operand2 = operand 2
-- Return: The result as a linked list
        function multiplication (operand1 : Node_Ptr; operand2 : Node_Ptr) return Node_Ptr is
        HeadResult: Node_Ptr;
        Scan_Ptr1: Node_Ptr;                  -- Scan the list.
        Scan_Ptr2: Node_Ptr;                  -- Scan the list.
        type resultArrayType is array(Integer range <>) of Node_Ptr;
        resultArray : resultArrayType(1 .. 3000);
        temp : Node_Ptr;
        carry : Integer := 0;
        result : Integer := 0;
        i : Integer := 0;
	--negativeFlag: Integer;

        begin

                Scan_Ptr1 := operand1;
                Scan_Ptr2 := operand2;
                temp := Scan_Ptr2;

		put("Scan1: ");
                Scan_Ptr1 := printList(Scan_Ptr1);
                new_line;
                put("Scan2: ");
                Scan_Ptr2 := printList(Scan_Ptr2);
                new_line;

                loop
                        -- If the list is entirely empty, bail out now.
                       -- exit when Scan_Ptr1 = null;

                        Scan_Ptr2 := temp;
                        i := i + 1;
                        carry := 0;

			loop
				--new_line;
				--put(Scan_Ptr1.Data);
                        	--put("+");
                        	--put(Scan_Ptr2.Data);
                        	--put("+");
                        	--put(carry);
				--new_line;

                                result := Scan_Ptr1.Data * Scan_Ptr2.Data + carry;
				
				--new_line;
				--put("RESULT: ");
				--put(result);
				--new_line;

				if abs(result) > 10 then
                                	carry := (result - (result mod 10))/10;
                                else
					carry := 0;
				end if;

				--new_line;
                                --put("carry: ");
                                --put(carry);
                                --new_line;

				result := (result - (carry * 10));

				--new_line;
                                --put("RESULT2: ");
                                --put(result);
                                --new_line;

                                New_Node := new Node'(result, null);
                                New_Node.Next := resultArray(i);
                                resultArray(i) := New_Node;

                                Scan_Ptr2 := Scan_Ptr2.Next;
                                
				-- If there is no next, we are done.
                                exit when Scan_Ptr2 = null;
                        end loop;

                        if carry > 0 then
                                New_Node := new Node'(carry, null);
                                New_Node.Next := resultArray(i);
                                resultArray(i) := New_Node;
                        end if;

                        Scan_Ptr1 := Scan_Ptr1.Next;
                        -- If the list is entirely empty, bail out now.
                        exit when Scan_Ptr1 = null;
                end loop;

		--Loop through all the elements of the list to pad a 0 to the right side, as if you were doing multiplication on paper
                -- eg   12
                --      12
                --      __
                --      2 4
                --    1 2 0   <----- Adds that zero
                for J in 1 .. i loop
                        temp := resultArray(J);

                        loop
                                exit when temp.Next = null;
                                temp := temp.Next;
                                --exit when temp.Next = null;
                        end loop;

                        --temp := printList(temp);

                        if temp /= null then
                                for K in 1 .. J-1 loop
                                        New_Node := new Node'(0, null);
                                        temp.Next := New_Node;
                                        temp := New_Node;
                                end loop;
                        end if;
                end loop;

		--for J in 1 .. i loop
                        --put("List: ");
                        --HeadResult := printList(resultArray(J));
                        --new_line;
                --end loop;

                --Store the first list in the array so that head is not null and can be added to
                HeadResult := resultArray(1);

                --Iterate through every list in the array starting at the 2nd, add the result to head, to return a total for the multiplication final value
                for J in 2 .. i loop
                        --Reverse each list to align the digits properly for the addition function
                        HeadResult := reverseList(HeadResult);
                        resultArray(J) := reverseList(resultArray(J));

                        --Pad Head with the required zeros to make it same size as next list element
                        HeadResult := balance(HeadResult, (countList(resultArray(J)) - countList(HeadResult)));

                        --Add the next list to Head, store new result in Head
                        HeadResult := addition(HeadResult, resultArray(J));
                end loop;
		
		put("Returned: ");
		HeadResult := printList(HeadResult);
		new_line;

                return HeadResult;
        end multiplication;

-- Name: factorial()
-- Description:	Performs the factorial math function on a number using the multiplication() function to hold the result
-- Paramters: operand = operand 1
-- Return: The result as a linked list
        function factorial (operand : Node_Ptr) return Node_Ptr is
        Head: Node_Ptr;
        subtract1List: Node_Ptr;
	next_value: Node_ptr;
	next_value2: Node_Ptr;

        begin
                Head := operand;
                next_value := operand;

		--Add the value 1 to a brand new list to always subtract from new_value to get the next value to multiply by
		New_Node := new Node'(1, null);
                New_Node.Next := subtract1List;
                subtract1List := New_Node;

                loop
			subtract1List := balance(subtract1List, ( countList(next_value) -  countList(subtract1List)));
	                --next_value := balance(next_value, ( countList(subtract1List) - countList(next_value)));

			next_value := subtraction(next_value, subtract1List);			
			
			--next_value := printList(next_value);
			new_line;

			exit when next_value.Data = 1;

			next_value2 := next_value;

			next_value2 := balance(next_value2, ( countList(Head) - countList(next_value) ));

                        Head := multiplication(Head, next_value2);
                end loop;

                return head;
        end factorial;
	
-- Name: createList()
-- Description: Iterates through the string digit by digit, storing each digit into a node of a linked list
-- Paramters: operand = operand 1 or 2 as a string, size = the amount of characters operand has
-- Return: The new list
	function createList (operand : String; size : Integer) return Node_Ptr is
        Head: Node_Ptr;
        convertInt : integer;
        negativeFlag : Integer := 0;

	begin
                --If the first digit is a minus sign, the entire number and all valu$
                if operand(operand'First) = '-' then
                        negativeFlag := 1;
                end if;

                for J in 1 .. size loop
                        --if the first character is a -, insert all numbers as negat$
                        if negativeFlag = 1 then
                                convertInt := Character'Pos(operand(J));
                                convertInt := convertInt - 48;
                                convertInt := convertInt * (-1); -- insert negative $
                        elsif negativeFlag = 0 then
                                convertInt := Character'Pos(operand(J));
                                convertInt := convertInt - 48; -- insert positive in$
                        end if;

                        --skip inserting the minus sign into the list
                        if operand(J) /= '-' then
                                New_Node := new Node'(convertInt, null);
				New_Node.Next := Head;
				Head := New_Node;
			end if;				
                end loop;
                return Head;
        end createList;

-- Name: printList()
-- Description: Display the entire contents of a list
-- Paramters: Head = the top of the list
-- Return: Returns the list with no changes
        function printList (Head : Node_Ptr) return Node_Ptr is
        Scan_Ptr: Node_Ptr;
        negativeFlag : Integer := 0;

        begin
                Scan_Ptr := Head;

                if Scan_Ptr = null then
                        return null;
                end if;

		--Skip printing any leading 0's
                loop
                        exit when Scan_Ptr.Data /= 0;
                        Scan_Ptr := Scan_Ptr.Next;

                        if Scan_Ptr = null then
                                put(0);
                                return Head;
                        end if;
               end loop;

                --If first number was negative, all numbers in list were negative
                --Want to avoid printing all numbers in the list as negative
                --if Scan_Ptr.Data < 0 then
                        --Head.Data := Head.Data * (-1);
                        --Put("-");
                --end if;

                loop
                -- If the list is entirely empty, bail out now.
                        exit when Scan_Ptr = null;

                        if negativeFlag = 1 then
                                Scan_Ptr.Data := Scan_Ptr.Data * (-1);
                        end if;

                -- Print, go to next.
                        Put(Scan_Ptr.Data, Width => 0);
                        Scan_Ptr := Scan_Ptr.Next;

                -- If there is no next, we are done.
                        exit when Scan_Ptr = null;

                -- Since there is a next, print a space to separate the items.
                        --Put(" ");
                end loop;

                return Head;
        end printList;

-- Name: reverseList()
-- Description: Reverses the order of all the nodes in the list. Used to align the list's digits properly when performing math functions on them
-- Paramters: operand = the list
-- Return: The reversed list
        function reverseList(operand : Node_Ptr) return Node_Ptr is
        Head: Node_Ptr;
        Scan_Ptr1: Node_Ptr;                  -- Scan the list.

        begin
                Scan_Ptr1 := operand;

                loop
                -- If the list is entirely empty, bail out now.
                        exit when Scan_Ptr1 = null;

                        -- Add the node to the list, it will reverse the order of the list (first becomes last)
			New_Node := new Node'(Scan_Ptr1.Data, null);
                        New_Node.Next := Head;
                        Head := New_Node;

                        Scan_Ptr1 := Scan_Ptr1.Next;
                        exit when Scan_Ptr1 = null;
                end loop;
                return Head;
        end reverseList;

-- Name: balance()
-- Description: Adds a required amount of zeros to a list. Used to make 2 lists equal size in node count
-- Paramters: operand = the list, howMany = the amount of zeros to be added
-- Return: The new list, paded with zeros
        function balance(operand : Node_Ptr; howMany : Integer) return Node_Ptr is
        Head: Node_Ptr;
        Scan_Ptr1: Node_Ptr;                  -- Scan the list.
        prev : Node_Ptr;

        begin
                Scan_Ptr1 := operand;

                loop
                -- If the list is entirely empty, bail out now.
                        exit when Scan_Ptr1 = null;

                        Scan_Ptr1 := Scan_Ptr1.Next;
                        prev := Scan_Ptr1;

                        -- Once at the end of the list, add 'howMany' zeros to the end
                        if Scan_Ptr1 = null then
                                for J in 1 .. howMany loop
                                        New_Node := new Node'(0, null);
                                        New_Node.Next := Head;
                                        Head := New_Node;
                                end loop;
                                exit;
                        end if;
                end loop;

		-- Reverse the entire order of the list to make it same order as the 2nd list
                Scan_Ptr1 := reverseList(operand);

                -- Add all the values into Head, to return
                loop
                -- If the list is entirely empty, bail out now.
                        exit when Scan_Ptr1 = null;

                        New_Node := new Node'(Scan_Ptr1.Data, null);
                        New_Node.Next := Head;
                        Head := New_Node;

                        Scan_Ptr1 := Scan_Ptr1.Next;
                        exit when Scan_Ptr1 = null;
                end loop;

        return Head;
        end balance;

-- Name: countList()
-- Description: Counts the nodes in the list to tell which one is longer than the other for padding zeros
-- Paramters: Head = the list
-- Return: Number of nodes as an integer       
	 function countList(Head : Node_Ptr) return Integer is
        count : Integer := 0;
        Scan_Ptr1: Node_Ptr;                  -- Scan the list.

        begin
                Scan_Ptr1 := Head;

                -- Get size of operand1 list
                loop
                        exit when Scan_Ptr1 = null;
                        count := count + 1;

                        Scan_Ptr1 := Scan_Ptr1.Next;
                end loop;
        return count;
        end countList;
end calculator;
