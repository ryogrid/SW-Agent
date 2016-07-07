#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>

#include "define.h"
#include "capture.h"

extern enum videoType vtype;

extern int video_width;
extern int video_height;

/* ====================================================================== */
static void MyError(char *s){
  fprintf(stderr,"Error: %s\n",s);
  exit(1);
}

/* ====================================================================== */
V4L *CaptureInit(char *device, int source){
  V4L   *v4l;

  /*--< V4Lの領域確保 >--*/
  if ((v4l = (V4L *)malloc(sizeof(V4L))) == NULL) MyError("malloc V4L");

  /*--< デバイスのオープン -->*/
  if((v4l->vfd = open(device, O_RDWR))<0) MyError("open device");
 
  /*--< デバイス仕様の取得 >--*/
  if(ioctl(v4l->vfd, VIDIOCGCAP, &v4l->vcap)<0) MyError("VIDIOCGCAP");

  /*--< 入力端子を選択 >--*/
  v4l->vch.channel=source;
  v4l->vch.norm = 3 ; 		/* AUTO */
  if(vtype == NTSC){
    v4l->vch.norm = VIDEO_MODE_NTSC;
  }

  if(ioctl(v4l->vfd, VIDIOCSCHAN, &v4l->vch)<0) MyError("VIDIOCSCHAN");

  /*--< 色調の設定 >--*/
  if(vtype == WEBCAM){
    /* for usb camera */
    v4l->vpic.brightness = 4767;
    v4l->vpic.hue        = 65535;
    v4l->vpic.colour     = 65535;
    v4l->vpic.contrast   = 15000;
    /*   v4l->vpic.whiteness  = 52767; */
    v4l->vpic.depth      = 24;
  }else{
    v4l->vpic.brightness = 32767;
    v4l->vpic.hue        = 32767;
    v4l->vpic.colour     = 32767;
    v4l->vpic.contrast   = 32767;
    v4l->vpic.whiteness  = 32767;
    v4l->vpic.depth      = 24;
  }

  v4l->vpic.palette=VIDEO_PALETTE_RGB24; /* パレット形式 */

  if(ioctl(v4l->vfd, VIDIOCSPICT, &v4l->vpic)) MyError("VIDIOCSPICT");

  /*--< サイズとパレットを指定 >--*/

  if(vtype == WEBCAM){
    v4l->vmap.width = v4l->vcap.maxwidth;
    v4l->vmap.height = v4l->vcap.maxheight;
  }else{
    v4l->vmap.width = video_width;
    v4l->vmap.height = video_height;
  }
  v4l->vmap.format=VIDEO_PALETTE_RGB24;

  /*--< mmap 情報の取得 >--*/
  if(ioctl(v4l->vfd, VIDIOCGMBUF, &v4l->vbuf)<0) MyError("VIDIOCGMBUF");
  if((v4l->mem = mmap(0,v4l->vbuf.size, PROT_READ|PROT_WRITE, MAP_SHARED,
		      v4l->vfd,0))==(char *)-1)
    MyError("mmap");

  return v4l;
}

/* ====================================================================== */

void CaptureEnd(V4L *v4l){
  close(v4l->vfd);
  free(v4l);
}
/* ====================================================================== */


extern V4L  *v4l;

void init_capture() {

  int  source;
  char *device="/dev/video0";

  char *format;
//	char savename[30] = "";

  extern char   *optarg;
  extern int    optind;

  /*--< 初期設定 >--*/
  source = 0;  // 1:Composite  2:S terminal
  format = (char *)NULL;
  OPT_Verbose = FALSE;
  OPT_Wait = -1;
  OPT_Average = 1;
  
  /*--< Video4Linux の準備 >--*/
  v4l = CaptureInit(device, source);

  /*--< 画像を格納するメモリを確保 >--*/

}
/*-----------------------------------------------------------------------------*/

void wait_capture() {

	int  sec, presec;
	struct timeval tv;

  /*--< キャプチャ開始時刻まで待機 >--*/
  if (OPT_Wait > 0) {
    presec=0;
    while(1){
      gettimeofday(&tv, (struct timezone *)NULL);
      sec = tv.tv_sec;
      if (sec == OPT_Wait) break;
      if (sec > OPT_Wait) {
				fprintf(stderr,
							"Error: Now time is %d. The specified time(%d) is past.\n",
							sec, OPT_Wait);
				exit(1);
      }
      
      if (sec != presec){
				fprintf(stderr, "<%3dsec>\n", OPT_Wait - sec);
				fflush(stderr);
				presec = sec;
      }
    }
  }

}
