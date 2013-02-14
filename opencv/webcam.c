#include <cv.h> 
#include <highgui.h> 
#include <stdio.h> 
#include <string.h>

int main(int argc, char *argv[]) {

  char filename[255];
  IplImage *frame;

  // Check for valid number of arguments
  if (argc < 2 || argc > 4) {
    fprintf(stderr, "ERROR: Incorrect number of arguments\n");
    return -1;
  }

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
  if ((strcmp(argv[1], "--capture") == 0) || (strcmp(argv[1], "-c") == 0)) {

    // Set picture name or use default
    if (argc == 3)
      strcpy(filename, argv[2]);
    else
      strcpy(filename, "picture.jpg");

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
  } else if ((strcmp(argv[1], "--live") == 0) || (strcmp(argv[1], "-l") == 0)) {

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
  }

  return 0;
}
