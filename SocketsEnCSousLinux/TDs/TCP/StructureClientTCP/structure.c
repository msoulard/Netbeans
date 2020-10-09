/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: msoulard
 *
 * Created on 15 septembre 2020, 11:12
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

typedef struct{
	unsigned char jour;
	unsigned char mois;
	unsigned short int annee;
	char jourDeLaSemaine[10];	// le jour en toute lettre
}datePerso;

/*
 * 
 */
int main(int argc, char** argv) {
    int soc; //ma socket
    struct sockaddr_in infosServeur;
    datePerso donnesAEnvoyer;
    ssize_t retour;
    socklen_t taille;
    int co;
    //crétion de la socket en mode datagram
    soc = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (soc == -1) {
        printf("pb création socket : %s \n", strerror(errno));
        exit(errno);
    }
    //initialisation de la structure contenant les infos du serveur
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(7777); //port dans l'ordre "network"
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.147"); //adresse dans l'ordre "network"
    //initialisation de le connection
    taille= sizeof(infosServeur);
    co = connect(soc, &infosServeur, taille);
    if (co == -1) {
        printf("pb création de la connection : %s \n", strerror(errno));
        exit(errno);
    }
    //envoyer la donnée au serveur
    donnesAEnvoyer.annee = 2006;
    donnesAEnvoyer.jour = 23;
    strcpy(donnesAEnvoyer.jourDeLaSemaine,"jeudi");
    donnesAEnvoyer.mois = 5;
    retour = write(soc, &donnesAEnvoyer, sizeof (donnesAEnvoyer));
    if (retour == -1) {
        printf("pb write : %s \n", strerror(errno));
        exit(errno);
    }
    // fermer la socket
    close(soc);

    return (EXIT_SUCCESS);
}

