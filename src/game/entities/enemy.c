#include "entities/entity.h"

static u16 offset;

static void ENEMY_draw(Entity *ent);
static void ENEMY_reset(Entity *ent);

Entity ENEMY_init(const SpriteDefinition *spriteDef, s16 speed, u16 chance) {
    Entity ent = {
        { screenWidth, 0, spriteDef->w, spriteDef->h },
        speed, chance, FALSE, .draw = &ENEMY_draw, .reset = &ENEMY_reset
    };

    ent.sprite = SPR_addSprite(spriteDef, ent.pos.x, ent.pos.y, 
        TILE_ATTR(PAL3, 0, 0, 0));

    return ent;
}

static void ENEMY_draw(Entity *ent) {
    ent->pos.x -= ent->speed;
    ent->pos.y = sinFix16(ent->pos.x * 4 + offset) / 4 + 130;

    if (ent->pos.x <= -ent->pos.w) {
        ent->reset(ent);
        return;       
    }

    SPR_setPosition(ent->sprite, ent->pos.x, ent->pos.y);
}

static void ENEMY_reset(Entity *ent) {
    ent->pos.x = screenWidth;
    ent->alive = FALSE;

    offset += 256;

    SPR_setPosition(ent->sprite, ent->pos.x, ent->pos.y); 
}