/* 
 * File:   serveurTCP.c
 * Author: msoulard
 *
 * Created on 3 novembre 2020, 10:58
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

#define MAXBUFF 255

/*
 * 
 */
int main(int argc, char** argv) {
    int socketFileDAttente; //ma socket
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosClient;
    int donneeRecue;
    ssize_t retour;
    socklen_t taille;
    int b;
    int lis;
    int socketCommunicationClient;
    FILE *fd;
    char *retourLecture;
    char buffer[MAXBUFF];
    //création de la socket en mode datagram
    socketFileDAttente = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFileDAttente == -1) {
        printf("pb création socket : %s \n", strerror(errno));
        exit(errno);
    }
    //initialisation de la structure contenant les infos du serveur
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(5555); //port dans l'ordre "network"
    infosServeur.sin_addr.s_addr = INADDR_ANY; //adresse dans l'ordre "network"
    //création du bind
    taille = sizeof (infosServeur);
    b = bind(socketFileDAttente, &infosServeur, taille);
    if (b == -1) {
        printf("pb création bind : %s \n", strerror(errno));
        exit(errno);
    }
    //file d'attente
    lis = listen(socketFileDAttente, 10);
    //attente de connexion
    taille = sizeof (infosClient);
    socketCommunicationClient = accept(socketFileDAttente, &infosClient, &taille);
    if (socketCommunicationClient == -1) {
        printf("pb création accept : %s \n", strerror(errno));
        exit(errno);
    }
    //recevoir la donnée en provenance du serveur
    retour = read(socketCommunicationClient, &donneeRecue, sizeof (donneeRecue));
    if (retour == -1) {
        printf("pb read : %s \n", strerror(errno));
        exit(errno);
    }
    //afficherles infos reçus
    printf("Adresse du client : %s (%d)\n", inet_ntoa(infosClient.sin_addr), infosClient.sin_port);
    printf("Donnée reçue : %d \n", donneeRecue);
    //envoyer la donnée au serveur
    do {
        switch (donneeRecue) {
            case 0:
                //récupération de la donnée à envoyer
                memset(buffer, '\0', MAXBUFF);
                // invocation d'un programme externe et mise dans un tube popen du resultat sous forme de chaine de caracteres
                // le tube popen sera en lecture (car on veut lire ce qu'a produit le programme externe
                fd = popen("/bin/date", "r");
                if (fd == NULL) {
                    printf(" pb popen : %s\n", strerror(errno));
                    exit(1);
                }
                //lecture de la chaine genere par le programme invoque par popen
                retourLecture = fgets(buffer, MAXBUFF, fd);
                if (retourLecture == NULL) {
                    printf("pb lecture popen\n");
                    exit(1);
                }
                // fermeture du tube
                pclose(fd);
                // affichage de ce qu'a produit "/bin/uname"
                printf("le process a ecrit : [%s]\n", buffer);
                //envoie de la donnée récupérée
                retour = write(socketCommunicationClient, buffer, strlen(buffer));
                if (retour == -1) {
                    printf("pb write : %s \n", strerror(errno));
                    exit(errno);
                }
                break;
            case 1:
                memset(buffer, '\0', MAXBUFF);
                // invocation d'un programme externe et mise dans un tube popen du resultat sous forme de chaine de caracteres
                // le tube popen sera en lecture (car on veut lire ce qu'a produit le programme externe
                fd = popen("/usr/bin/uptime", "r");
                if (fd == NULL) {
                    printf(" pb popen : %s\n", strerror(errno));
                    exit(1);
                }
                //lecture de la chaine genere par le programme invoque par popen
                retourLecture = fgets(buffer, MAXBUFF, fd);
                if (retourLecture == NULL) {
                    printf("pb lecture popen\n");
                    exit(1);
                }
                // fermeture du tube
                pclose(fd);
                // affichage de ce qu'a produit "/bin/uname"
                printf("le process a ecrit : [%s]\n", buffer);
                //envoie de la donnée récupérée
                retour = write(socketCommunicationClient, buffer, strlen(buffer));
                if (retour == -1) {
                    printf("pb write : %s \n", strerror(errno));
                    exit(errno);
                }
                break;
        }
        sleep(5);
    } while (1 == 1);
    // fermer la socket
    close(socketFileDAttente);

    return (EXIT_SUCCESS);
}
