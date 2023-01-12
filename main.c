#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>
//#include <SDL2/SDL_ttf.h>

#include "headers/elements.h"
#include "headers/define.h"
#include "headers/update.h"
#include "headers/draw.h"
#include "headers/init.h"

int main() {
    struct game game;
    game.brush_size=6;
    game.current_element=sand();
    fill_air(game.grille);

// initialisation de la video
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n",SDL_GetError());
        exit(EXIT_FAILURE); // On quitte le programme
    }
    if (0 != SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &(game.window), &(game.renderer))) {
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
// paint a black background on the windows
    SDL_SetRenderTarget(game.renderer, NULL); /* Le renderer est la cible de rendu. */
    SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
// mise a jour de l'affichage
    SDL_RenderPresent(game.renderer);
    if (game.renderer == NULL) {
        fprintf(stderr, "Echec de creation du renderer : %s", SDL_GetError());
    }
    SDL_SetRenderTarget(game.renderer, NULL);
    // mise a jour de l'affichage




        SDL_Surface *surface = NULL;
        SDL_Event event;
        SDL_bool continuer = 1;
        int frame=0;
        int mouse_held=0;
        srand(time(NULL));
        while (continuer) {
            frame++;
            update_gravity(game.grille,frame);
            update_render(game.grille, game.renderer);
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
                                game.current_element = air();
                                break;
                            case SDL_SCANCODE_KP_1:
                                game.current_element = sand();
                                break;
                            case SDL_SCANCODE_KP_2:
                                game.current_element = dirt();
                                break;
                            case SDL_SCANCODE_KP_3:
                                game.current_element = vapor();
                                break;
                            case SDL_SCANCODE_KP_5:
                                game.current_element=fire();
                                break;
                            case SDL_SCANCODE_KP_4:
                                game.current_element=water();
                                break;
                            case SDL_SCANCODE_KP_PLUS:
                                game.current_element=water_sink();
                                break;
                            case SDL_SCANCODE_KP_MINUS:
                                game.current_element=fire_sink();
                                break;
                            case SDL_SCANCODE_UP:
                                game.brush_size += 1;
                                break;
                            case SDL_SCANCODE_R:
                                fill_air(game.grille);
                                break;
                            case SDL_SCANCODE_DOWN:
                                game.brush_size -= 1;
                                if(game.brush_size<=1){
                                    game.brush_size=2;
                                }
                                break;
                        }
                        break;
                    case SDL_QUIT:
                        continuer = 0;
                        break;

                }
                if(mouse_held){
                    draw_under_mouse(game.grille, surface, game.current_element, game.brush_size,frame);
                }
                //fps
            }
        }


        if (NULL != game.renderer)
            SDL_DestroyRenderer(game.renderer);
        if (NULL != game.window)
            SDL_DestroyWindow(game.window);
        SDL_Quit();
        printf("Quit\n");


        return EXIT_SUCCESS;
    }