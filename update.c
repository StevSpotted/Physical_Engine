//
// Created by Coco on 10/01/2023.
//

#include "headers/update.h"

int switch_points(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT],int x1,int y1,int x2,int y2,int update){
    if(x1<0 || x1>=PIXEL_WIDTH  || y1<0 || y1>PIXEL_HEIGHT || x2<0 || x2>=PIXEL_WIDTH  || y2<0 || y2>PIXEL_HEIGHT){
        return 0;
    }
    struct element elem1=grille[x1][y1];
    struct element elem2=grille[x2][y2];
    if(elem1.last_update==update || elem2.last_update==update){
        return 0;
    }
    elem1.last_update=update;
    elem2.last_update=update;

    grille[x1][y1]=elem2;
    grille[x2][y2]=elem1;
    return 1;
}

int check_vertical(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT],int x,int y, int update,int direction){
    if ((y+direction<PIXEL_HEIGHT)&& grille[x][y + direction].weight == 0 && grille[x][y + direction].weight!=grille[x][y].weight) {//Check bottom first
        return switch_points(grille, x, y, x, y + direction, update);
    }
    return 0;
}

int check_vertical_right(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT],int x,int y, int update,int direction) {
    if ((y + direction < PIXEL_HEIGHT && y + direction > 0) && (x + 1 < PIXEL_WIDTH) &&
        grille[x + 1][y + direction].weight <= 0 && grille[x + 1][y + direction].weight != grille[x][y].weight) {
        return switch_points(grille, x, y, x + 1, y + direction, update);
    }
    return 0;
}

int check_vertical_left(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT],int x,int y, int update,int direction) {
    if ((y+direction<PIXEL_HEIGHT&& y+direction>0)&& (x - 1 >= 0)&& grille[x - 1][y + direction].weight <= 0 && grille[x-1][y + direction].weight!=grille[x][y].weight) {
        return switch_points(grille, x, y, x - 1, y + direction, update);
    }
    return 0;
}

int check_left(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT],int x,int y, int update,int direction) {
    if ((x - 1 >= 0) && grille[x - 1][y].weight <= 0 && grille[x - 1][y].weight != grille[x][y].weight) {//check left
        return switch_points(grille, x, y, x - 1, y, update);
    }
    return 0;
}

int check_right(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT],int x,int y, int update,int direction){
    if ((x + 1 < PIXEL_WIDTH) && grille[x + 1][y].weight == 0 && grille[x+1][y].weight!=grille[x][y].weight) {//check right
        return switch_points(grille, x, y, x + 1, y,update);
    }
    return 0;
}

void spawn_element(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT],struct element type,int x,int y,int frame){
    if(x>=0 && x< PIXEL_WIDTH && y>=0 && y<PIXEL_HEIGHT) {
        grille[x][y] = type;
        grille[x][y].spawn_frame = frame;
    }
}



void check_movement(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT],int x,int y,int update){
    struct element elemtemp = grille[x][y];
    int direction=elemtemp.gravity_scale;
    if(elemtemp.gaz){
        direction=-elemtemp.gravity_scale;
    }
    if(elemtemp.id<0){
        struct element elemtemp2= get_element_by_id(elemtemp.id);

        if(elemtemp2.gaz==0 && (grille[x][y+1].weight<elemtemp2.weight || grille[x][y+1].weight==0)){
            spawn_element(grille,elemtemp2,x,y+1, update);
        }
        else if(elemtemp2.gaz==1 && (grille[x][y-1].weight<elemtemp2.weight || grille[x][y-1].weight==0)){
            spawn_element(grille,elemtemp2,x,y-1, update);
        }
    }
    else if(elemtemp.lifetime>0 && elemtemp.last_update>elemtemp.spawn_frame+elemtemp.lifetime){
        grille[x][y]=air();
    }
    else if(elemtemp.last_update!=update){
        if(elemtemp.gravity_scale>0) {
            if (y + 1 < PIXEL_WIDTH) {
                if (elemtemp.pyramid_fall) {
                    if(check_vertical(grille,x,y,update,direction)==0) {
                        if(update%2){
                            if (check_vertical_left(grille, x, y, update, direction) == 0) {
                                check_vertical_right(grille, x, y, update, direction);
                            }
                        }
                        else if (check_vertical_right(grille, x, y, update, direction) == 0) {
                            check_vertical_left(grille, x, y, update, direction);
                        }
                    }
                }

                else if (elemtemp.fluid) {
                    //Also check all possibilities

                    dir_check func[5] = {&check_vertical,&check_vertical_left, &check_vertical_right, &check_right, &check_left};
                    int already_check[5] = {0};
                    for (int i = 0; i < 5; i++) {
                        int succes = 0;
                        int loop = 1;
                        while (loop) {
                            int temp_id = rand() % 5;
                            if (already_check[temp_id] == 0) {
                                succes = func[temp_id](grille, x, y, update, direction);
                                already_check[temp_id] = 1;
                                loop = 0;
                            }
                        }
                        if (succes) {
                            break;
                        }

                    }
                } else {
                    if (grille[x][y + direction].weight == 0 && grille[x][y + direction].weight!=elemtemp.weight) {
                        switch_points(grille, x, y, x, y + direction,update);
                    }
                }
            }
        }
    }
}


void update_gravity(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT],int update) {
    for (int x = PIXEL_WIDTH - 1; x >= 0; x--) {
        for (int y = PIXEL_HEIGHT - 1; y >= 0; y--) {
            check_movement(grille,x,y,update);
        }
    }
}

void fill_air(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT]) {
    for (int i = 0; i < PIXEL_WIDTH; i++) {
        for (int j = 0; j < PIXEL_HEIGHT; j++) {
            grille[i][j] = air();
        }
    }

}

void draw_under_mouse(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT], SDL_Surface *surface, struct element type,int brush_size,int frame) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x > WINDOW_GAME_PADDING_HEIGHT && x < WINDOW_GAME_PADDING_HEIGHT + WINDOW_HEIGHT &&
        y > WINDOW_GAME_PADDING_WIDTH && y < WINDOW_GAME_PADDING_WIDTH + WINDOW_WIDTH) {
        x = (x - WINDOW_GAME_PADDING_WIDTH) / (WINDOW_GAME_WIDTH / PIXEL_WIDTH);
        y = (y - WINDOW_GAME_PADDING_HEIGHT) / (WINDOW_GAME_HEIGHT / PIXEL_HEIGHT);
        for (int i = x - brush_size / 2; i < x + brush_size / 2; i++) {
            for (int j = y - brush_size; j < y + brush_size / 2; j++) {
                if(i>=0 && i<PIXEL_WIDTH && j>=0 && j<PIXEL_HEIGHT){
                    spawn_element(grille,type,i,j,frame);

                }

            }
        }
    }
}


