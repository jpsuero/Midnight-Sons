#include "simple_logger.h"
#include "BOSS.h"


void shuma_think(Entity* self)
{
    self->buffer++;
    Vector2D direction;
    Vector2D target;
    const Uint8* keys;
    if (!self)return;
    self->frame = (self->frame + 0.05);
    if (self->frame >= 14)self->frame = 0;


    //flip
    if (self->position.x < self->target_hitbox.x)
    {
        self->flip = vector2d(0, 0);
    }
    else
    {
        self->flip = vector2d(1, 0);
    }
    //set targets
    if (self->position.x != self->target.x && self->buffer >= 80)
    {
        direction.x = self->target.x - self->position.x;
        direction.y = self->target.y - self->position.y;
        // move forward
        vector2d_set_magnitude(&direction, 4);
        vector2d_copy(self->velocity, direction);
    }
    else
    {
        self->velocity.x = 0;
    }


    if (self->position.x >= 900 && self->position.y <= 500 && self->buffer >= 80)
    {
        self->target = vector2d(200, 500);
        self->buffer = 0;
    }
    if (self->position.x <= 200 && self->position.y >= 500 && self->buffer >= 80)
    {
        self->target = vector2d(900, 500);
        self->buffer = 0;
    }


    //self->rotation.z = angle;

   //hitbox movement
    self->hitbox.x = self->position.x;
    self->hitbox.y = self->position.y;

    keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame


}

Entity* shuma_ent_new(Vector2D position)
{
    Entity* ent;
    ent = entity_new();
    if (!ent)
    {
        slog("no space for shuma");
        return NULL;
    }
    ent->sprite = gf2d_sprite_load_all("images/ShumaGoreth/shuma_spin.png", 300, 200, 1);
    ent->think = shuma_think;
    ent->draw_offset.x = -64;
    ent->draw_offset.y = -64;
    ent->rotation.x = 64;
    ent->rotation.y = 64;
    ent->draw_scale.x = 1;
    ent->draw_scale.y = 1;
    ent->hitbox.w = 100;
    ent->hitbox.h = 100;
    ent->health = 3;
    ent->flip = vector2d(0, 0);
    ent->target = vector2d(900, 500);
    vector2d_copy(ent->position, position);
    ent->buffer = 0;
    return ent;
}


//eof
