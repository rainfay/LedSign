//Jason Archip
//endofnet.com
//OLD CODE USE signfp.c
#include <stdio.h> 
#include <stdlib.h>
#include "sign.h"

char null = 0x0;
char soh = 0x01;
char stx = 0x02;
char smf = 0x1b; // start of mode field
char pic = 0x14; //call a dots file
char cc = 0x1c; //collor code
char green = 0x35; //green color
char amb = 0x36;
char red = 0x31;
char time = 0x13 ; // print time
//fix 0x00's 
char date = 0x0B;
char datemmddyy = 0x30;
char datedashmmddyy = 0x32;
char datetext = 0x38;
char datedayofweek = 0x39;

char newpage =0x0c; //not supported on 4120c :( kept for comptaibilty 
char end = 0x04;
char topline = 0x22;
char botline = 0x26;
char fontmode = 0x1A;
char largetimesfont = 0x38;
char normallargefont = 0x39;
char normalsmallfont =0x33;
char enablewidechar =0x12;
char disablewidechar =0x11;

char speed1 = 0x15;
char speed2 = 0x16;
char speed3 = 0x17;
char speed4 = 0x18;
char speed5 = 0x19;

int setmem(void)
{
//print LED "\0\0\0\0\0\0";

//print LED "\001" . "!" . "00" . "\002" . "E" . "\x24". "AAUFFE8FF00ADU101F4000" . "\004" ;
        FILE *fp;
        if ((fp = fopen("/dev/ttyS0", "r+")) == NULL)
        {
        fprintf(stdout,"Can't open ttyS0 sign.c\n");
        exit(1);
        }
        printf("In setmem() \n");
        fprintf(fp,"%c%c%c%c%c!00%cE%cAAU1F58FF00",null,null,null,null,soh,stx,0x24);
	fprintf(fp,"BAU1D580000");
	fprintf(fp,"BAU2D580000");
	fprintf(fp,"BAU3D580000");
	fprintf(fp,"BAU4D580000");
	fprintf(fp,"BAU5D580000");
	fprintf(fp,"MDL10F78000");
	fprintf(fp,"PDL104F4000");
        fprintf(fp,"TDL104F4000");
	fprintf(fp,"%c \n",end);


        fclose(fp);
        return 0;


}

int start(char a, char b)
{
	//this will print the 0x00 to file field 
	FILE *fp;
if ((fp = fopen("/dev/ttyS0", "r+")) == NULL)
{
        fprintf(stdout,"Can't open ttyS0 sign.c\n");
        exit(1);
}
//printf("in sign c char a = %c char b = %c",a,b);
	fprintf(fp,"%c%c%c%c%c%c0%c%cAA",null,null,null,null,soh,a,b,stx);

	fclose(fp);
	return 0;
}
int starttext(char a, char b, char c)
{
        //this will print the 0x00 to file field 
        FILE *fp;
if ((fp = fopen("/dev/ttyS0", "r+")) == NULL)
{
        fprintf(stdout,"Can't open ttyS0 sign.c\n");
        exit(1);
}

        fprintf(fp,"%c%c%c%c%c%c0%c%cA%c",null,null,null,null,soh,a,b,stx,c);

        fclose(fp);
        return 0;
}



int startc(char a, char b, char c, char d)// Sign type, sign adress, Command, Extra
{
        //this will print the 0x00 to file field 
        FILE *fp;
if ((fp = fopen("/dev/ttyS0", "r+")) == NULL)
{
        fprintf(stdout,"Can't open ttyS0 sign.c\n");
        exit(1);
}

        fprintf(fp,"%c%c%c%c%c%c0%c%c%c%c",null,null,null,null,soh,a,b,stx,c,d);

        fclose(fp);
        return 0;
}
int startcommand(char a, char b, char c)// Sign type, sign adress, Command, Extra
{
        //this will print the 0x00 to file field
        FILE *fp;
if ((fp = fopen("/dev/ttyS0", "r+")) == NULL)
{
        fprintf(stdout,"Can't open ttyS0 sign.c\n");
        exit(1);
}

        fprintf(fp,"%c%c%c%c%c%c0%c%c%c",null,null,null,null,soh,a,b,stx,c);

        fclose(fp);
        return 0;
}

int startusb(char a, char b)
{
	//this will print the 0x00 to file field 
	FILE *fp;
	if ((fp = fopen("/dev/ttyUSB0", "r+")) == NULL)
	{
		fprintf(stdout,"Can't open ttyUSB0 sign.c\n");
		exit(1);
	}


	fprintf(fp,"%c%c%c%c%c%c0%c%cAA",null,null,null,null,soh,a,b,stx);

	fclose(fp);

	return 0;
}
int signsoff(void)
{
/*# Get the attention of the sign
print LED "\0\0\0\0\0\0";

# Tell the sign to print the message
print LED "\001" . "a" . "01" . "\002" . "AA" . "\x1b" . " b" ."$scroller1_color"."\x14" ."A"."$lower1_text"."\x0D"."\x1c\x35" ."Time \x13". "\004";
sleep 4;
*/

FILE *fp;
FILE *fusb;
if ((fp = fopen("/dev/ttyS0", "r+")) == NULL)
{
        fprintf(stdout,"Can't open ttyS0\n");
        exit(1);
}
if ((fusb = fopen("/dev/ttyUSB0", "r+")) == NULL)
{
        fprintf(stdout,"Can't open ttyS0\n");
        exit(1);
}


start('Z','0');
fprintf(fp,"%c0b  %c",smf,end);
startusb('Z','0');
fprintf(fusb,"%c0b %c",smf,end);
fclose(fusb);
fclose(fp);

return 0;
}

