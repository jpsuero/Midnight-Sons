#include <SDL.h>

#include "simple_logger.h"

#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "gf2d_draw.h"

#include "entity.h"
#include "skull_ent.h"
#include "tile_map.h"
#include "venom_ent.h"
#include "magik_ball.h"
#include "punisher_ent.h"
#include "moving_bg.h"
#include "collision.h"
#include "highscore.h"
#include "simple_json.h"


int main(int argc, char * argv[])
{
    /*variable declarations*/
    int highscore = 0;
    int score = 0;
    int done = 0;
    int i = 0;
    int count = 0;
    int enemyCount = 1;
    int staminaCount = 0;
    int colliding;
    float spawnPos = 1200;
    const Uint8 * keys;
    Sprite *icon, *health, *stamina;
    
    int mx,my;
    int position = 70;
    float mf = 0;
    Sprite *mouse;
    Vector4D mouseColor = {255,100,255,200};
    TileMap *tilemap;
    Entity* player;
    Entity* enemy;
    Entity* bg;
    
    
    /*program initializtion*/
    init_logger("gf2d.log");
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1200,
        720,
        1200,
        720,
        vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(16);
    gf2d_sprite_init(1024);
    tile_set_manager_init(16);
    entity_manager_init(1024);
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/
    bg = moving_bg_new(vector2d(0, 0));
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);
    player = venom_new(vector2d(300, 500));
    player->health = 5;
    enemy = skull_ent_new(vector2d(spawnPos, 300));
    icon = gf2d_sprite_load_image("images/venom_icon.png");
    health = gf2d_sprite_load_image("images/health.png");
    stamina = gf2d_sprite_load_image("images/stamina.png");
    highscore = highscore_load("levels/testlevel.json");

    //tilemap = tilemap_load("levels/testlevel.json");

    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        mf+=0.1;
        if (mf >= 16.0)mf = 0;
        entity_manager_think_all();
        colliding = collision_check(player, enemy);
        
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
        //gf2d_sprite_draw_image(sprite, vector2d(player->position.x *-1, 0));
            // draw other game elements
        
            //tilemap_draw(tilemap);
            entity_manager_draw_all();
            //UI elements last
            gf2d_draw_rect(player->hitbox, vector4d(255,0,0,200));
            gf2d_draw_rect(enemy->hitbox, mouseColor);
            //health manager
            if (player->health == 5)
            {
                gf2d_sprite_draw_image(health, vector2d(125, 50));
                gf2d_sprite_draw_image(health, vector2d(175, 50));
                gf2d_sprite_draw_image(health, vector2d(225, 50));
                gf2d_sprite_draw_image(health, vector2d(275, 50));
                gf2d_sprite_draw_image(health, vector2d(325, 50));
            }
            else if (player->health == 4)
            {
                gf2d_sprite_draw_image(health, vector2d(125, 50));
                gf2d_sprite_draw_image(health, vector2d(175, 50));
                gf2d_sprite_draw_image(health, vector2d(225, 50));
                gf2d_sprite_draw_image(health, vector2d(275, 50));
            }
            else if (player->health == 3)
            {
                gf2d_sprite_draw_image(health, vector2d(125, 50));
                gf2d_sprite_draw_image(health, vector2d(175, 50));
                gf2d_sprite_draw_image(health, vector2d(225, 50));
            }
            else if (player->health == 2)
            {
                gf2d_sprite_draw_image(health, vector2d(125, 50));
                gf2d_sprite_draw_image(health, vector2d(175, 50));
            }
            else if (player->health == 1)
            {
                gf2d_sprite_draw_image(health, vector2d(125, 50));
            }

            //stamina manager
            if (player->stamina == 5)
            {
                gf2d_sprite_draw_image(stamina, vector2d(125, 100));
                gf2d_sprite_draw_image(stamina, vector2d(175, 100));
                gf2d_sprite_draw_image(stamina, vector2d(225, 100));
                gf2d_sprite_draw_image(stamina, vector2d(275, 100));
                gf2d_sprite_draw_image(stamina, vector2d(325, 100));
            }
            else if (player->stamina == 4)
            {
                gf2d_sprite_draw_image(stamina, vector2d(125, 100));
                gf2d_sprite_draw_image(stamina, vector2d(175, 100));
                gf2d_sprite_draw_image(stamina, vector2d(225, 100));
                gf2d_sprite_draw_image(stamina, vector2d(275, 100));
            }
            else if (player->stamina == 3)
            {
                gf2d_sprite_draw_image(stamina, vector2d(125, 100));
                gf2d_sprite_draw_image(stamina, vector2d(175, 100));
                gf2d_sprite_draw_image(stamina, vector2d(225, 100));
            }
            else if (player->stamina == 2)
            {
                gf2d_sprite_draw_image(stamina, vector2d(125, 100));
                gf2d_sprite_draw_image(stamina, vector2d(175, 100));
            }
            else if (player->stamina == 1)
            {
                gf2d_sprite_draw_image(stamina, vector2d(125, 100));
            }


        
            gf2d_sprite_draw_image(icon, vector2d(50, 50));


        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
        
        //enemy spawner
        if (enemyCount == 0)
        {
            if (spawnPos == 1200)
            {
                spawnPos = 100;
            }
            else
            {
                spawnPos = 1200;
            }
            
            enemy = skull_ent_new(vector2d(spawnPos, 300));
            enemyCount = 1;
        }


                                  
        //player switch: 1 for punisher and 2 for venom
        if (keys[SDL_SCANCODE_1])
        {
            entity_free(player);
            player = punisher_new(vector2d(300, 500));
            icon = gf2d_sprite_load_image("images/punisher_pic.png");
        }
        if (keys[SDL_SCANCODE_2])
        {
            entity_free(player);
            player = venom_new(vector2d(300, 500));
            icon = gf2d_sprite_load_image("images/venom_icon.png");
        }
        

        //player attacks
        if (player->isAttacking == 1 && colliding)
        {
            enemy->health -= 1;
            player->isAttacking = 0;
        }
        
        if (player->isAttacking == 2 && colliding)
        {
            enemy->health -= 2;
        }

        if (player->isAttacking == 3 && colliding)
        {
            enemy->health -= 3;
        }

        //enemy target update
        enemy->target.x = player->position.x;
        enemy->target.y = player->position.y;
        
        //hurt player
        if (count == 0 && keys[SDL_SCANCODE_O])
        {
            player->health -= 1;
            player->stamina -= 1;
            count = 1;
        }

        if (keys[SDL_SCANCODE_R])
        {
            count = 0;
        }
        
        if (keys[SDL_SCANCODE_H])
        {
            slog("%i", highscore);
        }
        

        //give stamina back
        staminaCount++;
        if (staminaCount >= 200 && player->stamina < 5)
        {
            player->stamina++;
            staminaCount = 0;
        }

        //kill enemy
        if (enemy->health <= 0)
        {
            entity_free(enemy);
            enemyCount = 0;
            score++;
        }

        if (score>highscore)
        {
            highscore_save(score);
        }

       
        //player bounds
        if (player->position.x >= 1000)player->position.x -= 3;
        if (player->position.x <= 100)player->position.x += 3;
        if (player->position.y >= 625)player->position.y -= 3;
        if (player->position.y <= 320)player->position.y += 3;
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        //slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
