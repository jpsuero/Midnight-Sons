#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "gf2d_text.h"
#include "gf2d_particles.h"
#include "gf2d_list.h"
#include "gf2d_vector.h"
#include "gf2d_entity.h"

typedef struct
{
    Vector2D    position;
    Vector2D    positionVariance;
    Uint32      startPosition;
    Uint32      endPosition;
    Uint32      autospawn;
    TextLine    name;
}Spawn;


/**
 * @brief information about a level that is loaded from file
 */
typedef struct
{
    TextLine    name;
    Spawn      *spawnList;
    Uint32      spawnCount;
    Rect        bounds;
    TextLine    backgroundImage;
    Vector2D    backgroundOffset;
    TextLine    backgroundMusic;
    Vector4D    backgroundColor;
    Vector4D    starfield;
    Vector4D    starfieldVariance;
    Uint32      starRate;
    float       starSpeed;
}LevelInfo;

/**
 * @brief Load level information from file
 * @param filename the file to load info from
 * @return the information loaded for the level
 */
LevelInfo *level_info_load(char *filename);

/**
 * @brief free the information loaded for a level
 * @note: this can be done after the level has been started
 * @param info the info to free
 */
void level_info_free(LevelInfo *info);

/**
 * @brief using the level info, start running the level
 * @param info the level info to base this level on
 */
void level_start(LevelInfo *info);

/**
 * @brief clean up the loaded level and free all data
 */
void level_close();


/**
 * @brief update the current level
 */
void level_update();

/**
 * @brief draw the current level
 * @param cameraPosition for calculating position to draw
 */
void level_draw();

/**
 * @brief get the current absolute bounds of the level
 */
Rect level_get_bounds();

/**
 * @brief adds an entity to the level physics space
 * @note entity must have a Body defined
 * @param ent the entity to add to the space
 */
void level_add_entity(Entity *ent);

/**
 * @brief removes an entity from the level physics space
 * @note this should not be done during a space update (ie: collision callbacks)
 * @param ent the entity to be removed
 */
void level_remove_entity(Entity *ent);

#endif
