/******************************************************************************
 *  DeleteAllLinksByData.cpp
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
#include <cstring>

void DeleteAllLinksByData(const char* pszFlavor, int iSource, int iDest, const void* pvFilter, int iFilterLen)
{
	SService<ILinkSrv> pLS(g_pScriptManager);
	SService<ILinkToolsSrv> pLTS(g_pScriptManager);

	int (__cdecl *cmp)(const void*, const void*, size_t) = memcmp;
	if (pvFilter && iFilterLen == -1)
	{
		iFilterLen = strlen(reinterpret_cast<const char*>(pvFilter)) + 1;
		cmp = reinterpret_cast<int (*)(const void*,const void*,size_t)>(::strnicmp);
	}

	linkset lsLinks;
	linkkind lkFlavor = (pszFlavor) ? pLTS->LinkKindNamed(pszFlavor) : 0;
	pLS->GetAll(lsLinks, lkFlavor, iSource, iDest);
	for (; lsLinks.AnyLinksLeft(); lsLinks.NextLink())
	{
		void* pLinkData = lsLinks.Data();
		if (pvFilter)
		{
			if (!pLinkData)
				continue;
			if ((*cmp)(pvFilter, pLinkData, iFilterLen))
				continue;
		}
		else
		{
			if (pLinkData && *reinterpret_cast<const char*>(pLinkData))
				continue;
		}
		pLS->Destroy(lsLinks.Link());
	}
}
