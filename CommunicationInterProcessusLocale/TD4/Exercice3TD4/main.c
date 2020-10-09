/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: msoulard
 *
 * Created on 5 octobre 2020, 11:23
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define TAILLEMAXI 255

/*
 * 
 */
int main(int argc, char** argv) {
    int pid;
    int tube1[2];
    int tube2[2];
    int nbOctets;
    char chaineEnvoie[TAILLEMAXI];
    char chaineReception[TAILLEMAXI];
    float reelEnvoie;
    float reelReception;

    //P1
    if (pipe(tube1) == 0) { //création du tube1 ok
        if (pipe(tube2) == 0) { //création du tube2 ok
            pid = fork();
            if (pid == 0) { //P2
                //initialisation du buffer de réception
                memset(chaineReception, '\0', TAILLEMAXI);
                //lecture dans le tube1 (bloquant)
                nbOctets = read(tube1[0], chaineReception, TAILLEMAXI);
                //affichage du message lu dans le tube1
                printf("message du père : %s\n", chaineReception);
                //initialisation du réel à envoyer
                reelEnvoie = 3.5;
                //écriture dans le tube2
                nbOctets = write(tube2[1], &reelEnvoie, sizeof(reelEnvoie));
            } else { //P1
                //initialisation de la chaîne à envoyer
                strcpy(chaineEnvoie, "je suis ton pere");
                //écriture dans le tube1
                nbOctets = write(tube1[1], chaineEnvoie, strlen(chaineEnvoie));
                //lecture du message reçu dans le tube2
                nbOctets = read(tube2[0], &reelReception, sizeof(reelReception));
                //affichage du message lu dans le tube2
                printf("message du fils : %.2f\n", reelReception);
            }
        }
    }


    return (EXIT_SUCCESS);
}

