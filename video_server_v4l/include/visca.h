/*
 * visca.h
 */
//////////////////////////////////////////////////////////
// Modify List
// -------------------------------------------------------
// + Add some value for controling WhiteBalance IK20031031
//////////////////////////////////////////////////////////


#ifndef _VISCA_H_
#define _VISCA_H_

#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>

#ifndef 	TRUE
//#define 	TRUE 	(1)
//#define		FALSE	(0)
#endif /* TRUE */

/* define max size */
#define		VS_MAXDEVICE	7
#define		VS_MAXMSG	14
#define		VS_MAXPACKET	16

/* terminator of packet */
#define		VS_TERM		0xff

/* format type of message header */
#define		VS_RAWMODE	0x00
#define		VS_COMMAND1	0x01
#define		VS_COMMAND2   	0x02
#define		VS_COMMAND3   	0x03
#define		VS_COMMAND4  	0x04
#define		VS_INQUIRY      0x09
#define		VS_CLEAR        0x00
#define		VS_CANCEL   	0x20
#define		VS_ADDRESS   	0x30
#define		VS_ACK   	0x40
#define		VS_COMP         0x50
#define		VS_ERROR  	0x60
#define		VS_NETCHANGE   	0x38

/* broadcast address */
#define 	VS_BROADCAST 	0x00

/* category code */
#define 	VS_INTERFACE 	0x00
#define		VS_CONTROL_S    0x01
#define		VS_MEDIA_DEVICE 0x02
#define		VS_SWITCHER     0x03
#define		VS_CAMERA	0x04
#define		VS_PANTILT	0x06

#define		VS_VENDER 	0x7f

/* pan-tilt type */
#define		CAM_NORMAL	0x01
#define		CAM_ABS_POINT	0x02
#define		CAM_REL_POINT	0x03

/* couter type */
#define		VS_TOP_MID_END	0x01
#define		VS_4_DIGIT 	0x11
#define		VS_HMS		0x12
#define		VS_TIME_CODE 	0x21

/* white blance type */
#define		VS_WB		0x35
#define		VS_AUTO		0x00
#define		VS_INDOOR      	0x01
#define		VS_OUTDOOR    	0x02
#define		VS_ONEPUSH	0x03
#define		VS_ATW		0x04
#define		VS_MANUAL      	0x05

/* AE type */
#define		VS_AE			0x39
#define		VS_AE_AUTO      	0x00
#define		VS_AE_MANUAL    	0x03
#define		VS_AE_SHTR_PRY      	0x0A
#define		VS_AE_IRIS_PRY      	0x0B
#define		VS_AE_GAIN_PRY      	0x0C
#define		VS_AE_BRIGHT      	0x0D
#define		VS_AE_SHTR_AUTO      	0x1A
#define		VS_AE_IRIS_AUTO      	0x1B
#define		VS_AE_GAIN_AUTO      	0x1C

/* FOCUS type */
#define		VS_FOCUS_AUTO		0x02
#define		VS_FOCUS_MANU		0x03

/*
 * define structure of visca message
 */

typedef	struct vs_msg {
    unsigned char 	format_type;
    unsigned char 	category;
    unsigned char 	format_info[5];
    unsigned char 	body[VS_MAXMSG +1];
} vs_msg;

typedef		long vs_mid;

/*
 * global variable for visca error code and error defines 
 */

int 	vs_error;

#define		VS_ER_NETCHANGE	1	/* Visca network changed */
#define		VS_ER_RAWIO	2	/* I/O error */
#define		VS_ER_MEMORY	3	/* Can't alloc memory */
#define		VS_ER_INVALID	4	/* Invalid argument */
#define		VS_ER_REPLY	5	/* Illegal reply message */
#define		VS_ER_INITVISCA	6 	/* Fail to initialize visca */

/*
 *	visca functions
 */

int pack_visca_num(short num, unsigned char* buf);
short unpack_visca_num(unsigned char* buf);

int msglen(unsigned char* msg);
int visca_send_command_raw (int port, vs_msg message);
unsigned char serial_getc(int port);
int visca_read_message(int port, unsigned char* buf);
unsigned char visca_send_command_ack (int port, vs_msg message);
unsigned char visca_send_command_complete (int port, vs_msg message);
unsigned char visca_send_command_complete_without_ack(int port, vs_msg message);
int visca_open (char *line);
int visca_close(int port);
int visca_assign_address(int fd);
int visca_if_clear(int fd);
int visca_if_clear_all(int fd);

#endif /* _VISCA_H_ */

