#ifndef _TIMER_EX_H_
#define _TIMER_EX_H_

#include <genesis.h>

typedef struct {
    u32 tick, maxTick;
} Timer;

bool TIMER_update(Timer *timer);
void TIMER_reset(Timer *timer, u16 amount);

#endif