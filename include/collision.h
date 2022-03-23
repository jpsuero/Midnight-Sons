#ifndef __COLLISION_H__
#define __COLLISION_H__


#include "entity.h"

/**
 * @brief creates an instance of a collision entity
 * @param position the location in the world to spawn the skull at
 * @returns NULL on error, or a pointer to the skull
 */

int collision_check(Entity* player, Entity* enemy);

#endif // !__COLLISION_H__

