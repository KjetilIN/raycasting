#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "map.h"
#include "constants.h"
#include "ray.h"
#include "player.h"

// Map where
// - 1 represent a wall
// - 0 represents empty space
const int DEFAULT_MAP[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 2, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 5, 5}
};

void init_default_map(Map_T** map)
{
    *map = malloc(sizeof(Map_T));
    if (!map){
        fprintf(stderr, "Failed to allocate memory for map\n");
        exit(1);
    }
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            (*map)->grid[i][j] = DEFAULT_MAP[i][j];
        }
    }
}

void free_map(Map_T *map)
{
    if (map){
        free(map);
    }
}

void render_map(Map_T *map, SDL_Renderer* renderer)
{
    // Check if map has been initalized
    if (map == NULL){
        fprintf(stderr, "Map was not initalized for rendering\n");
        exit(1);
    }

    // Render map
    for (int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            // X and y position of the given tile
            int tile_x = j*TILE_SIZE; 
            int tile_y = i*TILE_SIZE; 

            // Tile color is either black or white, depending of if there is a wall there; 
            int tile_color = map->grid[i][j] != 0 ? 255 : 0; 

            // Color in the tile at given position 
            SDL_SetRenderDrawColor(renderer, tile_color, tile_color, tile_color, 255);
            
            // Create the tile and render it
            SDL_FRect rect = {
                MINIMAP_SCALE * tile_x, 
                MINIMAP_SCALE * tile_y,
                MINIMAP_SCALE * TILE_SIZE,
                MINIMAP_SCALE * TILE_SIZE
            };
            SDL_RenderFillRectF(renderer, &rect);
        }
    }
}

int wall_content(Map_T *map, float x, float y)
{
    // Map boundary is walls
    if(x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT){
        return 1;
    }

    // Grid position 
    int grid_x = (int) floor(x / TILE_SIZE);
    int grid_y = (int) floor(y / TILE_SIZE);

    // Return the content of the grid at that given position. 
    return map->grid[grid_y][grid_x];
}

int has_wall_at(Map_T *map, float x, float y)
{
    // Map boundary is walls
    if(x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT){
        return 1;
    }

    // Grid position 
    int grid_x = (int) floor(x / TILE_SIZE);
    int grid_y = (int) floor(y / TILE_SIZE);

    // Return the content of the grid at that given position. 
    return map->grid[grid_y][grid_x] != 0;
}

void render_room_projection(struct Ray *rays[RAY_COUNT], Uint32 *color_buffer, struct Player *player, Uint32 *wall_texture[8])
{
    for (int i = 0; i < RAY_COUNT; i++){
        // Calculate the correct distance for fixing the fish eye effect
        float correct_distance = rays[i]->distance * cos(rays[i]->ray_angle - player->rotation_angle);
        float distance_projection_plane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE /2);
        float projection_wall_height = (TILE_SIZE / correct_distance) * distance_projection_plane;

        // Calculate the strip height of the wall 
        int wall_strip_height = (int) projection_wall_height;
        
        // Find the top pixel of the strip
        int wall_top_pixel = (WINDOW_HEIGHT / 2) - (wall_strip_height / 2);
        wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;

        // Find the bottom pixel
        int wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (wall_strip_height / 2);
        wall_bottom_pixel = wall_bottom_pixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wall_bottom_pixel;

        // Render roof
        for (int y = 0; y < wall_top_pixel; y++){
            color_buffer[(WINDOW_WIDTH*y)+i] = DARK_GRAY; 
        }


        // Get the current wall ID
        // Will be used as a index to the textures in the array
        int TEXTURE_INDEX = rays[i]->wall_hit_content - 1;


        // We calculate the offset for texture in X axis
        int texture_offset_x; 
        if (rays[i]->was_hit_vertical){
            // vertical hit
            texture_offset_x = (int)rays[i]->wall_hit_y % TILE_SIZE; 
        }else{
            // horizontal hit 
            texture_offset_x = (int)rays[i]->wall_hit_x % TILE_SIZE; 
        }

        // Render the strip from the top to the bottom
        for (int y = wall_top_pixel; y < wall_bottom_pixel; y++){
            // Get the texture color for the given pixel
            // Use the texture buffer to access the color
            // First calculating the offset in Y 
            int distance_to_top = y + (wall_strip_height/2) - (WINDOW_HEIGHT / 2); 
            int texture_offset_y = distance_to_top* ((float)TEXTURE_HEIGHT / wall_strip_height); 

            // Get the color
            Uint32 color = wall_texture[TEXTURE_INDEX][(TEXTURE_WIDTH * texture_offset_y) + texture_offset_x];
            
            // Set the color 
            color_buffer[(WINDOW_WIDTH * y) + i] = color; 
        }

        // Render floor
        for (int y = wall_bottom_pixel; y < WINDOW_HEIGHT; y++){
            color_buffer[(WINDOW_WIDTH * y) + i] = LIGHT_GRAY;
        }
    }
}
