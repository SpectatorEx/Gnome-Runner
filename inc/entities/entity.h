#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <genesis.h>

typedef struct Entity {
    Vect2D_s16 pos;
    u16 width, height;
    u16 chance;
    u16 speed;
    bool alive;
    Sprite *sprite;

    void (*draw) (struct Entity *ent);
    void (*reset) (struct Entity *ent);   
} Entity;

Entity BIRD_init(const SpriteDefinition *spriteDef, Vect2D_s16 pos, u16 speed, u16 chance);
Entity ENEMY_init(const SpriteDefinition *spriteDef, Vect2D_s16 pos, u16 speed, u16 chance);
Entity OBSTACLE_init(const SpriteDefinition *spriteDef, Vect2D_s16 pos, u16 speed, u16 chance);

#endif