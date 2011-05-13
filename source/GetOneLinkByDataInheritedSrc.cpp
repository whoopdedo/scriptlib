/******************************************************************************
 *  GetOneLinkByDataInheritedSrc.cpp
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
#include <cstring>

long GetOneLinkByDataInheritedSrc(const char* pszFlavor, int iSource, int iDest, sLink* pResult, const void* pvData, int iDataLen)
{
	/*
	SInterface<ITraitManager> pTM(g_pScriptManager);
	SInterface<ILinkManager> pLM(g_pScriptManager);
	SInterface<IRelation> pRel = pLM->GetRelationNamed(pszFlavor);
	if (!pRel)
		return 0;
	SInterface<IObjectQuery> pTree = pTM->Query(iSource, kTraitQueryMetaProps | kTraitQueryFull);
	if (!pTree)
		return 0;

	int (__cdecl *cmp)(const void*, const void*, size_t) = memcmp;
	if (pvData && iDataLen == -1)
	{
		iDataLen = strlen(reinterpret_cast<const char*>(pvData)) + 1;
		cmp = reinterpret_cast<int (*)(const void*,const void*,size_t)>(::strnicmp);
	}

	link iLinkID;
	for (; ! pTree->Done(); pTree->Next())
	{
		if (pRel->AnyLinks(pTree->Object(), iDest))
		{
			SInterface<ILinkQuery> pLQ = pRel->Query(pTree->Object(), iDest);
			for (; ! pLQ->Done(); pLQ->Next())
			{
				void* pLinkData = pLQ->Data();
				if (pvData)
				{
					if (pLinkData && !(*cmp)(pvData, pLinkData, iDataLen))
					{
						iLinkID = pLQ->ID();
						if (pResult)
							pLQ->Link(pResult);
						break;
					}
				}
				else
				{
					if (!pLinkData || !*reinterpret_cast<const char*>(pLinkData))
					{
						iLinkID = pLQ->ID();
						if (pResult)
							pLQ->Link(pResult);
						break;
					}
				}
			}
			if (iLinkID)
				break;
		}
	}
	return iLinkID;
	*/
	SService<ILinkSrv> pLS(g_pScriptManager);
	SService<ILinkToolsSrv> pLTS(g_pScriptManager);

	int (__cdecl *cmp)(const void*, const void*, size_t) = memcmp;
	if (pvData && iDataLen == -1)
	{
		iDataLen = strlen(reinterpret_cast<const char*>(pvData)) + 1;
		cmp = reinterpret_cast<int (*)(const void*,const void*,size_t)>(::strnicmp);
	}

	linkset lsLinks;
	linkkind lkFlavor = (pszFlavor) ? pLTS->LinkKindNamed(pszFlavor) : 0;
	pLS->GetAllInheritedSingle(lsLinks, lkFlavor, iSource, iDest);
	link iLinkID;
	for (; lsLinks.AnyLinksLeft(); lsLinks.NextLink())
	{
		void* pLinkData = lsLinks.Data();
		if (pvData)
		{
			if (!pLinkData)
				continue;
			if ((*cmp)(pvData, pLinkData, iDataLen))
				continue;
		}
		else
		{
			if (pLinkData && *reinterpret_cast<const char*>(pLinkData))
				continue;
		}
		iLinkID = lsLinks.Link();
		if (pResult)
			*pResult = lsLinks.Get();
		break;
	}
	return iLinkID;
}
