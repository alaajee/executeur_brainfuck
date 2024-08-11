#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "brainfuck_helper.c"
/* un programme pour l etape  demandee */ 

int main() { 
    char instructions[] = "++++>++<.";
    uint8_t data[2] = {0,5 };
    struct Boucle loops[] = {{instructions + 2, instructions + 5}};
    char* ipp = instructions;
    uint8_t* dpp = data;
    while (*ipp != '\0') {
        execute_instruction(&ipp, &dpp, &loops);
    }
    for (int i = 0;i<2; i++ ){
    	printf("%hhu\n",data[i]);
     }
    return 0;
}

/* sortie attendue 4 7 */

