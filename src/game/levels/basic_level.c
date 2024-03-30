#include <genesis.h>

#include <res_gfx.h>
#include <res_tiles.h>

#include "level.h"

static u16 vramTileSet[6];
static bool vramIndexLoaded;

extern u16 vramIndex;

static void initVramIndex(void);

void LEVEL_init(void) {
    if (!vramIndexLoaded) {
        initVramIndex();
        vramIndexLoaded = TRUE;
    }

    /* Loads background map. */
    
    VDP_loadTileSet(bgmap.tileset, vramTileSet[BG], DMA);

    /* Loads ground data. */

    VDP_loadTileSet(ground_image.tileset, vramTileSet[GROUND], DMA);
    VDP_loadTileSet(ground_grass_image.tileset, vramTileSet[GROUND_GRASS], DMA);

    /* Loads trees and grass data. */

    VDP_loadTileSet(long_grass_image.tileset, vramTileSet[GRASS], DMA);
    VDP_loadTileSet(tree_image.tileset, vramTileSet[TREE], DMA);
    VDP_loadTileSet(tree_small_image.tileset, vramTileSet[TREE_SMALL], DMA);
}

void LEVEL_draw(void) {
    /* Draws background map. */

    VDP_setTileMapEx(BG_B, bgmap.tilemap, 
        TILE_ATTR_FULL(PAL0, 0, 0, 0, vramTileSet[BG]), 
        0, 0, 0, 0, 32, 28, DMA);

    /* Draws ground. */

    for (u16 x = 0; x < 32; x += 2) {
        VDP_fillTileMapRectInc(BG_A, 
            TILE_ATTR_FULL(PAL1, 0, 0, 0, vramTileSet[GROUND_GRASS]), 
            x, 20, 2, 2);
    }

    for (u16 y = 0; y < 6; y += 2) {
        for (u16 x = 0; x < 32; x += 2) {
            VDP_fillTileMapRectInc(BG_A, 
                TILE_ATTR_FULL(PAL1, 0, 0, 0, vramTileSet[GROUND]), 
                x, y + 22, 2, 2);
        }
    }

    /* Draws trees and grass. */

    VDP_fillTileMapRectInc(BG_A, 
        TILE_ATTR_FULL(PAL1, 1, 0, 0, vramTileSet[GRASS]), 15, 18, 2, 2);
    VDP_fillTileMapRectInc(BG_A, 
        TILE_ATTR_FULL(PAL1, 1, 0, 0, vramTileSet[GRASS]), 32, 18, 2, 2);

    VDP_fillTileMapRectInc(BG_A, 
        TILE_ATTR_FULL(PAL1, 0, 0, 0, vramTileSet[TREE]), 20, 4, 8, 16);
    VDP_fillTileMapRectInc(BG_A, 
        TILE_ATTR_FULL(PAL1, 0, 0, 0, vramTileSet[TREE_SMALL]), 4, 12, 8, 8);
}

static void initVramIndex(void) {
    vramTileSet[BG] = vramIndex;
    vramIndex += bgmap.tileset->numTile;

    for (u16 i = 0; i < 3; i++) {  
        vramTileSet[i + 1] = vramIndex;
        vramIndex += ground_image.tileset->numTile;
    }

    vramTileSet[TREE] = vramIndex;
    vramIndex += tree_image.tileset->numTile;

    vramTileSet[TREE_SMALL] = vramIndex;
    vramIndex += tree_small_image.tileset->numTile;
}