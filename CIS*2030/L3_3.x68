*L3_3: Sample program 3
	
	ORG	$8000

START   MOVE.B	$9001,D0	;memory address
	MOVE.B	VAR1+1,D0	;assemble-time expression
	MOVE.B	VAR2,D0		;label
	TRAP	#14		

	ORG	$9000
VAR1	DC.B	1	
VAR2	DC.B	2
VAR3	DC.B	3
		
	END	START
