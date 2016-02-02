*Lab5_3.x68: Signed and Unsigned Branches      
	 
	     ORG	  $8000
START	 MOVE.B   #7,d0   
         MOVE.B   CHARCODE,d1
         
         CMPI.B   #39,HEXVALUE
         BLE      exit ;if #39 > HEXVALUE       
         ADD.B    CHARCODE,d0 ;add 0x07 to CHARCODE         	   
exit 	 trap #14
           
          
            ORG   $9000
HEXVALUE    DC.B  40  
CHARCODE    DC.B  43
            end START          

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
