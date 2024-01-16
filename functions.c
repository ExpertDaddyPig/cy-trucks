#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

int i = 0;

City_Info* delListCity(City_Info *list) {
    if (list == NULL) return list;
    City_Info *x = list;
    list = list->next;
    free(x);
    return delListCity(list);
}

City_Info* createChainCity(char* city_name, int first, int pass) {
	City_Info* c = malloc(sizeof(City_Info));
	if (c == NULL) {
		exit(1);
	}
	c->next = NULL;
    strcpy(c->city_name, city_name);
	c->pass_times = pass;
    c->first_times = first;
	return c;
}

City_Info* insertStartCity(City_Info* begin, char* name, int first, int pass) {
	City_Info *new, *p1;
	new = createChainCity(name, first, pass);
	p1 = begin;
    begin = new;
	begin->next = p1;
	return begin;
}

City_Info* searchNameListCity(City_Info* c, char* name) {
    if (c == NULL) return c;
    if (strcmp(c->city_name, name) != 0) {
        return searchNameListCity(c->next, name);
    }
    return c;
}

void writeListCity(City_Info* chain) {
    if (chain != NULL) {
        printf("VILLE : %s, PASSAGE : %d FIRSTS : %d\n", chain->city_name, chain->pass_times, chain->first_times);
        writeListCity(chain->next);
    }
}

float max(float a, float b) {
    return a > b ? a : b;
}

float min(float a, float b) {
    return a < b ? a : b;
}

Leaf_City* createTree_city(char* name, int pass, int firsts) {
    Leaf_City* t = malloc(sizeof(Leaf_City));
    if (t == NULL) {
        printf("Something wrong happened with the allocation\n");
        exit(1);
    }
    t->l = NULL;
    t->r = NULL;
    t->eq = 0;
    strcpy(t->city_name, name);
    t->pass_times = pass;
    t->first_times = firsts;
    return t;
}

Leaf_City* rotg_city(Leaf_City *t) {
    Leaf_City* piv;
    int ea, ep;
    piv = t->r;
    t->r = piv->l;
    piv->l = t;
    ea = t->eq;
    ep = piv->eq;
    t->eq = ea - max(ep, 0) - 1;
    piv->eq = min(min(ea - 2, ea + ep - 2), ep - 1);
    t = piv;
    return t;
}

Leaf_City* rotd_city(Leaf_City *t) {
    Leaf_City* piv;
    int ea, ep;
    piv = t->l;
    t->l = piv->r;
    piv->r = t;
    ea = t->eq;
    ep = piv->eq;
    t->eq = ea - min(ep, 0) + 1;
    piv->eq = max(max(ea + 2, ea + ep + 2), ep + 1);
    t = piv;
    return t;
}

Leaf_City* drotg_city(Leaf_City *t) {
    t->r = rotd_city(t->r);
    return rotg_city(t);
}

Leaf_City* drotd_city(Leaf_City *t) {
    t->l = rotg_city(t->l);
    return rotd_city(t);
}

Leaf_City* treeBalance_city(Leaf_City *t) {
    if (t->eq >= 2) {
        if (t->r->eq >= 0) {
            return rotg_city(t);
        } else {
            return drotg_city(t);
        }
    } else if (t->eq <= -2) {
        if (t->l->eq <= 0) {
            return rotd_city(t);
        } else {
            return drotd_city(t);
        }
    }
    return t;
}

Leaf_City *insertAVL_City(Leaf_City *t, char* name, int pass, int first, int *h) {
    if (t == NULL) {
        *h = 1;
        return createTree_city(name, pass, first);
    } else if (pass < t->pass_times) {
        t->l = insertAVL_City(t->l, name, pass, first, h);
        *h = -*h;
    } else if (pass >= t->pass_times) {
        t->r = insertAVL_City(t->r, name, pass, first, h);
    } else {
        *h = 0;
        return t;
    }
    if (*h != 0) {
        t->eq = t->eq + *h;
        t = treeBalance_city(t);
        if (t->eq == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }
    return t;
}

Leaf_City *insertAVL_AlphaSort_City(Leaf_City *t, char* name, int pass, int first, int *h) {
    if (t == NULL) {
        *h = 1;
        return createTree_city(name, pass, first);
    } else if (strcmp(t->city_name, name) < 0) {
        t->l = insertAVL_AlphaSort_City(t->l, name, pass, first, h);
        *h = -*h;
    } else if (strcmp(t->city_name, name) > 0) {
        t->r = insertAVL_AlphaSort_City(t->r, name, pass, first, h);
    } else {
        *h = 0;
        return t;
    }
    if (*h != 0) {
        t->eq = t->eq + *h;
        t = treeBalance_city(t);
        if (t->eq == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }
    return t;
}

Leaf_City* addListToTree_City(Leaf_City *tree, City_Info *list, int *h) {
    if (list == NULL) return tree;
    tree = insertAVL_City(tree, list->city_name, list->pass_times, list->first_times, h);
    return addListToTree_City(tree, list->next, h);
}

Leaf_City* addListToTree_AlphaSort_City(Leaf_City *tree, City_Info *list, int *h) {
    if (list == NULL) return tree;
    tree = insertAVL_AlphaSort_City(tree, list->city_name, list->pass_times, list->first_times, h);
    return addListToTree_AlphaSort_City(tree, list->next, h);
}

void writeNodeCity(Leaf_City *t, FILE *f) {
    fprintf(f, "%s;%d;%d\n", t->city_name, t->pass_times, t->first_times);
}

void parc_City_Inv(Leaf_City *t, FILE* output) {
    if (t != NULL) {
        parc_City_Inv(t->r, output);
        writeNodeCity(t, output);
        parc_City_Inv(t->l, output);
    }
}

void deleteL_City(Leaf_City *t) {
    if (t != NULL) {
        if (t->l != NULL) {
            if (t->l->l != NULL) {
                deleteL_City(t->l);
            }
            if (t->l->r != NULL) {
                deleteR_City(t->l);
            }
            free(t->l);
        }
    }
}

void deleteR_City(Leaf_City *t) {
    if (t != NULL) {
        if (t->r != NULL) {
            if (t->r->l != NULL) {
                deleteL_City(t->r);
            }
            if (t->r->r != NULL) {
                deleteR_City(t->r);
            }
            free(t->r);
        }
    }
}

void deleteTree_City(Leaf_City *t) {
    deleteL_City(t);
    deleteR_City(t);
    free(t);
}

Step_Info* delListStep(Step_Info *list) {
    while (list != NULL) {
        Step_Info *x = list;
        list = list->next;    
        free(x);
    }
    return list;
}

Step_Info* createChainStep(int name, float dist, int total) {
	Step_Info* c = malloc(sizeof(Step_Info));
	if (c == NULL) exit(1);
    c->step = name;
    c->min = dist;
    c->moy = dist;
    c->max = dist;
    c->total = total;
    c->max_min = c->max - c->min;
    c->next = NULL;
	return c;
}

Step_Info* createChainStep_alt(int name, float min, float max, float moy, int total) {
	Step_Info* c = malloc(sizeof(Step_Info));
	if (c == NULL) exit(1);
    c->step = name;
    c->min = min;
    c->moy = moy;
    c->max = max;
    c->total = total;
    c->max_min = max - min;
    c->next = NULL;
	return c;
}

Step_Info* insertStartStep(Step_Info* begin, int name, float dist, int total) {
	Step_Info *new, *p1;
    new = createChainStep(name, dist, total);
    p1 = begin;
    begin = new;
	begin->next = p1;
	return new;
}

Step_Info* insertStartStep_alt(Step_Info* begin, int name, float min, float max, float moy, int total) {
	Step_Info *new, *p1;
    new = createChainStep_alt(name, min, max, moy, total);
    p1 = begin;
    begin = new;
	begin->next = p1;
	return new;
}

Step_Info* searchNameListStep(Step_Info* c, int name) {
    Step_Info *found, *parc = c;
    while (parc != NULL && name != parc->step) {
        parc = parc->next;
    }
    if (parc != NULL && name == parc->step) {
        found = parc;
    } else {
        found = NULL;
    }
    parc = NULL;
    return found;
}

void writeListStep(Step_Info* chain) {
    if (chain != NULL) {
        printf("TRIP : %d, MIN : %f MAX : %f MOY : %f\n", chain->step, chain->min, chain->max, chain->moy);
        writeListStep(chain->next);
    }
}

Leaf_Step* createTree_step(int name, float min, float max, float moy, int total) {
    Leaf_Step* t = malloc(sizeof(Leaf_Step));
    if (t == NULL) {
        printf("Something wrong happened with the allocation\n");
        exit(1);
    }
    t->l = NULL;
    t->r = NULL;
    t->eq = 0;
    t->step = name;
    t->min = min;
    t->moy = moy;
    t->max = max;
    t->total = total;
    t->max_min = max - min;
    return t;
}

Leaf_Step* rotg_step(Leaf_Step *t) {
    Leaf_Step* piv;
    int ea, ep;
    piv = t->r;
    t->r = piv->l;
    piv->l = t;
    ea = t->eq;
    ep = piv->eq;
    t->eq = ea - max(ep, 0) - 1;
    piv->eq = min(min(ea - 2, ea + ep - 2), ep - 1);
    t = piv;
    return t;
}

Leaf_Step* rotd_step(Leaf_Step *t) {
    Leaf_Step* piv;
    int ea, ep;
    piv = t->l;
    t->l = piv->r;
    piv->r = t;
    ea = t->eq;
    ep = piv->eq;
    t->eq = ea - min(ep, 0) + 1;
    piv->eq = max(max(ea + 2, ea + ep + 2), ep + 1);
    t = piv;
    return t;
}

Leaf_Step* drotg_step(Leaf_Step *t) {
    t->r = rotd_step(t->r);
    return rotg_step(t);
}

Leaf_Step* drotd_step(Leaf_Step *t) {
    t->l = rotg_step(t->l);
    return rotd_step(t);
}

Leaf_Step* treeBalance_step(Leaf_Step *t) {
    if (t->eq >= 2) {
        if (t->r->eq >= 0) {
            return rotg_step(t);
        } else {
            return drotg_step(t);
        }
    } else if (t->eq <= -2) {
        if (t->l->eq <= 0) {
            return rotd_step(t);
        } else {
            return drotd_step(t);
        }
    }
    return t;
}

Leaf_Step *insertAVL_Step(Leaf_Step *t, int name, float min, float max, float moy, int total, int *h) {
    if (t == NULL) {
        *h = 1;
        return createTree_step(name, min, max, moy, total);
    } else if ((max - min) < t->max_min) {
        t->l = insertAVL_Step(t->l, name, min, max, moy, total, h);
        *h = -*h;
    } else if ((max - min) >= t->max_min) {
        t->r = insertAVL_Step(t->r, name, min, max, moy, total, h);
    } else {
        *h = 0;
        return t;
    }
    if (*h != 0) {
        t->eq = t->eq + *h;
        t = treeBalance_step(t);
        if (t->eq == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }
    return t;
}

Leaf_Step* addListToTree_Step(Leaf_Step *tree, Step_Info *list, int *h) {
    Step_Info *temp = list;
    float min, max, moy, max_min;
    int total, trip;
    while (temp != NULL) {
        trip = temp->step;
        total = temp->total;
        min = temp->min;
        moy = temp->moy / (float)total;
        max = temp->max;
        tree = insertAVL_Step(tree, trip, min, max, moy, total, h);
        temp = temp->next;
    }
    return tree;
}

void deleteL_Step(Leaf_Step *t) {
    if (t != NULL) {
        if (t->l != NULL) {
            if (t->l->l != NULL) {
                deleteL_Step(t->l);
            }
            if (t->l->r != NULL) {
                deleteR_Step(t->l);
            }
            free(t->l);
        }
    }
}

void deleteR_Step(Leaf_Step *t) {
    if (t != NULL) {
        if (t->r != NULL) {
            if (t->r->l != NULL) {
                deleteL_Step(t->r);
            }
            if (t->r->r != NULL) {
                deleteR_Step(t->r);
            }
            free(t->r);
        }
    }
}

void deleteTree_Step(Leaf_Step *t) {
    deleteL_Step(t);
    deleteR_Step(t);
    free(t);
}

void writeNodeStep(Leaf_Step *t, FILE *f) {
    fprintf(f, "%d;%f;%f;%f;%f\n", t->step, t->min, t->moy, t->max, t->max_min);
}

void parc_Step_Inv(Leaf_Step *t, FILE* output) {
    if (t == NULL) return;
    parc_Step_Inv(t->r, output);
    writeNodeStep(t, output);
    parc_Step_Inv(t->l, output);
}
