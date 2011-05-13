/******************************************************************************
 *  GetOneLinkInheritedSrc.cpp
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

long GetOneLinkInheritedSrc(const char* pszFlavor, int iSource, int iDest, sLink* pResult)
{
	/*
	SInterface<ITraitManager> pTM(g_pScriptManager);
	SInterface<ILinkManager> pLM(g_pScriptManager);
	SInterface<IRelation> pRel = pLM->GetRelationNamed(pszFlavor);
	if (!pRel)
		return 0;

	link iLinkID;
	SInterface<IObjectQuery> pTree = pTM->Query(iSource, kTraitQueryMetaProps | kTraitQueryFull);
	if (!pTree)
		return 0;

	for (; ! pTree->Done(); pTree->Next())
	{
		if (pRel->AnyLinks(pTree->Object(), iDest))
		{
			SInterface<ILinkQuery> pLQ = pRel->Query(pTree->Object(), iDest);
			iLinkID = pLQ->ID();
			break;
		}
	}

	if (iLinkID && pResult)
		pLM->Get(iLinkID, pResult);
	return iLinkID;
	*/
	SService<ILinkSrv> pLS(g_pScriptManager);
	SService<ILinkToolsSrv> pLTS(g_pScriptManager);
	linkset lsLinks;
	linkkind lkFlavor = (pszFlavor) ? pLTS->LinkKindNamed(pszFlavor) : 0;
	pLS->GetAllInheritedSingle(lsLinks, lkFlavor, iSource, iDest);
	link iLinkID;
	if (lsLinks.AnyLinksLeft())
	{
		iLinkID = lsLinks.Link();
		if (pResult)
			*pResult = lsLinks.Get();
	}
	return iLinkID;
}
