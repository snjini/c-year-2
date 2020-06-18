/* FILE: A3_solutions.c is where you will code your answers for Assignment 3.
 * 
 * Each of the functions below can be considered a start for you. They have 
 * the correct specification and are set up correctly with the header file to
 * be run by the tester programs.  
 *
 * You should leave all of the code as is, especially making sure not to change
 * any return types, function name, or argument lists, as this will break
 * the automated testing. 
 *
 * Your code should only go within the sections surrounded by
 * comments like "REPLACE EVERTHING FROM HERE... TO HERE.
 *
 * The assignment document and the header A3_solutions.h should help
 * to find out how to complete and test the functions. Good luck!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "A3_provided_functions.h"

unsigned char*
bmp_open( char* bmp_filename,        unsigned int *width, 
          unsigned int *height,      unsigned int *bits_per_pixel, 
          unsigned int *padding,     unsigned int *data_size, 
          unsigned int *data_offset                                  )
{
  unsigned char *img_data=NULL;

 // Open a binary bmp file
  FILE *bmpfile = fopen( bmp_filename, "rb" );
  
  if( bmpfile == NULL ){
    printf( "I was unable to open the file.\n" );
    return NULL;
  }

  // Read the B and M characters into chars
  char b, m;
  fread (&b,1,1,bmpfile);
  fread (&m,1,1,bmpfile);

  fread( data_size, 1, sizeof(unsigned int), bmpfile );
  
  // Rewind file pointer to the beginning and read the entire contents.
  rewind(bmpfile);

  img_data = (unsigned char*)malloc(sizeof(unsigned char) * *data_size );
  if( fread( img_data, 1, *data_size, bmpfile ) != *data_size ){
    printf( "I was unable to read the requested %d bytes.\n", *data_size );
    return NULL;
  }
   
  *width = *(unsigned int*)(img_data+18);
 
  *height = *(unsigned int*)(img_data+22);

  *bits_per_pixel = *(unsigned short*)(img_data+28);

  unsigned int num_colors = *bits_per_pixel/8;
  *padding = ((4-(*width)*(num_colors) % 4) % 4);

  *data_offset = *(unsigned int*)(img_data+10);

  return img_data;
}

void 
bmp_close( unsigned char **img_data )
{
 
  free(*img_data);
  *img_data = NULL;

}

unsigned char***  
bmp_scale( unsigned char*** pixel_array, unsigned char* header_data, unsigned int header_size,
           unsigned int* width, unsigned int* height, unsigned int num_colors,
           float scale )
{
  unsigned char*** new_pixel_array = NULL; 

  *height = (*height * scale);
  *width = (*width * scale);

  if( header_data == NULL ){ 
    printf( "Error: bmp_open returned NULL. Returning from bmp_to_3D_array without attempting changes.\n" ); 
    return NULL; 
  }

  if( pixel_array == NULL ){
    printf( "Error: bmp_to_3D_array failed to allocate memory for image of height %d.\n", (*height) );
    return NULL;
  }
  new_pixel_array = (unsigned char***)malloc( sizeof(unsigned char**) * (*height));
  for( int row=0; row<*height; row++ ){
    new_pixel_array[row] = (unsigned char**)malloc( sizeof(unsigned char*) * (*width) );
    for( int col=0; col<*width; col++ ){
      new_pixel_array[row][col] = (unsigned char*)malloc( sizeof(unsigned char) * (num_colors) );
    }
  }

  for( int row=0; row<*height; row++ ) {
    for( int col=0; col<*width; col++ ) {
      new_pixel_array[row][col] = pixel_array[(int)(row/scale)][(int)(col/scale)];
    }
  }

*(unsigned int*)(header_data+2) = (header_size + (*height * *width *sizeof(unsigned char) * num_colors));

*(unsigned int*)(header_data+18) = *width;

*(unsigned int*)(header_data+22) = *height;


  return new_pixel_array;
}        


int 
bmp_collage( char* background_image_filename,     char* foreground_image_filename, 
             char* output_collage_image_filename, int row_offset,                  
             int col_offset,                      float scale )
{

 unsigned char* background_hd;
 unsigned int background_hdsize;
 unsigned int background_width;
 unsigned int background_height;
 unsigned int background_nc;

 unsigned char* foreground_hd;
 unsigned int foreground_hdsize;
 unsigned int foreground_width;
 unsigned int foreground_height;
 unsigned int foreground_nc;
 
unsigned char*** background_pixel_array = bmp_to_3D_array( background_image_filename, &background_hd,
  &background_hdsize, &background_width, &background_height, &background_nc );

unsigned char*** foreground_pixel_array = bmp_to_3D_array( foreground_image_filename, &foreground_hd,
  &foreground_hdsize, &foreground_width, &foreground_height, &foreground_nc );


foreground_pixel_array = bmp_scale( foreground_pixel_array, foreground_hd, foreground_hdsize,
  &foreground_width, &foreground_height, foreground_nc, scale );

for( int row=row_offset; row<row_offset+foreground_height; row++ )
  for( int col=col_offset; col<col_offset+foreground_width; col++ )
    if(foreground_pixel_array[row-row_offset][col-col_offset][0] != 0) {
    background_pixel_array[row][col] = foreground_pixel_array[row-row_offset][col-col_offset];
}

return bmp_from_3D_array( output_collage_image_filename, background_hd, background_hdsize, 
           background_pixel_array, background_width, background_height, background_nc );
}    

