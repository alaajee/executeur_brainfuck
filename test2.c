#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "brainfuck_helper.c"


int main() {
    /* je teste la fonction build_loops */
    char* input_prog = "--[----->+<]>---.++++++++++++.+.+++++++++.+[-->+<]>+++.++[-->[+++<]>.+++++++++]+++.+.+++++++++.-[-->+++++<]>++.[--->++<]>-.-----------.";
    void* loops = build_loops(input_prog);
    if (loops == NULL) {
        printf("Erreur: échec de la construction des boucles\n");
        return EXIT_FAILURE;
    }
    struct Boucle* maps = loops;
    for (int i = 0; maps[i].debut != NULL; i++){
        printf("Boucle %d: %.*s\n", i+1, (int)(maps[i].fin - maps[i].debut + 1), maps[i].debut);
    }
    free_loops(loops); 
    return EXIT_SUCCESS;
}


