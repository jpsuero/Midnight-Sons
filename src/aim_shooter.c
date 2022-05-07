#include "simple_logger.h"
#include "aim_shooter.h"



void shooter_think(Entity* self)
{
    Vector2D direction;
    Vector2D target;
    int     targety;
    int mx, my;
    float angle;
    const Uint8* keys;
    if (!self)return;
    self->frame = (self->frame + 0.1);
    if (self->frame >= 10)self->frame = 0;


    //set targets
    if (self->position.x != self->target.x)
    {
        direction.x = self->target.x - self->position.x;
        direction.y = self->target.y - self->position.y;
        // move forward
        vector2d_set_magnitude(&direction, 3);
        vector2d_copy(self->velocity, direction);
    }

    if (self->position.y <= 200)
    {
        self->target = vector2d(1000, 600);
       
    }
    if (self->position.y >= 650)
    {
        self->target = vector2d(1000,200);
        
    }


    //self->rotation.z = angle;

   //hitbox movement
    self->hitbox.x = self->position.x - 70;
    self->hitbox.y = self->position.y - 100;

    keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame


}

Entity* shooter_ent_new(Vector2D position)
{
    Entity* ent;
    ent = entity_new();
    if (!ent)
    {
        slog("no space for shooter");
        return NULL;
    }
    ent->sprite = gf2d_sprite_load_all("images/aim-shooter_walk.png", 74, 111, 10);
    ent->think = shooter_think;
    ent->draw_offset.x = -64;
    ent->draw_offset.y = -64;
    ent->rotation.x = 64;
    ent->rotation.y = 64;
    ent->draw_scale.x = 2;
    ent->draw_scale.y = 2;
    ent->hitbox.w = 80;
    ent->hitbox.h = 100;
    ent->health = 3;
    ent->flip = vector2d(1, 0);
    ent->target = vector2d(1000, 100);
    vector2d_copy(ent->position, position);
    return ent;
}


//eof
