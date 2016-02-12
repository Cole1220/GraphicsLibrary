#include "graphicsSpace.h"

//constructor for Timer
Timer::Timer()
{
  time(&startTime);
}

//destructor for Timer
Timer::~Timer(){}

//getTimingInfo creates a string that contains all run time information
void Timer::printTime(int row, int end)
{
  int currentTime, totalTime, timeLeft;
  int ch, cm, cs, th, tm, ts, lh, lm, ls;

  time(&cTime);
  currentTime = cTime - startTime;
  totalTime = end * currentTime / row;
  timeLeft = totalTime - currentTime;

  //set hours
  ch = currentTime / 3600;
  th = totalTime / 3600;
  lh = timeLeft / 3600;

  currentTime %= 3600;
  totalTime %= 3600;
  timeLeft %= 3600;

  //set minutes
  cm = currentTime / 60;
  tm = totalTime / 60;
  lm = timeLeft / 60;

  currentTime %= 60;
  totalTime %= 60;
  timeLeft %= 60;

  //set seconds
  cs = currentTime;
  ts = totalTime;
  ls = timeLeft;

  printf("%d/%d current: %d:%02d.%02d total: %d:%02d.%02d left: %d:%02d.%02d\n", row, end, ch, cm, cs, th, tm, ts, lh, lm, ls);
}

///////////////////////////////////////////////////////////////////////
//VECTOR
///////////////////////////////////////////////////////////////////////
Vector::Vector(double xD, double yD, double zD)
{
  x = xD;
  y = yD;
  z = zD;
}

Vector::~Vector()
{
	//Do nothing here
}

void Vector::setVector(double xD, double yD, double zD)
{
  x = xD;
  y = yD;
  z = zD;
}

///////////////////////////////////////////////////////////////////////
//INTERSECT
///////////////////////////////////////////////////////////////////////
Intersect::Intersect(Pixel colorIn, double depthIn, bool intersectIn)
{
  color = colorIn;
  depth = depthIn;
  intersect = intersectIn;
}

void Intersect::reIntersect(Pixel colorIn, double depthIn, bool intersectIn)
{
  color = colorIn;
  depth = depthIn;
  intersect = intersectIn;
}

void Intersect::copy(Intersect *in)
{
  color = in->color;
  depth = in->depth;
  intersect = in->intersect;
}

void Intersect::lookDownBest(Intersect *in)
{
  if (((in->intersect) && (!intersect)) || (in->depth > depth))
  {
    copy(in);
  }
}

///////////////////////////////////////////////////////////////////////
//POINT
///////////////////////////////////////////////////////////////////////
Point::Point(int xLoc, int yLoc, int zLoc, Pixel colorIn)
{
  P = new Vector((double)xLoc, (double)yLoc, (double)zLoc);
  color = colorIn;
}

Point::~Point()
{
	//DO NOTHING
}

void Point::lookDown(int xLoc, int yLoc, Intersect *output)
{
  if ((P->x == xLoc) && (P->y == yLoc))
  {
    output->reIntersect(color, P->z, true);
  }
  else
  {
    output->intersect = false;
  }
}
///////////////////////////////////////////////////////////////////////
//LINE
///////////////////////////////////////////////////////////////////////
Line::Line(int xLoc1, int yLoc1, int zLoc1, int xLoc2, int yLoc2, int zLoc2, Pixel colorIn)
{
  if(xLoc1 < xLoc2)
  {
    L1 = new Vector((double)xLoc1, (double)yLoc1, (double)zLoc1);
	L2 = new Vector((double)xLoc2, (double)yLoc2, (double)zLoc2);
  }
  else
  {
	L2 = new Vector((double)xLoc1, (double)yLoc1, (double)zLoc1);
	L1 = new Vector((double)xLoc2, (double)yLoc2, (double)zLoc2);  
  }
  
  color = colorIn;
}

Line::~Line()
{
	//DO NOTHING
}

void Line::lookDown(int xLoc, int yLoc, Intersect *output)
{
  double difX = L2->x - L1->x;
  double difY = L2->y - L1->y;
	
  //if horizontal line
  if(difY == 0 && yLoc == L2->y)
  {
    if(xLoc >= L1->x && xLoc <= L2->x)
    {
      output->reIntersect(color, 0, true);
    }
    else
    {
      output->intersect = false;
    }
  }

  //if vertical line
  else if(difX == 0 && xLoc == L2->x)
  {
    if(yLoc >= min(L1->y, L2->y) && yLoc <= max(L1->y, L2->y))
    {
      output->reIntersect(color, 0, true);
      output->reIntersect(color, 0, true);
    }
    else
    {
      output->intersect = false;
    }
  }

  //check in limits of line to ween out more cases
  else if (xLoc >= min(L1->x, L2->x) && xLoc <= max(L1->x, L2->x) && yLoc >= min(L1->y, L2->y) && yLoc <= max(L1->y, L2->y))
  {
	double slope = difY / difX;
	
	//Solve for b in (y = mx + b)
	double yDif = yLoc - (slope * xLoc);
	
	//Solve for y with (y = mx + b) with x being L1->x
	yDif = (slope * L1->x) + yDif;
	
	//Get difference between actual and current (thresh of .5)
	yDif = fabs(L1->y - yDif);
	
	if(yDif < .5)
	{
	  output->reIntersect(color, 0, true);	
	}
	else
	{
	  output->intersect = false;
	}
  }

  else
  {
    output->intersect = false;
  }
}

///////////////////////////////////////////////////////////////////////
//SPHERE
///////////////////////////////////////////////////////////////////////
Sphere::Sphere(int xLoc, int yLoc, int zLoc, double radiusIn, Pixel colorIn)
{
  C = new Vector(xLoc, yLoc, zLoc);
  radius = radiusIn;
  color = colorIn;
}

Sphere::~Sphere()
{
	//DO NOTHING
}

void Sphere::lookDown(int xLoc, int yLoc, Intersect *output)
{
  int sphereThresh = 5;
  //r^2 = x^2 + y^2 + z^2 -> solve for Z -> z^2 = r^2 - (x^2 + y ^2)
  double xDif, yDif, zDif;
  xDif = (xLoc - C->x) * (xLoc - C->x);
  yDif = (yLoc - C->y) * (yLoc - C->y);
  zDif = (radius * radius) - (xDif + yDif);
	
  if(zDif <= sphereThresh)
  {
	output->intersect=false;  
  }
  else
  {
    double colorCoef = (1 - sqrt(zDif)) / radius;
		
    Pixel newColor;
    newColor.r = (255 - ((int)(colorCoef * color.r)));
    newColor.g = (255 - ((int)(colorCoef * color.g)));
    newColor.b = (255 - ((int)(colorCoef * color.b)));
		
    output->reIntersect(newColor, zDif, true);
  }
}

///////////////////////////////////////////////////////////////////////
//GRAPHICSSPACE
///////////////////////////////////////////////////////////////////////
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

void GraphicsSpace::addPoint(int xLoc, int yLoc, int zLoc, Pixel colorIn)
{
  Point temp(xLoc, yLoc, zLoc, colorIn);
  
  points.push_back(temp);
}

void GraphicsSpace::addPoint(int xLoc, int yLoc, int zLoc, int red, int green, int blue)
{
  Pixel color;
  
  color.r = red;
  color.g = green;
  color.b = blue;
  addPoint(xLoc, yLoc, zLoc, color);
}

void GraphicsSpace::addLine(int xLoc1, int yLoc1, int zLoc1, int xLoc2, int yLoc2, int zLoc2, Pixel colorIn)
{
  Line temp(xLoc1, yLoc1, zLoc1, xLoc2, yLoc2, zLoc2, colorIn);

  lines.push_back(temp);
}

void GraphicsSpace::addLine(int xLoc1, int yLoc1, int zLoc1, int xLoc2, int yLoc2, int zLoc2, int red, int green, int blue)
{
  Pixel color;
  
  color.r = red;
  color.g = green;
  color.b = blue;
  addLine(xLoc1, yLoc1, zLoc1, xLoc2, yLoc2, zLoc2, color);
}

void GraphicsSpace::addSphere(int xLoc, int yLoc, int zLoc, int radiusIn, Pixel colorIn)
{
  Sphere temp(xLoc, yLoc, zLoc, radiusIn, colorIn);

  spheres.push_back(temp);
}

void GraphicsSpace::addSphere(int xLoc, int yLoc, int zLoc, int radiusIn, int red, int green, int blue)
{
  Pixel color;

  color.r = red;
  color.g = green;
  color.b = blue;
  addSphere(xLoc, yLoc, zLoc, radiusIn, color);
}
void GraphicsSpace::lookDown()
{
  Pixel temp;
  int i, x, y;

  temp.r = 0;
  temp.g = 0;
  temp.b = 0;
  Intersect best(temp, 0, false);
  Intersect test(temp, 0, false);
  Timer check;
  
  printf("\n");
  
  for (y = 0; y < height; y++)
  {
	//Make sure we keep track of time
    if ((y % 10 == 0) && (y != 0))
    {
      check.printTime(y,height);
    }

    for (x = 0; x < width; x++)
    {
      best.reIntersect(temp, 0, false);
	  
      //points
      for (i = 0; i < points.size(); i++)
      {
	    points[i].lookDown(x, y, &test);
	    best.lookDownBest(&test);
      }
	  if (best.intersect)
	  {
	    im[x + y * width] = best.color;
	  }
	  
      //lines
      for (i = 0; i < lines.size(); i++)
      {
	    lines[i].lookDown(x, y, &test);
	    best.lookDownBest(&test);
      }
	  if (best.intersect)
	  {
	    im[x + y * width] = best.color;
	  }
	  
	  //sphere
	  for (i = 0; i < spheres.size(); i++)
      {
	    spheres[i].lookDown(x, y, &test);
	    best.lookDownBest(&test);
      }
	  if (best.intersect)
	  {
	    im[x + y * width] = best.color;
	  }
    }
  }
}
