#include "engine/timer.h"

Timer TIMER_init(u32 minTick, u32 maxTick) {
    Timer newTimer = { 0, minTick, maxTick, FALSE };

    if (minTick >= maxTick || maxTick <= minTick) {
        newTimer.minTick = 0;
        newTimer.maxTick = 0;

        newTimer.infinite = TRUE;
    }

    return newTimer;
}

void TIMER_update(Timer *timer) {
    timer->tick++;

    if (!timer->infinite && timer->tick == timer->maxTick) {
        timer->tick = 0;
    }
}