#include "graphicsSpace.h"

static const double THRESHOLD = 0.5;

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

Vector::Vector(Vector *refVec)
{
  x = refVec->x;
  y = refVec->y;
  z = refVec->z;
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

void Vector::copy(Vector *copyVec)
{
	setVector(copyVec->x, copyVec->y, copyVec->z);
}

void Vector::add(Vector *addVec)
{
  x += addVec->x;
  y += addVec->y;
  z += addVec->z;
}

void Vector::subtract(Vector *subVec)
{
  x -= subVec->x;
  y -= subVec->y;
  z -= subVec->z;
}

double Vector::dotProduct(Vector *prodVec)
{
  //a.b = a1*b1 + a2*b2 + a3*b3
  return ((x * prodVec->x) + (y * prodVec->y) + (z * prodVec->z));
}

void Vector::multiply(double mult)
{
  x *= mult;
  y *= mult;
  z *= mult;
}

void Vector::unitize()
{
  //Pythag
  double w = sqrt((x*x)+(y*y)+(z*z));
  //Make mult for eff
  w = 1.0/w;
  x *= w;
  y *= w;
  z *= w;
}

double Vector::length(Vector *start)
{
  return sqrt((x * start->x) + (y * start->y) + (z * start->z));
}

//wihtout start
double Vector::length()
{
  return sqrt((x * x)+(y * y)+(z * z));
}

void Vector::printVector()
{
  printf("X: %f, Y: %f, Z: %f \n", x, y, z);
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

Intersect::~Intersect()
{
  //Nothing
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
  if (((in->intersect) && (!intersect)) || (in->depth < depth))
  {
    copy(in);
  }
}

void Intersect::rayTraceBest(Intersect *in)
{
  if (((in->intersect) && (!intersect)) || ((in->intersect) && (in->depth < depth)))
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

void Point::rayTrace(Ray *in, Intersect *output)
{
  //CP-(uD * CP.dotProd(uD))
  CP = new Vector(in->start);
  D = new Vector(in->direction);
  D->unitize();
  
  double dP = CP->dotProduct(D);
  D->multiply(dP);
  CP->subtract(D);
  
  if(CP->length() <= THRESHOLD)
  {
    output->reIntersect(color, CP->z, true);
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
    P1 = new Vector((double)xLoc1, (double)yLoc1, (double)zLoc1);
	P2 = new Vector((double)xLoc2, (double)yLoc2, (double)zLoc2);
  }
  else
  {
	P2 = new Vector((double)xLoc1, (double)yLoc1, (double)zLoc1);
	P1 = new Vector((double)xLoc2, (double)yLoc2, (double)zLoc2);  
  }
  
  color = colorIn;
}

Line::~Line()
{
	//DO NOTHING
}

void Line::lookDown(int xLoc, int yLoc, Intersect *output)
{
  double difX = P2->x - P1->x;
  double difY = P2->y - P1->y;
	
  //if horizontal line
  if(difY == 0 && yLoc == P2->y)
  {
    if(xLoc >= P1->x && xLoc <= P2->x)
    {
      output->reIntersect(color, 0, true);
    }
    else
    {
      output->intersect = false;
    }
  }

  //if vertical line
  else if(difX == 0 && xLoc == P2->x)
  {
    if(yLoc >= min(P1->y, P2->y) && yLoc <= max(P1->y, P2->y))
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
  else if (xLoc >= min(P1->x, P2->x) && xLoc <= max(P1->x, P2->x) 
	       && yLoc >= min(P1->y, P2->y) && yLoc <= max(P1->y, P2->y))
  {
	double slope = difY / difX;
	
	//Solve for b in (y = mx + b)
	double yDif = yLoc - (slope * xLoc);
	
	//Solve for y with (y = mx + b) with x being P1->x
	yDif = (slope * P1->x) + yDif;
	
	//Get difference between actual and current (thresh of .5)
	yDif = fabs(P1->y - yDif);
	
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

void Line::rayTrace(Ray *in, Intersect *output)
{
	V = new Vector(P2->x, P2->y, P2->z);
	V->subtract(P1);
	
	W = new Vector(in->start);
	W->subtract(P1);
	
	D = new Vector(in->direction);
	D->unitize();
	
	Vt = new Vector(0, -V->z, V->y);
	Dt = new Vector(0, -in->direction->z, in->direction->y);
	Dt->unitize();
	
	//If bottoms are 0 new plane
	if(Vt->dotProduct(D) == 0 || Dt->dotProduct(V) == 0)
	{
		Vt->setVector(-V->z, 0, V->x);
		Dt->setVector(-in->direction->z, 0, in->direction->x);
		Dt->unitize();
		
		if(Vt->dotProduct(D) == 0 || Dt->dotProduct(V) == 0)
		{
			Vt->setVector(-V->y, V->x, 0);
			Dt->setVector(-in->direction->y, in->direction->x, 0);
			Dt->unitize();
			
			if(Vt->dotProduct(D) == 0 || Dt->dotProduct(V) == 0)
			{
				output->intersect = false;
				return;
			}
		}
	}
	
	double s, t;
	s = -(Vt->dotProduct(W)/Vt->dotProduct(D));
	t = Dt->dotProduct(W)/Dt->dotProduct(V);
	
	if(t >= 0 && t <= 1)
	{
		Pt = new Vector(V);
		Pt->multiply(t);
		Pt->add(P1);
		
		Rs = new Vector(D);
		Rs->multiply(t);
		Rs->add(in->start);
		
		if(Pt->length(Rs) <= THRESHOLD)
		{
			output->reIntersect(color, s, true);
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
  C = new Vector((double)xLoc, (double)yLoc, (double)zLoc);
  radius = radiusIn;
  color = colorIn;
}

Sphere::~Sphere()
{
	//DO NOTHING
}

void Sphere::printSphere()
{
	printf("\n");
	printf("\n");
	C->printVector();
	printf("Radius: %f \n", radius);
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

void Sphere::rayTrace(Ray *in, Intersect *output)
{
	D = new Vector(in->direction);
	D->unitize();
	
	double a = D->dotProduct(D);
	
	temp = new Vector(in->start);
	temp->subtract(C);
	
	D->multiply(2);
	double b = D->dotProduct(temp);
	
	double c = temp->dotProduct(temp) - (radius * radius);
	
	//Only intersect if b^2 - 4ac >= 0
	double intersectCheck = (b * b) - (4 * a * c);
	
	if(intersectCheck >= 0 && 2 * a != 0)
	{
		double twoA = 1 / (2 * a);
		
		double s = (-b + sqrt(intersectCheck)) * twoA; 
		double s2 = (-b - sqrt(intersectCheck)) * twoA;
		
		s = (s <= s2) ? s : s2;
		
		output->reIntersect(color, s, true);
	}
	else
	{
		output->intersect = false;
	}
}

///////////////////////////////////////////////////////////////////////
//PLANE
///////////////////////////////////////////////////////////////////////
Plane::Plane()
{
  normal = new Vector(0,0,0);
  intersect = new Vector(0,0,0);
  k = 0;
  
  color.r = 0;
  color.g = 0;
  color.b = 0;
}

Plane::Plane(double x, double y, double z, double dX, double dY, double dZ, Pixel colorIn)
{
  normal = new Vector(x, y, z);
  intersect = new Vector(dX, dY, dZ);
  k = intersect->dotProduct(normal);
  
  color = colorIn;
}

Plane::~Plane()
{
	//DO NOTHING
}

void Plane::printPlane()
{
	printf("\n");
	printf("\n");
	normal->printVector();
	intersect->printVector();
	printf("\n");
}

void Plane::setNormal(double xIn,double yIn,double zIn)
{
  normal->setVector(xIn, yIn, zIn);
}

void Plane::setIntersect(double xIn,double yIn,double zIn)
{
  intersect->setVector(xIn, yIn, zIn);
}

void Plane::lookDown(int xLoc,int yLoc,Intersect *output)
{
  double zLoc = (k - normal->x * xLoc + normal->y * yLoc) / normal->z;
  if(zLoc == 0)
  {
    output->intersect=false;
  }
  else
  {
    output->reIntersect(color, zLoc, true);
  }
}

//TODO: Need to find out why either this or Ray doesnt work right for planes only
void Plane::rayTrace(Ray *in, Intersect *output)
{
	D = new Vector(in->direction);
    D->unitize();
	
    N = new Vector(normal);
    N->unitize();

    W = new Vector(in->start);
    W->subtract(intersect);

	output->intersect = false;
	
    if((N->dotProduct(D) != 0 && W->dotProduct(N) != 0)){
        double s = -(W->dotProduct(N)/D->dotProduct(N));

       if(s>=0){

            
            output->reIntersect(color, s, true);
       }
    }
}

///////////////////////////////////////////////////////////////////////
//RAY
///////////////////////////////////////////////////////////////////////
Ray::Ray()
{
  start = new Vector(0, 0, 0);
  direction = new Vector(0, 0, 0);
}

Ray::Ray(Vector *startIn, Vector *direct)
{
  start = new Vector(startIn);
  direction = new Vector(direct);
}

Ray::~Ray()
{
  //delete mem here
}

void Ray::setRayStart(int x, int y, int z)
{
	start->setVector(x, y, z);
}

void Ray::setRayStart(Vector *startIn)
{
	start->copy(startIn);
}

void Ray::setDirection(Vector *direct)
{
	direction->copy(direct);
}

void Ray::setRay(Vector *startIn, Vector *direct)
{
	start->copy(startIn);
	direction->copy(direct);
}

Pixel Ray::getColor()
{
	return color;
}

void Ray::setColor(Pixel colorIn)
{
	color = colorIn;
}

void Ray::printRay()
{
	printf("Start: (X: %d, Y: %d, Z: %d), Direction: (X: %d, Y: %d, Z: %d)", start->x, start->y, start->z, direction->x, direction->y, direction->z);
}

///////////////////////////////////////////////////////////////////////
//RAYCREATOR
///////////////////////////////////////////////////////////////////////
RayCreator::RayCreator()
{
  width = 0;
  height = 0;
  
  camera = new Vector(0, 0, 0);
  viewPlane = new Plane();
  
  sizeV = false;
  cam = false;
  planeC = false;
  planeN = false;
  tempLoc = false;
}

RayCreator::~RayCreator()
{
  //DO NOTHING
}

void RayCreator::setCamera(double x, double y, double z)
{
	camera->setVector(x, y, z);
	cam = true;
}

void RayCreator::setViewPlaneCenter(double x, double y, double z)
{
	viewPlane->setIntersect(x, y, z);
	planeC = true;
}

void RayCreator::setViewPlaneNormal(double x, double y, double z)
{
	viewPlane->setNormal(x, y, z);
	planeN = true;
}

void RayCreator::setViewPlaneSize(int widthIn, int heightIn)
{
	width = widthIn;
	height = heightIn;
	
	//set center image as origin
	cpX = ((double)width - 1) * 0.5;
	cpY = ((double)height - 1) * 0.5;
}

bool RayCreator::ready()
{
	return cam && planeC && planeN;
}

void RayCreator::printRayCreator()
{
  printf("Width: %f, Height: %f \n", width, height);
  printf("cpX: %f, cpY: %f \n", cpX, cpY);

  if(cam)
  {
	printf("Camera: ");
	camera->printVector();
  }
  if(viewPlane != NULL)
  {
    if(planeC)
    {
	  printf("intersect: ");
	  viewPlane->intersect->printVector();
    }
    if(planeN)
    {
	  printf("normal: ");
	  viewPlane->normal->printVector();
    }		
  }
}

void RayCreator::createRay(int xLoc,int yLoc,Ray *outRay)
{
	outRay->start->copy(camera);
	
	outRay->direction->setVector(xLoc - cpX, yLoc - cpY, 0);
	outRay->direction->subtract(camera);
	outRay->direction->add(viewPlane->intersect);
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
  
  viewPlane = new RayCreator();
  viewPlane->setViewPlaneSize(widthIn, heightIn);
  
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
  temp.printSphere();

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

void GraphicsSpace::addPlane(int x, int y, int z, double dX, double dY, double dZ, Pixel colorIn)
{
	Plane temp(x, y, z, dX, dY, dZ, colorIn);
	temp.printPlane();
	
	planes.push_back(temp);
}

void GraphicsSpace::addPlane(int x, int y, int z, double dX, double dY, double dZ, int red, int green, int blue)
{
	Pixel color;
	
	color.r = red;
	color.g = green;
	color.b = blue;
	addPlane(x, y, z, dX, dY, dZ, color);
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
	  
	  //planes
	  for (i = 0; i < planes.size(); i++)
      {
	    planes[i].lookDown(x, y, &test);
	    best.lookDownBest(&test);
      }
	  if (best.intersect)
	  {
	    im[x + y * width] = best.color;
	  }
    }
  }
}

void GraphicsSpace::setCamera(int x, int y, int z)
{
	viewPlane->setCamera(x, y, z);
}

void GraphicsSpace::setViewPlaneCenter(int x, int y, int z)
{
	viewPlane->setViewPlaneCenter(x, y, z);
}

void GraphicsSpace::setViewPlaneNormal(double x, double y, double z)
{
	viewPlane->setViewPlaneNormal(x, y, z);
}

void GraphicsSpace::render()
{
  Pixel temp;
  int i, x, y;
  Ray *curRay;

  if(viewPlane->ready())
  {
    //initialize RayCreator viewPlane
    viewPlane->printRayCreator();
    curRay = new Ray();
    //set inital variables
    temp.r = 0;
    temp.g = 0;
    temp.b = 0;
	
    Intersect best(temp, 0, false);
    Intersect test(temp, 0, false);

    //set time
    Timer check;

    printf("\n");
    for (y = 0; y < height; y++)
	{
      if ((y % 10 == 0) && (y != 0))
	  {
        check.printTime(y,height);
	  }
      for (x = 0; x < width; x++)
	  {
        best.reIntersect(temp, 0, false);
        viewPlane->createRay(x, y, curRay);
        //curRay->printRay();
		
        //points
        for (i = 0; i < points.size(); i++)
		{
          points[i].rayTrace(curRay, &test);
          best.rayTraceBest(&test);
        }
		
		//lines
        for (i = 0; i < lines.size(); i++)
		{
          lines[i].rayTrace(curRay, &test);
          best.rayTraceBest(&test);
        }
		
		//sphere
        for (i = 0; i < spheres.size(); i++)
		{
          spheres[i].rayTrace(curRay, &test);
          best.rayTraceBest(&test);
        }
		
		//planes
        for (i = 0; i < planes.size(); i++)
		{
          planes[i].rayTrace(curRay, &test);
          best.rayTraceBest(&test);
        }
		
        if (best.intersect)
		{
          im[x + y * width] = best.color;
        }
      }
    }
  }
}