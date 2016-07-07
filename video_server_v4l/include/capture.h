// v4l.cのためのheader file
#include <linux/videodev.h>

typedef struct {
  int                     vfd;
  struct video_capability vcap;
  struct video_channel    vch;
  struct video_picture    vpic;
  struct video_mbuf       vbuf;
  struct video_mmap       vmap;
  char                    *mem;
} V4L;

V4L *CaptureInit(char *device, int source);
void CaptureSingleFrame(V4L *v4l, unsigned char *buffer);
void CaptureSingleFrameGrey(V4L *v4l, unsigned char *buffer);
void CaptureSingleFrameAverage(V4L *v4l, char *buffer, int frame);
void CaptureSingleFrameGreyAverage(V4L *v4l, char *buffer, int frame);
void CaptureMultiFrame(V4L *v4l, unsigned char *buffer, int frame);
void CaptureEnd(V4L *v4l);
void init_capture();
void wait_capture();

V4L *CaptureInit2(char *device, int source);
void CaptureEnd2(V4L *v4l2);
void init_capture2();
void wait_capture2();
