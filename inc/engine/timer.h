#ifndef _TIMER_EXT_H_
#define _TIMER_EXT_H_

#include <genesis.h>

typedef struct {
    u32 tick;
    u32 minTick, maxTick;
    bool infinite;
} Timer;

Timer TIMER_init(u32 minTick, u32 maxTick);
void TIMER_update(Timer *timer);

#endif