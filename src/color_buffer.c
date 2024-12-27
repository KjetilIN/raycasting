#include "color_buffer.h"
#include "constants.h"
#include <SDL_stdinc.h>

void malloc_color_buffer(Uint32 **color_buffer) {
    // Allocate memory for the color buffer
    *color_buffer = (Uint32 *)malloc(sizeof(Uint32) * WINDOW_WIDTH * WINDOW_HEIGHT);

    // Check allocation was successful
    if (!*color_buffer) {
        fprintf(stderr, "Could not allocate memory for the color buffer\n");
        exit(1);
    }
}


void free_color_buffer(Uint32 *color_buffer)
{
    if(color_buffer){
        free(color_buffer);
    }
}

void fill_color_buffer(Uint32 *color_buffer, Uint32 color)
{   
    if(!color_buffer){
        fprintf(stderr, "cannot fill color buffer on a null pointer \n");
        exit(1);
    }

    //Fil the color buffer with the given color
    for(int x = 0; x < WINDOW_WIDTH; x++){
        for(int y = 0; y < WINDOW_HEIGHT; y++){
            color_buffer[(WINDOW_WIDTH * y) + x] = color;
        }
    }
}

void render_color_buffer(SDL_Renderer *renderer, Uint32 *color_buffer, SDL_Texture *color_buffer_texture)
{   
    SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)(Uint32)WINDOW_WIDTH * sizeof(Uint32));
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}
