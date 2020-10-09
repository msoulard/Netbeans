/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: msoulard
 *
 * Created on 6 octobre 2020, 11:00
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/syscall.h>

/*
 * 
 */

typedef struct {
	int v1;
	int v2;
	int v3;
}laStruct;

laStruct zoneCommune; //zone commune

void *threadT1(void *arg) {
    int *ptr = (int *) arg; //ptr prend l'adresse de l'entier en paramètre
    int val = *ptr; //récupération du contenu pointé
    printf("pour t1 pid dans le thread : %d\n", getpid());
    printf("pour t1 tid dans le thread : %d\n", syscall(SYS_gettid));
    zoneCommune.v1 = val;
    
    pthread_exit((void *)"");
}

void *threadT2(void *arg) {
    int *ptr = (int *) arg; //ptr prend l'adresse de l'entier en paramètre
    int val = *ptr; //récupération du contenu pointé
    printf("pour t2 pid dans le thread : %d\n", getpid());
    printf("pour t2 tid dans le thread : %d\n", syscall(SYS_gettid));
    zoneCommune.v2 = val;
    
    pthread_exit((void *)"");
}

void *threadT3(void *arg) {
    int *ptr = (int *) arg; //ptr prend l'adresse de l'entier en paramètre
    int val = *ptr; //récupération du contenu pointé
    printf("pour t3 pid dans le thread : %d\n", getpid());
    printf("pour t3 tid dans le thread : %d\n", syscall(SYS_gettid));
    zoneCommune.v3 = val;
    
    pthread_exit((void *)"");
}

int main() {
    int res;
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    void *thread_result;
    int val1;
    int val2;
    int val3;
    
    zoneCommune.v1 = 0;
    zoneCommune.v2 = 0;
    zoneCommune.v3 = 0;

    printf("zone commune avant thread : \nv1 = %d\nv2 = %d\nv3 = %d\n", zoneCommune.v1, zoneCommune.v2, zoneCommune.v3);

    val1 = 10;
    val2 = 15;
    val3 = 20;

    res = pthread_create(&t1, NULL, threadT1, (void *) &val1);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&t2, NULL, threadT2, (void *) &val2);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&t3, NULL, threadT3, (void *) &val3);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    printf("attente de la fin du thread...\n");

    res = pthread_join(t1, &thread_result);
    if (res != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    res = pthread_join(t2, &thread_result);
    if (res != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    res = pthread_join(t3, &thread_result);
    if (res != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    
    printf("zone commune après thread : \nv1 = %d\nv2 = %d\nv3 = %d\n", zoneCommune.v1, zoneCommune.v2, zoneCommune.v3);
    
    exit(EXIT_SUCCESS);
}


