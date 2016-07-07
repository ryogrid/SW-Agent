////////////////////  start of the part additionary wroted   /////////////////////////
#include <stdio.h>
#include <stdlib.h>     /* exit() */
#include <string.h>     /* memset(), memcpy() */
#include<sys/time.h> /* gettimeofday() */

#include <cv.h>
#include <highgui.h>
#include <ctype.h>

#include <cxcore.h>
#include "tcp_util.h"

#include "diff_and_countH.h"
#include "diff_count.nsmap"
#include "define.h"

//#define WEBCAM_WIDTH 352
//#define WEBCAM_HEIGHT 288
//
//#define NTSC_WIDTH 640
//#define NTSC_HEIGHT 480

#define SOAP_PROC(a) 	soap_init1(&soap,SOAP_ENC_MTOM); a; soap_end(&soap); soap_done(&soap);

int video_width = -1;
int video_height = -1;

char *rbuf;
int sock;

////////////////////  end of the part additionary wroted   /////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

SOAP_SOURCE_STAMP("@(#) diff_and_countClient.c ver 2.7.11 2008-11-17 18:03:44 GMT")


SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__getCurrentFoundCount(struct soap *soap, const char *soap_endpoint, const char *soap_action, int *result)
{	struct ns__getCurrentFoundCount soap_tmp_ns__getCurrentFoundCount;
	struct ns__getCurrentFoundCountResponse *soap_tmp_ns__getCurrentFoundCountResponse;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost:1024/";
	soap->encodingStyle = "";
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__getCurrentFoundCount(soap, &soap_tmp_ns__getCurrentFoundCount);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__getCurrentFoundCount(soap, &soap_tmp_ns__getCurrentFoundCount, "ns:getCurrentFoundCount", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__getCurrentFoundCount(soap, &soap_tmp_ns__getCurrentFoundCount, "ns:getCurrentFoundCount", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!result)
		return soap_closesock(soap);
	soap_default_int(soap, result);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_tmp_ns__getCurrentFoundCountResponse = soap_get_ns__getCurrentFoundCountResponse(soap, NULL, "ns:getCurrentFoundCountResponse", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (result && soap_tmp_ns__getCurrentFoundCountResponse->result)
		*result = *soap_tmp_ns__getCurrentFoundCountResponse->result;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__changeConditionToFind(struct soap *soap, const char *soap_endpoint, const char *soap_action, int color, int threshold, int *result)
{	struct ns__changeConditionToFind soap_tmp_ns__changeConditionToFind;
	struct ns__changeConditionToFindResponse *soap_tmp_ns__changeConditionToFindResponse;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost:1024/";
	soap->encodingStyle = "";
	soap_tmp_ns__changeConditionToFind.color = color;
	soap_tmp_ns__changeConditionToFind.threshold = threshold;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__changeConditionToFind(soap, &soap_tmp_ns__changeConditionToFind);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__changeConditionToFind(soap, &soap_tmp_ns__changeConditionToFind, "ns:changeConditionToFind", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__changeConditionToFind(soap, &soap_tmp_ns__changeConditionToFind, "ns:changeConditionToFind", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!result)
		return soap_closesock(soap);
	soap_default_int(soap, result);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_tmp_ns__changeConditionToFindResponse = soap_get_ns__changeConditionToFindResponse(soap, NULL, "ns:changeConditionToFindResponse", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (result && soap_tmp_ns__changeConditionToFindResponse->result)
		*result = *soap_tmp_ns__changeConditionToFindResponse->result;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__resetCounter(struct soap *soap, const char *soap_endpoint, const char *soap_action, int *result)
{	struct ns__resetCounter soap_tmp_ns__resetCounter;
	struct ns__resetCounterResponse *soap_tmp_ns__resetCounterResponse;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost:1024/";
	soap->encodingStyle = "";
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__resetCounter(soap, &soap_tmp_ns__resetCounter);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__resetCounter(soap, &soap_tmp_ns__resetCounter, "ns:resetCounter", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__resetCounter(soap, &soap_tmp_ns__resetCounter, "ns:resetCounter", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!result)
		return soap_closesock(soap);
	soap_default_int(soap, result);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_tmp_ns__resetCounterResponse = soap_get_ns__resetCounterResponse(soap, NULL, "ns:resetCounterResponse", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (result && soap_tmp_ns__resetCounterResponse->result)
		*result = *soap_tmp_ns__resetCounterResponse->result;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__getAFrameHexBinary(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct xsd__hexBinary *result)
{	struct ns__getAFrameHexBinary soap_tmp_ns__getAFrameHexBinary;
	struct ns__getAFrameHexBinaryResponse *soap_tmp_ns__getAFrameHexBinaryResponse;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost:1024/";
	soap->encodingStyle = "";
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__getAFrameHexBinary(soap, &soap_tmp_ns__getAFrameHexBinary);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__getAFrameHexBinary(soap, &soap_tmp_ns__getAFrameHexBinary, "ns:getAFrameHexBinary", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__getAFrameHexBinary(soap, &soap_tmp_ns__getAFrameHexBinary, "ns:getAFrameHexBinary", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!result)
		return soap_closesock(soap);
	soap_default_xsd__hexBinary(soap, result);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_tmp_ns__getAFrameHexBinaryResponse = soap_get_ns__getAFrameHexBinaryResponse(soap, NULL, "ns:getAFrameHexBinaryResponse", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (result && soap_tmp_ns__getAFrameHexBinaryResponse->result)
		*result = *soap_tmp_ns__getAFrameHexBinaryResponse->result;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__getAFramebase64Binary(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct xsd__base64Binary *result)
{	struct ns__getAFramebase64Binary soap_tmp_ns__getAFramebase64Binary;
	struct ns__getAFramebase64BinaryResponse *soap_tmp_ns__getAFramebase64BinaryResponse;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost:1024/";
	soap->encodingStyle = "";
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__getAFramebase64Binary(soap, &soap_tmp_ns__getAFramebase64Binary);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__getAFramebase64Binary(soap, &soap_tmp_ns__getAFramebase64Binary, "ns:getAFramebase64Binary", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__getAFramebase64Binary(soap, &soap_tmp_ns__getAFramebase64Binary, "ns:getAFramebase64Binary", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!result)
		return soap_closesock(soap);
	soap_default_xsd__base64Binary(soap, result);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_tmp_ns__getAFramebase64BinaryResponse = soap_get_ns__getAFramebase64BinaryResponse(soap, NULL, "ns:getAFramebase64BinaryResponse", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (result && soap_tmp_ns__getAFramebase64BinaryResponse->result)
		*result = *soap_tmp_ns__getAFramebase64BinaryResponse->result;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__getAFramebaseDimeStream(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct xsd__Dimebase64Binary *result)
{	struct ns__getAFramebaseDimeStream soap_tmp_ns__getAFramebaseDimeStream;
	struct ns__getAFramebaseDimeStreamResponse *soap_tmp_ns__getAFramebaseDimeStreamResponse;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost:1024/";
	soap->encodingStyle = "";
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__getAFramebaseDimeStream(soap, &soap_tmp_ns__getAFramebaseDimeStream);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__getAFramebaseDimeStream(soap, &soap_tmp_ns__getAFramebaseDimeStream, "ns:getAFramebaseDimeStream", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__getAFramebaseDimeStream(soap, &soap_tmp_ns__getAFramebaseDimeStream, "ns:getAFramebaseDimeStream", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!result)
		return soap_closesock(soap);
	soap_default_xsd__Dimebase64Binary(soap, result);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_tmp_ns__getAFramebaseDimeStreamResponse = soap_get_ns__getAFramebaseDimeStreamResponse(soap, NULL, "ns:getAFramebaseDimeStreamResponse", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	if (result && soap_tmp_ns__getAFramebaseDimeStreamResponse->result)
		*result = *soap_tmp_ns__getAFramebaseDimeStreamResponse->result;
	return soap_closesock(soap);
}

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__getAFrameMtom(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct x__mtomBinary *result)
{	struct ns__getAFrameMtom soap_tmp_ns__getAFrameMtom;
	if (!soap_endpoint)
		soap_endpoint = "http://localhost:1024/";
	soap->encodingStyle = "";
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_ns__getAFrameMtom(soap, &soap_tmp_ns__getAFrameMtom);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_ns__getAFrameMtom(soap, &soap_tmp_ns__getAFrameMtom, "ns:getAFrameMtom", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_ns__getAFrameMtom(soap, &soap_tmp_ns__getAFrameMtom, "ns:getAFrameMtom", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!result)
		return soap_closesock(soap);
	soap_default_x__mtomBinary(soap, result);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_x__mtomBinary(soap, result, "x:mtomBinary", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

////////////////////  start of the part additionary wroted   /////////////////////////


/* const char server[] = "http://localhost:1024/"; */
const char server[50];
struct soap soap;

double get_second()
{
  struct timeval  t_tv;
  struct timezone t_tz;
  double time;


  gettimeofday(&t_tv,&t_tz);

  time =  t_tv.tv_sec;
  time   += ((double)(t_tv.tv_usec))/1000000.0;

  return time;
}

///////////////////  Start of  handlers of MTOM(DIME)  ////////////////////////////////

void *dime_write_open(struct soap *soap, const char *id, const char *type, const char *options)
{
//	printf("mtom open!\n");
	return (void*)5; 			/* dumny */
}
void dime_write_close(struct soap *soap, void *handle)
{
//	printf("mtom close!\n");
	/* fclose((FILE*)handle); */
}

IplImage *frame;
long recv_counter_dime_stream = 0;
enum overhead_type {PRIMITIVE, FRAME};
enum transport_type {STREAM,RPC};

double mtom_start_time = 0;
double mtom_read_size_sum=0;
int mtom_division_count = 0;
int mtom_division_sec = 0;
int mtom_ex_count = 0;
double mtom_max_bandwidth=-1;

/* being used for mtom */
int dime_write(struct soap *soap, void *handle, const char *buf, size_t len)
{
	double elapsed_time,tmp_bandwidth;

//	printf("mtom write: %d bytes \n",len);
	memcpy(rbuf,buf,len);
    mtom_read_size_sum += len;
	elapsed_time = get_second() - mtom_start_time;
	if ((elapsed_time > mtom_division_sec)) {
		tmp_bandwidth = ((double) mtom_read_size_sum) / elapsed_time;
		if (tmp_bandwidth > mtom_max_bandwidth) {
			mtom_max_bandwidth = tmp_bandwidth;
		}
		mtom_read_size_sum = 0;
		mtom_division_count++;
		mtom_start_time = get_second();
	}
	if (mtom_division_count > mtom_ex_count) {
/* 		printf("max bandwidth=%10.10f Mbps", mtom_max_bandwidth * 8 / (1024.0 */
		printf("max bandwidth=%lf Mbps", mtom_max_bandwidth * 8 / (1024.0
				* 1024.0));
		exit(1);
	}
	//  recv_counter_dime_stream+=len;

	return SOAP_OK;
}

///////////////////  End  of  handlers of MTOM(DIME)  ////////////////////////////////

void get_frame_base64Binary(IplImage *new_frame){
  struct xsd__base64Binary result;

  soap_call_ns__getAFramebase64Binary(&soap,server,"",&result);
  if (soap.error){
    soap_print_fault(&soap, stderr);
    exit(1);
  }else{
    memcpy(new_frame->imageData,result.__ptr,FRAME_SIZE);
  }
}

void start_mtom(){
  struct x__mtomBinary result;

  soap_init1(&soap,SOAP_ENC_MTOM);
  /* for MTOM streaming */
  soap.fmimewriteopen = dime_write_open;
  soap.fmimewriteclose = dime_write_close;
  soap.fmimewrite = dime_write;
  soap_call_ns__getAFrameMtom(&soap,server,"",&result);
  soap_end(&soap);
  soap_done(&soap);
}

void connect_with_stream_IF(){
  char *server_host_stream =  strtok(server,":");
  int portno = 1234;

  sock = tcp_connect( server, portno );
  if( sock < 0 ){
	  printf("connect to %s:%d failed\n",server_host_stream,portno);
	  exit( -1 );
  }else{
	  printf("connect to %s:%d succeeded\n",server_host_stream,portno);
  }
}

void eval_overhead(enum overhead_type otype, int count){
	int i,int_result;
	struct xsd__base64Binary base64_result;
	double start,elapsed_time;

	if(otype == PRIMITIVE){
		printf("eval_overhead#PRIMITIVE\n");
		SOAP_PROC(soap_call_ns__changeConditionToFind(&soap,server,"",SET_EX_TYPE,OverheadPrimitive,&int_result));
	}else if(otype == FRAME){
		printf("set_width: %d\n",video_width);
	    SOAP_PROC(soap_call_ns__changeConditionToFind(&soap,server,"",SET_IMAGE_WIDTH,video_width,&int_result));
		printf("set_height: %d\n",video_height);
		SOAP_PROC(soap_call_ns__changeConditionToFind(&soap,server,"",SET_IMAGE_HEIGHT,video_height,&int_result));
//		if (soap.error){
//						    soap_print_fault(&soap, stderr);
//		}

		SOAP_PROC(soap_call_ns__changeConditionToFind(&soap,server,"",SET_EX_TYPE,OverheadFrame,&int_result));
		printf("set_ex_time\n");

		printf("eval_overhead#FRAME\n");
	}

	start = get_second();
	for(i=0; i < count; i++){
		if(otype == PRIMITIVE){
			SOAP_PROC(soap_call_ns__resetCounter(&soap,server,"",&int_result));
		}else if(otype == FRAME){
			SOAP_PROC(soap_call_ns__getAFramebase64Binary(&soap,server,"",&base64_result));
		}
	}

	elapsed_time = get_second() - start;
	printf("elapsed time: total(%d times) =%3.10lf avrage=%3.10lf\n",count,elapsed_time,(elapsed_time / (double)count));
}

void eval_bandwidth(enum transport_type ttype,int ex_count,int division_sec,int buffer_size){
	int int_result;
	double read_size_sum = 0;
	int read_size;
	int division_count=0;
	double start_time=0,elapsed_time;
	double max_bandwidth = 0, tmp_bandwidth;

	if(ttype == STREAM){
		printf("set_width: %d\n",video_width);
	    SOAP_PROC(soap_call_ns__changeConditionToFind(&soap,server,"",SET_IMAGE_WIDTH,video_width,&int_result));
		printf("set_height: %d\n",video_height);
		SOAP_PROC(soap_call_ns__changeConditionToFind(&soap,server,"",SET_IMAGE_HEIGHT,video_height,&int_result));
		printf("set_buffer_size_for_stream_interface: %d\n",buffer_size);
		if(buffer_size != -1){
			SOAP_PROC(soap_call_ns__changeConditionToFind(&soap,server,"",SET_BUFFER_SIZE_FOR_STREAM_INTERFACE,buffer_size,&int_result));
		}
		printf("eval_overhead#STREAM\n");
		SOAP_PROC(soap_call_ns__changeConditionToFind(&soap,server,"",SET_EX_TYPE,BandwidthStream,&int_result));
		printf("start stream write\n");
		SOAP_PROC(soap_call_ns__changeConditionToFind(&soap,server,"",START_WRITE_TO_STREAM,1,&int_result));

   	   sleep(1);
	   connect_with_stream_IF();
	   start_time = get_second();
	   rbuf = (char *) malloc(sizeof(char)*buffer_size);
	   if(rbuf == NULL){
		   fprintf(stderr, "allocation by malloc haven't succeeded\n");
	   }
   	   while(division_count < ex_count){
   		   read_size_sum += (read_size = read(sock,rbuf,buffer_size));
   		   elapsed_time = get_second() - start_time;
   		   if((elapsed_time > division_sec)){
   			  tmp_bandwidth = ((double)read_size_sum) / elapsed_time;
   			  if(tmp_bandwidth > max_bandwidth){
   				  max_bandwidth = tmp_bandwidth;
   			  }
   			  read_size_sum = 0;
   			  division_count++;
   			  start_time = get_second();
   		   }
   	   }
   	   printf("max bandwidth=%10.10f Mbps", max_bandwidth*8 / (1024.0*1024.0) );
   	   close(sock);
	}else if(ttype == RPC){
		printf("set_width: %d\n",video_width);
	    SOAP_PROC(soap_call_ns__changeConditionToFind(&soap,server,"",SET_IMAGE_WIDTH,video_width,&int_result));
		printf("set_height: %d\n",video_height);
		SOAP_PROC(soap_call_ns__changeConditionToFind(&soap,server,"",SET_IMAGE_HEIGHT,video_height,&int_result));
		printf("eval_bandwidth#RPC\n");
		SOAP_PROC(soap_call_ns__changeConditionToFind(&soap,server,"",SET_EX_TYPE,BandwidthRPC,&int_result));

		mtom_ex_count = ex_count;
		mtom_division_sec = division_sec;
		mtom_start_time = get_second();
		mtom_max_bandwidth = -1;
		rbuf = (char *) malloc(sizeof(char)*RPC_RECIEV_BUFFER_SIZE);
		start_mtom();
	}
}

void find_host(int argc,char** argv,char *host){
  int i;
  for(i=1;i<argc;i++){
    if(strcmp(argv[i],"-dest") == 0){
      if(i < (argc-1)){
    	  strcpy(host,argv[i+1]);
		  printf("destination host: %s\n",host);
		  return;
      }else{
    	  printf("please append destination \"host:port\"\n");
		  exit(-1);
      }
    }
  }
}

/* get integer from argv */
int get_count(int index,char **argv){
  return atoi(argv[index]);
}

extern void sigpipe_handler();

void sigpipe_handler(){
}

int main (int argc, char **argv){
  int ex_count;
  int division_sec;
  int buffer_size;

    signal(SIGPIPE,sigpipe_handler);

    if(argc == 1){ 		/* print usage */
      printf("usage: ./diff_and_count_bench_client <evaluation type> [some params ...] -dest <host:port>\n");
      printf("*************************evaluation types*******************************\n");
      printf("     -eval_overhead_primitive <experiment count> ......\n");
      printf("     -eval_overhead_frame <experiment count> <frame_width> <frame_height>......\n");
      printf("     -eval_bandwidth_stream <experiment count> <division_sec> <frame_width> <frame_height> <buffer_size>......\n");
      printf("     -eval_bandwidth_rpc <experiment count> <division_sec> <frame_width> <frame_height> ......\n");
      printf("***************************************************************************\n");
	  exit(1);
    }else{
      if (strcmp(argv[1], "eval_overhead_primitive") == 0) {
    	 find_host(argc, argv, server);
		 ex_count = get_count(2, argv);
		 eval_overhead(PRIMITIVE,ex_count);
      } else if(strcmp(argv[1],"eval_overhead_frame") == 0) {
    	  find_host(argc,argv,server);
    	  ex_count = get_count(2, argv);
    	  video_width = get_count(3,argv);
    	  video_height = get_count(4,argv);
    	  printf("video width: %d, video height: %d\n",video_width,video_height);
    	  eval_overhead(FRAME,ex_count);
      } else if(strcmp(argv[1],"eval_bandwidth_stream") == 0) {
    	  find_host(argc,argv,server);
    	  ex_count = get_count(2, argv);
    	  division_sec = get_count(3,argv);
    	  video_width = get_count(4,argv);
    	  video_height = get_count(5,argv);
    	  buffer_size = get_count(6, argv);
    	  printf("experiment count:%d, division sec:%d\n",ex_count,division_sec);
    	  printf("buffer size: %d\n",buffer_size);
    	  eval_bandwidth(STREAM,ex_count,division_sec,buffer_size);
      } else if(strcmp(argv[1],"eval_bandwidth_rpc") == 0) {
    	  find_host(argc,argv,server);
    	  ex_count = get_count(2, argv);
    	  division_sec = get_count(3,argv);
    	  video_width = get_count(4,argv);
    	  video_height = get_count(5,argv);
    	  eval_bandwidth(RPC,ex_count,division_sec,-1);
      } else {
    	  printf("unkown benchmark!\n");
    	  exit(-1);
	  }
    }

    return 0;
}

////////////////////  end of the part additionary wroted   /////////////////////////

#ifdef __cplusplus
}
#endif

/* End of diff_and_countClient.c */
