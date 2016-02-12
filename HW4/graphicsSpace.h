#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include "ppmIO.h"

using namespace std;

class Timer
{
 public:
  time_t startTime, cTime;//start and current time of the process

  Timer();
  ~Timer();
  void printTime(int row, int end);
};

class Vector
{
 public:
  double x, y, z;
  
  Vector(double xD, double yD, double zD);
  Vector(Vector *refVec);
  ~Vector();
  void setVector(double xD, double yD, double zD);
  void copy(Vector *copyVec);
  void add(Vector *addVec);
  void subtract(Vector *subVec);
  double dotProduct(Vector *prodVec);
  void unitize();
  void printVector();
};

class Intersect
{
 public:
  Pixel color;
  double depth;
  bool intersect;

  Intersect(Pixel colorIn, double depthIn, bool intersectIn);
  void reIntersect(Pixel colorIn, double depthIn, bool intersectIn);
  void copy(Intersect *in);
  void lookDownBest(Intersect *in);
};

class Point
{
 public:
  Vector *P;
  Pixel color;

  Point(int xLoc, int yLoc, int zLoc, Pixel colorIn);
  ~Point();
  void lookDown(int xLoc, int yLoc, Intersect *output);
};

class Line
{
 public:
  Vector *L1;
  Vector *L2;
  Pixel color;

  Line(int xLoc1, int yLoc1, int zLoc1, int xLoc2, int yLoc2, int zLoc2, Pixel colorIn);
  ~Line();
  void lookDown(int xLoc, int yLoc, Intersect *output);
};

class Sphere
{
 public:
  Vector *C;
  double radius;
  Pixel color;
  
  Sphere(int xLoc, int yLoc, int zLoc, double radiusIn, Pixel colorIn);
  ~Sphere();
  void lookDown(int xLoc, int yLoc, Intersect *output);
};

class Plane
{
 public:
  Vector *normal;
  Vector *intersect;
  double k;
  Pixel color;
  
  Plane();
  Plane(double x, double y, double z, double dX, double dY, double dZ, Pixel colorIn);
  ~Plane();
  void setNormal(double xIn, double yIn, double zIn);
  void setIntersect(double xIn, double yIn, double zIn);
  void lookDown(int xLoc, int yLoc, Intersect *output);
};

class GraphicsSpace
{
 public:
  int width;
  int height;
  int colors;
  
  char name[1024];//name of space (is used as name when writting image)    
  Pixel *im;  

  vector<Point> points;
  vector<Line> lines;
  vector<Sphere> spheres;
  vector<Plane> planes;

  GraphicsSpace(char const *filename);
  void rename(char const *nameIn);
  void loadBackground(char const *filename);
  void createImage(int widthIn, int heightIn);
  void writeImage();
  void setBackground(int red, int green, int blue);
  void setBackground(Pixel color);
  void colorBackground();
  void swapBackgroundColors();
  //graphics elements
  void addPoint(int xLoc, int yLoc, int zLoc, Pixel colorIn);
  void addPoint(int xLoc, int yLoc, int zLoc, int red, int green, int blue);
  void addLine(int xLoc1, int yLoc1, int zLoc1, int xLoc2, int yLoc2, int zLoc2, Pixel color);
  void addLine(int xLoc1, int yLoc1, int zLoc1, int xLoc2, int yLoc2, int zLoc2, int red, int green, int blue);
  void addSphere(int xLoc, int yLoc, int zLoc, int radiusIn, Pixel colorIn);
  void addSphere(int xLoc, int yLoc, int zLoc, int radiusIn, int red, int green, int blue);
  void addPlane(int x, int y, int z, double dx, double dy, double dz, Pixel colorIn);
  void addPlane(int x, int y, int z, double dx, double dy, double dz, int red, int green, int blue);  
  
  void lookDown();
};

