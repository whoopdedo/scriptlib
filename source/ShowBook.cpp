/******************************************************************************
 *  ShowBook.cpp
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
#include <malloc.h>

int ShowBook(int iObject, bool bArt, int iTime)
{
#if (_DARKGAME == 3)
	SService<IPropertySrv> pPS(g_pScriptManager);
	if (!pPS->Possessed(iObject, "UseMsg"))
		return 1;
	SService<IShockGameSrv> pShock(g_pScriptManager);
	pShock->AddTextObjProp(iObject, "UseMsg", 0, iTime);
#else
	SService<IPropertySrv> pPS(g_pScriptManager);
	if (!pPS->Possessed(iObject, "Book"))
		return 1;
	cMultiParm mpBook, mpBookArt;
	pPS->Get(mpBook, iObject, "Book", NULL);
	if (cScrStr(mpBook).IsEmpty())
	{
		return 1;
	}
	SService<IDarkUISrv> pUI(g_pScriptManager);
	if (bArt && pPS->Possessed(iObject, "BookArt"))
	{
		pPS->Get(mpBookArt, iObject, "BookArt", NULL);
		pUI->ReadBook(mpBook, mpBookArt);
	}
	else
	{
		SService<IDataSrv> pDS(g_pScriptManager);
		char* szBookFile = reinterpret_cast<char*>(alloca(strlen(mpBook) + 10));
		strcpy(szBookFile, "..\\books\\");
		strcat(szBookFile, mpBook);
		cScrStr str;
		pDS->GetString(str, szBookFile, "page_0", "", "strings");
		if (!str.IsEmpty())
		{
			if (iTime == 0)
				iTime = CalcTextTime(str, 500);
			pUI->TextMessage(str, 0, iTime);
		}
		str.Free();
	}
#endif
	return 0;
}
