#ifndef _STATE_MANAGER_H_
#define _STATE_MANAGER_H_

#include <genesis.h>

typedef struct {
    void (*init) (void);
    void (*update) (void);
    void (*destroy) (void);
} State;

typedef struct {
    s16 top, capacity;
    State **states;
} StateManager;

bool STATE_MANAGER_init(StateManager *manager, s16 capacity);
s16 STATE_MANAGER_push(StateManager *manager, State *state);
s16 STATE_MANAGER_pop(StateManager *manager);
void STATE_MANAGER_update(StateManager *manager);
void STATE_MANAGER_free(StateManager *manager);

#endif