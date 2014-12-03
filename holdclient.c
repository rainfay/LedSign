//Jason Archip 2013 This program shall send a command to the server to display text in the A file on the sign
#include "signfp.h"
#include <stdio.h>      
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>   
#include <netdb.h>

int main(int argc, char *argv[]) {

    int simpleSocket = 0;
    int simplePort = 0;
    int returnStatus = 0;
    char buffer[256] = "";
    struct sockaddr_in simpleServer;
    struct hostent *server;
    int LOL1;
	char LOL[256];
	int temp;
	char stringtemp[1024];
    if (6 != argc) {

        fprintf(stderr, "Usage: %s <server> <port> <sign addr> <color> \"message\"\n", argv[0]);
        exit(1);

    }

    /* create a streaming socket      */
    simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (simpleSocket == -1) {

        fprintf(stderr, "Could not create a socket!\n");
        exit(1);

    }
    else {
	    fprintf(stdout, "Socket created!\n");
    }

    /* retrieve the port number for connecting */
    simplePort = atoi(argv[2]);
	printf(" %s %s %s %s %s ",argv[1],argv[2],argv[3],argv[4],argv[5]);
	//    server = gethostbyname(argv[1]); is the magical dns lookup
	    server = gethostbyname(argv[1]);

    /* setup the address structure */
    /* use the IP address sent as an argument for the server address  */
    bzero(&simpleServer, sizeof(simpleServer)); 
    simpleServer.sin_family = AF_INET;
    //inet_addr(server, &simpleServer.sin_addr.s_addr); is outdated 
        bcopy((char *)server->h_addr, 
         (char *)&simpleServer.sin_addr.s_addr,
	server->h_length);
    simpleServer.sin_port = htons(simplePort);

    /*  connect to the address and port with our socket  */
    returnStatus = connect(simpleSocket, (struct sockaddr *)&simpleServer, sizeof(simpleServer));

    if (returnStatus == 0) {
	    fprintf(stderr, "Connect successful!\n");
    }
    else {
        fprintf(stderr, "Could not connect to address!\n");
	close(simpleSocket);
	exit(1);
    }

    /* get the message from the server   */
       temp=sprintf(stringtemp,"AZ%s",argv[3]);
	printf("%s",stringtemp);
	temp=write(simpleSocket,stringtemp,temp);
	read(simpleSocket, buffer, sizeof(buffer));
	printf("%s \n",buffer);
       temp=sprintf(stringtemp,"AA");
       temp=write(simpleSocket,stringtemp,temp);

	 temp=sprintf(stringtemp,"%c b %c%c",smf,fontmode,largetimesfont); //Set the sign to scroll on all lines 
                                                                        // and largetimes font in to buffer
       temp=write(simpleSocket,stringtemp,temp); //write buffer to mainfd (which should be the serial port see signfp.c)
       if (strcmp(argv[4],"red")==0){
	 temp=sprintf(stringtemp,"%c%c",cc,red);// set the color code
         temp=write(simpleSocket,stringtemp,temp); //and shove it out the door

	}else if (strcmp(argv[4],"green")==0){                                           
                        temp=sprintf(stringtemp,"%c%c",cc,green);
                          temp=write(simpleSocket,stringtemp,temp);

        }else if (strcmp(argv[4],"amber")==0){                                           
                        temp=sprintf(stringtemp,"%c%c",cc,amb);
                        temp=write(simpleSocket,stringtemp,temp);
        }else
                {

                        temp=sprintf(stringtemp,"%c%c",cc,green);
                        temp=write(simpleSocket,stringtemp,temp);


		}

	 temp=strlen(argv[5]);  //count the argv2 which should be a string
        temp=write(simpleSocket,argv[5],temp); // and shove x chars out the door
	temp=sprintf(stringtemp," %c",end); // tell the sign were done
        temp=write(simpleSocket,stringtemp,temp); // output it


	usleep(250);

	 endloop(simpleSocket);

    returnStatus = read(simpleSocket, buffer, sizeof(buffer));

    if ( returnStatus > 0 ) {
        printf("%d: %s", returnStatus, buffer);
    } else {
        fprintf(stderr, "Return Status = %d \n", returnStatus);
    }

    close(simpleSocket);
    return 0;

}

