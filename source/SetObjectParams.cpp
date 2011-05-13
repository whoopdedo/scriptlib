/******************************************************************************
 *  SetObjectParams.cpp
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

extern const char* g_pszDesignNote;

int SetObjectParams(int iObject, const char* pszParams)
{
	SService<IPropertySrv> pPS(g_pScriptManager);
	cMultiParm mpDesignNote;
	mpDesignNote.Set(const_cast<char*>(pszParams));
	pPS->Add(iObject, g_pszDesignNote);
	int iRet = pPS->SetSimple(iObject, g_pszDesignNote, mpDesignNote);
	mpDesignNote.type = kMT_Undef;
	return iRet;
}
