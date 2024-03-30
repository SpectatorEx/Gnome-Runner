#include "engine/graphics.h"

void GS_drawTextCenter(VDPPlane plane, s8 *str, u16 top) {
    u16 left = screenWidth / 16 - strlen(str) / 2;
    VDP_drawTextBG(plane, str, left, top);
}

void GS_drawBlinkText(Timer *timer, VDPPlane plane, s8 *str, u16 x, u16 y) {
    if (!timer->tick) {
        VDP_drawTextBG(plane, str, x, y);
    } else if (timer->tick == timer->maxTick / 2) {
        VDP_clearTextBG(plane, x, y, strlen(str));
    }

    TIMER_update(timer);
}