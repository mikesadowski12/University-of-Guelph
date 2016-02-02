*L2_1.x68: Performs a series of moves (copies) involving data registers

	ORG	$8000
PROGRAM	MOVE.B	D0,D1
	MOVE.W	D0,D2
	MOVE.L	D0,D3
	MOVE	D0,D4
	TRAP	#14
	END	PROGRAM
