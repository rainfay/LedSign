//Jason Archip 2013 2line_cmd.c
// This program shall take inputs form the command line process them and send it over tcp to a sign server 
// which will display it on a sign 

#include "signfp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <getopt.h>
//#define DEBUG 1 moved to a flag 
int DEBUG;

int main(int argc, char **argv) {

    int simpleSocket = 0;
    int simplePort = 0;
    int returnStatus = 0;
    char IP[255] = "";
    char port[10] = "";
    char line1mode[4] = "";
    char line2mode[4] = "";
    char sign_addr[4] = "";
    char line1color[10] = "";
    char line1text[1024] = "";
    char line2color[10] = "";
    char line2text[1024] = "";
    char time_var[3] = "";
    int timearray[2] ;
    int datearray[2];
    char buffer[1024] = "";
    struct sockaddr_in simpleServer;
    struct hostent *server;
    int LOL1;
	char LOL[256];
	int temp;
	char stringtemp[1024];
   int c;

if (1 == argc)
exit(1);

while (1)
{
static struct option long_options[] =
             {
               /* These options set a flag. */
               {"debug", no_argument,       &DEBUG, 1},
               /* These options don't set a flag.
                  We distinguish them by their indices. */
               {"server",  required_argument, 0, 'a'},
               {"port",  required_argument, 0, 'b'},
               {"sign",  required_argument, 0, 'c'},
               {"line1color",    required_argument, 0, 'd'},
	       {"line1text",    required_argument, 0, 'e'},
	       {"line2color",   required_argument, 0, 'f'},
	       {"line2text",    required_argument, 0, 'g'},
	       {"time",		required_argument, 0, 'h'},
	       {"line1mode", 	required_argument, 0, 'i'},
	       {"line2mode",    required_argument, 0, 'j'},
	       {"date",		required_argument, 0, 'k'},
	       {"help",		no_argument,	  0, '?'},
               {0, 0, 0, 0}
             };

           /* getopt_long stores the option index here. */
           int option_index = 0;
 c = getopt_long (argc, argv, "?", long_options, &option_index); 
	if (c == -1)
	break;
	
	switch (c)
	{
	case 'a':
		if (DEBUG == 1)
		printf("--server is %s\n\n", optarg);
	temp=strlen(optarg);
		if (temp >254){
		fprintf(stderr,"IP too long\n\n");
		exit(1);
		}
	strncpy(IP, optarg, temp); //IP = optarg;
	break;
	
	case 'b':
                if (DEBUG == 1)
                printf("--port is %s\n\n", optarg);
	        temp=strlen(optarg);
		                if (temp >9){
                fprintf(stderr,"Port too long\n\n");
                exit(1);
                }       		 
		strncpy(port, optarg, temp); //port = optarg
	break;
	
	case 'c':
                if (DEBUG == 1)
                 printf("--sign is %s\n\n", optarg);
                temp=strlen(optarg);
                if (temp >1){
                fprintf(stderr,"sign Addr is too long\n\n");
                exit(1);
                }

                 strncpy(sign_addr, optarg, temp); //sign_addr = optarg;	
	break;
	case 'd': 
		if (DEBUG == 1)
                 printf("--line1color is %s\n\n", optarg);
                temp=strlen(optarg);
                if (temp >9){
                fprintf(stderr,"Color to long\n\n");
                exit(1);
                }

                 strncpy(line1color, optarg, temp); //line1color = optarg;
	break;
	case 'e':
		if (DEBUG == 1)
                 printf("--line1text is %s\n\n", optarg);
                temp=strlen(optarg);
                if (temp >1023){
                fprintf(stderr,"Text too long\n\n");
                exit(1);
                }

                 strncpy(line1text, optarg, temp); //line1text = optarg;
	break;
	case 'f':
		if (DEBUG == 1)
                 printf("--line2color is %s\n\n", optarg);
                temp=strlen(optarg);
                if (temp >9){
                fprintf(stderr,"Color2 too long\n\n");
                exit(1);
                }

                 strncpy(line2color, optarg, temp); //line2color = optarg;
	break;
	case 'g':
		if (DEBUG == 1)
                 printf("--line2text  is %s\n\n", optarg);
                temp=strlen(optarg);
                if (temp >1023){
                fprintf(stderr,"Text2 too long\n\n");
                exit(1);
                }

                 strncpy(line2text, optarg, temp); //line2text = optarg;
	break;
	case 'h':
		if (DEBUG == 1)
                 printf("--time is %s\n\n", optarg);
                temp=strlen(optarg);
                 strncpy(time_var, optarg, temp); //time_var = optarg;
		temp = atoi(time_var);
		if (temp == 1){
		   timearray[0] = 1;
		} else if (temp == 2){
		   timearray[1]  = 1 ;
		}else {
		printf("TIME VAR IS WRONG :( (OUT OF RANGE)\n");
		exit(1);
		}
	break;
	case 'i':
                if (DEBUG == 1)
                 printf("--line1mode is %s\n\n", optarg);
                temp=strlen(optarg);
                if (temp >3){
                fprintf(stderr,"line1mode too long\n\n");
                exit(1);
                }

                 strncpy(line1mode, optarg, temp); //line1mode = optarg;	
	
	break;
	case 'j':
                if (DEBUG == 1)
                 printf("--line2mode is %s\n\n", optarg);
                temp=strlen(optarg);
                if (temp >3){
                fprintf(stderr,"line2mode too long\n\n");
                exit(1);
                }
                 strncpy(line2mode, optarg, temp); //line2mode = optarg;	
	
	break;
	case 'k':
                if (DEBUG == 1)
                 printf("--date is %s\n\n", optarg);
                temp=strlen(optarg);
                 strncpy(time_var, optarg, temp); //time_var = optarg;
                temp = atoi(time_var);
                if (temp == 1){
                   datearray[0] = 1;
                } else if (temp == 2){
                   datearray[1]  = 1 ;
                }else {
                printf("DATEVAR IS WRONG :( (OUT OF RANGE)\n");
                exit(1);
                }
	
	break;

	case '?':
	       fprintf(stderr, "Welcome to %s ! this program will display two lines of text on a 4120c led sign add --time <line num> to add time at the end of line \n",argv[0]);
		//					0  1         2       3          4                  5            6            7
fprintf(stderr, "Usage: %s --server <ip> --port <port> --sign <addr> --line1color <color> --line1mode <mode letter> --line1text \"line 1\" --line2mode <mode letter> --line2color <color> --line2text \"line 2\"\n", argv[0]);
		
        exit(1);
	break;

    }
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
    simplePort = atoi(port);
	//    server = gethostbyname(argv[1]); is the magical dns lookup
	    server = gethostbyname(IP);

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
	   if (DEBUG ==1 ){
    	fprintf(stderr, "Connect successful!\n");
	   }
	   }
    else {
        fprintf(stderr, "Could not connect to address!\n");
	close(simpleSocket);
	exit(1);
    }

 /*  get the mode sign mode sane */
	if(strcmp(line1mode,"")==0){
	strncpy(line1mode, "b", 1);
	}
	if(strcmp(line2mode,"")==0){
	strncpy(line2mode, "t", 1);
	}

    /* get the message to the server   */
       temp=sprintf(stringtemp,"AZ%s",sign_addr);  //Start building the message here 
	if (DEBUG == 1){
       printf("DEBUG: %s \n",stringtemp);
	}
	temp=write(simpleSocket,stringtemp,temp);  //shove it out the door 
	read(simpleSocket, buffer, sizeof(buffer));
	if (DEBUG == 1){
	printf("DEBUG FROM SERVER: %s \n",buffer);
	}
       temp=sprintf(stringtemp,"AA");
       temp=write(simpleSocket,stringtemp,temp);

	 temp=sprintf(stringtemp,"%c%c%s %c%c",smf,topline,line1mode,fontmode,normalsmallfont); //Set the sign to hold on top line
                                                                        // and normal small font in to buffer
       temp=write(simpleSocket,stringtemp,temp); //write buffer to socket 
       if (strcmp(line1color,"red")==0){	//line  1 color anyone?
    		if (DEBUG == 1){
    		printf("DEBUG: red argv[4] \n");
    		}
	 temp=sprintf(stringtemp,"%c%c",cc,red);// set the color code
         temp=write(simpleSocket,stringtemp,temp); //and shove it out the door

	}else if (strcmp(line1color,"green")==0){
                        temp=sprintf(stringtemp,"%c%c",cc,green);
                          temp=write(simpleSocket,stringtemp,temp);
                  		if (DEBUG == 1){
                  		printf("DEBUG: green argv[4] \n");
                  		}

        }else if (strcmp(line1color,"amber")==0){
                        temp=sprintf(stringtemp,"%c%c",cc,amb);
                        temp=write(simpleSocket,stringtemp,temp);
                		if (DEBUG == 1){
                		printf("DEBUG: Amber argv[4] \n");
                		}
        }else
                {

                        temp=sprintf(stringtemp,"%c%c",cc,green);
                        temp=write(simpleSocket,stringtemp,temp);
                		if (DEBUG == 1){
                		printf("DEBUG: WRONG INPUT --line1color \n");
                		}


		}

	 temp=strlen(line1text);  //count the line1text  which should be a string
        temp=write(simpleSocket,line1text,temp); // and shove x chars out the door
	if (timearray[0] == 1){ //time at the end of the line
	temp=sprintf(stringtemp," %c",timeLED);
	temp=write(simpleSocket,stringtemp,temp);
	}
	 if (datearray[0] == 1){ //date at the end of the line
        temp=sprintf(stringtemp," %c%c",date,datemmddyy);
        temp=write(simpleSocket,stringtemp,temp);
        }

        //Now for the Bot line
   	 temp=sprintf(stringtemp,"%c%c%s %c%c",smf,botline,line2mode,fontmode,normalsmallfont); //Set the sign to scroll on bot line
                                                                           // and normal small font in to buffer
          temp=write(simpleSocket,stringtemp,temp); //write buffer to mainfd (which should be the serial port see signfp.c)
          if (strcmp(line2color,"red")==0){ //line2color anyone?
      		if (DEBUG == 1){
      		printf("DEBUG: red argv[6] \n");
      		}
   	 temp=sprintf(stringtemp,"%c%c",cc,red);// set the color code
            temp=write(simpleSocket,stringtemp,temp); //and shove it out the door

   	}else if (strcmp(line2color,"green")==0){
                           temp=sprintf(stringtemp,"%c%c",cc,green);
                             temp=write(simpleSocket,stringtemp,temp);
                       		if (DEBUG == 1){
                           		printf("DEBUG: green --line2color \n");
                           		}

           }else if (strcmp(line2color,"amber")==0){
                           temp=sprintf(stringtemp,"%c%c",cc,amb);
                           temp=write(simpleSocket,stringtemp,temp);
                     		if (DEBUG == 1){
                         		printf("DEBUG: amb --line2color \n");
                         		}
           }else
                   {

                           temp=sprintf(stringtemp,"%c%c",cc,green);
                           temp=write(simpleSocket,stringtemp,temp);
                     		if (DEBUG == 1){
                         		printf("DEBUG: WRONG INPUT --line2color \n");
                         		}


   		}

   	 temp=strlen(line2text);  //count the argv5 which should be a string
           temp=write(simpleSocket,line2text,temp); // and shove x chars out the door
     		if (DEBUG == 1){
         		printf("DEBUG line2text: %s \n",line2text);
         		}
        if (timearray[1] == 1){ //then line 2 time is added 
        temp=sprintf(stringtemp," %c",timeLED);
        temp=write(simpleSocket,stringtemp,temp);
        }
         if (datearray[1] == 1){ //date at the end of the line
        temp=sprintf(stringtemp," %c%c",date,datemmddyy);
        temp=write(simpleSocket,stringtemp,temp);
        }


        temp=sprintf(stringtemp," %c",end); // tell the sign were done
        temp=write(simpleSocket,stringtemp,temp); // output it
 		if (DEBUG == 1){
     		printf("DEBUG: End sent \n");
     		}


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
