#include <stdio.h>
#include <stdlib.h>
#include "ppmIO.h"
#include "graphicsSpace.h"

main(int argc, char *argv[]) {
  char name[256];
  int i;

  //create an instance of the graphicsSpace class
  GraphicsSpace space2("space2.ppm");

  //create an image background plane for space 2
  space2.createImage(400,600);
  //set a background color for space 2
  space2.setBackground(255,0,0);
  for (i=0;i<100;i++)
    space2.addPoint(i,i,0,255,255,255);
  for (i=0;i<100;i++)
    space2.addPoint(i,100-i,2,0,0,0);
  space2.lookDown();

  //write out the image plane from image space 1 and 2
  space2.writeImage();

}
