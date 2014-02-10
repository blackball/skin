#include "skin.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>

static void
all_in_one_test(void) {
        CvCapture *cap = cvCaptureFromCAM(0);
        IplImage *frame, *map = 0, *tmp = 0;
        
        if (!cap) {
                return ;
        }

        cvNamedWindow("RGB", 1);
        cvNamedWindow("RG", 1);
        cvNamedWindow("YCRCB", 1);
        cvNamedWindow("HSV", 1);
        
        while ( frame = cvQueryFrame(cap) ) {
                map = cvCreateImage(cvGetSize(frame), 8, 3);
                
                skin_detect_rg(frame, map);
                cvShowImage("RG", map);
                
                skin_detect_rgb(frame, map);
                cvShowImage("RGB", map);
                
                tmp = cvCreateImage(cvGetSize(frame), 8, 3);
                cvCvtColor(frame, tmp, CV_BGR2YCrCb);
                skin_detect_ycrcb(tmp, map);
                cvCvtColor(map, tmp, CV_YCrCb2BGR);
                cvShowImage("YCRCB", tmp);

                cvCvtColor(frame, tmp, CV_BGR2HSV);
                skin_detect_hsv(tmp, map);
                cvCvtColor(map, tmp, CV_HSV2BGR);
                cvShowImage("HSV", tmp);
                
                cvReleaseImage(&tmp); tmp = 0;
                cvReleaseImage(&map); map = 0;

                if (27 == cvWaitKey(10) ) {
                        break;
                }
        }

        cvDestroyAllWindows();
        cvReleaseCapture(&cap);
}

int
main(int argc, char **argv) {
        all_in_one_test();
        return 0;
}
