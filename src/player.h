#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "constants.h" // Only include this for ROWS/COLS

// Forward declaration
struct Map; // Forward declaration of Map_T

/**
 * Player struct
 * 
 * Represents where the player is in the minimap.
 * Used for figuring out where we should render the projection from.
 * 
 */
typedef struct Player {
    float x; 
    float y; 
    float width; 
    float height; 
    int turn_direction; 
    int walk_direction; 
    float rotation_angle;
    float walk_speed; 
    float rotation_speed;
} Player_T;

/**
 * Allocate memory for the player 
 * 
 * @param player player pointer to be allocated memory for.
 */
void init_player(Player_T **player);

/**
 * Move the player based on the player current state. 
 * 
 * Uses the structs parameters to choose how the player should move.
 * The structs is changed by the input controls (which changes the state of the player struct)
 * 
 * @param player player to move
 * @param map the given map to move in
 * @param delta_time delta time which represent how much movement the player should do
 */
void move_player(Player_T* player, struct Map* map, float delta_time);

/**
 * Free the memory for the given player
 * 
 * @param player player to free resources for
 */
void free_player(Player_T *player);

/**
 * Render the players position and direction within the map
 * 
 * @param player player to be rendered
 * @param renderer SDL renderer to use 
 */
void render_player(Player_T *player, SDL_Renderer *renderer);

#endif
