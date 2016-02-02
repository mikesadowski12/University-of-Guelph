*  hello.x68 displays the message "Hello, world!" on the SunRay console


	ORG	$8000
PROGRAM LEA	MESSAGE,A1	;A1 points to message in memory
	TRAP	#2		;Send message to screen
	TRAP	#14		;Stop program and return to MON68k

MESSAGE	DC.B	'Hello world!'
	DC.B	$0D,$0A,0	;Carriage return, line feed, null
	
	END	PROGRAM		;Code ends here
