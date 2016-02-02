DUART   EQU     $00C001
ISR     EQU     $A
CTUR    EQU     6*2
STOP    EQU     $1E
OPR_SET EQU     $1C
OPR_CLR EQU     $1E
COUNT   EQU     14400

        ORG     $8000
EIGHTHZ MOVEA.L #DUART,A0
        MOVE.W  COUNT,D0
        MOVEP.W D0,CTUR(A0)
        MOVE.B  #$11,D1

LOOP    MOVE.B  ISR(A0),D0
        AND.B   #8,D0
        BEQ     LOOP
        TST.B   STOP(A0)
        MOVE.B  #%11111111,OPR_SET(A0)
LOOP2   MOVE.B  ISR(A0),D0
        AND.B   #8,D0
        BEQ     LOOP2
        TST.B   STOP(A0)
        MOVE.B  #%11111111,OPR_CLR(A0)
        BRA     LOOP
        END     EIGHTHZ
        


*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
