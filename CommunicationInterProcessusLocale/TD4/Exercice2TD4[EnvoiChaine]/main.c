/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: msoulard
 *
 * Created on 5 octobre 2020, 10:45
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
    int tube[2];
    int nbOctets;
    char chaineEnvoie[TAILLEMAXI];
    char chaineReception[TAILLEMAXI];

    //P1
    if (pipe(tube) == 0) { //création du tube ok
        pid = fork();
        if (pid == 0) { //P2
            //initialisation du buffer de réception
            memset(chaineReception, '\0', TAILLEMAXI);
            //lecture dans le tube (bloquant)
            nbOctets = read(tube[0], chaineReception, TAILLEMAXI);
            //affichage du message lu dans le tube
            printf("message du père : %s\n", chaineReception);
            //exit(EXIT_SUCCESS);
        }
        else{ //P1
            //initialisation de la chaîne à envoyer
            strcpy(chaineEnvoie, "je suis ton pere");
            //écriture dans le tube
            nbOctets = write(tube[1], chaineEnvoie, strlen(chaineEnvoie));
        }
    }


    return (EXIT_SUCCESS);
}

