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

package calculator is
	
	type Node;
        type Node_Ptr is access Node;        -- Node_Ptr points to the nodes.

        type Node is record
                Data: Integer;               -- A single digit of the entire number
                Next: Node_Ptr;
        end record;

	function createList (operand : String; size : Integer) return Node_Ptr;
	function printList (Head : Node_Ptr) return Node_Ptr;
	function reverseList(operand : Node_Ptr) return Node_Ptr;
	function balance(operand : Node_Ptr; howMany : Integer) return Node_Ptr;
	function countList(Head : Node_Ptr) return Integer;

	function addition (op1 : Node_Ptr; op2 : Node_Ptr) return Node_Ptr;
	function subtraction (operand1 : Node_Ptr; operand2 : Node_Ptr) return Node_Ptr;
	function multiplication (operand1 : Node_Ptr; operand2 : Node_Ptr) return Node_Ptr;	
	function factorial (operand : Node_Ptr) return Node_Ptr;
	
end calculator;
