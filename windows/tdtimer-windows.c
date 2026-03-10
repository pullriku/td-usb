// tdtimer-windows.c

#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "..\tdtimer.h"

#pragma comment (lib, "winmm.lib")

static int(*pUserHandler)(td_context_t *);
static td_context_t *pUserParam;

static void CALLBACK MyTimerCallback(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	pUserHandler(pUserParam);
}

int TdTimer_Start(int pCallback(td_context_t *), td_context_t *pParam, int Interval)
{
	pUserHandler = pCallback;
	pUserParam = pParam;

	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	timeSetEvent(Interval, 10, (LPTIMECALLBACK)MyTimerCallback, 0, TIME_PERIODIC);
	WaitForSingleObject(hEvent, INFINITE);
	return 0;
}
