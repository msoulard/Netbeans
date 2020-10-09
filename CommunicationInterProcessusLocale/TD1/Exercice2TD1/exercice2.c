/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   exercice2.c
 * Author: msoulard
 *
 * Created on 22 septembre 2020, 10:55
 */

#include <stdio.h>
#include <stdlib.h>

int main ( int argc, char *argv[] )
{
	int pid1,pid2,pid3;
	pid1 = fork();
	if ( pid1 == 0 )	//p1
	{
		printf ( "p1\n" );
	}
	else	//p4
	{
		pid2 = fork();
		if ( pid2 == 0 )	//p2
		{
			printf ( "p2\n" );
		}
		else	//p4
		{
			pid3 = fork();
			if ( pid3 == 0 )	//p3
			{
				printf ( "p3\n" );
			}
			else	//p4
			{
				printf ( "p4\n" );
			}
		}
	}
	return EXIT_SUCCESS;
}

