/******************************************************************************
 *  ScriptLib.h
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
#ifndef SCRIPTLIB_H
#define SCRIPTLIB_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <lg/config.h>
#include <lg/objstd.h>
#include <lg/interface.h>
#include <lg/types.h>
#include <lg/scrservices.h>
#include <lg/scrmanagers.h>
#include <lg/links.h>

interface IScript;

/****************
 * Globals
 * The hosting app/module must define these.
 */
extern IMalloc* g_pMalloc;
extern IScriptMan* g_pScriptManager;


/* Game-dependent string constants. */
extern const char* g_pszDesignNote;
extern const char* g_pszCDLinkFlavor;

/*************
 * Properties
 */

// Read parameters from the Editor\DesignNote property.
// Strings are allocated using g_pMalloc. Please use Free.

// Returns the whole Design Note.
// Useful to save time if you're reading a lot of params.
char* GetObjectParams(int iObject);
char* GetObjectParamsDirect(int iObject);
int SetObjectParams(int iObject, const char* pszParams);
// Returns the param as a particular type.
char* GetObjectParamString(int iObject, const char* pszParam, const char* pszDefault = NULL);
int GetObjectParamInt(int iObject, const char* pszParam, int iDefault = 0);
float GetObjectParamFloat(int iObject, const char* pszParam, float iDefault = 0.0f);
bool GetObjectParamBool(int iObject, const char* pszParam, bool bDefault = false);
int SetObjectParamString(int iObject, const char* pszParam, const char* pszVal);
int SetObjectParamInt(int iObject, const char* pszParam, int iVal);
int SetObjectParamFloat(int iObject, const char* pszParam, float fVal);
int SetObjectParamBool(int iObject, const char* pszParam, bool bVal);
// Same, but uses the supplied string instead of extracting from the object.
char* GetParamString(const char* pszString, const char* pszParam, const char* pszDefault = NULL);
int GetParamInt(const char* pszString, const char* pszParam, int iDefault = 0);
float GetParamFloat(const char* pszString, const char* pszParam, float fDefault = 0.0f);
bool GetParamBool(const char* pszString, const char* pszParam, bool bDefault = false);
char* SetParamString(char* pszString, const char* pszParam, const char* pszVal);
char* SetParamInt(char* pszString, const char* pszParam, int iVal);
char* SetParamFloat(char* pszString, const char* pszParam, float fVal);
char* SetParamBool(char* pszString, const char* pszParam, bool bVal);
// Delete a specific parameter from the Design Note.
// All occurances of the parameter are removed.
bool RemoveObjectParam(int iObject, const char* pszParam);

int GetObjectParamObject(int iObject, const char* pszParam, int iDefault = 0);
int GetParamObject(const char* pszString, const char* pszParam, int iDefault = 0);
int GetObjectParamTime(int iObject, const char* pszParam, int iDefault = 0);
int GetParamTime(const char* pszString, const char* pszParam, int iDefault = 0);


/***********
 * Metaproperties
 */

// These functions take care to not put more than one instance
// of a metaproperty on an object.
int AddSingleMetaProperty(const char* pszMetaProp, int iObjId);
int AddSingleMetaProperty(int iMetaProp, int iObjId);
int RemoveSingleMetaProperty(const char* pszMetaProp, int iObjId);
int RemoveSingleMetaProperty(int iMetaProp, int iObjId);
// Simple add and replace. Allows for duplicates.
int AddMetaProperty(const char* pszMetaProp, int iObjId);
int RemoveMetaProperty(const char* pszMetaProp, int iObjId);


/********
 * Links
 */
// TODO: Change to this when the link class has access to ILinkManager
//typedef int (*LinkIterCallbackFunc)(link,const sLink&,IScript*,void*);
typedef int (*LinkIterCallbackFunc)(ILinkSrv*,ILinkQuery*,IScript*,void*);

// GetOne... - return the first link found.
// GetAny... - Randomly select a link from all that exist.
// ...Inheritedxxx - Crawl up the inheritence tree for the source or dest (or both)
//     until a match is found. For GetAny, the crawl will stop at the first
//     object found with a valid link.
// ...ByData - Filter based on link data. If the length is -1, a case-insensitive
//     string comparison is used.

long GetOneLink(const char* pszFlavor, int iSource, int iDest, sLink* pResult);
long GetOneLinkInherited(const char* pszFlavor, int iSource, int iDest, sLink* pResult);
long GetOneLinkInheritedSrc(const char* pszFlavor, int iSource, int iDest, sLink* pResult);
int GetOneLinkDest(const char* pszFlavor, int iSource);
long GetOneLinkByData(const char* pszFlavor, int iSource, int iDest, sLink* pResult, const void* pvData, int iDataLen);
long GetOneLinkByDataInherited(const char* pszFlavor, int iSource, int iDest, sLink* pResult, const void* pvData, int iDataLen);
long GetOneLinkByDataInheritedSrc(const char* pszFlavor, int iSource, int iDest, sLink* pResult, const void* pvData, int iDataLen);
int GetOneLinkByDataDest(const char* pszFlavor, int iSource, const void* pvData, int iDataLen);
long GetAnyLink(const char* pszFlavor, int iSource, int iDest, sLink* pResult);
long GetAnyLinkInherited(const char* pszFlavor, int iSource, int iDest, sLink* pResult);
long GetAnyLinkInheritedSrc(const char* pszFlavor, int iSource, int iDest, sLink* pResult);
int GetAnyLinkDest(const char* pszFlavor, int iSource);
long GetAnyLinkByData(const char* pszFlavor, int iSource, int iDest, sLink* pResult,
			    const void* pvData, int iDataLen);
long GetAnyLinkByDataInherited(const char* pszFlavor, int iSource, int iDest, sLink* pResult,
			    const void* pvData, int iDataLen);
long GetAnyLinkByDataInheritedSrc(const char* pszFlavor, int iSource, int iDest, sLink* pResult,
			    const void* pvData, int iDataLen);
int GetAnyLinkByDataDest(const char* pszFlavor, int iSource, const void* pvData, int iDataLen);
// The iterator callback should be a static member function.
// (Or just a regular non-member function.)
// Iteration will be halted if the callback returns 0.
long IterateLinks(const char* pszFlavor, int iSource, int iDest,
			    LinkIterCallbackFunc pfnLinkIterCallback, IScript* pScript, void* pData);
long IterateLinksByData(const char* pszFlavor, int iSource, int iDest,
			    const void* pvFilter, int iFilterLen,
			    LinkIterCallbackFunc pfnLinkIterCallback, IScript* pScript, void* pData);
void DeleteAllLinks(const char* pszFlavor, int iSource, int iDest);
void DeleteAllLinksByData(const char* pszFlavor, int iSource, int iDest, const void* pvData, int iDataLen);

// Any links between the source and the object that's the source of a PlayerFactory link
// will be relinked so the source points to the actual Player object.
void FixupPlayerLinks(int iSource, int iPlayer);


/***********
 * Messages
 */

void SimpleSend(int iSource, int iDest, const char* pszMessage,
		    const cMultiParm& mpData1 = cMultiParm::Undef, const cMultiParm& mpData2 = cMultiParm::Undef, const cMultiParm& mpData3 = cMultiParm::Undef);
void SimplePost(int iSource, int iDest, const char* pszMessage,
		    const cMultiParm& mpData1 = cMultiParm::Undef, const cMultiParm& mpData2 = cMultiParm::Undef, const cMultiParm& mpData3 = cMultiParm::Undef);
#if (_DARKGAME == 1)
inline void SimplePostLocal(int iSource, int iDest, const char* pszMessage,
		    const cMultiParm& mpData1 = cMultiParm::Undef, const cMultiParm& mpData2 = cMultiParm::Undef, const cMultiParm& mpData3 = cMultiParm::Undef)
{
	SimplePost(iSource, iDest, pszMessage, mpData1, mpData2, mpData3);
}
#else
void SimplePostLocal(int iSource, int iDest, const char* pszMessage,
		    const cMultiParm& mpData1 = cMultiParm::Undef, const cMultiParm& mpData2 = cMultiParm::Undef, const cMultiParm& mpData3 = cMultiParm::Undef);
#endif
long CDSend(const char* pszMessage, int iSource);
long CDSend(const char* pszMessage, int iSource, const cMultiParm& mpData);


/*************
 * MultiParms
 */

// The cMultiParm class provides for direct assignment and casting.
// This is mostly for setting the pReply in ReceiveMessage.
void MultiParmAssignInt(sMultiParm* pParm, int iValue);
void MultiParmAssignFloat(sMultiParm* pParm, float fValue);
void MultiParmAssignString(sMultiParm* pParm, const char* pszValue);
void MultiParmAssignVector(sMultiParm* pParm, const mxs_vector* pvValue);


/*************
 * Objects
 */

int StrToObject(const char* pszName);


/***********
 * User
 */

int CalcTextTime(const char* pszText, int iWordTime = 500);
int ShowBook(int iObject, bool bArt, int iTime = 0);
void ShowString(const char* pszStr, int iTime, ulong color = 0);
__attribute__((format (printf,1,2)))
	void DebugPrintf(const char* pszFormat, ...);
__attribute__((format (printf,1,2)))
	void DisplayPrintf(const char* pszFormat, ...);


/************
 * Utils
 */
__attribute__((nonnull (1,2)))
	char* strsep(char** str, const char* delim);
__attribute__((nonnull (1,2,3)))
	char* strqsep(char** str, const char* delim, const char* quotes);

inline ulong makecolor(unsigned char r, unsigned char g, unsigned char b)
{
	return ((ulong)r) | ((ulong)g << 8) | ((ulong)b << 16);
}
inline unsigned char getred(ulong c) { return (unsigned char)(c & 0xFF); }
inline unsigned char getgreen(ulong c) { return (unsigned char)(c >> 8 & 0xFF); }
inline unsigned char getblue(ulong c) { return (unsigned char)(c >> 16 & 0xFF); }
ulong strtocolor(const char* str);
int strtotime(const char* str);

#endif // SCRIPTLIB_H
