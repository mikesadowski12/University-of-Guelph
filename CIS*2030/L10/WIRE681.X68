DUART   EQU     $00C001
IPR     EQU     $1A
OPR_SET EQU     $1C
OPR_CLR EQU     $1E

        ORG     $8000
WIRE681 MOVEA.L #DUART,A0
LOOP    MOVE.B  IPR(A0),D0
        BSR     OUT681
        BRA LOOP
        
OUT681  MOVE.B  D0,OPR_CLR(A0)
        NOT.B   D0
        MOVE.B  D0,OPR_SET(A0)
        RTS
        END     WIRE681
*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
