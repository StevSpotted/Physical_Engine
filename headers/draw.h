//
// Created by Coco on 10/01/2023.
//

#ifndef C_PROJECTS_DRAW_H
#define C_PROJECTS_DRAW_H

#include <SDL2/SDL.h>
#include "define.h"
#include "elements.h"

void update_render(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT], SDL_Renderer *renderer);
void draw_GUI(SDL_Renderer *renderer);


#endif //C_PROJECTS_DRAW_H
