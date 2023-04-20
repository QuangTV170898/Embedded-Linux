#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "timer.h"

typedef struct TimerDefinition
{
    char *name;
    int period_ms;
    int auto_reload;
    void *id;
    TimerCallbackFunction_t callback;
    int running;
    pthread_t thread;
} TIMER;

typedef TIMER Timer_t;

static void *_timer_process(void *arg)
{
    Timer_t *timer = (Timer_t *)arg;
    struct timespec sleep_time;
    sleep_time.tv_sec = timer->period_ms / 1000;
    sleep_time.tv_nsec = (timer->period_ms % 1000) * 1000000;
    while (timer->running)
    {
        nanosleep(&sleep_time, NULL);
        timer->callback(timer->name);
        if (!timer->auto_reload)
        {
            timer->running = 0;
        }
    }
    return NULL;
}

Timer_t *TimerCreate(const char *name, uint64_t period, bool reload, TimerCallbackFunction_t callback)
{
    Timer_t *timer = (Timer_t *)malloc(sizeof(Timer_t));
    if (timer == NULL)
    {
        return NULL;
    }
    timer->name = strdup(name);
    timer->period_ms = period;
    timer->auto_reload = reload;
    timer->callback = callback;
    timer->running = 0;
    return timer;
}

void TimerStart(Timer_t *timer)
{
    timer->running = 1;
    pthread_create(&timer->thread, NULL, _timer_process, timer);
}

void TimerStop(Timer_t *timer)
{
    timer->running = 0;
    pthread_join(timer->thread, NULL);
}

void TimerDelele(Timer_t *timer)
{
    printf("name: %s\n", timer->name);
    free(timer->name);
    free(timer);
    printf("name: %s\n", timer->name);
}