/*
  This program is imported from:
  https://gist.github.com/andrejbauer/7919569
  This program is an adaptation of the Mandelbrot program
  from the Programming Rosetta Stone, see
  http://rosettacode.org/wiki/Mandelbrot_set
  See http://www.imagemagick.org/Usage/color_mods/ for what ImageMagick
  can do. It can do a lot.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include <omp.h>

int main(int argc, char* argv[])
{
  const char* filename;
    uint16_t maxiter;
    int xres;
    double workspace[4];
    /* Parse the command line arguments. */
    if (argc == 2) {
        /* The output file name */
        filename = argv[1];
        /* Maximum number of iterations, at most 65535. */
        maxiter = 1000;
        xres = 1000;
        workspace[0] = -2;
        workspace[1] = 1;
        workspace[2] = -1.5;
        workspace[3] = 1.5;
    }
    else if (argc == 4){
        /* The output file name */
        filename = argv[1];
        /* Maximum number of iterations, at most 65535.*/
        maxiter = atoi(argv[2]);
        xres = atoi(argv[3]);
        workspace[0] = -2;
        workspace[1] = 1;
        workspace[2] = -1.5;
        workspace[3] = 1.5;
    }
    else if (argc == 8) {
        /* The output file name */
        filename = argv[1];
        /* Maximum number of iterations, at most 65535.*/
        maxiter = atoi(argv[2]);
        xres = atoi(argv[3]);
        workspace[0] = atof(argv[4]);
        workspace[1] = atof(argv[5]);
        workspace[2] = atof(argv[6]);
        workspace[3] = atof(argv[7]);
    }
    else{
        printf("Usage:   %s <out.ppm>\n", argv[0]);
        printf("Example: %s pic.ppm\n", argv[0]);
        return -1;
    }

    /* The window in the plane. */
    const double xmin = workspace[0];
    const double xmax = workspace[1];
    const double ymin = workspace[2];
    const double ymax = workspace[3];

    /* Image size, width is given, height is computed. */
    const int yres = xres;

  /* Open the file and write the header. */
  FILE * fp = fopen(filename, "wb");
//char *comment="# Mandelbrot set";/* comment should start with # */

  /*write ASCII header to the file*/
  fprintf(fp,
          "P6\n# Mandelbrot, xmin=%lf, xmax=%lf, ymin=%lf, ymax=%lf, maxiter=%d\n%d\n%d\n%d\n",
          xmin, xmax, ymin, ymax, maxiter, xres, yres, (maxiter < 256 ? 256 : maxiter));

  /* Precompute pixel width and height. */
  double dx=(xmax-xmin)/xres;
  double dy=(ymax-ymin)/yres;

  double x, y; /* Coordinates of the current point in the complex plane. */
//double u, v; /* Coordinates of the iterated point. */
  int i,j; /* Pixel counters */
  int k; /* Iteration counter */
  int result[yres][xres];
  int c = 0;
  double itime, ftime, exec_time;
  itime = omp_get_wtime();

  #pragma omp parallel for shared(result,ymax, dy, dx, xmin) private(i, j, k, x, y) schedule(dynamic)
  for (j = 0; j < yres; j++) {
    y = ymax - j * dy;
    for(i = 0; i < xres; i++) {
      double u = 0.0;
      double v = 0.0;
      double u2 = u * u;
      double v2 = v * v;
      x = xmin + i * dx;
      /* iterate the point */
      for (k = 1; k < maxiter && (u2 + v2 < 4.0); k++) {
            v = 2 * u * v + y;
            u = u2 - v2 + x;
            u2 = u * u;
            v2 = v * v;
      };
      /* compute  pixel color and write it to file */
      if (k >= maxiter) {
        result[j][i] = -1;
      }
      else {
        result[j][i] = k;
      };
    }
  }

    ftime = omp_get_wtime();
    exec_time = ftime - itime;
    printf("\n\nParallel Time is %f\n", exec_time);
    
    /* exterior */
    unsigned char black[] = {0, 0, 0, 0, 0, 0};
    for(j = 0; j<yres; j++){
      for(i = 0; i<xres; i++){
        if (result[j][i] == -1) fwrite(black, 6, 1, fp);
        else{
            int colorMultiplier = 65535 / maxiter;
            unsigned char color[6];

            int redVal = 65535-(colorMultiplier * result[j][i]);
            color[0] = redVal >> 8;
            color[1] = redVal & 255;

            int greenVal = (65535/2) - abs(colorMultiplier * result[j][i] / 2);
            color[2] = greenVal >> 8;
            color[3] = greenVal & 255;

            int blueVal = (colorMultiplier * result[j][i]);
            color[4] = blueVal >> 8;
            color[5] = blueVal & 255;

            fwrite(color, 6, 1, fp);
        } 
      }
    }
  fclose(fp);
  return 0;
}