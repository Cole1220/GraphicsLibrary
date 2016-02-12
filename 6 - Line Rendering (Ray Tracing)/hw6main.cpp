#include <stdio.h>
#include <stdlib.h>
#include "ppmIO.h"
#include "graphicsSpace.h"

main(int argc, char *argv[]) {
  char name[256];
  int i,cx,cy,cz,x,y,squareSize,maxCZ;
  
  GraphicsSpace space3("rayLine3.ppm");
  space3.createImage(301,301);
  space3.setBackground(0,0,0);
  //lines
  space3.addLine(-150,-150,0, 150,150,0, 255,0,0);
  space3.addLine(-150,0,0, 150,0,0, 0,255,0);
  space3.addLine(0,-150,0, 0,150,0, 0,0,255);
  space3.addLine(-150,150,0, 150,-150,0, 255,255,0);
  //camera stuff
  space3.setCamera(0,0,-5);
  space3.setViewPlaneCenter(0,0,0);
  space3.setViewPlaneNormal(1,1,1);//not important right now
  //render image
  space3.render();
  space3.writeImage();
  
  GraphicsSpace space1("rayLine1.ppm");
  space1.createImage(301,301);
  space1.setBackground(0,0,0);
  //create stuff to look at
  maxCZ=100;
  for (cz=0;cz<maxCZ;cz+=1){
    space1.addLine(-145,-145,cz, -145,145,cz, 255-(255*cz/maxCZ),0,0);
    space1.addLine(-145,-145,cz, 145,-145,cz, 255-(255*cz/maxCZ),0,0);
    space1.addLine(145,145,cz, -145,145,cz, 255-(255*cz/maxCZ),0,0);
    space1.addLine(145,145,cz, 145,-145,cz, 255-(255*cz/maxCZ),0,0);
  }

  //set camera stuff
  space1.setCamera(0,0,-50);
  space1.setViewPlaneCenter(0,0,0);
  space1.setViewPlaneNormal(1,1,1);//not important right now

  //render image
  space1.render();
  space1.writeImage();
  
  //second image
  GraphicsSpace space2("rayLine2.ppm");
  space2.createImage(600,600);
  //set a black background color for space 2
  space2.setBackground(0,0,0);
  for (i=0;i<512;i+=1){
    space2.addLine(-300,i-300,0, i-300,300,i, i/2,0,0);
    space2.addLine(i-300,300,0, 300,300-i,i, i/2,0,0);
    space2.addLine(300,300-i,0, 300-i,-300,i, i/2,0,0);
    space2.addLine(300-i,-300,0, -300,i-300,i, i/2,0,0);
  }

  //set camera stuff
  space2.setCamera(0,0,-5);
  space2.setViewPlaneCenter(0,0,0);
  space2.setViewPlaneNormal(1,1,1);//not important right now

  //render image
  space2.render();
  space2.writeImage();
}
