#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "brainfuck_helper.h"
#include <stdbool.h>

char *get_input_prog(char *input_filename) {
    FILE *fichier;
    fichier = fopen(input_filename, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return NULL;
    }

    fseek(fichier, 0, SEEK_END);
    int taille = ftell(fichier);
    char *tab = malloc((taille + 1) * sizeof(char));
    if (tab == NULL) {
        printf("Erreur lors de l'allocation de mémoire.\n");
        fclose(fichier);
    }

    rewind(fichier);
    int i = 0;
    char caractere;
    while ((caractere = fgetc(fichier)) != EOF && i < taille) {
       
        if (strchr("+-<>[].,", caractere) != NULL) {
            tab[i] = caractere;
            i++;
        }
    }
    tab[i] = '\0';
    printf("\n");
    fclose(fichier);
    return tab;
}

void free_input_prog(char *input_prog) {
    if (input_prog != NULL) {
        free(input_prog);
    }
}

struct Boucle {
    char *debut;
    char *fin;
};

void* build_loops(char *input_prog) {
    int nbr_de_boucle = 0;
    char* str = input_prog;
    while (*str != '\0') {
        if (*str == '[') {
            nbr_de_boucle++;
        }
        str++;
    }

    struct Boucle* loops = (struct Boucle*)malloc(sizeof(struct Boucle) * nbr_de_boucle);
    if (loops == NULL) {
        printf("Erreur: échec de l'allocation de mémoire\n");
        exit(1);
    }
    str = input_prog;
    int boucle_m = 0;
    while (*str != '\0') {
        if (*str == '[') {
            loops[boucle_m].debut = str;
            int count2 = 1; 
            char *start = str;
            str++;
            while (*str != '\0' && count2 != 0) {
                if (*str == '[') {
                    count2++;
                }
                else if (*str == ']') {
                    count2--;
                }
                str++;
            }
            if (count2 == 0) {
                loops[boucle_m].fin = str - 1;
                boucle_m++;
            } else {
                return NULL;
            }
            str = start;
        }
        str++;
    }
    return loops;
}


void free_loops(void* loops) {
    if (loops != NULL) {
        free(loops);
    }
}
void execute_instruction(char** ipp, uint8_t** dpp, void* loops) {
    struct Boucle* maps = (struct Boucle*)loops;
    char instruction = **ipp;

    switch (instruction) {
        case '>':
            (*dpp)++;
            break;
        case '<':
            (*dpp)--;
            break;
        case '+':
            (**dpp)++;
            break;
        case '-':
            (**dpp)--;
            break;
        case '.':
            putchar(**dpp);
            break;
        case ',':
            **dpp = getchar();
            break;
        case '[':
            if (**dpp == 0) {
                for (int i = 0; maps[i].debut != NULL; i++) {
                    if (maps[i].debut == *ipp) {
                        *ipp = maps[i].fin;
                        break;
                    }
                }
            }
            break;
        case ']':
            if (**dpp != 0) {
                for (int i = 0; maps[i].fin != NULL; i++) {
                    if (maps[i].fin == *ipp) {
                        *ipp = maps[i].debut - 1;  
                        break;
                    }
                }
            }
            break;
    }
    (*ipp)++; 
}

