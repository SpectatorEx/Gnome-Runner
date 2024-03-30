#include <genesis.h>
#include <res_gfx.h>

#include "engine/timer.h"
#include "engine/joytype.h"
#include "engine/graphics.h"
#include "engine/state_manager.h"

JoyType joy;
StateManager stateManager;

Timer timers[2];

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

    timers[0] = (Timer) { 0, 50 };  // Text delay.
    timers[1] = (Timer) { 0, 10 };  // Score delay.

    while (TRUE) {
        STATE_MANAGER_update(&stateManager);
        handleInput();

        if (!reset) {
            TIMER_reset(timers, 2);

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