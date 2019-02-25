#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//Global variables

// JSON object
/*{
    "seed": 1234,
    "width": 14,
    "height": 14,
    "entry": 1,
    "exit": 196,
    "cells": [[{"north": true, "south": true, "east": false, "west": false}, ...], ...]
}*/
 
// C data structures
 
typedef struct cell {
    unsigned int north;
    unsigned int south;
    unsigned int east;
    unsigned int west;
    unsigned int value;
}cell;
 
typedef struct labyrinth {
    int seed;
    int width;
    int height;
    int entry;
    int exit;
    cell **cells;
} lab;

void alloc_cells(lab *lab){
  lab->cells = malloc(lab->height*sizeof(cell));
  for(int i = 0;i < lab->width;i++){
    lab->cells[i] = malloc(lab->width * sizeof(cell));
  }
}
int flipBits2(int n, int k) {
    int mask = (1 << k) - 1;
    return ~n & mask;
}
int returnBits2(int n, int k) {
    int mask = (1 << k) - 1;
    return n & mask;
}
unsigned int_to_int(unsigned k) {
    if (k == 0) return 0;
    if (k == 1) return 1;                       /* optional */
    return (k % 2) + 10 * int_to_int(k / 2);
}
unsigned int bitCheck(unsigned int mask, int bit){
   if ( (mask >> bit ) & 1){
      return 1;
   }else{
      return 0;
   }
}
void fill_cell(cell *c){
    unsigned int mask = c->value ;// 1 1 1 1
    int pin0 = 0;
    int pin1 = 1;
    int pin2 = 2;
    int pin3 = 3;
    unsigned int bit0= bitCheck( mask, pin0);
    unsigned int bit1= bitCheck( mask, pin1);
    unsigned int bit2= bitCheck( mask, pin2);
    unsigned int bit3= bitCheck( mask, pin3);
    c->north = bit0 ;
    c->south = bit1 ;
    c->east = bit2 ;
    c->west = bit3 ;
    printf("North %d South: %d East: %d West: %d",c->north,c->south,c->east,c->west);
    printf("\n");
}

int next_dir(cell *c){
    puts("Next Direction");
    
    fill_cell(c);
    int result = 0;
    if (!c->north){
      return result = 1;
    } if (!c->south){
      return result = 2;
    }if (!c->east){
      return result = 4;
    } if(!c->west){
      return result = 8;
    }
}

void print_lab(lab *lab){
  printf("Seed %d width %d height %d entry %d exit %d\n",lab->seed, lab->width, lab->height, lab->entry, lab->exit);
  for(int i = 0;i < lab->height;i++){
    for(int j = 0;j< lab->width;j++){
      printf("%d ",lab->cells[j][i].value);
      printf("%d ",lab->cells[j][i].north);
      printf("%d ",lab->cells[j][i].south);
      printf("%d ",lab->cells[j][i].east);
      printf("%d ",lab->cells[j][i].west);
    }
    printf("\n");
  }
}
void init_cells(lab *l){
  for(int i=0;i<l->height;i++){
    for(int j=0;j<l->width;j++){
      fill_cell(&l->cells[j][i]);
    }
    printf("\n");
  }
}

void get_lab(char* file_name,struct labyrinth *lab){
  int linecounter = 0;
  int rowCounter = 0;
  char line[255];
  FILE* file = fopen(file_name,"r"); 
  if (!file) {
         fprintf(stderr, "error: could not open textfile: %s\n", file_name);
  }
  while (fgets(line, sizeof(line), file)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
    
    char* tmp = malloc(sizeof(line));

    if(linecounter==0){
        lab->seed = atoi(line);
        linecounter++;
    }else if(linecounter==1){
        tmp = strtok(line," ");
        lab->width = atoi(tmp);
        tmp = strtok(NULL," ");
        lab->height = atoi(tmp);
        alloc_cells(lab);
        linecounter++;

    }else if(linecounter==2){
        
        tmp = strtok(line," ");
        lab->entry = atoi(tmp);
        tmp = strtok(NULL," ");
        lab->exit = atoi(tmp);
        linecounter++;
    } else{
        //alloc cells
        tmp = strtok(line, ",");
        for (int j = 0;j < lab->width; j++){
          lab->cells[j][rowCounter].value = atoi(tmp);
          tmp = strtok(NULL,",");
        }
        rowCounter++;
    }
  }
  fclose(file);
}
/*
int move(int row,int col,lab *lab,int dir){
  row--;
  col--;
  int goal_y = lab->height-1;
  int goal_x = lab->exit-1;
  if(row == goal_y && col == goal_x){
      return 1;
      puts("Found it");
  }
  if(dir == 1){
    puts("Going North");
    printf("dir%d, row %d,col %d",dir,row,col);

    row--;
    lab->cells[row][col].value = lab->cells[row][col].value + dir;
    dir = next_dir(&lab->cells[row][col]);
    printf("dir%d, row %d,col %d",dir,row,col);
  
    move(row,col,lab,dir);
  }else if(dir == 2){
    puts("Going South");
    printf("dir%d, row %d,col %d",dir,row,col);
    row++;
    lab->cells[row][col].value + dir;
    dir = next_dir(&lab->cells[row][col]);  
    move(row,col,lab,dir);
  }else if(dir == 4){
    puts("Going East");
    col++;

    printf("dir%d, row %d,col %d",dir,row,col);
    lab->cells[row][col].value = lab->cells[row][col].value + dir;
    dir = next_dir(&lab->cells[row][col]);  
    move(row,col,lab,dir);
  }else if(dir == 8){
    puts("Going West");
    col--;

    printf("%d, %d",dir,lab->cells[row][col].value);
    lab->cells[row][col].value = lab->cells[row][col].value + dir;
    dir = next_dir(&lab->cells[row][col]);;  
    move(row,col,lab,dir);
  }  
}
*/
void alloc_visited(lab *lab){
    int rows = lab->height;
    int cols = lab->width;
    int** maze = malloc(rows * sizeof(int));
    for (int i= 0;i < rows;i++){
      maze[i] = malloc(cols * sizeof(int));
  }
}
void get_visited(lab *l,int** visited){
  alloc_visited(l);


}
int main(){
  int ** visited;
  lab lab1;
  lab * plab = &lab1;
  get_lab("3x3_1.dat", plab);
  print_lab(plab);
  init_cells(plab);
  print_lab(plab);
  //move(0,plab->entry,plab,2);
  print_lab(plab);
  return 0;
}