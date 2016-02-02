*L2_3.x68: Adds four 8-bit integers using byte addition

	ORG       $8000
PROGRAM	MOVE.L	#$21,D0	
	ADD.B	#$57,D0	
	ADD.B	#$B9,D0	 
	ADD.B	#$7D,D0
	TRAP	#14
	END	PROGRAM
