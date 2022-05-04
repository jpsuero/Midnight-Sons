#include "simple_logger.h"
#include "punisher_ent.h"
#include "gf2d_draw.h"

void punisher_think(Entity* self)
{
	//declare think variables
	const Uint8* keys;
	//return if not punish ent
	if (!self)return;
	self->frame = (self->frame + 0.1);
	//set frame limit
	if (self->frame >= self->frame_limit)self->frame = 0;

	//animator
	if (self->player_state == 1)
	{
		self->frame_limit = 3;
	}
	else if (self->player_state == 2)
	{
		self->frame_limit = 12;
	}
	else if (self->player_state == 3)
	{
		self->frame_limit = 3;
	}
	else if (self->player_state == 4)
	{
		self->frame_limit = 11;
	}
	else if (self->player_state == 5)
	{
		self->frame_limit = 8;
	}
	else if (self->player_state == 6)
	{
		self->frame_limit = 6;
	}
	else if (self->player_state == 7)
	{
		self->frame_limit = 8;
	}
	else if (self->player_state == 8)
	{
		self->frame_limit = 7;
	}

	//hitbox movement
	self->hitbox.x = self->position.x-50;
	self->hitbox.y = self->position.y-80;


	//get the keyboard state
	keys = SDL_GetKeyboardState(NULL); //get the keyboard for this frame

	//move player forward
	if (keys[SDL_SCANCODE_D])
	{
		
		self->player_state = 2;
		self->position.x += self->speed;
		self->flip = vector2d(0, 0);
		self->sprite = gf2d_sprite_load_all("images/punisher_walking.png", 84, 99, 12);
	}
	//move player backwards
	if (keys[SDL_SCANCODE_A])
	{
		self->player_state = 2;
		self->position.x -= self->speed;
		self->flip = vector2d(1, 0);
		self->sprite = gf2d_sprite_load_all("images/punisher_walking.png", 84, 99, 12);
	}
	//move player up
	if (keys[SDL_SCANCODE_W])
	{
		//self->frame_limit = 6;
		self->player_state = 2;
		self->position.y -= self->speed;
		self->position.x -= 1;
		self->sprite = gf2d_sprite_load_all("images/punisher_walking.png", 84, 99, 12);
	}
	//move player down
	if (keys[SDL_SCANCODE_S])
	{
		self->player_state = 2;
		self->position.y += self->speed;
		self->position.x += 1;
		self->sprite = gf2d_sprite_load_all("images/punisher_walking.png", 84, 99, 12);
	}

	//player jump 
	if (keys[SDL_SCANCODE_SPACE])
	{
		self->player_state = 3;
		self->sprite = gf2d_sprite_load_all("images/Gambit_jump.png", 93, 106, 3);

	}
	//punisher punch
	if (keys[SDL_SCANCODE_E] && self->canAttack == 1)
	{
		self->player_state = 4;
		self->isAttacking = 1;
		self->canAttack = 0;
		self->sprite = gf2d_sprite_load_all("images/punisher_attack1.png", 97, 101, 11);

	}
	//punisher kick
	if (keys[SDL_SCANCODE_Q] && self->canAttack == 1 && self->stamina >= 2)
	{
		self->player_state = 5;
		self->stamina -= 2;
		self->isAttacking = 2;
		self->canAttack = 0;
		self->sprite = gf2d_sprite_load_all("images/punisher_kick.png", 94, 112, 8);
	}
	//punisher twirl
	if (keys[SDL_SCANCODE_F] && self->canAttack == 1 && self->stamina >= 3)
	{
		self->player_state = 6;
		self->stamina -= 3;
		self->isAttacking = 3;
		self->canAttack = 1;
		self->sprite = gf2d_sprite_load_all("images/punisher_twirl.png", 80, 103, 6);
	}
	//punisher shotgun
	if (keys[SDL_SCANCODE_X] && self->canAttack == 1)
	{
		if (self->frame > 8)self->frame = 0;
		self->player_state = 7;
		self->isAttacking = 1;
		self->canAttack = 0;
		self->sprite = gf2d_sprite_load_all("images/venom_attack3.png", 311, 161, 8);
	}

	//punisher invisible
	if (keys[SDL_SCANCODE_G])
	{
		self->invisible = 1;
	}
	else
	{
		self->invisible = 0;
	}

	//idle requirements
	if (!keys[SDL_SCANCODE_X] && !keys[SDL_SCANCODE_S] && !keys[SDL_SCANCODE_W] && !keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_SPACE] && !keys[SDL_SCANCODE_E] && !keys[SDL_SCANCODE_Q] && !keys[SDL_SCANCODE_F] && !keys[SDL_SCANCODE_G])
	{
		self->player_state = 1;
		self->sprite = gf2d_sprite_load_all("images/punisher_idle.png", 85, 93, 3);
		self->frame = (self->frame + 0.01);
		self->isAttacking = 0;
		self->canAttack = 1;
	}
}

Entity* punisher_new(Vector2D position)
{
	Entity* ent;
	ent = entity_new();
	if (!ent)
	{
		slog("no space for punisher homie");
		return NULL;
	}
	ent->sprite = gf2d_sprite_load_all("images/punisher_idle.png", 85, 93, 3);
	ent->think = punisher_think;
	ent->draw_offset.x = -64;
	ent->draw_offset.y = -64;
	ent->rotation.x = 64;
	ent->rotation.y = 64;
	ent->draw_scale.x = 1.5;
	ent->draw_scale.y = 1.5;
	ent->frame_limit = 3;
	ent->player_state = 1;
	ent->health = 5;
	ent->strength = 1;
	ent->stamina = 5;
	ent->hitbox.w = 200;
	ent->hitbox.h = 200;
	ent->flip = vector2d(0, 0);
	ent->speed = 3;

	vector2d_copy(ent->position, position);
	return ent;

}
//end of file