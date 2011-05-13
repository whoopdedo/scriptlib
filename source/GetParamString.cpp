/******************************************************************************
 *  GetParamString.cpp
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
#include <malloc.h>

extern const char* g_pszParamDelim;
extern const char* g_pszQuotes;

char* GetParamString(const char* pszString, const char* pszParam, const char* pszDefault)
{
	char* pszRet = NULL;
	if (pszString && pszParam)
	{
		char* pszTemp = reinterpret_cast<char*>(alloca(strlen(pszString)+1));
		if (!pszTemp)
			return NULL;
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
				char* pszEnd, quote;
				if (*pszStart == '"' || *pszStart == '\'')
				{
					quote = *pszStart++;
					pszEnd = strrchr(pszStart, quote);
					if (!pszEnd)
						pszEnd = pszStart + strlen(pszStart);
				}
				else
				{
					pszEnd = pszStart + strlen(pszStart);
					quote = 0;
				}
				int iLen = pszEnd - pszStart;
				pszRet = reinterpret_cast<char*>(g_pMalloc->Alloc(iLen + 1));
				if (pszRet)
				{
					if (quote)
					{
						char* pszChar = pszRet;
						while (pszStart < pszEnd)
						{
							if (*pszStart == '\\' &&
							    (pszStart[1] == '\\' || pszStart[1] == quote))
							{
								++pszStart;
							}
							*pszChar++ = *pszStart++;
						}
						*pszChar = '\0';
					}
					else
					{
						strncpy(pszRet, pszStart, iLen);
						pszRet[iLen] = '\0';
					}
				}
				break;
			}
		}
	}
	if (!pszRet && pszDefault)
	{
		pszRet = reinterpret_cast<char*>(g_pMalloc->Alloc(strlen(pszDefault) + 1));
		if (pszRet)
			strcpy(pszRet, pszDefault);
	}
	return pszRet;
}
