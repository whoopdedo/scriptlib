###############################################################################
##  Makefile-gcc
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


.SUFFIXES:
.SUFFIXES: .o .cpp .rc

srcdir = ./source
bin1dir = ./bin1
bin2dir = ./bin2
bin3dir = ./bin3
bindirectories = $(bin1dir) $(bin2dir) $(bin3dir)

LGDIR = ../lg

CC = gcc
CXX = g++
AR = ar

DEFINES = -DWINVER=0x0400 -D_WIN32_WINNT=0x0400 -DWIN32_LEAN_AND_MEAN

CXXDEBUG = -O2 -DNDEBUG
D =

ARFLAGS = rc
INCLUDES = -I. -I$(srcdir) -I$(LGDIR)
CXXFLAGS = -W -Wall -masm=intel

SRCS =  ScriptLib.cpp \
	GetObjectParams.cpp \
	GetObjectParamsDirect.cpp \
	SetObjectParams.cpp \
	GetObjectParamString.cpp \
	GetObjectParamInt.cpp \
	GetObjectParamFloat.cpp \
	GetObjectParamBool.cpp \
	GetObjectParamObject.cpp \
	GetObjectParamTime.cpp \
	SetObjectParamString.cpp \
	SetObjectParamInt.cpp \
	SetObjectParamFloat.cpp \
	SetObjectParamBool.cpp \
	GetParamString.cpp \
	GetParamInt.cpp \
	GetParamFloat.cpp \
	GetParamBool.cpp \
	GetParamObject.cpp \
	GetParamTime.cpp \
	SetParamString.cpp \
	SetParamInt.cpp \
	SetParamFloat.cpp \
	SetParamBool.cpp \
	RemoveObjectParam.cpp \
	AddSingleMetaProperty.cpp \
	RemoveSingleMetaProperty.cpp \
	AddMetaProperty.cpp \
	RemoveMetaProperty.cpp \
	GetOneLink.cpp \
	GetOneLinkDest.cpp \
	GetOneLinkByData.cpp \
	GetOneLinkByDataDest.cpp \
	GetOneLinkInherited.cpp \
	GetOneLinkInheritedSrc.cpp \
	GetOneLinkByDataInherited.cpp \
	GetOneLinkByDataInheritedSrc.cpp \
	GetAnyLink.cpp \
	GetAnyLinkDest.cpp \
	GetAnyLinkByData.cpp \
	GetAnyLinkByDataDest.cpp \
	GetAnyLinkInherited.cpp \
	GetAnyLinkInheritedSrc.cpp \
	GetAnyLinkByDataInherited.cpp \
	GetAnyLinkByDataInheritedSrc.cpp \
	IterateLinks.cpp \
	IterateLinksByData.cpp \
	DeleteAllLinks.cpp \
	DeleteAllLinksByData.cpp \
	FixupPlayerLinks.cpp \
	SimpleSend.cpp \
	SimplePost.cpp \
	SimplePostLocal.cpp \
	CDSend.cpp \
	CDSendData.cpp \
	StrToObject.cpp \
	ShowBook.cpp \
	ShowString.cpp \
	DebugPrintf.cpp \
	DisplayPrintf.cpp \
	MultiParmAssignFloat.cpp \
	MultiParmAssignInt.cpp \
	MultiParmAssignString.cpp \
	MultiParmAssignVector.cpp \
	CalcTextTime.cpp \
	strsep.cpp \
	strqsep.cpp \
	strtocolor.cpp \
	strtotime.cpp \

OBJS1 = $(SRCS:%.cpp=$(bin1dir)/%.o)
OBJS1D = $(SRCS:%.cpp=$(bin1dir)/%-d.o)
OBJS2 = $(SRCS:%.cpp=$(bin2dir)/%.o)
OBJS2D = $(SRCS:%.cpp=$(bin2dir)/%-d.o)
OBJS3 = $(SRCS:%.cpp=$(bin3dir)/%.o)
OBJS3D = $(SRCS:%.cpp=$(bin3dir)/%-d.o)

SCRIPTLIB1 = libScript1.a
SCRIPTLIB1D = libScript1-d.a
SCRIPTLIB2 = libScript2.a
SCRIPTLIB2D = libScript2-d.a
SCRIPTLIB3 = libScript3.a
SCRIPTLIB3D = libScript3-d.a

$(bin1dir)/%.o: $(srcdir)/%.cpp
	$(CXX) $(CXXFLAGS) $(CXXDEBUG) $(DEFINES) -D_DARKGAME=1 $(INCLUDES) -o $@ -c $<

$(bin1dir)/%-d.o: $(srcdir)/%.cpp
	$(CXX) $(CXXFLAGS) $(CXXDEBUG) $(DEFINES) -D_DARKGAME=1 $(INCLUDES) -o $@ -c $<

$(bin2dir)/%.o: $(srcdir)/%.cpp
	$(CXX) $(CXXFLAGS) $(CXXDEBUG) $(DEFINES) -D_DARKGAME=2 $(INCLUDES) -o $@ -c $<

$(bin2dir)/%-d.o: $(srcdir)/%.cpp
	$(CXX) $(CXXFLAGS) $(CXXDEBUG) $(DEFINES) -D_DARKGAME=2 $(INCLUDES) -o $@ -c $<

$(bin3dir)/%.o: $(srcdir)/%.cpp
	$(CXX) $(CXXFLAGS) $(CXXDEBUG) $(DEFINES) -D_DARKGAME=3 $(INCLUDES) -o $@ -c $<

$(bin3dir)/%-d.o: $(srcdir)/%.cpp
	$(CXX) $(CXXFLAGS) $(CXXDEBUG) $(DEFINES) -D_DARKGAME=3 $(INCLUDES) -o $@ -c $<


all: $(bindirectories) $(SCRIPTLIB1) $(SCRIPTLIB1D) $(SCRIPTLIB2) $(SCRIPTLIB2D) $(SCRIPTLIB3) $(SCRIPTLIB3D)

clean:
	$(RM) $(bin1dir)/*.o $(bin2dir)/*.o $(bin3dir)/*.o $(SCRIPTLIB1) $(SCRIPTLIB1D) $(SCRIPTLIB2) $(SCRIPTLIB2D) $(SCRIPTLIB3) $(SCRIPTLIB3D)

$(bin1dir):
	mkdir -p $@
$(bin2dir):
	mkdir -p $@
$(bin3dir):
	mkdir -p $@

$(SCRIPTLIB1): $(OBJS1)
	$(AR) $(ARFLAGS) $@ $?

$(SCRIPTLIB1D): CXXDEBUG = -g -DDEBUG
$(SCRIPTLIB1D): LDDEBUG = -g
$(SCRIPTLIB1D): $(OBJS1D)
	$(AR) $(ARFLAGS) $@ $?

$(SCRIPTLIB2): $(OBJS2)
	$(AR) $(ARFLAGS) $@ $?

$(SCRIPTLIB2D): CXXDEBUG = -g -DDEBUG
$(SCRIPTLIB2D): LDDEBUG = -g
$(SCRIPTLIB2D): $(OBJS2D)
	$(AR) $(ARFLAGS) $@ $?

$(SCRIPTLIB3): $(OBJS3)
	$(AR) $(ARFLAGS) $@ $?

$(SCRIPTLIB3D): CXXDEBUG = -g -DDEBUG
$(SCRIPTLIB3D): LDDEBUG = -g
$(SCRIPTLIB3D): $(OBJS3D)
	$(AR) $(ARFLAGS) $@ $?

