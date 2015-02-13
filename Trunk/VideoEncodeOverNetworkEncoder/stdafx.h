// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <process.h>
#include <atlimage.h>
#include <assert.h>

#include "IniReader.h"
#include "PreciseTimer.h"
#include "zlib.h"
#include "ClientNetwork.h"

void MyMain();

struct GlobalStore
{
	HWND	WndSrc;
	int		FPSLimit;
	char	*CapturePCIP;
	char	*CapturePCPort;
	int		MaxPacketSize;
	int		ThreadIsRunning;
	int		ShowStatistics;
};

extern GlobalStore GlobalData;

#define RGB_BYTE_COUNT 4