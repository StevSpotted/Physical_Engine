//
// Created by Coco on 10/01/2023.
//

#ifndef C_PROJECTS_INIT_H
#define C_PROJECTS_INIT_H

#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "elements.h"

struct game *init_game(void);
void fill_air(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT]);

#endif //C_PROJECTS_INIT_H
