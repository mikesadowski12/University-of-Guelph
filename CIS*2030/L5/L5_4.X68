*Lab5_3.x68: Signed and Unsigned Branches      
	 
	     ORG	  $8000
START	 MOVE.B   num1,d1   
         MOVE.B   num2,d2
         MOVE.B   num3,d3
         
if       CMP.B   num1,d2 
         BGT      else   ;if num2 >= num1, branch to else     
         CMP.B   num1,d3 
         BGT      else_if ;if num3 >= num1, branch to else if
         MOVE.B  num1,d0 ;biggest = num1
         BRA    exit 
           
else_if  MOVE.B  num3,d0 ;biggest = num3
         BRA    exit

         
else     CMP.B   num2,d3
         BGT      else_if ;if num3 >= num2, branch to else if    
         MOVE.B  num2,d0 ;biggest = num2
                                 	   
exit 	 trap #14
           
         
            ORG   $9000
num1    DC.B  41  
num2    DC.B  43
num3    DC.B  42
            end START          
*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
