#ifndef __CHAIR_BREAKABLE_H__
#define __CHAIR_BREAKABLE_H__


#include "entity.h"

/**
 * @brief creates an instance of a bench entity
 * @param position the location in the world to spawn the bench at
 * @returns NULL on error, or a pointer to the bench
 */
Entity* chair_ent_new(Vector2D position);

#endif
