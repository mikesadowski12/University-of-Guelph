*L3_1.x68: Simple program.
	
	ORG	$8000		;program starts at $8000
START   MOVE.B	VALUE1,D0	;load 1st byte from $9000
	MOVE.B	VALUE2,D1	;load 2nd byte from $9001
	ADD.B	D0,D1		;sum bytes
	MOVE.B	D1,RESULT	;store sum at $9002
	TRAP	#14		;return to 68KMB

	ORG	$9000
VALUE1	DC.B	11		;initialize RAM with 11
VALUE2	DC.B	22		;initialize RAM with 22
RESULT	DS.B	1		;reserve one byte of RAM
	END	START
