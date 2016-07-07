////////////////////  start of the part additionary wroted   /////////////////////////

#include "diff_and_countH.h"
#include "diff_count.nsmap"

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include <linux/types.h>
#include <linux/videodev.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>		// for thread programming

#include "define.h"
#include "camera.h"
#include <highgui.h>

CAM_ATTR *video; // for cap_video
int c_port[CAMERA_NUM];

extern int ObjectColorThreshold;
extern int ObjectCount;
extern int ToFindColor;

extern  IplImage *imgMask;
extern  IplImage *imgSrc;

int video_width = -1;
int video_height = -1;
int buffer_size_for_stream_interface = -1;

/////////////////////// start of flags for benchmark ///////////////////////

int do_image_process = FALSE;
int do_video_read = FALSE;
int do_using_stream_interface = FALSE; /* processing request of connection, writing data to interface */

enum exType experiment_type;
enum videoType vtype;

/////////////////////// end of flags for benchmark   ///////////////////////

/* #define FRAME_SIZE video_width*video_height*3; */
#define DUMMY 0xffffff

#ifdef __cplusplus
extern "C" {
#endif

SOAP_SOURCE_STAMP("@(#) diff_and_countServer.c ver 2.7.11 2008-10-13 07:20:39 GMT")

void data_write(){
 int wrote_bytes;
//  int wrote_bytes_sum = 0;

//  while((wrote_bytes = write(-1,(imgSrc->imageData)+wrote_bytes_sum,video_width*video_height*3 - wrote_bytes_sum)) != 0){
//    wrote_bytes_sum += wrote_bytes;
//  }
  while((wrote_bytes = write(-1,imgSrc->imageData,buffer_size_for_stream_interface)) != 0){
  }
}

int ns__getCurrentFoundCount(struct soap* soap,int *result){
  *result = ObjectCount;
  return SOAP_OK;
}

int ns__changeConditionToFind(struct soap* soap,int color,int threshold,int *result){
 char ex_type_str[50];

  switch(color){
 case SET_EX_TYPE: 				/* set experiment type */
   experiment_type = threshold;

   switch(threshold){
   case OverheadPrimitive:
     strcpy(ex_type_str,"OverheadPrimitive\n");
     break;
   case OverheadFrame:
     strcpy(ex_type_str,"OverheadFrame\n");
     imgSrc		= cvCreateImageHeader( cvSize( video_width, video_height),  IPL_DEPTH_8U, 3);
     if ( (imgSrc->imageData = (unsigned char *)malloc(sizeof(unsigned char)*FRAME_SIZE) )==NULL){
       fprintf(stderr,"Error:Can't allocate memory\n");
       exit(1);
     }
     break;
   case BandwidthStream:
     strcpy(ex_type_str,"BandwidthStream\n");
     imgSrc		= cvCreateImageHeader( cvSize( video_width, video_height),  IPL_DEPTH_8U, 3);
     if ( (imgSrc->imageData = (unsigned char *)malloc(sizeof(unsigned char)*FRAME_SIZE) )==NULL){
       fprintf(stderr,"Error:Can't allocate memory\n");
       exit(1);
     }
     break;
   case BandwidthRPC:
     strcpy(ex_type_str,"BandwidthRPC\n");
     imgSrc		= cvCreateImageHeader( cvSize( video_width, video_height),  IPL_DEPTH_8U, 3);
     if ( (imgSrc->imageData = (unsigned char *)malloc(sizeof(unsigned char)*FRAME_SIZE) )==NULL){
       fprintf(stderr,"Error:Can't allocate memory\n");
       exit(1);
     }
     break;
   default:
     strcpy(ex_type_str,"unknown experiment type\n");
   }

   printf("Set Experiment Type: %s\n",ex_type_str);
   fflush(stdout);
   break;

 case SET_IMAGE_HEIGHT:				/* set video height */
   video_height = threshold;
   printf("set_height: %d\n",video_height);
   break;
 case SET_IMAGE_WIDTH:				/* set video width */
   video_width = threshold;
   printf("set width: %d\n",video_width);
   break;
 case START_VIDEO_READ:				/* start reading of video data */
   do_video_read = TRUE;
   init_video();
   break;
 case START_IMAGE_PROCESS:		        /* start image processing */
   do_image_process = TRUE;
   break;
 case SET_VIDEO_TYPE:
   vtype = threshold;
   break;
 case START_WRITE_TO_STREAM:
  do_using_stream_interface = TRUE;
  break;
 case SET_BUFFER_SIZE_FOR_STREAM_INTERFACE:
  buffer_size_for_stream_interface = threshold;
  printf("set buffer size form stream interface: %d\n",buffer_size_for_stream_interface);
  break;
 default:
   printf("unkown operation code!\n");
   exit(1);
 }

/*   ToFindColor=color; */
/*   ObjectColorThreshold=threshold; */
  *result = 1;
  return SOAP_OK;
}

int ns__resetCounter(struct soap* soap,int *result){
  ObjectCount = 0;
  *result = 1;
  return SOAP_OK;
}

int ns__getAFrameHexBinary(struct soap* soap,struct xsd__hexBinary *result){
  printf("Called getAFrameHexBinary\n");
  result->__ptr = imgSrc->imageData;
  result->__size = FRAME_SIZE;

  return SOAP_OK;
}

int ns__getAFramebase64Binary(struct soap* soap,struct xsd__base64Binary *result){
//  printf("Called getAFramebase64Binary\n");
  result->__ptr = imgSrc->imageData;
  result->__size = FRAME_SIZE;

  return SOAP_OK;
}

int send_counter_dime_stream=0;

int ns__getAFramebaseDimeStream(struct soap* soap,struct xsd__Dimebase64Binary *result){
  char id[100];
  printf("Called getAFramebaseDimeStream\n");

  result->__ptr = (unsigned char*)5; /* dummy */
  result->__size = 0; 		/* for dime stream */

  result->id = NULL;
  result->type = "image/jpeg";

  return SOAP_OK;
}

int ns__getAFrameMtom(struct soap* soap,struct x__mtomBinary *result){
  char id[100];
  printf("Called getAFrameMtom\n");

  result->xop__Include.__ptr = (unsigned char*)5; /* dummy */
  result->xop__Include.__size = 0; 		/* for dime stream */
  result->xop__Include.id = NULL;
  result->xop__Include.type = "image/jpeg";

  return SOAP_OK;
}

////////////////////// handlers for DIME streaming ///////////////////////////

void *dime_read_open(struct soap *soap, void *handle, const char *id, const char *type, const char *options)
{
  // we should return NULL without setting soap->error if we don't want to use the streaming callback for this DIME attachment. The handle contains the non-NULL __ptr field value which should have been set in the application.
  // return value of this function will be passed on to the fdimeread and fdimereadclose callbacks. The return value will not affect the __ptr field.
/*   return handle; */
  return handle; 			/* dummy */
}

void dime_read_close(struct soap *soap, void *handle)
{
/* fclose((FILE*)handle); */
}

size_t dime_read(struct soap *soap, void *handle, char *buf, size_t len)
{
  int ret;

//  printf("dime read!\n");
  memcpy(buf,imgSrc->imageData,len);
  return len;
}

////////////////////  end of the part additionary wroted   /////////////////////////

SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap *soap)
{
#ifndef WITH_FASTCGI
	unsigned int k = soap->max_keep_alive;
#endif

	do
	{
#ifdef WITH_FASTCGI
		if (FCGI_Accept() < 0)
		{
			soap->error = SOAP_EOF;
			return soap_send_fault(soap);
		}
#endif

		soap_begin(soap);

#ifndef WITH_FASTCGI
		if (soap->max_keep_alive > 0 && !--k)
			soap->keep_alive = 0;
#endif

		if (soap_begin_recv(soap))
		{	if (soap->error < SOAP_STOP)
			{
#ifdef WITH_FASTCGI
				soap_send_fault(soap);
#else
				return soap_send_fault(soap);
#endif
			}
			soap_closesock(soap);

			continue;
		}

		if (soap_envelope_begin_in(soap)
		 || soap_recv_header(soap)
		 || soap_body_begin_in(soap)
		 || soap_serve_request(soap)
		 || (soap->fserveloop && soap->fserveloop(soap)))
		{
#ifdef WITH_FASTCGI
			soap_send_fault(soap);
#else
			return soap_send_fault(soap);
#endif
		}

#ifdef WITH_FASTCGI
		soap_destroy(soap);
		soap_end(soap);
	} while (1);
#else
	} while (soap->keep_alive);
#endif
	return SOAP_OK;
}

#ifndef WITH_NOSERVEREQUEST
SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap *soap)
{
	soap_peek_element(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:getCurrentFoundCount"))
		return soap_serve_ns__getCurrentFoundCount(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:changeConditionToFind"))
		return soap_serve_ns__changeConditionToFind(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:resetCounter"))
		return soap_serve_ns__resetCounter(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:getAFrameHexBinary"))
		return soap_serve_ns__getAFrameHexBinary(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:getAFramebase64Binary"))
		return soap_serve_ns__getAFramebase64Binary(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:getAFramebaseDimeStream"))
		return soap_serve_ns__getAFramebaseDimeStream(soap);
	if (!soap_match_tag(soap, soap->tag, "ns:getAFrameMtom"))
		return soap_serve_ns__getAFrameMtom(soap);
	return soap->error = SOAP_NO_METHOD;
}
#endif

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__getCurrentFoundCount(struct soap *soap)
{	struct ns__getCurrentFoundCount soap_tmp_ns__getCurrentFoundCount;
	struct ns__getCurrentFoundCountResponse soap_tmp_ns__getCurrentFoundCountResponse;
	int soap_tmp_int;
	soap_default_ns__getCurrentFoundCountResponse(soap, &soap_tmp_ns__getCurrentFoundCountResponse);
	soap_default_int(soap, &soap_tmp_int);
	soap_tmp_ns__getCurrentFoundCountResponse.result = &soap_tmp_int;
	soap_default_ns__getCurrentFoundCount(soap, &soap_tmp_ns__getCurrentFoundCount);
	soap->encodingStyle = "";
	if (!soap_get_ns__getCurrentFoundCount(soap, &soap_tmp_ns__getCurrentFoundCount, "ns:getCurrentFoundCount", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__getCurrentFoundCount(soap, &soap_tmp_int);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__getCurrentFoundCountResponse(soap, &soap_tmp_ns__getCurrentFoundCountResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__getCurrentFoundCountResponse(soap, &soap_tmp_ns__getCurrentFoundCountResponse, "ns:getCurrentFoundCountResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__getCurrentFoundCountResponse(soap, &soap_tmp_ns__getCurrentFoundCountResponse, "ns:getCurrentFoundCountResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__changeConditionToFind(struct soap *soap)
{	struct ns__changeConditionToFind soap_tmp_ns__changeConditionToFind;
	struct ns__changeConditionToFindResponse soap_tmp_ns__changeConditionToFindResponse;
	int soap_tmp_int;
	soap_default_ns__changeConditionToFindResponse(soap, &soap_tmp_ns__changeConditionToFindResponse);
	soap_default_int(soap, &soap_tmp_int);
	soap_tmp_ns__changeConditionToFindResponse.result = &soap_tmp_int;
	soap_default_ns__changeConditionToFind(soap, &soap_tmp_ns__changeConditionToFind);
	soap->encodingStyle = "";
	if (!soap_get_ns__changeConditionToFind(soap, &soap_tmp_ns__changeConditionToFind, "ns:changeConditionToFind", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__changeConditionToFind(soap, soap_tmp_ns__changeConditionToFind.color, soap_tmp_ns__changeConditionToFind.threshold, &soap_tmp_int);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__changeConditionToFindResponse(soap, &soap_tmp_ns__changeConditionToFindResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__changeConditionToFindResponse(soap, &soap_tmp_ns__changeConditionToFindResponse, "ns:changeConditionToFindResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__changeConditionToFindResponse(soap, &soap_tmp_ns__changeConditionToFindResponse, "ns:changeConditionToFindResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__resetCounter(struct soap *soap)
{	struct ns__resetCounter soap_tmp_ns__resetCounter;
	struct ns__resetCounterResponse soap_tmp_ns__resetCounterResponse;
	int soap_tmp_int;
	soap_default_ns__resetCounterResponse(soap, &soap_tmp_ns__resetCounterResponse);
	soap_default_int(soap, &soap_tmp_int);
	soap_tmp_ns__resetCounterResponse.result = &soap_tmp_int;
	soap_default_ns__resetCounter(soap, &soap_tmp_ns__resetCounter);
	soap->encodingStyle = "";
	if (!soap_get_ns__resetCounter(soap, &soap_tmp_ns__resetCounter, "ns:resetCounter", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__resetCounter(soap, &soap_tmp_int);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__resetCounterResponse(soap, &soap_tmp_ns__resetCounterResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__resetCounterResponse(soap, &soap_tmp_ns__resetCounterResponse, "ns:resetCounterResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__resetCounterResponse(soap, &soap_tmp_ns__resetCounterResponse, "ns:resetCounterResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__getAFrameHexBinary(struct soap *soap)
{	struct ns__getAFrameHexBinary soap_tmp_ns__getAFrameHexBinary;
	struct ns__getAFrameHexBinaryResponse soap_tmp_ns__getAFrameHexBinaryResponse;
	struct xsd__hexBinary soap_tmp_xsd__hexBinary;
	soap_default_ns__getAFrameHexBinaryResponse(soap, &soap_tmp_ns__getAFrameHexBinaryResponse);
	soap_default_xsd__hexBinary(soap, &soap_tmp_xsd__hexBinary);
	soap_tmp_ns__getAFrameHexBinaryResponse.result = &soap_tmp_xsd__hexBinary;
	soap_default_ns__getAFrameHexBinary(soap, &soap_tmp_ns__getAFrameHexBinary);
	soap->encodingStyle = "";
	if (!soap_get_ns__getAFrameHexBinary(soap, &soap_tmp_ns__getAFrameHexBinary, "ns:getAFrameHexBinary", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__getAFrameHexBinary(soap, &soap_tmp_xsd__hexBinary);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__getAFrameHexBinaryResponse(soap, &soap_tmp_ns__getAFrameHexBinaryResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__getAFrameHexBinaryResponse(soap, &soap_tmp_ns__getAFrameHexBinaryResponse, "ns:getAFrameHexBinaryResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__getAFrameHexBinaryResponse(soap, &soap_tmp_ns__getAFrameHexBinaryResponse, "ns:getAFrameHexBinaryResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__getAFramebase64Binary(struct soap *soap)
{	struct ns__getAFramebase64Binary soap_tmp_ns__getAFramebase64Binary;
	struct ns__getAFramebase64BinaryResponse soap_tmp_ns__getAFramebase64BinaryResponse;
	struct xsd__base64Binary soap_tmp_xsd__base64Binary;
	soap_default_ns__getAFramebase64BinaryResponse(soap, &soap_tmp_ns__getAFramebase64BinaryResponse);
	soap_default_xsd__base64Binary(soap, &soap_tmp_xsd__base64Binary);
	soap_tmp_ns__getAFramebase64BinaryResponse.result = &soap_tmp_xsd__base64Binary;
	soap_default_ns__getAFramebase64Binary(soap, &soap_tmp_ns__getAFramebase64Binary);
	soap->encodingStyle = "";
	if (!soap_get_ns__getAFramebase64Binary(soap, &soap_tmp_ns__getAFramebase64Binary, "ns:getAFramebase64Binary", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__getAFramebase64Binary(soap, &soap_tmp_xsd__base64Binary);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__getAFramebase64BinaryResponse(soap, &soap_tmp_ns__getAFramebase64BinaryResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__getAFramebase64BinaryResponse(soap, &soap_tmp_ns__getAFramebase64BinaryResponse, "ns:getAFramebase64BinaryResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__getAFramebase64BinaryResponse(soap, &soap_tmp_ns__getAFramebase64BinaryResponse, "ns:getAFramebase64BinaryResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__getAFramebaseDimeStream(struct soap *soap)
{	struct ns__getAFramebaseDimeStream soap_tmp_ns__getAFramebaseDimeStream;
	struct ns__getAFramebaseDimeStreamResponse soap_tmp_ns__getAFramebaseDimeStreamResponse;
	struct xsd__Dimebase64Binary soap_tmp_xsd__Dimebase64Binary;
	soap_default_ns__getAFramebaseDimeStreamResponse(soap, &soap_tmp_ns__getAFramebaseDimeStreamResponse);
	soap_default_xsd__Dimebase64Binary(soap, &soap_tmp_xsd__Dimebase64Binary);
	soap_tmp_ns__getAFramebaseDimeStreamResponse.result = &soap_tmp_xsd__Dimebase64Binary;
	soap_default_ns__getAFramebaseDimeStream(soap, &soap_tmp_ns__getAFramebaseDimeStream);
	soap->encodingStyle = "";
	if (!soap_get_ns__getAFramebaseDimeStream(soap, &soap_tmp_ns__getAFramebaseDimeStream, "ns:getAFramebaseDimeStream", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__getAFramebaseDimeStream(soap, &soap_tmp_xsd__Dimebase64Binary);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_ns__getAFramebaseDimeStreamResponse(soap, &soap_tmp_ns__getAFramebaseDimeStreamResponse);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__getAFramebaseDimeStreamResponse(soap, &soap_tmp_ns__getAFramebaseDimeStreamResponse, "ns:getAFramebaseDimeStreamResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__getAFramebaseDimeStreamResponse(soap, &soap_tmp_ns__getAFramebaseDimeStreamResponse, "ns:getAFramebaseDimeStreamResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__getAFrameMtom(struct soap *soap)
{	struct ns__getAFrameMtom soap_tmp_ns__getAFrameMtom;
	struct x__mtomBinary result;
	soap_default_x__mtomBinary(soap, &result);
	soap_default_ns__getAFrameMtom(soap, &soap_tmp_ns__getAFrameMtom);
	soap->encodingStyle = "";
	if (!soap_get_ns__getAFrameMtom(soap, &soap_tmp_ns__getAFrameMtom, "ns:getAFrameMtom", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = ns__getAFrameMtom(soap, &result);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	soap_serialize_x__mtomBinary(soap, &result);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_x__mtomBinary(soap, &result, "x:mtomBinary", "")
		 || soap_body_end_out(soap)

		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_x__mtomBinary(soap, &result, "x:mtomBinary", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}

#ifdef __cplusplus
}
#endif

/* End of diff_and_countServer.c */
