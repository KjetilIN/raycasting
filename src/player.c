#include "player.h"
#include "constants.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "map.h"

void init_player(Player_T *player)
{
    player->x = WINDOW_WIDTH / 2;
    player->y = WINDOW_HEIGHT / 2;  
    player->width = 5;
    player->height = 5; 
    player->turn_direction = 0; 
    player->walk_direction = 0; 
    player->rotation_angle = PI / 2; 
    player->walk_speed = 200; 
    player->rotation_speed = 50 * (PI / 180);
}

void move_player(Player_T *player, struct Map* map, float delta_time)
{   
    // Makes the player able to rotate
    player->rotation_angle += player->turn_direction*player->rotation_speed * delta_time;

    // Moves the player in a direction on the axis
    float movestep = player->walk_direction * player->walk_speed * delta_time;
    
    // Calculate the new x and y positions 
    float new_x = player->x + SDL_cos(player->rotation_angle) * movestep; 
    float new_y = player->y + SDL_sin(player->rotation_angle) * movestep;

    // Set new x and y postion for the player
    if (!has_wall_at(map, new_x, new_y)){
        player->x = new_x;
        player->y = new_y; 
    }
}   

void render_player(Player_T* player, SDL_Renderer* renderer)
{
    // Create and render the player rectangle 
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_FRect player_rect = {
        MINIMAP_SCALE * player->x,
        MINIMAP_SCALE * player->y, 
        MINIMAP_SCALE * player->width,
        MINIMAP_SCALE * player->height
    };
    // Draw the rectangle itself
    SDL_RenderFillRectF(renderer, &player_rect);

    // Render the direction where the player is looking at
    SDL_RenderDrawLineF(renderer, 
        MINIMAP_SCALE * player->x,
        MINIMAP_SCALE * player->y, 
        MINIMAP_SCALE * player->x + SDL_cos(player->rotation_angle) * 40,
        MINIMAP_SCALE * player->y + SDL_sin(player->rotation_angle) * 40
    );
}
