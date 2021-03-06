/* 
 * File:   main.c
 * Author: msoulard
 *
 * Created on 5 octobre 2020, 09:36
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
        printf("un signal SIGUSR1 je suis pid :%d\n", getppid());
}

int main(int argc, char** argv) {
    int pid;
    int pidP1 = getpid();
    (void) signal(SIGUSR1, traitement);	//redéroutage des signaux SIGUSR1 vers la fonction traitement
    
    pid = fork();
    
    if(pid == 0){ //P2
        pid = fork();
        if(pid == 0){ //P3
            printf("P3 pid=%d ppid=%d\n", getpid(), getppid());
            kill(pidP1, SIGUSR1);
        }
        else{ //P2
            sleep(1);
            printf("P2 pid=%d ppid=%d\n", getpid(), getppid());
            kill(pidP1, SIGUSR1);
        }
    }
    else{ //P1
        pause();
        pause();
        printf("pere pid=%d\n", getpid());
    }

    return (EXIT_SUCCESS);
}

