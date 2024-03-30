#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include <genesis.h>
#include "entities/entity.h"

typedef struct {
    Entity *ents, *lastEnt;
    u16 entCount, distance;
} EntityManager;

EntityManager ENTITY_MANAGER_init(Entity *ents, u16 entLength);

void ENTITY_MANAGER_update(EntityManager *inspector);
void ENTITY_MANAGER_reset(EntityManager *inspector);

#endif