//
// Created by Coco on 10/01/2023.
//

#include "headers/init.h"


struct game *init_game(void) {
    struct game *new_game = malloc(sizeof(struct game));
    fill_air(new_game->grille);

// initialisation de la video
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n",SDL_GetError());
        exit(EXIT_FAILURE); // On quitte le programme
    }
    if (0 != SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &(new_game->window), &(new_game->renderer))) {
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
// paint a black background on the windows
    SDL_SetRenderTarget(new_game->renderer, NULL); /* Le renderer est la cible de rendu. */
    SDL_SetRenderDrawColor(new_game->renderer, 0, 0, 0, 255);
// mise a jour de l'affichage
    SDL_RenderPresent(new_game->renderer);
    if (new_game->renderer == NULL) {
        fprintf(stderr, "Echec de creation du renderer : %s", SDL_GetError());
    }
    SDL_SetRenderTarget(new_game->renderer, NULL);
    // mise a jour de l'affichage




    return &new_game;
}


void fill_air(struct element grille[PIXEL_WIDTH][PIXEL_HEIGHT]) {
    for (int i = 0; i < PIXEL_WIDTH; i++) {
        for (int j = 0; j < PIXEL_HEIGHT; j++) {
            grille[i][j] = air();
        }
    }

}