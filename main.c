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
	int start = 0;

	FILE* lab = fopen("3x3_1.dat", "r");
	if( lab == NULL ){
		puts("Error loading file");
		return (-1);
	}
	
	while (fgets(buf, 1024,lab))
    {
        char* tmp = strdup(buf);
        //puts(tmp);
				
				tmp = strtok(tmp,delim);
				while(tmp != NULL ){
					if(start == 0){
						laby.seed = atoi(tmp);
						printf(" %d", laby.seed);
					}
					if(start == 1){
						tmp = strtok(tmp," ");
						laby.width = atoi(tmp);
						printf(" %d", laby.width);
						tmp = strtok(NULL,delim);

						laby.height = atoi(tmp);
						printf(" %d", laby.height);
					}

					if(start == 2){
						tmp = strtok(tmp," ");
						laby.entry = atoi(tmp);
						printf(" %d", laby.entry);
						tmp = strtok(NULL,delim);

						laby.exit = atoi(tmp);
						printf(" %d", laby.exit);
					}
					if( start <= 3){
						int Array[laby.width][laby.height];
						puts("Hi");
						
						for (int i = 0; i < laby.height; i++){
							puts("Me");
							while (tmp != NULL){

								for (int j = 0;j < laby.width;j++){
									tmp = strtok(tmp, ",");

									puts("Cat");
									while (tmp != NULL){
										printf("Tmp is %s",tmp);
										Array[i][j] = atoi(tmp);
										printf("Stored value is %d",Array[i][j]);	
										tmp = strtok(NULL, ",");
									}

									

								}
								tmp = strtok(NULL,delim);

							}
							

						}
						
					}					
					//printf(" %s", tmp);	
					start++;
					tmp = strtok(NULL,delim);
				}	
				

        // NOTE strtok clobbers tmp
        free(tmp);
    }
		
	/*
	while(fgets(buf,256,lab) != NULL ){
				
		tmp = strtok(buf, delim);
		puts(tmp);

		while(tmp != NULL ){
			printf(" %s", tmp);	
			tmp = strtok(NULL,delim);
		}	
			
		//laby.seed = atoi(tmp);
		return 0;

	}
*/
	fclose(lab);

}


