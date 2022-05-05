#include "simple_logger.h"
#include "portal.h"



void portal_think(Entity* self)
{
    //declare think variables
    const Uint8* keys;
    if (!self)return;
    self->frame = (self->frame + 0.1);
    if (self->frame >= 4)self->frame = 0;

    //get the keyboard state
    keys = SDL_GetKeyboardState(NULL); //get the keyboard for this frame

    if (!self)return;

    if (keys[SDL_SCANCODE_D])
    {
        self->position.x -= 5;
    }
    //move player backwards
    if (keys[SDL_SCANCODE_A])
    {
        self->position.x += 5;
    }

    //hitbox movement
    self->hitbox.x = self->position.x;
    self->hitbox.y = self->position.y;
}

Entity* portal_ent_new(Vector2D position)
{
    Entity* ent;
    ent = entity_new();
    if (!ent)
    {
        slog("no space for health");
        return NULL;
    }
    ent->sprite = gf2d_sprite_load_all("images/portal.png",169,100,1);
    ent->think = portal_think;
    ent->draw_offset.x = -64;
    ent->draw_offset.y = -64;
    ent->rotation.x = 64;
    ent->rotation.y = 64;
    ent->draw_scale.x = 2;
    ent->draw_scale.y = 2;
    ent->hitbox.w = 50;
    ent->hitbox.h = 50;
    vector2d_copy(ent->hitbox, position);

    vector2d_copy(ent->position, position);
    return ent;
}