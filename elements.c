//
// Created by Coco on 24/11/2022.
//
#include <SDL2/SDL.h>
#include "headers/elements.h"

struct element;
typedef struct element (*lm)(void);

struct element get_element_by_id(int id){
    lm all[]={&air, &sand, &dirt, &vapor, &water,&fire};
    if(id<0){
        return all[id*(-1)]();
    }
    return all[id]();
}

struct element air(){
    SDL_Color color={0,0,100,100};
    struct element elem={"air",color,0,0,0,0,0,0,0,0,0,0,-1};

    return elem;
};

struct element sand(){
    SDL_Color color={255,247,0,255};
    struct element elem={"sand",color,1,1,1,0,0,1,0,0,0,0,-1};
    return elem;
};

struct element dirt(){
    SDL_Color color={119,69,19,255};
    struct element elem={"dirt",color,0,1,0,0,0,2,0,0,0,0,-1};
    return elem;
};

struct element vapor(){
    SDL_Color color={150,150,150,255};
    struct element elem={"vapor",color,2,-1,0,1,1,3,0,0,0,0,50};
    return elem;
};

struct element water(){
    SDL_Color color={0,60,150,100};
    struct element elem={"water",color,1,-1,0,1,0,4,0,1,0,0,-1};
    return elem;
}
struct element fire(){
    SDL_Color color={200,20,20,100};
    struct element elem={"fire",color,2,-1,0,1,1,5,0,0,1,0,50};
    return elem;
}

struct element water_sink(){
    SDL_Color color={0,0,0,100};
    struct element elem={"water sink",color,1,999,0,1,0,-4,0,0,0,0,-1};
    return elem;

}

struct element fire_sink(){
    SDL_Color color={0,0,0,100};
    struct element elem={"fire sink",color,1,999,0,1,0,-5,0,0,0,0,-1};
    return elem;

}