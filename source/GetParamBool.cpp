/******************************************************************************
 *  GetParamBool.cpp
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
#include <cctype>
#include <cstdlib>
#include <malloc.h>

extern const char* g_pszParamDelim;
extern const char* g_pszQuotes;

bool GetParamBool(const char* pszString, const char* pszParam, bool bDefault)
{
	if (!pszString || !pszParam)
		return bDefault;
	bool bRet = bDefault;
	char* pszTemp = reinterpret_cast<char*>(alloca(strlen(pszString)+1));
	if (!pszTemp)
		return false;
	strcpy(pszTemp, pszString);
	char* pszSep, *pszToken;
	for (pszSep = pszTemp, pszToken = strqsep(&pszSep, g_pszParamDelim, g_pszQuotes);
	     pszToken; pszToken = strqsep(&pszSep, g_pszParamDelim, g_pszQuotes))
	{
		while (isspace(*pszToken)) ++pszToken;
		char* pszStart = strchr(pszToken, '=');
		if (pszStart)
			*pszStart++ = '\0';
		if (!_stricmp(pszToken, pszParam))
		{
			if (!pszStart)
				break;
			while (isspace(*pszStart)) ++pszStart;
			char* pszEnd = pszStart + strlen(pszStart);
			if (*pszStart == '\"' || *pszStart == '\'')
			{
				if (*(pszEnd-1) == *pszStart)
					*(--pszEnd) = '\0';
				++pszStart;
			}
			switch (*pszStart)
			{
			case '1': case 't': case 'T': case 'y': case 'Y':
				bRet = true;
				break;
			case '$':
			{
				++pszStart;
				if (pszEnd > pszStart)
				{
					SService<IQuestSrv> pQS(g_pScriptManager);
					if (pQS->Exists(pszStart))
						bRet = pQS->Get(pszStart);
				}
				break;
			}
			default:
				bRet = strtol(pszStart, NULL, 0);
				break;
			}
			break;
		}
	}
	return bRet;
}
