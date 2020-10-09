/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   exercice5.c
 * Author: msoulard
 *
 * Created on 22 septembre 2020, 11:37
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/*
 * 
 */
int main(int argc, char** argv) {
    int pid;
    char message[BUFSIZ] = {0};
    //P1
    pid = fork();
    if (pid == 0) { //P3
        pid = fork();
        if (pid == 0) { //P2

            sprintf(message, "P2 pid = %d ppid = %d", getpid(), getppid());
            boite("P2", message);
        } else { //P3
            pid = fork();
            if (pid == 0) { //P5
                pid = fork();
                if (pid == 0) { //P6
                        sprintf(message, "P6 pid = %d ppid = %d", getpid(), getppid());
                        boite("P6", message);
                } else { //P5
                    pid = fork();
                    if (pid == 0) { //P7
                        sprintf(message, "P7 pid = %d ppid = %d", getpid(), getppid());
                        boite("P7", message);
                    }
                    else{ //P5
                        sprintf(message, "P5 pid = %d ppid = %d", getpid(), getppid());
                        boite("P5", message);
                    }
                }

            } else { //P3
                pid = fork();
                if (pid == 0) { // P4
                    sprintf(message, "P4 pid = %d ppid = %d", getpid(), getppid());
                    boite("P4", message);
                }
                sprintf(message, "P3 pid = %d ppid = %d", getpid(), getppid());
                boite("P3", message);
            }
        }

    } else { //P1
        sprintf(message, "P1 pid = %d ppid = %d", getpid(), getppid());
        boite("P1", message);
    }

    return (EXIT_SUCCESS);
}

