/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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
#include "zone.h"

/*
 *
 */
int main(int argc, char** argv) {
    key_t clef;
    int id;
    donnees zoneCommune;

    //création de la clef de partage
    clef = ftok("/tmp/msoulard", 'a');
    if (clef == -1) {
        printf("problème ftok : %s\n", strerror(errno));
        exit(errno);
    }
    //création du segment mémoire partagé
    id = msgget(clef, IPC_CREAT | 0600);
    if (id == -1) {
        printf("problème shmget : %s\n", strerror(errno));
        exit(errno);
    }
    printf("id du segment : %d\n", id);
    //attribution adresse virtuelle du segment
    zoneCommune = (donnees *) shmat(id, NULL, SHM_W);
    if (zoneCommune == (void *) - 1) {
        printf("problème shmat : %s\n", strerror(errno));
        exit(errno);
    }
    return (EXIT_SUCCESS);
}

