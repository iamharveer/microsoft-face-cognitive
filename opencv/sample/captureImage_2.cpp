#include "opencv/cv.h"
#include "opencv2/opencv.hpp"

#include <stdio.h>

using namespace cv;
//
// A Simple Camera Capture Framework
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
    // Show the image captured from the camera in the window and repeat
    while ( 1 )
    {
        // Get one frame
        IplImage* frame = cvQueryFrame( capture );
        if ( !frame )
        {
            fprintf( stderr, "ERROR: frame is null...\n" );
            getchar();
            break;
        }

        cvShowImage( "mywindow", frame );
        // Do not release the frame!

        if ( (cvWaitKey(10) & 255) == 's' )
        {

           // CvSize size = cvGetSize(frame);
           // IplImage* img= cvCreateImage(size, IPL_DEPTH_16S, 1);
           // img = frame;

            cvSaveImage("matteo.jpg", frame);

        }

        if ( (cvWaitKey(10) & 255) == 27 ) break;
    }
    // Release the capture device housekeeping
    cvReleaseCapture( &capture );
    cvDestroyWindow( "mywindow" );
    return 0;
}
