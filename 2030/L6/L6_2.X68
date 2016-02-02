            ORG		$8000

START	LEA word1,a1     ;load word1 into a1
           LEA word2,a2    ;load word2 into a2
           CLR.W d2
           CLR.W d3
           MOVE.L #index,d1   ;put length of the words into d1

loop       BEQ.S same_word    ;once d1=0, the words were the same
           MOVE.B (a1)+,d2   ;put character into d2 from word1
           MOVE.B (a2)+,d3  ;put character into d3 from word2
           CMP.B d2,d3
           BNE wrong
           SUBQ.B #1,d1   ;decrement d1 for every letter checked
           BRA loop

same_word  MOVE.B #$FF,d0
           TRAP #14

wrong       MOVE.B #$00,d0
            TRAP #14


           ORG                $9000

word1 DC.B '',$0D
word2 DC.B '',$0D
sum   DS.W 1
index EQU (sum-word1)/2

           END START

*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
