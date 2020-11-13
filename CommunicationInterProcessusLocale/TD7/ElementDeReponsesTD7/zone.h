/************************************************/
/*	zone.h
 *	Le type des donnees de la
 *	file de message	
 ************************************************/
#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>

#ifndef ZONE_H
#define ZONE_H

// type de ce qui va etre partage
struct donnees{
	long type;
	char texte[9];
};
#endif