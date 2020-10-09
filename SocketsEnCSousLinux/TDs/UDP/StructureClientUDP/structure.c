/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   structure.c
 * Author: msoulard
 *
 * Created on 8 septembre 2020, 11:55
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
    datePerso donneeRecue;
    int retour;
    socklen_t taille;
    //crétion de la socket en mode datagram
    soc = socket(PF_INET, SOCK_DGRAM, 0 /*IPPROTO_UDP*/);
    if (soc == -1) {
        printf("pb création socket : %s \n", strerror(errno));
        exit(errno);
    }
    //initialisation de la structure contenant les infos du serveur
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(4444); //port dans l'ordre "network"
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.104"); //adresse dans l'ordre "network"
    //envoyer la donnée au serveur
    donnesAEnvoyer.annee = 2006;
    donnesAEnvoyer.jour = 23;
    strcpy(donnesAEnvoyer.jourDeLaSemaine,"jeudi");
    donnesAEnvoyer.mois = 5;
    retour = sendto(soc, &donnesAEnvoyer, sizeof (donnesAEnvoyer), 0, (struct sockaddr *) &infosServeur, sizeof (infosServeur));
    if (retour == -1) {
        printf("pb sendto : %s \n", strerror(errno));
        exit(errno);
    }
/*
    //recevoir la donnée en provenance du serveur
    retour = recvfrom(soc, &donneeRecue, sizeof (donneeRecue), 0, (struct sockaddr *) &infosServeur, &taille);
    if (retour == -1) {
        printf("pb recvfrom : %s \n", strerror(errno));
        exit(errno);
    }
    //afficher la donée
    printf("Donnée reçue : %s %d %d %d \n", donneeRecue.jourDeLaSemaine, donneeRecue.jour, donneeRecue.mois, donneeRecue.annee);
*/
    // fermer la socket
    close(soc);
    
    return (EXIT_SUCCESS);
}
