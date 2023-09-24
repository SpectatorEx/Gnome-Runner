#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <genesis.h>
#include "timer.h"

/* Palette */

void GS_copyPalette(u16 *pal, u16 index, u16 argsCount, ...);

/* Scrolling */

void GS_tileScrolling(void);
void GS_initScrollTiles(void);

/* Text */

void GS_drawTextCenter(VDPPlane plane, s8 *str, u16 top);
void GS_drawBlinkText(Timer *timer, VDPPlane plane, s8 *str, u16 x, u16 y);

#endif