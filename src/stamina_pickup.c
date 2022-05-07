#include "simple_logger.h"
#include "stamina_pickup.h"



void stamina_think(Entity* self)
{
    //declare think variables
    const Uint8* keys;

    //get the keyboard state
    keys = SDL_GetKeyboardState(NULL); //get the keyboard for this frame

    if (!self)return;

    //move backwards
    if (self->speed > 0)
    {
        self->position.x -= 4;
    }
    //move forwards
    if (self->speed < 0)
    {
        self->position.x += 4;
    }

    //hitbox movement
    self->hitbox.x = self->position.x;
    self->hitbox.y = self->position.y;
}

Entity* stamina_ent_new(Vector2D position)
{
    Entity* ent;
    ent = entity_new();
    if (!ent)
    {
        slog("no space for health");
        return NULL;
    }
    ent->sprite = gf2d_sprite_load_image("images/stamina_potion.png");
    ent->think = stamina_think;
    ent->draw_offset.x = -64;
    ent->draw_offset.y = -64;
    ent->rotation.x = 64;
    ent->rotation.y = 64;
    ent->draw_scale.x = 1.5;
    ent->draw_scale.y = 1.5;
    ent->hitbox.w = 50;
    ent->hitbox.h = 50;
    vector2d_copy(ent->hitbox, position);

    vector2d_copy(ent->position, position);
    return ent;
}