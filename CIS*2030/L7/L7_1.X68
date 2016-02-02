        ORG		$8000

START	MOVE.W num1,d0
           MOVE.W num2,d1
           BTST #0,d1
           BNE odd_number

LOOP       LSL #1,d0
           LSR #1,d1

           CMPI.W #1,d1
           BLE  done

           BTST #0,d1
           BNE odd_number
           BRA LOOP

odd_number ADD.W d0,d2
           BRA LOOP
           
done       ADD.W d0,d2
           TRAP #14

           ORG                $9000
num1 DC.W  $ffff
num2 DC.W  $FFFF
           END START


*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
