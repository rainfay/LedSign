//Jason Archip
//endofnet.com
//OLD CODE USE SIGNFP.h
#ifndef __SIGN_H__
#define __SIGN_H__

//shared variables start
extern char null;
extern char soh;
extern char stx;
extern char smf; // start of mode field
extern char pic; //call a dots file
extern char cc; //collor code
extern char green; //green color
extern char amb;
extern char red;
extern char time; // print time
extern char datemode;//use datemode  and datemmddyy or datetext to display date.
extern char date;
extern char datemmddyy;
extern char datedashmmddyy;
extern char datetext;
extern char datedayofweek;
extern char newpage;
extern char end;
extern char topline;
extern char botline;
extern char fontmode;
extern char largetimesfont;
extern char normallargefont;
extern char normalsmallfont;
extern char enablewidechar;
extern char disablewidechar;
extern char speed1;
extern char speed2;
extern char speed3;
extern char speed4;
extern char speed5;

int setmem(void);

int start(char a,char b ); //prototype (type of signs, sign 1 or 2 or both)
int starttext(char a, char b, char c); //prototype (type of sign, sign #, Text file)
int startc(char a, char b, char c, char d);
int startcommand(char a, char b, char c);
int startusb(char a,char b); //prototype usb
int signsoff(void);
#endif

