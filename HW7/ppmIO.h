#ifndef PPMIO_H

#define PPMIO_H

#if defined(__cplusplus) || defined(c_plusplus) /* for C++ V2.0 */
extern "C" {
#endif

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} Pixel;


Pixel *readPPM(int *rows, int *cols, int * colors, char const *filename);
Pixel *readPPM2(int *rows, int *cols, int * colors, char const *filename,Pixel *image);
void writePPM(Pixel *image, int rows, int cols, int colors, char const *filename);

unsigned char *readPGM(int *rows, int *cols, int *intensities, char const *filename);
void writePGM(unsigned char *image, long rows, long cols, int intensities, char const *filename);

#if defined(__cplusplus) || defined(c_plusplus) /* for C++ V2.0 */
}
#endif

#endif
