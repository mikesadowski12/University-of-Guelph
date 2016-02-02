*Lab5_2.x68: Signed and Unsigned Branches
	 
	  ORG	     $8000
START	  MOVE.B   #%11110000,D0
	  MOVE.B   #%00000001,D1
	  CMP.B    D0,D1
	  BGT	   LABEL1             
	  NOP
LABEL1 	  BHI	   LABEL2		      
	  NOP
LABEL2    TRAP     #14
          END      START
