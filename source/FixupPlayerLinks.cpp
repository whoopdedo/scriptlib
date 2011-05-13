/******************************************************************************
 *  FixupPlayerLinks.cpp
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

static int FixupPlayerLinksFunc(ILinkSrv*, ILinkQuery* pLQ, IScript*, void* pData)
{
	// Move the destination of the link to the object specified in pData
	SInterface<ILinkManager> pLM(g_pScriptManager);
	object iPlayer = reinterpret_cast<int>(pData);
	sLink slInfo;
	pLQ->Link(&slInfo);
	link lNew = pLM->Add(slInfo.source, iPlayer, slInfo.flavor);
	if (lNew)
	{
		void* pLinkData = pLQ->Data();
		if (pLinkData)
			pLM->SetData(lNew, pLinkData);
	}
	pLM->Remove(pLQ->ID());
	return 1;
}

void FixupPlayerLinks(int iSource, int iPlayer)
{
	SService<ILinkSrv> pLS(g_pScriptManager);
	SService<ILinkToolsSrv> pLTS(g_pScriptManager);
	// Get the PlayerFactory link. There should only ever be one of these.
	link lPFLink;
	pLS->GetOne(lPFLink, pLTS->LinkKindNamed("PlayerFactory"), 0, 0);
	if (!lPFLink)
		return;
	// Iterate through all links from here to the source of the PF link.
	sLink lPFInfo;
	pLTS->LinkGet(lPFLink, lPFInfo);
	IterateLinks(NULL, iSource, lPFInfo.source, FixupPlayerLinksFunc, NULL, reinterpret_cast<void*>(iPlayer));
}
