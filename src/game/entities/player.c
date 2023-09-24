#include "level.h"

#include "engine/joytype.h"
#include "entities/player.h"

extern JoyType joy;

static void PLAYER_handleInput(Player *ply);

Player PLAYER_init(f16 x, f16 y, f16 jumpForce, const SpriteDefinition *spriteDef) {
    Player newPlayer = { 
        .pos = { x, y },
        .width = spriteDef->w, 
        .height = spriteDef->h,
        .jumpForce = jumpForce,
        .alive = TRUE,
        .sprite = SPR_addSprite(spriteDef, fix16ToInt(x), fix16ToInt(y), 
                                TILE_ATTR(PAL2, 0, 0, 0))
    };

    return newPlayer;
}

void PLAYER_draw(Player *ply) {
    PLAYER_handleInput(ply);
    
    if (ply->jumping) {
        ply->pos.y = fix16Sub(ply->pos.y, ply->velocity);
        ply->velocity = fix16Sub(ply->velocity, GRAVITY);

        if (fix16ToInt(ply->pos.y) + ply->height >= GROUND_Y) {
            ply->velocity = FIX16(0);
            ply->pos.y = intToFix16(GROUND_Y - ply->height);

            ply->jumping = FALSE;

            SPR_setAnim(ply->sprite, ANIM_RUN);
        }
    }

    SPR_setPosition(ply->sprite, fix16ToInt(ply->pos.x), fix16ToInt(ply->pos.y));   
}

bool PLAYER_collideEntity(Player *ply, Entity *ent) {
    s16 destPosX = fix16ToInt(ply->pos.x);
    s16 destPosY = fix16ToInt(ply->pos.y) + ply->crouch;

    if (destPosX < ent->pos.x + ent->width - 5
        && destPosX + ply->width - 5 > ent->pos.x
        && destPosY < ent->pos.y + ent->height - 2
        && destPosY + ply->height - 5 > ent->pos.y)
    {
        return TRUE;
    }

    return FALSE;
}

static void PLAYER_handleInput(Player *ply) {
    if ((joy.value & BUTTON_LEFT) && ply->pos.x > FIX16(0)) {
        ply->pos.x = fix16Sub(ply->pos.x, FIX16(1));

    } else if ((joy.value & BUTTON_RIGHT) 
        && ply->pos.x < FIX16(screenWidth - ply->width)) {

        ply->pos.x = fix16Add(ply->pos.x, FIX16(1));
    }

    if (JOY_INPUT(joy, BUTTON_A) && !ply->jumping) {
        XGM_startPlayPCM(64, 14, SOUND_PCM_CH2);
        SPR_setAnim(ply->sprite, ANIM_JUMP);

        ply->velocity = ply->jumpForce;
        ply->jumping = TRUE;
    }

    if ((joy.value & BUTTON_DOWN) && !ply->jumping) {
        SPR_setAnim(ply->sprite, ANIM_SIT);
        ply->crouch = 10;   
    } else if (ply->crouch > 0) {
        SPR_setAnim(ply->sprite, ANIM_RUN);
        ply->crouch = 0;
    }
}