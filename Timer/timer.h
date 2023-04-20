#ifndef __TIMER_H__
#define __TIMER_H__

#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>


struct TimerDefinition;
typedef struct TimerDefinition  TimerHandle_t;

typedef void (*TimerCallbackFunction_t)(void *);


TimerHandle_t *TimerCreate(const char *name, uint64_t period, bool reload, TimerCallbackFunction_t callback);
void TimerStart(TimerHandle_t* timer);
void TimerStop(TimerHandle_t* timer);
void TimerDelele(TimerHandle_t *timer);


#endif // __TIMER_H__