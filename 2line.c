/*
 *     This program 2line will open a tty, and tells it to display multi lines .
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
#include "signfp.h"
//MUTILINE EXAMPLE
int main(void)
{
	char TempBuff[200]; // Tempory buff.
	int fp,Bcount,Wcount; //fp = file pointer Bcount=Buffer Count Wcount= Wrote out count
	fp = open_port(); // Oh magical open_port I call you! ^.^ look in signfp.c for source
	starttext(fp,'Z','3','A'); // See Data sheet for 'Z', '3', 'A'

	Bcount=sprintf(TempBuff,"%c%ce",smf,topline);
	Wcount=write(fp,TempBuff,Bcount);
	Bcount=sprintf(TempBuff,"%c%c TODO:",cc,red);
	Wcount=write(fp,TempBuff,Bcount);
	Bcount=sprintf(TempBuff,"%c%ce",smf,botline);
	Wcount=write(fp,TempBuff,Bcount);
	Bcount=sprintf(TempBuff,"%c%c",cc,green);
	Wcount=write(fp,TempBuff,Bcount);
	Bcount=sprintf(TempBuff,"1.Work on render Ideas  \n");
	Wcount=write(fp,TempBuff,Bcount);
	Bcount=sprintf(TempBuff,"2.re read doubt start working on plot\n");
	Wcount=write(fp,TempBuff,Bcount);
	Bcount=sprintf(TempBuff,"3. Research teathering\n");
	Wcount=write(fp,TempBuff,Bcount);
	Bcount=sprintf(TempBuff,"%c%c%cUNION WEBSITE!!!!%c",enablewidechar,cc,red,disablewidechar);
	Wcount=write(fp,TempBuff,Bcount);
	Bcount=sprintf(TempBuff,"%c",end);
	Wcount=write(fp,TempBuff,Bcount);


return 0;
}
