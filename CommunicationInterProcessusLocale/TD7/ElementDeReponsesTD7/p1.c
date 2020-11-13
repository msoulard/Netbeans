/*****************************************
 *	p1.c
 *	met des messages de type 2(temp) et 4(press)
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

    key_t clef;

    // creation de la clef de partage
    clef = ftok("/tmp/bidonFile", 'a');
    if (clef == -1) {
        printf("pb ftok : %s\n", strerror(errno));
        exit(errno);
    }
    // creation de la file
    idFile = msgget(clef, IPC_CREAT |0600);
    if (idFile == -1) {
        printf("pb creation file : %s\n", strerror(errno));
        exit(0);
    }

    // boucle infinie de changement de temperature et de pression
    while (1 == 1) {
        memset(tampon,'\0',255);
        maFile.type = 2;
        sprintf(tampon,"%f",randomF());
        strcpy(maFile.texte,tampon);
        msgsnd(idFile, (void*) &maFile, 9, IPC_NOWAIT);
        sleep(1);
        memset(tampon,'\0',255);
        maFile.type = 4;
        sprintf(tampon,"%d",randomI());
        strcpy(maFile.texte,tampon);
        msgsnd(idFile, (void*) &maFile, 9, IPC_NOWAIT);
        sleep(2);
    }

    exit(EXIT_SUCCESS);
}