#define VERSION "capture-V4L Version 1.1\n"

#define TRUE  1
#define FALSE 0

#define FRAME_SIZE (video_height*video_width*3)

enum videoType{ WEBCAM, NTSC};

/* for usb camera */
#define WEBCAM_WIDTH  352
#define WEBCAM_HEIGHT 288

/* for NTSC Camera */
#define NTSC_WIDTH  640
#define NTSC_HEIGHT 480

/* #define FSIZE (WIDTH*HEIGHT*3) */

#define HWIDTH 320
#define HHEIGHT 240

typedef struct {
	int 	role;
	int		number;
	int		position;
	short pan_s;
	short	tilt_s;
	short	zoom_s;
	short focus;
	int 	PanTiltCtrlFlag;
	int		BlurFlag;
	int		ForestallCompFlag;
	int 	flag;	
} CAM_ATTR ;

#define C_X 335
#define C_Y 227

#define CAMERA_NUM 		1
#define CAMERA_NUM2		1

#define MONITOR 			0
#define STANDBY 			1

#define CENTER				0
#define UP						1
#define BOTTOM				2
#define LEFT					3
#define RIGHT					4
#define UPPER_LEFT		5
#define UPPER_RIGHT		6
#define BOTTOM_LEFT		7
#define BOTTOM_RIGHT	8


#define YES	1
#define NO	0

int OPT_Verbose;
int OPT_Wait;
int OPT_Average;

/* added by Ryo */
void init_video();
void process_a_frame();
void finilize_video();
/**/

void *cap_video();
void *cap_video2();
void *cam_ctrl();
void *cam_ctrl2();
void *video_queue();

void init_of_camera_parameter( CAM_ATTR *cam_attr );
void init_of_fukancamera_parameter( CAM_ATTR *cam_attr );

pthread_mutex_t mutex;

