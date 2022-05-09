#include "simple_logger.h"
#include "skull_ent.h"
#include "gfc_audio.h"


void aimbot_think(Entity* self)
{
    Vector2D direction;
    float angle;
    const Uint8* keys;
    if (!self)return;
    //self->frame = (self->frame + 0.5);
    if (self->frame >= self->frame_limit)self->frame = 0;

    
    if (self->position.x < self->target.x)
    {
        self->flip = vector2d(0, 0);
    }
    else
    {
        self->flip = vector2d(1, 0);
    }

    float y = self->target.y - self->position.y;
    //self->rotation.z = angle;

   //hitbox movement
    self->hitbox.x = self->position.x;
    self->hitbox.y = self->position.y;

    keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
    if (self->position.x < self->target.x)
    { 
        if ((self->target.x - self->position.x) <= 300)
        {
            
            self->frame_limit = 7;
            if (self->frame >= 3 && self->frame < 5)
            {
                self->isAttacking = 1;
            }
            else { self->isAttacking = 0; }
            self->frame = (self->frame + 0.08);
            self->sprite = gf2d_sprite_load_all("skeleton/003_attack.png", 32, 32, 4);
        }
        else
        {
            self->frame = (self->frame + 0.04);
            self->isAttacking = 0;
            self->frame_limit =2;
            self->sprite = gf2d_sprite_load_all("skeleton/003_idle.png", 32, 32, 2);
        }
    }
    else
    {
        if ((self->position.x - self->target.x) <= 300)
        {
            self->frame_limit = 7;

            if (self->frame >= 3 && self->frame < 5)
            {
                self->isAttacking = 1;
            }
            else { self->isAttacking = 0; }
            self->frame = (self->frame + 0.08);
            self->sprite = gf2d_sprite_load_all("skeleton/003_attack.png", 32, 32, 4);
        }
        else
        {
            self->frame = (self->frame + 0.04);
            self->isAttacking = 0;
            self->frame_limit = 2;
            self->sprite = gf2d_sprite_load_all("skeleton/003_idle.png", 32, 32, 2);
        }
    }
    
    //move with bg
    if (self->speed > 0)
    {
        self->position.x -= 4;
    }
    if (self->speed< 0)
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
    ent->sprite = gf2d_sprite_load_all("skeleton/003_idle.png", 32, 32, 2);
    ent->think = aimbot_think;
    ent->draw_offset.x = -64;
    ent->draw_offset.y = -64;
    ent->rotation.x = 64;
    ent->rotation.y = 64;
    ent->draw_scale.x = 5;
    ent->draw_scale.y = 5;
    ent->hitbox.w = 75;
    ent->hitbox.h = 100;
    ent->health = 2;
    ent->flip = vector2d(0, 0);
    vector2d_copy(ent->position, position);
    return ent;
}


//eof
