#include "level.h"

#include "engine/joytype.h"
#include "entities/player.h"

extern JoyType joy;

static void PLAYER_input(Player *ply);

Player PLAYER_init(f16 x, f16 y, f16 jumpForce, const SpriteDefinition *spriteDef) {
    Player ply = { 
        { x, y }, spriteDef->w, spriteDef->h, 
        0, 0, jumpForce, TRUE, FALSE, NULL
    };

    ply.sprite = SPR_addSprite(spriteDef, fix16ToInt(x), fix16ToInt(y), 
        TILE_ATTR(PAL2, 0, 0, 0));

    return ply;
}

void PLAYER_draw(Player *ply) {
    PLAYER_input(ply);

    if (ply->jumping) {
        ply->pos.y -= ply->velocity;
        ply->velocity -= FIX16(0.3);

        if (fix16ToInt(ply->pos.y) + ply->height >= GROUND_Y) {
            ply->velocity = FIX16(0);
            ply->pos.y = intToFix16(GROUND_Y - ply->height);

            ply->jumping = FALSE;

            SPR_setAnim(ply->sprite, ANIM_RUN);
        }
    }

    SPR_setPosition(ply->sprite, fix16ToInt(ply->pos.x), fix16ToInt(ply->pos.y));   
}

void PLAYER_reset(Player *ply) {
    ply->pos.x = FIX16(-16);
    ply->pos.y = FIX16(GROUND_Y - 16);

    ply->alive = TRUE, ply->jumping = FALSE;
}

bool PLAYER_collide(Player *ply, Box *pos) {
    s16 destPosX = fix16ToInt(ply->pos.x);
    s16 destPosY = fix16ToInt(ply->pos.y) + ply->crouch;

    if (destPosX < pos->x + pos->w - 5
        && destPosX + ply->width - 5 > pos->x
        && destPosY < pos->y + pos->h - 2
        && destPosY + ply->height - 5 > pos->y) {

        return TRUE;
    }

    return FALSE;
}

static void PLAYER_input(Player *ply) {
    if ((joy.value & BUTTON_LEFT) && ply->pos.x > FIX16(0)) {
        ply->pos.x -= FIX16(1);
    } else if ((joy.value & BUTTON_RIGHT) 
        && ply->pos.x < FIX16(screenWidth - ply->width)) {
        ply->pos.x += FIX16(1);
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