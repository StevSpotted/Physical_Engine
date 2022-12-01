//
// Created by Coco on 24/11/2022.
//

#ifndef C_PROJECTS_ELEMENTS_H
#define C_PROJECTS_ELEMENTS_H

struct element{

    char name[20];
    SDL_Color color;
    int gravity_scale;//Always >0
    int weight;
    int pyramid_fall;
    int fluid;
    int gaz;
    int id;
    int last_update;
    int flamable;
    int hot;
    int spawn_frame;
    int lifetime;
};

#endif //C_PROJECTS_ELEMENTS_H
struct element get_element_by_id(int id); //DONT FORGET TO UPDATE
//BASIC ELEMENTS
struct element air();
struct element sand();
struct element dirt();
struct element vapor();
struct element water();
struct element fire();
//ELEMENT GENERATOR
struct element water_sink();
struct element fire_sink();