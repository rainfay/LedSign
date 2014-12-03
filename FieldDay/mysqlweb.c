#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mysql.h>
#include <unistd.h>
/* build ins
 gcc -o mysqlweb  $(mysql_config --cflags) mysqlweb.c $(mysql_config --libs)

*/

/*
 *This program shall get data from the mysqldatabase and output it to the 
 *Html  
 
 
 */
struct contact
   {
      char id[30];
      char call[30];
      char type[30];
      char location[30];
      char date[35];
      char time[35];
      char  band[30];
      char mode[50];
      char op[25];
   };
int main( int argc, char *argv[])
{
 time_t now;
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;
   struct contact list[5];
   char *server = "127.0.0.1";
   char *user = "ham";
   char *password = "K5SLD"; /* set me first */
   char *database = "FD";
FILE *output;
int i = 0;
int count = 0;
int lines ;
char c;
char buff[512] ; // output to the sign
char bufftmp[100]; // local concat
int numberOfRows;

		 
output = fopen("/home/kd5lct/hamradio/hamoutput.htm" , "w");
fprintf(output,"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" ");
fprintf(output,"\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n");
fprintf(output,"<html xmlns=\"http://www.w3.org/1999/xhtml\">\n");
fprintf(output,"<head>\n");
fprintf(output,"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n");
fprintf(output,"<META HTTP-EQUIV=\"REFRESH\" CONTENT=\"65\">");
fprintf(output,"<META HTTP-EQUIV=\"PRAGMA\" CONTENT=\"NO-CACHE\">");
fprintf(output,"<title>K5SLD Field Day Stats TESTING DATA NOT REAL!!!!</title>");
fprintf(output, "<link href=\"css/oneColFixCtrHdr.css\" rel=\"stylesheet\" type=\"text/css\" />\n");
fprintf(output,"</head>\n");

fprintf(output,"<body>\n"
"<div class=\"container\">\n"
"<div class=\"header\"><a href=\"http://www.k5sld.com\"><img src=\"images/header.jpg\" alt=\"Radio\" name=\"Radio\" width=\"180\" height=\"90\" id=\"Radio\" style=\"background: #C6D580; display:block; background-color: #00FFFF;\" />\n"
  "</a> <a href=\"/hamoutput.htm\">Stats</a> <BR />\n"
  "<!-- end .header --></div>\n"
  "<div class=\"content\">\n");
fprintf(output,"<h1>Welcome to K5SLD Field day statsi<br> TEST DATA NOT REAL!!!!!,</h1>\n"
    "<p>This page will display the last five stations worked for each station and auto refresh every 65 seconds.</p>\n"
    "<p>cw</p>\n"
      "<p>");

   conn = mysql_init(NULL);
   if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }

i =0;//					0	1	2	3		4		   5	6 	7
   if (mysql_query(conn, "select fldPrimaryKey,fldCall,fldClass, fldState, fldDateStr, fldTransmitterID, fldBand, FldMode  from tblContacts where FldBand>=10 AND FldMode ='CW' order by fldPrimaryKey DESC LIMIT 0,5")) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }

   res = mysql_use_result(conn);

while ((row = mysql_fetch_row(res)) != NULL)
      	{


        strcpy(list[i].id, " "); //number NOT USED
        strcpy(list[i].call, row[1]); // Call Sign
        strcpy(list[i].type, row[2]); // Type of station (3A)
        strcpy(list[i].location, row[3]); // Section Section
        strcpy(list[i].date, row[4]); //Date string
        strcpy(list[i].time, row[5]); //Time string
        strcpy(list[i].band, row[6]); // Band
        strcpy(list[i].mode, row[7]); // Mode
        strcpy(list[i].op, " ");

	i++;
	}
	count =i;
   mysql_free_result(res);    
	fprintf(output,"<table width=\"400\" border=\"1\">");
        fprintf(output, "<tr><td>");
        fprintf(output, "Call");
        fprintf(output,"</td><td>");
        fprintf(output,"Class");
       fprintf(output, "</td><td>");
        fprintf(output, "Section");
	    fprintf(output,"</td><td>");
        fprintf(output, "Date");
		fprintf(output,"</td><td>");
        fprintf(output, "Time");

        fprintf(output,"</td><td>");
        fprintf(output, "Band");
        fprintf(output, "</td><td>");
        fprintf(output,"Mode");
		fprintf(output,"</td></tr>\n");
for(i =0 ; i < count ; i++)
{
        // Print out the contents of each row into a table
        fprintf(output,"<tr><td>");
        fprintf(output,"%s ",list[i].call);
        fprintf(output,"</td><td>");
        fprintf(output,"%s ",list[i].type);
        fprintf(output,"</td><td>");
fprintf(output,"%s",list[i].location);        
        fprintf(output,"</td><td>");

        fprintf(output, "%s ",list[i].date);
        fprintf(output,"</td><td>");
        fprintf(output,"%sUTC",list[i].time);
        fprintf(output,"</td><td>");
        fprintf(output,"%s ",list[i].band);

        fprintf(output,"</td><td>");
        fprintf(output,"%s ",list[i].mode);
		fprintf(output,"</td></tr>\n");
		}
                fprintf(output," </table> </p>");


i =0;
   if (mysql_query(conn, "select fldPrimaryKey,fldCall,fldClass, fldState, fldDateStr, fldTransmitterID, fldBand, FldMode  from tblContacts where FldBand>=10 AND FldMode ='DIG' order by fldPrimaryKey DESC LIMIT 0,5")) {

      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }

   res = mysql_use_result(conn);

while ((row = mysql_fetch_row(res)) != NULL)
      	{


    strcpy(list[i].id, " "); //number NOT USED
    strcpy(list[i].call, row[1]); // Call Sign
    strcpy(list[i].type, row[2]); // Type of station (3A)
    strcpy(list[i].location, row[3]); // Section Section
    strcpy(list[i].date, row[4]); //Date string
    strcpy(list[i].time, row[5]); //Time string
    strcpy(list[i].band, row[6]); // Band
    strcpy(list[i].mode, row[7]); // Mode
    strcpy(list[i].op, " ");


	i++;
	}
count = i;
   mysql_free_result(res);
   fprintf(output,"<p>digi</p>\n"
      "<p>\n");
        fprintf(output,"<table width=\"400\" border=\"1\">");
        fprintf(output, "<tr><td>");;
        fprintf(output, "Call");
        fprintf(output,"</td><td>");
        fprintf(output,"Class");
       fprintf(output, "</td><td>");
        fprintf(output, "Section");
	    fprintf(output,"</td><td>");
        fprintf(output, "Date");
		fprintf(output,"</td><td>");
        fprintf(output, "Time");

        fprintf(output,"</td><td>");
        fprintf(output, "Band");
        fprintf(output, "</td><td>");
        fprintf(output,"Mode");
		fprintf(output,"</td></tr>\n");
for(i =0 ; i < count ; i++)
{
        // Print out the contents of each row into a table
        fprintf(output,"<tr><td>");
       fprintf(output,"%s ",list[i].call);
        fprintf(output,"</td><td>");
        fprintf(output,"%s ",list[i].type);
        fprintf(output,"</td><td>");
fprintf(output,"%s",list[i].location);        
        fprintf(output,"</td><td>");

        fprintf(output, "%s ",list[i].date);
        fprintf(output,"</td><td>");
        fprintf(output,"%sUTC",list[i].time);
        fprintf(output,"</td><td>");
        fprintf(output,"%s ",list[i].band);

        fprintf(output,"</td><td>");
        fprintf(output,"%s ",list[i].mode);
		fprintf(output,"</td></tr>\n");
		}
fprintf(output,"</table>  </p>");

i =0;
   if (mysql_query(conn, "select fldPrimaryKey,fldCall,fldClass, fldState, fldDateStr, fldTransmitterID, fldBand, FldMode  from tblContacts where FldBand>=10 AND FldMode ='PH' order by fldPrimaryKey DESC LIMIT 0,5")) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }

   res = mysql_use_result(conn);

while ((row = mysql_fetch_row(res)) != NULL)
      	{

    strcpy(list[i].id, " "); //number NOT USED
    strcpy(list[i].call, row[1]); // Call Sign
    strcpy(list[i].type, row[2]); // Type of station (3A)
    strcpy(list[i].location, row[3]); // Section Section
    strcpy(list[i].date, row[4]); //Date string
    strcpy(list[i].time, row[5]); //Time string
    strcpy(list[i].band, row[6]); // Band
    strcpy(list[i].mode, row[7]); // Mode
    strcpy(list[i].op, " ");


	i++;
	}
count = i;
   mysql_free_result(res);
   fprintf(output,"<p>phone</p>\n"
      "<p>\n");
        fprintf(output,"<table width=\"400\" border=\"1\">");
        fprintf(output, "<tr><td>");
        fprintf(output, "Call");
        fprintf(output,"</td><td>");
        fprintf(output,"Class");
       fprintf(output, "</td><td>");
        fprintf(output, "Section");
	    fprintf(output,"</td><td>");
        fprintf(output, "Date");
		fprintf(output,"</td><td>");
        fprintf(output, "Time");

        fprintf(output,"</td><td>");
        fprintf(output, "Band");
        fprintf(output, "</td><td>");
        fprintf(output,"Mode");
		fprintf(output,"</td></tr>\n");
for(i =0 ; i < count ; i++)
{
        // Print out the contents of each row into a table
        fprintf(output,"<tr><td>");
       fprintf(output,"%s ",list[i].call);
        fprintf(output,"</td><td>");
        fprintf(output,"%s ",list[i].type);
        fprintf(output,"</td><td>");
fprintf(output,"%s",list[i].location);        
        fprintf(output,"</td><td>");

        fprintf(output, "%s ",list[i].date);
        fprintf(output,"</td><td>");
        fprintf(output,"%sUTC",list[i].time);
        fprintf(output,"</td><td>");
        fprintf(output,"%s ",list[i].band);

        fprintf(output,"</td><td>");
        fprintf(output,"%s ",list[i].mode);
		fprintf(output,"</td></tr>\n");
		}
                fprintf(output, "</table>  </p>");
                i =0;
   if (mysql_query(conn, "select fldPrimaryKey,fldCall,fldClass, fldState, fldDateStr, fldTransmitterID, fldBand, FldMode  from tblContacts where FldBand<10 order by fldPrimaryKey DESC LIMIT 0,5")) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }

   res = mysql_use_result(conn);

while ((row = mysql_fetch_row(res)) != NULL)
      	{



    strcpy(list[i].id, " "); //number NOT USED
    strcpy(list[i].call, row[1]); // Call Sign
    strcpy(list[i].type, row[2]); // Type of station (3A)
    strcpy(list[i].location, row[3]); // Section Section
    strcpy(list[i].date, row[4]); //Date string
    strcpy(list[i].time, row[5]); //Time string
    strcpy(list[i].band, row[6]); // Band
    strcpy(list[i].mode, row[7]); // Mode
    strcpy(list[i].op, " ");
	i++;
	}
count = i;
   mysql_free_result(res);
   fprintf(output,"<p>VHF</p>\n"
      "<p>\n");
        fprintf(output,"<table width=\"400\" border=\"1\">");
        fprintf(output, "<tr><td>");
        fprintf(output, "Call");
        fprintf(output,"</td><td>");
        fprintf(output,"Class");
       fprintf(output, "</td><td>");
        fprintf(output, "Section");
	    fprintf(output,"</td><td>");
        fprintf(output, "Date");
		fprintf(output,"</td><td>");
        fprintf(output, "Time");

        fprintf(output,"</td><td>");
        fprintf(output, "Band");
        fprintf(output, "</td><td>");
        fprintf(output,"Mode");
		fprintf(output,"</td></tr>\n");
for(i =0 ; i < count ; i++)
{
        // Print out the contents of each row into a table
        fprintf(output,"<tr><td>");
       fprintf(output,"%s ",list[i].call);
        fprintf(output,"</td><td>");
        fprintf(output,"%s ",list[i].type);
        fprintf(output,"</td><td>");
fprintf(output,"%s",list[i].location);        
        fprintf(output,"</td><td>");

        fprintf(output, "%s ",list[i].date);
        fprintf(output,"</td><td>");
        fprintf(output,"%sUTC",list[i].time);
        fprintf(output,"</td><td>");
        fprintf(output,"%s ",list[i].band);

        fprintf(output,"</td><td>");
        fprintf(output,"%s ",list[i].mode);
		fprintf(output,"</td></tr>\n");
		}
                fprintf(output,"</table>  </p>");
                i =0;

time(&now);
	fprintf(output,"<br>time generated, %s <br>",ctime(&now));
	fprintf(output,"<p>View of the Field Day</p>"
"<p><img src=\"out.jpg\" width=\"640\" height=\"480\" alt=\"A webcam\" longdesc=\"A webcam at Field day site\" /><br>"
"</p>");
fprintf(output," </div>\n"
  "<div class=\"footer\">\n"
    "<p>^.^</p>\n"
   " <!-- end .footer --></div>"
 " <!-- end .container --></div>"
"\n</body>\n"
"</html>");
   mysql_close(conn);
fclose(output);
return 0;
}

