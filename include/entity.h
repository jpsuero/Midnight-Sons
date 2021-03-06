#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <SDL.h>
#include "gf2d_sprite.h"

typedef struct ENTITY_S
{
    Uint8       _inuse;     /**<this flag keeps track if this entity is active or free to reassign*/
    Sprite     *sprite;     /**<sprite used to draw the sprite*/
    float       frame;      /**<current frame to draw*/
    Vector2D    draw_offset;/**<draw position relative to the entity position*/
    Vector2D    position;   /**<where our entity lives*/
    Vector2D    velocity;   /**<how our entity moves*/
    Vector3D    rotation;   /**<how to rotate the sprite*/
    Vector2D    draw_scale;  /**<the scale factor for drawing the sprite*/
    Vector2D    mins,maxs;  /**<describe the bounding box around this entity*/
    float       health;     /**entity health*/
    int         frame_limit; /**used fr animations*/
    int         player_state; /**0 for load, 1 = idle, 2 = walking, 3 = jump, 4 = attack, etc. */
    void (*think)(struct ENTITY_S *self);   /**<a pointer to a think function for this entity*/
    void (*update)(struct ENTITY_S* self); //update thingy
}Entity;


/**
 * @brief initialize the internal entity entity_manager_init
 * @note must be called before other entity functions
 * @param max_entities how many concurrent entities will be supported
 */
void entity_manager_init(Uint32 max_entities);

/**
 * @brief draws all active entities to the screen
 */
void entity_manager_draw_all();

/**
 * @brief runs any think function for all active entities
 */
void entity_manager_think_all();


/**
 * @brief free all active entities
 * @note for use in level transitions.
 */
void entity_manager_clear();

/**
 * @brief get a new empty entity
 * @returns NULL on error, or a pointer to a blank entity
 */
Entity *entity_new();

/**
 * @brief draws the given entity
 * @param entity the entity to draw
 */
void entity_draw(Entity *entity);

/**
 * @brief free the memory of an entity
 * @param entity the entity to free
 */
void entity_free(Entity *entity);

#endif
