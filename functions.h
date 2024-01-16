#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

City_Info* delListCity(City_Info* list);
City_Info* createChainCity(char* name, int first, int pass);
City_Info* insertStartCity(City_Info* begin, char* name, int first, int pass);
City_Info* searchNameListCity(City_Info* c, char* name);
void writeListCity(City_Info* chain);

Step_Info* delListStep(Step_Info* list);
Step_Info* createChainStep(int name, float dist, int total);
Step_Info* insertStartStep(Step_Info* begin, int name, float dist, int total);
Step_Info* createChainStep_alt(int name, float min, float max, float moy, int total);
Step_Info* insertStartStep_alt(Step_Info* begin, int name, float min, float max, float moy, int total);
Step_Info* searchNameListStep(Step_Info* c, int name);
void writeListStep(Step_Info* chain);

Leaf_City* createTree_city(char name[], int value);
Leaf_City* rotg_city(Leaf_City *t);
Leaf_City* rotd_city(Leaf_City *t);
Leaf_City* drotg_city(Leaf_City *t);
Leaf_City* drotd_city(Leaf_City *t);
Leaf_City* treeBalance_city(Leaf_City *t);
Leaf_City *insertAVL_City(Leaf_City *t, char* name, int pass, int first, int *h);
Leaf_City *insertAVL_AlphaSort_City(Leaf_City *t, char* name, int pass, int first, int *h);
Leaf_City* addListToTree_City(Leaf_City *tree, City_Info *list, int *h);
Leaf_City* addListToTree_AlphaSort_City(Leaf_City *tree, City_Info *list, int *h);

Leaf_Step* createTree_step(int name, float min, float max, float moy, int total);
Leaf_Step* rotg_step(Leaf_Step *t);
Leaf_Step* rotd_step(Leaf_Step *t);
Leaf_Step* drotg_step(Leaf_Step *t);
Leaf_Step* drotd_step(Leaf_Step *t);
Leaf_Step* treeBalance_step(Leaf_Step *t);
Leaf_Step *insertAVL_Step(Leaf_Step *t, int name, float min, float max, float moy, int total, int *h);
Leaf_Step* addListToTree_Step(Leaf_Step *tree, Step_Info *list, int *h);
void writeNodeCity(Leaf_City *t, FILE *f);
void parc_City_Inv(Leaf_City *t, FILE *f);
void deleteR_Step(Leaf_Step *t);
void deleteL_Step(Leaf_Step *t);
void deleteTree_Step(Leaf_Step *t);
void writeNodeStep(Leaf_Step *t, FILE *f);
void parc_Step_Inv(Leaf_Step *t, FILE *out);
#endif