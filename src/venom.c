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

	//hitbox movement
	self->hitbox.x = self->position.x - 40;
	self->hitbox.y = self->position.y - 60;


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
	else if (self->player_state == 8)
	{
		self->frame_limit = 6;
	}


	//get the keyboard state
	keys = SDL_GetKeyboardState(NULL); //get the keyboard for this frame

	//move player forward
	if (keys[SDL_SCANCODE_D])
	{
		self->player_state = 2;
		self->position.x += 3;
		self->flip = vector2d(0, 0);
		self->sprite = gf2d_sprite_load_all("images/venom_walk.png", 150, 156, 10);
	}
	//move player backwards
	if (keys[SDL_SCANCODE_A])
	{
		self->player_state = 2;
		self->position.x -= 3;
		self->flip = vector2d(1, 0);
		
		self->sprite = gf2d_sprite_load_all("images/venom_walk.png", 150, 156, 10);

	}
	//move player up
	if (keys[SDL_SCANCODE_W])
	{
		self->player_state = 2;
		self->position.y -= 3;
		self->sprite = gf2d_sprite_load_all("images/venom_walk.png", 150, 156, 10);
	}
	//move player down
	if (keys[SDL_SCANCODE_S])
	{
		self->player_state = 2;
		self->position.y += 3;
		self->sprite = gf2d_sprite_load_all("images/venom_walk.png", 150, 156, 10);
	}

	//player jump 
	if (keys[SDL_SCANCODE_SPACE])
	{
		self->player_state = 3;
		self->sprite = gf2d_sprite_load_all("images/Gambit_jump.png", 93, 106, 3);
	}

	if (keys[SDL_SCANCODE_E] && self->canAttack == 1)
	{
		self->player_state = 4;
		self->isAttacking = 1;
		self->canAttack = 0;
		self->stamina -= 1;
		self->sprite = gf2d_sprite_load_all("images/venom_attack1.png", 212, 131, 3);

	}
	if (keys[SDL_SCANCODE_Q] && self->canAttack == 1 && self->stamina >= 2)
	{
		self->player_state = 5;
		self->isAttacking = 2;
		self->canAttack = 0;
		self->stamina -= 2;
		self->sprite = gf2d_sprite_load_all("images/venom_attack2.png", 165.14, 220, 7);
	}
	if (keys[SDL_SCANCODE_F] && self->canAttack == 1 && self->stamina == 5)
	{
		self->player_state = 6;
		self->health = 5;
		self->canAttack = 0;
		self->stamina -= 5;
		self->sprite = gf2d_sprite_load_all("images/venom_attack4.png", 246, 191, 18);
	}
	if (keys[SDL_SCANCODE_G] && self->canAttack == 1 && self->stamina >= 3)
	{
		self->player_state = 7;
		self->isAttacking = 3;
		self->canAttack = 0;
		self->stamina -= 3;
		self->sprite = gf2d_sprite_load_all("images/venom_attack3.png", 311, 161, 8);
	}
	if (keys[SDL_SCANCODE_X] && self->canAttack == 1)
	{
		self->player_state = 8;
		self->canAttack = 0;
		self->stamina -= 3;
		self->sprite = gf2d_sprite_load_all("images/venom_poison.png", 220, 144, 7);
	}

	//idle requirements
	if (!keys[SDL_SCANCODE_X] && !keys[SDL_SCANCODE_S] && !keys[SDL_SCANCODE_W] && !keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_SPACE] && !keys[SDL_SCANCODE_E] && !keys[SDL_SCANCODE_Q] && !keys[SDL_SCANCODE_F] && !keys[SDL_SCANCODE_G])
	{
		self->player_state = 1;
		self->sprite = gf2d_sprite_load_all("images/venom_idle.png", 173, 143, 13);
		self->frame = (self->frame + 0.01);
		self->isAttacking = 0;
		self->canAttack = 1;
	}
}

Entity* venom_new(Vector2D position)
{
	SDL_Rect hitbox;
	
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
	ent->draw_scale.x = 1.5;
	ent->draw_scale.y = 1.5;
	ent->frame_limit = 20;
	ent->player_state = 0;
	ent->health = 5;
	ent->stamina = 5;
	ent->flip = vector2d(0, 0);
	vector2d_copy(ent->position, position);
	
	ent->hitbox.w = 200;
	ent->hitbox.h = 200;
	return ent;
	
	

	
}

//end of file