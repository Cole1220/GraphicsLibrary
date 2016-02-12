#include <stdio.h>
#include <stdlib.h>
#include "ppmIO.h"
#include "graphicsSpace.h"
//main 
main(int argc, char *argv[]) {
  char name[256];

  printf("Starting...Done\n");

  //create an instance of the graphicsSpace class
  GraphicsSpace space("space1.ppm");

  //Gradient Bgd
  printf("Space 1...");
  space.loadBackground(argv[1]);
  space.swapBackgroundColors();
  
  space.writeImage();
  printf("Done\n");

  //Solid Bgd
  printf("Space 2...");
  space.rename("space2.ppm");
  space.createImage(400,600);
  space.setBackground(255,0,0);
  
  space.writeImage();
  printf("Done\n");

  //Something Interesting
  printf("Space 3...");
  space.rename("space3.ppm");
  space.colorBackground();
  
  space.writeImage();
  printf("Done\n");

  printf("Space 4...");
  space.rename("space4.ppm");
  space.createImage(768, 400);
  space.setBackground(0,0,0);
  space.gradientImage(4);
  
  space.writeImage();
  printf("Done\n");
}
