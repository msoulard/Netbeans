/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: msoulard
 *
 * Created on 5 octobre 2020, 11:04
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
    int entierEnvoie;
    int entierReception;

    //P1
    if (pipe(tube) == 0) { //création du tube ok
        pid = fork();
        if (pid == 0) { //P2
            //lecture dans le tube (bloquant)
            nbOctets = read(tube[0], &entierReception, sizeof(entierReception));
            //affichage du message lu dans le tube
            printf("message du père : %d\n", entierReception);
            //exit(EXIT_SUCCESS);
        }
        else{ //P1
            //initialisation de la chaîne à envoyer
            entierEnvoie = 10;
            //écriture dans le tube
            nbOctets = write(tube[1], &entierEnvoie, sizeof(entierEnvoie));
        }
    }


    return (EXIT_SUCCESS);
}

