C                dc.b            $A

START org $8000


        MOVE.W C, d0   ;load number to convert
        MOVE.W #9, d1    ;load 9 to multiply with later
        MOVE.W #5, d2    ;load 5 to divide with later
        MOVE.W #32, d3   ;load 32 to add to total later



        MULS d0, d1
        DIVS d2, d1
        ADD.W d3, d1
        TRAP #15
        END START