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
#define BX 32
#define BY 32

// CUDA kernel. Each thread takes care of one element of c
__global__ void mandelbrot_kernel(double *result, double dx, double dy, double xmin, double ymax, int maxiter, int n){

    int tx = blockIdx.x * blockDim.x + threadIdx.x;
    int ty = blockIdx.y * blockDim.y + threadIdx.y;
    if ((tx < n) && (ty < n)){
        // printf(" blockz: %d, blocky: %d, blockx: %d, threadidz: %d, threadidy: %d, threadidx: %d.\n", blockIdx.z, blockIdx.y, blockIdx.x, threadIdx.z, threadIdx.y, threadIdx.x);    
        double y = ymax - ty * dy;
        double x = xmin + tx * dx;
        // printf("threadidy: %d, threadidx: %d, y: %f, x: %f.\n", threadIdx.y, threadIdx.x, y, x);

        double u = 0.0;
        double v = 0.0;
        double u2 = u * u;
        double v2 = v * v;

        int k;
        for (k = 1; k < maxiter && (u2 + v2 < 4.0); k++){
            v = 2 * u * v + y;
            u = u2 - v2 + x;
            u2 = u * u;
            v2 = v * v;
        };
        /* compute result */
        if (k >= maxiter) {
            result[ty * n + tx] = 0;
        }
        else {
            result[ty * n + tx] = 1;
            // printf("tx: %i, ty: %i at k: %i", tx, ty, k);
        };
        __syncthreads();
    }
}

int main(int argc, char* argv[])
{
    const char* filename;
    uint16_t maxiter;
    int xres;
    /* Parse the command line arguments. */
    if (argc == 2){
        /* The output file name */
        filename = argv[1];
        /* Maximum number of iterations, at most 65535. */
        maxiter = 1000;
        xres = 1000;
    }
    else if (argc == 4){
        /* The output file name */
        filename = argv[1];
        /* Maximum number of iterations, at most 65535. */
        maxiter = atoi(argv[2]);
        xres = atoi(argv[3]);
    }
    else{
        printf("Usage:   %s <out.ppm>\n", argv[0]);
        printf("Example: %s pic.ppm\n", argv[0]);
        return -1;
    }

    /* The window in the plane. */
    const double xmin = -2;
    const double xmax = 1;
    const double ymin = -1.5;
    const double ymax = 1.5;

    /* Image size, width is given, height is computed. */
    const int yres = xres;

    //Host output vector
    double *h_result;
    //Device output vector
    double *d_result;

    // Size, in bytes, of each vector
    size_t bytes = xres*yres*sizeof(double);

    // allocate memory
    h_result = (double*)malloc(bytes);
    cudaMalloc(&d_result, bytes);

    /* Precompute pixel width and height. */
    double dx=(xmax-xmin)/xres;
    double dy=(ymax-ymin)/yres;
 
    float time;
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, 0);

    dim3 block(BX,BY);
    dim3 grid((xres+block.x-1)/block.x, (yres+block.y-1)/block.y);
    // printf("blockx: %i, blocky: %i, gridx: %i, gridy: %i\n", block.x, block.y, grid.x, grid.y);


    // Execute the kernel
    mandelbrot_kernel <<<grid, block>>>(d_result, dx, dy, xmin, ymax, maxiter, xres);

    cudaMemcpy( h_result, d_result, bytes, cudaMemcpyDeviceToHost );

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&time, start, stop);
    printf("Elapsed time:  %3.3f ms \n", time);

    /* Open the file and write the header. */
    FILE * fp = fopen(filename, "wb");

    /*write ASCII header to the file*/
    fprintf(fp,
            "P6\n# Mandelbrot, xmin=%lf, xmax=%lf, ymin=%lf, ymax=%lf, maxiter=%d\n%d\n%d\n%d\n",
            xmin, xmax, ymin, ymax, maxiter, xres, yres, (maxiter < 256 ? 256 : maxiter));

    unsigned char color[] = {1,3,3,5,3,3};
    const unsigned char black[] = {0, 0, 0, 0, 0, 0};
    for (int c = 0; c < yres*xres; c++){
        if (h_result[c] == 0) fwrite(black, 6, 1, fp);
        else fwrite(color, 6, 1, fp);
    }
    fclose(fp);
    return 0;
}
