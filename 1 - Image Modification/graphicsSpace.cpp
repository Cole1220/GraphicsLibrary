#include "graphicsSpace.h"

//constructor for graphics environment
GraphicsSpace::GraphicsSpace(char const *filename)
{
  sprintf(name, "%s", filename);
}

//rename the environment
void GraphicsSpace::rename(char const *nameIn)
{
  sprintf(name, "%s", nameIn);
}

//load an image as a background image
void GraphicsSpace::loadBackground(char const *filename)
{
  im = readPPM(&height, &width, &colors, filename);//read the image
}

//create an image output plain
void GraphicsSpace::createImage(int widthIn, int heightIn)
{
  width = widthIn;
  height = heightIn;
  colors = 255;
  im = new Pixel[width * height];
}

//write the image plane
void GraphicsSpace::writeImage()
{
  writePPM(im, height, width, colors, name);
}

//set a background color for the image plane
void GraphicsSpace::setBackground(int red, int green, int blue)
{
  Pixel color;

  color.r = red;
  color.g = green;
  color.b = blue;
  setBackground(color);
}

//set a background color for the image plane
void GraphicsSpace::setBackground(Pixel color)
{
  int i, j;

  for (i = 0; i < width; i++)
  {
    for (j = 0; j < height; j++)
    {
      im[i + j * width] = color;
    }
  }
}

//sample method for coloring the background
void GraphicsSpace::colorBackground()
{
  int i, j;

  for (i = 0; i < width; i++)
  {
    for (j = 0; j < height; j++)
    {
      im[j * width + i].r = (i * j) % 255;
      im[j * width + i].g = ((i + 128) * (j + 128)) % 255;
      im[j * width + i].b = 0;
    }
  }
}

//swap the red and blue color channels of the background image
void GraphicsSpace::swapBackgroundColors()
{
  int i, j, temp;

  for (i = 0; i < width; i++)
  {
    for (j = 0; j < height; j++)
    {
      temp = im[j * width + i].r;
      im[j * width + i].r = im[j * width + i].b;
      im[j * width + i].b = temp;
    }
  }
}

void GraphicsSpace::gradientImage(int divides)
{
  //Declare/Instatiate Variables
  int i, j, onQuad;
  float quad, numIncr, addToCol=0;
  bool red, blue = false;
  onQuad = 1;

  //Make sure param isn't 0
  if(divides < 1)
  {
      quad = 1;
  }
  else
  {
      //make param the right amount of quadrants
      divides = divides - 1;
      quad = (width/divides)-1;
  }
  
  //Divide 255 by width of block size
  //for adding color dependent on img size
  numIncr = 255/quad;
  addToCol = 0;

  //while needing to fulfill amount of quadrants
  while(onQuad <= divides)
  {
      //Changing from start or green to red
      if(red == false) 
      {
	  for(i = (quad * (onQuad - 1)); i < (quad * onQuad); i++)
	  {
	      for(j = 0; j < height; j++)
	      {
		  im[j * width + i].r = floor(addToCol);
		  if(im[j * width + i].g > 0)
		  {
		      im[j * width + i].g = (255 - floor(addToCol));
		  } 
	      }
	      addToCol = addToCol + numIncr;
	  }
	  //set params for next run through
	  red = true;
	  onQuad = onQuad + 1;
	  addToCol = 0;
      }
      //Changing from red to blue
      else if(red == true && blue == false)
      {
	  for(i = (quad * (onQuad - 1)); i < (quad * onQuad); i++)
	  {
	      for(j = 0; j < height; j++)
	      {
		  im[j * width + i].b = floor(addToCol);
		  im[j * width + i].r = (255 - floor(addToCol));
	      }
	      addToCol = addToCol + numIncr;
	  }
	  //set params for next run through
	  blue = true;
	  onQuad = onQuad + 1;
	  addToCol = 0;
      }
      //Changing blue to green
      else if(blue == true)
      {
	  for(i = (quad * (onQuad - 1)); i < (quad * onQuad); i++)
	  {
	      for(j = 0; j < height; j++)
	      {
		  im[j * width + i].g = floor(addToCol);
		  im[j * width + i].b = (255 - floor(addToCol));
	      }
	      addToCol = addToCol + numIncr;
	  }
	  //set params for next run through
	  red = false;
	  blue = false;
	  onQuad = onQuad + 1;
	  addToCol = 0;
      }
   }
}


