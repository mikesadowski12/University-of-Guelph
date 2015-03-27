

START ORG #1000
x          EQU   5
Y          EQU   $12
           DS.L  12
One        DS.B  1
Two        DC.B X*Y
Four       DS.L Three*Five
Three      DC.B One+Two
Five       DC.B X+Y