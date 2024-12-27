#include "constants.h"
#include <stdio.h>
#include <math.h>
#include <SDL_stdinc.h>

float normalize_angle(float angle){
    // Take the remainder
    angle = SDL_fmod(angle, TWO_PI);

    // Handle the case when the angle becomes negative
    if (angle < 0){
        angle = TWO_PI + angle;
    }

    return angle; 
}

float calculate_distance(float x1, float y1, float x2, float y2){
    return SDL_sqrtf((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}