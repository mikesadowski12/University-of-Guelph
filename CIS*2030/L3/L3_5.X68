*L3_3: Sample program 3
	
	ORG	$8000

START   MOVE.W	Z+4,D0	;move 4 into d0
	    MOVE.B	Z+6,D1    ; move 2 into d1
	    MOVE.W  Z+8,d2    ; move 6 into d2
	    MULS    d0,d1       ;multiply W*Y result in d1 8
	    DIVS    #3,d2
	    ADD.W   d2,d1	    ;result is in d1

	ORG	$9000
Z	DC.L	1	;9000
W	DC.W	4   ;9004
Y	DC.B	2   ;9006
X	DC.W	6   ;9008
		
	END	START

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
