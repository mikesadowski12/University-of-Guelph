        ORG		$8000

START      MOVE.W x,-(sp)
           jsr solve_quad
           TRAP #14


solve_quad move.l d1,-(sp)
           move.l d0,-(sp)
           move.w 12(sp),d0 ;move x into d0
           move.w 12(sp),d1 ;move x into d1
           
           muls d0,d0   ;x^2
           muls #5,d0   ;5*x^2

           muls #2,d1
           addi.w #6,d1

           sub.w d1,d0 ;left - right side
           move.l 4(sp),d1
           move.l (sp),d0
           rts
           
           ORG                $9000
x DC.W  5
           END START




; 5*x*x-2*x+6




*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
