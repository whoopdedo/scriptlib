/******************************************************************************
 *  SetParamString.cpp
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
#include <cstdio>

extern const char* g_pszParamDelim;
extern const char* g_pszQuotes;

char* SetParamString(char* pszString, const char* pszParam, const char* pszVal)
{
	if (!pszParam || !pszVal)
		return NULL;
	int iLen = pszString ? strlen(pszString) : 0;
	iLen += strlen(pszParam) + 2;
	char quote = 0;
	const char* pszChar = pszVal;
	while (*pszChar)
	{
		switch (*pszChar++)
		{
		case '"':
			if (!quote) quote = '\'';
			iLen += 2;
			break;
		case '\'':
			quote = '"';
			iLen += 2;
			break;
		case '\\':
			++iLen;
		case ';': case '=': case '!': case ' ':
			if (!quote) quote = '"';
		default:
			++iLen;
			break;
		}
	}
	if (quote)
		iLen += 2;
	char* pszNew = reinterpret_cast<char*>(g_pMalloc->Alloc(iLen + 1));
	if (!pszNew)
		return NULL;
	char* pszRet;
	if (quote)
	{
		pszRet = pszNew + sprintf(pszNew, "%s=", pszParam);
		pszChar = pszVal;
		*pszRet++ = quote;
		while (*pszChar)
		{
			if (*pszChar == quote || *pszChar == '\\')
				*pszRet++ = '\\';
			*pszRet++ = *pszChar++;
		}
		*pszRet++ = quote;
	}
	else
		pszRet = pszNew + sprintf(pszNew, "%s=%s", pszParam, pszVal);
	if (pszString)
	{
		*pszRet++ = *g_pszParamDelim;
		char* pszSep, *pszToken;
		for (pszSep = pszString, pszToken = strqsep(&pszSep, g_pszParamDelim, g_pszQuotes);
		     pszToken; pszToken = strqsep(&pszSep, g_pszParamDelim, g_pszQuotes))
		{
			while (isspace(*pszToken)) ++pszToken;
			if (!*pszToken)
				continue;
			char* pszStart = strchr(pszToken, '=');
			if (pszStart)
				*pszStart++ = '\0';
			if (_stricmp(pszToken, pszParam))
			{
				strcpy(pszRet, pszToken);
				pszRet += strlen(pszToken);
				if (pszStart)
				{
					*pszRet++ = '=';
					strcpy(pszRet, pszStart);
					pszRet += strlen(pszStart);
				}
				*pszRet++ = *g_pszParamDelim;
			}
		}
	}
	*pszRet = '\0';
	return pszNew;
}
