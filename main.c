#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>
//#include <SDL2/SDL_ttf.h>

#include "headers/elements.h"
#include "headers/define.h"
#include "headers/update.h"
#include "headers/draw.h"s

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
        int start_time= time(NULL);
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
                                current_element = vapor();
                                break;
                            case SDL_SCANCODE_KP_5:
                                current_element=fire();
                                break;
                            case SDL_SCANCODE_KP_4:
                                current_element=water();
                                break;

                            case SDL_SCANCODE_KP_PLUS:
                                current_element=water_sink();
                                break;
                            case SDL_SCANCODE_KP_MINUS:
                                current_element=fire_sink();
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
                    draw_under_mouse(grille, surface, current_element, brush_size,frame);
                }
                //fps
            }
        }


        if (NULL != renderer)
            SDL_DestroyRenderer(renderer);
        if (NULL != window)
            SDL_DestroyWindow(window);
        SDL_Quit();
        printf("Quit\n");


        return EXIT_SUCCESS;
    }