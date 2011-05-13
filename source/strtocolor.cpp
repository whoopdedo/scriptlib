/******************************************************************************
 *  strtocolor.cpp
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

#include <lg/config.h>
#include <lg/objstd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

static const unsigned char g_cHexTable[] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        0,1,2,3,4,5,6,7,8,9,0,0,0,0,0,0,
	0,10,11,12,13,14,15,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,10,11,12,13,14,15,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

typedef struct _colorname
{
	const char* n;
	uint c;
} colorname;
static const colorname g_sColorNames[] = {
	{ "aqua",       0xFFFF00U },
	{ "black",      0x080808U },
	{ "blue",       0xFF0000U },
	{ "chartreuse", 0x80FF80U },
	{ "dodger",     0x0080FFU },
	{ "fuchsia",    0xFF00FFU },
	{ "gold",       0x80FFFFU },
	{ "gray",       0x808080U },
	{ "green",      0x008000U },
	{ "grey",       0x808080U },
	{ "lawn",       0x00FF80U },
	{ "lime",       0x00FF00U },
	{ "maroon",     0x000080U },
	{ "navy",       0x800000U },
	{ "olive",      0x008080U },
	{ "orange",     0x0080FFU },
	{ "orchid",     0xFF80FFU },
	{ "pink",       0x8000FFU },
	{ "purple",     0x800080U },
	{ "red",        0x0000FFU },
	{ "rose",       0x8080FFU },
	{ "silver",     0xC0C0C0U },
	{ "slate",      0xFF8080U },
	{ "spring",     0x80FF00U },
	{ "steel",      0xFF8000U },
	{ "teal",       0x808000U },
	{ "turquoise",  0xFFFF80U },
	{ "violet",     0xFF0080U },
	{ "white",      0xFFFFFFU },
	{ "yellow",     0x00FFFFU }
};

int colornamecmp(const void* key, const void* elem)
{
	return _stricmp(reinterpret_cast<const char*>(key),
		reinterpret_cast<const colorname*>(elem)->n);
}

uint strtocolor(const char* str)
{
	const unsigned char* c = reinterpret_cast<const unsigned char*>(str);
	if (*c == '#')
	{
		if (strlen(reinterpret_cast<const char*>(++c)) < 6)
			return 0;
		uint r,g,b;
		r  = g_cHexTable[*c++] << 4;
		r |= g_cHexTable[*c++];
		g  = g_cHexTable[*c++] << 4;
		g |= g_cHexTable[*c++];
		b  = g_cHexTable[*c++] << 4;
		b |= g_cHexTable[*c];
		return (r|(g<<8)|(b<<16));
	}
	if (strchr(str, ','))
	{
		uint r,g,b;
		if (3 == sscanf(str, "%u , %u , %u", &r, &g, &b))
		{
			return ((r&0xFF)|((g&0xFF)<<8)|((b&0xFF)<<16));
		}
	}
	else
	{
		const colorname* clr = reinterpret_cast<const colorname*>(
			bsearch(reinterpret_cast<const void*>(str),
				reinterpret_cast<const void*>(g_sColorNames),
				sizeof(g_sColorNames)/sizeof(g_sColorNames[0]),
				sizeof(colorname),
				colornamecmp)
			);
		if (clr)
			return clr->c;
	}
	return 0;
}
