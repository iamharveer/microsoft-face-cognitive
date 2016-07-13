// system defined header files.
#include <queue>
#include <iostream>

// user or external lib dependent header files.
#include "face.hpp"
#include "opencv/cv.h"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;


/********************************************************************/
/* Function Name  : captureFrame                                    */
/* Description    :                                                 */
/* Restrictions   :                                                 */
/********************************************************************/
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


/********************************************************************/
/* Function Name  : main                                            */
/* Description    :                                                 */
/* Restrictions   :                                                 */
/********************************************************************/
int main() 
{
   CvCapture* capture = cvCaptureFromCAM( CV_CAP_ANY );
 
   if ( !capture )
   {
      fprintf( stderr, "ERROR: capture is NULL \n" );
      getchar();
        
      return -1;
   }

   // Create a window in which the captured images will be presented
   cvNamedWindow( "mywindow", CV_WINDOW_AUTOSIZE );

   // Get one frame
   IplImage* frame;;

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

      // Do not release the frame!
      if ( (cvWaitKey(10) & 255) == 's' )
      {
         cvSaveImage("1.jpg", frame);
         frame->imageData[frame->imageSize - 1] = '\0';

         importPythonModule ("1.jpg");
      }

      if ( (cvWaitKey(10) & 255) == 27 ) break;
   }

   // Release the capture device housekeeping
   cvReleaseCapture( &capture );
   cvDestroyWindow( "mywindow" );

   return 0;
}
