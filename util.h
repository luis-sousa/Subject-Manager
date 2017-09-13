/* 
 * File:   util.h
 * Authores: 8090228 Luis Sousa
 *           8100158 Joel Babo
 *
 * Created on 14 de Dezembro de 2011, 20:45
 */
#include <time.h>

void clean() {
    while (getchar() != '\n');
}

/*Limpa os caracteres existentes no ecran*/
void clearScreen() {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

/*Faz o programa ficar em pausa por um certo tempo(em segundos)*/
void wait(int segundos) {
    clock_t esperar_ate;
    esperar_ate = clock() + segundos * CLOCKS_PER_SEC;
    while (clock() < esperar_ate) {
    }
}

/*Espera um caracter e apresenta uma mensagem "simulando" o system pause*/
void pause() {
    printf("Prima qualquer tecla para continuar...");
    getchar();
}



