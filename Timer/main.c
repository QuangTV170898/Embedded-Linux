#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include "timer.h"

void timer_callback_0(void *arg)
{
    char *name = (char *)arg;
    printf("Timer #%s callback\n", name);
}


int main()
{
    TimerHandle_t *timer_0 = TimerCreate("Timer0", 1000, true, timer_callback_0);
    TimerStart(timer_0);

    sleep(10);
    TimerStop(timer_0);
    TimerDelele(timer_0);

    return 0;
}
