#ifndef __SKULL_ENT_H__
#define __SKULL_ENT_H__


#include "entity.h"

/**
 * @brief creates an instance of a skull entity
 * @param position the location in the world to spawn the skull at
 * @returns NULL on error, or a pointer to the skull
 */
Entity *skull_ent_new(Vector2D position);

#endif
