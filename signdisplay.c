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
 gcc -o signdisplay  $(mysql_config --cflags) signdisplay.c signfp.c $(mysql_config --libs)

*/
int shoveToSign (int port, char sign_addr, char *message);

int signB(int a);
int signA(int a);
int sign9(int a);
int sign8(int a);
int sign7(int a);
int sign6(int a);
int sign5(int a);
int sign4(int a);
int sign3(int a);
int sign2(int a);
int sign1(int a);
struct Player //this table shall hold the table player
   {
      char key[15];
      char name[65];
      char score[5];
      char active[3];
      char sign[3];
    };
struct Game //this table shall hold the table Game
   {
      char key[15];
      char game[65];
      char playername[65];
    };
struct SignPatch //this table shall hold the table signs patch
   {
      char key[3];
      char sign[3];
      char mode[3];
    };

//start shared global structs
struct Player player[120];
struct Player playsign3[10];
struct Player playsign4[10];
struct Player playsign5[10];
struct Player playsign6[10];
struct Player playsign7[10];
struct Player playsign8[10];
struct Player playsign9[10];
struct Player playsignA[10];
struct Player playsignB[10];

struct SignPatch signpatch[12];
//end global struts
//start Message text
const char mode1Top[] = "Ranking";
const char mode2One[] = "Ranking";
const char mode3Top[] = "Overall Rankings";
const char mode3Bot ='a' ;
const char mode3Mode = 'b';
		int main( int argc, char *argv[]){
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;
   char *server = "127.0.0.1";
   char *user = "kd5lct";
   char *password = "PASS"; /* set me first */
   char *database = "Game";

int i = 0;
int count = 0;
int lines ;
char c;
char buff[512] ; // output to the sign
char bufftmp[100]; // local concat
int numberOfRows;

		 
printf("ALIVE");


   conn = mysql_init(NULL);

   /* Connect to database */
   if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
   if (mysql_query(conn, "SELECT * FROM Player Order by score desc")) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
   i=0;
   res = mysql_store_result(conn);
   while ((row = mysql_fetch_row(res)) != NULL)
         	{

/*       char key[15];
      char name[65];
      char score[10];
      char active[3];
      char sign[3];   */
           strcpy(player[i].key, row[0]);
           strcpy(player[i].name, row[1]);
           strcpy(player[i].score,row[2]);
           strcpy(player[i].active, row[3]);
           strcpy(player[i].sign, row[4]);
           printf("lol\n");
   	i++;
   	}
  // 	count =i;
      mysql_free_result(res);
      if (mysql_query(conn, "SELECT * FROM SignPatch")) {
          fprintf(stderr, "%s\n", mysql_error(conn));
          exit(1);
       }
       i=0;
       res = mysql_store_result(conn);
       while ((row = mysql_fetch_row(res)) != NULL)
             	{

    /*      char key[3];
      char sign[3];
      char mode;  */
               strcpy(signpatch[i].key, row[0]);
               strcpy(signpatch[i].sign, row[1]);
               strcpy(signpatch[i].mode,row[2]);
               printf("%d %s %s\n",i,signpatch[i].sign, signpatch[i].mode);

       	i++;
       	}


       if (mysql_query(conn, "SELECT * FROM Player WHERE Player.sign ='B' Order by score desc ")) {
          fprintf(stderr, "%s\n", mysql_error(conn));
          exit(1);
       }
       i=0;
       res = mysql_store_result(conn);
       while ((row = mysql_fetch_row(res)) != NULL)
             	{

    /*       char key[15];
          char name[65];
          char score[10];
          char active[3];
          char sign[3];   */
               strcpy(playsignB[i].key, row[0]);
               strcpy(playsignB[i].name, row[1]);
               strcpy(playsignB[i].score,row[2]);
               strcpy(playsignB[i].active, row[3]);
               strcpy(playsignB[i].sign, row[4]);
               printf("lol\n");
       	i++;
       	}
       if (i <=4){

       signB(i);
       }else{
    	   signB(5);
       }

      // 	count =i;
          mysql_free_result(res);

          if (mysql_query(conn, "SELECT * FROM Player WHERE Player.sign ='A' Order by score desc ")) {
             fprintf(stderr, "%s\n", mysql_error(conn));
             exit(1);
          }
          i=0;
          res = mysql_store_result(conn);
          while ((row = mysql_fetch_row(res)) != NULL)
                	{

       /*       char key[15];
             char name[65];
             char score[10];
             char active[3];
             char sign[3];   */
                  strcpy(playsignA[i].key, row[0]);
                  strcpy(playsignA[i].name, row[1]);
                  strcpy(playsignA[i].score,row[2]);
                  strcpy(playsignA[i].active, row[3]);
                  strcpy(playsignA[i].sign, row[4]);
                  printf("lol\n");
          	i++;
          	}
          if (i <=4){

              signA(i);
              }else{
           	   signA(5);
              }

         // 	count =i;
             mysql_free_result(res);

             if (mysql_query(conn, "SELECT * FROM Player WHERE Player.sign ='9' Order by score desc ")) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                exit(1);
             }
             i=0;
             res = mysql_store_result(conn);
             while ((row = mysql_fetch_row(res)) != NULL)
                   	{

          /*       char key[15];
                char name[65];
                char score[10];
                char active[3];
                char sign[3];   */
                     strcpy(playsign9[i].key, row[0]);
                     strcpy(playsign9[i].name, row[1]);
                     strcpy(playsign9[i].score,row[2]);
                     strcpy(playsign9[i].active, row[3]);
                     strcpy(playsign9[i].sign, row[4]);
                  	i++;
             	}

             if (i <=4){

                 sign9(i);
                 }else{
              	   sign9(5);
                 }


            // 	count =i;
                mysql_free_result(res);

                if (mysql_query(conn, "SELECT * FROM Player WHERE Player.sign ='8' Order by score desc ")) {
                   fprintf(stderr, "%s\n", mysql_error(conn));
                   exit(1);
                }
                i=0;
                res = mysql_store_result(conn);
                while ((row = mysql_fetch_row(res)) != NULL)
                      	{

             /*       char key[15];
                   char name[65];
                   char score[10];
                   char active[3];
                   char sign[3];   */
                        strcpy(playsign8[i].key, row[0]);
                        strcpy(playsign8[i].name, row[1]);
                        strcpy(playsign8[i].score,row[2]);
                        strcpy(playsign8[i].active, row[3]);
                        strcpy(playsign8[i].sign, row[4]);
                        printf("lol\n");
                	i++;
                	}
                if (i <=4){

                    sign8(i);
                    }else{
                 	   sign8 (5);
                    }


               // 	count =i;
                   mysql_free_result(res);


                   if (mysql_query(conn, "SELECT * FROM Player WHERE Player.sign ='7' Order by score desc ")) {
                      fprintf(stderr, "%s\n", mysql_error(conn));
                      exit(1);
                   }
                   i=0;
                   res = mysql_store_result(conn);
                   while ((row = mysql_fetch_row(res)) != NULL)
                         	{

                /*       char key[15];
                      char name[65];
                      char score[10];
                      char active[3];
                      char sign[3];   */
                           strcpy(playsign7[i].key, row[0]);
                           strcpy(playsign7[i].name, row[1]);
                           strcpy(playsign7[i].score,row[2]);
                           strcpy(playsign7[i].active, row[3]);
                           strcpy(playsign7[i].sign, row[4]);
                           printf("lol\n");
                   	i++;
                   	}
                   if (i <=4){

                       sign7(i);
                       }else{
                    	   sign7(5);
                       }


                  // 	count =i;
                      mysql_free_result(res);


                      if (mysql_query(conn, "SELECT * FROM Player WHERE Player.sign ='6' Order by score desc ")) {
                         fprintf(stderr, "%s\n", mysql_error(conn));
                         exit(1);
                      }
                      i=0;
                      res = mysql_store_result(conn);
                      while ((row = mysql_fetch_row(res)) != NULL)
                            	{

                   /*       char key[15];
                         char name[65];
                         char score[10];
                         char active[3];
                         char sign[3];   */
                              strcpy(playsign6[i].key, row[0]);
                              strcpy(playsign6[i].name, row[1]);
                              strcpy(playsign6[i].score,row[2]);
                              strcpy(playsign6[i].active, row[3]);
                              strcpy(playsign6[i].sign, row[4]);
                              printf("lol\n");
                      	i++;
                      	}
                      if (i <=4){

                          sign6(i);
                          }else{
                       	   sign6(5);
                          }


                     // 	count =i;
                         mysql_free_result(res);

                         if (mysql_query(conn, "SELECT * FROM Player WHERE Player.sign ='5' Order by score desc ")) {
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(1);
                         }
                         i=0;
                         res = mysql_store_result(conn);
                         while ((row = mysql_fetch_row(res)) != NULL)
                               	{

                      /*       char key[15];
                            char name[65];
                            char score[10];
                            char active[3];
                            char sign[3];   */
                                 strcpy(playsign5[i].key, row[0]);
                                 strcpy(playsign5[i].name, row[1]);
                                 strcpy(playsign5[i].score,row[2]);
                                 strcpy(playsign5[i].active, row[3]);
                                 strcpy(playsign5[i].sign, row[4]);

                         	i++;
                         	}
                         if (i <=4){

                             sign5(i);
                             }else{
                          	   sign5(5);
                             }


                        // 	count =i;
                            mysql_free_result(res);


                            if (mysql_query(conn, "SELECT * FROM Player WHERE Player.sign ='4' Order by score desc ")) {
                               fprintf(stderr, "%s\n", mysql_error(conn));
                               exit(1);
                            }
                            i=0;
                            res = mysql_store_result(conn);
                            while ((row = mysql_fetch_row(res)) != NULL)
                                  	{

                         /*       char key[15];
                               char name[65];
                               char score[10];
                               char active[3];
                               char sign[3];   */
                                    strcpy(playsign4[i].key, row[0]);
                                    strcpy(playsign4[i].name, row[1]);
                                    strcpy(playsign4[i].score,row[2]);
                                    strcpy(playsign4[i].active, row[3]);
                                    strcpy(playsign4[i].sign, row[4]);

                            	i++;
                            	}
                            if (i <=4){

                                sign4(i);
                                }else{
                             	   sign4(5);
                                }


                           // 	count =i;
                               mysql_free_result(res);

                               if (mysql_query(conn, "SELECT * FROM Player WHERE Player.sign ='3' Order by score desc ")) {
                                  fprintf(stderr, "%s\n", mysql_error(conn));
                                  exit(1);
                               }
                               i=0;
                               res = mysql_store_result(conn);
                               while ((row = mysql_fetch_row(res)) != NULL)
                                     	{

                            /*       char key[15];
                                  char name[65];
                                  char score[10];
                                  char active[3];
                                  char sign[3];   */
                                       strcpy(playsign3[i].key, row[0]);
                                       strcpy(playsign3[i].name, row[1]);
                                       strcpy(playsign3[i].score,row[2]);
                                       strcpy(playsign3[i].active, row[3]);
                                       strcpy(playsign3[i].sign, row[4]);

                               	i++;
                               	}
                               if (i <=4){

                                   sign3(i);
                                   }else{
                                	   sign3(5);
                                   }


                              // 	count =i;
                                  mysql_free_result(res);
sign2('0');
sign1('0');
   mysql_close(conn);

return 0;
}
int signB(int a){
	//this shall work with a sign
    int temp;
    int i;
	char bufftmp[1024];
	char buff[1024];
	if (strncmp(signpatch[10].mode,"0",1) != 0){
printf("PASSB0");
	if (strncmp(signpatch[10].mode,"1",1) == 0 ){
printf("PASSB1\n");
		sprintf(buff,"AA%c%cb %c%c %c%c",smf,topline,fontmode,largetimesfont,cc,green);
		sprintf(bufftmp,"%s %c",mode1Top,timeLED);
		strcat(buff,bufftmp);
		sprintf(bufftmp,"%c%ca",smf,botline,fontmode,largetimesfont );
		strcat(buff,bufftmp);
		for(i=0; i<a;i++){
			sprintf(bufftmp,"#%d %s %s ",i+1,playsignB[i].name,playsignB[i].score);
			strcat(buff,bufftmp);
		}
		sprintf(bufftmp,"%c",end);
		strcat(buff,bufftmp);
		//printf("%s",buff);
		shoveToSign(5050,'B',buff);
		}else if (strncmp(signpatch[10].mode,"2",1) == 0 ){
			printf("PASSB2\n");
				printf(buff,"AA%c a %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
				printf(bufftmp,"%s ",mode2One);
				strcat(buff,bufftmp);
				for(i=0; i<a;i++){
					sprintf(bufftmp,"#%d %s %s ",i+1,playsignB[i].name,playsignB[i].score);
					strcat(buff,bufftmp);
				}
				sprintf(bufftmp,"%c",end);
				strcat(buff,bufftmp);
				//printf("%s",buff);
				shoveToSign(5050,'B',buff);
			}else if (strncmp(signpatch[10].mode,"3",1) == 0 ){
					printf("PASSB3\n");
					sprintf(buff,"AA%c%c%c %c%c %c%c",smf,topline,mode3Mode,fontmode,largetimesfont,cc,green);
					sprintf(bufftmp,"%s",mode3Top);
					strcat(buff,bufftmp);
					sprintf(bufftmp,"%c%c%c ",smf,botline,mode3Bot);
					strcat(buff,bufftmp);

					for(i=0; i<5;i++){
						sprintf(bufftmp,"#%d %s %s ",i+1,player[i].name,player[i].score);
						strcat(buff,bufftmp);
						}
						sprintf(bufftmp,"%c",end);
						strcat(buff,bufftmp);
						//printf("%s",buff);
						shoveToSign(5050,'B',buff);
					}else if (strncmp(signpatch[10].mode,"4",1) == 0 ){
						printf("PASSB4\n");
						sprintf(buff,"AA%c b %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
						sprintf(bufftmp,"%c",timeLED);
						strcat(buff,bufftmp);
						sprintf(bufftmp,"%c",end);
						strcat(buff,bufftmp);
						//printf("%s",buff);
						shoveToSign(5050,'B',buff);
					}
	}

	return 0;
}
int signA(int a){
	//this shall work with a sign
    int temp;
    int i;
	char bufftmp[1024];
	char buff[1024];
	if (strncmp(signpatch[9].mode,"0",1) != 0){
printf("PASSA0");
	if (strncmp(signpatch[9].mode,"1",1) == 0 ){
printf("PASSA1\n");
		sprintf(buff,"AA%c%cb %c%c %c%c",smf,topline,fontmode,largetimesfont,cc,green);
		sprintf(bufftmp,"%s %c",mode1Top,timeLED);
		strcat(buff,bufftmp);
		sprintf(bufftmp,"%c%ca",smf,botline,fontmode,largetimesfont );
		strcat(buff,bufftmp);
		for(i=0; i<a;i++){
			sprintf(bufftmp,"#%d %s %s ",i+1,playsignA[i].name,playsignA[i].score);
			strcat(buff,bufftmp);
		}
		sprintf(bufftmp,"%c",end);
		strcat(buff,bufftmp);
		//printf("%s",buff);
		shoveToSign(5050,'A',buff);
		}else if (strncmp(signpatch[9].mode,"2",1) == 0 ){
			printf("PASSA2\n");
					sprintf(buff,"AA%c a %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
					sprintf(bufftmp,"%s ",mode2One);
					strcat(buff,bufftmp);
					for(i=0; i<a;i++){
						sprintf(bufftmp,"#%d %s %s ",i+1,playsignA[i].name,playsignA[i].score);
						strcat(buff,bufftmp);
					}
					sprintf(bufftmp,"%c",end);
					strcat(buff,bufftmp);
					//printf("%s",buff);
					shoveToSign(5050,'A',buff);
					}else if (strncmp(signpatch[9].mode,"3",1) == 0 ){
						printf("PASSA3\n");
						sprintf(buff,"AA%c%c%c %c%c %c%c",smf,topline,mode3Mode,fontmode,largetimesfont,cc,green);
							sprintf(bufftmp,"%s",mode3Top);
							strcat(buff,bufftmp);
							sprintf(bufftmp,"%c%c%c ",smf,botline,mode3Bot);
							strcat(buff,bufftmp);
								for(i=0; i<5;i++){
									sprintf(bufftmp,"#%d %s %s ",i+1,player[i].name,player[i].score);
									strcat(buff,bufftmp);
								}
								sprintf(bufftmp,"%c",end);
								strcat(buff,bufftmp);
								//printf("%s",buff);
								shoveToSign(5050,'A',buff);
								}else if (strncmp(signpatch[9].mode,"4",1) == 0 ){
									printf("PASSA4\n");
											sprintf(buff,"AA%c b %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
											sprintf(bufftmp,"%c",timeLED);
											strcat(buff,bufftmp);
											sprintf(bufftmp,"%c",end);
											strcat(buff,bufftmp);
											//printf("%s",buff);
											shoveToSign(5050,'A',buff);
											}
	}

	return 0;
}

int sign9(int a){
	//this shall work with a sign
    int temp;
    int i;
	char bufftmp[1024];
	char buff[1024];
	if (strncmp(signpatch[8].mode,"0",1) != 0){
printf("PASS90");
	if (strncmp(signpatch[8].mode,"1",1) == 0 ){
printf("PASS91\n");
		sprintf(buff,"AA%c%cb %c%c %c%c",smf,topline,fontmode,largetimesfont,cc,green);
		sprintf(bufftmp,"%s %c",mode1Top,timeLED);
		strcat(buff,bufftmp);
		sprintf(bufftmp,"%c%ca",smf,botline,fontmode,largetimesfont );
		strcat(buff,bufftmp);
		for(i=0; i<a;i++){
			sprintf(bufftmp,"#%d %s %s ",i+1,playsign9[i].name,playsign9[i].score);
			strcat(buff,bufftmp);
		}
		sprintf(bufftmp,"%c",end);
		strcat(buff,bufftmp);
		//printf("%s",buff);
		shoveToSign(5050,'9',buff);
		}else if (strncmp(signpatch[8].mode,"2",1) == 0 ){
			printf("PASS92\n");
					sprintf(buff,"AA%c a %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
					sprintf(bufftmp,"%s ",mode2One);
					strcat(buff,bufftmp);
					for(i=0; i<a;i++){
						sprintf(bufftmp,"#%d %s %s ",i+1,playsign9[i].name,playsign9[i].score);
						strcat(buff,bufftmp);
					}
					sprintf(bufftmp,"%c",end);
					strcat(buff,bufftmp);
					//printf("%s",buff);
					shoveToSign(5050,'9',buff);
					}else if (strncmp(signpatch[8].mode,"3",1) == 0 ){
						printf("PASS93\n");
						sprintf(buff,"AA%c%c%c %c%c %c%c",smf,topline,mode3Mode,fontmode,largetimesfont,cc,green);
														sprintf(bufftmp,"%s",mode3Top);
														strcat(buff,bufftmp);
														sprintf(bufftmp,"%c%c%c ",smf,botline,mode3Bot);
														strcat(buff,bufftmp);
							for(i=0; i<5;i++){
									sprintf(bufftmp,"#%d %s %s ",i+1,player[i].name,player[i].score);
									strcat(buff,bufftmp);
								}
								sprintf(bufftmp,"%c",end);
								strcat(buff,bufftmp);
								//printf("%s",buff);
								shoveToSign(5050,'9',buff);
								}else if (strncmp(signpatch[8].mode,"4",1) == 0 ){
									printf("PASS94\n");
											sprintf(buff,"AA%c b %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
											sprintf(bufftmp,"%c",timeLED);
											strcat(buff,bufftmp);
											sprintf(bufftmp,"%c",end);
											strcat(buff,bufftmp);
											//printf("%s",buff);
											shoveToSign(5050,'9',buff);
											}
	}

	return 0;
}
int sign8(int a){
	//this shall work with a sign
    int temp;
    int i;
	char bufftmp[1024];
	char buff[1024];
	if (strncmp(signpatch[7].mode,"0",1) != 0){
printf("PASS80");
	if (strncmp(signpatch[7].mode,"1",1) == 0 ){
printf("PASS81\n");
		sprintf(buff,"AA%c%cb %c%c %c%c",smf,topline,fontmode,largetimesfont,cc,green);
		sprintf(bufftmp,"%s %c",mode1Top,timeLED);
		strcat(buff,bufftmp);
		sprintf(bufftmp,"%c%ca",smf,botline,fontmode,largetimesfont );
		strcat(buff,bufftmp);
		for(i=0; i<a;i++){
			sprintf(bufftmp,"#%d %s %s ",i+1,playsign8[i].name,playsign8[i].score);
			strcat(buff,bufftmp);
		}
		sprintf(bufftmp,"%c",end);
		strcat(buff,bufftmp);
		//printf("%s",buff);
		shoveToSign(5050,'8',buff);
		}else if (strncmp(signpatch[7].mode,"2",1) == 0 ){
			printf("PASS82\n");
					sprintf(buff,"AA%c a %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
					sprintf(bufftmp,"%s ",mode2One);
					strcat(buff,bufftmp);
					for(i=0; i<a;i++){
						sprintf(bufftmp,"#%d %s %s ",i+1,playsign8[i].name,playsign8[i].score);
						strcat(buff,bufftmp);
					}
					sprintf(bufftmp,"%c",end);
					strcat(buff,bufftmp);
					//printf("%s",buff);
					shoveToSign(5050,'8',buff);
					}else if (strncmp(signpatch[7].mode,"3",1) == 0 ){
						printf("PASS83\n");
						sprintf(buff,"AA%c%c%c %c%c %c%c",smf,topline,mode3Mode,fontmode,largetimesfont,cc,green);
														sprintf(bufftmp,"%s",mode3Top);
														strcat(buff,bufftmp);
														sprintf(bufftmp,"%c%c%c ",smf,botline,mode3Bot);
														strcat(buff,bufftmp);
						for(i=0; i<5;i++){
									sprintf(bufftmp,"#%d %s %s ",i+1,player[i].name,player[i].score);
									strcat(buff,bufftmp);
								}
								sprintf(bufftmp,"%c",end);
								strcat(buff,bufftmp);
								//printf("%s",buff);
								shoveToSign(5050,'8',buff);
								}else if (strncmp(signpatch[7].mode,"4",1) == 0 ){
									printf("PASS84\n");
											sprintf(buff,"AA%c b %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
											sprintf(bufftmp,"%c",timeLED);
											strcat(buff,bufftmp);
											sprintf(bufftmp,"%c",end);
											strcat(buff,bufftmp);
											//printf("%s",buff);
											shoveToSign(5050,'8',buff);
											}
	}

	return 0;
}

int sign7(int a){
	//this shall work with a sign
    int temp;
    int i;
	char bufftmp[1024];
	char buff[1024];
	if (strncmp(signpatch[6].mode,"0",1) != 0){
printf("PASS70");
	if (strncmp(signpatch[6].mode,"1",1) == 0 ){
printf("PASS71\n");
		sprintf(buff,"AA%c%cb %c%c %c%c",smf,topline,fontmode,largetimesfont,cc,green);
		sprintf(bufftmp,"%s %c",mode1Top,timeLED);
		strcat(buff,bufftmp);
		sprintf(bufftmp,"%c%ca",smf,botline,fontmode,largetimesfont );
		strcat(buff,bufftmp);
		for(i=0; i<a;i++){
			sprintf(bufftmp,"#%d %s %s ",i+1,playsign7[i].name,playsign7[i].score);
			strcat(buff,bufftmp);
		}
		sprintf(bufftmp,"%c",end);
		strcat(buff,bufftmp);
		//printf("%s",buff);
		shoveToSign(5050,'7',buff);
		}else if (strncmp(signpatch[6].mode,"2",1) == 0 ){
			printf("PASS72\n");
					sprintf(buff,"AA%c a %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
					sprintf(bufftmp,"%s ",mode2One);
					strcat(buff,bufftmp);
					for(i=0; i<a;i++){
						sprintf(bufftmp,"#%d %s %s ",i+1,playsign7[i].name,playsign7[i].score);
						strcat(buff,bufftmp);
					}
					sprintf(bufftmp,"%c",end);
					strcat(buff,bufftmp);
					//printf("%s",buff);
					shoveToSign(5050,'7',buff);
					}else if (strncmp(signpatch[6].mode,"3",1) == 0 ){
						printf("PASS73\n");
						sprintf(buff,"AA%c%c%c %c%c %c%c",smf,topline,mode3Mode,fontmode,largetimesfont,cc,green);
														sprintf(bufftmp,"%s",mode3Top);
														strcat(buff,bufftmp);
														sprintf(bufftmp,"%c%c%c ",smf,botline,mode3Bot);
														strcat(buff,bufftmp);
						for(i=0; i<5;i++){
									sprintf(bufftmp,"#%d %s %s ",i+1,player[i].name,player[i].score);
									strcat(buff,bufftmp);
								}
								sprintf(bufftmp,"%c",end);
								strcat(buff,bufftmp);
								//printf("%s",buff);
								shoveToSign(5050,'7',buff);
								}else if (strncmp(signpatch[6].mode,"4",1) == 0 ){
									printf("PASS74\n");
											sprintf(buff,"AA%c b %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
											sprintf(bufftmp,"%c",timeLED);
											strcat(buff,bufftmp);
											sprintf(bufftmp,"%c",end);
											strcat(buff,bufftmp);
											//printf("%s",buff);
											shoveToSign(5050,'7',buff);
											}
	}

	return 0;
}

int sign6(int a){
	//this shall work with a sign
    int temp;
    int i;
	char bufftmp[1024];
	char buff[1024];
	if (strncmp(signpatch[5].mode,"0",1) != 0){
printf("PASS60");
	if (strncmp(signpatch[5].mode,"1",1) == 0 ){
printf("PASS61\n");
		sprintf(buff,"AA%c%cb %c%c %c%c",smf,topline,fontmode,largetimesfont,cc,green);
		sprintf(bufftmp,"%s %c",mode1Top,timeLED);
		strcat(buff,bufftmp);
		sprintf(bufftmp,"%c%ca",smf,botline,fontmode,largetimesfont );
		strcat(buff,bufftmp);
		for(i=0; i<a;i++){
			sprintf(bufftmp,"#%d %s %s ",i+1,playsign6[i].name,playsign6[i].score);
			strcat(buff,bufftmp);
		}
		sprintf(bufftmp,"%c",end);
		strcat(buff,bufftmp);
		//printf("%s",buff);
		shoveToSign(5050,'6',buff);
		}else if (strncmp(signpatch[5].mode,"2",1) == 0 ){
			printf("PASS62\n");
					sprintf(buff,"AA%c a %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
					sprintf(bufftmp,"%s ",mode2One);
					strcat(buff,bufftmp);
					for(i=0; i<a;i++){
						sprintf(bufftmp,"#%d %s %s ",i+1,playsign6[i].name,playsign6[i].score);
						strcat(buff,bufftmp);
					}
					sprintf(bufftmp,"%c",end);
					strcat(buff,bufftmp);
					//printf("%s",buff);
					shoveToSign(5050,'6',buff);
					}else if (strncmp(signpatch[5].mode,"3",1) == 0 ){
						printf("PASS63\n");
						sprintf(buff,"AA%c%c%c %c%c %c%c",smf,topline,mode3Mode,fontmode,largetimesfont,cc,green);
														sprintf(bufftmp,"%s",mode3Top);
														strcat(buff,bufftmp);
														sprintf(bufftmp,"%c%c%c ",smf,botline,mode3Bot);
														strcat(buff,bufftmp);
						for(i=0; i<5;i++){
									sprintf(bufftmp,"#%d %s %s ",i+1,player[i].name,player[i].score);
									strcat(buff,bufftmp);
								}
								sprintf(bufftmp,"%c",end);
								strcat(buff,bufftmp);
								//printf("%s",buff);
								shoveToSign(5050,'6',buff);
								}else if (strncmp(signpatch[5].mode,"4",1) == 0 ){
									printf("PASS64\n");
											sprintf(buff,"AA%c b %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
											sprintf(bufftmp,"%c",timeLED);
											strcat(buff,bufftmp);
											sprintf(bufftmp,"%c",end);
											strcat(buff,bufftmp);
											//printf("%s",buff);
											shoveToSign(5050,'6',buff);
											}
	}

	return 0;
}
int sign5(int a){
	//this shall work with a sign
    int temp;
    int i;
	char bufftmp[1024];
	char buff[1024];
	if (strncmp(signpatch[4].mode,"0",1) != 0){
printf("PASS50");
	if (strncmp(signpatch[4].mode,"1",1) == 0 ){
printf("PASS51\n");
		sprintf(buff,"AA%c%cb %c%c %c%c",smf,topline,fontmode,largetimesfont,cc,green);
		sprintf(bufftmp,"%s %c",mode1Top,timeLED);
		strcat(buff,bufftmp);
		sprintf(bufftmp,"%c%ca",smf,botline,fontmode,largetimesfont );
		strcat(buff,bufftmp);
		for(i=0; i<a;i++){
			sprintf(bufftmp,"#%d %s %s ",i+1,playsign5[i].name,playsign5[i].score);
			strcat(buff,bufftmp);
		}
		sprintf(bufftmp,"%c",end);
		strcat(buff,bufftmp);
		//printf("%s",buff);
		shoveToSign(5050,'5',buff);
		}else if (strncmp(signpatch[4].mode,"2",1) == 0 ){
			printf("PASS52\n");
					sprintf(buff,"AA%c a %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
					sprintf(bufftmp,"%s ",mode2One);
					strcat(buff,bufftmp);
					for(i=0; i<a;i++){
						sprintf(bufftmp,"#%d %s %s ",i+1,playsign5[i].name,playsign5[i].score);
						strcat(buff,bufftmp);
					}
					sprintf(bufftmp,"%c",end);
					strcat(buff,bufftmp);
					//printf("%s",buff);
					shoveToSign(5050,'5',buff);
					}else if (strncmp(signpatch[4].mode,"3",1) == 0 ){
						printf("PASS53\n");
						sprintf(buff,"AA%c%c%c %c%c %c%c",smf,topline,mode3Mode,fontmode,largetimesfont,cc,green);
														sprintf(bufftmp,"%s",mode3Top);
														strcat(buff,bufftmp);
														sprintf(bufftmp,"%c%c%c ",smf,botline,mode3Bot);
														strcat(buff,bufftmp);
						for(i=0; i<5;i++){
									sprintf(bufftmp,"#%d %s %s ",i+1,player[i].name,player[i].score);
									strcat(buff,bufftmp);
								}
								sprintf(bufftmp,"%c",end);
								strcat(buff,bufftmp);
								//printf("%s",buff);
								shoveToSign(5050,'5',buff);
								}else if (strncmp(signpatch[4].mode,"4",1) == 0 ){
									printf("PASS54\n");
											sprintf(buff,"AA%c b %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
											sprintf(bufftmp,"%c",timeLED);
											strcat(buff,bufftmp);
											sprintf(bufftmp,"%c",end);
											strcat(buff,bufftmp);
											//printf("%s",buff);
											shoveToSign(5050,'5',buff);
											}
	}

	return 0;
}
int sign4(int a){
	//this shall work with a sign
    int temp;
    int i;
	char bufftmp[1024];
	char buff[1024];
	if (strncmp(signpatch[3].mode,"0",1) != 0){
printf("PASS50");
	if (strncmp(signpatch[3].mode,"1",1) == 0 ){
printf("PASS41\n");
		sprintf(buff,"AA%c%cb %c%c %c%c",smf,topline,fontmode,largetimesfont,cc,green);
		sprintf(bufftmp,"%s %c",mode1Top,timeLED);
		strcat(buff,bufftmp);
		sprintf(bufftmp,"%c%ca",smf,botline,fontmode,largetimesfont );
		strcat(buff,bufftmp);
		for(i=0; i<a;i++){
			sprintf(bufftmp,"#%d %s %s ",i+1,playsign4[i].name,playsign4[i].score);
			strcat(buff,bufftmp);
		}
		sprintf(bufftmp,"%c",end);
		strcat(buff,bufftmp);
		//printf("%s",buff);
		shoveToSign(5050,'4',buff);
		}else if (strncmp(signpatch[3].mode,"2",1) == 0 ){
			printf("PASS42\n");
					sprintf(buff,"AA%c a %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
					sprintf(bufftmp,"%s ",mode2One);
					strcat(buff,bufftmp);
					for(i=0; i<a;i++){
						sprintf(bufftmp,"#%d %s %s ",i+1,playsign4[i].name,playsign4[i].score);
						strcat(buff,bufftmp);
					}
					sprintf(bufftmp,"%c",end);
					strcat(buff,bufftmp);
					//printf("%s",buff);
					shoveToSign(5050,'4',buff);
					}else if (strncmp(signpatch[3].mode,"3",1) == 0 ){
						printf("PASS43\n");
						sprintf(buff,"AA%c%c%c %c%c %c%c",smf,topline,mode3Mode,fontmode,largetimesfont,cc,green);
														sprintf(bufftmp,"%s",mode3Top);
														strcat(buff,bufftmp);
														sprintf(bufftmp,"%c%c%c ",smf,botline,mode3Bot);
														strcat(buff,bufftmp);
						for(i=0; i<5;i++){
									sprintf(bufftmp,"#%d %s %s ",i+1,player[i].name,player[i].score);
									strcat(buff,bufftmp);
								}
								sprintf(bufftmp,"%c",end);
								strcat(buff,bufftmp);
								//printf("%s",buff);
								shoveToSign(5050,'4',buff);
								}else if (strncmp(signpatch[3].mode,"4",1) == 0 ){
									printf("PASS44\n");
											sprintf(buff,"AA%c b %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
											sprintf(bufftmp,"%c",timeLED);
											strcat(buff,bufftmp);
											sprintf(bufftmp,"%c",end);
											strcat(buff,bufftmp);
											//printf("%s",buff);
											shoveToSign(5050,'4',buff);
											}
	}

	return 0;
}
int sign3(int a){
	//this shall work with a sign
    int temp;
    int i;
	char bufftmp[1024];
	char buff[1024];
	if (strncmp(signpatch[2].mode,"0",1) != 0){
printf("PASS30");
	if (strncmp(signpatch[2].mode,"1",1) == 0 ){
printf("PASS31\n");
		sprintf(buff,"AA%c%cb %c%c %c%c",smf,topline,fontmode,largetimesfont,cc,green);
		sprintf(bufftmp,"%s %c",mode1Top,timeLED);
		strcat(buff,bufftmp);
		sprintf(bufftmp,"%c%ca",smf,botline,fontmode,largetimesfont );
		strcat(buff,bufftmp);
		for(i=0; i<a;i++){
			sprintf(bufftmp,"#%d %s %s ",i+1,playsign3[i].name,playsign3[i].score);
			strcat(buff,bufftmp);
		}
		sprintf(bufftmp,"%c",end);
		strcat(buff,bufftmp);
		//printf("%s",buff);
		shoveToSign(5050,'3',buff);
		}else if (strncmp(signpatch[2].mode,"2",1) == 0 ){
			printf("PASS32\n");
					sprintf(buff,"AA%c a %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
					sprintf(bufftmp,"%s ",mode2One);
					strcat(buff,bufftmp);
					for(i=0; i<a;i++){
						sprintf(bufftmp,"#%d %s %s ",i+1,playsign3[i].name,playsign3[i].score);
						strcat(buff,bufftmp);
					}
					sprintf(bufftmp,"%c",end);
					strcat(buff,bufftmp);
					//printf("%s",buff);
					shoveToSign(5050,'3',buff);
					}else if (strncmp(signpatch[2].mode,"3",1) == 0 ){
						printf("PASS33\n");
						sprintf(buff,"AA%c%c%c %c%c %c%c",smf,topline,mode3Mode,fontmode,largetimesfont,cc,green);
														sprintf(bufftmp,"%s",mode3Top);
														strcat(buff,bufftmp);
														sprintf(bufftmp,"%c%c%c ",smf,botline,mode3Bot);
														strcat(buff,bufftmp);
														for(i=0; i<5;i++){
									sprintf(bufftmp,"#%d %s %s ",i+1,player[i].name,player[i].score);
									strcat(buff,bufftmp);
								}
								sprintf(bufftmp,"%c",end);
								strcat(buff,bufftmp);
								//printf("%s",buff);
								shoveToSign(5050,'3',buff);
								}else if (strncmp(signpatch[2].mode,"4",1) == 0 ){
									printf("PASS34\n");
											sprintf(buff,"AA%c b %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
											sprintf(bufftmp,"%c",timeLED);
											strcat(buff,bufftmp);
											sprintf(bufftmp,"%c",end);
											strcat(buff,bufftmp);
											//printf("%s",buff);
											shoveToSign(5050,'3',buff);
											}
	}

	return 0;
}
int sign2(int a){
	//this shall work with a sign
    int temp;
    int i;
	char bufftmp[1024];
	char buff[1024];
	if (strncmp(signpatch[1].mode,"0",1) != 0){
printf("PASS20");
	if (strncmp(signpatch[1].mode,"1",1) == 0 ){
printf("PASS21\n");
		sprintf(buff,"AA%c%cb %c%c %c%c",smf,topline,fontmode,largetimesfont,cc,green);
		sprintf(bufftmp,"%s %c",mode1Top,timeLED);
		strcat(buff,bufftmp);
		sprintf(bufftmp,"%c%ca",smf,botline,fontmode,largetimesfont );
		strcat(buff,bufftmp);
	/*	for(i=0; i<a;i++){
			sprintf(bufftmp,"#%d %s %s ",i+1,playsign3[i].name,playsign3[i].score);
			strcat(buff,bufftmp);
		} */
		sprintf(bufftmp,"%c",end);
		strcat(buff,bufftmp);
		//printf("%s",buff);
		shoveToSign(5050,'2',buff);
		}else if (strncmp(signpatch[1].mode,"2",1) == 0 ){
			printf("PASS22\n");
					sprintf(buff,"AA%c a %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
					sprintf(bufftmp,"%s ",mode2One);
					strcat(buff,bufftmp);
			/*		for(i=0; i<a;i++){
						sprintf(bufftmp,"#%d %s %s ",i+1,playsign3[i].name,playsign3[i].score);
						strcat(buff,bufftmp);
					} */
					sprintf(bufftmp,"%c",end);
					strcat(buff,bufftmp);
					//printf("%s",buff);
					shoveToSign(5050,'2',buff);
					}else if (strncmp(signpatch[1].mode,"3",1) == 0 ){
						printf("PASS23\n");
						sprintf(buff,"AA%c%c%c %c%c %c%c",smf,topline,mode3Mode,fontmode,largetimesfont,cc,green);
														sprintf(bufftmp,"%s",mode3Top);
														strcat(buff,bufftmp);
														sprintf(bufftmp,"%c%c%c ",smf,botline,mode3Bot);
														strcat(buff,bufftmp);
						for(i=0; i<5;i++){
									sprintf(bufftmp,"#%d %s %s ",i+1,player[i].name,player[i].score);
									strcat(buff,bufftmp);
								}
								sprintf(bufftmp,"%c",end);
								strcat(buff,bufftmp);
								//printf("%s",buff);
								shoveToSign(5050,'2',buff);
								}else if (strncmp(signpatch[1].mode,"4",1) == 0 ){
									printf("PASS24\n");
											sprintf(buff,"AA%c b %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
											sprintf(bufftmp,"%c",timeLED);
											strcat(buff,bufftmp);
											sprintf(bufftmp,"%c",end);
											strcat(buff,bufftmp);
											//printf("%s",buff);
											shoveToSign(5050,'2',buff);
											}
	}

	return 0;
}
int sign1(int a){
	//this shall work with a sign
    int temp;
    int i;
	char bufftmp[1024];
	char buff[1024];
	if (strncmp(signpatch[0].mode,"0",1) != 0){
printf("PASS10");
	if (strncmp(signpatch[0].mode,"1",1) == 0 ){
printf("PASS11\n");
		sprintf(buff,"AA%c%cb %c%c %c%c",smf,topline,fontmode,largetimesfont,cc,green);
		sprintf(bufftmp,"%s %c",mode1Top,timeLED);
		strcat(buff,bufftmp);
		sprintf(bufftmp,"%c%ca",smf,botline,fontmode,largetimesfont );
		strcat(buff,bufftmp);
	/*	for(i=0; i<a;i++){
			sprintf(bufftmp,"#%d %s %s ",i+1,playsign3[i].name,playsign3[i].score);
			strcat(buff,bufftmp);
		} */
		sprintf(bufftmp,"%c",end);
		strcat(buff,bufftmp);
		//printf("%s",buff);
		shoveToSign(5050,'1',buff);
		}else if (strncmp(signpatch[0].mode,"2",1) == 0 ){
			printf("PASS12\n");
					sprintf(buff,"AA%c a %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
					sprintf(bufftmp,"%s ",mode2One);
					strcat(buff,bufftmp);
			/*		for(i=0; i<a;i++){
						sprintf(bufftmp,"#%d %s %s ",i+1,playsign3[i].name,playsign3[i].score);
						strcat(buff,bufftmp);
					} */
					sprintf(bufftmp,"%c",end);
					strcat(buff,bufftmp);
					//printf("%s",buff);
					shoveToSign(5050,'2',buff);
					}else if (strncmp(signpatch[0].mode,"3",1) == 0 ){
						printf("PASS13\n");
						sprintf(buff,"AA%c%c%c %c%c %c%c",smf,topline,mode3Mode,fontmode,largetimesfont,cc,green);
														sprintf(bufftmp,"%s",mode3Top);
														strcat(buff,bufftmp);
														sprintf(bufftmp,"%c%c%c ",smf,botline,mode3Bot);
														strcat(buff,bufftmp);
						for(i=0; i<5;i++){
									sprintf(bufftmp,"#%d %s %s ",i+1,player[i].name,player[i].score);
									strcat(buff,bufftmp);
								}
								sprintf(bufftmp,"%c",end);
								strcat(buff,bufftmp);
								//printf("%s",buff);
								shoveToSign(5050,'1',buff);
								}else if (strncmp(signpatch[0].mode,"4",1) == 0 ){
									printf("PASS14\n");
											sprintf(buff,"AA%c b %c%c %c%c",smf,fontmode,largetimesfont,cc,green);
											sprintf(bufftmp,"%c",timeLED);
											strcat(buff,bufftmp);
											sprintf(bufftmp,"%c",end);
											strcat(buff,bufftmp);
											//printf("%s",buff);
											shoveToSign(5050,'1',buff);
											}
	}

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
		    server = gethostbyname("127.0.0.1");

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
printf("%s \n",buffer);
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
	   usleep(2500);
	    return 0;

	}

