/*****************************************
 *	p3.c
 *	affiche les messages de type 2(temp), 3(ordre) et 4(press)
 *	dans la file de message ayant pour clef
 *	bindonFile
 * *****************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <errno.h>
#include <sys/ipc.h>
#include <string.h>
#include "zone.h"

float randomF() {
    return ((float) 100.0 * (rand() / (RAND_MAX + 0.1)));
}

int randomI() {
    return ((int) 100.0 * (rand() / (RAND_MAX + 0.1)));
}

char randomC() {
    char tabCar[3] = {'a', 'b', 'c'};
    int index = 0;
    index = randomI() % 3;
    return tabCar[index];
}

int main() {
    struct donnees maFile;
    char tampon[255];
    int idFile;
    int ret;

    key_t clef;

    // creation de la clef de partage
    clef = ftok("/tmp/bidonFile", 'a');
    if (clef == -1) {
        printf("pb ftok : %s\n", strerror(errno));
        exit(errno);
    }
    // creation de la file
    idFile = msgget(clef, IPC_CREAT | 0600);
    if (idFile == -1) {
        printf("pb creation file : %s\n", strerror(errno));
        exit(0);
    }

    // boucle infinie de changement de temperature et de pression
    while (1 == 1) {
        // reception des messages de type 2
        memset(tampon, '\0', 255);
        ret = msgrcv(idFile, (void*) &maFile, 9, 2, IPC_NOWAIT);
        if (ret != -1) {
            printf("temp : %s type : %d\n", maFile.texte, maFile.type);
        }

        // reception des messages de type 3
        memset(tampon, '\0', 255);
        ret = msgrcv(idFile, (void*) &maFile, 9, 3, IPC_NOWAIT);
        if (ret != -1) {
            printf("ordre : %s type : %d\n", maFile.texte, maFile.type);
        }

        // reception des messages de type 4
        memset(tampon, '\0', 255);
        ret = msgrcv(idFile, (void*) &maFile, 9, 4, IPC_NOWAIT);
        if (ret != -1) {
            printf("pression : %s type : %d\n", maFile.texte, maFile.type);
        }

    }

    exit(EXIT_SUCCESS);
}