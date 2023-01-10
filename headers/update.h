//
// Created by Coco on 10/01/2023.
//

#ifndef C_PROJECTS_UPDATE_H
#define C_PROJECTS_UPDATE_H


#include <stdlib.h>
#include <SDL2/SDL.h>
#include "define.h"
#include "elements.h"


int check_vertical(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT],int x,int y, int update,int direction);
int check_vertical_right(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT],int x,int y, int update,int direction);
int check_vertical_left(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT],int x,int y, int update,int direction);
int check_left(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT],int x,int y, int update,int direction);
int check_right(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT],int x,int y, int update,int direction);
int switch_points(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT],int x1,int y1,int x2,int y2,int update);
void spawn_element(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT],struct element type,int x,int y,int frame);
void check_movement(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT],int x,int y,int update);
void update_gravity(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT],int update);
void fill_air(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT]);
void draw_under_mouse(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT], SDL_Surface *surface, struct element type,int brush_size,int frame);

#endif //C_PROJECTS_UPDATE_H
