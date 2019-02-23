#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct labyrinth{
  int seed, width, height, entry, exit;
  int * cells;
};

int loadLab(FILE* fp, struct labyrinth *lab){
  char line[256];
  int i = 0;
  int rowCounter = 0;

  if (!fp) {
      fprintf(stderr, "error: could not open textfile: %s\n", fp);
         return EXIT_FAILURE;
    }
  while (fgets(line, sizeof(line), fp)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
      char* tmp = malloc(sizeof(line));
      printf("%s", line); 
      if(i==0) //First line is the seed of the labyrinth
          {
          lab->seed = atoi(line);
          i++;
          }
      else if(i==1)
          //Second line is width and height separated by whitespace 
          {
						tmp = strtok(line," ");
						lab->width = atoi(tmp);
						tmp = strtok(NULL," ");
						lab->height = atoi(tmp);
            i++;
          }    
      else if(i==2)
          //Third line is entry and exit separated by whitespace 
          {
						tmp = strtok(line," ");
						lab->entry = atoi(tmp);
						tmp = strtok(NULL," ");

						lab->exit = atoi(tmp);
            i++;
          }
      else
          {
            //Construct cells, comma-separated
            lab->cells = malloc(lab->width * lab->height * sizeof(int));
            int (*cells)[lab->width] = lab->cells;
            tmp = strtok(line,",");
            for(int j= 0;j < lab->width;j++){
              cells[rowCounter][j] = atoi(tmp);
              tmp = strtok(NULL,",");
              printf("Coord (%d,%d) Bitpattern value: %d\n", j,rowCounter,cells[rowCounter][j]);

            }
            rowCounter++;
          }
    
  }
  printf("Seed %d width %d height %d entry %d exit %d\n",lab->seed, lab->width, lab->height, lab->entry, lab->exit);
  return 0;
}        

int main(int argc, char* argv[])
{
    char const* const fileName = argv[1]; /* should check that argc > 1 */
    puts(fileName);
    FILE* file = fopen(fileName,"r");
    int i= 0;
    char line[256];
    struct labyrinth laby;

    loadLab(file,&laby);


    fclose(file);
    return 0;
}