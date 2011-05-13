/******************************************************************************
 *  strtotime.cpp
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

#include <cstdlib>

int strtotime(const char* str)
{
	char* end = NULL;
	double t = strtod(str, &end);
	if (t <= 0)
		return 0;
	if (end)
	{
		if ((*end | 0x20) == 'm')
			t *= 60000;
		else if ((*end | 0x20) == 's')
			t *= 1000;
	}
	return int(t);
}
