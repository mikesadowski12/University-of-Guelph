*L4_6.x68     

	ORG	$8000
START  	MOVEA.L #MATRIX,A0	  
	MOVE.W	#8,D2		  
	MULU	#1,D2		  
	MOVE.W	4(A0,D2.L),D3
	MULU	#3,D2
	MOVE.W	6(A0,D2.L),D4
    ADD.W   d3,d4 
	TRAP	#14
	

**** 4 x 4 matrix ****

	ORG	$9000		
MATRIX	DC.W	1,2,3,4
	DC.W	5,6,7,8
	DC.W	9,10,11,12
	DC.W	13,14,15,16
	END	START

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
