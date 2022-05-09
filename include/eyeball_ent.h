#ifndef __EYEBALL_ENT_H__
#define __EYEBALL_ENT_H__


#include "entity.h"

/**
 * @brief creates an instance of a eyeball enemy entity
 * @param position the location in the world to spawn the eyeball enemy at
 * @returns NULL on error, or a pointer to the shooter
 */
Entity* eyeball_ent_new(Vector2D position);

#endif

