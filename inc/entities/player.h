#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <genesis.h>

#include "entity.h"
#include "engine/animtype.h"

typedef struct {
    Vect2D_f16 pos;
    u16 width, height;
    u16 crouch;
    f16 velocity, jumpForce;
    bool alive, jumping;
    Sprite *sprite;
} Player;

Player PLAYER_init(f16 x, f16 y, f16 jumpForce, const SpriteDefinition *spriteDef);

void PLAYER_draw(Player *ply);
bool PLAYER_collideEntity(Player *ply, Entity *ent);

#endif