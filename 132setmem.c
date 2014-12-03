/*
 *     This program 132setmem connects to a server, and asks it to call the setmem commands.
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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#define debug 0 
// get sockaddr, IPv4 or IPv6:
 void *get_in_addr(struct sockaddr *sa)
 {
     if (sa->sa_family == AF_INET){ 
             return &(((struct sockaddr_in*)sa)->sin_addr);
                 }

              return &(((struct sockaddr_in6*)sa)->sin6_addr);                     }
int main( int argc, char *argv[])
{
int temp,count,rv;	
 int sockfd = 0;

    int returnStatus = 0;
    char buff[256] = "";
    char buffer[256] = "";
    char stringtemp[256] = "";
char s[INET6_ADDRSTRLEN];

    struct sockaddr_in simpleServer;	
    struct hostent *server;
 struct addrinfo hints, *servinfo, *p;

/*		if (argc > 3 || argv[1] == NULL)
		{
		printf("usage: %s  color \"text\"\n",argv[0]);
		return 1;
		}
*/
 if (4 != argc) {

        fprintf(stderr, "Usage: %s <server> <port> <sign #>\n", argv[0]);
        exit(1);

    }
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if ((rv = getaddrinfo(argv[1], argv[2], &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
	 /* create a streaming socket      */
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }
    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

	

       temp=sprintf(stringtemp,"C%s",argv[3]); //see DAE code for commands
        temp=write(sockfd,stringtemp,temp); // normal shove out the door code
        read(sockfd, buffer, sizeof(buffer)); // read data from the server
        printf("%s \n",buffer); //display on consle


	close(sockfd);

return 0;
}
