#ifndef SKIN_H
#define SKIN_H

typedef struct _IplImage IplImage;

void skin_detect_rg(const IplImage *rgb, IplImage *map);
void skin_detect_rgb(const IplImage *rgb, IplImage *map);
void skin_detect_ycrcb(const IplImage *ycb, IplImage *map);
void skin_detect_hsv(const IplImage *hsv, IplImage *map);

#endif
