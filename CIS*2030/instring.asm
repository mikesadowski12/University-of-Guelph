DUART      EQU         $C001
IPR        EQU         13*2
OPR_SET    EQU         14*2
OPR_CLR    EQU         15*2

           ORG         $8000
WIRE681    MOVEA.L     #DUART,a0

LOOP       MOVE.B      IPR(a0),d0
           ANDI.B      #$FF,d0
           BSR.S       OUT681
           BRA         LOOP


OUT681     MOVE.B      d0,OP_CLR(a0)
           NOT.B       d0
           MOVE.B      OPR_SET(a0)
           NOT.B       d0
           RTS
           END         WIRE681



