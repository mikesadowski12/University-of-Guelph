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
