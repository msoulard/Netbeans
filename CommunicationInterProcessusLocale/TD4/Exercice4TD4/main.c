/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: msoulard
 *
 * Created on 5 octobre 2020, 11:33
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/*
 * 
 */

//fonction de traitement du signal SIGUSR1
void traitement(int sig) {
    (void) signal(SIGUSR1, traitement);
    printf("un signal SIGUSR1 je suis pid :%d\n", getpid());
}

int main(int argc, char** argv) {
    int pid;
    int pidEnvoi;
    int pidReception;
    int pidP1 = getpid();
    int tube[2];
    int nbOctets;
    (void) signal(SIGUSR1, traitement); //redéroutage des signaux SIGUSR1 vers la fonction traitement

    if (pipe(tube) == 0) {
        pid = fork();
        if (pid == 0) { //P2
            pid = fork();
            if (pid == 0) { //P3
                printf("P3 pid=%d ppid=%d\n", getpid(), getppid());
                //initialisation du pid à envoyer
                pidEnvoi = getpid();
                //écriture du pid dans le tube
                nbOctets = write(tube[1], &pidEnvoi, sizeof (pidEnvoi));
                pause();
            } else { //P2
                printf("P2 pid=%d ppid=%d\n", getpid(), getppid());
                pause();

            }
        } else { //P1
            kill(pid, SIGUSR1);
            printf("pere pid=%d\n", getpid());
            //lecture du message reçu dans le tube
            nbOctets = read(tube[0], &pidReception, sizeof (pidReception));
            //affichage du message reçu dans le tube
            printf("Pere : pid de P3 : %d\n", pidReception);
            //envoie d'un signal
            kill(pidReception, SIGUSR1);
        }
    }

    return (EXIT_SUCCESS);
}

