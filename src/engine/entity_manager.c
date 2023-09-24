#include "engine/entity_manager.h"

static void ENTITY_MANAGER_spawn(EntityManager *manager);
extern u16 getRandomRange(u16 min, u16 max);

EntityManager ENTITY_MANAGER_init (Entity *ents, u16 entLength) {
    EntityManager newManager = { NULL, NULL, entLength, 0 };
    newManager.ents = (Entity*)malloc(entLength * sizeof(Entity));

    if (newManager.ents != NULL) {
        memcpy(newManager.ents, ents, entLength * sizeof(Entity));
    }

    return newManager;
}

void ENTITY_MANAGER_update(EntityManager *manager) {
    ENTITY_MANAGER_spawn(manager);

    for (u16 i = 0; i < manager->entLength; i++) {
        Entity *ent = &manager->ents[i];

        if (ent->alive) { 
            ent->draw(ent);
        }
    }
}

void ENTITY_MANAGER_respawn(EntityManager *manager) {
    for (u16 i = 0; i < manager->entLength; i++) {
        Entity *ent = &manager->ents[i];
        ent->reset(ent);
    }

    manager->lastEnt = NULL;
}

static void ENTITY_MANAGER_spawn(EntityManager *manager) {
    if (manager->lastEnt != NULL
        && manager->lastEnt->pos.x >= screenWidth - manager->distance) {
        return;
    }

    u16 chance = getRandomRange(1, 100);

    for (u16 i = 0; i < manager->entLength; i++) {
        Entity *ent = &manager->ents[i];

        if (!ent->alive && chance <= ent->chance) {
            ent->alive = TRUE;

            manager->lastEnt = ent;
            manager->distance = getRandomRange(screenWidth / 2, screenWidth - 96);

            break;
        }
    }
}