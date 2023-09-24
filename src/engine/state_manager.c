#include "engine/state_manager.h"

bool STATE_MANAGER_init(StateManager *manager, s16 capacity) {
    manager->states = (State**)malloc(capacity * sizeof(State*));

    if (manager->states == NULL) {
        return 0;
    }

    manager->top = -1;
    manager->capacity = capacity;

    return 1;
}

s16 STATE_MANAGER_push(StateManager *manager, State *state) {
    if (manager->top + 1 == manager->capacity) {
        return 0;
    }

    if (state->init != NULL) {
        state->init();
    }

    s16 index = ++manager->top;
    manager->states[index] = state;

    return manager->top;
}

s16 STATE_MANAGER_pop(StateManager *manager) {
    if (manager->top == -1) {
        return 0;
    }

    s16 index = manager->top;
    State *state = manager->states[index];

    if (state->destroy != NULL) {
        state->destroy();
    }

    manager->states[index] = NULL;
    manager->top--;

    return manager->top;
}

void STATE_MANAGER_update(StateManager *manager) {
    s16 index = manager->top;
    State *state = manager->states[index];

    if (state->update != NULL) {
        state->update();
    }
}

void STATE_MANAGER_free(StateManager *manager) {
    while (manager->top > -1) {
        STATE_MANAGER_pop(manager);
    }

    free(manager->states);
}