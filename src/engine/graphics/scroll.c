#include "engine/graphics.h"

static s16 offsetTileA[28];
static s16 offsetTileB[20];
static f16 offsetTileBF[20];

void GS_tileScrolling(void) {
    /* 'PLANE A' tile scrolling. */

    VDP_setHorizontalScrollTile(BG_A, 2, offsetTileA, 28, CPU);

    for (u16 i = 2; i < 28; i++) {
        offsetTileA[i] = (offsetTileA[i] - 2) % 256;
    }

    /* 'PLANE B' tile scrolling. */
    
    VDP_setHorizontalScrollTile(BG_B, 0, offsetTileB, 20, CPU);

    for (u16 i = 0; i < 20; i++) {
        if (i < 6) {
            offsetTileBF[i] += FIX16(-0.5);
        } else if (i < 15) {
            offsetTileBF[i] += FIX16(-0.3);
        } else if (i < 20) {
            offsetTileBF[i] += FIX16(-1);
        }

        if (offsetTileBF[i] <= FIX16(-256)) {
            offsetTileBF[i] = FIX16(0);
        }

        offsetTileB[i] = fix16ToInt(offsetTileBF[i]);
    }
}

void GS_initScrollTiles(void) {
    for (u16 i = 0; i < 28; i++) {
        offsetTileA[i] = 0;
    }

    for (u16 i = 0; i < 20; i++) {
        offsetTileB[i] = 0;
        offsetTileBF[i] = FIX16(0);
    }

    VDP_setHorizontalScrollTile(BG_A, 2, offsetTileA, 28, CPU);
    VDP_setHorizontalScrollTile(BG_B, 0, offsetTileB, 20, CPU);
}