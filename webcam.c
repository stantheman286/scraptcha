#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <string.h>
#include <cv.h> 
#include <highgui.h> 
#include "webcam.h"

int main(int argc, char *argv[]) {

  char filename[255];

//  // Check for valid number of arguments
//  if (argc < 2 || argc > 4) {
//    fprintf(stderr, "ERROR: Incorrect number of arguments\n");
//    return -1;
//  }

  strcpy(filename, "testing.jpg");

  // Take a picture and analyze the result
  if (takePicture(filename, CAPTURE) == 0) {
    switch (detectScrap(filename)) {
      case TRASH:     printf("\nThis object is TRASH!\n\n"); break;
      case RECYCLING: printf("\nThis object is RECYCLING!\n\n"); break;
      case COMPOST:   printf("\nThis object is COMPOST!\n\n"); break;
      default: break;
    }
  }

  return 0;
}

int takePicture(char *filename, int type) {
  
  IplImage *frame;
  
  // Connect to the only camera
  CvCapture* capture = cvCaptureFromCAM(0);
  if (!capture) {
    fprintf(stderr, "ERROR: Capture is NULL (webcam not connected)\n");
    return -1;
  }

  // Set frame size
  cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 320); 
  cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 240);

  // Image capture mode
//  if ((strcmp(argv[1], "--capture") == 0) || (strcmp(argv[1], "-c") == 0)) {
  if (type == CAPTURE) {

//    // Set picture name or use default
//    if (argc == 3)
//      strcpy(filename, argv[2]);
//    else
//      strcpy(filename, "picture.jpg");

    // Get frame for image
    frame = cvQueryFrame(capture);
    if (!frame) {
      fprintf(stderr, "ERROR: Frame is NULL\n");
      return -1;
    }

    // Save image
    cvSaveImage(filename, frame, 0);

    // Release the frame and capture device housekeeping
    cvReleaseImage(&frame);
    cvReleaseCapture(&capture);

  // Live video mode
//  } else if ((strcmp(argv[1], "--live") == 0) || (strcmp(argv[1], "-l") == 0)) {
  } else if (type == LIVE) {

    // Create a window in which the captured images will be presented
    cvNamedWindow("Live Camera", CV_WINDOW_AUTOSIZE);
  
    // Show the image captured from the camera in the window and repeat
    while (1) {
      // Get one frame
      frame = cvQueryFrame(capture);
      if (!frame) {
        fprintf(stderr, "ERROR: Frame is NULL\n");
        break;
      }
    
      cvShowImage("Live Camera", frame);
      // Do not release the frame!
      //If ESC key pressed, Key=0x10001B under OpenCV 0.9.7(linux version),
      //remove higher bits using AND operator
      if ((cvWaitKey(10) & 255) == 27) break;
    }

    // Release the capture device housekeeping
    cvReleaseCapture(&capture);
    cvDestroyWindow("Live Camera");
  } else {
    fprintf(stderr, "ERROR: Not a valid option\n");
    return -1;
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
