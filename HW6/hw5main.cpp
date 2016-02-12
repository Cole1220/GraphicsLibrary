#include <stdio.h>
#include <stdlib.h>
#include "ppmIO.h"
#include "graphicsSpace.h"

main(int argc, char *argv[]) {
  char name[256];
  int i, cx, cy, cz, x, y, squareSize;
  
  GraphicsSpace spacePoint("rayTest1.ppm");
  spacePoint.createImage(301, 301);
  spacePoint.setBackground(0, 0, 0);
  //create stuff to look at
  squareSize = 100;
  
  /*
  for (cz = 0; cz < 80; cz += 3)
  {
    cx = -95;
    cy = -95;
    for (x = cx - squareSize / 2; x <= cx + squareSize / 2; x += 4)
	{
      for (y = cy - squareSize / 2; y <= cy + squareSize / 2; y += 4)
	  {
		spacePoint.addPoint(x, y, cz, 255 - (4 * cz), 0, 0);
	  }
	}
	
	
    cx=95;
    cy=95;
    for (x=cx-squareSize/2;x<=cx+squareSize/2;x+=4)
      for (y=cy-squareSize/2;y<=cy+squareSize/2;y+=4)
	spacePoint.addPoint(x,y,cz, 255-4*cz,0,0);
    cx=-95;
    cy=95;
    for (x=cx-squareSize/2;x<=cx+squareSize/2;x+=4)
      for (y=cy-squareSize/2;y<=cy+squareSize/2;y+=4)
	spacePoint.addPoint(x,y,cz, 255-4*cz,0,0);
    cx=95;
    cy=-95;
    for (x=cx-squareSize/2;x<=cx+squareSize/2;x+=4)
      for (y=cy-squareSize/2;y<=cy+squareSize/2;y+=4)
      spacePoint.addPoint(x,y,cz, 255-4*cz,0,0);
  */
  //}
  spacePoint.addPoint(0,0,0, 255,0,0);

  //set camera stuff
  spacePoint.setCamera(0, 0, -5);
  spacePoint.setViewPlaneCenter(0,0,0);
  spacePoint.setViewPlaneNormal(1,1,1);//not important right now

  //render image
  spacePoint.render();
  spacePoint.writeImage();

  /*
  //second image
  GraphicsSpace space2("rayTest2.ppm");
  space2.createImage(301,201);
  space2.setBackground(0,0,0);
  //create stuff to look at
  squareSize=100;
  for (cz=0;cz<80;cz+=3){
    cx=-95;
    cy=0;
    for (x=cx-squareSize/2;x<=cx+squareSize/2;x+=2)
      for (y=cy-squareSize/2;y<=cy+squareSize/2;y+=2)
	space2.addPoint(x,y,cz, 255-4*cz,255-4*cz,255-4*cz);
    cx=95;
    cy=0;
    for (x=cx-squareSize/2;x<=cx+squareSize/2;x+=2)
      for (y=cy-squareSize/2;y<=cy+squareSize/2;y+=2)
	space2.addPoint(x,y,cz, 255-4*cz,255-4*cz,255-4*cz);
  }

  //set camera stuff
  space2.setCamera(0,0,-5);
  space2.setViewPlaneCenter(0,0,0);
  space2.setViewPlaneNormal(1,1,1);//not important right now

  //render image
  space2.render();
  space2.writeImage();

  //third image
  GraphicsSpace space3("rayTest3.ppm");
  space3.createImage(301,301);
  space3.setBackground(0,0,0);
  //create stuff to look at
  squareSize=35;
  for (cz=0;cz<20;cz+=1){
    cx=-145;
    cy=-145;
    for (x=0;x<squareSize;x++){
      space3.addPoint(cx+x,cy,cz, 0,255-10*cz,0);
      space3.addPoint(cx,cy+x,cz, 0,255-10*cz,0);
    }
    cx=145;
    cy=145;
    for (x=0;x<squareSize;x++){
      space3.addPoint(cx-x,cy,cz, 0,255-10*cz,0);
      space3.addPoint(cx,cy-x,cz, 0,255-10*cz,0);
    }
    cx=145;
    cy=-145;
    for (x=0;x<squareSize;x++){
      space3.addPoint(cx-x,cy,cz, 0,255-10*cz,0);
      space3.addPoint(cx,cy+x,cz, 0,255-10*cz,0);
    }
    cx=-145;
    cy=145;
    for (x=0;x<squareSize;x++){
      space3.addPoint(cx+x,cy,cz, 0,255-10*cz,0);
      space3.addPoint(cx,cy-x,cz, 0,255-10*cz,0);
    }
  }
  //set camera stuff
  space3.setCamera(0,0,-20);
  space3.setViewPlaneCenter(0,0,0);
  space3.setViewPlaneNormal(1,1,1);//not important right now

  //render image
  space3.render();
  space3.writeImage();
  */
}