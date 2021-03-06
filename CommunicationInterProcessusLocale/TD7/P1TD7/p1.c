/*
 * File:   p1.c
 * Author: msoulard
 *
 * Created on 12 octobre 2020, 11:46
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
float randomF() {
    return ((float) 100.0 * (rand() / (RAND_MAX + 0.1)));
}

int randomI() {
    return ((int) 100.0 * (rand() / (RAND_MAX + 0.1)));
}

int main(int argc, char** argv) {
    key_t clef;
    int id;
    int erreur;
    char buff[255];
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
    //boucle infinie d'envoie de la pression et de la température
    while(1 == 1) {
        //température
        memset(buff, '\0', 255);
        zoneCommune.type = 2;
        sprintf(buff, "%f", randomF());
        strcpy(zoneCommune.texte, buff);
        erreur = msgsnd(id, &zoneCommune, 9, IPC_NOWAIT);
        if (erreur == -1) {
            printf("problème msgsnd : %s\n", strerror(errno));
            exit(errno);
        }
        sleep(1);
        //pression
        memset(buff, '\0', 255);
        zoneCommune.type = 4;
        sprintf(buff, "%d", randomI());
        strcpy(zoneCommune.texte, buff);
        erreur = msgsnd(id, &zoneCommune, 9, IPC_NOWAIT);
        if (erreur == -1) {
            printf("problème msgsnd : %s\n", strerror(errno));
            exit(errno);
        }
        sleep(1);
    }    
    
    return (EXIT_SUCCESS);
}

