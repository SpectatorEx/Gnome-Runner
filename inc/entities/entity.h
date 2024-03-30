#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <genesis.h>

typedef struct Entity {
    Box pos;
    s16 speed;
    u16 chance;
    bool alive;
    Sprite *sprite;

    void (*draw) (struct Entity *ent);
    void (*reset) (struct Entity *ent);   
} Entity;

Entity BIRD_init(const SpriteDefinition *spriteDef, s16 speed, u16 chance);
Entity ENEMY_init(const SpriteDefinition *spriteDef, s16 speed, u16 chance);
Entity OBSTACLE_init(const SpriteDefinition *spriteDef, s16 speed, u16 chance);

#endif