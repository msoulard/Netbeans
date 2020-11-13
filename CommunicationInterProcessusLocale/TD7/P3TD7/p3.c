/* 
 * File:   p3.c
 * Author: msoulard
 *
 * Created on 2 novembre 2020, 11:02
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
int main(int argc, char** argv) {
    key_t clef;
    int id;
    ssize_t erreur;
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
    //consultation de la file de messages
    erreur = msgctl(id, IPC_STAT, &zoneCommune);
    if (erreur == -1) {
        printf("problème msgctl : %s\n", strerror(errno));
        exit(errno);
    }
    //recevoir les messages
    while(1 == 1){
        erreur = msgrcv(id, &zoneCommune, 9, 4, IPC_NOWAIT);
        if (erreur != -1) {
            printf("type : %d\n", zoneCommune.type);
            printf("pression : %s\n\n", zoneCommune.texte);
        }
        else{
          if(errno != ENOMSG){
            printf("problème msgrcv : %s\n", strerror(errno));
            exit(errno);
        }   
        }
        erreur = msgrcv(id, &zoneCommune, 9, 3, IPC_NOWAIT);
        if (erreur != -1) {
            printf("type : %d\n", zoneCommune.type);
            printf("ordre : %s\n\n", zoneCommune.texte);
        }
        else{
            if(errno != ENOMSG){
            printf("problème msgrcv : %s\n", strerror(errno));
            exit(errno);
        } 
        }
        erreur = msgrcv(id, &zoneCommune, 9, 2, IPC_NOWAIT);
        if (erreur != -1) {
            printf("type : %d\n", zoneCommune.type);
            printf("temperature : %s\n\n", zoneCommune.texte);
        }
        else{
          if (errno != ENOMSG) {
                printf("problème msgrcv : %s\n", strerror(errno));
                exit(errno);
            }     
        }
             
    }

    return (EXIT_SUCCESS);
}

