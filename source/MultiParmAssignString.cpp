/******************************************************************************
 *  MultiParmAssignString.cpp
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

#include "ScriptLib.h"

#include <string.h>

void MultiParmAssignString(sMultiParm* pParm, const char* pszValue)
{
	char* pTemp = pParm->psz;
	pParm->psz = reinterpret_cast<char*>(g_pMalloc->Alloc(strlen(pszValue) + 1));
	if (pParm->psz)
		strcpy(pParm->psz, pszValue);
	if (pTemp && (pParm->type == kMT_String || pParm->type == kMT_Vector))
		g_pMalloc->Free(pTemp);
	pParm->type = kMT_String;
}
