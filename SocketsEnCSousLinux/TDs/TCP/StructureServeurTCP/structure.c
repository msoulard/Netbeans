/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   structure.c
 * Author: msoulard
 *
 * Created on 21 septembre 2020, 11:21
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

/*
 * 
 */
typedef struct{
	unsigned char jour;
	unsigned char mois;
	unsigned short int annee;
	char	jourDeLaSemaine[10];
}datePerso;

int main ( int argc, char *argv[] )
{
	int fdSocket,fdSocketClient;

	struct sockaddr_in adresseServeur;
	struct sockaddr_in adresseClient;

	int retour;
	int tailleClient;
	char buffer[255];
	int valeurEnv, valeurRet=0;
	datePerso dateClient;

	printf("serveur TCP sur port 7777 attend une structure de type datePerso\n");
	memset ( buffer, '\0', 255 );



	adresseServeur.sin_family = AF_INET;

	adresseServeur.sin_port = htons ( 7777 );	//numero de port du serveur dans l'ordre des octets du r�seau
	adresseServeur.sin_addr.s_addr = INADDR_ANY;	// adresse IP du serveur dans l'ordre des octets du reseau
	//stresseur de serveur
	fdSocket = socket ( PF_INET, SOCK_STREAM, IPPROTO_TCP );

	if ( fdSocket == -1 )
	{
		printf ( "pb socket : %s\n", strerror ( errno ) );
		exit ( 0 );
	}
retour = bind ( fdSocket, ( struct sockaddr* ) &adresseServeur, sizeof ( adresseServeur ) );	//attachement ip-port

	if ( retour == -1 )
	{
		printf ( "pb bind : %s\n", strerror ( errno ) );
		exit ( 0 );
	}

	retour=listen ( fdSocket,10 );	//je peux gerer 10 clients en file d'attente
	if ( retour == -1 )
	{
		printf ( "pb listen : %s\n", strerror ( errno ) );
		exit ( 0 );
	}

	tailleClient = sizeof ( adresseClient );


	while ( 1==1 )
	{
		fdSocketClient=accept ( fdSocket, ( struct sockaddr * ) &adresseClient, &tailleClient );	// acceptation de la connexion client et creation de la socket de communication

		if ( fdSocketClient == -1 )
		{
			printf ( "pb accept : %s\n", strerror ( errno ) );
			exit ( 0 );
		}

		retour = read ( fdSocketClient,&dateClient,sizeof ( dateClient ) );
		if ( retour == -1 )
		{
			printf ( "pb connect : %s\n", strerror ( errno ) );
			exit ( 0 );
		}
		printf("message du client %s/%d: \n", inet_ntoa(adresseClient.sin_addr), adresseClient.sin_port);
		printf("%s %d/%d/%d\n",dateClient.jourDeLaSemaine,dateClient.jour,dateClient.mois,dateClient.annee);

		

		close ( fdSocketClient );

	}
	return EXIT_SUCCESS;
}

