#ifndef _LEVEL_H_
#define _LEVEL_H_

#define GROUND_Y 160

typedef enum {
    BG,
    GROUND, 
    GROUND_GRASS,
    GRASS,
    TREE, 
    TREE_SMALL
} TileSetName;

void LEVEL_init(void);
void LEVEL_draw(void);

#endif