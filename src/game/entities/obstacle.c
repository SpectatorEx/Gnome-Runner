#include "level.h"
#include "entities/entity.h"

static void OBSTACLE_draw(Entity *ent);
static void OBSTACLE_reset(Entity *ent);

Entity OBSTACLE_init(const SpriteDefinition *spriteDef, s16 speed, u16 chance) {
    Entity ent = {
        { screenWidth, GROUND_Y - 16, spriteDef->w, spriteDef->h },
        speed, chance, FALSE, .draw = &OBSTACLE_draw, .reset = &OBSTACLE_reset
    };

    ent.sprite = SPR_addSprite(spriteDef, ent.pos.x, ent.pos.y, 
        TILE_ATTR(PAL1, 0, 0, 0));

    return ent;
}

static void OBSTACLE_draw(Entity *ent) {
    ent->pos.x -= ent->speed;  

    if (ent->pos.x <= -ent->pos.w) {
        ent->reset(ent);
        return;
    }

    SPR_setPosition(ent->sprite, ent->pos.x, ent->pos.y);
}

static void OBSTACLE_reset(Entity *ent) {
    ent->pos.x = screenWidth;
    ent->alive = FALSE;

    SPR_setPosition(ent->sprite, ent->pos.x, ent->pos.y);
}