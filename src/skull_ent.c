#include "simple_logger.h"
#include "skull_ent.h"


void skull_think(Entity *self)
{
    Vector2D direction;
    int mx,my;
    float angle;
    const Uint8 *keys;
    if (!self)return;
    self->frame = (self->frame + 0.1);
    if (self->frame >= 4)self->frame = 0;
    
    if (self->position.x < self->target.x)
    {
        self->flip = vector2d(1, 0);
    }
    else
    {
        self->flip = vector2d(0, 0);
    }


    direction.x = self->target.x - self->position.x+20;
    direction.y = self->target.y - self->position.y+20;
    angle = vector2d_angle(direction) - 90;
    //self->rotation.z = angle;

   //hitbox movement
    self->hitbox.x = self->position.x - 0;
    self->hitbox.y = self->position.y - 60;
    
    keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
    
   if(self->target.x != self->position.x)
    {
        // move forward
        vector2d_set_magnitude(&direction,2);
        vector2d_copy(self->velocity,direction);
    }

   

}

Entity *skull_ent_new(Vector2D position, Vector2D hero)
{
    Entity *ent;
    ent = entity_new();
    if (!ent)
    {
        slog("no space for skull");
        return NULL;
    }
    ent->sprite = gf2d_sprite_load_all("images/skull_enemie.png",44,38,4);
    ent->think = skull_think;
    ent->draw_offset.x = -64;
    ent->draw_offset.y = -64;
    ent->rotation.x = 64;
    ent->rotation.y = 64;
    ent->health = 3;
    ent->draw_scale.x = 3;
    ent->draw_scale.y = 3;
    ent->hitbox.w = 75;
    ent->hitbox.h = 100;
    ent->health = 3;
    ent->flip = vector2d(0, 0);
    


    vector2d_copy(ent->position,position);
    return ent;
}


//eof
