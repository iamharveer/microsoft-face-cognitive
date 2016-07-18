// C++ style system defined header files.
#include <queue>
#include <iostream>

// C style system defined header files.
#include <pthread.h>
#include <errno.h>

// user or external lib dependent header files.
#include "face.hpp"
#include "opencv/cv.h"
#include "opencv2/opencv.hpp"

// include namespaces.
using namespace cv;
using namespace std;

// global variables.
queue<IplImage> que;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


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
   int rtn_code = 0;
   

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
   struct timespec maxT_toObtainMutex = { .tv_sec  = 0,
                                          .tv_nsec = 28000 };

   int pushedFrameCount = 0;
   int rtn_code = 0;

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
  
   pthread_t frameProcessorThID;
   
   rtn_code = pthread_create (&frameProcessorThID, NULL, processFrame, NULL);
   if (rtn_code != 0)
   {
      perror ("Error creating thread (frameProcessor): ");
      return -2;
   } 
    
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
      if (pushedFrameCount < MAX_FRAMES_TO_PROCESS)
      {
         // critical section, need to protect que against
         // simultaneous access.
         rtn_code = pthread_mutex_timedlock (&mutex, &maxT_toObtainMutex);

         if (!rtn_code)
         {
            que.push (*frame);

            pthread_mutex_unlock (&mutex);
            pushedFrameCount++;
         }

         else if (rtn_code == ETIMEDOUT || rtn_code == EAGAIN)
         {
            cout << "timeout occurred.\n";
         }

         else
         {
            cout << "unexpected error occurred in locking mutex, rtn_code = "
                 << rtn_code << endl;
         }
      }

      cvWaitKey(28);

      // give a chance other thread to process just captured frame.
      pthread_yield();
   }

   // Release the capture device housekeeping
   cvReleaseCapture( &capture );
   cvDestroyWindow( "mywindow" );

   return 0;
}
