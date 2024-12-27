#include <SDL_stdinc.h>
#include <SDL.h>
#ifndef COLOR_BUFFER_H
#define COLOR_BUFFER_H

/**
 * Allocates memory for the given color buffer pointer.
 * 
 * Allocates Uint32 for each pixel in the screen. 
 * Each element in the buffer represent a color for the given screen.
 * Will terminate the program, if it was not able to allocate memory for the buffer.
 * 
 * @param color_buffer color buffer pointer that requires the memory
 */
void malloc_color_buffer(Uint32 **color_buffer);

/**
 * Free the dynamic memory for the color buffer.
 * 
 * @param color_buffer buffer to be freed
 */
void free_color_buffer(Uint32 *color_buffer);

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