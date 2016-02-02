DUART   EQU     $C001
SRA     EQU     2
RBA     EQU     6

        ORG     $8000
MESSAGE LEA     DUART,A0
        MOVEA.L #TEXT,A1
        BSR     INSTR
        TRAP    #14
        
INSTR   MOVEQ   #10,D2
INSTR2  MOVE.B  SRA(A0),D7
        ANDI.B  #1,D7
        BEQ     INSTR2
        MOVE.B  RBA(A0),(A1)
        CMPI.B  #$0d,(A1)+
        BEQ     EXIT
        BRA     INSTR2
        
EXIT    MOVE.B  #0,(A1)
        RTS

TEXT    DS.B    11        
        END     MESSAGE


*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
