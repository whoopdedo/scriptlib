/******************************************************************************
 *  GetObjectParams.cpp
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

char* GetObjectParams(int iObject)
{
	SService<IPropertySrv> pPS(g_pScriptManager);
	cMultiParm mpDesignNote;
	if (!pPS->Possessed(iObject, g_pszDesignNote))
		return NULL;
	pPS->Get(mpDesignNote, iObject, g_pszDesignNote, NULL);
	// naughty little shortcut to avoid alloc+copy
	mpDesignNote.type = kMT_Undef;
	return (mpDesignNote.psz);
}
