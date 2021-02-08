/********************************************************
 * Kernels to be optimized for the Metu Ceng Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/*
 * Please fill in the following team struct
 */
team_t team = {
    "",                     /* Team name */

    "İbrahim Özdemir",             /* First member full name */
    "",                 /* First member id */

    "Onat Özdemir",                         /* Second member full name (leave blank if none) */
    "",                         /* Second member id (leave blank if none) */

    "",                         /* Third member full name (leave blank if none) */
    ""                          /* Third member id (leave blank if none) */
};

/****************
 * BOKEH KERNEL *
 ****************/

/****************************************************************
 * Various typedefs and helper functions for the bokeh function
 * You may modify these any way you like.
 ****************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/*
 * initialize_pixel_sum - Initializes all fields of sum to 0
 */
static void initialize_pixel_sum(pixel_sum *sum)
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/*
 * accumulate_sum - Accumulates field values of p in corresponding
 * fields of sum
 */
static void accumulate_sum(pixel_sum *sum, pixel p)
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/*
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum)
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/*
 * avg - Returns averaged pixel value at (i,j)
 */
static pixel avg(int dim, int i, int j, pixel *src)
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++)
    for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++)
        accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/*******************************************************
 * Your different versions of the bokeh kernel go here
 *******************************************************/

/*
 * naive_bokeh - The naive baseline version of bokeh effect with filter
 */
char naive_bokeh_descr[] = "naive_bokeh: Naive baseline bokeh with filter";
void naive_bokeh(int dim, pixel *src, short *flt, pixel *dst) {

    int i, j;

    for(i = 0; i < dim; i++) {
        for(j = 0; j < dim; j++) {
            if ( !flt[RIDX(i, j, dim)] )
                dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
            else
                dst[RIDX(i, j, dim)] = src[RIDX(i, j, dim)];
        }
    }
}


/*
 * bokeh - Your current working version of bokeh
 * IMPORTANT: This is the version you will be graded on
 */
char bokeh_descr[] = "bokeh: Current working version";
void bokeh(int dim, pixel *src, short *flt, pixel *dst)
{
    int i, j;
    pixel_sum sum;
    pixel current_pixel;


    if(!flt[RIDX(0, 0, dim)]){
      initialize_pixel_sum(&sum);
      accumulate_sum(&sum,src[RIDX(0, 0, dim)]);
      accumulate_sum(&sum,src[RIDX(0, 1, dim)]);
      accumulate_sum(&sum,src[RIDX(1, 0, dim)]);
      accumulate_sum(&sum,src[RIDX(1, 1, dim)]);
      assign_sum_to_pixel(&current_pixel,sum);
      dst[RIDX(0, 0, dim)] = current_pixel;
    } else dst[RIDX(0, 0, dim)] = src[RIDX(0, 0, dim)];

    if (!flt[RIDX(0, dim-1, dim)]){
      initialize_pixel_sum(&sum);
      accumulate_sum(&sum,src[RIDX(0, dim-2, dim)]);
      accumulate_sum(&sum,src[RIDX(0, dim-1, dim)]);
      accumulate_sum(&sum,src[RIDX(1, dim-2, dim)]);
      accumulate_sum(&sum,src[RIDX(1, dim-1, dim)]);
      assign_sum_to_pixel(&current_pixel,sum);
      dst[RIDX(0, dim-1, dim)] = current_pixel;
    } else dst[RIDX(0, dim-1, dim)] = src[RIDX(0, dim-1, dim)];

    if(!flt[RIDX(dim-1, 0, dim)]){
      initialize_pixel_sum(&sum);
      accumulate_sum(&sum,src[RIDX(dim-2, 0, dim)]);
      accumulate_sum(&sum,src[RIDX(dim-2, 1, dim)]);
      accumulate_sum(&sum,src[RIDX(dim-1, 0, dim)]);
      accumulate_sum(&sum,src[RIDX(dim-1, 1, dim)]);
      assign_sum_to_pixel(&current_pixel,sum);
      dst[RIDX(dim-1, 0, dim)] = current_pixel;
    } else dst[RIDX(dim-1, 0, dim)] = src[RIDX(dim-1, 0, dim)];

    if(!flt[RIDX(dim-1, dim-1, dim)]){
      initialize_pixel_sum(&sum);
      accumulate_sum(&sum,src[RIDX(dim-2, dim-2, dim)]);
      accumulate_sum(&sum,src[RIDX(dim-2, dim-1, dim)]);
      accumulate_sum(&sum,src[RIDX(dim-1, dim-2, dim)]);
      accumulate_sum(&sum,src[RIDX(dim-1, dim-1, dim)]);
      assign_sum_to_pixel(&current_pixel,sum);
      dst[RIDX(dim-1, dim-1, dim)] = current_pixel;
    } else dst[RIDX(dim-1, dim-1, dim)] = src[RIDX(dim-1, dim-1, dim)];




      for(i = 1; i < dim-1; i++) {
          for(j = 1; j < dim-1; j++) {
              if ( !flt[RIDX(i, j, dim)] ){
                  initialize_pixel_sum(&sum);
                  accumulate_sum(&sum,src[RIDX(i-1, j-1, dim)]);
                  accumulate_sum(&sum,src[RIDX(i-1, j, dim)]);
                  accumulate_sum(&sum,src[RIDX(i-1, j+1, dim)]);
                  accumulate_sum(&sum,src[RIDX(i, j-1, dim)]);
                  accumulate_sum(&sum,src[RIDX(i, j, dim)]);
                  accumulate_sum(&sum,src[RIDX(i, j+1, dim)]);
                  accumulate_sum(&sum,src[RIDX(i+1, j-1, dim)]);
                  accumulate_sum(&sum,src[RIDX(i+1, j, dim)]);
                  accumulate_sum(&sum,src[RIDX(i+1, j+1, dim)]);
                  assign_sum_to_pixel(&current_pixel,sum);
                  dst[RIDX(i, j, dim)] = current_pixel;
                }
                else
                    dst[RIDX(i, j, dim)] = src[RIDX(i, j, dim)];
              }
        }


        for(j=1; j<dim-1; j++){
          if (!flt[RIDX(0, j, dim)] ){
            initialize_pixel_sum(&sum);
            accumulate_sum(&sum,src[RIDX(0, j-1, dim)]);
            accumulate_sum(&sum,src[RIDX(0, j, dim)]);
            accumulate_sum(&sum,src[RIDX(0, j+1, dim)]);
            accumulate_sum(&sum,src[RIDX(1, j-1, dim)]);
            accumulate_sum(&sum,src[RIDX(1, j, dim)]);
            accumulate_sum(&sum,src[RIDX(1, j+1, dim)]);
            assign_sum_to_pixel(&current_pixel,sum);
            dst[RIDX(0, j, dim)] = current_pixel;
          }else dst[RIDX(0, j, dim)] = src[RIDX(0, j, dim)];
        }

        for(j=1; j<dim-1; j++){
          if (!flt[RIDX(dim-1, j, dim)] ){
            initialize_pixel_sum(&sum);
            accumulate_sum(&sum,src[RIDX(dim-2, j-1, dim)]);
            accumulate_sum(&sum,src[RIDX(dim-2, j, dim)]);
            accumulate_sum(&sum,src[RIDX(dim-2, j+1, dim)]);
            accumulate_sum(&sum,src[RIDX(dim-1, j-1, dim)]);
            accumulate_sum(&sum,src[RIDX(dim-1, j, dim)]);
            accumulate_sum(&sum,src[RIDX(dim-1, j+1, dim)]);
            assign_sum_to_pixel(&current_pixel,sum);
            dst[RIDX(dim-1, j, dim)] = current_pixel;
          }else dst[RIDX(dim-1, j, dim)] = src[RIDX(dim-1, j, dim)];
        }

        for(i=1; i<dim-1; i++){
          if (!flt[RIDX(i, 0, dim)] ){
            initialize_pixel_sum(&sum);
            accumulate_sum(&sum,src[RIDX(i-1, 0, dim)]);
            accumulate_sum(&sum,src[RIDX(i-1, 1, dim)]);
            accumulate_sum(&sum,src[RIDX(i, 0, dim)]);
            accumulate_sum(&sum,src[RIDX(i, 1, dim)]);
            accumulate_sum(&sum,src[RIDX(i+1, 0, dim)]);
            accumulate_sum(&sum,src[RIDX(i+1, 1, dim)]);
            assign_sum_to_pixel(&current_pixel,sum);
            dst[RIDX(i, 0, dim)] = current_pixel;
          }else dst[RIDX(i, 0, dim)] = src[RIDX(i, 0, dim)];
        }

        for(i=1; i<dim-1; i++){
          if ( !flt[RIDX(i, dim-1, dim)] ){
            initialize_pixel_sum(&sum);
            accumulate_sum(&sum,src[RIDX(i-1, dim-2, dim)]);
            accumulate_sum(&sum,src[RIDX(i-1, dim-1, dim)]);
            accumulate_sum(&sum,src[RIDX(i, dim-2, dim)]);
            accumulate_sum(&sum,src[RIDX(i, dim-1, dim)]);
            accumulate_sum(&sum,src[RIDX(i+1, dim-2, dim)]);
            accumulate_sum(&sum,src[RIDX(i+1, dim-1, dim)]);
            assign_sum_to_pixel(&current_pixel,sum);
            dst[RIDX(i, dim-1, dim)] = current_pixel;
          }else dst[RIDX(i, dim-1, dim)] = src[RIDX(i, dim-1, dim)];
        }
}

/*********************************************************************
 * register_bokeh_functions - Register all of your different versions
 *     of the bokeh kernel with the driver by calling the
 *     add_bokeh_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_bokeh_functions()
{
    add_bokeh_function(&naive_bokeh, naive_bokeh_descr);
    add_bokeh_function(&bokeh, bokeh_descr);
    /* ... Register additional test functions here */
}

/***************************
 * HADAMARD PRODUCT KERNEL *
 ***************************/

/******************************************************
 * Your different versions of the hadamard product functions go here
 ******************************************************/

/*
 * naive_hadamard - The naive baseline version of hadamard product of two matrices
 */
char naive_hadamard_descr[] = "naive_hadamard The naive baseline version of hadamard product of two matrices";
void naive_hadamard(int dim, int *src1, int *src2, int *dst) {

    int i, j;

    for(i = 0; i < dim; i++)
        for(j = 0; j < dim; j++)
            dst[RIDX(i, j, dim)] = src1[RIDX(i, j, dim)] * src2[RIDX(i, j, dim)];
}

/*
 * hadamard - Your current working version of hadamard product
 * IMPORTANT: This is the version you will be graded on
 */
char hadamard_descr[] = "hadamard: Current working version";
void hadamard(int dim, int *src1, int *src2, int *dst)
{
    int i;
    const int size = dim*dim;

    for(i = 0; i < size; i+=32){
        dst[i]=  src1[i] * src2[i];
        dst[i+1] = src1[i+1] * src2[i+1];
        dst[i+2] = src1[i+2] * src2[i+2];
        dst[i+3] = src1[i+3] * src2[i+3];
        dst[i+4] = src1[i+4] * src2[i+4];
        dst[i+5] = src1[i+5] * src2[i+5];
        dst[i+6] = src1[i+6] * src2[i+6];
        dst[i+7] = src1[i+7] * src2[i+7];
        dst[i+8] = src1[i+8] * src2[i+8];
        dst[i+9] = src1[i+9] * src2[i+9];
        dst[i+10] = src1[i+10] * src2[i+10];
        dst[i+11] = src1[i+11] * src2[i+11];
        dst[i+12] = src1[i+12] * src2[i+12];
        dst[i+13] = src1[i+13] * src2[i+13];
        dst[i+14] = src1[i+14] * src2[i+14];
        dst[i+15] = src1[i+15] * src2[i+15];
        dst[i+16] = src1[i+16] * src2[i+16];
        dst[i+17] = src1[i+17] * src2[i+17];
        dst[i+18] = src1[i+18] * src2[i+18];
        dst[i+19] = src1[i+19] * src2[i+19];
        dst[i+20] = src1[i+20] * src2[i+20];
        dst[i+21] = src1[i+21] * src2[i+21];
        dst[i+22] = src1[i+22] * src2[i+22];
        dst[i+23] = src1[i+23] * src2[i+23];
        dst[i+24] = src1[i+24] * src2[i+24];
        dst[i+25] = src1[i+25] * src2[i+25];
        dst[i+26] = src1[i+26] * src2[i+26];
        dst[i+27] = src1[i+27] * src2[i+27];
        dst[i+28] = src1[i+28] * src2[i+28];
        dst[i+29] = src1[i+29] * src2[i+29];
        dst[i+30] = src1[i+30] * src2[i+30];
        dst[i+31] = src1[i+31] * src2[i+31];
    }
}
/*********************************************************************
 * register_hadamard_functions - Register all of your different versions
 *     of the hadamard kernel with the driver by calling the
 *     add_hadamard_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_hadamard_functions()
{
    add_hadamard_function(&naive_hadamard, naive_hadamard_descr);
    add_hadamard_function(&hadamard, hadamard_descr);
    /* ... Register additional test functions here */
}
