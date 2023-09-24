#include <genesis.h>
#include <res_gfx.h>

#include "engine/timer.h"
#include "engine/joytype.h"
#include "engine/graphics.h"
#include "engine/state_manager.h"

JoyType joy;
StateManager stateManager;

Timer scoreTimer, textTimer;

u16 vramIndex;
u16 paletteAll[64];

extern State stateMenu, stateGame;
extern u32 score;

static void handleInput(void);

static void initGraphics(void);
extern void initMenuStates(void);
extern void initGameStates(void);

int main(bool reset) {
    JOY_init();
    SPR_init();

    initGraphics();

    initMenuStates();
    initGameStates();

    STATE_MANAGER_init(&stateManager, 2);
    STATE_MANAGER_push(&stateManager, &stateMenu);

    textTimer = TIMER_init(0, 50);
    scoreTimer = TIMER_init(0, 10);

    while (TRUE) {
        handleInput();
        STATE_MANAGER_update(&stateManager);

        if (!reset) {
            textTimer.tick = 0, scoreTimer.tick = 0;
            score = 0;

            reset = TRUE;
        }

        SYS_doVBlankProcess();
    }

    return 0;
}

static void handleInput(void) {
    joy.preValue = joy.value;
    joy.value = JOY_readJoypad(joy.type);
}

static void initGraphics(void) {
    VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_COLUMN);

    GS_copyPalette(paletteAll, 16, 3, palette_summer_fg, 
                   palette_sprite, palette_enemy);
}