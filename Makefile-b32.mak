###############################################################################
##  Makefile-b32.mak
##
##  This file is part of Object Script Library
##  Copyright (C) 2011 Tom N Harris <telliamed@whoopdedo.org>
##
##  This program is free software; you can redistribute it and/or modify
##  it under the terms of the GNU General Public License as published by
##  the Free Software Foundation; either version 2 of the License, or
##  (at your option) any later version.
##
##  This program is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU General Public License for more details.
##
##  You should have received a copy of the GNU General Public License
##  along with this program. If not, see <http://www.gnu.org/licenses/>.
##
###############################################################################

BCCROOT = D:\BCC

IMPLIB = $(BCCROOT)\bin\Implib
ILINK32 = $(BCCROOT)\bin\ILink32
TLIB = $(BCCROOT)\bin\TLib
BRC32 = $(BCCROOT)\bin\Brc32
TASM32 = $(BCCROOT)\bin\Tasm32
CC = $(BCCROOT)\bin\BCC32

srcdir = .\source
bin1dir = .\bin1
bin2dir = .\bin2
bin3dir = .\bin3
bindirectories = $(bin1dir) $(bin2dir) $(bin3dir)

LGDIR = ..\lg
LGLIB = lg.lib

DEFINES = -DWINVER=0x0400 -D_WIN32_WINNT=0x0400 -DWIN32_LEAN_AND_MEAN

!ifdef DEBUG
CXXDEBUG = -v -y -O0 -DDEBUG
!else
CXXDEBUG = -O2 -5 -OS -v- -DNDEBUG
!endif

INCLUDES = -I. -I$(srcdir) -I$(LGDIR)
CXXFLAGS = -q -P -tWD -tWM

SRCS =  $(srcdir)\ScriptLib.cpp \
	$(srcdir)\GetObjectParams.cpp \
	$(srcdir)\GetObjectParamsDirect.cpp \
	$(srcdir)\SetObjectParams.cpp \
	$(srcdir)\GetObjectParamString.cpp \
	$(srcdir)\GetObjectParamInt.cpp \
	$(srcdir)\GetObjectParamFloat.cpp \
	$(srcdir)\GetObjectParamBool.cpp \
	$(srcdir)\GetObjectParamObject.cpp \
	$(srcdir)\GetObjectParamTime.cpp \
	$(srcdir)\SetObjectParamString.cpp \
	$(srcdir)\SetObjectParamInt.cpp \
	$(srcdir)\SetObjectParamFloat.cpp \
	$(srcdir)\SetObjectParamBool.cpp \
	$(srcdir)\GetParamString.cpp \
	$(srcdir)\GetParamInt.cpp \
	$(srcdir)\GetParamFloat.cpp \
	$(srcdir)\GetParamBool.cpp \
	$(srcdir)\GetParamObject.cpp \
	$(srcdir)\GetParamTime.cpp \
	$(srcdir)\SetParamString.cpp \
	$(srcdir)\SetParamInt.cpp \
	$(srcdir)\SetParamFloat.cpp \
	$(srcdir)\SetParamBool.cpp \
	$(srcdir)\RemoveObjectParam.cpp \
	$(srcdir)\AddSingleMetaProperty.cpp \
	$(srcdir)\RemoveSingleMetaProperty.cpp \
	$(srcdir)\AddMetaProperty.cpp \
	$(srcdir)\RemoveMetaProperty.cpp \
	$(srcdir)\GetOneLink.cpp \
	$(srcdir)\GetOneLinkDest.cpp \
	$(srcdir)\GetOneLinkByData.cpp \
	$(srcdir)\GetOneLinkByDataDest.cpp \
	$(srcdir)\GetOneLinkInherited.cpp \
	$(srcdir)\GetOneLinkInheritedSrc.cpp \
	$(srcdir)\GetOneLinkByDataInherited.cpp \
	$(srcdir)\GetOneLinkByDataInheritedSrc.cpp \
	$(srcdir)\GetAnyLink.cpp \
	$(srcdir)\GetAnyLinkDest.cpp \
	$(srcdir)\GetAnyLinkByData.cpp \
	$(srcdir)\GetAnyLinkByDataDest.cpp \
	$(srcdir)\GetAnyLinkInherited.cpp \
	$(srcdir)\GetAnyLinkInheritedSrc.cpp \
	$(srcdir)\GetAnyLinkByDataInherited.cpp \
	$(srcdir)\GetAnyLinkByDataInheritedSrc.cpp \
	$(srcdir)\IterateLinks.cpp \
	$(srcdir)\IterateLinksByData.cpp \
	$(srcdir)\DeleteAllLinks.cpp \
	$(srcdir)\DeleteAllLinksByData.cpp \
	$(srcdir)\FixupPlayerLinks.cpp \
	$(srcdir)\SimpleSend.cpp \
	$(srcdir)\SimplePost.cpp \
	$(srcdir)\SimplePostLocal.cpp \
	$(srcdir)\CDSend.cpp \
	$(srcdir)\CDSendData.cpp \
	$(srcdir)\StrToObject.cpp \
	$(srcdir)\ShowBook.cpp \
	$(srcdir)\ShowString.cpp \
	$(srcdir)\DebugPrintf.cpp \
	$(srcdir)\DisplayPrintf.cpp \
	$(srcdir)\MultiParmAssignFloat.cpp \
	$(srcdir)\MultiParmAssignInt.cpp \
	$(srcdir)\MultiParmAssignString.cpp \
	$(srcdir)\MultiParmAssignVector.cpp \
	$(srcdir)\CalcTextTime.cpp \
	$(srcdir)\strsep.cpp \
	$(srcdir)\strqsep.cpp \
	$(srcdir)\strtocolor.cpp \
	$(srcdir)\strtotime.cpp \

OBJS = $(SRCS:.cpp=.obj)
OBJS1 = $(OBJS:$(srcdir)=$(bin1dir))
OBJS2 = $(OBJS:$(srcdir)=$(bin2dir))
OBJS3 = $(OBJS:$(srcdir)=$(bin3dir))

SCRIPTLIB1 = ScriptLib1.lib
SCRIPTLIB2 = ScriptLib2.lib
SCRIPTLIB3 = ScriptLib3.lib

{$(srcdir)}.cpp{$(bin1dir)}.obj:
	$(CC) $(CXXFLAGS) $(CXXDEBUG) $(DEFINES) -D_DARKGAME=1 $(INCLUDES) -n$(bin1dir) -c $<

{$(srcdir)}.cpp{$(bin2dir)}.obj:
	$(CC) $(CXXFLAGS) $(CXXDEBUG) $(DEFINES) -D_DARKGAME=2 $(INCLUDES) -n$(bin2dir) -c $<

{$(srcdir)}.cpp{$(bin3dir)}.obj:
	$(CC) $(CXXFLAGS) $(CXXDEBUG) $(DEFINES) -D_DARKGAME=3 $(INCLUDES) -n$(bin3dir) -c $<


all: $(bindirectories) $(SCRIPTLIB1) $(SCRIPTLIB2) $(SCRIPTLIB3)

clean:
	del /q $(OBJS1) $(OBJS2) $(OBJS3) $(SCRIPTLIB1) $(SCRIPTLIB2) $(SCRIPTLIB3)

BINS: $(bindirectories)
	@&md $**

$(bin1dir):
	-

$(bin2dir):
	-

$(bin3dir):
	-


$(SCRIPTLIB1): $(OBJS1)
	del /q $(SCRIPTLIB1)
	$(TLIB) /a $@ $?

$(SCRIPTLIB2): $(OBJS2)
	del /q $(SCRIPTLIB2)
	$(TLIB) /a $@ $?

$(SCRIPTLIB3): $(OBJS3)
	del /q $(SCRIPTLIB3)
	$(TLIB) /a $@ $?

