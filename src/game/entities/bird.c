#include "level.h"
#include "entities/entity.h"

static void BIRD_draw(Entity *bird);
static void BIRD_reset(Entity *bird);

static u16 BIRD_getRandomPosY(void);

Entity BIRD_init(const SpriteDefinition *spriteDef, Vect2D_s16 pos, u16 speed, u16 chance) {
    Entity bird = { 
        .pos = pos,
        .width = spriteDef->w,
        .height = spriteDef->h,
        .speed = speed,
        .chance = chance, 
        .alive = FALSE,
        .draw = &BIRD_draw,
        .reset = &BIRD_reset,
        .sprite = SPR_addSprite(spriteDef, pos.x, pos.y, TILE_ATTR(PAL3, 0, 0, 0)),
    };

    bird.pos.y = BIRD_getRandomPosY();

    return bird;
}

static void BIRD_draw(Entity *bird) {
    bird->pos.x -= bird->speed;

    if (bird->pos.x <= -bird->width) {
        bird->reset(bird);
        return;
    }

    SPR_setPosition(bird->sprite, bird->pos.x, bird->pos.y);
}

static void BIRD_reset(Entity *bird) {
    bird->pos.x = screenWidth;
    bird->pos.y = BIRD_getRandomPosY();

    bird->alive = FALSE;

    SPR_setPosition(bird->sprite, bird->pos.x, bird->pos.y);
}

static u16 BIRD_getRandomPosY(void) {
    u16 spawnPos[] = { GROUND_Y - 24, GROUND_Y - 16 };
    u16 index = random() % 2;

    return spawnPos[index];
}