#ifndef __AIM_SHOOTER_H__
#define __AIM_SHOOTER_H__


#include "entity.h"

/**
 * @brief creates an instance of a shooter entity
 * @param position the location in the world to spawn the shooter at
 * @returns NULL on error, or a pointer to the shooter
 */
Entity* shooter_ent_new(Vector2D position);

#endif
