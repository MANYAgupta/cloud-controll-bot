//CODE:
FOR 8051//
#include<reg51.h>
sbit m1p=P2^0; # assigning pin for wheel 1
sbit m1n=P2^1; # assigning pin for wheel 1
sbit m2p=P2^2; # assigning pin for wheel 2
sbit m2n=P2^3; # assigning pin for wheel 2
void main()
{
unsigned char x;
SCON=0X50; # serial communication mode 1
TMOD=0X20; # using timer 1, mode 2
TH1=-3; # setting baud rate to 9600
TR1=1; # setting timer flag
while(1)
{
while(RI==0); # checking whether bit received or not
x=SBUF; # sending bit serially
RI=0; # setting flag to 0
SBUF=x;
while(TI==0); # checking whether bit transmitted or not
TI=0; # setting flag to 0
if(x=='f') # checking command for wheel
{
m1p=1;m1n=0; # setting condition for wheel
m2p=1;m2n=0; # setting condition for wheel
}
if(x=='b') # checking command for wheel
{
m1p=0;m1n=1; # setting condition for wheel
m2p=0;m2n=1; # setting condition for wheel
}
if(x=='l') # checking command for wheel
{
m1p=1;m1n=0; # setting condition for wheel
m2p=0;m2n=1; # setting condition for wheel
}
if(x=='r') # checking command for wheel
{
m1p=0;m1n=1; # setting condition for wheel
m2p=1;m2n=0; # setting condition for wheel
}
if(x=='s') # checking command for wheel
{
m1p=m1n=m2p=m2n=0; # setting condition for wheel
}
}
}