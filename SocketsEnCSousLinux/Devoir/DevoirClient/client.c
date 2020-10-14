/* 
 * File:   client.c
 * Author: msoulard
 * Programme du client UDP
 * Created on 29 septembre 2020, 09:16
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
    char adresseServeur[25]; //adresse du serveur choisi
    int choix; //choix de la donnée à envoyer au serveur
    char donneeAEnvoyer; //la donnée à envoyer au serveur
    char donneeRecue[255]; //donnée reçue si le type demandé est char *
    struct tm dateEtHeure; //donnée reçue si le type demandé est struct tm
    int retour; // variable de retour pour tester les fonctions
    socklen_t taille;

    //création de la socket en mode DATAGRAM
    soc = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (soc == -1) {
        printf("pb création socket : %s \n", strerror(errno));
        exit(errno);
    }
    //initialisation de la structure contenant les infos du serveur
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(4444); //port dans l'ordre "network"
    printf("Quelle est l'adresse du serveur ? ");
    gets(adresseServeur);
    infosServeur.sin_addr.s_addr = inet_addr(adresseServeur); //adresse dans l'ordre "network"
    //Données à envoyer au serveur
    choix == 0;
    //faire tant que choix est différent de 5
    do {
        //Affichage des différentes possiblités
        printf("1 - Date et heure du serveur\n");
        printf("2 - Utilisateur ayant lancé le serveur\n");
        printf("3 - Chemin de l'environnement JAVA sur le serveur\n");
        printf("4 - Encodage des caractères sur le serveur\n");
        printf("5 - Quitter le programme\n");
        //Choix de l'utilisateur
        printf("Votre choix : ");
        scanf(" %d", &choix);
        switch (choix) {
            case 1: // si choix est 1, on envoie d
                donneeAEnvoyer = 'd';
                //envoie de la donnée
                retour = sendto(soc, &donneeAEnvoyer, sizeof (donneeAEnvoyer), 0, (struct sockaddr *) &infosServeur, sizeof (infosServeur));
                if (retour == -1) {
                    printf("pb sendto : %s \n", strerror(errno));
                    exit(errno);
                }
                //recevoir la donnée
                retour = recvfrom(soc, &dateEtHeure, sizeof (dateEtHeure), 0, (struct sockaddr *) &infosServeur, &taille);
                if (retour == -1) {
                    printf("pb recvfrom : %s \n", strerror(errno));
                    exit(errno);
                }
                //afficher la donnée
                printf("%d/%d/%d %d:%d:%d\n", dateEtHeure.tm_mday, dateEtHeure.tm_mon + 1, dateEtHeure.tm_year + 1900, dateEtHeure.tm_hour, dateEtHeure.tm_min, dateEtHeure.tm_hour);
                break;
            case 2: // si choix est 2, on envoie u
                donneeAEnvoyer = 'u';
                //envoie de la donnée
                retour = sendto(soc, &donneeAEnvoyer, sizeof (donneeAEnvoyer), 0, (struct sockaddr *) &infosServeur, sizeof (infosServeur));
                if (retour == -1) {
                    printf("pb sendto : %s \n", strerror(errno));
                    exit(errno);
                }
                //recevoir la donnée
                memset(donneeRecue, '\0', 255);
                retour = recvfrom(soc, donneeRecue, 255, 0, (struct sockaddr *) &infosServeur, &taille);
                if (retour == -1) {
                    printf("pb recvfrom : %s \n", strerror(errno));
                    exit(errno);
                }
                //afficher la donnée reçue
                printf("Utilisateur : %s \n", donneeRecue);
                memset(donneeRecue, '\0', 255);
                break;
            case 3: // si choix est 3, on envoie j
                donneeAEnvoyer = 'j';
                //envoie de la donnée
                retour = sendto(soc, &donneeAEnvoyer, sizeof (donneeAEnvoyer), 0, (struct sockaddr *) &infosServeur, sizeof (infosServeur));
                if (retour == -1) {
                    printf("pb sendto : %s \n", strerror(errno));
                    exit(errno);
                }                
                //recevoir la donnée
                memset(donneeRecue, '\0', 255);
                retour = recvfrom(soc, donneeRecue, 255, 0, (struct sockaddr *) &infosServeur, &taille);
                if (retour == -1) {
                    printf("pb recvfrom : %s \n", strerror(errno));
                    exit(errno);
                }
                //afficher la donnée reçue
                printf("Version du gestionnaire graphique : %s \n", donneeRecue);
                memset(donneeRecue, '\0', 255);
                break;
            case 4: //si choix est 4, on envoie l
                donneeAEnvoyer = 'l';
                //envoie de la donnée
                retour = sendto(soc, &donneeAEnvoyer, sizeof (donneeAEnvoyer), 0, (struct sockaddr *) &infosServeur, sizeof (infosServeur));
                if (retour == -1) {
                    printf("pb sendto : %s \n", strerror(errno));
                    exit(errno);
                }
                //recevoir la donnée
                memset(donneeRecue, '\0', 255);
                retour = recvfrom(soc, donneeRecue, 255, 0, (struct sockaddr *) &infosServeur, &taille);
                if (retour == -1) {
                    printf("pb recvfrom : %s \n", strerror(errno));
                    exit(errno);
                }
                //afficher la donnée reçue
                printf("Encodage des caractères : %s \n", donneeRecue);
                memset(donneeRecue, '\0', 255);
                break;
        }
    } while (choix != 5);
    // fermer la socket
    close(soc);

    return 0;
}

