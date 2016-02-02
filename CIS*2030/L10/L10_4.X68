DUART   EQU     $C001
SRA     EQU     2
RBA     EQU     6
OPR_SET EQU     $1C
OPR_CLR EQU     $1E

        ORG     $8000
MESSAGE LEA     DUART,A0
        MOVEA.L #TEXT,A1
        BSR     INSTR
        TRAP    #14
        
INSTR   MOVEQ   #10,D2
INSTR2  MOVE.B  SRA(A0),D7
        ANDI.B  #1,D7
        BEQ     INSTR2
        MOVE.B  RBA(A0),D0
        MOVE.B  D0,OPR_SET(A0)
        NOT.B   D0
        MOVE.B  D0,OPR_CLR(A0)
        NOT.B   D0
        CMPI.B  #'0',D0
        BNE     INSTR2
*        MOVE.B  #%11111111,OPR_CLR(A0)
        RTS

TEXT    DS.B    11        
        END     MESSAGE
*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
