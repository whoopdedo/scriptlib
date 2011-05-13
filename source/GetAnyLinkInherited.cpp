/******************************************************************************
 *  GetAnyLinkInherited.cpp
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
#include <lg/objects.h>
#include <lg/dynarray.h>

long GetAnyLinkInherited(const char* pszFlavor, int iSource, int iDest, sLink* pResult)
{
	SService<ILinkSrv> pLS(g_pScriptManager);
	SService<ILinkToolsSrv> pLTS(g_pScriptManager);

	cDynArray<link> aLinks;
	aLinks.resize(32);
	linkset lsLinks;
	linkkind lkFlavor = (pszFlavor) ? pLTS->LinkKindNamed(pszFlavor) : 0;
	pLS->GetAllInherited(lsLinks, lkFlavor, iSource, iDest);
	for (; lsLinks.AnyLinksLeft(); lsLinks.NextLink())
	{
		aLinks.append(lsLinks.Link());
	}

	link iLinkID;
	if (aLinks.size() != 0)
	{
		SService<IDataSrv> pDS(g_pScriptManager);
		iLinkID = aLinks[pDS->RandInt(0, aLinks.size() - 1)];
		if (iLinkID && pResult)
			pLTS->LinkGet(iLinkID, *pResult);
	}
	return iLinkID;
}
