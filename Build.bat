@ECHO off
SETLOCAL enabledelayedexpansion
cls
COLOR 1f

ECHO.
ECHO.
ECHO   ##############################################################
ECHO   #               ��ӭʹ�� SOUI ����������                   #
ECHO   #                                ������� 2014.10.31         #
ECHO   ##############################################################
ECHO.
ECHO.

SET cfg=
SET specs=
SET target=x86
SET selected=
rem ѡ�����汾
SET /p selected=1.ѡ�����汾[1=x86;2=x64]:
if %selected%==1 (
	SET target=x86
) else if %selected%==2 (
	SET target=x64
	SET cfg=!cfg! x64
) else (
	goto error
)

rem ѡ�񿪷�����
SET /p selected=2.ѡ�񿪷�����[1=vs2008;2=vs2010;3=vs2012;4=vs2013;5=2005]:
if %selected%==1 (
	SET specs=win32-msvc2008
	call "%VS90COMNTOOLS%..\..\VC\vcvarsall.bat" %target%
) else if %selected%==2 (
	SET specs=win32-msvc2010
	call "%VS100COMNTOOLS%..\..\VC\vcvarsall.bat" %target%
) else if %selected%==3 (
	SET specs=win32-msvc2010
	call "%VS110COMNTOOLS%..\..\VC\vcvarsall.bat" %target%
) else if %selected%==4 (
	SET specs=win32-msvc2010
	call "%VS120COMNTOOLS%..\..\VC\vcvarsall.bat" %target%
) else if %selected%==5 (
	SET specs=win32-msvc2005
	call "%VS80COMNTOOLS%..\..\VC\vcvarsall.bat" %target%
) else (
	goto error
)

rem ѡ���������
SET /p selected=3.ѡ��SOUI����ģʽ[1=ȫģ��DLL;2=ȫģ��LIB;3=�ں�LIB,���DLL(����ʹ��LUA�ű�ģ��)]:
if %selected%==1 (
	rem do nothing
) else if %selected%==2 (
	SET cfg=!cfg! LIB_ALL
) else if %selected%==3 (
	SET cfg=!cfg! CORE_LIB
) else (
	goto error
)

rem ѡ���ַ���
SET /p selected=4.ѡ���ַ���[1=UNICODE;2=MBCS]:
if %selected%==1 (
	rem do nothing
) else if %selected%==2 (
	SET cfg=!cfg! MBCS
) else (
	goto error
)

rem ѡ��WCHAR֧��
SET /p selected=5.��WCHAR��Ϊ�ڽ�����[1=��;2=��]:
if %selected%==1 (
	rem do nothing
) else if %selected%==2 (
	SET cfg=!cfg! DISABLE_WCHAR
) else (
	goto error
)

rem CRT
SET /p selected=6.ѡ��CRT����ģʽ[1=��̬����(MT);2=��̬����(MD)]:
if %selected%==1 (
	SET cfg=!cfg! USING_MT
) else if %selected%==2 (
	rem do nothing
) else (
	goto error
)

rem Ϊrelease�汾���ɵ�����Ϣ
SET /p selected=7.�Ƿ�Ϊrelease�汾���ɵ�����Ϣ[1=����;2=������]:
if %selected%==1 (
	SET cfg=!cfg! CAN_DEBUG
) else if %selected%==2 (
	rem do nothing
) else (
	goto error
)

rem �����������

tools\qmake -tp vc -r -spec .\tools\mkspecs\%specs% "CONFIG += %cfg%"

SET /p selected=open[o], compile[c] "soui.sln" or quit(q) [o,c or q]?
if "%selected%" == "o" (
	soui.sln
) else if "%selected%" == "c" (
	call devenv soui.sln /Clean Debug
	call devenv soui.sln /build Debug
	call devenv soui.sln /Clean Release
	call devenv soui.sln /build Release
) else (
	goto final
)

goto final

:error
	ECHO ѡ�����������ѡ��

:final


















rem pause