#include <genesis.h>

#include <res_gfx.h>
#include <res_sfx.h>
#include <res_sprites.h>

#include "engine/timer.h"
#include "engine/joytype.h"
#include "engine/graphics.h"
#include "engine/state_manager.h"
#include "engine/entity_manager.h"

#include "level.h"
#include "entities/player.h"

#define MAX_SCORE 99999

State stateGame, statePause;
EntityManager entManager;

u32 score, highScore;

static bool preStart, isEndGame;
static Player ply;

extern StateManager stateManager;
extern State stateMenu;

extern JoyType joy;
extern Timer scoreTimer, textTimer;

extern u16 paletteAll[64];

static void gameInit(void);
static void gameUpdate(void);
static void gameDestroy(void);
static void gameRestart(void);

static void pauseInit(void);
static void pauseUpdate(void);
static void pauseDestroy(void);

static void displayScore(void);
static void randomSeason(void);

void initGameStates(void) {
    stateGame.init = &gameInit;
    stateGame.update = &gameUpdate;
    stateGame.destroy = &gameDestroy;

    statePause.init = &pauseInit;
    statePause.update = &pauseUpdate;
    statePause.destroy = &pauseDestroy;
}

static void gameInit(void) {
    /* Basic init. */
    preStart = TRUE;

    VDP_setPlaneSize(32, 32, TRUE);
    GS_initScrollTiles();

    /* Init sounds. */
    XGM_setPCM(64, sfx_player_jump, sizeof(sfx_player_jump));
    XGM_setPCM(65, sfx_player_hurt, sizeof(sfx_player_hurt));
    XGM_setPCM(66, sfx_win, sizeof(sfx_win));

    /* Init level and draw interface. */
    LEVEL_init();

    randomSeason();
    displayScore();

    PAL_fadeInAll(paletteAll, 30, FALSE);

    /* Init entities. */
    Entity ents[4];

    ents[0] = ENEMY_init(&bat_sprite, (Vect2D_s16) { screenWidth, 0 }, 3, 15);
    ents[1] = BIRD_init(&eagle_sprite, (Vect2D_s16) { screenWidth, 0 }, 3, 30);
    ents[2] = OBSTACLE_init(&rock_sprite, (Vect2D_s16) { screenWidth, GROUND_Y - 16 }, 2, 65);
    ents[3] = OBSTACLE_init(&stump_sprite, (Vect2D_s16) { screenWidth, GROUND_Y - 16 }, 2, 100);

    ply = PLAYER_init(FIX16(-16), FIX16(GROUND_Y - 16), FIX16(3), &player_sprite);
    entManager = ENTITY_MANAGER_init(ents, 4);
}

static void gameUpdate(void) {
    if (preStart) {
        SPR_setAnim(ply.sprite, ANIM_RUN);
        ply.pos.x = fix16Add(ply.pos.x, FIX16(1.5));

        if (ply.pos.x == FIX16(50)) {
            preStart = FALSE; 
        }

        SPR_setPosition(ply.sprite, fix16ToInt(ply.pos.x), fix16ToInt(ply.pos.y));
        SPR_update();

        return;
    }

    GS_tileScrolling();
    
    PLAYER_draw(&ply);
    ENTITY_MANAGER_update(&entManager);

    for (u16 i = 0; i < entManager.entLength; i++) {
        Entity *ent = &entManager.ents[i];
        bool collide = PLAYER_collideEntity(&ply, ent);

        if (collide) {
            XGM_startPlayPCM(65, 15, SOUND_PCM_CH2);
            ply.alive = FALSE;

            break;
        }
    }

    if (scoreTimer.tick == scoreTimer.minTick) {
        score++;
        displayScore();
    }

    TIMER_update(&scoreTimer);
    SPR_update();

    if (JOY_INPUT(joy, BUTTON_START) || !ply.alive 
        || score == MAX_SCORE) {

        STATE_MANAGER_push(&stateManager, &statePause);
    }
}

static void gameDestroy(void) {
    VDP_setPlaneSize(64, 32, TRUE);

    VDP_clearPlane(BG_A, TRUE);
    VDP_clearPlane(BG_B, TRUE);

    GS_initScrollTiles();
    SPR_reset();

    free(entManager.ents);
}

static void gameRestart(void) {
    ply.pos.x = FIX16(-16);
    ply.pos.y = FIX16(GROUND_Y - 16);

    preStart = TRUE, isEndGame = FALSE;
    ply.alive = TRUE, ply.jumping = FALSE;

    ENTITY_MANAGER_respawn(&entManager);

    randomSeason();
    PAL_fadeInAll(paletteAll, 30, TRUE);
}

static void displayScore(void) {
    s8 scoreStr[6], highScoreStr[6];

    intToStr(score, scoreStr, 5);
    intToStr(highScore, highScoreStr, 5);

    VDP_drawTextBG(BG_A, "SCORE", 12, 0);
    VDP_drawTextBG(BG_A, scoreStr, 12, 1);

    VDP_drawTextBG(BG_A, "HI SCORE", 21, 0);
    VDP_drawTextBG(BG_A, highScoreStr, 21, 1);
}

static void randomSeason(void) {
    u16 rnd = random() % 3;

    switch (rnd) {
        case 0: // Summer
            GS_copyPalette(paletteAll, 0, 2, palette_summer_bg, 
                            palette_summer_fg);
            break;
        case 1: // Autumn
            GS_copyPalette(paletteAll, 0, 2, palette_autumn_bg,
                            palette_autumn_fg);
            break;
        case 2: // Winter
            GS_copyPalette(paletteAll, 0, 2, palette_winter_bg,
                            palette_winter_fg);
            break;   
    }
}

static void pauseInit(void) {
    if (!ply.alive || score == MAX_SCORE) {
        PAL_fadeOutAll(30, FALSE);
        PAL_setColor(15, 0xFFF);

        highScore = highScore < score ? score : highScore;

        if (score == MAX_SCORE) {
            XGM_startPlayPCM(66, 15, SOUND_PCM_CH2);

            GS_drawTextCenter(BG_B, "You got 99999 points!", 23);
            GS_drawTextCenter(BG_B, "Return to menu?", 24);

            isEndGame = TRUE;
        }

        score = 0;
        displayScore();

        return;
    }

    GS_drawTextCenter(BG_B, "GAME IS PAUSED!", 24);
}

static void pauseUpdate(void) {
    if (!ply.alive) {
        GS_drawBlinkText(&textTimer, BG_B, "GAME OVER. RETRY?", 12, 23);
    }

    if (JOY_INPUT(joy, BUTTON_START)) {
        if (!ply.alive || isEndGame) {
            gameRestart();
        }

        STATE_MANAGER_pop(&stateManager);

    } else if (JOY_INPUT(joy, BUTTON_C)) {
        PAL_fadeOutAll(30, FALSE);

        while (stateManager.top > -1) {
            STATE_MANAGER_pop(&stateManager);
        }

        STATE_MANAGER_push(&stateManager, &stateMenu);
    }
}

static void pauseDestroy(void) {
    VDP_clearTextAreaBG(BG_B, 10, 23, 25, 2);

    textTimer.tick = 0;
    scoreTimer.tick = 0;
}