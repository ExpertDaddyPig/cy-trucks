#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "defs.h"
#include "functions.h"

#define color(param) printf("\033[%sm",param)

int main(int argc, char *argv[]) {
    int option_t = 0, option_s = 0, linecount = 0;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            option_t = 1;
        }
        if (strcmp(argv[i], "-s") == 0) {
            option_s = 1;
        }
        if (strcmp(argv[i], "-lc") == 0) {
            linecount = atoi(argv[i+1]);
        }
    }
    if (option_t == 1) {
        int h = 0;
        FILE *data = fopen("trips_data.csv", "r+");
        FILE *sorted = fopen("sorted_data.csv", "w+");
        FILE *alpha_sorted = fopen("alpha_sorted_data.csv", "w+");
        FILE *res = fopen("res.csv", "w+");
        if (data == NULL) {
            printf("Erreur lors de la lecture du fichier.\n");
            exit(10);
        }
        if (sorted == NULL) {
            printf("Erreur lors de la creation du fichier temporaire de tri.\n");
            exit(11);
        }
        if (alpha_sorted == NULL) {
            printf("Erreur lors de la creation du fichier temporaire de tri.\n");
            exit(11);
        }
        if (res == NULL) {
            printf("Erreur lors de la creation du fichier de sortie.\n");
            exit(11);
        }
        char buffer[300];
        char *current_trip_id;
        City_Info *list = NULL;
        City_Info *alpha_list = NULL;
        City_Info *found = NULL;
        Leaf_City *tree = NULL;
        Leaf_City *alpha_tree = NULL;
        char city_name_A[51];
        char city_name_B[51];
        char city_name[51];
        int pass;
        int first;
        int step;
        char letter;
        float percent;
        int line;
        printf("Traitement des données:\n");
        printf("\e[?25l");
        while (!feof(data)) {
            line++;
            percent = ((float)line/(float)linecount) * 100;
            printf("\r|");
            for (int i = 0; i < 100; i++) {
                if (i < (int)percent) {
                    color("92");
                    printf("▇");
                    color("0");
                } else {
                    color("91");
                    printf("▇");
                    color("0");
                }
            }
            printf("| %.2f%% \t%d/%d lignes traités", percent, line, linecount);
            fscanf(data, "%d;%50[^;];%50[^\n]", &step, city_name_A, city_name_B);
            if (step == 1) {
                if (list == NULL) {
                    list = createChainCity(city_name_A, 1, 1);
                } else {
                    found = searchNameListCity(list, city_name_A);
                    if (found != NULL) {
                        found->pass_times++;
                        found->first_times++;
                    } else {
                        list = insertStartCity(list, city_name_A, 1, 1);
                    }
                }        
            }
            if (list == NULL) {
                list = createChainCity(city_name_B, 0, 1);
            } else {
                found = searchNameListCity(list, city_name_B);
                if (found != NULL) {
                    found->pass_times++; 
                } else {
                    list = insertStartCity(list, city_name_B, 0, 1);
                }
            }
        }
        printf("\nTraitement terminé\n");
        printf("\e[?25h");
        tree = addListToTree_City(tree, list, &h);
        parc_City_Inv(tree, sorted);
        rewind(sorted);
        deleteTree_City(tree);
        tree = NULL;
        for (int i = 0; i < 10; i++) {
            fscanf(sorted, "%50[^;];%d;%d\n", city_name, &pass, &first);
            if (alpha_list == NULL) {
                alpha_list = createChainCity(city_name, first, pass);
            } else {
                alpha_list = insertStartCity(alpha_list, city_name, first, pass);
            }
        }
        h = 0;
        alpha_tree = addListToTree_AlphaSort_City(alpha_tree, alpha_list, &h);
        parc_City_Inv(alpha_tree, alpha_sorted);
        rewind(alpha_sorted);
        for (int i = 0; i < 10; i++) {
            fgets(buffer, sizeof(buffer), alpha_sorted);
            fputs(buffer, res);
        }
        fclose(alpha_sorted);
        fclose(sorted);
        fclose(res);
        remove("sorted_data.csv");
        remove("alpha_sorted_data.csv");
        remove("trips_data.csv");
        deleteTree_City(tree);
        delListCity(list);
    }
    if (option_s == 1) {
        int h = 0;
        FILE *data = fopen("trips_distance.csv", "r");
        FILE *sorted = fopen("sorted_data.csv", "w+");
        FILE *save = fopen("saved_list.csv", "r+");
        FILE *res = fopen("res.csv", "w+");
        if (data == NULL) {
            printf("Erreur lors de la lecture du fichier.\n");
            exit(10);
        }
        if (sorted == NULL) {
            printf("Erreur lors de la creation du fichier temporaire de tri.\n");
            exit(11);
        }
        if (res == NULL) {
            printf("Erreur lors de la creation du fichier de sortie.\n");
            exit(11);
        }
        char values[300];
        char buffer[300];
        Step_Info *list = NULL;
        Step_Info *found = NULL;
        Step_Info *parc = NULL;
        Leaf_Step *tree = NULL;
        int step = 0;
        int line = 0;
        float dist = 0;
        int size = 0;
        float percent;
        printf("Traitement des données:\n");
        printf("\e[?25l");
        while (!feof(data)) {
            line++;
            percent = ((float)line/(float)linecount) * 100;
            printf("\r|");
            for (int i = 0; i < 100; i++) {
                if (i < (int)percent) {
                    color("92");
                    printf("▇");
                    color("0");
                } else {
                    color("91");
                    printf("▇");
                    color("0");
                }
            }
            printf("| %.2f%% \t%d/%d lignes traités", percent, line, linecount);
            step = 0;
            dist = 0;
            fscanf(data, "%d;%f\n", &step, &dist);
            parc = list;
            found = searchNameListStep(parc, step);
            if (found != NULL) {
                found->total++;
                found->moy = found->moy + dist;
                if (dist < found->min) found->min = dist;
                if (dist > found->max) found->max = dist;
                found->max_min = found->max - found->min;
            } else {
                list = insertStartStep(list, step, dist, 1);
                size++;
            }
        }
        printf("\nTraitement terminé\n");
        printf("\e[?25h");
        tree = addListToTree_Step(tree, list, &h);
        parc_Step_Inv(tree, sorted);
        rewind(sorted);
        for (int i = 0; i < 50; i++) {
            fgets(buffer, sizeof(buffer), sorted);
            fputs(buffer, res);
        }
        fclose(sorted);
        fclose(res);
        remove("sorted_data.csv");
        remove("trip_distance.csv");
        deleteTree_Step(tree);
        delListStep(list);
    }
    return 0;
}