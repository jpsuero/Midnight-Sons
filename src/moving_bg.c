#include "simple_logger.h"
#include "moving_bg.h"

void moving_bg_think(Entity* self)
{
	//declare think variables
	const Uint8* keys;

	//get the keyboard state
	keys = SDL_GetKeyboardState(NULL); //get the keyboard for this frame

	//move player forward
	if (keys[SDL_SCANCODE_D])
	{
		self->position.x -= 4;
	}
	//move player backwards
	if (keys[SDL_SCANCODE_A])
	{
		self->position.x += 4;
	}
}


Entity* moving_bg_new(Vector2D position)
{
	Entity* ent;
	ent = entity_new();
	if (!ent)
	{
		slog("no space for the bg homie");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_image("images/backgrounds/turtles.png");
	ent->think = moving_bg_think;
	ent->draw_offset.x = -64;
	ent->draw_offset.y = -64;
	ent->rotation.x = 64;
	ent->rotation.y = 64;
	vector2d_copy(ent->position, position);
	return ent;

}