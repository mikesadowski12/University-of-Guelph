*L3_2.x68:  Sample program 2

CODE	EQU		$8000
DATA	EQU		$9000	

	ORG		CODE
START	MOVE.W  	$9000,D0
	MULU		#7,D0
	DIVU		#3,D0
	ADD.W	 	$9004,D0
	MOVE.W		D0,$9002
	TRAP		#14

	ORG		DATA
	DC.W		$10
	DS.W		1
	DC.W		10
	END		START
