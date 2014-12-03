#include <stdio.h> 
#include <stdlib.h>
      //shared variables start
        char null = 0x0;
        char soh = 0x01;
        char stx = 0x02;
        char smf = 0x1b; // start of mode field
        char pic = 0x14; //call a dots file
        char cc = 0x1c; //collor code 
        char green = 0x35; //green color
        char time = 0x13 ; // print time
        char newpage =0x0c;
        char end = 0x04;
char start(char a,char b ); //prototype (type of signs, sign 1 or 2 or both)
char startusb(char a,char b); //prototype usb 

int main(void)
{
/*# Get the attention of the sign
print LED "\0\0\0\0\0\0";

# Tell the sign to print the message
print LED "\001" . "a" . "01" . "\002" . "AA" . "\x1b" . " b" ."$scroller1_color"."\x14" ."A"."$lower1_text"."\x0D"."\x1c\x35" ."Time \x13". "\004";
sleep 4;
*/

FILE *fp;
FILE *fusb;
/*if ((fp = fopen("/dev/ttyS0", "r+")) == NULL)
{
	fprintf(stdout,"Can't open ttyS0\n");
	exit(1);
}*/
if ((fusb = fopen("/dev/ttyUSB0", "r+")) == NULL)
{
        fprintf(stdout,"Can't open ttyS0\n");
        exit(1);
}


       
startusb('!','0');
fprintf(fusb,"%c i%c%c %c%c %c",smf,cc,green,0x0B,0x30,end);
fclose(fusb);

return 0;
}
char start(char a, char b)
{
//this will print the 0x00 to file field 
FILE *fp;
if ((fp = fopen("/dev/ttyS0", "r+")) == NULL)
{
        fprintf(stdout,"Can't open ttyS0\n");
        exit(1);
}


fprintf(fp,"%c%c%c%c%c%c0%c%cAA",null,null,null,null,soh,a,b,stx);

fclose(fp);

return 0;
}
char startusb(char a, char b)
{
//this will print the 0x00 to file field 
FILE *fp;
if ((fp = fopen("/dev/ttyUSB0", "r+")) == NULL)
{
        fprintf(stdout,"Can't open ttyS0\n");
        exit(1);
}


fprintf(fp,"%c%c%c%c%c%c0%c%cAA",null,null,null,null,soh,a,b,stx);

fclose(fp);

return 0;
}

