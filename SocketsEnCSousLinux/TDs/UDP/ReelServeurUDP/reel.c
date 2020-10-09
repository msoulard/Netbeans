/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   reel.c
 * Author: msoulard
 *
 * Created on 14 septembre 2020, 11:27
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

/*
 * 
 */
int main(int argc, char** argv) {
    int soc; //ma socket
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosClient;
    float donnesAEnvoyer;
    float donneeRecue;
    int retour;
    socklen_t taille;
    int b;
    //création de la socket en mode datagram
    soc = socket(PF_INET, SOCK_DGRAM, 0 /*IPPROTO_UDP*/);
    if (soc == -1) {
        printf("pb création socket : %s \n", strerror(errno));
        exit(errno);
    }    
    //initialisation de la structure contenant les infos du serveur
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(3333); //port dans l'ordre "network"
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.138"); //adresse dans l'ordre "network"
    //création du bind
    taille= sizeof(infosServeur);
    b = bind(soc, &infosServeur, taille);
    if(b == -1){
        printf("pb création bind : %s \n", strerror(errno));
        exit(errno);
    }
    //recevoir la donnée en provenance du client
    retour = recvfrom(soc, &donneeRecue, sizeof (donneeRecue), 0, (struct sockaddr *) &infosClient, &taille);
    if (retour == -1) {
        printf("pb recvfrom : %s \n", strerror(errno));
        exit(errno);
    }
    //afficher infos client
    printf("Adresse du client : %s (%d)\n",inet_ntoa(infosClient.sin_addr), infosClient.sin_port);
    printf("Donnée reçue : %f \n", donneeRecue);
    //envoyer la donnée au client
    donnesAEnvoyer = -donneeRecue;
    retour = sendto(soc, &donnesAEnvoyer, sizeof (donnesAEnvoyer), 0, (struct sockaddr *) &infosClient, sizeof (infosClient));
    if (retour == -1) {
        printf("pb sendto : %s \n", strerror(errno));
        exit(errno);
    }
    // fermer la socket
    close(soc);

    return (EXIT_SUCCESS);
}

