#ifndef __AIMBOT_H__
#define __AIMBOT_H__


#include "entity.h"

/**
 * @brief creates an instance of a aim enemy entity
 * @param position the location in the world to spawn the aim enemy at
 * @returns NULL on error, or a pointer to the aim enemy
 */
Entity* aim_ent_new(Vector2D position);

#endif

