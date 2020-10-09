/* 
 * File:   web.c
 * Author: msoulard
 *
 * Created on 21 septembre 2020, 10:27
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

#define NBMAX 800

/*
 * 
 */
int main(int argc, char** argv) {
    int socketFileDAttente; //ma socket
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosClient;
    char donnesAEnvoyer[NBMAX] = "HTTP/1.1 200 OK\nContent-Length: 3301\nContent-Type: text/html\n\n<html><body><center><h1>c'est mon serveur http</h1></center></body></html>";
    char donneeRecue[NBMAX];
    ssize_t retour;
    socklen_t taille;
    int b;
    int lis;
    int socketCommunicationClient;
    //création de la socket en mode datagram
    socketFileDAttente = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFileDAttente == -1) {
        printf("pb création socket : %s \n", strerror(errno));
        exit(errno);
    }
    //initialisation de la structure contenant les infos du serveur
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(8888); //port dans l'ordre "network"
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.98"); //adresse dans l'ordre "network"
    //création du bind
    taille= sizeof(infosServeur);
    b = bind(socketFileDAttente, &infosServeur, taille);
    if(b == -1){
        printf("pb création bind : %s \n", strerror(errno));
        exit(errno);
    }
    //file d'attente
    lis = listen(socketFileDAttente, 10);
    //attente de connexion
    taille = sizeof(infosClient);
    socketCommunicationClient = accept(socketFileDAttente, &infosClient, &taille);
    if(socketCommunicationClient == -1){
        printf("pb création accept : %s \n", strerror(errno));
        exit(errno);
    }
    //recevoir la donnée en provenance du serveur
    retour = read(socketCommunicationClient, donneeRecue, NBMAX);
    if (retour == -1) {
        printf("pb read : %s \n", strerror(errno));
        exit(errno);
    }
    //afficherles infos reçus
    printf("Adresse du client : %s (%d)\n",inet_ntoa(infosClient.sin_addr), infosClient.sin_port);
/*
    printf("Donnée reçue : %f \n", donneeRecue);
*/
    //envoyer la donnée au serveur
    retour = write(socketCommunicationClient, donnesAEnvoyer, strlen (donnesAEnvoyer));
    if (retour == -1) {
        printf("pb write : %s \n", strerror(errno));
        exit(errno);
    }
    // fermer la socket
    close(socketFileDAttente);

    return (EXIT_SUCCESS);
}

