#include <SDL_stdinc.h>
#include <SDL.h>
#ifndef COLOR_BUFFER_H
#define COLOR_BUFFER_H

/**
 * Fill the color buffer with a given color
 * 
 * @param color_buffer the buffer to be filled
 * @param color color to fill the buffer with
 */
void fill_color_buffer(Uint32 *color_buffer, Uint32 color);

/**
 * Render the color buffer by copying the content to the texture and then render it
 * 
 * @param renderer renderer
 * @param color_buffer the color buffer that we want to render
 * @param color_buffer_texture the color buffer texture
 */
void render_color_buffer(SDL_Renderer *renderer, Uint32 *color_buffer, SDL_Texture *color_buffer_texture);

#endif