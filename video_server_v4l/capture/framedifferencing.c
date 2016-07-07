#include <cv.h>          // for OpenCV
#include <highgui.h> 
#include <cxcore.h>	
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>		// for thread programming

#include <sys/time.h>

#include "capture.h"
#include "define.h"
#include "camera.h"
#include "time_count.h"

V4L *v4l;
extern CAM_ATTR *video;
IplImage *imgSrc; // Source Image

int AutoTrackMode=0;
int camDirection=0;

extern enum videoType vtype;

extern int video_width;
extern int video_height;

/* ====================================================================== */
static void MyError(char *s){
  fprintf(stderr,"Error: %s\n",s);
  exit(1);
}

//////////////////////////////////////////////////////////
//
// capture frame
//
//////////////////////////////////////////////////////////
int captureFrame( V4L *v4l, unsigned char *buffer)
{
	int n;
	unsigned char *ptr;

  ptr = v4l->mem + v4l->vbuf.offsets[v4l->vmap.frame];

  for(n=0; n<video_width*video_height; n++) {
    *buffer++=ptr[0];
    *buffer++=ptr[1];
    *buffer++=ptr[2];
  	ptr+=3;
  }

	return 0;
}

double time_sum=0;
//////////////////////////////////////////////////////////
//
// double buffering mode capture start
//
//////////////////////////////////////////////////////////
int CaptureDoubleBufferingStart( V4L *v4l, IplImage *frame )
{
  ///////////////////////////////////////////////////// frame #0 capture start
	v4l->vmap.frame=0;
	if(ioctl(v4l->vfd, VIDIOCMCAPTURE, &v4l->vmap)<0) MyError("VIDIOCMCAPTURE");
 	///////////////////////////////////////////////////// frame #1 capture start
	v4l->vmap.frame=1;
	if(ioctl(v4l->vfd, VIDIOCMCAPTURE, &v4l->vmap)<0) MyError("VIDIOCMCAPTURE");

	v4l->vmap.frame=0;
 	//////////////////////////////////////// frame #0 waiting for end of capture
	if(ioctl(v4l->vfd, VIDIOCSYNC, &v4l->vmap.frame)<0) MyError("1 VIDIOCSYNC");

	////////////////////////////////////////////////////////////// capture frame

	captureFrame( v4l, frame->imageData);


	return 0;
}

//////////////////////////////////////////////////////////
//
// double buffering stationary mode
//
//////////////////////////////////////////////////////////
int CaptureDoubleBufferingStationaryMode( V4L *v4l, IplImage *frame )
{

/* time_checker(&tcountcap); */
  ////////////////////////////////////////////////////// frame #0 capture start
  if (ioctl(v4l->vfd, VIDIOCMCAPTURE, &v4l->vmap)<0) MyError("VIDIOCMCAPTURE");


  v4l->vmap.frame = 1 - v4l->vmap.frame;

/*   v4l->vmap.frame = v4l->vmap.frame + 1; */
/*   if(v4l->vmap.frame == 3){ */
/*     v4l->vmap.frame = 0; */
/*   } */
 	//////////////////////////////////////// frame #0 or #1 waiting for end of capture
  if(ioctl(v4l->vfd, VIDIOCSYNC, &v4l->vmap.frame)<0) MyError("2 VIDIOCSYNC");
	////////////////////////////////////////////////////////////// capture frame

	captureFrame( v4l, frame->imageData);

	return 0;
}


	int loopNo=0;
/* 	int key; */
/* 	int delayTime=2; */
/* 	int RoiNum=0; */
/* 	int TimeChecker=0; */
/* 	int thresh=80; */
/* 	int dilation=2; */
/* 	int smooth=1; */
	
/* 	timecount tcountBlur; */
/* 	double timeBlur=0.0; */

/* 	timecount tcounta; */
/*         double _a=0.0, _b=0.0, _c=0.0, _d=0.0, _e =0.0, _f=0.0, _g=0.0; */

/* 	IplImage *imgGray[3]; */
/* 	IplImage *imgDiff[2]; */
/* 	IplImage *imgAnd; */
/* 	IplImage *imgEnh[2]; */
/* 	IplImage *imgRct[2]; */
/* 	IplImage *imgMask; */
/* 	IplImage *imgEnh3ch; */
/* 	IplImage *imgEnhNot; */
/* 	IplImage *imgSrc1; */
/* 	IplImage *imgSrc2; */

/*        	CvFont dfont; */

void init_video(){
	int i, j;
	int k=0, tmp=0;

	float hscale			= 0.6f;
	float vscale			= 0.6f;
	float italicscale	= 0.0f;
	int thickness			= 2;

	////// capture device ready //////
	init_capture();
	wait_capture();


	imgSrc		= cvCreateImageHeader( cvSize( video_width, video_height),  IPL_DEPTH_8U, 3);
	if ( (imgSrc->imageData = (unsigned char *)malloc(sizeof(unsigned char)*FRAME_SIZE) )==NULL){
	  fprintf(stderr,"Error:Can't allocate memory\n");
	  exit(1);
	}
}

void process_a_frame(){
		if ( loopNo == 0 ) {
			CaptureDoubleBufferingStart( v4l, imgSrc );
		}
		else if ( loopNo > 0 ) {
			CaptureDoubleBufferingStationaryMode( v4l, imgSrc );
		}

		loopNo++;
}

void finilize_video(){
	CaptureEnd(v4l);
	free(imgSrc->imageData);

	cvReleaseImageHeader( &imgSrc );

	return NULL;
}


