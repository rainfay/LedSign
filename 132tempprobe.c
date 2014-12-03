/*
 *     This program 132tempprobe connects to a server, and tells it to display the tempature.
 *         Copyright (C) 2011  Jason Archip
 *
         This program is free software: you can redistribute it and/or modify
 *       it under the terms of the GNU Affero General Public License as published by
 *       the Free Software Foundation, either version 3 of the License, or
 *       (at your option) any later version.
 *      This program is distributed in the hope that it will be useful,
 *       but WITHOUT ANY WARRANTY; without even the implied warranty of
 *       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *       GNU Affero General Public License for more details.
 *     You should have received a copy of the GNU Affero General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *     See LICENSE file for this copy of the GNU Affero General Public License.
 */

#include "signfp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define debug 0 

int main( int argc, char *argv[])
{
int temp,count;	
 int simpleSocket = 0;
    int simplePort = 0;
    int returnStatus = 0;
    char buff[256] = "";
    char buffer[256] = "";
    char stringtemp[256] = "";
    struct sockaddr_in simpleServer;	
    struct hostent *server;

/*		if (argc > 3 || argv[1] == NULL)
		{
		printf("usage: %s  color \"text\"\n",argv[0]);
		return 1;
		}
*/
 if (3 != argc) {

        fprintf(stderr, "Usage: %s <server> <port>\n", argv[0]);
        exit(1);

    }
	 /* create a streaming socket      */
    simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (simpleSocket == -1) {

        fprintf(stderr, "Could not create a socket!\n");
        exit(1);

    }
    else {
            fprintf(stderr, "Socket created!\n");
    }

    /* retrieve the port number for connecting */
    simplePort = atoi(argv[2]);

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


	

       temp=sprintf(stringtemp,"AZ0"); //see DAE code for commands
        temp=write(simpleSocket,stringtemp,temp); // normal shove out the door code
        read(simpleSocket, buffer, sizeof(buffer)); // read data from the server
        printf("%s \n",buffer); //display on consle

      temp=sprintf(stringtemp,"AA"); //Text Lablel is Next after STX
       temp=write(simpleSocket,stringtemp,temp);

	count=sprintf(buff,"%c%cb %c%c %c%c",smf,topline,cc,green,fontmode,normalsmallfont); //set up formating
	write(simpleSocket,buff,count);

	count=sprintf(buff,"Ext temp is%c1C %c3F",0x10,0x10); //display stuff 
	write(simpleSocket,buff,count);
	count=sprintf(buff,"%c%cb The Int temp is %c2 ",smf,botline,0x10);
	write(simpleSocket,buff,count);
	count=sprintf(buff,"%c",end);
	write(simpleSocket,buff,count);
	usleep(250); 
	endloop(simpleSocket); //see signfp.c
	read(simpleSocket, buffer, sizeof(buffer));
	printf("%s \n", buffer);
	close(simpleSocket);

return 0;
}
