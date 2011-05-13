/******************************************************************************
 *  AddSingleMetaProperty.cpp
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

static int DoAddMetaProperty(const SService<IObjectSrv>& pOS, object oMetaProp, object oObject)
{
	int iRet = 0;
	true_bool has_mp;
	pOS->HasMetaProperty(has_mp, oObject, oMetaProp);
	if (!has_mp)
	{
		iRet = pOS->AddMetaProperty(oObject, oMetaProp);
	}
	return iRet;
}

int AddSingleMetaProperty(const char* pszMetaProp, int iObjId)
{
	SService<IObjectSrv> pOS(g_pScriptManager);
	object oMetaProp;
	pOS->Named(oMetaProp, pszMetaProp);
	if (oMetaProp)
		return DoAddMetaProperty(pOS, oMetaProp, iObjId);
	return 0;
}

int AddSingleMetaProperty(int iMetaProp, int iObjId)
{
	SService<IObjectSrv> pOS(g_pScriptManager);
	return DoAddMetaProperty(pOS, iMetaProp, iObjId);
}
