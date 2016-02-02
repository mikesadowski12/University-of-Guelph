        ORG		$8000

START      MOVE.W x,-(sp)
           MOVE.W y,-(sp)
           pea z
           jsr squared
           lea 14(sp),sp
           TRAP #14

squared    link a0,#-6 ;reserve 6 byte stack frame

           
           movea.l 14(sp),a1 ;move &z into a1
           
           move.w 20(sp),d2 
           muls d2,d2 
           move.w d2,-(a0) ;u=x*x
           
           move.w 18(sp),d1 
           muls d1,d1 
           move.w d1,-(a0) ;v=y*y
           
           move.w 20(sp),d4 
           muls 18(sp),d4 
           muls #2,d4 
           move.w d0,-(a0) ;w=2*x*y
           
           
           add.w 2(sp),d4 ;w+v
           add.w 4(sp),d4 ;u+w+v
           move.w d4,(a1) ;*z=u+w+v
           
           
           unlk a0
           rts

           ORG                $9000
x DC.W  5
y DC.W  6
z DS.W  1
           END START




; 5*x*x - 2*x*y + z*z







*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
