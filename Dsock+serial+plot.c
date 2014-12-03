/*
 *     This program Dsock+serial+plot is a server, connects to the serial port and recives info from clients.
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

/*
 *"This software uses the gnuplot_i library written by N.Devillard" 
  
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <syslog.h>
#include <signal.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
    #include <termios.h>
    #include <unistd.h>
#include <sys/ioctl.h>
#include "signfp.h"
#include "libs/gnuplot_i.h"
#define DEBUG 0 

const char ACKMESSAGE[] = "RECIVED 73's \n"; //Acholgement message

struct sigaction act; 
   int simpleSocket = 0; //Socket is GLOBAL since I am messing with it from differnt functions 
   int mainfd = 0;
   void *get_in_addr(struct sockaddr *sa)
   {
       if (sa->sa_family == AF_INET){
               return &(((struct sockaddr_in*)sa)->sin_addr);
                   }

                return &(((struct sockaddr_in6*)sa)->sin6_addr);                     }
void IO_GO(int sig){
 syslog(LOG_ERR, "SIG IO SIG IO!!!!!!"); //Log it
mainfd = open_port();

        struct sockaddr_in clientName = { 0 };
        int BuffCount;  // Got Count 
	char Buff[1024]; //Buffer size 
        bzero(Buff,sizeof(Buff)); //Zero out the buffer
	int simpleChildSocket = 0;
        int clientNameLength = sizeof(clientName);
	int flag=0;
	char endL[3];
	char TempBuff[256];
	int TempCount;
	int returnstatus;
	bzero(endL,sizeof(endL));
	//transbridgeon(mainfd);
	sprintf(endL,"%c%c",end,0x82);

        simpleChildSocket = accept(simpleSocket,(struct sockaddr *)&clientName, &clientNameLength);

        if (simpleChildSocket == -1) {

            syslog(LOG_ERR, "Cannot accept connections!\n");
            close(simpleSocket);
            exit(1);

        }
        BuffCount=read(simpleChildSocket, Buff, 3);
	TempCount=sprintf(TempBuff,"%d",BuffCount);
        syslog(LOG_WARNING, "I read %d : %s",BuffCount,Buff);
	//trying a switch case to select the begining mode of the sign protocoll
	switch(Buff[0]){
	case 'A':// Sign Type, Sign Addr (last bit)
	startc(mainfd,Buff[1],Buff[2]);
        TempCount=sprintf(TempBuff,"CASE A");
	write(simpleChildSocket, TempBuff, strlen(TempBuff) );
	bzero(Buff,sizeof(Buff));

	break;
	case 'B': //simple mode 
	starttext(mainfd,'Z','0','A');
        TempCount=sprintf(TempBuff," CASE B");
        write(simpleChildSocket, TempBuff, strlen(TempBuff));
	bzero(Buff,sizeof(Buff));

	break;
	case 'C': //set 2 line mem
        TempCount=sprintf(TempBuff,"CASE C");
        write(simpleChildSocket, TempBuff, strlen(TempBuff));
    	syslog(LOG_ERR, "CASE C Buff1=%c",Buff[1]);
    	setmem(mainfd,Buff[1]);

        bzero(Buff,sizeof(Buff));

	flag =1;	// skip loop
	break;
	case 'D': //Single line set memory
        TempCount=sprintf(TempBuff,"CASE D");
        write(simpleChildSocket, TempBuff, strlen(TempBuff));

 syslog(LOG_ERR, "CASE D"); //Log it

	slsetmem(mainfd,Buff[1]);
	bzero(Buff,sizeof(Buff));
	 syslog(LOG_ERR, "End of Case D"); //Log it


	flag =1;
	break;
	case 'P': 
	plotit();
	flag=1;
	break;
	case 'X':
	 TempCount=sprintf(TempBuff,"CASE X");
        write(simpleChildSocket, TempBuff, strlen(TempBuff));
        bzero(Buff,sizeof(Buff));
	break;
	}
       while(flag != 1){

	BuffCount=read(simpleChildSocket, Buff, sizeof(Buff));
	if(DEBUG == 1)
	syslog(LOG_WARNING, "I read %d : %s",BuffCount,Buff);	
		if(endsearch(Buff)==1 )
		{
			flag=1;
		}
		if(BuffCount == 0){
			flag =1;
		}
        /* handle the new connection request  */
        /* write out our message to the client */

			write(mainfd,Buff,strlen(Buff));
			bzero(Buff,sizeof(Buff));
/* OLD CODE SNIPPIT
        write(simpleChildSocket, ACKMESSAGE, strlen(ACKMESSAGE));
        close(simpleChildSocket);
        transbridgeon(mainfd);
        write(mainfd,Buff,strlen(Buff));
        transbridgeoff(mainfd);

*/
	}
	//transbridgeoff(mainfd);
	        write(simpleChildSocket, ACKMESSAGE, strlen(ACKMESSAGE));

	close(simpleChildSocket);
	close(mainfd);
	flag = 0;
	usleep(250);


}
int tempIO(void){
	close(mainfd);
	mainfd = open_port();
	int temp,count,rv;
	 int sockfd = 0;

	    int returnStatus = 0;
	    int i,index,JOSF ;
	    char buff[256] = "";
	    char buffer[256] = "";
	    char stringtemp[256] = "";
	    char JOS[4],JIN[4],HIN[4];
	char s[INET6_ADDRSTRLEN];

	    struct sockaddr_in simpleServer;
	    struct hostent *server;
	 struct addrinfo hints, *servinfo, *p;
	 memset(&hints, 0, sizeof hints);
	    hints.ai_family = AF_UNSPEC;
	    hints.ai_socktype = SOCK_STREAM;
	    if ((rv = getaddrinfo("xkun.endofnet.com", "5050", &hints, &servinfo)) != 0) {
	        syslog(LOG_ERR, "getaddrinfo: %s\n", gai_strerror(rv));
	        return 1;
	    }
		 /* create a streaming socket      */
	    for(p = servinfo; p != NULL; p = p->ai_next) {
	        if ((sockfd = socket(p->ai_family, p->ai_socktype,
	                p->ai_protocol)) == -1) {
	        	syslog(LOG_ERR, "client: socket");
	            continue;
	        }

	        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
	            close(sockfd);
	            syslog(LOG_ERR, "client: connect");
	            continue;
	        }

	        break;
	    }
	    	    if (p == NULL) {
	    	    	syslog(LOG_ERR, "client: failed to connect\n");
	    	        return 2;
	    	    }

	    	    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
	    	            s, sizeof s);
	    	    syslog(LOG_ERR, "client: connecting to %s\n", s);

	    	    freeaddrinfo(servinfo); // all done with this structure



	    	       temp=sprintf(stringtemp,"E"); //see DAE code for commands
	    	        temp=write(sockfd,stringtemp,temp); // normal shove out the door code

	    	        read(sockfd,stringtemp,9);
	    	        syslog(LOG_ERR, "%s",stringtemp);
	    	        index = 0;
	    	        for(i=0; i<3; i++){
	    	        	JOS[index] = stringtemp[i];
	    	        	index++;
	    	        }
	    	        index++;
	    	        JOS[index]= '\0';
	    	        JOSF = converttoF(JOS);
	    	        index = 0;

	    	        for(i=3; i<6; i++){
	    	        	JIN[index] = stringtemp[i];
	    	        	index++;
	    	        }
	    	        index++;
	    	        JIN[index]= '\0';
	    	        index = 0;

	    		close(sockfd);
	    		startc(mainfd,'Z','0');
	    		count=sprintf(stringtemp,"G4%s%c",JIN,etx);
	    		write(mainfd,stringtemp,count);
	    		count=sprintf(stringtemp,"%cG5%s%c",stx,JOS,etx);
	    		write(mainfd,stringtemp,count);
	    		count=sprintf(stringtemp,"%cG6%d%c%c",stx,JOSF,etx,end);
	    		write(mainfd,stringtemp,count);
	    		close(mainfd);
	    		return 0;
}
int converttoF(char temp[6]){
	        int TempInC, TempInF;
		char stringtemp[50];
		int tempint;
	TempInC = atoi(temp);
	//syslog(LOG_WARNING, "temp is %d\n",TempInC);
        TempInF = TempInC * 1.8  + 32;
//	syslog(LOG_WARNING, "tempF is %d\n",TempInF);

	        return TempInF;
}
int endsearch(char str[1024]){
	//This function looks at the last three chars of the input string and sees if it matches the special end char string 
	int lenOfStr;
	int i;
	int index = 0;
	int ans;
	char storage[3];
	char endL[3];
	sprintf(endL,"%c%c",end,0x82);

	lenOfStr=strlen(str);
	for(i = lenOfStr -2; i <= lenOfStr; i++){
	if(DEBUG == 1)
	syslog(LOG_WARNING,"%c \n", str[i]);
	storage[index] = str[i];
	index++;

	}
	index = 0;
	ans = strcmp(endL, storage);
	if (ans == 0){
	return 1;
	}else{
	return 0;
	}



}
int plotit(){ 
char temp[50];
    gnuplot_ctrl * h ;
    h = gnuplot_init() ;
    // gnuplot_set_ylabel(h, "Temp") ;
      //  gnuplot_set_xlabel(h, "Time") ;
           gnuplot_cmd(h, "set terminal png size 900,900");
            gnuplot_cmd(h, "set output \"/tmp/Temp1.png\"");
            gnuplot_cmd(h, "set xdata time");
            gnuplot_cmd(h,"set timefmt \"%%m-%%d-%%H:%%M:%%S\"");
          // gnuplot_cmd(h,"set xrange [\"08-10-00:00\":\"08-11-23:59\"]");
            //gnuplot_cmd(h, "set grid");
            gnuplot_cmd(h, "plot \"/tmp/log1\" using 1:2 index 0 with linespoint");
       gnuplot_close(h);
    h = gnuplot_init() ;

       // gnuplot_set_ylabel(h, "Temp") ;
         //  gnuplot_set_xlabel(h, "Time") ;
              gnuplot_cmd(h, "set terminal png size 900,900");
               gnuplot_cmd(h, "set output \"/tmp/Temp2.png\"");
               gnuplot_cmd(h, "set xdata time");
               gnuplot_cmd(h,"set timefmt \"%%m-%%d-%%H:%%M:%%S\"");
             // gnuplot_cmd(h,"set xrange [\"08-10-00:00\":\"08-11-23:59\"]");
               //gnuplot_cmd(h, "set grid");
               gnuplot_cmd(h, "plot \"/tmp/log2\" using 1:2 index 0 with linespoint");
          gnuplot_close(h);
          return 0;
 ;





}
void signal_handler(int sig) {
 
    switch(sig) {
        case SIGHUP:
            syslog(LOG_WARNING, "Received SIGHUP signal.");
	    close(simpleSocket);
	    close(mainfd);
            closelog();
	            exit(EXIT_SUCCESS);
        case SIGTERM:
            syslog(LOG_WARNING, "Received SIGTERM signal.");
            close(simpleSocket);
            close(mainfd);

		closelog();
        exit(EXIT_SUCCESS);
	case SIGIO:	
	 syslog(LOG_WARNING, "SIG IO SIG IO!!!!!!i went to signal_handler");    
            close(simpleSocket);
            close(mainfd);

            closelog();

        exit(EXIT_SUCCESS);


        default:
            syslog(LOG_WARNING, "Unhandled signal  %s", strsignal(sig));
            close(simpleSocket);
            close(mainfd);

		closelog();

        exit(EXIT_SUCCESS);

    }
}
int ReadTemp(){
/* this function will read 100  chars from the pic chip and stop and proccess these 20 charaters 
 * staring with Z00
 * look for g1 or g2 
 * output branch 
 * output temp
 * ?????
 * Profit!
 */
 char strout[100];
char strouttmp[100];
char tempchar= 0;
char Gnum[3];
int bytes =0;
int stat;
int i=0;
int n=0;
int nullcount=0;
char tempinC[8];
bzero(Gnum,sizeof(Gnum));
bzero(strout,sizeof(strout));
mainfd = open_port();
sleep(1);
    ioctl(mainfd, FIONREAD, &bytes); //read number of bytes aviable to read in 
	if(bytes == 0 )
	return 1;
	for(i=0 ; i < bytes; i++){
		stat = read(mainfd, &tempchar, sizeof(tempchar));  //debuging check with the stat = blah 
		        if(DEBUG == 1)
		syslog(LOG_WARNING,"in for %d %c \n",stat,tempchar); //debug it out 
		strouttmp[i] = tempchar; //Copy the char to the array 
		if(tempchar == 0x00) //check if null 
			nullcount++; // inc nullcount 
		}	

	for(i=nullcount; i < bytes; i++){ //then for loop it with the offset of the null count 
		strout[n] = strouttmp[i]; //copy and paste it to another array 
		n++; // inc array counter 
		}
	n++;
	strout[n] ='\0'; //add a null just incase 
        if(DEBUG == 1)
	syslog(LOG_WARNING,"read from mainfd %d =%s \n",bytes, strout); //dump out the string 
	n = 0;
	for(i=5; i < 7; i++){
	Gnum[n] = strout[i];

	n++;
	}
	
	Gnum[n] = '\0';
        if(DEBUG == 1)
	syslog(LOG_WARNING,"String get =%sX \n",Gnum); //dump out the string

	//start of switch for which probe we are looking at
		if(strcmp(Gnum, "G1")==0){
		n=0;
			for(i=8 ; i <11; i++){
			tempinC[n] = strout[i];
			n++;
			}
		
		tempinC[n] ='\0';
	        syslog(LOG_WARNING,"IN G1!!!!!!!!!! %s \n",tempinC); //dump out
		converttoFtoG3(tempinC);
		logittofile(1,tempinC);	

		}else if(strcmp(Gnum, "G2")==0){
                n=0;
                        for(i=8 ; i <11; i++){
                        tempinC[n] = strout[i];
                        n++;
                        }
                n++;
                tempinC[n] ='\0';
                syslog(LOG_WARNING,"IN G2!!!!!!!!!! %s \n",tempinC); //dump out
                logittofile(2,tempinC);


                }

bzero(strout,sizeof(strout)); //clean up 
bzero(strouttmp,sizeof(strouttmp));
close(mainfd);
tempIO();
return 0;
} 
int converttoFtoG3(char temp[6]){
	        int TempInC, TempInF;
		char stringtemp[50];
		int tempint;
	TempInC = atoi(temp);
	//syslog(LOG_WARNING, "temp is %d\n",TempInC);
        TempInF = TempInC * 1.8  + 32;
//	syslog(LOG_WARNING, "tempF is %d\n",TempInF);
                transbridgeon(mainfd);

	startc(mainfd,'Z','0');
    tempint=sprintf(stringtemp,"G3%d%c",TempInF,end);
     tempint=write(mainfd,stringtemp,tempint);
	        transbridgeoff(mainfd);
	        return 0;
}

int logittofile(int probe, char tempinC[6]){
    int log1, log2,count;
    struct tm *ptr;
    time_t lt;
    char str[80];
    char tempchar[100];
   
log1 = open("/tmp/log1", O_RDWR | O_APPEND | O_CREAT, 0644);
log2 = open("/tmp/log2", O_RDWR | O_APPEND | O_CREAT, 0644);
    lt = time(NULL);
    ptr = localtime(&lt);

    strftime(str, 100, "%m-%d-%H:%M:%S", ptr);
	syslog(LOG_ERR,"%d %s %s",probe,str,tempinC);
	if (probe == 1){
	count=sprintf(tempchar,"%s %s\n",str,tempinC);
	shovetoserver(probe, tempinC);
	write(log1,tempchar,count);
	}else if (probe ==2){
        count=sprintf(tempchar,"%s %s\n",str,tempinC);
        write(log2,tempchar,count);
//    	shovetoserver(probe, tempinC);
	}

	close(log1);
	close(log2);
	return 0;
}
// get sockaddr, IPv4 or IPv6:

int shovetoserver(int probe, char tempinC[6]){
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
	 memset(&hints, 0, sizeof hints);
	    hints.ai_family = AF_UNSPEC;
	    hints.ai_socktype = SOCK_STREAM;
	    if ((rv = getaddrinfo("xkun.endofnet.com", "5050", &hints, &servinfo)) != 0) {
	        syslog(LOG_ERR, "getaddrinfo: %s\n", gai_strerror(rv));
	        return 1;
	    }
		 /* create a streaming socket      */
	    for(p = servinfo; p != NULL; p = p->ai_next) {
	        if ((sockfd = socket(p->ai_family, p->ai_socktype,
	                p->ai_protocol)) == -1) {
	        	syslog(LOG_ERR, "client: socket");
	            continue;
	        }

	        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
	            close(sockfd);
	            syslog(LOG_ERR, "client: connect");
	            continue;
	        }

	        break;
	    }
	    if (p == NULL) {
	    	syslog(LOG_ERR, "client: failed to connect\n");
	        return 2;
	    }

	    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
	            s, sizeof s);
	    syslog(LOG_ERR, "client: connecting to %s\n", s);

	    freeaddrinfo(servinfo); // all done with this structure


	    if(probe == 1){
	       temp=sprintf(stringtemp,"LHI%s",tempinC); //see DAE code for commands
	        temp=write(sockfd,stringtemp,temp); // normal shove out the door code
	    }else if(probe == 2){
	        temp=sprintf(stringtemp,"LHO%s",tempinC); //see DAE code for commands
	        temp=write(sockfd,stringtemp,temp); // normal shove out the door code
	    }

		close(sockfd);

	return 0;
}
int main(void)
{
//    setup signal handling
//

 struct sigaction handler;
  handler.sa_handler = IO_GO; // Set signal handler for SIGIO
// Create mask that mask all signals
   if (sigfillset(&handler.sa_mask) < 0)
      perror("sigfillset() failed");
         handler.sa_flags = 0;              // No flags
  //
           if (sigaction(SIGIO, &handler, 0) < 0)

           perror("sigaction() failed for SIGIO");
  //
  //                 // We must own the socket to receive the SIGIO message
    
    signal(SIGHUP, signal_handler); // Turn on normal Signal Handling 
    signal(SIGTERM, signal_handler);// and point to the signal_handler subroutne
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
    int simplePort = 0;
    int returnStatus = 0;
    int x;
    int worked;
    struct sockaddr_in simpleServer;

	pid_t pid, sid;
	
	int fd, len;
	time_t timebuf;


	/* Open the system log */
	openlog("tempmond", LOG_PID, LOG_DAEMON);//Name of program goes in here 

	

	pid = fork();
	if(pid < 0) {
		syslog(LOG_ERR, "%s\n","fork");
		exit(EXIT_FAILURE);
	}
	if(pid > 0){
		//in parent, lets bail
		exit(EXIT_SUCCESS);
	}
	//In the child ...
	//First start a new session
	if((sid = setsid()) < 0) {
		syslog(LOG_ERR, "%s\n","setsid");
		exit(EXIT_FAILURE);
	}
	//Next make / the current working dir
	if((chdir("/")) < 0) {
		syslog(LOG_ERR, "%s\n","chdir");
                exit(EXIT_FAILURE);
	}
	//Reset File mode
	umask(0);
	//Close the world stdin....etc
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	//FINALLY LETS DO SOME WORK!
	 simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

                if (fcntl(simpleSocket, F_SETOWN, getpid()) < 0)
	 syslog(LOG_ERR, "Unable to set process owner to us");
        // Arrange for nonblocking I/O and SIGIO delivery  is this redundent?
           if (fcntl(simpleSocket, F_SETFL, O_NONBLOCK | FASYNC) < 0)
               syslog(LOG_ERR, "Unable to put client sock into non-blocking/async mode");
  //
	    if (simpleSocket == -1) {

         syslog(LOG_ERR,"Could not create a socket!");
        exit(EXIT_FAILURE);

    }
    else {
             syslog(LOG_ERR, "Socket created!\n");
    }
/* retrieve the port number for listening */
    simplePort = atoi("5050");

    /* setup the address structure */
    /* use INADDR_ANY to bind to all local addresses  */
    bzero(&simpleServer, sizeof(simpleServer));
    simpleServer.sin_family = AF_INET;
    simpleServer.sin_addr.s_addr = htonl(INADDR_ANY); //NOTICE THE htonl and htons functions!
    simpleServer.sin_port = htons(simplePort);
//Trying non blocking code here is this redundent? 
	x=fcntl(simpleSocket,F_GETFL,0);
	fcntl(simpleSocket,F_SETFL,x | O_NONBLOCK);

    /*  bind to the address and port with our socket  */
    returnStatus = bind(simpleSocket,(struct sockaddr *)&simpleServer,sizeof(simpleServer));

    if (returnStatus == 0) {
		        
            syslog(LOG_ERR,  "Bind completed!\n");
    }
    else {
        syslog(LOG_ERR, "Could not bind to address!\n");
        close(simpleSocket);
        exit(EXIT_FAILURE);
    }
 /* lets listen on the socket for connections      */
    returnStatus = listen(simpleSocket, 5);

    if (returnStatus == -1) {
        syslog(LOG_ERR, "Cannot listen on socket!\n");
        close(simpleSocket);
        exit(EXIT_FAILURE);
    }

    while (1){
        /* wait here */
//	worked=ReadTemp();
//	if (worked == 1){
//	close(mainfd);
//	sleep(3);
  //      if(DEBUG == 1)
//	        syslog(LOG_ERR, "Noting to hear\n");
		
//
//	}else {
//	 sleep(120);
//	}
	sleep(120);
}

	//we never get here !
	closelog();
	exit(EXIT_SUCCESS);	
}
