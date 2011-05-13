/******************************************************************************
 *  strqsep.cpp
 *
 *  This file is part of Object Script Library
 *  Copyright (C) 2011 Tom N Harris <telliamed@whoopdedo.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************/

#include <cstring>

/* Seperate a string on any of delim characters while preserving
 * substrings surrounded by an equal pair of any of quotes characters.
 * str is the address of a pointer to the string to be seperated.
 * The pointer to the next token in the string, or NULL, is copied to
 * the address and the the value that was passed in *str is returned.
 * delim and quotes cannot be NULL.
 * Empty tokens will be returned.
 * Like strtok and strsep, the string data will be modified.
 * str, of course, must be an lvalue.
 */
char* strqsep(char** str, const char* delim, const char* quotes)
{
	char dtable[256];
	char qtable[256];
	char* p = *str;
	if (!p) return NULL;
	memset(dtable,0,sizeof(dtable));
	memset(qtable,0,sizeof(dtable));
	{
		const unsigned char* d = reinterpret_cast<const unsigned char*>(delim);
		while (*d)
			dtable[*d++] = -1;
	}
	{
		const unsigned char* q = reinterpret_cast<const unsigned char*>(quotes);
		while (*q)
			qtable[*q++] = -1;
	}
	while (*p)
	{
		if (qtable[*reinterpret_cast<unsigned char*>(p)])
		{
			char* t = p;
			do
			{
				t = strchr(t+1, *p);
				if (!t)
				{
					p = *str;
					*str = NULL;
					return p;
				}
			}
			while (*(t-1) == '\\');
			p = t;
		}
		else if (dtable[*reinterpret_cast<unsigned char*>(p)])
		{
			char* t = *str;
			*p++ = '\0';
			*str = p;
			return t;
		}
		++p;
	}
	p = *str;
	*str = NULL;
	return p;
}
