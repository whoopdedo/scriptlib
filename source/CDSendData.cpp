/******************************************************************************
 *  CDSendData.cpp
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

extern const char* g_pszCDLinkFlavor;

long CDSend(const char* pszMessage, int iSource, const cMultiParm& mp)
{
	SService<ILinkSrv> pLS(g_pScriptManager);
	SService<ILinkToolsSrv> pLTS(g_pScriptManager);
#if (_DARKGAME == 1)
	linkset lsLinks;
	pLS->GetAll(lsLinks, pLTS->LinkKindNamed(g_pszCDLinkFlavor), iSource, 0);
	for (; lsLinks.AnyLinksLeft(); lsLinks.NextLink())
	{
		sLink sl = lsLinks.Get();
		g_pScriptManager->PostMessage2(iSource, sl.dest, pszMessage, mp, cMultiParm::Undef, cMultiParm::Undef);
	}
	return 0;
#else
	return pLS->BroadcastOnAllLinksData(iSource, pszMessage, pLTS->LinkKindNamed(g_pszCDLinkFlavor), mp);
#endif
}
