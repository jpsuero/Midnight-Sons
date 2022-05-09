#include "simple_logger.h"
#include "skull_ent.h"
#include <math.h>


void eyeball_blast_think(Entity* self)
{
    self->buffer++;
    Vector2D direction;
    if (!self)return;
    self->frame = (self->frame + 0.1);
    if (self->frame >= 21)self->frame = 0;

    if (self->position.x < self->target.x)
    {
        self->flip = vector2d(1, 0);
    }
    else
    {
        self->flip = vector2d(0, 0);
    }

    //collision checker
    if (self->hitbox.x >= self->target_hitbox.x && self->hitbox.x <= self->target_hitbox.x + self->target_hitbox.w && self->hitbox.y >= self->target_hitbox.y && self->hitbox.y <= self->target_hitbox.y + self->target_hitbox.h)
    {
        entity_free(self);
    }

    //hitbox movement
    self->hitbox.x = self->position.x - 50;
    self->hitbox.y = self->position.y- 50;
   
    
    //kill self
    if (abs(self->position.x - self->target.x) >= 1500)
    {
        entity_free(self);
        slog("eyeball dead");
    }
}

Entity* eyeball_blast_ent_new(Vector2D position)
{
    Entity* ent;
    ent = entity_new();
    if (!ent)
    {
        slog("no space for eyeball_blast");
        return NULL;
    }
    ent->sprite = gf2d_sprite_load_all("images/eyeball/eyeball_blast.png", 50, 50, 1);
    ent->think = eyeball_blast_think;
    ent->draw_offset.x = -64;
    ent->draw_offset.y = -64;
    ent->rotation.x = 64;
    ent->rotation.y = 64;
    ent->health = 3;
    ent->draw_scale.x = 1;
    ent->draw_scale.y = 1;
    ent->hitbox.w = 50;
    ent->hitbox.h = 50;
    ent->health = 1;
    ent->flip = vector2d(0, 0);



    vector2d_copy(ent->position, position);
    return ent;
}


//eof
