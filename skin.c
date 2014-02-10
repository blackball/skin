#include <opencv/cv.h>
#include <opencv/highgui.h>

void
skin_detect_rgb(const IplImage *rgb, IplImage *map) {
        int i, j, w = rgb->width, h = rgb->height;
        
        cvSetZero(map);
        for (i = 0; i < h; ++i) {
                for (j = 0; j < w; ++j) {
                        const CvScalar p = cvGet2D(rgb, i, j);
                        const double
                                b = p.val[0],
                                g = p.val[1],
                                r = p.val[2];
                        if (r > 95.0 && g > 40.0 && b > 20.0 && (r - g > 15.0) && r > b)
                                cvSet2D(map, i, j, p);
                }
        }
}

void
skin_detect_rg(const IplImage *rgb, IplImage *map) {
        const double 
                Aup = -1.8423, 
                Bup = 1.5294,
                Cup = 0.0422,
                Adown = -0.7279,
                Bdown = 0.6066,
                Cdown = 0.1766;

        int i, j, h = rgb->height, w = rgb->width;

        cvSetZero(map);
        
        for (i = 0; i < h; ++i) {
                for (j = 0; j < w; ++j) {
                        const CvScalar p = cvGet2D(rgb, i, j);
                        const double s = p.val[0] + p.val[1] + p.val[2];
                        const double 
                                r = (double)p.val[2] / s,
                                g = (double)p.val[1] / s,
                                Gup = Aup*r*r+Bup*r+Cup,
                                Gdown = Adown*r*r+Bdown*r+Cdown,
                                Wr = (r-0.33)*(r-0.33)+(g-0.33)*(g-0.33);
                         
                        if (g < Gup && g > Gdown && Wr > 0.004) {
                                cvSet2D(map, i, j, p);
                        }                        
                }
        }
}

void
skin_detect_ycrcb(const IplImage *ycb, IplImage *map) {
        int i, j, w = ycb->width, h = ycb->height;
        
        cvSetZero(map);
        for (i = 0; i < h; ++i) {
                for (j = 0; j < w; ++j) {
                        const CvScalar p  = cvGet2D(ycb, i, j);
                        const double 
                                cr = p.val[1],
                                cb = p.val[2];
                        if ((cr>130.0 && cr<170.0 ) && (cb>70.0 && cb<125.0)) {
                                cvSet2D(map, i, j, p);
                        }
                        /*
                          if ((cr <= 1.5862*cb + 20.0) && 
                          (cr >= 0.3448*cb+76.2069) &&
                          (cr >= -4.5652*cb+234.5652) &&
                          (cr <= -1.15*cb+301.75) && 
                          (cr <= -2.2857*cb+432.85) ) {
                          cvSet2D(map, i, j, p);
                          }
                        */
                }
        }
}

void
skin_detect_hsv(const IplImage *hsv, IplImage *map) {
        int i, j, w = hsv->width, h = hsv->height;
        
        cvSetZero(map);
        for (i = 0; i < h; ++i) {
                for (j = 0; j < w; ++j) {
                        const CvScalar p  = cvGet2D(hsv, i, j);
                        const double h  = p.val[0];
                        if ( (h < 25.0) | (h > 230.0))
                                cvSet2D(map, i, j, p);
                }
        }
}
