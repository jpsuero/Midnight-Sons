#include "simple_logger.h"
#include "venom_ent.h"

void magik_think(Entity* self)
{
	//declare think variables
	float angle;
	const Uint8* keys;
	//return if not magik ent
	if (!self)return;
	self->frame = (self->frame + 0.1);
	//set frame limit
	if (self->frame >= self->frame_limit)self->frame = 0;

	//animator
	if (self->player_state == 1)
	{
		self->frame_limit = 13;
	}
	else if (self->player_state == 2)
	{
		self->frame_limit = 10;
	}
	else if (self->player_state == 3)
	{
		self->frame_limit = 3;
	}
	else if (self->player_state == 4)
	{
		self->frame_limit = 3;
	}
	else if (self->player_state == 5)
	{
		self->frame_limit = 7;
	}
	else if (self->player_state == 6)
	{
		self->frame_limit = 18;
	}
	else if (self->player_state == 7)
	{
		self->frame_limit = 8;
	}


	//get the keyboard state
	keys = SDL_GetKeyboardState(NULL); //get the keyboard for this frame

	//move player forward
	if (keys[SDL_SCANCODE_D])
	{
		//self->frame_limit = 6;
		self->player_state = 2;
		self->position.x += 3;
		self->sprite = gf2d_sprite_load_all("images/venom_walk.png", 150, 156, 10);
		slog("moving forward");
	}
	//move player backwards
	if (keys[SDL_SCANCODE_A])
	{
		//self->frame_limit = 6;

		self->player_state = 2;
		self->position.x -= 3;
		self->sprite = gf2d_sprite_load_all("images/venom_walk.png", 150, 156, 10);

	}
	//move player up
	if (keys[SDL_SCANCODE_W])
	{
		//self->frame_limit = 6;
		self->player_state = 2;
		self->position.y -= 3;
		self->sprite = gf2d_sprite_load_all("images/venom_walk.png", 150, 156, 10);
	}
	//move player down
	if (keys[SDL_SCANCODE_S])
	{
		//self->frame_limit = 6;
		self->player_state = 2;
		self->position.y += 3;
		self->sprite = gf2d_sprite_load_all("images/venom_walk.png", 150, 156, 10);
	}

	//player jump 
	if (keys[SDL_SCANCODE_SPACE])
	{
		//self->frame_limit = 3;
		self->player_state = 3;
		self->sprite = gf2d_sprite_load_all("images/Gambit_jump.png", 93, 106, 3);

	}

	if (keys[SDL_SCANCODE_E])
	{
		self->player_state = 4;
		self->sprite = gf2d_sprite_load_all("images/venom_attack1.png", 212, 131, 3);

	}
	if (keys[SDL_SCANCODE_Q])
	{
		self->player_state = 5;
		self->sprite = gf2d_sprite_load_all("images/venom_attack2.png", 165.14, 220, 7);
	}
	if (keys[SDL_SCANCODE_F])
	{
		self->player_state = 6;
		self->sprite = gf2d_sprite_load_all("images/venom_attack4.png", 246, 191, 18);
	}
	if (keys[SDL_SCANCODE_G])
	{
		self->player_state = 7;
		self->sprite = gf2d_sprite_load_all("images/venom_attack3.png", 311, 161, 8);
	}


	if (!keys[SDL_SCANCODE_S] && !keys[SDL_SCANCODE_W] && !keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_SPACE] && !keys[SDL_SCANCODE_E] && !keys[SDL_SCANCODE_Q] && !keys[SDL_SCANCODE_F] && !keys[SDL_SCANCODE_G])
	{
		self->player_state = 1;
		self->frame_limit = 13;
		self->sprite = gf2d_sprite_load_all("images/venom_idle.png", 173, 143, 13);
	}

}

Entity* venom_new(Vector2D position)
{
	Entity* ent;
	ent = entity_new();
	if (!ent)
	{
		slog("no space for magik homie");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_all("images/venom_transform.png", 71, 118, 17);
	ent->think = magik_think;
	ent->draw_offset.x = -64;
	ent->draw_offset.y = -64;
	ent->rotation.x = 64;
	ent->rotation.y = 64;
	ent->draw_scale.x = 1;
	ent->draw_scale.y = 1;
	ent->frame_limit = 20;
	ent->player_state = 0;
	vector2d_copy(ent->position, position);
	return ent;

}

//end of file