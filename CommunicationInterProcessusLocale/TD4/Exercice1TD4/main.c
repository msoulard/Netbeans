/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: msoulard
 *
 * Created on 5 octobre 2020, 10:37
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAXBUFF 255

int main() {
    FILE *fd;
    char *retourLecture;
    char buffer[MAXBUFF];
    memset(buffer, '\0', MAXBUFF);
    // invocation d'un programme externe et mise dans un tube popen du resultat sous forme de chaine de caracteres
    // le tube popen sera en lecture (car on veut lire ce qu'a produit le programme externe
    fd = popen("/bin/uname", "r");
    if (fd == NULL) {
        printf(" pb popen : %s\n", strerror(errno));
        exit(1);
    }
    //lecture de la chaine genere par le programme invoque par popen (-> /bin/uname)
    retourLecture = fgets(buffer, MAXBUFF, fd);
    if (retourLecture == NULL) {
        printf("pb lecture popen\n");
        exit(1);
    }
    // fermeture du tube
    pclose(fd);
    // affichage de ce qu'a produit "/bin/uname"
    printf("le process a écrit : [%s]\n", buffer);

    return 0;
}

