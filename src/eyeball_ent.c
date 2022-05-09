#include "simple_logger.h"
#include "skull_ent.h"
#include "eyeball_blast.h"



void eyeball_think(Entity* self)
{
    Entity* blast;
    self->buffer++;
    Vector2D direction;
    int mx, my;
    float angle;
    const Uint8* keys;
    if (!self)return;
    self->frame = (self->frame + 0.05);
    if (self->frame >= 4)self->frame = 0;

    if (self->position.x < self->target.x)
    {
        self->flip = vector2d(1, 0);
    }
    else
    {
        self->flip = vector2d(0, 0);
    }

    //self->rotation.z = angle;

   //hitbox movement
    self->hitbox.x = self->position.x;
    self->hitbox.y = self->position.y;

    keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame

    if (self->position.y - self->target.y <= 10)
    {
        self->sprite = gf2d_sprite_load_all("images/eyeball/eye_attack.png", 200, 200, 1);
    }
    else
    {
        self->sprite = gf2d_sprite_load_all("images/eyeball/eye_idle.png", 150, 170, 1);
    }


    //follow player height
    direction = vector2d(0, self->target.y - self->position.y);

    if(self->target.y != self->position.y)
    {
        vector2d_set_magnitude(&direction, 1.2);
        vector2d_copy(self->velocity, direction);
    }


    //move with bg
    if (self->speed > 0)
    {
        self->position.x -= 4;
    }
    if (self->speed < 0)
    {
        self->position.x += 4;
    }

}

Entity* eyeball_ent_new(Vector2D position)
{
    Entity* ent;
    ent = entity_new();
    if (!ent)
    {
        slog("no space for eyeball");
        return NULL;
    }
    ent->sprite = gf2d_sprite_load_all("images/eyeball/eye_idle.png", 150, 170, 1);
    ent->think = eyeball_think;
    ent->draw_offset.x = -64;
    ent->draw_offset.y = -64;
    ent->rotation.x = 64;
    ent->rotation.y = 64;
    ent->health = 3;
    ent->draw_scale.x = 1;
    ent->draw_scale.y = 1;
    ent->hitbox.w = 100;
    ent->hitbox.h = 100;
    ent->health = 3;
    ent->flip = vector2d(0, 0);
    ent->buffer = 0;



    vector2d_copy(ent->position, position);
    return ent;
}


//eof
