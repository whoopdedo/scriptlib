/******************************************************************************
 *  StrToObject.cpp
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
#include <cstdlib>

int StrToObject(const char* pszName)
{
	if (!pszName || !*pszName)
		return 0;
	SService<IObjectSrv> pOS(g_pScriptManager);
	object obj;
	pOS->Named(obj, pszName);
	if (!obj)
	{
		char *p = NULL;
		obj = strtol(pszName, &p, 10);
		//if (*p != '\0')
		//	return 0;
		true_bool _p;
		if (! *pOS->Exists(_p, obj))
			return 0;
	}
	return obj;
}

