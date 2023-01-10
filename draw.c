//
// Created by Coco on 10/01/2023.
//

#include "headers/draw.h"



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

    //draw_GUI(renderer);
    SDL_RenderPresent(renderer);
}


/*
void draw_GUI(SDL_Renderer *renderer){
    TTF_Font* Sans = TTF_OpenFont("Sans.ttf",24);
    SDL_Color White={255,255,255};
    SDL_Surface* surfaceMessage =
            TTF_RenderText_Solid(Sans, "Keybinds", White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect;
    Message_rect.x = 0;
    Message_rect.y = 0;
    Message_rect.w = 100;
    Message_rect.h = 100;

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}
*/