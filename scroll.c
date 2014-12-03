//Jason Archip very simple write to the serial port to scroll a message on the sign
#include <stdio.h>
#include <string.h>
#include "signfp.h"

#define debug 0 



int main( int argc, char *argv[]) //get options from command line
{
	
	 int mainfd=0; //mainfd is like file pointer execpt with no buff
 mainfd = open_port(); //call the open port command in signfp.c
		       //Oh magical serial port config is done there! 

	int temp; //temp count of number of chars in buffer
	char stringtemp[1024]; //HUGE BUFFER for strings

		if (argc > 3 || argv[1] == NULL) //check to see if there are the correct # of args
		{
		printf("usage: %s  color \"text\"\n",argv[0]);
		return 1;
		}

                         


	starttext(mainfd,'Z','0','A'); //See signfp.c and datasheet for the alpha protocol 
				       // but basickly it says HEY ALL SIGNS WRITE TO Label A
	temp=sprintf(stringtemp,"%c a %c%c",smf,fontmode,largetimesfont); //Set the sign to scroll on all lines 
									// and largetimes font in to buffer
	temp=write(mainfd,stringtemp,temp); //write buffer to mainfd (which should be the serial port see signfp.c)
	printf("wrote %d",temp); //debug 
                if (strcmp(argv[1],"red") == 0) //argv 1 ahould be the color att. for the sign  from command line
                {
                       if (debug == 1)
			 printf("red\n");
			temp=sprintf(stringtemp,"%c%c",cc,red);// set the color code
		        temp=write(mainfd,stringtemp,temp); //and shove it out the door
             if (debug == 1)
	printf("wrote %d",temp);

                }
                else if (strcmp(argv[1],"green") == 0)
                {
			if (debug == 1)
                        printf("green\n");
			temp=sprintf(stringtemp,"%c%c",cc,green);
      			  temp=write(mainfd,stringtemp,temp);
     if (debug == 1)
        printf("wrote %d",temp);

                }
		else if (strcmp(argv[1],"amber") == 0)
                {
                        if (debug == 1)
                        printf("amber\n");
                        temp=sprintf(stringtemp,"%c%c",cc,amb);
        		temp=write(mainfd,stringtemp,temp);
     if (debug == 1)
        printf("wrote %d",temp);

                }
		else
		{
                        if (debug == 1)
                        printf("defult\n");
                        temp=sprintf(stringtemp,"%c%c",cc,green);
        		temp=write(mainfd,stringtemp,temp);
     if (debug == 1)
        printf("wrote %d",temp);

		}

	temp=strlen(argv[2]);  //count the argv2 which should be a string
        temp=write(mainfd,argv[2],temp); // and shove x chars out the door
     if (debug == 1)
        printf("wrote %d",temp);
        temp=sprintf(stringtemp,"%c",end); // tell the sign were done
	temp=write(mainfd,stringtemp,temp); // output it
     if (debug == 1)
        printf("wrote %d",temp);


close(mainfd); //close the serialport pointer


return 0;
}
