#include "ray.h"
#include "help_functions.h"
#include "map.h"
#include "player.h"
#include <limits.h>
#include <float.h> 
#include <SDL_stdinc.h>
#include <SDL.h>

void cast_ray(Ray_T *rays, struct Map *map, struct Player *player, float ray_angle, int strip_numb)
{   
    // Normalize the given angle 
    ray_angle = normalize_angle(ray_angle);

    // Find the direction that the ray is pointing in
    int is_ray_pointing_down = ray_angle > 0 && ray_angle < PI; 
    int is_ray_pointing_up = !is_ray_pointing_down;

    int is_ray_pointing_right = ray_angle < PI * 0.5 || ray_angle > PI * 1.5; 
    int is_ray_pointing_left = !is_ray_pointing_right;

    // Variables for intercept and step size
    float x_intercept, y_intercept; 
    float x_step, y_step; 

    // HORIZONTAL CHECK FIRST
    int found_horizontal_wall = 0; 
    float horizontal_wall_hit_x = 0;
    float horizontal_wall_hit_y = 0;
    int horizontal_wall_content = 0; 

    // Find the intercept 
    y_intercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
    y_intercept +=  is_ray_pointing_down ? TILE_SIZE : 0.0; 

    x_intercept = player->x + (y_intercept - player->y) / SDL_tan(ray_angle);

    // Find the step
    y_step = TILE_SIZE; 
    y_step *= is_ray_pointing_up ? -1.0 : 1.0; 

    x_step = TILE_SIZE / SDL_tan(ray_angle);
    x_step *= (is_ray_pointing_left && x_step > 0) ? -1.0 : 1.0; 
    x_step *= (is_ray_pointing_right && x_step < 0) ? -1.0 : 1.0;

    // Calculate the next intercept for the horizontal lines
    float next_horizontal_wall_hit_x = x_intercept;
    float next_horizontal_wall_hit_y = y_intercept; 

    // Loop until we find a wall
    while(next_horizontal_wall_hit_x >= 0 && next_horizontal_wall_hit_x <= WINDOW_WIDTH && next_horizontal_wall_hit_y >= 0 && next_horizontal_wall_hit_y <= WINDOW_HEIGHT){
        // Need to move into the cell that we want to check
        // We might be in-between cells
        float x_to_check = next_horizontal_wall_hit_x;
        float y_to_check = next_horizontal_wall_hit_y + (is_ray_pointing_up ? -1 : 0);

        float grid_content = wall_content(map, x_to_check, y_to_check);
        if (has_wall_at(map, x_to_check, y_to_check)){
            // Found a wall
            // Mark this wall hit
            found_horizontal_wall = 1; 
            horizontal_wall_hit_x = next_horizontal_wall_hit_x;
            horizontal_wall_hit_y = next_horizontal_wall_hit_y;
            horizontal_wall_content = grid_content;
            break;  

        }else{
            // Go to the next intersection
            next_horizontal_wall_hit_x += x_step;
            next_horizontal_wall_hit_y += y_step;
        }
    }


    // VERTICAL CHECK
    int found_vertical_wall = 0; 
    float vertical_wall_hit_x = 0;
    float vertical_wall_hit_y = 0;
    int vertical_wall_content = 0; 

    // Find the intercept 
    x_intercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
    x_intercept +=  is_ray_pointing_right ? TILE_SIZE : 0.0; 

    y_intercept = player->y + (x_intercept - player->x) * SDL_tan(ray_angle);

    // Find the step
    x_step = TILE_SIZE; 
    x_step *= is_ray_pointing_left ? -1.0 : 1.0; 

    y_step = TILE_SIZE * SDL_tan(ray_angle);
    y_step *= (is_ray_pointing_up && y_step > 0) ? -1.0 : 1.0; 
    y_step *= (is_ray_pointing_down && y_step < 0) ? -1.0 : 1.0;

    // Calculate the next intercept for the horizontal lines
    float next_vertical_wall_hit_x = x_intercept;
    float next_vertical_wall_hit_y = y_intercept; 

    // Loop until we find a wall
    while(next_vertical_wall_hit_x >= 0 && next_vertical_wall_hit_x <= WINDOW_WIDTH && next_vertical_wall_hit_y >= 0 && next_vertical_wall_hit_y <= WINDOW_HEIGHT){
        // Need to move into the cell that we want to check
        // We might be in-between cells
        float x_to_check = next_vertical_wall_hit_x + (is_ray_pointing_left ? -1 : 0);
        float y_to_check = next_vertical_wall_hit_y;

        float grid_content = wall_content(map, x_to_check, y_to_check);
        if (grid_content != 0){
            // Found a wall
            // Mark this wall hit
            found_vertical_wall = 1; 
            vertical_wall_hit_x = next_vertical_wall_hit_x;
            vertical_wall_hit_y = next_vertical_wall_hit_y;
            vertical_wall_content = grid_content;
            break;  

        }else{
            // Go to the next intersection
            next_vertical_wall_hit_x += x_step;
            next_vertical_wall_hit_y += y_step;
        }
    }

    // Calculate the wall hit for both horizontal and vertical hist
    float horizontal_hit_distance = found_horizontal_wall ? calculate_distance(player->x, player->y, horizontal_wall_hit_x, horizontal_wall_hit_y) : FLT_MAX;
    float vertical_hit_distance = found_vertical_wall ? calculate_distance(player->x, player->y, vertical_wall_hit_x, vertical_wall_hit_y) : FLT_MAX;

    // Use the smallest distance to set make the ray struct and set it in the ray list
    if (vertical_hit_distance < horizontal_hit_distance){
        // Vertical wall hit was the first wall that we found
        rays[strip_numb].distance = vertical_hit_distance; 
        rays[strip_numb].wall_hit_x = vertical_wall_hit_x;
        rays[strip_numb].wall_hit_y = vertical_wall_hit_y;
        rays[strip_numb].wall_hit_content = vertical_wall_content;
        rays[strip_numb].was_hit_vertical = 1; 
    }else{
        // Horizontal wall hit was the first wall that we found 
        rays[strip_numb].distance = horizontal_hit_distance; 
        rays[strip_numb].wall_hit_x = horizontal_wall_hit_x;
        rays[strip_numb].wall_hit_y = horizontal_wall_hit_y;
        rays[strip_numb].wall_hit_content = horizontal_wall_content;
        rays[strip_numb].was_hit_vertical = 0; 
    }

    // Set the common fields for the ray struct
    rays[strip_numb].ray_angle = ray_angle;
    rays[strip_numb].is_ray_pointing_down = is_ray_pointing_down;
    rays[strip_numb].is_ray_pointing_up = is_ray_pointing_up;
    rays[strip_numb].is_ray_pointing_left = is_ray_pointing_left;
    rays[strip_numb].is_ray_pointing_right = is_ray_pointing_right;

}

void cast_rays(Ray_T *rays, struct Map *map, struct Player *player)
{
    // Calculate the first ray to be cast
    // It starts from the left in the FOV of the player
    float current_ray_angle = player->rotation_angle - (FOV_ANGLE / 2);

    // Loop over each column
    for (int strip_numb = 0; strip_numb < RAY_COUNT; strip_numb++){
        // Cast the ray for the given column
        // Each ray has their own angle, starting from the left most angel, to the right most
        cast_ray(rays, map, player, current_ray_angle, strip_numb); 

        // Increment the ray angle for allowing the next angle to be cast
        current_ray_angle += FOV_ANGLE / RAY_COUNT;
    }
}

void render_rays(Ray_T *rays, SDL_Renderer *renderer, struct Player *player)
{
    // Set the color for the ray
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    // Loop over each ray and render it
    for (int i = 0; i < RAY_COUNT; i++){
        SDL_RenderDrawLineF(renderer, 
            MINIMAP_SCALE * player->x, 
            MINIMAP_SCALE * player->y, 
            MINIMAP_SCALE * rays[i].wall_hit_x, 
            MINIMAP_SCALE * rays[i].wall_hit_y
        );
    }
}
