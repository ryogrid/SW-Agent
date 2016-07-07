/*
  camera.h
*/
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "visca.h"
//#include "camwork.h" /* PAR構造体用 */

/* 
   Some important CONTSTANS of Sony EV-G20 & EV-D30
*/

#define PI 3.14159265358979
#define FL 180.000000000000
#define CAMERA_DEV "/dev/ttyd" /* serial port */

enum {
  G20,
  D30,
  D100
};

// 視野角の半分(degree)
#define D100G1 32.5
#define D100G2 26.8
#define D100G3 22.7
#define D100G4 18.7
#define D100G5 15.0
#define D100G6 11.5
#define D100G7 8.9
#define D100G8 6.6
#define D100G9 4.7
#define D100G10 3.3

// 首振角(制御値)
#define D100_CAM_MAX_PAN_VAL     100   /* degree */
#define D100_CAM_MAX_PAN_CODE    0x05A0
#define D100_CAM_MAX_TILT_VAL    25    /* degree */
#define D100_CAM_MAX_TILT_CODE   0x0168

// 速度
#define D100_CAM_MAX_PAN_SPEED   0x18
#define D100_CAM_MAX_TILT_SPEED  0x14
#define D100_CAM_MAX_ZOOM_VAL    10    /* tele */
#define D100_CAM_MAX_ZOOM_CODE   0x4000

// 視野角の半分(degree)
#define D30G1 24.4
#define D30G2 21.0
#define D30G3 18.4
#define D30G4 15.7
#define D30G5 13.0
#define D30G6 10.5
#define D30G7 8.5
#define D30G8 6.6
#define D30G9 5.1
#define D30G10 3.9
#define D30G11 3.0
#define D30G12 2.2

// 首振角(制御値)
#define D30_CAM_MAX_PAN_VAL     100   /* degree */
#define D30_CAM_MAX_PAN_CODE    0x370
#define D30_CAM_MAX_TILT_VAL    25    /* degree */
#define D30_CAM_MAX_TILT_CODE   0x12C

// 速度
#define D30_CAM_MAX_PAN_SPEED   0x18
#define D30_CAM_MAX_TILT_SPEED  0x14
#define D30_CAM_MAX_ZOOM_VAL    12    /* tele */
#define D30_CAM_MAX_ZOOM_CODE   0x3FF

// 視野角の半分(degree)
#define G20G1 22.5
#define G20G2 11.2
#define G20G3 7.5

// 首振角(制御値)
#define G20_CAM_MAX_PAN_VAL     30   /* degree */
#define G20_CAM_MAX_PAN_CODE    0x3CDA
#define G20_CAM_MAX_TILT_VAL    15    /* degree */
#define G20_CAM_MAX_TILT_CODE   0x1E6D

// 速度
#define G20_CAM_MAX_PAN_SPEED   0x7F
#define G20_CAM_MAX_TILT_SPEED  0x7F
#define G20_CAM_MAX_ZOOM_VAL    3    /* tele */
#define G20_CAM_MAX_ZOOM_CODE   0x4000

typedef struct _Camera {
  int id;
  int type;
  int target_receiver;
  double zoom;
  int port;
  double Wpos[3];
  double CtoW[3][3];
  double Rtarget[3];
  double Offset[3];
} Camera;

// 基本関数
int camera_zoom (int port, int wait, short zoom_s);
int cam_zoom_all (Camera *Camera, int cam_number);
int camera_pan_tilt (int port, int wait, short pan_s, int p_vel, short tilt_s, int t_vel);
int ask_camera_pan_tilt (int port, short* pan, short* tilt);
int ask_camera_zoom (int port, short* zoom);

int camera_wb (int port, int wait, char wb_mode);
int ask_camera_wb (int port, char *wb_mode );
int camera_ae (int port, int wait, char ae_mode);
int ask_camera_ae (int port, char *ae_mode );

int camera_fcs(int port, int wait, char focus);
int ask_camera_fcs (int port, short *focus);
int camera_fcs_infty(int port, int wait);
int camera_fcs_drct(int port, int wait, int fcs_d);
int camera_fcs_manu(int port, int wait, char focus);
int camera_PicEf(int port, int wait, char pic_ef);
int camera_init(char *dev,int *c_port);
void foucus_change(int x, double *f_w, double *f_h);
void cal_pt_degree(double *pan, double *tilt, int x, int y, double f_w, double f_h);
void calculate_pan_tilt_degree( int x_posi, int y_posi, double f_w, double f_h, short *d_p, short *d_t   ); 
void calculate_pan_tilt_degree_swing_correct( int pan_pixel, int tilt_pixel,
																double f_w, double f_h, 
																short *d_p, short *d_t   );

// 実際の撮影時に使う
//int Load_Cam_Setting(char *setting_file, int cam_num, Camera *Camera, PAR *par, int frequency);
int Cam_Open(Camera *Camera, int cam_number, char *camera_dev);
int Cam_Close(Camera *Camera, int cam_num);

// 互換性のために残してある
int Cam_Zoom_All(Camera *Camera, int cam_number);
int Cam_Zoom(short zoom_s, int port, int adr);
int Cam_Pan_Tilt (int port, int adr, short pan_s, int p_vel, short tilt_s, int t_vel);

#endif /* _CAMERA_H_ */
