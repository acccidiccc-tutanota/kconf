/*  tool for configuring kernels
    Copyright (C) 2021  Leon C. Gundel

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/
/* this file was originally a part of the thalassa operating system */
/* not really a script isn't it? */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define IN_PATH "kconf.conf"
#define OUT_PATH "kconf.d"
#define MAXBUFLEN 1000000
#define COMMENT_CHAR '%'
#define SEPERATOR '\n'
int main ()
{
	char flag[1000];
	char final[1002];
	char source[MAXBUFLEN + 1];
	FILE *IN = fopen (IN_PATH, "r");
	FILE *OUT = fopen (OUT_PATH, "w");
	size_t newLen;
	if (IN != NULL) {
		newLen = fread (source, sizeof (char), MAXBUFLEN, IN);
		if (ferror (IN) != 0) {
			fputs ("Error reading file", stderr);
		} else {
			source[newLen++] = '\0';	/* Just to be safe. */
		}
		fclose (IN);

	}
	int i, j;
	for (i = 0; i <= newLen;) {

		memset (flag, 0, strlen (flag));
		memset (final, 0, strlen (final));
		final[0] = '-';
		final[1] = 'D';
		int get_checked = 0;
	      check:

		if (source[i] == '\0') {
			break;
		}
		if (source[i] == ' ') {
			i++;
			get_checked = 1;

		}
		if (source[i] == '\n') {	//checking for trailing characters.
			i++;
			get_checked = 1;
		}
		if (get_checked) {
		//printf("trailing characters.\n");
			get_checked = 0;
			goto check;
		}
		if (source[i] == COMMENT_CHAR) {
			i++;
			for (; source[i] != COMMENT_CHAR; i++);

			i++;
			goto check;
		}
		for (j = 0; source[i] != '\n' && source[i] != ' '; j++, i++) {
			flag[j] = source[i];
		//printf("%d ", j);             

		}

		strcat (final, flag);

		fputs (final, OUT);
		fputc (SEPERATOR, OUT);


	}
	fclose (OUT);
}
