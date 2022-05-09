#ifndef __HYDRANT_H__
#define __HYDRANT_H__


#include "entity.h"

/**
 * @brief creates an instance of a hydrant entity
 * @param position the location in the world to spawn the hydrant at
 * @returns NULL on error, or a pointer to the hydrant
 */
Entity* hydrant_ent_new(Vector2D position);

#endif
