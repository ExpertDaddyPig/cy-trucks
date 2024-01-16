#ifndef DEFS_H
#define DEFS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Leaf_City {
    int pass_times;
    int first_times;
    char city_name[100];
    struct Leaf_City *r, *l;
    int eq;
} Leaf_City;

typedef struct Leaf_Step {
    int total;
    float max_min;
    float min;
    float max;
    float moy;
    int step;
    struct Leaf_Step *r, *l;
    int eq; 
} Leaf_Step;

typedef struct City_Info {
    char city_name[100];
    int pass_times;
    int first_times;
    struct City_Info *next;
} City_Info;

typedef struct Step_Info {
    int total;
    float max_min;
    float min;
    float max;
    float moy;
    int step;
    struct Step_Info *next;
} Step_Info;

#endif