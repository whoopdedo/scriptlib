/******************************************************************************
 *  GetObjectParamsDirect.cpp
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
#include <lg/properties.h>
#include <cstring>

extern const char* g_pszDesignNote;

char* GetObjectParamsDirect(int iObject)
{
	SInterface<IPropertyManager> pPM(g_pScriptManager);
	SInterface<IProperty> pProp = pPM->GetPropertyNamed(g_pszDesignNote);
	if (!pProp)
		throw null_pointer();
	if (!pProp->IsSimplyRelevant(iObject))
		return NULL;
	SInterface<IStringProperty> pDNProp = static_cast<IUnknown*>(pProp);
	const char* pszDesignNote;
	char* pszRet;
	pDNProp->GetSimple(iObject, &pszDesignNote);
	pszRet = reinterpret_cast<char*>(g_pMalloc->Alloc(strlen(pszDesignNote) + 1));
	if (pszRet)
		strcpy(pszRet, pszDesignNote);
	return pszRet;
}
