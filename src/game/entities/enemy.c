#include "entities/entity.h"

static u16 offset;

static void ENEMY_draw(Entity *enemy);
static void ENEMY_reset(Entity *enemy);

Entity ENEMY_init(const SpriteDefinition *spriteDef, Vect2D_s16 pos, u16 speed, u16 chance) {
    Entity enemy = {
        .pos = pos,
        .width = spriteDef->w,
        .height = spriteDef->h,
        .speed = speed,
        .chance = chance,
        .alive = FALSE,
        .draw = &ENEMY_draw,
        .reset = &ENEMY_reset,
        .sprite = SPR_addSprite(spriteDef, pos.x, pos.y, TILE_ATTR(PAL3, 0, 0, 0)),
    };

    return enemy;
}

static void ENEMY_draw(Entity *enemy) {
    enemy->pos.x -= enemy->speed;
    enemy->pos.y = sinFix16(enemy->pos.x * 4 + offset) / 4 + 130;

    if (enemy->pos.x <= -enemy->width) {
        enemy->reset(enemy);
        return;       
    }

    SPR_setPosition(enemy->sprite, enemy->pos.x, enemy->pos.y);
}

static void ENEMY_reset(Entity *enemy) {
    enemy->pos.x = screenWidth;
    enemy->alive = FALSE;

    offset += 256;

    SPR_setPosition(enemy->sprite, enemy->pos.x, enemy->pos.y); 
}