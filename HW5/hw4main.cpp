#include <stdio.h>
#include <stdlib.h>
#include "ppmIO.h"
#include "graphicsSpace.h"

main(int argc, char *argv[]) {
  char name[256];
  int i;

  GraphicsSpace space1("planeTest.ppm");
  space1.createImage(4,4);
  space1.addPlane(0,0,-5, 1,1,1, 255,0,0);
  space1.lookDown();

  space1.writeImage();
}
