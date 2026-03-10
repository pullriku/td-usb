// tdtimer.h
#pragma once

typedef struct td_context td_context_t;

int TdTimer_Start(int pCallback(td_context_t *), td_context_t *pParam, int interval);
