*Lab5_1.x68: Relative addressing

	ORG	  $4030
START	BEQ  	  HERE
	NOP
	ORG	  $4040
HERE	BNE	  START
	END	  START
