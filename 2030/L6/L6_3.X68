            ORG		$8000
START	LEA matrix,a0                ;load address of matrix into a0
           MOVEA.L #0,a1                ;i=0




loop1      MOVEA.L a1,a2
           ADDA.L #1,a2                ; j=i+1

loop2
           MOVE.W a1,d0
           MULU.W #4,d0                 ; offset into the matrix[i]
           MOVE.W d0,a3                
           ADDA.L a2,a3                ;offset into the matrix[i][j]
           ADDA.L #matrix,a3
           MOVE.B (a3),d1              ;temp = matrix[i][j]


           MOVE.W a2,d0
           MULU.W #4,d0
           MOVE.W d0,a4                ;offset into the matrix[j]
           ADDA.L a1,a4                ;offset into the matrix[j][i]
           ADDA.L #matrix,a4
           MOVE.B (a4),(a3)              ;matrix[i][j] = matrix[j][i]


           MOVE.B d1,(a4)              ;matrix[j][i] = temp


           ADDA.L #1,a2                ;increment loop 2
           CMPA #04,a2  ; j <= 3
           BMI loop2       ;if a2 <=3, keep looping
           

           ADDA.L #1,a1      ;increment loop 1
           CMPA #03,a1  ; i <= 2
           BMI loop1        ;if a1 <=2 keep looping

done       TRAP #14


           ORG                $9000
matrix DC.B 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16
sum   DS.W 1
index EQU (sum-matrix)/2
           END START
*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
