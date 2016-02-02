*L3_3: Sample program 3
	
	ORG	$8000

START   MOVE.W	W,D0	
	    MOVE.B	Y,D1
	    MOVE.W  X,d2
	    MULS    d0,d1       ;multiply W*Y result in d1
	    DIVS    #3,d2
	    ADD.W   d2,d1	

	ORG	$9000
Z	DC.W	1	;9000
W	DC.W	2   ;9001
Y	DC.B	3   ;9002
X	DC.W	3   ;9003
		
	END	START

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
