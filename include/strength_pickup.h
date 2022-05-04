#ifndef __STRENGTH_PICKUP_H__
#define __STRENGTH_PICKUP_H__


#include "entity.h"

/**
 * @brief creates an instance of a strength pickup entity
 * @param position the location in the world to spawn the strength pickup at
 * @returns NULL on error, or a pointer to the strength
 */
Entity* strength_ent_new(Vector2D position);

#endif
