#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "signfp.h"
#include <mysql.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
/* build ins
 gcc -o mysqlreader  $(mysql_config --cflags) mysqlreader.c signfp.c $(mysql_config --libs)

*/
int shoveToSign (int port, char sign_addr, char *message);
struct contact
   {
      char id[30];
      char call[30];
      char type[30];
      char location[30];
      char date[35];
      char time[35];
      char  band[30];
      char mode[4];
      char op[25];
   };
int main( int argc, char *argv[])
{
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;
   struct contact list[5];
   char *server = "127.0.0.1";
   char *user = "ham";
   char *password = "K5SLD"; /* set me first */
   char *database = "FD";
FILE *tty;
int i = 0;
int count = 0;
int lines ;
char c;
char buff[512] ; // output to the sign
char bufftmp[100]; // local concat
int numberOfRows;

		 



   conn = mysql_init(NULL);

   /* Connect to database */
   if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
   if (mysql_query(conn, "select fldPrimaryKey,fldCall,FldBand,FldMode,fldComputerName  from tblContacts where FldBand>=10 AND FldMode ='DIG'")) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }

   res = mysql_store_result(conn);
   numberOfRows = mysql_num_rows(res);

   mysql_free_result(res);



sprintf(buff,"G3%d",numberOfRows);


sprintf(bufftmp,"%c",end);
strcat(buff,bufftmp);
//printf("%s",buff);
shoveToSign(5050,'0',buff);
//Digiatial 2
if (mysql_query(conn, "select fldPrimaryKey,fldCall,FldBand,FldMode,fldComputerName  from tblContacts where FldBand>=10 AND FldMode ='CW'")) {
   fprintf(stderr, "%s\n", mysql_error(conn));
   exit(1);
}

res = mysql_store_result(conn);
numberOfRows = mysql_num_rows(res);

mysql_free_result(res);



sprintf(buff,"G2%d",numberOfRows);


sprintf(bufftmp,"%c",end);
strcat(buff,bufftmp);
//printf("%s",buff);
shoveToSign(5050,'0',buff);
//phone
if (mysql_query(conn, "select fldPrimaryKey,fldCall,FldBand,FldMode,fldComputerName  from tblContacts where FldBand>=10 AND FldMode ='PH'")) {
   fprintf(stderr, "%s\n", mysql_error(conn));
   exit(1);
}

res = mysql_store_result(conn);
numberOfRows = mysql_num_rows(res);

mysql_free_result(res);




sprintf(buff,"G1%d",numberOfRows);


sprintf(bufftmp,"%c",end);
strcat(buff,bufftmp);
//printf("%s",buff);
shoveToSign(5050,'0',buff);

//vhf
if (mysql_query(conn, "select fldPrimaryKey,fldCall,FldBand,FldMode,fldComputerName from tblContacts where FldBand<10")) {
   fprintf(stderr, "%s\n", mysql_error(conn));
   exit(1);
}

res = mysql_store_result(conn);
numberOfRows = mysql_num_rows(res);

mysql_free_result(res);




sprintf(buff,"G4%d",numberOfRows);


sprintf(bufftmp,"%c",end);
strcat(buff,bufftmp);
//printf("%s",buff);
shoveToSign(5050,'0',buff);

//TOTAL
if (mysql_query(conn, "select * from tblContacts ORDER BY fldPrimaryKey")) {
   fprintf(stderr, "%s\n", mysql_error(conn));
   exit(1);
}

res = mysql_store_result(conn);
numberOfRows = mysql_num_rows(res);

mysql_free_result(res);





sprintf(buff,"G5%d",numberOfRows);


sprintf(bufftmp,"%c",end);
strcat(buff,bufftmp);
//printf("%s",buff);
shoveToSign(5050,'0',buff);


sprintf(buff,"G5%d",numberOfRows);
//shove to ethernet sign

sprintf(bufftmp,"%c",end);
strcat(buff,bufftmp);
printf("%s",buff);
shoveToSign(5052,'0',buff);
//shoveToSign(5050,'6',buff);
/*
i =0;
   if (mysql_query(conn, "SELECT * FROM hfphone ORDER BY id DESC LIMIT 0,5")) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }

   res = mysql_use_result(conn);

while ((row = mysql_fetch_row(res)) != NULL)
      	{


        strcpy(list[i].id, row[0]);
        strcpy(list[i].call, row[1]);
        strcpy(list[i].type, row[2]);
        strcpy(list[i].location, row[3]);
        strcpy(list[i].date, row[4]);
        strcpy(list[i].time, row[5]);
        strcpy(list[i].band, row[6]);
        strcpy(list[i].mode, row[7]);
        strcpy(list[i].op, row[8]);

	i++;
	}
	count =i;
   mysql_free_result(res);

starttext('Z','2','A');
tty = fopen("/dev/ttyS0", "r+");
    

fprintf(tty,"%c0b%c%c ",smf,cc,green);
fprintf(tty,"HF PHONE WORKED \nupdated every min.\n");
fprintf(tty,"%c0b%c%c%c5",smf,cc,red,0x1A);
for(i =0 ; i < count ; i++)
{0.20.2.50"
fprintf(tty,"%s ",list[i].id);
fprintf(tty,"%s ",list[i].call);
fprintf(tty,"%s ",list[i].type);
fprintf(tty,"%s \n",list[i].location);
fprintf(tty,"%sUTC\n",list[i].time);
fprintf(tty,"%s ",list[i].band);
fprintf(tty,"%s ",list[i].mode);
fprintf(tty,"%s \n",list[i].op);
}

fprintf(tty,"%c",end);
fclose(tty);

i =0;
   if (mysql_query(conn, "SELECT * FROM hfcw ORDER BY id DESC LIMIT 0,5")) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }

   res = mysql_use_result(conn);

while ((row = mysql_fetch_row(res)) != NULL)
      	{


        strcpy(list[i].id, row[0]);
        strcpy(list[i].call, row[1]);
        strcpy(list[i].type, row[2]);
        strcpy(list[i].location, row[3]);
        strcpy(list[i].date, row[4]);
        strcpy(list[i].time, row[5]);
        strcpy(list[i].band, row[6]);
        strcpy(list[i].mode, row[7]);
        strcpy(list[i].op, row[8]);

	i++;
	}
count = i;
   mysql_free_result(res);

starttext('Z','3','A');
tty = fopen("/dev/ttyS0", "r+");
    

fprintf(tty,"%c0b%c%c ",smf,cc,green);
fprintf(tty,"HF Digital WORKED \nupdated every min.\n");
fprintf(tty,"%c0b%c%c%c5",smf,cc,red,0x1A);
for(i =0 ; i < count ; i++)
{
fprintf(tty,"%s ",list[i].id);
fprintf(tty,"%s ",list[i].call);
fprintf(tty,"%s ",list[i].type);
fprintf(tty,"%s \n",list[i].location);
fprintf(tty,"%sUTC\n",list[i].time);
fprintf(tty,"%s ",list[i].band);
fprintf(tty,"%s ",list[i].mode);
fprintf(tty,"%s \n",list[i].op);
}

fprintf(tty,"%c",end);
fclose(tty);


i =0;
   if (mysql_query(conn, "SELECT * FROM gota ORDER BY id DESC LIMIT 0,5")) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }

   res = mysql_use_result(conn);

while ((row = mysql_fetch_row(res)) != NULL)
      	{


        strcpy(list[i].id, row[0]);
        strcpy(list[i].call, row[1]);
        strcpy(list[i].type, row[2]);
        strcpy(list[i].location, row[3]);
        strcpy(list[i].date, row[4]);
        strcpy(list[i].time, row[5]);
        strcpy(list[i].band, row[6]);
        strcpy(list[i].mode, row[7]);
        strcpy(list[i].op, row[8]);

	i++;
	}
count = i;
   mysql_free_result(res);

starttext('Z','4','A');
tty = fopen("/dev/ttyS0", "r+");
    

fprintf(tty,"%c0b%c%c ",smf,cc,green);
fprintf(tty,"GOTA STATION WORKED \nupdated every min.\n");
fprintf(tty,"%c0b%c%c%c5",smf,cc,red,0x1A);
for(i =0 ; i < count ; i++)
{
fprintf(tty,"%s ",list[i].id);
fprintf(tty,"%s ",list[i].call);
fprintf(tty,"%s ",list[i].type);
fprintf(tty,"%s \n",list[i].location);
fprintf(tty,"%sUTC\n",list[i].time);
fprintf(tty,"%s ",list[i].band);
fprintf(tty,"%s ",list[i].mode);
fprintf(tty,"%s \n",list[i].op);
}


fprintf(tty,"%c",end);
fclose(tty);
*/
   mysql_close(conn);

return 0;
}

int shoveToSign (int port, char sign_addr, char *message){
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

	    /* create a streaming socket      */
	    simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	    if (simpleSocket == -1) {

	        fprintf(stderr, "Could not create a socket!\n");
	        return 1;

	    }
	    else {
	//	    fprintf(stdout, "Socket created!\n");
	    }

	    /* retrieve the port number for connecting */
	    simplePort = port;

		//    server = gethostbyname(argv[1]); is the magical dns lookup
		    server = gethostbyname("172.90.0.1");


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
		//    fprintf(stderr, "Connect successful!\n");
	    }
	    else {
	        fprintf(stderr, "Could not connect to address! %d %c \n",port,sign_addr);
		close(simpleSocket);
		exit(1);
	    }

	    /* get the message from the server   */
	       temp=sprintf(stringtemp,"AZ%c", sign_addr); //! for debug
	//	printf("%s",stringtemp);
		temp=write(simpleSocket,stringtemp,temp);
		read(simpleSocket, buffer, sizeof(buffer));
	//	printf("%s \n",buffer);
/*		were not updating the message only the string buff
 *     temp=sprintf(stringtemp,"AA");
	       temp=write(simpleSocket,stringtemp,temp);

		 temp=sprintf(stringtemp,"%c b %c%c",smf,fontmode,largetimesfont); //Set the sign to scroll on all lines
	                                                                        // and largetimes font in to buffer
	       temp=write(simpleSocket,stringtemp,temp); //write buffer to mainfd (which should be the serial port see signfp.c)

	                        temp=sprintf(stringtemp,"%c%c",cc,green);
	                          temp=write(simpleSocket,stringtemp,temp);
*/
		 temp=strlen(message);  //count the argv2 which should be a string
	        temp=write(simpleSocket,message,temp); // and shove x chars out the door
		temp=sprintf(stringtemp,"%c",end); // tell the sign were done
	        temp=write(simpleSocket,stringtemp,temp); // output it


		usleep(250);

		 endloop(simpleSocket);

	    returnStatus = read(simpleSocket, buffer, sizeof(buffer));

	    if ( returnStatus > 0 ) {
	  //      printf("%d: %s", returnStatus, buffer);
	    } else {
	        fprintf(stderr, "Return Status = %d \n", returnStatus);
	    }

	    close(simpleSocket);
	    return 0;

	}
