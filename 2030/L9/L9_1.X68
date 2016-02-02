        ORG		$8000

START      move.w #1234,-(sp)
           jsr display
           lea  2(sp),sp
           trap #14

display    link a6,#-4
           clr.l d1
           clr.l d2
           move.w 8(a6),d2

           cmpi #0,8(a6) ;if(n==0)
           bne  AA
           move.w 8(a6),d2 ;return n
           BRA BB


AA         move   8(a6),d1 ; remainder = n % 10
           DIVU  #10,d1
           SWAP d1
           move.w d1,-(sp) ;push remainder onto stack

           clr.l d1
           
           move.w 8(a6),d1  ; quotient = n/10
           DIVU  #10,d1
           move.w d1,-(sp) ;push quotient onto stack
           jsr display ;display(quotient)
           clr.l d0
           move.w -6(a6),d0
           ADD.B #'0',d0          ; print char to screen
           trap #1

BB         movem.l (sp)+,D0-D2/A6
           unlk   a6
                                
           rts
           END START

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
