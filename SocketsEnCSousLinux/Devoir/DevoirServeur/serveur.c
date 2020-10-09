/* 
 * File:   serveur.c
 * Author: msoulard
 *
 * Created on 29 septembre 2020, 10:47
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
#include <time.h>
#include <string.h>

/*
 * 
 */
int main() {
    int soc; //socket de communication avec le serveur
    struct sockaddr_in infosServeur; //variable contenant les informations du serveur
    struct sockaddr_in infosClient; //variable contenant les informations du client
    char donneeRecue; //donnée reçue si le type demandé est char
    struct tm *dateEtHeure = 0; //donnée envoyé si le type demandé est struct tm
    time_t t;
    char *donneeAEnvoyer = {0}; //variable pour le renvoie de la réponse
    int retour; // variable de retour pour tester les fonctions
    socklen_t taille;
    int b; //variable pour le bind

    //création de la socket en mode DATAGRAM
    soc = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (soc == -1) {
        printf("pb création socket : %s \n", strerror(errno));
        exit(errno);
    }
    //initialisation de la structure contenant les infos du serveur
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(4444); //port dans l'ordre "network"
    infosServeur.sin_addr.s_addr = inet_addr(INADDR_ANY); //adresse dans l'ordre "network"
    //création du bind
    taille = sizeof (infosServeur);
    b = bind(soc, &infosServeur, taille);
    if (b == -1) {
        printf("pb création bind : %s \n", strerror(errno));
        exit(errno);
    }
    //affichage du message
    printf("Serveur UDP sur port 4444 attend une requête d, u, j ou l\n");
    //faire l'envoie tant que le programme n'est pas fermé
    do {
        //recevoir la donnée en provenance du client
        retour = recvfrom(soc, &donneeRecue, sizeof (donneeRecue), 0, (struct sockaddr *) &infosClient, &taille);
        if (retour == -1) {
            printf("pb recvfrom : %s \n", strerror(errno));
            exit(errno);
        }
        //afficherles infos reçus
        printf("message du client : %s /%d : %c\n", inet_ntoa(infosClient.sin_addr), infosClient.sin_port, donneeRecue);
        //envoyer la réponse
        switch (donneeRecue) {
            case 'd': //le client demande la date et l'heure du serveur
                //initialiser la variable avec la date et l'heure
                t = time(NULL);
                dateEtHeure = localtime(&t);
                //envoie de la date et de l'heure
                retour = sendto(soc, &dateEtHeure, sizeof (dateEtHeure), 0, (struct sockaddr *) &infosClient, sizeof (infosClient));
                if (retour == -1) {
                    printf("pb sendto : %s \n", strerror(errno));
                    exit(errno);
                }
                break;
            case 'u': //le client demande l'utilisateur ayant lancé le serveur
                //initialisation du nom
                donneeAEnvoyer = getenv("USER");
                //envoie du nom de l'utilisateur
                retour = sendto(soc, &donneeAEnvoyer, sizeof (donneeAEnvoyer), 0, (struct sockaddr *) &infosClient, sizeof (infosClient));
                if (retour == -1) {
                    printf("pb sendto : %s \n", strerror(errno));
                    exit(errno);
                }
                break;
            case 'j':
                //initialisation du chemin
                donneeAEnvoyer = getenv("CINNAMON_VERSION");
                //envoie du chemin de l'environnement JAVA sur le serveur
                retour = sendto(soc, &donneeAEnvoyer, sizeof (donneeAEnvoyer), 0, (struct sockaddr *) &infosClient, sizeof (infosClient));
                if (retour == -1) {
                    printf("pb sendto : %s \n", strerror(errno));
                    exit(errno);
                }
                break;
            case 'l':
                //initialisation de l'encodage
                donneeAEnvoyer = getenv("LANG");
                //envoie de l'encodage des caractères sur le serveur
                retour = sendto(soc, &donneeAEnvoyer, sizeof (donneeAEnvoyer), 0, (struct sockaddr *) &infosClient, sizeof (infosClient));
                if (retour == -1) {
                    printf("pb sendto : %s \n", strerror(errno));
                    exit(errno);
                }
                break;
        }
    } while (1 == 1);
    // fermer la socket
    close(soc);

    return 0;
}

