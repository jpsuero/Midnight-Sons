#ifndef __SHUMA_GORETH_H__
#define __SHUMA_GORETH_H__


#include "entity.h"

/**
 * @brief creates an instance of a SHUMA GORETH enemy entity
 * @param position the location in the world to spawn the eyeball enemy at
 * @returns NULL on error, or a pointer to the shooter
 */
Entity* shuma_ent_new(Vector2D position);

#endif