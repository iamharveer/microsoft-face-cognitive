// system defined header files.
#include <queue>
#include <thread>
#include <iostream>

// user or external lib dependent header files.
#include "face.hpp"
#include "opencv/cv.h"
#include "opencv2/opencv.hpp"

// include namespaces.
using namespace cv;
using namespace std;

// global variables.
queue<IplImage> que;


/******************************************************************************/
/* Function Name  : captureFrame                                              */
/* Description    : captures a frame from primary camera (webcam).            */
/* Parameters     : - CvCapture* const                                        */
/*                  - IplImage** const                                        */
/* Restrictions   :                                                           */
/* Dependencies   :                                                           */
/******************************************************************************/
int captureFrame (CvCapture* const capture, IplImage** const frame)
{
   // Get one frame
   *frame = cvQueryFrame (capture);

   if (*frame == NULL)
   {
      fprintf( stderr, "ERROR: frame is null...\n" );

      // needs to be replaced with proper error handling.
      return -1;
   }
  
   return 0;
}


/******************************************************************************/
/* Function Name  : main                                                      */
/* Description    : main function.                                            */
/* Parameters     : - argc : number of arguments passed to the program.       */
/*                  - argv : pointers to paramters passed.                     */
/* Restrictions   :                                                           */
/* Dependencies   :                                                           */
/******************************************************************************/
int main(int argc, char *argv[]) 
{
   int pushedFrameCount = 0;

   // Get one frame
   IplImage* frame;

   CvCapture* capture = cvCaptureFromCAM( CV_CAP_ANY );
 
   if ( !capture )
   {
      fprintf( stderr, "ERROR: capture is NULL \n" );
      getchar();
        
      return -1;
   }

   // Create a window in which the captured images will be presented
   cvNamedWindow( "mywindow", CV_WINDOW_AUTOSIZE );
   
   int n = 10;
   thread processFrameThID (processFrame, n);

   // Show the image captured from the camera in the window and repeat
   while ( 1 )
   {
      frame = NULL;

      // grab a frame.
      captureFrame (capture, &frame);

      // if we are not able to grab a frame, then generate error msg and exit.
      if (frame == NULL)
      {
         fprintf( stderr, "ERROR: frame is null...\n" );

         getchar();
         break;
      }

      cvShowImage( "mywindow", frame );
      
      // push frame to queue until the count < 10.
      if (pushedFrameCount++ < MAX_FRAMES_TO_PROCESS)
      {
         que.push (*frame);
      }

      cvWaitKey(28);
   }

   // Release the capture device housekeeping
   cvReleaseCapture( &capture );
   cvDestroyWindow( "mywindow" );

   return 0;
}
