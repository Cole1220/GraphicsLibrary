#include <stdio.h>
#include <stdlib.h>
#include "ppmIO.h"
#include "graphicsSpace.h"

main(int argc, char *argv[]) {
  char name[256];
  int i;

  //create an instance of the graphicsSpace class
  GraphicsSpace spaceSphere("sphereTest.ppm");
  //create an image background plane for space 2
  spaceSphere.createImage(400, 600);
  //set a background color for space 2
  spaceSphere.setBackground(255, 0, 0);
  //create a large number of circles
  for (i = 1;i < 200; i++)
  {
    spaceSphere.addSphere(199, 299, 200 - 2 * i, i + 1, i, i, i);
  }
  //run look down to create the image
  spaceSphere.lookDown();
  //write out the image plane from image space 2
  spaceSphere.writeImage();
  
  //create space for the ellipse test
  GraphicsSpace spaceSphereTest("Test.ppm");
  //create an image background plane for space 3
  spaceSphereTest.createImage(600, 200);
  //set a black background color for space 3
  spaceSphereTest.setBackground(0, 0, 0);
  //create a single sphere
  spaceSphereTest.addSphere(199, 99, 0, 50, 255, 255, 255);
  //space1.addSphere(0,0,0, 50, 255,255,255);
  //run look down to create the image
  spaceSphereTest.lookDown();
  //write out the image plane from image space 1
  spaceSphereTest.writeImage();
}
