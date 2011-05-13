/******************************************************************************
 *  CalcTextTime.cpp
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

#include <cctype>

int CalcTextTime(const char* pszText, int iWordTime)
{
	const char *p = pszText;
	const char *q = p;
	int c = 0, e = 0;
	while (*p)
	{
		if (isspace(*p))
		{
			if ((p - q) + e > 3)
			{
				++c;
				e = 0;
			}
			else
				++e;
			while (isspace(*++p)) ;
			q = p;
			continue;
		}
		++p;
	}
	if ((p - q) + e > 3)
		++c;
	//if (c < ((p-pszText)/8))
	//	c = (p-pszText)/8;
	return iWordTime * ((c < 10) ? 10 : c);
}
