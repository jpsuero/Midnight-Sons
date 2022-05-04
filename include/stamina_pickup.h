#ifndef __STAMINA_PICKUP_H__
#define __STAMINA_PICKUP_H__


#include "entity.h"

/**
 * @brief creates an instance of a stamina pickup entity
 * @param position the location in the world to spawn the stamina pickup at
 * @returns NULL on error, or a pointer to the stamina
 */
Entity* stamina_ent_new(Vector2D position);

#endif


