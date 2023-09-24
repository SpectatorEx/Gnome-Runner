#include "entities/entity.h"

static void OBSTACLE_draw(Entity *obst);
static void OBSTACLE_reset(Entity *obst);

Entity OBSTACLE_init(const SpriteDefinition *spriteDef, Vect2D_s16 pos, u16 speed, u16 chance) {
    Entity obst = { 
        .pos = pos,
        .width = spriteDef->w,
        .height = spriteDef->h,
        .speed = speed,
        .chance = chance, 
        .alive = FALSE,
        .draw = &OBSTACLE_draw,
        .reset = &OBSTACLE_reset,
        .sprite = SPR_addSprite(spriteDef, pos.x, pos.y, TILE_ATTR(PAL1, 0, 0, 0)),
    };

    return obst;
}

static void OBSTACLE_draw(Entity *obst) {
    obst->pos.x -= obst->speed;  

    if (obst->pos.x <= -obst->width) {
        obst->reset(obst);
        return;
    }

    SPR_setPosition(obst->sprite, obst->pos.x, obst->pos.y);
}

static void OBSTACLE_reset(Entity *obst) {
    obst->pos.x = screenWidth;
    obst->alive = FALSE;

    SPR_setPosition(obst->sprite, obst->pos.x, obst->pos.y);
}