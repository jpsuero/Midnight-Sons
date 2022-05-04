#ifndef __HEALTH_PICKUP_H__
#define __HEALTH_PICKUP_H__


#include "entity.h"

/**
 * @brief creates an instance of a health entity
 * @param position the location in the world to spawn the health at
 * @returns NULL on error, or a pointer to the health
 */
Entity* health_ent_new(Vector2D position);

#endif

