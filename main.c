#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>


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

void update_render(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT], SDL_Renderer *renderer){
    int xsize= (WINDOW_GAME_WIDTH / PIXEL_WIDTH);
    int ysize= (WINDOW_GAME_HEIGHT / PIXEL_HEIGHT);
    SDL_Rect pix={WINDOW_GAME_PADDING_HEIGHT,WINDOW_GAME_PADDING_WIDTH,xsize,ysize};
    for(int x=0;x<PIXEL_WIDTH;x++) {
        for (int y=0;y<PIXEL_HEIGHT;y++) {
            SDL_SetRenderDrawColor(renderer,grille[x][y].color.r,grille[x][y].color.g,grille[x][y].color.b,grille[x][y].color.a);
            SDL_RenderFillRect(renderer,&pix);
            pix.x = (x * xsize)+WINDOW_GAME_PADDING_HEIGHT;
            pix.y = (y* ysize)+WINDOW_GAME_PADDING_WIDTH;
        }
    }
    SDL_RenderPresent(renderer);
}


int switch_points(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT],int x1,int y1,int x2,int y2,int update){
    if(x1<0 || x1>=PIXEL_WIDTH  || y1<0 || y1>PIXEL_HEIGHT || x2<0 || x2>=PIXEL_WIDTH  || y2<0 || y2>PIXEL_HEIGHT){
        return 0;
    }
    struct element elem1=grille[x1][y1];
    struct element elem2=grille[x2][y2];
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


void check_movement(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT],int x,int y,int update){
    struct element elemtemp = grille[x][y];
    int direction=elemtemp.gravity_scale;
    if(elemtemp.gaz){
        direction=-elemtemp.gravity_scale;
    }
    if(elemtemp.last_update!=update){
        if(elemtemp.gravity_scale>0) {
            if (y + 1 < PIXEL_WIDTH) {
                if (elemtemp.pyramid_fall) {

                    //randomly check all possibility
                    dir_check func[3]={&check_vertical,&check_vertical_left,&check_vertical_right};
                    int already_check[3]={0};
                    for(int i=0;i<3;i++){
                        int succes=0;
                        int loop=1;
                        while(loop){
                            int temp_id=rand()%3;
                            if(already_check[temp_id]==0){
                                succes=func[temp_id](grille,x,y,update,direction);
                                already_check[temp_id]=1;
                                loop=0;
                            }
                        }
                        if(succes){
                            break;
                        }
                    }

                } else if (elemtemp.fluid) {

                    if (grille[x][y + direction].weight <= 0 && grille[x][y + direction].weight!=elemtemp.weight) {//check bottom
                        switch_points(grille, x, y, x, y + direction,update);
                    } else if ((x - 1 >= 0) && grille[x - 1][y + direction].weight <= 0 && grille[x-1][y + direction].weight!=elemtemp.weight) {//CHECK bottom left
                        switch_points(grille, x, y, x - 1, y + direction,update);
                    } else if ((x + 1 < PIXEL_WIDTH) && grille[x + 1][y + direction].weight <= 0 && grille[x+1][y + direction].weight!=elemtemp.weight) {//CHECK bottom right
                        switch_points(grille, x, y, x + 1, y + direction,update);
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

    void draw_under_mouse(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT], SDL_Surface *surface, struct element type,int brush_size) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x > WINDOW_GAME_PADDING_HEIGHT && x < WINDOW_GAME_PADDING_HEIGHT + WINDOW_HEIGHT &&
            y > WINDOW_GAME_PADDING_WIDTH && y < WINDOW_GAME_PADDING_WIDTH + WINDOW_WIDTH) {
            x = (x - WINDOW_GAME_PADDING_WIDTH) / (WINDOW_GAME_WIDTH / PIXEL_WIDTH);
            y = (y - WINDOW_GAME_PADDING_HEIGHT) / (WINDOW_GAME_HEIGHT / PIXEL_HEIGHT);
            for (int i = x - brush_size / 2; i < x + brush_size / 2; i++) {
                for (int j = y - brush_size; j < y + brush_size / 2; j++) {
                    if(i>=0 && i<PIXEL_WIDTH && j>=0 && j<PIXEL_HEIGHT){
                        grille[i][j] = type;
                    }

                }
            }
        }
    }


    int main() {
        //main parameters
        struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT];
        fill_air(grille);
        struct element current_element = sand();
        int brush_size = 6;



        // une fenêtre
        SDL_Window *window = NULL;
// un renderer (chargé du rendu graphique)
        SDL_Renderer *renderer = NULL;
// initialisation de la video
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n",
                    SDL_GetError());
            exit(EXIT_FAILURE); // On quitte le programme
        }
        if (0 != SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &window,
                                             &renderer)) {
            fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
            return EXIT_FAILURE;
        }
// paint a black background on the windows
        SDL_SetRenderTarget(renderer, NULL); /* Le renderer est la cible de rendu. */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
// mise a jour de l'affichage
        SDL_RenderPresent(renderer);
        if (renderer == NULL) {
            fprintf(stderr, "Echec de creation du renderer : %s", SDL_GetError());
        }
        SDL_SetRenderTarget(renderer, NULL);
        // mise a jour de l'affichage


        SDL_Surface *surface = NULL;
        SDL_Event event;
        SDL_bool continuer = 1;
        int frame=0;
        int mouse_held=0;
        srand(time(NULL));
        while (continuer) {
            frame++;
            update_gravity(grille,frame);
            update_render(grille, renderer);
            //WAIT
            while(SDL_PollEvent(&event)) {
                switch (event.type) {//INPUTS

                    case SDL_MOUSEBUTTONDOWN:
                        mouse_held=1;
                        break;
                    case SDL_MOUSEBUTTONUP:
                        mouse_held=0;
                        break;
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.scancode) {
                            case SDL_SCANCODE_KP_0:
                                current_element = air();
                                break;
                            case SDL_SCANCODE_KP_1:
                                current_element = sand();
                                break;
                            case SDL_SCANCODE_KP_2:
                                current_element = dirt();
                                break;
                            case SDL_SCANCODE_KP_3:
                                current_element = cloud();
                                break;
                            case SDL_SCANCODE_KP_4:
                                current_element=water();
                                break;
                            case SDL_SCANCODE_UP:
                                brush_size += 1;
                                break;
                            case SDL_SCANCODE_R:
                                fill_air(grille);
                                break;
                            case SDL_SCANCODE_DOWN:
                                brush_size -= 1;
                                if(brush_size<=1){
                                    brush_size=2;
                                }
                                break;
                        }
                        break;
                    case SDL_QUIT:
                        continuer = 0;
                        break;

                }
                if(mouse_held){
                    draw_under_mouse(grille, surface, current_element, brush_size);
                }

            }
        }


        if (NULL != renderer)
            SDL_DestroyRenderer(renderer);
        if (NULL != window)
            SDL_DestroyWindow(window);
        SDL_Quit();
        printf("Quit\n");

        //DEBUG
        struct element a=air();
        for (int i = 0; i < PIXEL_WIDTH; i++) {
            for (int j = 0; j < PIXEL_HEIGHT; j++) {
                if(grille[i][j].id!=a.id){
                    printf("%d %d, %s\n",i,j,grille[i][j].name);
                }

            }
        }
        return EXIT_SUCCESS;
    }