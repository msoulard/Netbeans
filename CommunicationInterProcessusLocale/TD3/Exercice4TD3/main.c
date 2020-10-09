/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: msoulard
 *
 * Created on 5 octobre 2020, 10:21
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
int compteur = 0;

//fonction de traitement du signal SIGUSR1
void traitement(int sig) {
    //compteur++;
    (void) signal(SIGUSR1, traitement);
    //if (compteur == 2) {
        printf("un signal SIGUSR1 je suis pid :%d\n", getpid());
    //}
}

int main(int argc, char** argv) {
    int pid;
    int pidP1 = getpid();
    (void) signal(SIGUSR1, traitement); //redéroutage des signaux SIGUSR1 vers la fonction traitement

    pid = fork();

    if (pid == 0) { //P2
        pid = fork();
        if (pid == 0) { //P3
            printf("P3 pid=%d ppid=%d\n", getpid(), getppid());
            kill(getppid(), SIGUSR1); //envoyer SIGUSR1 à P2
        } 
        else { //P2
            printf("P2 pid=%d ppid=%d\n", getpid(), getppid());
            pause();
            pause();            
        }
    } 
    else { //P1
        kill(pid, SIGUSR1); //envoyer SIGUSR1 à P2
        printf("P1 pid=%d ppid=%d\n", getpid(), getppid());
        sleep(2);
    }

    return (EXIT_SUCCESS);
}