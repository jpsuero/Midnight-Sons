#ifndef __PORTAL_H__
#define __PORTAL_H__


#include "entity.h"

/**
 * @brief creates an instance of a portal entity
 * @param position the location in the world to spawn the portal entity
 * @returns NULL on error, or a pointer to the portal
 */
Entity* portal_ent_new(Vector2D position);

#endif
