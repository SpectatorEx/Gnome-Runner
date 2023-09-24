#ifndef _LEVEL_H_
#define _LEVEL_H_

#define GROUND_Y 160
#define SCROLL_SPEED 2
#define GRAVITY FIX16(0.3)

typedef enum {
    BACKGROUND,
    GROUND, 
    GROUND_GRASS,
    GRASS,
    TREE, 
    TREE_SMALL
} TileSetName;

void LEVEL_init(void);

#endif