*L4_6.x68     

	ORG	$8000
START  	MOVEA.L #MATRIX,A0	  
	MOVE.W	#4,D2		  
	MULU	#1,D2		  
	MOVE.B	2(A0,D2.L),D3
	MULU	#3,D2
	MOVE.B	3(A0,D2.L),D4
    ADD.B   d3,d4 
	TRAP	#14
	

**** 4 x 4 matrix ****

	ORG	$9000		
MATRIX	DC.B	1,2,3,4
	DC.B	5,6,7,8
	DC.B	9,10,11,12
	DC.B	13,14,15,16
	END	START

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
