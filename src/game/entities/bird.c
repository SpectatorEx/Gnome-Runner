#include "level.h"
#include "entities/entity.h"

static void BIRD_draw(Entity *ent);
static void BIRD_reset(Entity *ent);

static s16 BIRD_getRandPosY(void);

Entity BIRD_init(const SpriteDefinition *spriteDef, s16 speed, u16 chance) {
    Entity ent = { 
        { screenWidth, BIRD_getRandPosY(), spriteDef->w, spriteDef->h },
        speed, chance, FALSE, .draw = &BIRD_draw, .reset = &BIRD_reset
    };

    ent.sprite = SPR_addSprite(spriteDef, ent.pos.x, ent.pos.y, 
        TILE_ATTR(PAL3, 0, 0, 0));

    return ent;
}

static void BIRD_draw(Entity *ent) {
    ent->pos.x -= ent->speed;

    if (ent->pos.x <= -ent->pos.w) {
        ent->reset(ent);
        return;
    }

    SPR_setPosition(ent->sprite, ent->pos.x, ent->pos.y);
}

static void BIRD_reset(Entity *ent) {
    ent->pos.x = screenWidth;
    ent->pos.y = BIRD_getRandPosY();

    ent->alive = FALSE;

    SPR_setPosition(ent->sprite, ent->pos.x, ent->pos.y);
}

static s16 BIRD_getRandPosY(void) {
    s16 spawnPos[] = { GROUND_Y - 24, GROUND_Y - 16 };
    u16 index = random() % 2;

    return spawnPos[index];
}