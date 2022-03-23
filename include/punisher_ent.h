#ifndef __PUNISHER_ENT_H__
#define __PUNISHER_ENT_H__

#include "entity.h"
/**
*@brief creates an instance of the punisher player entity
*@param position the location in the world to spawn magik at
*@returns NULL on error, or a pointer to magik
*/

Entity* punisher_new(Vector2D position);

#endif 