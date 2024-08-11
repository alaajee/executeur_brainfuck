#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "brainfuck_helper.c"
int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Vous devez passer le nom du fichier Brainfuck à interpréter\n");
        return 1;
    }
    char* input_prog = get_input_prog(argv[1]); /* je lis le fichier */
    int n = strlen(input_prog);
    for (int i = 0 ; i<n ; i++){
        printf("%c", input_prog[i]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}


