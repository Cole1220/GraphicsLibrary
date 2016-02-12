#include <stdio.h>
#include <stdlib.h>
#include "ppmIO.h"
#include "graphicsSpace.h"

main(int argc, char *argv[]) {
  char name[256];
  int i, j;

  //create an instance of the graphicsSpace class for point example
  GraphicsSpace spacePoint("pointTest.ppm");

  //create an image plane for spacePoint
  spacePoint.createImage(400,400);

  //set a black background color for space spacePoint
  spacePoint.setBackground(0,0,0);

  //add a lot of points
  for (i = 0; i < 400; i++)
  {
    for(j = 0; j < 400; j++)
    {
      spacePoint.addPoint(i, j, 0, (i * j) % 256, (j * i * 2) % 255, (j * i * 3) % 255);
    }
  }
  
  //put points into image plane
  spacePoint.lookDown();

  //write out the image plane from image space
  spacePoint.writeImage();
  
  /* Small test case - a lot of points takes a lot of time
  //create an instance of the graphicsSpace class for point example
  GraphicsSpace space2("pointTest.ppm");

  //create an image plane for space 2
  space2.createImage(400,400);
  //set a black background color for space 2
  space2.setBackground(0,0,0);
  //add lots of points
  // for (i=0;i<4;i++)//00;i++)
       // for(j=0;j<4;j++)//00;j++)
      space2.addPoint(i,j,0,(i*j)%256,(j*i*2)%255,(j*i*3)%255);
  //put points into image plane
  space2.lookDown();

  //write out the image plane from image space 2
  space2.writeImage();
  */
  
  //create an instance of the graphicsSpace class for line example
  GraphicsSpace spaceLine("lineTest.ppm");

  //create an image plane for spaceLine
  spaceLine.createImage(600,600);
  
  //set a black background color for spaceLine
  spaceLine.setBackground(0,0,0);
  
  for (i = 0; i < 512; i += 2)
  {
    spaceLine.addLine(0, i, i, i, 599, i, i / 2, 0, 0); // BOTTOM LEFT
    spaceLine.addLine(i, 599, i, 599, 599 - i, i, i / 2, 0, 0); // BOTTOM RIGHT
    spaceLine.addLine(599, 599 - i, i, 599 - i,0, i, i / 2, 0, 0);
    spaceLine.addLine(599 - i, 0, i, 0, i, i, i / 2, 0, 0);
  }
  
  //put points into image plane
  spaceLine.lookDown();

  //write out the image plane from image spaceLine
  spaceLine.writeImage();
}

