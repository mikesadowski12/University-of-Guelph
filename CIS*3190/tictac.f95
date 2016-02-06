! A PROGRAM TO PLAY TIC-TAC-TOE
      PROGRAM TICTACTOE
      
      CHARACTER * 1 TICTAC(3,3), WINNER
      LOGICAL OVER
      LOGICAL CHKPLAY
      INTEGER MOVE, TURN
      CHARACTER(LEN=100) :: FMT
      FMT = "(2X,A1,1X,'|',1X,A1,1X,'|',1X,A1,1X)"

      WRITE(*,*) "PLAY TIC-TAC-TOE. ENTER 1-9 TO PLAY"
      WRITE(*,*) " "
      WRITE(*,*) "        1 | 2 | 3 "
      WRITE(*,*) "       ---+---+---"
      WRITE(*,*) "        4 | 5 | 6 "
      WRITE(*,*) "       ---+---+---"
      WRITE(*,*) "        7 | 8 | 9 "
      WRITE(*,*) " "
            
      CALL BOARDSETUP(TICTAC)

	DO !start game loop
	DO !start user input loop, loop until a number between 1-9 is entered, and box is empty
                TURN = 0 !set turn to be user's turn
        	WRITE(*,*) "Your move? "
        	READ(*,*) MOVE
        	IF (MOVE < 1 .OR. MOVE > 9) THEN
                	WRITE(*,*) "Invalid input."
        	ELSE IF (.NOT. CHKPLAY(TICTAC,MOVE)) THEN
                	WRITE(*,*) "Invalid move, box already occupied."
        	ELSE
                	IF (MOVE == 1) TICTAC(1,1) = "X"
                	IF (MOVE == 2) TICTAC(1,2) = "X"
                	IF (MOVE == 3) TICTAC(1,3) = "X"
                	IF (MOVE == 4) TICTAC(2,1) = "X"
                	IF (MOVE == 5) TICTAC(2,2) = "X"
                	IF (MOVE == 6) TICTAC(2,3) = "X"
                	IF (MOVE == 7) TICTAC(3,1) = "X"
                	IF (MOVE == 8) TICTAC(3,2) = "X"
               		IF (MOVE == 9) TICTAC(3,3) = "X"
                	EXIT !exit user input loop when input is between 1-9 and box is empty
        	END IF
	END DO !end user input loop

! Print game board after each move
	DO !start auto loop, draws board after each turn and computer moves
		IF (TURN == 0) WRITE(*,*) "After your move..." !draw board after player turn
		IF (TURN == 1) WRITE(*,*) "After my move..." !draw board after computer turns
		
		!draw the board
		DO I=1,3 
	       
       		!FMT is a string formats the output for WRITE (initialized at top of program) 
		WRITE(*,FMT) (TICTAC(I,J), J=1,3)	
		WRITE(*,*) "---+---+---"
 	END DO !end iteration loop


! Check if game over 
	CALL CHKOVR(TICTAC,OVER,WINNER)
	IF (OVER) THEN
	       	IF (WINNER == "D") THEN
		WRITE(*,*) "The game is a draw. "
		ELSE
		WRITE(*,*) "The winner is: ", WINNER
		END IF
		STOP !if the game has ended, this stops the program
	END IF
	
	IF (TURN == 0) THEN ! if it's the players turn, let computer go
		TURN = 1
		CALL COMPMOVE(TICTAC)
	ELSE
		EXIT
	END IF
	END DO !end autoloop
 	END DO !end game loop   
	END
            
! SUBROUTINE TO CHECK TO SEE IF THE GAME IS OVER      
! =========================================
      SUBROUTINE CHKOVR(TICTAC,OVER,WINNER)
      CHARACTER * 1 TICTAC(3,3), WINNER
      LOGICAL OVER
      
      CHARACTER * 1 BLANK, DRAW
      PARAMETER (BLANK = ' ', DRAW = 'D')

      LOGICAL SAME
      LOGICAL DSAME
      INTEGER IR, IC

! ASSUME GAME IS OVER AT START
      OVER = .TRUE.

! CHECK FOR A WINNER
! CHECK ROWS FOR A WINNER
      DO IR = 1, 3
      	IF (SAME(TICTAC(IR,1),TICTAC(IR,2),TICTAC(IR,3))) THEN
      		WINNER = TICTAC(IR,1)
      		RETURN
      	END IF
      END DO

! NO WINNER BY ROWS, CHECK COLUMNS FOR A WINNER
      DO IC = 1, 3
      	IF (SAME(TICTAC(1,IC),TICTAC(2,IC),TICTAC(3,IC))) THEN
      		WINNER = TICTAC(1,IC)
      		RETURN
      	END IF
      END DO

! NO WINNER BY ROWS OR COLUMNS, CHECK DIAGONALS
      DSAME = SAME(TICTAC(1,1),TICTAC(2,2),TICTAC(3,3)) & 
        .OR. SAME(TICTAC(1,3),TICTAC(2,2),TICTAC(3,1)) 
      IF (DSAME) THEN
      WINNER = TICTAC(2,2)
      RETURN
      END IF

! NO WINNER AT ALL. SEE IF GAME IS A DRAW
! CHECK EACH ROW FOR AN EMPTY SPACE
      DO IR = 1,3
      	DO IC = 1,3
      		IF (TICTAC(IR,IC) == BLANK) THEN
      			OVER = .FALSE.
      			RETURN
      		END IF
	END DO  
       END DO

! NO BLANK FOUND, GAME IS A DRAW
      WINNER = DRAW
      RETURN    
      END
      
! SUBROUTINE TO PLAY FOR THE COMPUTER  
! =========================================
      SUBROUTINE COMPMOVE(TICTAC)
      CHARACTER * 1 TICTAC(3,3)
      INTEGER PATHS(3,8), PATHSUM(8)
      DATA PATHS/1,2,3,4,5,6,7,8,9, &
                1,4,7,2,5,8,3,6,9, &
                1,5,9,3,5,7/
      INTEGER BOARD(9,2), K, X, Y, RANDPOS
      DATA BOARD/1,1,1,2,2,2,3,3,3,1,2,3,1,2,3,1,2,3/

      
!     YOUR CODE GOES HERE 

!     CALCULATE THE PATHSUMS
      DO I = 1,8
      	PATHSUM(I) = 0
      	DO J = 1,3
      		X = BOARD(PATHS(J,I),1)
      		Y = BOARD(PATHS(J,I),2)
      		IF (TICTAC(X,Y) == " ") K = 0
      		IF (TICTAC(X,Y) == "X") K = 1
      		IF (TICTAC(X,Y) == "O") K = 4 
      		PATHSUM(I) = PATHSUM(I) + K
	END DO
       END DO
     
!     OFFENSIVE CODE TO DEAL WITH SCENARIOS WHERE THE
!     COMPUTER HAS TWO IN A PATH
      DO I = 1,8
      	IF (PATHSUM(I) == 8) THEN
      		DO J = 1,3
      			X = BOARD(PATHS(J,I),1)
      			Y = BOARD(PATHS(J,I),2)
      			IF (TICTAC(X,Y) == " ") THEN
      				TICTAC(X,Y) = "O"
      				RETURN
     		 	END IF
		END DO
      	END IF
       END DO
  
!     DEFENSIVE CODE TO DEAL WITH SCENARIOS WHERE THE
!     OPPONENT HAS TWO IN A PATH
      DO I = 1,8
      	IF (PATHSUM(I) == 2) THEN
      		DO J = 1,3
      			X = BOARD(PATHS(J,I),1)
      			Y = BOARD(PATHS(J,I),2)
      			IF (TICTAC(X,Y) == " ") THEN
      				TICTAC(X,Y) = "O"
      				RETURN
     			END IF
		END DO
      	END IF
       END DO

! choose a random square to place a '0'
! it randomly generates a number between 1-9
! then it checks if the square is empty
! if it's empty, place a '0', if not, start whole block over  

	DO 
      		RANDPOS = INT(RAND(0)*9)+1
      		X = BOARD(RANDPOS,1)
      		Y = BOARD(RANDPOS,2)
      		IF (TICTAC(X,Y) == " ") THEN
        		TICTAC(X,Y) = "O"
        		RETURN
      		END IF  
	END DO    
	RETURN
      	END

! FUNCTION TO CHECK TO SEE IF THREE ELEMENTS IN A ROW, COLUMN OR DIAGONAL
! ARE THE SAME           
! =========================================
      LOGICAL FUNCTION SAME(T1,T2,T3)
      CHARACTER T1,T2,T3
      
      IF (T1 == "X" .AND. T2 == "X" .AND. T3 == "X") THEN
	SAME = .TRUE.
      ELSE IF (T1 == "O" .AND. T2 == "O" .AND. T3 == "O") THEN      
	SAME = .TRUE.
      ELSE
	SAME = .FALSE.
      END IF
      END
  
! SUBROUTINE TO SET UP THE TIC-TAC-TOE BOARD  
! =========================================  
      SUBROUTINE BOARDSETUP(TICTAC)
      CHARACTER * 1 TICTAC(3,3)

      DO I = 1,3
      	DO J = 1,3
      	   TICTAC(I,J) = " "
        END DO
      END DO
      RETURN
      END

! SUBROUTINE TO CHECK HUMAN PLAY  
! ========================================= 
      LOGICAL FUNCTION CHKPLAY(TICTAC,MOVE) 
      CHARACTER * 1 TICTAC(3,3)
      INTEGER MOVE
      

	! depending on the value of move, a check is made to see if the square is empty
	! if it's empty it will return true, in all other circumstances it returns false

	IF (MOVE == 1 .AND. TICTAC(1,1) == " ") THEN
		CHKPLAY = .TRUE.
	ELSE IF (MOVE == 2 .AND. TICTAC(1,2) == " ") THEN
		CHKPLAY = .TRUE.
	ELSE IF (MOVE == 3 .AND. TICTAC(1,3) == " ") THEN
		CHKPLAY = .TRUE.
	ELSE IF (MOVE == 4 .AND. TICTAC(2,1) == " ") THEN
		CHKPLAY = .TRUE.
	ELSE IF (MOVE == 5 .AND. TICTAC(2,2) == " ") THEN
		CHKPLAY = .TRUE.
	ELSE IF (MOVE == 6 .AND. TICTAC(2,3) == " ") THEN
		CHKPLAY = .TRUE.
	ELSE IF (MOVE == 7 .AND. TICTAC(3,1) == " ") THEN
		CHKPLAY = .TRUE.
	ELSE IF (MOVE == 8 .AND. TICTAC(3,2) == " ") THEN
		CHKPLAY = .TRUE.
	ELSE IF (MOVE == 9 .AND. TICTAC(3,3) == " ") THEN
		CHKPLAY = .TRUE.
	ELSE
		CHKPLAY = .FALSE.
	END IF 
	END

