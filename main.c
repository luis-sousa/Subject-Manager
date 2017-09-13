/* 
 * File:   main.c
 * Authores: 8090228 Luis Sousa
 *           8100158 Joel Babo
 *
 * Created on 14 de Dezembro de 2011, 20:43
 */

#include <stdio.h>
#include "myFunctions.h"

int main(int argc, char** argv) {
    UserPtr startPtr = NULL; /* initialize startPtr */
    insertAuto(&startPtr);
    menuInit(startPtr);
    return (EXIT_SUCCESS);
}

