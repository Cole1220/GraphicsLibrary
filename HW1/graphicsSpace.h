#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include "ppmIO.h"

using namespace std;

class GraphicsSpace{
 public:
  int width;
  int height;
  int colors;
  int divides;
  
  char name[1024];//name of space (is used as name when writting image)    
  Pixel *im;  
  
  GraphicsSpace(char const *filename);
  void rename(char const *nameIn);
  void loadBackground(char const *filename);
  void createImage(int widthIn,int heightIn);
  void writeImage();
  void setBackground(int red,int green,int blue);
  void setBackground(Pixel color);
  void colorBackground();
  void swapBackgroundColors();
  void gradientImage(int divides);
};

