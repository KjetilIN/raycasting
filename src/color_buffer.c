#include "color_buffer.h"
#include "constants.h"
#include <SDL_stdinc.h>

void fill_color_buffer(Uint32 *color_buffer, Uint32 color)
{ 

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
