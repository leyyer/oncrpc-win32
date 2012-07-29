# Microsoft Developer Studio Project File - Name="oncrpc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=oncrpc - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "oncrpc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "oncrpc.mak" CFG="oncrpc - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "oncrpc - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "oncrpc - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "oncrpc - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /MT /W3 /Gf /I "..\..\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_NT" /FR /YX"all_oncrpc.h" /FD /c
# SUBTRACT CPP /nologo
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /D "NDEBUG" /mktyplib203 /win32
# SUBTRACT MTL /nologo
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /subsystem:windows /dll /debug /machine:I386 /libpath:"\dserver\lib\nt4.0\Release"
# SUBTRACT LINK32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy .\release\oncrpc.lib \taco\dserver\lib\win32\release	copy    .\release\oncrpc.dll \taco\dserver\lib\win32\release
# End Special Build Tool

!ELSEIF  "$(CFG)" == "oncrpc - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /G5 /MTd /W3 /Gm /GX /ZI /Od /I "\oncrpc\win32\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_X86_" /D "_NT" /FR /YX"all_oncrpc.h" /FD /c
# SUBTRACT CPP /nologo
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /D "_DEBUG" /mktyplib203 /win32
# SUBTRACT MTL /nologo
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /subsystem:windows /dll /debug /machine:I386 /libpath:"\dserver\lib\nt4.0\debug"
# SUBTRACT LINK32 /nologo

!ENDIF 

# Begin Target

# Name "oncrpc - Win32 Release"
# Name "oncrpc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\Auth_non.c

!IF  "$(CFG)" == "oncrpc - Win32 Release"

# ADD CPP /Yu"all_oncrpc.h"

!ELSEIF  "$(CFG)" == "oncrpc - Win32 Debug"

# ADD CPP /Yc"all_oncrpc.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Auth_uni.c

!IF  "$(CFG)" == "oncrpc - Win32 Release"

# ADD CPP /Yc"all_oncrpc.h"

!ELSEIF  "$(CFG)" == "oncrpc - Win32 Debug"

# ADD CPP /Yu"all_oncrpc.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AUTHUNIX.C
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\BCOPY.C
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\Bindresv.c
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\CLNT_GEN.C
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\Clnt_per.c
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\CLNT_RAW.C
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\CLNT_SIM.C
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\Clnt_tcp.c
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\Clnt_udp.c
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\Get_myad.c
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\Getrpcen.c
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\Getrpcpo.c
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\NT.C
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\Pmap_cln.c
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\PMAP_GET.C
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\PMAP_GMA.C
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\PMAP_PR.C
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\PMAP_PRO.C
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\Pmap_rmt.c
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\PORTMAP.C
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\RPC_CALL.C
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\RPC_COMM.C
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\RPC_PROT.C
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\Svc.c
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\SVC_AUTH.C
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\Svc_autu.c
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\SVC_RAW.C
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\Svc_run.c
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\Svc_simp.c
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\Svc_tcp.c
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\Svc_udp.c
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\Xdr.c
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\Xdr_arra.c
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\XDR_FLOA.C
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\XDR_MEM.C
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\Xdr_rec.c
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\Xdr_refe.c
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# Begin Source File

SOURCE=..\XDR_STDI.C
# ADD CPP /Yu"all_oncrpc.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
