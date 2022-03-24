#include "simple_logger.h"
#include "BOSS.h"


void boss_think(Entity* self)
{
    Vector2D direction;
    Vector2D target;
    int     targety;
    int mx, my;
    float angle;
    const Uint8* keys;
    if (!self)return;
    self->frame = (self->frame + 0.1);
    if (self->frame >= 1)self->frame = 0;


    //set targets
    if (self->position.x != self->target.x)
    {
        direction.x = self->target.x-self->position.x;
        direction.y = self->target.y - self->position.y;
        // move forward
        vector2d_set_magnitude(&direction, 10);
        vector2d_copy(self->velocity, direction);
    }

    if (self->position.x >= 1000 && self->position.y <= 100)
    {
        self->target = vector2d(1000, 500);
    }
    if (self->position.x >= 1000 && self->position.y >= 500)
    {
        self->target = vector2d(100, 100);
    }
    if (self->position.x <= 100 && self->position.y<=100)
    {
        self->target = vector2d(100, 500);
    }
    if (self->position.x <= 100 && self->position.y >= 500)
    {
        self->target = vector2d(1000, 100);
    }

   
    //self->rotation.z = angle;

   //hitbox movement
    self->hitbox.x = self->position.x-100;
    self->hitbox.y = self->position.y-100;

    keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
    

}

Entity* boss_ent_new(Vector2D position)
{
    Entity* ent;
    ent = entity_new();
    if (!ent)
    {
        slog("no space for boss");
        return NULL;
    }
    ent->sprite = gf2d_sprite_load_all("images/boss.png", 125, 124, 1);
    ent->think = boss_think;
    ent->draw_offset.x = -64;
    ent->draw_offset.y = -64;
    ent->rotation.x = 64;
    ent->rotation.y = 64;
    ent->draw_scale.x = 2;
    ent->draw_scale.y = 2;
    ent->hitbox.w = 140;
    ent->hitbox.h = 160;
    ent->health = 1000;
    ent->flip = vector2d(0, 0);
    ent->target = vector2d(1000, 100);
    vector2d_copy(ent->position, position);
    return ent;
}


//eof
