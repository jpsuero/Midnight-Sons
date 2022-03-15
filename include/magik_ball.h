#ifndef __MAGIK_BALL_H__
#define __MAGIK_BALL_H__

#include "entity.h"
/**
*@brief creates an instance of the magik ball projectile entity
*@param position the location in the world to spawn ball at
*@returns NULL on error, or a pointer to magik
*/

Entity* magik_ball_new(Vector2D position);

#endif 
