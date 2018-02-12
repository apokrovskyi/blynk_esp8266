#ifndef ESP_MISSING_H_
#define ESP_MISSING_H_

#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>

#include <mem.h>
/*
void *pvPortMalloc(size_t xWantedSize, const char* file, int line) __attribute__((malloc, alloc_size(1)));
void *pvPortRealloc(void* ptr, size_t xWantedSize, const char* file, int line) __attribute__((alloc_size(2)));
void vPortFree(void *ptr, const char* file, int line);
*/

#include <osapi.h>
void ets_timer_disarm(ETSTimer *ptimer);
void ets_timer_setfn(ETSTimer *ptimer, ETSTimerFunc *pfunction, void *parg);
void ets_timer_arm_new(ETSTimer *ptimer,uint32_t milliseconds, bool repeat_flag, bool);

int ets_vsprintf(char *str, const char *format, va_list argptr);
int ets_vsnprintf(char *buffer, size_t sizeOfBuffer, const char *format, va_list argptr);

#define vsprintf ets_vsprintf
#define vsnprintf ets_vsnprintf

#endif
