#include <stdio.h>
#include <stdlib.h>
#include "ppmIO.h"
#include "graphicsSpace.h"

main(int argc, char *argv[]) {
  char name[256];
  int i,cx,cy,cz,x,y,z,squareSize,maxCZ;
  
  GraphicsSpace space1("planeTest.ppm");
  space1.createImage(301,301);
  space1.setBackground(0,0,0);
  //planes
  //floor
  space1.addPlane(0,100,0, 0,1,0, 0,100,100);
  //ceiling
  //space1.addPlane(0,-100,0, 0,1,0, 200,200,200);
  //left wall
  space1.addPlane(-200,0,0, 1,0,0, 150,150,150);
  //right wall
  //space1.addPlane(200,0,0, 1,0,0, 150,150,150);
  
  /*
  //legs
  for (x=0;x<10;x++)
    for (z=1;z<10;z++){
      space1.addLine(-50+x,100,z, -50+x,0,z, 200,0,0);
      space1.addLine(-50+x,100,100-z, -50+x,0,100-z, 200,0,0);
      space1.addLine(50-x,100,z, 50-x,0,z, 200,0,0);
      space1.addLine(50-x,100,100-z, 50-x,0,100-z, 200,0,0);
    }
  //leg fronts
  for (x=0;x<10;x++){
    space1.addLine(-50+x,100,0, -50+x,0,0, 255,0,0);
    space1.addLine(-50+x,100,100, -50+x,0,100, 255,0,0);
    space1.addLine(50-x,100,0, 50-x,0,0, 255,0,0);
    space1.addLine(50-x,100,100, 50-x,0,100, 255,0,0);
    
    space1.addLine(-50+x,100,10, -50+x,0,10, 255,0,0);
    space1.addLine(-50+x,100,90, -50+x,0,90, 255,0,0);
    space1.addLine(50-x,100,10, 50-x,0,10, 255,0,0);
    space1.addLine(50-x,100,90, 50-x,0,90, 255,0,0);
  }
  //table
  for (x=-50;x<=50;x++)
    for (y=0;y<10;y++){
      space1.addLine(x,-y,1, x,-y,99, 200,100,0);
    }

  for (y=0;y<10;y++){
    space1.addLine(-50,-y,0, 50,-y,0, 255,50,0);
    space1.addLine(-50,-y,100, 50,-y,100, 255,50,0);
  }  
  */
  //camera stuff
  space1.setCamera(0,40,-50);
  space1.setViewPlaneCenter(0,40,0);
  space1.setViewPlaneNormal(1,1,1);//not important right now
  //render image
  space1.render();
  space1.writeImage();

  //image 2
  //space1.rename("planeTest2.ppm");
  //space1.setCamera(0,-40,-75);
  //space1.setViewPlaneCenter(0,-40,0);
  //space1.render();
  //space1.writeImage();
  
  //*
  GraphicsSpace space2("sphereTest1.ppm");
  space2.createImage(301,301);
  space2.setBackground(255,0,0);

  for (cz=0;cz<10;cz+=2){
    space2.addSphere(50,50,cz*100, 50, 0,255-cz*10,0);
    space2.addSphere(50,301-50,cz*100, 50, 0,255-cz*10,0);
    space2.addSphere(301-50,50,cz*100, 50, 0,255-cz*10,0);
    space2.addSphere(301-50,301-50,cz*100, 50, 0,255-cz*10,0);
  }

  space2.lookDown();
  space2.writeImage();

  space2.setBackground(255,0,0);
  space2.rename("sphereTest2.ppm");
  space2.setCamera(151,151,-300);
  space2.setViewPlaneCenter(151,151,0);
  space2.setViewPlaneNormal(1,1,1);//not important right now
  //render image
  space2.render();
  space2.writeImage();
  //*/
}
