// system defined headers.
#include <thread>
#include <cstring>
#include <unistd.h>

// user or external lib dependent headers.
#include "opencv/cv.h"
#include "opencv2/opencv.hpp"
#include "face.hpp"

using namespace std;


/******************************************************************************/
/* Function Name  : processFrame                                              */
/* Description    : captures a frame from primary camera (webcam).            */
/* Parameters     : - CvCapture* const                                        */
/*                  - IplImage** const                                        */
/* Restrictions   :                                                           */
/* Dependencies   :                                                           */
/******************************************************************************/
int processFrame (int arg)
{
   char fileName[10] = { 0 };
   int i = 0;

   while (1)
   {
      if (0 != que.size())
      {
         IplImage &frame = que.front();
         que.pop();
         
         sprintf (fileName, ".%u.jpg", i++);
         cvSaveImage (fileName, &frame);

         printf ("call python \n");
         importPythonModule (fileName);
         sleep(1);
      }
   }

   return 0;
}
