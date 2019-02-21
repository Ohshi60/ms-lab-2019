#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// JSON object
/*{
    "seed": 1234,
    "width": 14,
    "height": 14,
    "entry": 1,
    "exit": 196,
    "cells": [[{"north": true, "south": true, "east": false, "west": false}, ...], ...]
}
 */
// C data structures

//Prototypes
int loadLab();
//Data Structures

struct cell {
    int north;
    int south;
    int east;
    int west;
};
 
struct labyrinth {
    int seed;
    int width;
    int height;
    int entry;
    int exit;
    struct cell **cells;
} laby;

int main()
{
	printf("***Loading Labyrinth ***\n" );
	char *buffy;
	loadLab();

	return 0;
}

int loadLab(){
	
	char *buf = malloc(256);
	char *tmp;
	const char delim[2] = "\n";

	FILE* lab = fopen("3x3_1.dat", "r");
	if( lab == NULL ){
		puts("Error loading file");
		return (-1);
	}
	if(fgets(buf,255,lab) != NULL ){
		puts(buf);		
		tmp = strtok(buf, delim);
			printf(" %s\n", tmp);	
		/*
		while(tmp != NULL ){

			tmp = strtok(NULL,delim);
		}	
		*/			
		//laby.seed = atoi(tmp);
		return 0;

	}
	fclose(lab);

}


