#ifndef RAY_H
#define RAY_H

#include "constants.h" 
#include <SDL.h>

// Forward declarations
struct Map;
struct Player; 

typedef struct Ray {
    // Ray information
    float ray_angle; 
    float wall_hit_x;
    float wall_hit_y; 
    float distance; 
    int was_hit_vertical; 

    // Keep track of direction
    int is_ray_pointing_up; 
    int is_ray_pointing_down; 
    int is_ray_pointing_left;
    int is_ray_pointing_right; 

    // Content and color of the ray hit
    int wall_hit_content; 
} Ray_T;

/**
 * Cast a ray on the given map from the given player, and set the ray struct in the array list of rays.
 * 
 * @param rays the list of rays
 * @param map the map to cast array in
 * @param player the player to cast from
 * @param ray_angle the angle the ray currently have
 * @param strip_numb the column strip id, used as a index to place the ray in the ray list
 */
void cast_ray(Ray_T *rays, struct Map *map, struct Player *player, float ray_angle, int strip_numb);

/**
 * Casts all the rays from the given player position
 * 
 * Stores the casted rays in the list of rays.
 * 
 * @param rays list of rays 
 * @param map the map to cast all rays in 
 * @param player given player to cast rays from 
 */
void cast_rays(Ray_T *rays, struct Map *map, struct Player *player);

/**
 * Render the rays in the minimap from the given player position. 
 * 
 * Will appear as red lines in the minimap.
 * Each ray starts from the direction the player is, until the wall.
 * 
 * @param rays list of rays that has been casted
 * @param renderer SDL renderer to use for rendering the rays
 * @param player player that have been used to cast rays from
 */
void render_rays(Ray_T *rays, SDL_Renderer *renderer, struct Player *player);

#endif

