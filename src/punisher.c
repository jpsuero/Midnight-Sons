#include "simple_logger.h"
#include "punisher_ent.h"
#include "gf2d_draw.h"
#include "gfc_audio.h"

void punisher_think(Entity* self)
{
	//declare think variables
	const Uint8* keys;
	Sound* punch, * kick, * throw, * shoot, * patch;
	punch = gfc_sound_load("SFX/punisher_punch.mp3", 10, 0);
	kick = gfc_sound_load("SFX/punisher_kick.mp3", 10, 0);
	throw = gfc_sound_load("SFX/later_bitch.wav", 10, 0);
	shoot = gfc_sound_load("SFX/venom_heal.wav", 10, 0);
	patch = gfc_sound_load("SFX/slurp.wav", 10, 0);
	
	//joystick movement
	int punching = 0, swiping = 0, chomping = 0, movingR = 0, movingL = 0, movingU = 0, movingD = 0, jumping = 0, poisoning = 0, healing = 0;

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

	//hitbox movement, flips with player flip
	if (self->flip.x == 0)
	{
		self->hitbox.x = self->position.x - 50;
		self->hitbox.y = self->position.y - 80;
	}
	else
	{
		self->hitbox.x = self->position.x - 150;
		self->hitbox.y = self->position.y - 80;
	}
	
	//joystick input
	//joystick
	SDL_Init(SDL_INIT_JOYSTICK);

	SDL_Joystick* joystick;

	SDL_JoystickEventState(SDL_ENABLE);
	joystick = SDL_JoystickOpen(0);
	if (joystick == NULL)
	{
		slog("no joystick connected");
	}

	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			entity_free(self);
		}

		else if (event.type == SDL_JOYAXISMOTION)
		{
			if (event.jaxis.which == 0)
			{
				//horizontal movement
				if (event.jaxis.axis == 0)
				{
					if (event.jaxis.value < -3200)
					{
						movingL = 1;
					}
					else if (event.jaxis.value > 3200)
					{
						movingR = 1;
					}
					else
					{
						self->velocity.x = 0;
						movingL = 0;
						movingR = 0;
					}
				}
				//vertical movement
				if (event.jaxis.axis == 1)
				{
					if (event.jaxis.value < -3200)
					{
						movingU = 1;
					}
					else if (event.jaxis.value > 3200)
					{
						movingD = 1;
					}
					else
					{
						self->velocity.y = 0;
						movingD = 0;
						movingU = 0;
					}
				}
			}
		}
		else if (event.type == SDL_JOYBUTTONDOWN)
		{
			if (event.jbutton.button == 2)
			{
				punching = 1;
			}
			else if (event.jbutton.button == 3)
			{
				swiping = 1;
			}
			else if (event.jbutton.button == 1)
			{
				chomping = 1;
			}
			else if (event.jbutton.button == 9)
			{
				healing = 1;
			}
			else if (event.jbutton.button == 0)
			{
				jumping = 1;
			}

		}
		else if (SDL_JOYBUTTONUP)
		{
			if (event.jbutton.button == 2)
			{
				punching = 0;
				self->canAttack = 1;
			}
			else if (event.jbutton.button == 3)
			{
				swiping = 0;
				self->canAttack = 1;
			}
			else if (event.jbutton.button == 1)
			{
				chomping = 0;
				self->canAttack = 1;
			}
			else if (event.jbutton.button == 9)
			{
				healing = 0;
				self->canAttack = 1;
				self->invisible = 0;
			}
			else if (event.jbutton.button == 0)
			{
				jumping = 0;
				self->canAttack = 1;
			}
		}
	}



	//get the keyboard state
	keys = SDL_GetKeyboardState(NULL); //get the keyboard for this frame

	//move player forward
	if (keys[SDL_SCANCODE_D] || movingR)
	{
		self->sprite = gf2d_sprite_load_all("images/punisher_walking.png", 84, 99, 12);
		self->player_state = 2;
		self->velocity.x = 3;
		self->flip = vector2d(0, 0);
	}
	//move player backwards
	if (keys[SDL_SCANCODE_A] || movingL)
	{
		self->sprite = gf2d_sprite_load_all("images/punisher_walking.png", 84, 99, 12);
		self->player_state = 2;
		self->velocity.x = -3;
		self->flip = vector2d(1, 0);
	}
	//move player up
	if (keys[SDL_SCANCODE_W] || movingU)
	{
		self->sprite = gf2d_sprite_load_all("images/punisher_walking.png", 84, 99, 12);
		self->player_state = 2;
		self->velocity.y = -3;
	}
	//move player down
	if (keys[SDL_SCANCODE_S] || movingD)
	{
		self->sprite = gf2d_sprite_load_all("images/punisher_walking.png", 84, 99, 12);
		self->player_state = 2;
		self->velocity.y = 3;
	}

	//player jump 
	if (keys[SDL_SCANCODE_SPACE] || jumping)
	{
		self->player_state = 3;
		self->sprite = gf2d_sprite_load_all("images/Gambit_jump.png", 93, 106, 3);

	}
	//punisher punch
	if (keys[SDL_SCANCODE_E] || punching && self->canAttack == 1)
	{
		self->sprite = gf2d_sprite_load_all("images/punisher_attack1.png", 97, 101, 11);
		self->player_state = 4;
		self->isAttacking = 1;
		self->canAttack = 0;
		gfc_sound_play(punch, 0, 10, -1, -1);

	}
	//punisher kick
	if (keys[SDL_SCANCODE_Q] || swiping && self->canAttack == 1 && self->stamina >= 2)
	{
		self->player_state = 5;
		self->stamina -= 2;
		self->isAttacking = 2;
		self->canAttack = 0;
		gfc_sound_play(kick, 0, 10, -1, -1);
		self->sprite = gf2d_sprite_load_all("images/punisher_kick.png", 94, 112, 8);

	}
	//punisher twirl
	if (keys[SDL_SCANCODE_F] || chomping && self->stamina >=2)
	{
		self->player_state = 6;
		self->stamina -= 2;
		self->isAttacking = 4;
		self->canAttack = 0;
		gfc_sound_play(throw, 0, 10, -1, -1);
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
	if (keys[SDL_SCANCODE_G] || healing)
	{
		self->invisible = 1;
	}

	//idle requirements
	if (self->velocity.x == 0 && self->velocity.y == 0 && self->canAttack == 1)
	{
		self->player_state = 1;
		self->sprite = gf2d_sprite_load_all("images/punisher_idle.png", 85, 93, 3);
		self->frame = (self->frame + 0.01);
		self->isAttacking = 0;

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