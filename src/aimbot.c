#include "simple_logger.h"
#include "skull_ent.h"


void aimbot_think(Entity* self)
{
    Vector2D direction;
    float angle;
    const Uint8* keys;
    if (!self)return;
    self->frame = (self->frame + 0.1);
    if (self->frame >= self->frame_limit)self->frame = 0;

    
    if (self->position.x < self->target.x)
    {
        self->flip = vector2d(1, 0);
    }
    else
    {
        self->flip = vector2d(0, 0);
    }


    direction.x = self->target.x - self->position.x;
    direction.y = self->target.y - self->position.y;
    angle = vector2d_angle(direction) - 90;
    //self->rotation.z = angle;

   //hitbox movement
    self->hitbox.x = self->position.x + 100;
    self->hitbox.y = self->position.y - 60;

    keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
    if (self->position.x < self->target.x)
    { 
        if ((self->target.x - self->position.x) <= 300)
        {
            self->frame_limit = 15;
            if (self->frame >= 11 && self->frame < 12)
            {
                self->isAttacking = 1;
            }
            else { self->isAttacking = 0; }
            self->sprite = gf2d_sprite_load_all("images/aimbots_knife.png", 80, 50, 1);
            self->draw_scale.x = 3;
            self->draw_scale.y = 3;
        }
        else
        {
            self->isAttacking = 0;
            self->frame_limit = 4;
            self->sprite = gf2d_sprite_load_all("images/aimbot_idle.png", 41, 53, 4);
            self->draw_scale.x = 1.5;
            self->draw_scale.y = 1.5;
        }
    }
    else
    {
        self->hitbox.x = self->position.x+100;
        self->hitbox.y = self->position.y - 60;
        if ((self->position.x - self->target.x) <= 300)
        {
            self->frame_limit = 15;

            if (self->frame >= 11 && self->frame < 12)
            {
                self->isAttacking = 1;
            }
            else { self->isAttacking = 0; }
            self->sprite = gf2d_sprite_load_all("images/aimbots_knife.png", 80, 50, 1);
            self->draw_scale.x = 3;
            self->draw_scale.y = 3;
        }
        else
        {
            self->isAttacking = 0;
            self->frame_limit = 4;
            self->sprite = gf2d_sprite_load_all("images/aimbot_idle.png", 41, 53, 4);
            self->draw_scale.x = 1.5;
            self->draw_scale.y = 1.5;
        }
    }

    //move with bg
    if (keys[SDL_SCANCODE_D])
    {
        self->position.x -= 4;
    }
    if (keys[SDL_SCANCODE_A])
    {
        self->position.x += 4;
    }
    

}

Entity* aimbot_ent_new(Vector2D position)
{
    Entity* ent;
    ent = entity_new();
    if (!ent)
    {
        slog("no space for aimbot");
        return NULL;
    }
    ent->sprite = gf2d_sprite_load_all("images/aimbot_idle.png", 41, 53, 4);
    ent->think = aimbot_think;
    ent->draw_offset.x = -64;
    ent->draw_offset.y = -64;
    ent->rotation.x = 64;
    ent->rotation.y = 64;
    ent->draw_scale.x = 1;
    ent->draw_scale.y = 1;
    ent->hitbox.w = 75;
    ent->hitbox.h = 100;
    ent->health = 2;
    ent->flip = vector2d(0, 0);
    vector2d_copy(ent->position, position);
    return ent;
}


//eof
