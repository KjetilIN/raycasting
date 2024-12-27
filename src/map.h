#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include "constants.h" // Include only necessary files

// Forward declaration
struct Ray; // Forward declaration of Ray_T
struct Player; // Forward declaration of Player_T

typedef struct Map {
    int grid[ROWS][COLS];
} Map_T;

/**
 * Init the map with default map
 * 
 * @param map given map to allocate memory for
 */
void init_default_map(Map_T *map);


/**
 * Render the given minimap to the SDL renderers
 * 
 * @param map given map
 * @param renderer given SDL renderer
 */
void render_map(Map_T *map, SDL_Renderer *renderer);

/**
 * Get the content for the map at given postion. 
 * 
 * Translates the given coordinate pair into indexes used to access the content of the wall grid.
 * 
 * @param map given map to use for searching 
 * @param x given X coord in the map
 * @param y given Y coord in the map
 * @return int that is in the given map position
 */
int wall_content(Map_T *map, float x, float y);

/**
 * Check if there is a wall in the grid 
 * 
 * @param map given map to search in 
 * @param x given X coord in the map
 * @param y given Y coord in the map
 * @return int 0 if there is no wall or 1 if there is a wall.
 */
int has_wall_at(Map_T *map, float x, float y);

/**
 * Renders floor, walls and roof for the given projection
 * 
 * @param rays list of all rays that has been casted from the players position
 * @param color_buffer given color buffer to fill for rendering 
 * @param player player that casts the projections 
 * @param wall_texture pointer to wolfenstein textures for the wall.
 */
void render_room_projection(struct Ray *rays, Uint32 *color_buffer, struct Player *player, Uint32 *wall_texture[8]);

#endif
