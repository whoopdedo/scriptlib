/******************************************************************************
 *  strsep.cpp
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

char* strsep(char** str, const char* delim)
{
	char dtable[256];
	char* p = *str;
	if (!p) return NULL;
	memset(dtable,0,sizeof(dtable));
	{
		const unsigned char* d = reinterpret_cast<const unsigned char*>(delim);
		while (*d)
			dtable[*d++] = -1;
	}
	while (*p)
	{
		if (dtable[*reinterpret_cast<unsigned char*>(p)])
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
