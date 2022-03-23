#ifndef __MOVING_BG_H__
#define __MOVING_BG_H__

#include "entity.h"
/**
*@brief creates an instance of the background player entity
*@param position the location in the world to spawn magik at
*@returns NULL on error, or a pointer to magik
*/

Entity* moving_bg_new(Vector2D position);

#endif 
