#include "engine/timer.h"

bool TIMER_update(Timer *timer) {
    timer->tick++;

    if (timer->tick == timer->maxTick) {
        timer->tick = 0;
        return TRUE;
    }

    return FALSE;
}

void TIMER_reset(Timer *timer, u16 amount) {
    for (u16 i = 0; i < amount; i++) {
        timer[i].tick = 0;
    }
}