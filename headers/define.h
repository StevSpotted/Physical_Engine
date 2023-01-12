
//
// Created by Coco on 10/01/2023.
//

#ifndef C_PROJECTS_DEFINE_H
#define C_PROJECTS_DEFINE_H

#include <SDL2/SDL.h>
#include "elements.h"


#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 900
#define WINDOW_GAME_PADDING_WIDTH 150
#define WINDOW_GAME_PADDING_HEIGHT 150
#define WINDOW_GAME_WIDTH 600
#define WINDOW_GAME_HEIGHT 600
#define PIXEL_WIDTH 300
#define PIXEL_HEIGHT 300

typedef int (*dir_check)(struct element[PIXEL_WIDTH][PIXEL_HEIGHT],int,int,int,int);

//struct with all information
struct game{
    struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT];
    SDL_Window *window;
    SDL_Renderer *renderer;
    //USER SETTINGS
    int brush_size;
    struct element current_element;
};



#endif //C_PROJECTS_DEFINE_H
