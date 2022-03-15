#include "simple_logger.h"
#include "magik_ball.h"

void magik_ball_think(Entity* self)
{
	//declare think variables
	Vector2D direction;
	int mx, my;
	float angle;
	const Uint8* keys;
	//return if not magik ent
	if (!self)return;
	self->frame = (self->frame + 0.1);
	//set frame length
	if (self->frame >= 6)self->frame = 0;


	//get the keyboard state
	keys = SDL_GetKeyboardState(NULL); //get the keyboard for this frame


}

Entity* magik_ball_new(Vector2D position)
{
	Entity* ent;
	ent = entity_new();
	if (!ent)
	{
		slog("no space for magik_ball homie");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_all("images/magik_ball.png", 66, 84, 6);
	ent->think = magik_ball_think;
	ent->draw_offset.x = -64;
	ent->draw_offset.y = -64;
	ent->rotation.x = 64;
	ent->rotation.y = 64;
	ent->draw_scale.x = 1;
	ent->draw_scale.y = 1;
	vector2d_copy(ent->position, position);
	return ent;

}