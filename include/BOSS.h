#ifndef __BOSS_H__
#define __BOSS_H__


#include "entity.h"

/**
 * @brief creates an instance of a boss entity
 * @param position the location in the world to spawn the boss at
 * @returns NULL on error, or a pointer to the boss
 */
Entity* boss_ent_new(Vector2D position);

#endif
