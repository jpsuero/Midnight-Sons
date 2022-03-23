#include "simple_logger.h"
#include "collision.h"
#include "gf2d_draw.h"

int collision_check(Entity* player, Entity* enemy)
{
	if (enemy->hitbox.x >= player->hitbox.x && enemy->hitbox.x <= player->hitbox.x + player->hitbox.w)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}