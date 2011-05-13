/******************************************************************************
 *  SimplePostLocal.cpp
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

#if (_DARKGAME != 1)
void SimplePostLocal(int iSource, int iDest, const char* pszMessage, const cMultiParm& mpData1, const cMultiParm& mpData2, const cMultiParm& mpData3)
{
	g_pScriptManager->PostMessage2(iSource, iDest, pszMessage, mpData1, mpData2, mpData3, 0);
}
#endif
