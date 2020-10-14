/*
 * Programme P3 qui affiche les données de la zone partagée
 */

/* 
 * File:   main.c
 * Author: msoulard
 *
 * Created on 12 octobre 2020, 11:13
 */

#include <sys/types.h> 
#include <sys/shm.h> 
#include <sys/ipc.h> 
#include <errno.h> 
#include <time.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h>
#include "zone.h"

/*
 * 
 */
int main(int argc, char** argv) {
    structPartagee *zoneCommune;
    key_t clef;
    int id;
    
    //création de la clef de partage
    clef = ftok("/tmp/msoulard", 'a');
    if(clef == -1){
        printf("problème ftok : %s\n", strerror(errno));
        exit(errno);
    }
    //création du segment mémoire partagé
    id = shmget(clef, sizeof(structPartagee), IPC_CREAT | 0600);
    if(id == -1){
        printf("problème shmget : %s\n", strerror(errno));
        exit(errno);
    }
    printf("id du segment : %d\n", id);
    //attribution adresse virtuelle du segment
    zoneCommune = (structPartagee *)shmat(id, NULL, SHM_R);
    if(zoneCommune == (void *)-1){
        printf("problème shmat : %s\n", strerror(errno));
        exit(errno);
    }
    //boucle infinie de changement des valeurs temp et de pression
    while (1 == 1) {
        printf("temperature : %.2f\n", zoneCommune->temp);
        printf("presion : %d\n", zoneCommune->press);
        printf("ordre : %c\n", zoneCommune->ordre);
        sleep(2);
    }

    return (EXIT_SUCCESS);
}

