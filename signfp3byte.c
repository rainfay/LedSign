//Jason Archip
//endofnet.com
#include <stdio.h> 
#include <stdlib.h>
 #include <unistd.h>  /* UNIX standard function definitions */
 #include <fcntl.h>   /* File control definitions */
 #include <errno.h>   /* Error number definitions */
 #include <termios.h> /* POSIX terminal control definitions */
#include "signfp3byte.h"
//REFER TO DATA SHEET FOR EXPLATION OF ASCII CODES
char null = 0x0;
char soh[] = "_01";
char stx[] = "_02";
char etx[] = "_03";
char smf[] ="_1B"; // start of mode field
char pic[] =  "_14"; //call a dots file
char cc[] = "_1C"; //collor code
char green[] = "5"; //green color
char amb[] = "6";
char red[] = "1";
char timeLED[] ="_13" ; // print time
//fix 0x00's 
char date[] = "_0B";
char datemmddyy[] = "_30";
char datedashmmddyy[] = "_32";
char datetext[] = "_38";
char datedayofweek[] = "_39";

char newpage[] ="_0c"; //not supported on 4120c :( kept for comptaibilty 
char end[] = "_04";
char topline[] = "\"";
char botline[] = "&";
char fontmode[] = "_1A";
char largetimesfont[] = "8";
char normallargefont[] = "9";
char normalsmallfont[] ="3";
char enablewidechar[] ="_12";
char disablewidechar[] ="_11";

char speed1[] = "_15";
char speed2[] = "_16";
char speed3[] = "_17";
char speed4[] = "_18";
char speed5[] = "_19";
 int open_port(void)
 {
   int fd;                                   /* File descriptor for the port */

   fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY |  O_NONBLOCK);

   if (fd == -1)
   {                                              /* Could not open the port */
     fprintf(stderr, "open_port: Unable to open /dev/ttyS0 :(\n");
   }

   fd = configport(fd);
   return(fd);
 }
int configport(int intfp)
{
//taken from http://slackware.osuosl.org/slackware-3.3/docs/mini/Serial-Port-Programming 
 struct termios options;

fcntl(intfp, F_SETFL, FNDELAY);                  /* Configure port reading */
                                     /* Get the current options for the port */
 tcgetattr(intfp, &options);
 cfsetispeed(&options, B9600);                 /* Set the baud rates to 9600 */
 cfsetospeed(&options, B9600);

                                   /* Enable the receiver and set local mode */
 options.c_cflag |= (CLOCAL | CREAD);
 options.c_cflag &= ~PARENB; /* Mask the character size to 8 bits, no parity */
 options.c_cflag &= ~CSTOPB;
 options.c_cflag &= ~CSIZE;
 options.c_cflag |=  CS8;                              /* Select 8 data bits */
 options.c_cflag &= ~CRTSCTS;               /* Disable hardware flow control */

                                 /* Enable data to be processed as raw input */
 options.c_lflag &= ~(ICANON | ECHO | ISIG);

                                        /* Set the new options for the port */
 tcsetattr(intfp, TCSANOW, &options);
return (intfp);
}

int transbridgeon(int fp) //for pic chip
{
        char LocalBuff[200];
        int LocalLength,Lcount;

        LocalLength=sprintf(LocalBuff,"%c%c\n",0x04,0x80);
        Lcount=write(fp,LocalBuff,LocalLength);


return 0;
}
int transbridgeoff(int fp) //for pic chip
{
        char LocalBuff[200];
        int LocalLength,Lcount;

        LocalLength=sprintf(LocalBuff,"%c%c\n",0x04,0x81);
        Lcount=write(fp,LocalBuff,LocalLength);


return 0;
}
int endloop(int fp) //for pic chip
{
        char LocalBuff[200];
        int LocalLength,Lcount;

        LocalLength=sprintf(LocalBuff,"%c%c",0x04,0x82);
        Lcount=write(fp,LocalBuff,LocalLength);
return 0;
}

int setmem(int fp,char SignAddr)
{
//Perl code below 
//print LED "\0\0\0\0\0\0";

//print LED "\001" . "!" . "00" . "\002" . "E" . "\x24". "AAUFFE8FF00ADU101F4000" . "\004" ;
        char LocalBuff[200]; //char buffer for write()
        int LocalLength,Lcount;//debuging varables 
        printf("In setmem() \n");

        LocalLength=sprintf(LocalBuff,"%s!0%c%sE$AAU1F58FF00",soh,SignAddr,stx); //start !=display if it was recived ok
        Lcount=write(fp,LocalBuff,LocalLength); //write it out
//        printf(" wrote %d\n",Lcount); //debug
	LocalLength=sprintf(LocalBuff,"BAU1D58FFFF"); //see datasheet for explation of memory settings 
        Lcount=write(fp,LocalBuff,LocalLength);
//        printf(" wrote %d\n",Lcount);
	LocalLength=sprintf(LocalBuff,"MDL10784000");
        Lcount=write(fp,LocalBuff,LocalLength);
//        printf(" wrote %d\n",Lcount);
//	fprintf(fp,"PDL104F4000");
//        fprintf(fp,"TDL104F4000");
	LocalLength=sprintf(LocalBuff,"1BL00FF0000");
        Lcount=write(fp,LocalBuff,LocalLength);
//        printf(" wrote %d\n",Lcount);
	LocalLength=sprintf(LocalBuff,"2BL00FF0000");
        Lcount=write(fp,LocalBuff,LocalLength);
//        printf(" wrote %d\n",Lcount);
        LocalLength=sprintf(LocalBuff,"3BL00FF0000");
        Lcount=write(fp,LocalBuff,LocalLength);
//        printf(" wrote %d\n",Lcount);
        LocalLength=sprintf(LocalBuff,"4BL00FF0000");
        Lcount=write(fp,LocalBuff,LocalLength);
        LocalLength=sprintf(LocalBuff,"5BL00FF0000");
        Lcount=write(fp,LocalBuff,LocalLength);
//        LocalLength=sprintf(LocalBuff,"6BL00FF0000");
//        Lcount=write(fp,LocalBuff,LocalLength);

	LocalLength=sprintf(LocalBuff,"%s \n",end);
        Lcount=write(fp,LocalBuff,LocalLength);
     //   printf(" wrote %d\n",Lcount);

        return 0;


}

int slsetmem(int fp, char signaddr)
{
//Perl code below
//print LED "\0\0\0\0\0\0";

//print LED "\001" . "!" . "00" . "\002" . "E" . "\x24". "AAUFFE8FF00ADU101F4000" . "\004" ;
        char LocalBuff[200]; //char buffer for write()
        int LocalLength,Lcount;//debuging varables
        printf("In setmem() \n");

        LocalLength=sprintf(LocalBuff,"%s!0%c%sE$AAU1088FF00",soh,signaddr,stx); //start !=display if it was recived ok
        Lcount=write(fp,LocalBuff,LocalLength); //write it out
//        printf(" wrote %d\n",Lcount); //debug
//        printf(" wrote %d\n",Lcount);
//	fprintf(fp,"PDL104F4000");
//        fprintf(fp,"TDL104F4000");
	LocalLength=sprintf(LocalBuff,"1BL00FF0000");
        Lcount=write(fp,LocalBuff,LocalLength);
//        printf(" wrote %d\n",Lcount);
	LocalLength=sprintf(LocalBuff,"2BL00FF0000");
        Lcount=write(fp,LocalBuff,LocalLength);
//        printf(" wrote %d\n",Lcount);
        LocalLength=sprintf(LocalBuff,"3BL00FF0000");
        Lcount=write(fp,LocalBuff,LocalLength);
//        printf(" wrote %d\n",Lcount);
        LocalLength=sprintf(LocalBuff,"4BL00FF0000");
        Lcount=write(fp,LocalBuff,LocalLength);
        LocalLength=sprintf(LocalBuff,"5BL00FF0000");
        Lcount=write(fp,LocalBuff,LocalLength);
        LocalLength=sprintf(LocalBuff,"6BL00FF0000");
        Lcount=write(fp,LocalBuff,LocalLength);

	LocalLength=sprintf(LocalBuff,"%s \n",end);
        Lcount=write(fp,LocalBuff,LocalLength);
      //  printf(" wrote %d\n",Lcount);

        return 0;


}
int start(int fp,char a, char b) //char a = sign type char b = sign address 
{
	//
//printf("in sign c char a = %c char b = %c",a,b);

	        char LocalBuff[200];
        int LocalLength,Lcount;
        LocalLength=sprintf(LocalBuff,"%s%c0%c%sAA",soh,a,b,stx);
        Lcount=write(fp,LocalBuff,LocalLength);
//        printf(" wrote %d\n",Lcount);

	return 0;
}
int starttext(int fp,char a, char b, char c) //char a =sign type char b = sign address char c= file lable
{
        
	char LocalBuff[200];
	int LocalLength,Lcount;
        LocalLength=sprintf(LocalBuff,"%s%c0%c%sA%c",soh,a,b,stx,c);
	Lcount=write(fp,LocalBuff,LocalLength);
//	printf(" wrote %d\n",Lcount);
 

        return 0;
}



int startc(int fp,char a, char b)// Sign type, sign adress
{
        //this will print the 0x00 to file field 

          char LocalBuff[200];
        int LocalLength,Lcount;
        LocalLength=sprintf(LocalBuff,"%s%c0%c%s",soh,a,b,stx);
        Lcount=write(fp,LocalBuff,LocalLength);
  //      printf(" wrote %d\n",Lcount);


        return 0;
}
int startcommand(int fp, char a, char b, char c)// Sign type, sign adress, Command, Extra
{
        //this will print the 0x00 to file field

                char LocalBuff[200];
        int LocalLength,Lcount;
        LocalLength=sprintf(LocalBuff,"%s%c0%c%s%c",soh,a,b,stx,c);
        Lcount=write(fp,LocalBuff,LocalLength);
    //    printf(" wrote %d\n",Lcount);

        return 0;
}

int startusb(char a, char b)
{	//OLD CODE IS OLD!
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


