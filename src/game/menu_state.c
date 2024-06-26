#include <genesis.h>

#include <res_gfx.h>

#include "engine/timer.h"
#include "engine/joytype.h"
#include "engine/graphics.h"
#include "engine/state_manager.h"

State stateMenu, stateControl;

extern u16 vramIndex;
extern u16 paletteAll[64];

extern JoyType joy;
extern Timer timers[2];

extern StateManager stateManager;
extern State stateGame;

static void menuInit(void);
static void menuUpdate(void);
static void menuDraw(void);

static void controlInit(void);
static void controlUpdate(void);

void initMenuStates(void) {
    stateMenu.init = &menuInit;
    stateMenu.update = &menuUpdate;

    stateControl.init = &controlInit;
    stateControl.update = &controlUpdate;
}

static void menuInit(void) {
    vramIndex = TILE_USER_INDEX;
    menuDraw();
}

static void menuUpdate(void) {
    GS_drawBlinkText(&timers[0], BG_A, "> START <", 15, 18);

    if (JOY_INPUT(joy, BUTTON_START) 
        || JOY_INPUT(joy, BUTTON_C)) {

        PAL_fadeOutAll(30, FALSE);
        VDP_clearPlane(BG_A, TRUE);

        timers[0].tick = 0;
    }

    if (JOY_INPUT(joy, BUTTON_START)) {
        STATE_MANAGER_pop(&stateManager);
        STATE_MANAGER_push(&stateManager, &stateGame);

    } else if (JOY_INPUT(joy, BUTTON_C)) {
        STATE_MANAGER_push(&stateManager, &stateControl);
    }
}

static void menuDraw(void) {
    PAL_setColor(15, 0xFFF);
    PAL_setColors(16, &paletteAll[16], 16, DMA);

    VDP_drawImageEx(BG_A, &main_logo, 
        TILE_ATTR_FULL(PAL1, 0, 0, 0, vramIndex), 9, 4, FALSE, DMA);

    VDP_drawTextBG(BG_A, "Controls - C.", 1, 25);
    VDP_drawTextBG(BG_A, "Authors: Spectator & Yurakola.", 1, 26);
}

static void controlInit(void) {
    s8 keys[][30] = { 
        "[A]       | Jump.",
        "[C]       | Return.",
        "[Arrows]  | Move / Crouch.",
        "[Start]   | Launch / Pause."
    };

    PAL_setColor(15, 0xFFF);
    VDP_drawTextBG(BG_A, "CONTROLS", 16, 1);

    for (u16 i = 0; i < 4; i++) {
        VDP_drawTextBG(BG_A, keys[i], 9, 6 + i);
    }
}

static void controlUpdate(void) {
    if (JOY_INPUT(joy, BUTTON_C)) {
        PAL_fadeOut(0, 15, 30, FALSE);

        VDP_clearPlane(BG_A, TRUE);
        STATE_MANAGER_pop(&stateManager);

        menuDraw();
    }
}