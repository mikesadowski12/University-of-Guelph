DUART   EQU     $C001
SRA     EQU     2
TBA     EQU     6
CR      EQU     $0D
LF      EQU     $0A

        ORG     $8000
MESSAGE MOVE.W  #10,D7
LOOP    MOVEA.L #TEXT,A1
        BSR     OUTSTR
        SUBQ    #1,D7
        BNE     LOOP
        TRAP    #14
        
TEXT    DC.B    CR,LF,'Assembly language programming'
        DC.B    ' is fun',0
        
OUTCHR  MOVE.L  A0,-(A7)
        MOVE.W  D7,-(A7)
        MOVEA.L #DUART,A0
OUTCHR2 MOVE.B  SRA(A0),D7
        ANDI.B  #4,D7
        BEQ     OUTCHR2
        MOVE.B  RBA(A0),D0
        MOVE.B  D0,TBA(A0)
        MOVE.W  (A7)+,D7
        MOVE.L  (A7)+,A0
        RTS
        
OUTSTR  MOVE.L  D0,-(A7)
OUTSTR2 MOVE.B  (A1)+,D0
        BEQ     EXIT
        BSR     OUTCHR
        BRA     OUTSTR2
EXIT    MOVE.L  (A7)+,D0
        RTS
        
        END     MESSAGE

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
