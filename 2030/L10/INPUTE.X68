DUART   EQU     $C001
SRA     EQU     2
RBA     EQU     6

        ORG     $9000
START   LEA     DUART,A0
LOOP    MOVE.B  SRA(A0),D7
        ANDI.B  #1,D7
        BEQ     LOOP
*        MOVE.B  RBA(A0),D0
        END     START
*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
