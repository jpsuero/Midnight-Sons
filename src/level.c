#include "level.h"
#include "camera.h"
#include "spawn.h"
#include "simple_json.h"
#include "simple_logger.h"
#include "gf2d_graphics.h"
#include "gf2d_config.h"
#include <stdio.h>

typedef struct
{
    Space      *space;
    Sprite     *backgroundImage;
    Sprite     *tileLayer;
    Mix_Music  *backgroundMusic;
}Level;

static Level gamelevel = {0};

void level_clear()
{
    gf2d_space_free(gamelevel.space);
    gf2d_sprite_free(gamelevel.backgroundImage);
    gf2d_sprite_free(gamelevel.tileLayer);
    if (gamelevel.backgroundMusic)
    {
        Mix_FreeMusic(gamelevel.backgroundMusic);
    }
    memset(&gamelevel,0,sizeof(Level));
    slog("level cleared");
}

void level_info_free(LevelInfo *linfo)
{
    if (!linfo)return;
    if (linfo->tileMap != NULL)
    {
        free(linfo->tileMap);
    }
    sj_free(linfo->spawnList);
    //TODO:free spawn list
    free(linfo);
}

LevelInfo *level_info_new()
{
    LevelInfo *linfo = NULL;
    linfo = (LevelInfo*)malloc(sizeof(LevelInfo));
    if (!linfo)
    {
        slog("failed to allocate level info");
        return NULL;
    }
    memset(linfo,0,sizeof(LevelInfo));
    return linfo;
}

void level_info_tilemap_load(LevelInfo *linfo, SJson *tilemap,Uint32 w,Uint32 h)
{
    int i,j;
    SJson *row,*value;
    if ((!linfo)||(!tilemap))
    {
        slog("missing level info or map object");
        return;
    }
    if ((!w) || (!h))
    {
        slog("cannot have a zero width or height for tilemap");
        return;
    }
    linfo->tileMap = (int *)malloc(sizeof(int)*w*h);
    if (!linfo->tileMap)
    {
        slog("failed to allocate tilemap data");
        return;
    }
    for (j = 0; j < h;j++)
    {
        row = sj_array_get_nth(tilemap,j);
        for (i = 0;i < w;i++)
        {
            value = sj_array_get_nth(row,i);
            sj_get_integer_value(value,&linfo->tileMap[j*w+i]);
        }
    }
}

LevelInfo *level_info_load(char *filename)
{
    LevelInfo *linfo = NULL;
    SJson *json,*world;
    if (!filename)return NULL;
    json = sj_load(filename);
    if (!json)
    {
        slog("failed to load level file %s",filename);
        return NULL;
    }
    linfo = level_info_new();
    if (!linfo)
    {
        return NULL;
    }
    world = sj_object_get_value(json,"world");
    if (!world)
    {
        slog("missing world object in level file %s",filename);
        sj_free(json);
        level_info_free(linfo);
        return NULL;
    }
    gf2d_line_cpy(linfo->backgroundImage,sj_get_string_value(sj_object_get_value(world,"backgroundImage")));
    gf2d_line_cpy(linfo->backgroundMusic,sj_get_string_value(sj_object_get_value(world,"backgroundMusic")));
    gf2d_line_cpy(linfo->tileSet,sj_get_string_value(sj_object_get_value(world,"tileSet")));
    
    sj_value_as_vector2d(sj_object_get_value(world,"tileMapSize"),&linfo->tileMapSize);
    slog("loaded tile size of %f,%f",linfo->tileMapSize.x,linfo->tileMapSize.y);
    
    level_info_tilemap_load(linfo, sj_object_get_value(world,"tileMap"),(Uint32)linfo->tileMapSize.x,(Uint32)linfo->tileMapSize.y);

    sj_value_as_vector2d(sj_object_get_value(world,"tileSize"),&linfo->tileSize);
    
    linfo->spawnList = sj_copy(sj_object_get_value(world,"spawnList"));
    
    sj_free(json);
    slog("loaded level info for %s",filename);
    return linfo;
}

Sprite *level_make_tile_layer(LevelInfo *linfo,Sprite * tileset, Uint32 format)
{
    Sprite *sprite;
    Uint32 clear;
    int i,j;
    if (!linfo)return NULL;
    sprite = gf2d_sprite_new();
    if (!sprite)return NULL;
    sprite->surface = SDL_CreateRGBSurfaceWithFormat(
        0,
        linfo->tileMapSize.x*linfo->tileSize.x,
        linfo->tileMapSize.y*linfo->tileSize.y,
        32,
        format);

    clear = SDL_MapRGBA(sprite->surface->format,0,0,0,0);
    SDL_FillRect(sprite->surface,NULL,clear);
    
    for (j = 0; j < linfo->tileMapSize.y;j++)
    {
        for (i = 0; i < linfo->tileMapSize.x;i++)
        {
            if (linfo->tileMap[j*(Uint32)linfo->tileMapSize.x + i])
            {
                gf2d_sprite_draw_to_surface(
                tileset,
                vector2d(i*linfo->tileSize.x,j*linfo->tileSize.y),
                NULL,
                NULL,
                linfo->tileMap[j*(Uint32)linfo->tileMapSize.x + i] - 1,
                sprite->surface);
            }
        }
    }

    sprite->surface = gf2d_graphics_screen_convert(&sprite->surface);

    if (sprite->surface)
    {
        sprite->texture = SDL_CreateTextureFromSurface(gf2d_graphics_get_renderer(),sprite->surface);
        if (!sprite->texture)
        {
            slog("failed to convert tileLayer data to texture");
            gf2d_sprite_free(sprite);
            return NULL;
        }
        SDL_SetTextureBlendMode(sprite->texture,SDL_BLENDMODE_BLEND);        
        SDL_UpdateTexture(
            sprite->texture,
            NULL,
            sprite->surface->pixels,
            sprite->surface->pitch);
        
        sprite->frame_w = sprite->surface->w;
        sprite->frame_h = sprite->surface->h;
        sprite->frames_per_line = 1;
        
        gf2d_line_cpy(sprite->filepath,"tileLayer");
    }
    else
    {
        slog("failed to convert tile layer to supported format");
        gf2d_sprite_free(sprite);
    }
    
    return sprite;
}

void level_build_tile_space(LevelInfo *linfo)
{
    int i,j;
    for (j = 0;j < linfo->tileMapSize.y;j++)
    {
        for (i = 0; i < linfo->tileMapSize.x;i++)
        {
            if (!linfo->tileMap[j * (Uint32)linfo->tileMapSize.x + i])continue;
            gf2d_space_add_static_shape(gamelevel.space,gf2d_shape_rect(i * linfo->tileSize.x, j * linfo->tileSize.y, linfo->tileSize.x, linfo->tileSize.y));
        }
    }
}

void level_spawn_entities(SJson *spawnList)
{
    int i = 0, count = 0;
    SJson *item;
    Vector2D position;
    count  = sj_array_get_count(spawnList);
    for (i = 0; i < count; i++)
    {
        item = sj_array_get_nth(spawnList,i);
        if (!item)continue;
        sj_value_as_vector2d(sj_object_get_value(item,"position"),&position);
        spawn_entity(sj_get_string_value(sj_object_get_value(item,"name")),position,sj_object_get_value(item,"args"));
    }
}

void level_init(LevelInfo *linfo)
{
    Sprite *tileset;
    if (!linfo)
    {
        return;
    }
    level_clear();
    gamelevel.backgroundImage = gf2d_sprite_load_image(linfo->backgroundImage);
    tileset = gf2d_sprite_load_all(
        linfo->tileSet,
        linfo->tileSize.x,
        linfo->tileSize.y,
        1,
        true);

    gamelevel.backgroundMusic = Mix_LoadMUS(linfo->backgroundMusic);
    if (gamelevel.backgroundMusic)Mix_PlayMusic(gamelevel.backgroundMusic, -1);
    
    tileset = gf2d_sprite_load_all(
        linfo->tileSet,
        linfo->tileSize.x,
        linfo->tileSize.y,
        1,
        true);
    gamelevel.tileLayer = level_make_tile_layer(linfo,tileset, tileset->surface->format->format);
    gf2d_sprite_free(tileset);

    gamelevel.space = gf2d_space_new_full(
        3,
        gf2d_rect(0,0,gamelevel.tileLayer->surface->w,gamelevel.tileLayer->surface->h),
        0.1,
        vector2d(0,0),
        1,
        0.1);
    level_build_tile_space(linfo);
    camera_set_bounds(0,0,gamelevel.tileLayer->surface->w,gamelevel.tileLayer->surface->h);
    level_spawn_entities(linfo->spawnList);
}

void level_draw()
{
    Vector2D cam;
    cam = camera_get_position();
    gf2d_sprite_draw_image(gamelevel.backgroundImage,vector2d(-cam.x,-cam.y));
    gf2d_sprite_draw_image(gamelevel.tileLayer,vector2d(-cam.x,-cam.y));
    gf2d_entity_draw_all();
    if (gamelevel.space)gf2d_space_draw(gamelevel.space,vector2d(-cam.x,-cam.y));
}

void level_update()
{
    gf2d_entity_pre_sync_all();
    gf2d_space_update(gamelevel.space);
    gf2d_entity_post_sync_all();
}

int body_body_touch(Body *self, Body *other, Collision *collision)
{
    Entity *selfEnt,*otherEnt;
    if ((!self)||(!other))return 0;
    selfEnt = (Entity *)self->data;
    if (!selfEnt)return 0;
    otherEnt = (Entity *)other->data;
    if (!otherEnt)return 0;
    if (selfEnt->touch)
    {
        slog("%s is touching %s",selfEnt->name,otherEnt->name);
        return selfEnt->touch(selfEnt,otherEnt);
    }
    return 0;
}

void level_remove_entity(Entity *ent)
{
    if (!ent)return;
    if (!gamelevel.space)
    {//nothing to do
        return;
    }
    gf2d_space_remove_body(gamelevel.space,&ent->body);
}

void level_add_entity(Entity *ent)
{
    if (!ent)return;
    if (!gamelevel.space)
    {
        slog("cannot add entity %s to level, no space defined!",ent->name);
        return;
    }
    if (ent->body.bodyTouch == NULL)
    {
        ent->body.bodyTouch = body_body_touch;
    }
    gf2d_space_add_body(gamelevel.space,&ent->body);
}

Space *level_get_space()
{
    return gamelevel.space;
}
/*eol@eof*/