DUART      EQU         $C001
sra        EQU         2
tba        EQU         6
rba        EQU         2

           ORG         $8000
loop       jsr         INSTRING
           move.l      (a1),d0
           *CMPI.B     #q,d0
           BEQ         EXIT
           move.b      d0,$00C01F
           not.b       d0
           move.b      d0,$00C01D
           BRA         loop
EXIT       trap        #14


OUTSTRING:
begin_out  move.b      (a1)+,d0
           bra         SEND_CHAR
out_return CMPI.B      #0,(a1)
           BNE         begin_out
           rts
SEND_CHAR  lea         DUART,a0
send_loop  move.b      sra(a0),d7
           andi.b      #4,d7
           beq         send_loop
           move.b      d0,tba(a0)
           bra         out_return


INSTRING:
begin_in   bra         REC_CHAR
in_return  move.b      d0,(a1)+
           CMPI.B      #$0D,d0
           BNE         begin_in
           move.b      #0,(a1)
           rts
REC_CHAR   lea         DUART,a0
rec_loop   move.b      sra(a0),d7
           andi.b      #1,d7
           beq         rec_loop
           move.b      rba(a0),d0
           bra         in_return

           org         $9000
out_buffer dc.b 'abcdefg',0