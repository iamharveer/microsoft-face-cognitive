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
void* processFrame (void* arg)
{
   char fileName[10] = { 0 };
   unsigned int i = 0;
   size_t queue_size = 0;
   int rtn_code = 0;

   while (1)
   {
      // critical section, needs to protect it against
      // concurent access to que.
      rtn_code = pthread_mutex_lock (&mutex);
      if (rtn_code != 0)
      {
         cout << "Error occurred in waiting for mutex, rtn_code = "
              << rtn_code << endl;
         return NULL;
      }

      queue_size = que.size();

      if (queue_size != 0)
      {
         printf ("call python \n");
         IplImage &frame = que.front();
         IplImage frameCopy;
         pthread_mutex_unlock (&mutex);
         
         que.pop();

         memcpy (&frameCopy, &frame, sizeof(IplImage));

         sprintf (fileName, ".%u.jpg", i++);
         cvSaveImage (fileName, &frameCopy);

         importPythonModule (fileName);
      }
      
      pthread_mutex_unlock (&mutex);

   }

   return NULL;
}
