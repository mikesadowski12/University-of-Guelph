DUART   EQU     $00C001
ACR     EQU     4*2
CTUR    EQU     6*2
CTLR    EQU     7*2
OPCR    EQU     13*2
COUNT   EQU     14400

        ORG     $8000
TWOHZ   MOVEA.L #DUART,A0
        MOVE.W  #COUNT,D0
        MOVEP.W D0,CTUR(A0)
        MOVE.B  #$70,ACR(A0)
        MOVE.B  #$04,OPCR(A0)
i        BRA    i
        
        END     TWOHZ


*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
