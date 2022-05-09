#include "simple_logger.h"
#include "hydrant.h"



void hydrant_think(Entity* self)
{
    //declare think variables
    const Uint8* keys;

    //get the keyboard state
    keys = SDL_GetKeyboardState(NULL); //get the keyboard for this frame

    if (!self)return;
    self->frame = (self->frame + 0.1);
    if (self->frame >= self->frame_limit)self->frame = 0;

    //move backwards
    if (self->health > 0)
    {
        self->position.x -= 4;
    }
    //move forwards
    if (self->health < 0)
    {
        self->position.x += 4;
    }

    //hitbox movement
    self->hitbox.x = self->position.x;
    self->hitbox.y = self->position.y;

    if (self->speed > 0 && self->buffer == 0)
    {
        self->buffer = 1;
        self->frame_limit = 4;
        self->position.y = self->position.y - 130;
        self->sprite = gf2d_sprite_load_all("images/backgrounds/hydrant_shoot.png", 200, 300, 1);
    }
}

Entity* hydrant_ent_new(Vector2D position)
{
    Entity* ent;
    ent = entity_new();
    if (!ent)
    {
        slog("no space for hydrant");
        return NULL;
    }
    ent->sprite = gf2d_sprite_load_all("images/backgrounds/hydrant_idle.png", 200, 200, 1);
    ent->think = hydrant_think;
    ent->draw_offset.x = -64;
    ent->draw_offset.y = -64;
    ent->rotation.x = 64;
    ent->rotation.y = 64;
    ent->draw_scale.x = 1;
    ent->draw_scale.y = 1;
    ent->hitbox.w = 50;
    ent->hitbox.h = 300; 
    ent->frame_limit = 2;
    vector2d_copy(ent->hitbox, position);

    vector2d_copy(ent->position, position);
    return ent;
}


//eof
