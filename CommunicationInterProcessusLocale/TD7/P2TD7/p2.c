/* 
 * File:   p2.c
 * Author: msoulard
 *
 * Created on 2 novembre 2020, 09:27
 */

#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "zone.h"

/*
 * 
 */
int randomI() {
    return ((int) 100.0 * (rand() / (RAND_MAX + 0.1)));
}

char randomC() {
    char tabCar[3] = {'a', 'b', 'c'};
    int index = 0;
    index = randomI() % 3;
    return tabCar[index];
}

int main(int argc, char** argv) {
    key_t clef;
    int id;
    int erreur;
    donnees zoneCommune;

    //création de la clef de partage
    clef = ftok("/tmp/msoulardfile", 'a');
    if (clef == -1) {
        printf("problème ftok : %s\n", strerror(errno));
        exit(errno);
    }
    //création de la file de messages
    id = msgget(clef, IPC_CREAT | 0600);
    if (id == -1) {
        printf("problème msgget : %s\n", strerror(errno));
        exit(errno);
    }
    printf("id du segment : %d\n", id);
    //boucle infinie de l'envoie
    while (1 == 1) {
        //ordre
        zoneCommune.type = 3;
        zoneCommune.texte[0] = randomC();
        zoneCommune.texte[1] = 0;
        erreur = msgsnd(id, &zoneCommune, 9, IPC_NOWAIT);
        if (erreur == -1) {
            printf("problème msgsnd : %s\n", strerror(errno));
            exit(errno);
        }
        sleep(3);
    }

    return (EXIT_SUCCESS);
}

