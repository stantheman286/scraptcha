#include <stdio.h>
#include <highgui.h>
#include <cv.h>
#include <math.h>
#include <stdlib.h>

// Scraptcha Definitions
#define TRASH 0
#define RECYCLING 1
#define COMPOST 2

int detectScrap(char*);

int main(int argc, char **argv) {

  switch (detectScrap("picture.jpg")) {
    case TRASH:     printf("\nThis object is TRASH!\n\n"); break;
    case RECYCLING: printf("\nThis object is RECYCLING!\n\n"); break;
    case COMPOST:   printf("\nThis object is COMPOST!\n\n"); break;
    default: break;
  }
 
  return 0;

}

int detectScrap(char *imageName) {

  int h, w, r_step, g_step, b_step, i, j, result;
  unsigned int r_sum, g_sum, b_sum;
  IplImage* image;
 
  // Open image
  image = cvLoadImage(imageName, CV_LOAD_IMAGE_UNCHANGED);
  if (!image)
    printf("Could not load image file: %s\n", imageName);

  // Grab image dimmensions
  h = image->height;
  w = image->width;

  // Create an image for each RGB channel
  IplImage* r = cvCreateImage(cvGetSize(image), 8, 1);
  IplImage* g = cvCreateImage(cvGetSize(image), 8, 1);
  IplImage* b = cvCreateImage(cvGetSize(image), 8, 1);

  // Split the image up into its respective RGB channels
  cvSplit(image, b, g, r, 0);

  // Calculate step values
  r_step = r->widthStep;
  g_step = g->widthStep;
  b_step = b->widthStep;

  // Go through the entire image, summing the RGB channel values separately
  r_sum = g_sum = b_sum = 0;

  for(i = 0; i < h; i++) {
    for (j = 0; j < w; j++) {
      r_sum += r->imageData[i*r_step+j];
      g_sum += g->imageData[i*g_step+j];
      b_sum += b->imageData[i*b_step+j];
    }
  }

  // Calculate result based on major color (red = TRASH, green = COMPOST, blue = RECYCLING)
  if ((r_sum > g_sum) && (r_sum > b_sum))
    result = TRASH;
  else if ((b_sum > r_sum) && (b_sum > g_sum))
    result = RECYCLING;
  else
    result = COMPOST;

  // Print out the results
//  printf("Red\t>> %u\n", r_sum);
//  printf("Green\t>> %u\n", g_sum);
//  printf("Blue\t>> %u\n", b_sum);

  // Release all image pointers
  cvReleaseImage(&image);
  cvReleaseImage(&r);
  cvReleaseImage(&g);
  cvReleaseImage(&b);

  return result;
}


