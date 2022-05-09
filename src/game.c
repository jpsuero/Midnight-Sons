#define RAND_MAX =4;
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "simple_logger.h"

#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "gf2d_draw.h"
#include "gfc_audio.h"
#include "gfc_text.h"

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
#include "aimbot.h"
#include "BOSS.h"
#include "aim_shooter.h"
#include "chair_breakable.h"
#include "health_pickup.h"
#include "stamina_pickup.h"
#include "speed_pickup.h"
#include "strength_pickup.h"
#include "Portal.h"
#include "eyeball_ent.h"
#include "shuma_goreth.h"
#include "hydrant.h"


int main(int argc, char * argv[])
{
    /*variable declarations*/
    int debug = 0;
    int attack = 0;
    int attack2 = 0;
    int level = 0;
    int highscore = 0;
    int score = 0;
    int done = 0;
    int i = 0;
    int count = 0;
    int ouchCount = 0;
    int enemyCount = 1;
    int blastCount = 1;
    int staminaCount = 0;
    int enemySwap = 0;
    int colliding;
    int enemy2col;
    int blast_collision = 0;
    int bossCollision = 0;
    int hydrant_collision;
    int enviroCollsion;
    int chairCollision;
    int healthCollision, speedCollision, staminaCollision, strengthCollision;
    int timer = 0;
    int BOSSMODE = 0;
    int vountBoss = 0;
    float spawnPos = 1200;
    float skullHeight = 300;
    const Uint8 * keys;
    Sprite* icon, * health, * stamina;
    
    int mx,my;
    int position = 70;
    float mf = 0;
    Sprite* mouse;
    Vector4D mouseColor = {255,100,255,200};
    TileMap *tilemap;
    Entity* portal;
    Entity* player;
    Entity* enemy, * enemy2 = NULL;
    Entity* eyeball_blast = NULL;
    Entity* bg;
    Entity* BOSS = NULL;
    Entity* chair;
    Entity* health_pickup;
    Entity* speed_pickup;
    Entity* stamina_pickup;
    Entity* strength_pickup;
    Entity* hydrant;

    //audio
    Mix_Music* music;
    Sound* levelup;

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
    gfc_audio_init(256, 16, 4, 1, 1, 1);
    SDL_ShowCursor(SDL_DISABLE);

    //joystick
    SDL_Init(SDL_INIT_JOYSTICK);

    SDL_Joystick* joystick;

    SDL_JoystickEventState(SDL_ENABLE);
    joystick = SDL_JoystickOpen(0);


    /*demo setup*/
    bg = moving_bg_new(vector2d(0, 0));
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);
    player = venom_new(vector2d(300, 500));
    player->health = 5;
    portal = portal_ent_new(vector2d(7000, 500));
    enemy = skull_ent_new(vector2d(spawnPos, 300));
    icon = gf2d_sprite_load_image("images/venom_icon.png");
    health = gf2d_sprite_load_image("images/health.png");
    stamina = gf2d_sprite_load_image("images/stamina.png");
    highscore = highscore_load("levels/testlevel.json");
    chair = chair_ent_new(vector2d(600, 400));
    hydrant = hydrant_ent_new(vector2d(1500, 330));
    health_pickup = health_ent_new(vector2d(900, 650));
    stamina_pickup = stamina_ent_new(vector2d(3000, 400));
    speed_pickup = speed_ent_new(vector2d(4000, 650));
    strength_pickup = strength_ent_new(vector2d(5000, 400));
    music = Mix_LoadMUS("music/UAMenu.mp3");
    levelup = gfc_sound_load("SFX/levelup.wav", 10, 0);
    Mix_PlayMusic(music, -1);

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
        chairCollision = collision_check(player, chair);
        healthCollision = collision_check(player, health_pickup);
        staminaCollision = collision_check(player, stamina_pickup);
        speedCollision = collision_check(player, speed_pickup);
        strengthCollision = collision_check(player, strength_pickup);
        hydrant_collision = collision_check(player, hydrant);
        enviroCollsion = collision_check(hydrant, enemy);
        if (eyeball_blast) {  blast_collision= collision_check(player, eyeball_blast); }
        if (enemy2) { enemy2col = collision_check(player, enemy2); }

        
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            // draw other game elements
        
            //tilemap_draw(tilemap);
            entity_manager_draw_all();
            //UI elements last
            gf2d_draw_rect(player->hitbox, vector4d(0, 0, 255, 200));
            gf2d_draw_rect(enemy->hitbox, vector4d(255, 0, 0, 255));
            gf2d_draw_rect(hydrant->hitbox, vector4d(255, 0, 0, 255));
            if (eyeball_blast)
            {
                gf2d_draw_rect(eyeball_blast->hitbox, vector4d(255, 0, 0, 255));
            }
            if(BOSS)gf2d_draw_rect(BOSS->hitbox, mouseColor);
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
        
        //BOSS MODE
        //BOSS MODE
        if (keys[SDL_SCANCODE_L])
        {
            BOSSMODE = 1;
            BOSS = boss_ent_new(vector2d(200, 500));
        }

        if (BOSSMODE)
        {
            bossCollision = collision_check(BOSS, player);
            if (bossCollision)player->health = 0;
        }


        //enemy spawner
        if (enemyCount == 0 && !BOSSMODE)
        {
            if (spawnPos == 1200)
            {
                spawnPos = 200;
            }
            else
            {
                spawnPos = 1200;
                if (enemySwap == 1)spawnPos = 500;
                if (enemySwap == 2)spawnPos = 1000;
            }
            if (skullHeight == 300)
            {
                skullHeight = 500;
            }
            else
            {
                skullHeight = 300;
            }
            
            if (enemySwap == 0)enemy = skull_ent_new(vector2d(spawnPos, 300));
            else if (enemySwap == 2)enemy = shooter_ent_new(vector2d(200, 500));
            else if (enemySwap == 1) { enemy = aimbot_ent_new(vector2d(1500, skullHeight)); }
            else if (enemySwap == 4)enemy = shuma_ent_new(vector2d(200, 500));
            else { enemy = eyeball_ent_new(vector2d(1500, skullHeight)); }
            enemyCount = 1;
        }

        //enemy swapper for demo
        if (keys[SDL_SCANCODE_6])
        {
            entity_free(enemy);
            enemySwap = 1;
        }
        if (keys[SDL_SCANCODE_7])
        {
            entity_free(enemy);
            enemySwap = 2;
        }
        if (keys[SDL_SCANCODE_8])
        {
            entity_free(enemy);
            enemySwap = 0;
        }
        if (keys[SDL_SCANCODE_5])
        {
            entity_free(enemy);
            enemySwap = 3;
        }
        if (keys[SDL_SCANCODE_4])
        {
            entity_free(enemy);
            enemySwap = 4;
        }

        if (keys[SDL_SCANCODE_K])
        {
            entity_free(enemy);
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
        if (player->isAttacking == 1 && colliding && player->frame > 2)
        {
            enemy->health -= 1 * player->strength;
            player->isAttacking = 0;
        }
        
        if (player->isAttacking == 2 && colliding && player->frame > 2)
        {
            enemy->health -= 2 * player->strength;
            player->isAttacking = 0;
        }

        if (player->isAttacking == 3 && colliding && player->frame > 2)
        {
            enemy->health -= 3 * player->strength;
            player->isAttacking = 0;
        }
        //hurt enemy 2
        if (enemy2)
        {
            if (player->isAttacking == 1 && enemy2col && player->frame > 2)
            {
                enemy2->health -= 1 * player->strength;
                player->isAttacking = 0;
            }

            if (player->isAttacking == 2 && enemy2col && player->frame > 2)
            {
                enemy2->health -= 2 * player->strength;
                player->isAttacking = 0;
            }

            if (player->isAttacking == 3 && enemy2 && player->frame > 2)
            {
                enemy2->health -= 3 * player->strength;
                player->isAttacking = 0;
            }
        }
        
        
        //player throw
        if (player->isAttacking == 4 && colliding && player->frame > 2)
        {
            enemy->thrown = 1;
        }
        
        if (enemy->thrown)
        {
                enemy->draw_scale.x +=1;
                enemy->draw_scale.y +=1;
                enemy->velocity.y - 1;
                enemy->velocity.x = 0;
        }


        //enemy target update
        if (!player->invisible && enemySwap != 2 && enemySwap != 4)
        {
            enemy->target = player->position;
        }

        
        //background and more update
        if (player->velocity.x > 0)
        {
            bg->speed = 1;
            chair->speed = 1;
            health_pickup->speed = 1;
            speed_pickup->speed = 1;
            stamina_pickup->speed = 1;
            strength_pickup->speed = 1;
            portal->speed = 1;
            enemy->speed = 1;
            hydrant->health = 1;
            if(enemy2){ enemy2->speed = 1; }
        }
        if (player->velocity.x < 0)
        {
            bg->speed = -1;
            chair->speed = -1;
            health_pickup->speed = -1;
            speed_pickup->speed = -1;
            stamina_pickup->speed = -1;
            strength_pickup->speed = -1;
            portal->speed = -1;
            enemy->speed = -1;
            hydrant->health = -1;
            if (enemy2) { enemy2->speed = -1; }
        }
        if (player->velocity.x == 0)
        {
            bg->speed = 0;
            chair->speed = 0;
            health_pickup->speed = 0;
            speed_pickup->speed = 0;
            stamina_pickup->speed = 0;
            strength_pickup->speed = 0;
            portal->speed = 0;
            enemy->speed = 0;
            hydrant->health = 0;
            if (enemy2) { enemy2->speed = 0; }
        }

        //skull hurt player
        if (enemySwap == 0)
        {
            if (colliding && enemy->thrown == 0)
            {
                timer++;
                if (timer >= 90)
                {
                    player->health--;
                    timer = 0;
                }
            }
            else
            {
                timer = 0;
            }
        }

        

        //hydrant kill enemy
        if (enviroCollsion)
        {
            enemy->health--;
        }

        //shuma hurt player
        if (enemySwap == 4)
        {
            if (colliding)
            {
                if (attack2 == 0 && enemy->buffer >150)
                {
                    enemy->buffer = 0;
                    attack2 = 1;
                    player->health -= 2;
                }
            }
            else
            {
                attack2 = 0;
            }
        }

        //track target hitbox
        enemy->target_hitbox = player->hitbox;
        if (eyeball_blast) { eyeball_blast->target_hitbox = player->hitbox; }

        //eyeball blast
        if (enemySwap == 3)
        {
            if(enemy->buffer >= 100)
            {
                
                if (player->position.x < enemy->position.x)
                {
                    eyeball_blast = eyeball_blast_ent_new(enemy->position);
                    blastCount = 1;
                    eyeball_blast->velocity.x = -3;
                    enemy->buffer = 0;
                }
                else
                {
                    eyeball_blast = eyeball_blast_ent_new(enemy->position);
                    blastCount = 1;
                    eyeball_blast->velocity.x = 3;
                    enemy->buffer = 0;
                }
            }
        }
        //eyeball blast hurt player
        if (blast_collision && ouchCount == 0)
        {
            player->health -= 2;
            ouchCount = 1;
        }

        //player level updater
        if(score==20)
        {
            player->level = 2;
            score += 1;
            gfc_sound_play(levelup, 0, 50, -1, -1);
        }
        if (score == 30)
        {
            player->level = 3;
            score += 1;
            gfc_sound_play(levelup, 0, 50, -1, -1);
        }
        if (score == 35)
        {
            player->level = 4;
            score += 1;
            gfc_sound_play(levelup, 0, 50, -1, -1);
        }


        if (!blast_collision)
        {
            ouchCount = 0;
        }

        //hurt player
        if (enemy->isAttacking == 1 && count == 0 && colliding)
        {
            player->health -= 1;
            count = 1;
        }

        if (enemy->isAttacking == 0)
        {
            count = 0;
        }
        
        if (keys[SDL_SCANCODE_H])
        {
            slog("%i", highscore);
        }
        
        //hydrant manager
        if (hydrant_collision && player->isAttacking)
        {
            hydrant->speed = 1;
        }
        
        //chair manager
        if (chairCollision && player->isAttacking)
        {
            chair->sprite = gf2d_sprite_load_image("images/brokenbench.png");
        }

        //health pickup manager
        if (healthCollision)
        {
            player->health = 5;
            entity_free(health_pickup);
        }

        //stamina pickup manager
        if(staminaCollision)
        {
            player->stamina = 5;
            entity_free(stamina_pickup);
        }

        //speed pickup manager
        if (speedCollision)
        {
            player->speed = 6;
            entity_free(speed_pickup);
        }

        //strength pickup manager
        if (strengthCollision)
        {
            player->strength = 2;
            entity_free(strength_pickup);
        }

        //give stamina back
        staminaCount++;
        if (staminaCount >= 200 && player->stamina < 5)
        {
            player->stamina++;
            staminaCount = 0;
        }

        //kill enemy
        if (enemy->health <= 0 || enemy->draw_scale.x >=20 || enemy->draw_scale.x<=0)
        {
            entity_free(enemy);
            enemyCount = 0;
            if (level == 3)
            {
                enemySwap ++;
                if (enemySwap == 5)
                {
                    enemySwap = 0;
                }
                if (enemySwap == 2)
                {
                    enemySwap = 3;
                }
            }

            score++;
        }



        //last level
        if (level == 3 && bg->position.x <= -4000 && vountBoss ==0)
        {
            vountBoss = 1;
            BOSSMODE = 1;
            BOSS = boss_ent_new(vector2d(200, 500));
        }
        

        if (score>highscore)
        {
            highscore_save(score);
        }

        if (player->health <= 0) done = 1;

        if (bg->position.x <= -5000 && level != 3)
        {
            if (level == 0)
            {
                Mix_HaltMusic();
                health_pickup = health_ent_new(vector2d(900, 650));
                //enemy2 = shuma_ent_new(vector2d(200, 500));
                player->position = vector2d(300, 500);
                bg->sprite = gf2d_sprite_load_image("images/backgrounds/xmenarcade.png");
                portal->position = (vector2d(7000, 500));
                bg->position = vector2d(0, 0);
                music = Mix_LoadMUS("music/KHBattle.mp3");
                Mix_PlayMusic(music, -1);
                level = 1;
                entity_free(enemy);
                enemySwap = 1;
            }
            else if (level == 1)
            {
                Mix_HaltMusic();
                health_pickup = health_ent_new(vector2d(900, 650));
                player->position = vector2d(300, 500);
                bg->sprite = gf2d_sprite_load_image("images/backgrounds/japan.jpg");
                portal->position = (vector2d(7000, 500));
                bg->position = vector2d(0, 10);
                music = Mix_LoadMUS("music/japan_music.mp3");
                Mix_PlayMusic(music, -1);
                level = 2;
                entity_free(enemy);
                enemySwap = 3;
            }
            else if (level == 2)
            {
                Mix_HaltMusic();
                health_pickup = health_ent_new(vector2d(900, 650));
                player->position = vector2d(300, 500);
                bg->sprite = gf2d_sprite_load_image("images/backgrounds/hellbg.png");
                //portal->position = (vector2d(7000, 500));
                bg->position = vector2d(0, 10);
                music = Mix_LoadMUS("music/finalboss.mp3");
                Mix_PlayMusic(music, -1);
                level = 3;
                entity_free(enemy);
            }
        }

       
        //player bounds
        if (player->position.x >= 800)player->position.x -= 3;
        if (player->position.x <= 100)player->position.x += 3;
        if (player->position.y >= 625)player->position.y -= 3;
        if (player->position.y <= 320)player->position.y += 3;
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        //slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }

    SDL_JoystickClose(joystick);
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    gfc_sound_clear_all();
    slog("---==== END ====---");
    return 0;
}

/*eol@eof*/
