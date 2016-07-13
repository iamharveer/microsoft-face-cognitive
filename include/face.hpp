#include <queue>

#include "opencv/cv.h"
#include "opencv2/opencv.hpp"

#define MAX_FRAMES_TO_PROCESS 10

// global queue that pushes frames in order for processFrame to execute.
extern std::queue<IplImage> que;

int importPythonModule (const char *);
int captureFrame (CvCapture* const, IplImage** const);
int processFrame (int arg);

