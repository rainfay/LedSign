#include <stdio.h> 
#include <stdlib.h>
#include "signfp.h"
int main(void)
{
//This program will Blank ALL displays of the led signs !
	//Varables start
        int temp; //temp count of number of chars in buffer
        char stringtemp[1024]; //HUGE BUFFER for strings
	int mainfd=0; //mainfd is like file pointer execpt with no buff
	//Varables end 
	mainfd = open_port(); //call the open port command in signfp.c 
	mainfd = configport(mainfd); //Call the magical config port stuff in signfp.c
	
	starttext(mainfd,'Z','0','A'); //Start sending data to ALL THE SIGNS to File Label A
        temp=sprintf(stringtemp,"%c0b  %c",smf,end); // tell the sign to display " " and were done
        temp=write(mainfd,stringtemp,temp); // output it
close(mainfd); //close the serialport pointer
return 0; 

}

