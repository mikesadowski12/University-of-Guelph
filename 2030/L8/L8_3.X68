        ORG		$8000

START      MOVE.W x,-(sp)
           MOVE.W y,-(sp)
           MOVE.W z,-(sp)
           pea w
           jsr solve_quad
           lea 12(sp),sp
           TRAP #14


solve_quad movem.l D0-D2/A0
                    
           move.w 20(sp),d0 ;move z into d0
           move.w 22(sp),d1 ;move y into d1
           move.w 24(sp),d2 ;move x into d2
           movea.l 16(sp),a0 ;move &w into a0

           muls d2,d2
           muls #5,d2   ;5*x^2

           muls 24(sp),d1 ;2*x*y
           muls #2,d1

           muls d0,d0
           
           sub.w d1,d2 ;left - right side
           add.w d0,d2
           move.w d2,(a0)
           movem.l (sp)+,D0-D2/A0
           
           rts

           ORG                $9000
x DC.W  5
y DC.W  6
z DC.W  7
w DS.W  1
           END START

; 5*x*x - 2*x*y + z*z






*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
