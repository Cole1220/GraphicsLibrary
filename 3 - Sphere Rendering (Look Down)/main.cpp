#include <stdio.h>
#include <stdlib.h>
#include "ppmIO.h"
#include "graphicsSpace.h"

//this is a first attempt at a main function to load
//all files including image information

main(int argc, char *argv[]) {
  FILE *inFile;
  char line[1024];
  char inputs1[1024];

  if ((inFile=fopen(argv[1],"r"))==NULL)
    printf("couldn't read file\n");
  else {
    while (fgets(line,1024,inFile) != NULL){
      printf("%s",line);
      //if image create image
      printf("%d\n",scanf(line,"Image %s\n",inputs1));


    }
    fclose(inFile);
  }
}
