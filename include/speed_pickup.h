#ifndef __SPEED_PICKUP_H__
#define __SPEED_PICKUP_H__


#include "entity.h"

/**
 * @brief creates an instance of a speed pickup entity
 * @param position the location in the world to spawn the speed pickup at
 * @returns NULL on error, or a pointer to the speed
 */
Entity* speed_ent_new(Vector2D position);

#endif



