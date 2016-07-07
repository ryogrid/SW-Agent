/* soapH.h
   Generated by gSOAP 2.7.11 from diff_count.h
   Copyright(C) 2000-2008, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#ifndef soapH_H
#define soapH_H
#include "soapStub.h"
#ifndef WITH_NOIDREF

#ifdef __cplusplus
extern "C" {
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_markelement(struct soap*, const void*, int);
SOAP_FMAC3 int SOAP_FMAC4 soap_putelement(struct soap*, const void*, const char*, int, int);
SOAP_FMAC3 void *SOAP_FMAC4 soap_getelement(struct soap*, int*);

#ifdef __cplusplus
}
#endif
SOAP_FMAC3 int SOAP_FMAC4 soap_putindependent(struct soap*);
SOAP_FMAC3 int SOAP_FMAC4 soap_getindependent(struct soap*);
#endif
SOAP_FMAC3 int SOAP_FMAC4 soap_ignore_element(struct soap*);

SOAP_FMAC3 void * SOAP_FMAC4 soap_instantiate(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 int SOAP_FMAC4 soap_fdelete(struct soap_clist*);
SOAP_FMAC3 void* SOAP_FMAC4 soap_class_id_enter(struct soap*, const char*, void*, int, size_t, const char*, const char*);

#ifndef SOAP_TYPE_byte
#define SOAP_TYPE_byte (3)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_byte(struct soap*, char *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_byte(struct soap*, const char *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_byte(struct soap*, const char*, int, const char *, const char*);
SOAP_FMAC3 char * SOAP_FMAC4 soap_get_byte(struct soap*, char *, const char*, const char*);
SOAP_FMAC3 char * SOAP_FMAC4 soap_in_byte(struct soap*, const char*, char *, const char*);

#ifndef SOAP_TYPE_int
#define SOAP_TYPE_int (1)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_int(struct soap*, int *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_int(struct soap*, const int *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_int(struct soap*, const char*, int, const int *, const char*);
SOAP_FMAC3 int * SOAP_FMAC4 soap_get_int(struct soap*, int *, const char*, const char*);
SOAP_FMAC3 int * SOAP_FMAC4 soap_in_int(struct soap*, const char*, int *, const char*);

#ifndef SOAP_TYPE_unsignedByte
#define SOAP_TYPE_unsignedByte (9)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_unsignedByte(struct soap*, unsigned char *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_unsignedByte(struct soap*, const unsigned char *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_unsignedByte(struct soap*, const char*, int, const unsigned char *, const char*);
SOAP_FMAC3 unsigned char * SOAP_FMAC4 soap_get_unsignedByte(struct soap*, unsigned char *, const char*, const char*);
SOAP_FMAC3 unsigned char * SOAP_FMAC4 soap_in_unsignedByte(struct soap*, const char*, unsigned char *, const char*);

#ifndef SOAP_TYPE_unsignedInt
#define SOAP_TYPE_unsignedInt (8)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_unsignedInt(struct soap*, unsigned int *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_unsignedInt(struct soap*, const unsigned int *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_unsignedInt(struct soap*, const char*, int, const unsigned int *, const char*);
SOAP_FMAC3 unsigned int * SOAP_FMAC4 soap_get_unsignedInt(struct soap*, unsigned int *, const char*, const char*);
SOAP_FMAC3 unsigned int * SOAP_FMAC4 soap_in_unsignedInt(struct soap*, const char*, unsigned int *, const char*);

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (42)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Fault(struct soap*, struct SOAP_ENV__Fault *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Fault(struct soap*, const struct SOAP_ENV__Fault *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Fault(struct soap*, const struct SOAP_ENV__Fault *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Fault(struct soap*, const char*, int, const struct SOAP_ENV__Fault *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Fault * SOAP_FMAC4 soap_get_SOAP_ENV__Fault(struct soap*, struct SOAP_ENV__Fault *, const char*, const char*);
SOAP_FMAC3 struct SOAP_ENV__Fault * SOAP_FMAC4 soap_in_SOAP_ENV__Fault(struct soap*, const char*, struct SOAP_ENV__Fault *, const char*);
SOAP_FMAC5 struct SOAP_ENV__Fault * SOAP_FMAC6 soap_new_SOAP_ENV__Fault(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_SOAP_ENV__Fault(struct soap*, struct SOAP_ENV__Fault*);
SOAP_FMAC3 struct SOAP_ENV__Fault * SOAP_FMAC4 soap_instantiate_SOAP_ENV__Fault(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_SOAP_ENV__Fault(struct soap*, int, int, void*, size_t, const void*, size_t);

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (41)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Reason(struct soap*, const struct SOAP_ENV__Reason *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Reason(struct soap*, const struct SOAP_ENV__Reason *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Reason(struct soap*, const char*, int, const struct SOAP_ENV__Reason *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Reason * SOAP_FMAC4 soap_get_SOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason *, const char*, const char*);
SOAP_FMAC3 struct SOAP_ENV__Reason * SOAP_FMAC4 soap_in_SOAP_ENV__Reason(struct soap*, const char*, struct SOAP_ENV__Reason *, const char*);
SOAP_FMAC5 struct SOAP_ENV__Reason * SOAP_FMAC6 soap_new_SOAP_ENV__Reason(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_SOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason*);
SOAP_FMAC3 struct SOAP_ENV__Reason * SOAP_FMAC4 soap_instantiate_SOAP_ENV__Reason(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_SOAP_ENV__Reason(struct soap*, int, int, void*, size_t, const void*, size_t);

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (38)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Detail(struct soap*, const struct SOAP_ENV__Detail *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Detail(struct soap*, const struct SOAP_ENV__Detail *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Detail(struct soap*, const char*, int, const struct SOAP_ENV__Detail *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Detail * SOAP_FMAC4 soap_get_SOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail *, const char*, const char*);
SOAP_FMAC3 struct SOAP_ENV__Detail * SOAP_FMAC4 soap_in_SOAP_ENV__Detail(struct soap*, const char*, struct SOAP_ENV__Detail *, const char*);
SOAP_FMAC5 struct SOAP_ENV__Detail * SOAP_FMAC6 soap_new_SOAP_ENV__Detail(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_SOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail*);
SOAP_FMAC3 struct SOAP_ENV__Detail * SOAP_FMAC4 soap_instantiate_SOAP_ENV__Detail(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_SOAP_ENV__Detail(struct soap*, int, int, void*, size_t, const void*, size_t);

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (36)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Code(struct soap*, const struct SOAP_ENV__Code *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Code(struct soap*, const struct SOAP_ENV__Code *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Code(struct soap*, const char*, int, const struct SOAP_ENV__Code *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Code * SOAP_FMAC4 soap_get_SOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code *, const char*, const char*);
SOAP_FMAC3 struct SOAP_ENV__Code * SOAP_FMAC4 soap_in_SOAP_ENV__Code(struct soap*, const char*, struct SOAP_ENV__Code *, const char*);
SOAP_FMAC5 struct SOAP_ENV__Code * SOAP_FMAC6 soap_new_SOAP_ENV__Code(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_SOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code*);
SOAP_FMAC3 struct SOAP_ENV__Code * SOAP_FMAC4 soap_instantiate_SOAP_ENV__Code(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_SOAP_ENV__Code(struct soap*, int, int, void*, size_t, const void*, size_t);

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (35)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Header(struct soap*, struct SOAP_ENV__Header *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Header(struct soap*, const struct SOAP_ENV__Header *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Header(struct soap*, const struct SOAP_ENV__Header *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Header(struct soap*, const char*, int, const struct SOAP_ENV__Header *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Header * SOAP_FMAC4 soap_get_SOAP_ENV__Header(struct soap*, struct SOAP_ENV__Header *, const char*, const char*);
SOAP_FMAC3 struct SOAP_ENV__Header * SOAP_FMAC4 soap_in_SOAP_ENV__Header(struct soap*, const char*, struct SOAP_ENV__Header *, const char*);
SOAP_FMAC5 struct SOAP_ENV__Header * SOAP_FMAC6 soap_new_SOAP_ENV__Header(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_SOAP_ENV__Header(struct soap*, struct SOAP_ENV__Header*);
SOAP_FMAC3 struct SOAP_ENV__Header * SOAP_FMAC4 soap_instantiate_SOAP_ENV__Header(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_SOAP_ENV__Header(struct soap*, int, int, void*, size_t, const void*, size_t);

#endif

#ifndef SOAP_TYPE_ns__getAFramebaseDimeStream
#define SOAP_TYPE_ns__getAFramebaseDimeStream (34)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__getAFramebaseDimeStream(struct soap*, struct ns__getAFramebaseDimeStream *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__getAFramebaseDimeStream(struct soap*, const struct ns__getAFramebaseDimeStream *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__getAFramebaseDimeStream(struct soap*, const struct ns__getAFramebaseDimeStream *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__getAFramebaseDimeStream(struct soap*, const char*, int, const struct ns__getAFramebaseDimeStream *, const char*);
SOAP_FMAC3 struct ns__getAFramebaseDimeStream * SOAP_FMAC4 soap_get_ns__getAFramebaseDimeStream(struct soap*, struct ns__getAFramebaseDimeStream *, const char*, const char*);
SOAP_FMAC3 struct ns__getAFramebaseDimeStream * SOAP_FMAC4 soap_in_ns__getAFramebaseDimeStream(struct soap*, const char*, struct ns__getAFramebaseDimeStream *, const char*);
SOAP_FMAC5 struct ns__getAFramebaseDimeStream * SOAP_FMAC6 soap_new_ns__getAFramebaseDimeStream(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_ns__getAFramebaseDimeStream(struct soap*, struct ns__getAFramebaseDimeStream*);
SOAP_FMAC3 struct ns__getAFramebaseDimeStream * SOAP_FMAC4 soap_instantiate_ns__getAFramebaseDimeStream(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_ns__getAFramebaseDimeStream(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef SOAP_TYPE_ns__getAFramebaseDimeStreamResponse
#define SOAP_TYPE_ns__getAFramebaseDimeStreamResponse (33)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__getAFramebaseDimeStreamResponse(struct soap*, struct ns__getAFramebaseDimeStreamResponse *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__getAFramebaseDimeStreamResponse(struct soap*, const struct ns__getAFramebaseDimeStreamResponse *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__getAFramebaseDimeStreamResponse(struct soap*, const struct ns__getAFramebaseDimeStreamResponse *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__getAFramebaseDimeStreamResponse(struct soap*, const char*, int, const struct ns__getAFramebaseDimeStreamResponse *, const char*);
SOAP_FMAC3 struct ns__getAFramebaseDimeStreamResponse * SOAP_FMAC4 soap_get_ns__getAFramebaseDimeStreamResponse(struct soap*, struct ns__getAFramebaseDimeStreamResponse *, const char*, const char*);
SOAP_FMAC3 struct ns__getAFramebaseDimeStreamResponse * SOAP_FMAC4 soap_in_ns__getAFramebaseDimeStreamResponse(struct soap*, const char*, struct ns__getAFramebaseDimeStreamResponse *, const char*);
SOAP_FMAC5 struct ns__getAFramebaseDimeStreamResponse * SOAP_FMAC6 soap_new_ns__getAFramebaseDimeStreamResponse(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_ns__getAFramebaseDimeStreamResponse(struct soap*, struct ns__getAFramebaseDimeStreamResponse*);
SOAP_FMAC3 struct ns__getAFramebaseDimeStreamResponse * SOAP_FMAC4 soap_instantiate_ns__getAFramebaseDimeStreamResponse(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_ns__getAFramebaseDimeStreamResponse(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef SOAP_TYPE_ns__getAFramebase64Binary
#define SOAP_TYPE_ns__getAFramebase64Binary (30)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__getAFramebase64Binary(struct soap*, struct ns__getAFramebase64Binary *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__getAFramebase64Binary(struct soap*, const struct ns__getAFramebase64Binary *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__getAFramebase64Binary(struct soap*, const struct ns__getAFramebase64Binary *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__getAFramebase64Binary(struct soap*, const char*, int, const struct ns__getAFramebase64Binary *, const char*);
SOAP_FMAC3 struct ns__getAFramebase64Binary * SOAP_FMAC4 soap_get_ns__getAFramebase64Binary(struct soap*, struct ns__getAFramebase64Binary *, const char*, const char*);
SOAP_FMAC3 struct ns__getAFramebase64Binary * SOAP_FMAC4 soap_in_ns__getAFramebase64Binary(struct soap*, const char*, struct ns__getAFramebase64Binary *, const char*);
SOAP_FMAC5 struct ns__getAFramebase64Binary * SOAP_FMAC6 soap_new_ns__getAFramebase64Binary(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_ns__getAFramebase64Binary(struct soap*, struct ns__getAFramebase64Binary*);
SOAP_FMAC3 struct ns__getAFramebase64Binary * SOAP_FMAC4 soap_instantiate_ns__getAFramebase64Binary(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_ns__getAFramebase64Binary(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef SOAP_TYPE_ns__getAFramebase64BinaryResponse
#define SOAP_TYPE_ns__getAFramebase64BinaryResponse (29)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__getAFramebase64BinaryResponse(struct soap*, struct ns__getAFramebase64BinaryResponse *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__getAFramebase64BinaryResponse(struct soap*, const struct ns__getAFramebase64BinaryResponse *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__getAFramebase64BinaryResponse(struct soap*, const struct ns__getAFramebase64BinaryResponse *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__getAFramebase64BinaryResponse(struct soap*, const char*, int, const struct ns__getAFramebase64BinaryResponse *, const char*);
SOAP_FMAC3 struct ns__getAFramebase64BinaryResponse * SOAP_FMAC4 soap_get_ns__getAFramebase64BinaryResponse(struct soap*, struct ns__getAFramebase64BinaryResponse *, const char*, const char*);
SOAP_FMAC3 struct ns__getAFramebase64BinaryResponse * SOAP_FMAC4 soap_in_ns__getAFramebase64BinaryResponse(struct soap*, const char*, struct ns__getAFramebase64BinaryResponse *, const char*);
SOAP_FMAC5 struct ns__getAFramebase64BinaryResponse * SOAP_FMAC6 soap_new_ns__getAFramebase64BinaryResponse(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_ns__getAFramebase64BinaryResponse(struct soap*, struct ns__getAFramebase64BinaryResponse*);
SOAP_FMAC3 struct ns__getAFramebase64BinaryResponse * SOAP_FMAC4 soap_instantiate_ns__getAFramebase64BinaryResponse(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_ns__getAFramebase64BinaryResponse(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef SOAP_TYPE_ns__getAFrameHexBinary
#define SOAP_TYPE_ns__getAFrameHexBinary (26)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__getAFrameHexBinary(struct soap*, struct ns__getAFrameHexBinary *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__getAFrameHexBinary(struct soap*, const struct ns__getAFrameHexBinary *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__getAFrameHexBinary(struct soap*, const struct ns__getAFrameHexBinary *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__getAFrameHexBinary(struct soap*, const char*, int, const struct ns__getAFrameHexBinary *, const char*);
SOAP_FMAC3 struct ns__getAFrameHexBinary * SOAP_FMAC4 soap_get_ns__getAFrameHexBinary(struct soap*, struct ns__getAFrameHexBinary *, const char*, const char*);
SOAP_FMAC3 struct ns__getAFrameHexBinary * SOAP_FMAC4 soap_in_ns__getAFrameHexBinary(struct soap*, const char*, struct ns__getAFrameHexBinary *, const char*);
SOAP_FMAC5 struct ns__getAFrameHexBinary * SOAP_FMAC6 soap_new_ns__getAFrameHexBinary(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_ns__getAFrameHexBinary(struct soap*, struct ns__getAFrameHexBinary*);
SOAP_FMAC3 struct ns__getAFrameHexBinary * SOAP_FMAC4 soap_instantiate_ns__getAFrameHexBinary(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_ns__getAFrameHexBinary(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef SOAP_TYPE_ns__getAFrameHexBinaryResponse
#define SOAP_TYPE_ns__getAFrameHexBinaryResponse (25)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__getAFrameHexBinaryResponse(struct soap*, struct ns__getAFrameHexBinaryResponse *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__getAFrameHexBinaryResponse(struct soap*, const struct ns__getAFrameHexBinaryResponse *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__getAFrameHexBinaryResponse(struct soap*, const struct ns__getAFrameHexBinaryResponse *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__getAFrameHexBinaryResponse(struct soap*, const char*, int, const struct ns__getAFrameHexBinaryResponse *, const char*);
SOAP_FMAC3 struct ns__getAFrameHexBinaryResponse * SOAP_FMAC4 soap_get_ns__getAFrameHexBinaryResponse(struct soap*, struct ns__getAFrameHexBinaryResponse *, const char*, const char*);
SOAP_FMAC3 struct ns__getAFrameHexBinaryResponse * SOAP_FMAC4 soap_in_ns__getAFrameHexBinaryResponse(struct soap*, const char*, struct ns__getAFrameHexBinaryResponse *, const char*);
SOAP_FMAC5 struct ns__getAFrameHexBinaryResponse * SOAP_FMAC6 soap_new_ns__getAFrameHexBinaryResponse(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_ns__getAFrameHexBinaryResponse(struct soap*, struct ns__getAFrameHexBinaryResponse*);
SOAP_FMAC3 struct ns__getAFrameHexBinaryResponse * SOAP_FMAC4 soap_instantiate_ns__getAFrameHexBinaryResponse(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_ns__getAFrameHexBinaryResponse(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef SOAP_TYPE_ns__resetCounter
#define SOAP_TYPE_ns__resetCounter (22)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__resetCounter(struct soap*, struct ns__resetCounter *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__resetCounter(struct soap*, const struct ns__resetCounter *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__resetCounter(struct soap*, const struct ns__resetCounter *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__resetCounter(struct soap*, const char*, int, const struct ns__resetCounter *, const char*);
SOAP_FMAC3 struct ns__resetCounter * SOAP_FMAC4 soap_get_ns__resetCounter(struct soap*, struct ns__resetCounter *, const char*, const char*);
SOAP_FMAC3 struct ns__resetCounter * SOAP_FMAC4 soap_in_ns__resetCounter(struct soap*, const char*, struct ns__resetCounter *, const char*);
SOAP_FMAC5 struct ns__resetCounter * SOAP_FMAC6 soap_new_ns__resetCounter(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_ns__resetCounter(struct soap*, struct ns__resetCounter*);
SOAP_FMAC3 struct ns__resetCounter * SOAP_FMAC4 soap_instantiate_ns__resetCounter(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_ns__resetCounter(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef SOAP_TYPE_ns__resetCounterResponse
#define SOAP_TYPE_ns__resetCounterResponse (21)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__resetCounterResponse(struct soap*, struct ns__resetCounterResponse *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__resetCounterResponse(struct soap*, const struct ns__resetCounterResponse *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__resetCounterResponse(struct soap*, const struct ns__resetCounterResponse *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__resetCounterResponse(struct soap*, const char*, int, const struct ns__resetCounterResponse *, const char*);
SOAP_FMAC3 struct ns__resetCounterResponse * SOAP_FMAC4 soap_get_ns__resetCounterResponse(struct soap*, struct ns__resetCounterResponse *, const char*, const char*);
SOAP_FMAC3 struct ns__resetCounterResponse * SOAP_FMAC4 soap_in_ns__resetCounterResponse(struct soap*, const char*, struct ns__resetCounterResponse *, const char*);
SOAP_FMAC5 struct ns__resetCounterResponse * SOAP_FMAC6 soap_new_ns__resetCounterResponse(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_ns__resetCounterResponse(struct soap*, struct ns__resetCounterResponse*);
SOAP_FMAC3 struct ns__resetCounterResponse * SOAP_FMAC4 soap_instantiate_ns__resetCounterResponse(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_ns__resetCounterResponse(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef SOAP_TYPE_ns__changeConditionToFind
#define SOAP_TYPE_ns__changeConditionToFind (19)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__changeConditionToFind(struct soap*, struct ns__changeConditionToFind *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__changeConditionToFind(struct soap*, const struct ns__changeConditionToFind *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__changeConditionToFind(struct soap*, const struct ns__changeConditionToFind *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__changeConditionToFind(struct soap*, const char*, int, const struct ns__changeConditionToFind *, const char*);
SOAP_FMAC3 struct ns__changeConditionToFind * SOAP_FMAC4 soap_get_ns__changeConditionToFind(struct soap*, struct ns__changeConditionToFind *, const char*, const char*);
SOAP_FMAC3 struct ns__changeConditionToFind * SOAP_FMAC4 soap_in_ns__changeConditionToFind(struct soap*, const char*, struct ns__changeConditionToFind *, const char*);
SOAP_FMAC5 struct ns__changeConditionToFind * SOAP_FMAC6 soap_new_ns__changeConditionToFind(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_ns__changeConditionToFind(struct soap*, struct ns__changeConditionToFind*);
SOAP_FMAC3 struct ns__changeConditionToFind * SOAP_FMAC4 soap_instantiate_ns__changeConditionToFind(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_ns__changeConditionToFind(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef SOAP_TYPE_ns__changeConditionToFindResponse
#define SOAP_TYPE_ns__changeConditionToFindResponse (18)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__changeConditionToFindResponse(struct soap*, struct ns__changeConditionToFindResponse *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__changeConditionToFindResponse(struct soap*, const struct ns__changeConditionToFindResponse *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__changeConditionToFindResponse(struct soap*, const struct ns__changeConditionToFindResponse *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__changeConditionToFindResponse(struct soap*, const char*, int, const struct ns__changeConditionToFindResponse *, const char*);
SOAP_FMAC3 struct ns__changeConditionToFindResponse * SOAP_FMAC4 soap_get_ns__changeConditionToFindResponse(struct soap*, struct ns__changeConditionToFindResponse *, const char*, const char*);
SOAP_FMAC3 struct ns__changeConditionToFindResponse * SOAP_FMAC4 soap_in_ns__changeConditionToFindResponse(struct soap*, const char*, struct ns__changeConditionToFindResponse *, const char*);
SOAP_FMAC5 struct ns__changeConditionToFindResponse * SOAP_FMAC6 soap_new_ns__changeConditionToFindResponse(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_ns__changeConditionToFindResponse(struct soap*, struct ns__changeConditionToFindResponse*);
SOAP_FMAC3 struct ns__changeConditionToFindResponse * SOAP_FMAC4 soap_instantiate_ns__changeConditionToFindResponse(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_ns__changeConditionToFindResponse(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef SOAP_TYPE_ns__getCurrentFoundCount
#define SOAP_TYPE_ns__getCurrentFoundCount (16)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__getCurrentFoundCount(struct soap*, struct ns__getCurrentFoundCount *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__getCurrentFoundCount(struct soap*, const struct ns__getCurrentFoundCount *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__getCurrentFoundCount(struct soap*, const struct ns__getCurrentFoundCount *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__getCurrentFoundCount(struct soap*, const char*, int, const struct ns__getCurrentFoundCount *, const char*);
SOAP_FMAC3 struct ns__getCurrentFoundCount * SOAP_FMAC4 soap_get_ns__getCurrentFoundCount(struct soap*, struct ns__getCurrentFoundCount *, const char*, const char*);
SOAP_FMAC3 struct ns__getCurrentFoundCount * SOAP_FMAC4 soap_in_ns__getCurrentFoundCount(struct soap*, const char*, struct ns__getCurrentFoundCount *, const char*);
SOAP_FMAC5 struct ns__getCurrentFoundCount * SOAP_FMAC6 soap_new_ns__getCurrentFoundCount(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_ns__getCurrentFoundCount(struct soap*, struct ns__getCurrentFoundCount*);
SOAP_FMAC3 struct ns__getCurrentFoundCount * SOAP_FMAC4 soap_instantiate_ns__getCurrentFoundCount(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_ns__getCurrentFoundCount(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef SOAP_TYPE_ns__getCurrentFoundCountResponse
#define SOAP_TYPE_ns__getCurrentFoundCountResponse (15)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__getCurrentFoundCountResponse(struct soap*, struct ns__getCurrentFoundCountResponse *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__getCurrentFoundCountResponse(struct soap*, const struct ns__getCurrentFoundCountResponse *);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__getCurrentFoundCountResponse(struct soap*, const struct ns__getCurrentFoundCountResponse *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__getCurrentFoundCountResponse(struct soap*, const char*, int, const struct ns__getCurrentFoundCountResponse *, const char*);
SOAP_FMAC3 struct ns__getCurrentFoundCountResponse * SOAP_FMAC4 soap_get_ns__getCurrentFoundCountResponse(struct soap*, struct ns__getCurrentFoundCountResponse *, const char*, const char*);
SOAP_FMAC3 struct ns__getCurrentFoundCountResponse * SOAP_FMAC4 soap_in_ns__getCurrentFoundCountResponse(struct soap*, const char*, struct ns__getCurrentFoundCountResponse *, const char*);
SOAP_FMAC5 struct ns__getCurrentFoundCountResponse * SOAP_FMAC6 soap_new_ns__getCurrentFoundCountResponse(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_ns__getCurrentFoundCountResponse(struct soap*, struct ns__getCurrentFoundCountResponse*);
SOAP_FMAC3 struct ns__getCurrentFoundCountResponse * SOAP_FMAC4 soap_instantiate_ns__getCurrentFoundCountResponse(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_ns__getCurrentFoundCountResponse(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef SOAP_TYPE_xsd__Dimebase64Binary
#define SOAP_TYPE_xsd__Dimebase64Binary (12)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_xsd__Dimebase64Binary(struct soap*, struct xsd__Dimebase64Binary *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_xsd__Dimebase64Binary(struct soap*, struct xsd__Dimebase64Binary const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_xsd__Dimebase64Binary(struct soap*, const struct xsd__Dimebase64Binary *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_xsd__Dimebase64Binary(struct soap*, const char*, int, const struct xsd__Dimebase64Binary *, const char*);
SOAP_FMAC3 struct xsd__Dimebase64Binary * SOAP_FMAC4 soap_get_xsd__Dimebase64Binary(struct soap*, struct xsd__Dimebase64Binary *, const char*, const char*);
SOAP_FMAC3 struct xsd__Dimebase64Binary * SOAP_FMAC4 soap_in_xsd__Dimebase64Binary(struct soap*, const char*, struct xsd__Dimebase64Binary *, const char*);
SOAP_FMAC5 struct xsd__Dimebase64Binary * SOAP_FMAC6 soap_new_xsd__Dimebase64Binary(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_xsd__Dimebase64Binary(struct soap*, struct xsd__Dimebase64Binary*);
SOAP_FMAC3 struct xsd__Dimebase64Binary * SOAP_FMAC4 soap_instantiate_xsd__Dimebase64Binary(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_xsd__Dimebase64Binary(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef SOAP_TYPE_xsd__base64Binary
#define SOAP_TYPE_xsd__base64Binary (11)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_xsd__base64Binary(struct soap*, struct xsd__base64Binary *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_xsd__base64Binary(struct soap*, struct xsd__base64Binary const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_xsd__base64Binary(struct soap*, const struct xsd__base64Binary *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_xsd__base64Binary(struct soap*, const char*, int, const struct xsd__base64Binary *, const char*);
SOAP_FMAC3 struct xsd__base64Binary * SOAP_FMAC4 soap_get_xsd__base64Binary(struct soap*, struct xsd__base64Binary *, const char*, const char*);
SOAP_FMAC3 struct xsd__base64Binary * SOAP_FMAC4 soap_in_xsd__base64Binary(struct soap*, const char*, struct xsd__base64Binary *, const char*);
SOAP_FMAC5 struct xsd__base64Binary * SOAP_FMAC6 soap_new_xsd__base64Binary(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_xsd__base64Binary(struct soap*, struct xsd__base64Binary*);
SOAP_FMAC3 struct xsd__base64Binary * SOAP_FMAC4 soap_instantiate_xsd__base64Binary(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_xsd__base64Binary(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef SOAP_TYPE_xsd__hexBinary
#define SOAP_TYPE_xsd__hexBinary (7)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_xsd__hexBinary(struct soap*, struct xsd__hexBinary *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_xsd__hexBinary(struct soap*, struct xsd__hexBinary const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_xsd__hexBinary(struct soap*, const struct xsd__hexBinary *, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_xsd__hexBinary(struct soap*, const char*, int, const struct xsd__hexBinary *, const char*);
SOAP_FMAC3 struct xsd__hexBinary * SOAP_FMAC4 soap_get_xsd__hexBinary(struct soap*, struct xsd__hexBinary *, const char*, const char*);
SOAP_FMAC3 struct xsd__hexBinary * SOAP_FMAC4 soap_in_xsd__hexBinary(struct soap*, const char*, struct xsd__hexBinary *, const char*);
SOAP_FMAC5 struct xsd__hexBinary * SOAP_FMAC6 soap_new_xsd__hexBinary(struct soap*, int);
SOAP_FMAC5 void SOAP_FMAC6 soap_delete_xsd__hexBinary(struct soap*, struct xsd__hexBinary*);
SOAP_FMAC3 struct xsd__hexBinary * SOAP_FMAC4 soap_instantiate_xsd__hexBinary(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 void SOAP_FMAC4 soap_copy_xsd__hexBinary(struct soap*, int, int, void*, size_t, const void*, size_t);

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_PointerToSOAP_ENV__Reason
#define SOAP_TYPE_PointerToSOAP_ENV__Reason (44)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToSOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToSOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason *const*, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToSOAP_ENV__Reason(struct soap*, const char *, int, struct SOAP_ENV__Reason *const*, const char *);
SOAP_FMAC3 struct SOAP_ENV__Reason ** SOAP_FMAC4 soap_get_PointerToSOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason **, const char*, const char*);
SOAP_FMAC3 struct SOAP_ENV__Reason ** SOAP_FMAC4 soap_in_PointerToSOAP_ENV__Reason(struct soap*, const char*, struct SOAP_ENV__Reason **, const char*);

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_PointerToSOAP_ENV__Detail
#define SOAP_TYPE_PointerToSOAP_ENV__Detail (43)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToSOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToSOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail *const*, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToSOAP_ENV__Detail(struct soap*, const char *, int, struct SOAP_ENV__Detail *const*, const char *);
SOAP_FMAC3 struct SOAP_ENV__Detail ** SOAP_FMAC4 soap_get_PointerToSOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail **, const char*, const char*);
SOAP_FMAC3 struct SOAP_ENV__Detail ** SOAP_FMAC4 soap_in_PointerToSOAP_ENV__Detail(struct soap*, const char*, struct SOAP_ENV__Detail **, const char*);

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_PointerToSOAP_ENV__Code
#define SOAP_TYPE_PointerToSOAP_ENV__Code (37)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToSOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToSOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code *const*, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToSOAP_ENV__Code(struct soap*, const char *, int, struct SOAP_ENV__Code *const*, const char *);
SOAP_FMAC3 struct SOAP_ENV__Code ** SOAP_FMAC4 soap_get_PointerToSOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code **, const char*, const char*);
SOAP_FMAC3 struct SOAP_ENV__Code ** SOAP_FMAC4 soap_in_PointerToSOAP_ENV__Code(struct soap*, const char*, struct SOAP_ENV__Code **, const char*);

#endif

#ifndef SOAP_TYPE_PointerToxsd__Dimebase64Binary
#define SOAP_TYPE_PointerToxsd__Dimebase64Binary (31)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToxsd__Dimebase64Binary(struct soap*, struct xsd__Dimebase64Binary *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToxsd__Dimebase64Binary(struct soap*, struct xsd__Dimebase64Binary *const*, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToxsd__Dimebase64Binary(struct soap*, const char *, int, struct xsd__Dimebase64Binary *const*, const char *);
SOAP_FMAC3 struct xsd__Dimebase64Binary ** SOAP_FMAC4 soap_get_PointerToxsd__Dimebase64Binary(struct soap*, struct xsd__Dimebase64Binary **, const char*, const char*);
SOAP_FMAC3 struct xsd__Dimebase64Binary ** SOAP_FMAC4 soap_in_PointerToxsd__Dimebase64Binary(struct soap*, const char*, struct xsd__Dimebase64Binary **, const char*);

#ifndef SOAP_TYPE_PointerToxsd__base64Binary
#define SOAP_TYPE_PointerToxsd__base64Binary (27)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToxsd__base64Binary(struct soap*, struct xsd__base64Binary *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToxsd__base64Binary(struct soap*, struct xsd__base64Binary *const*, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToxsd__base64Binary(struct soap*, const char *, int, struct xsd__base64Binary *const*, const char *);
SOAP_FMAC3 struct xsd__base64Binary ** SOAP_FMAC4 soap_get_PointerToxsd__base64Binary(struct soap*, struct xsd__base64Binary **, const char*, const char*);
SOAP_FMAC3 struct xsd__base64Binary ** SOAP_FMAC4 soap_in_PointerToxsd__base64Binary(struct soap*, const char*, struct xsd__base64Binary **, const char*);

#ifndef SOAP_TYPE_PointerToxsd__hexBinary
#define SOAP_TYPE_PointerToxsd__hexBinary (23)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToxsd__hexBinary(struct soap*, struct xsd__hexBinary *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToxsd__hexBinary(struct soap*, struct xsd__hexBinary *const*, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToxsd__hexBinary(struct soap*, const char *, int, struct xsd__hexBinary *const*, const char *);
SOAP_FMAC3 struct xsd__hexBinary ** SOAP_FMAC4 soap_get_PointerToxsd__hexBinary(struct soap*, struct xsd__hexBinary **, const char*, const char*);
SOAP_FMAC3 struct xsd__hexBinary ** SOAP_FMAC4 soap_in_PointerToxsd__hexBinary(struct soap*, const char*, struct xsd__hexBinary **, const char*);

#ifndef SOAP_TYPE_PointerToint
#define SOAP_TYPE_PointerToint (13)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToint(struct soap*, int *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToint(struct soap*, int *const*, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToint(struct soap*, const char *, int, int *const*, const char *);
SOAP_FMAC3 int ** SOAP_FMAC4 soap_get_PointerToint(struct soap*, int **, const char*, const char*);
SOAP_FMAC3 int ** SOAP_FMAC4 soap_in_PointerToint(struct soap*, const char*, int **, const char*);

#ifndef SOAP_TYPE_PointerTounsignedByte
#define SOAP_TYPE_PointerTounsignedByte (10)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerTounsignedByte(struct soap*, unsigned char *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerTounsignedByte(struct soap*, unsigned char *const*, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerTounsignedByte(struct soap*, const char *, int, unsigned char *const*, const char *);
SOAP_FMAC3 unsigned char ** SOAP_FMAC4 soap_get_PointerTounsignedByte(struct soap*, unsigned char **, const char*, const char*);
SOAP_FMAC3 unsigned char ** SOAP_FMAC4 soap_in_PointerTounsignedByte(struct soap*, const char*, unsigned char **, const char*);

#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (5)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default__QName(struct soap*, char **);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize__QName(struct soap*, char *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put__QName(struct soap*, char *const*, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out__QName(struct soap*, const char*, int, char*const*, const char*);
SOAP_FMAC3 char ** SOAP_FMAC4 soap_get__QName(struct soap*, char **, const char*, const char*);
SOAP_FMAC3 char * * SOAP_FMAC4 soap_in__QName(struct soap*, const char*, char **, const char*);

#ifndef SOAP_TYPE_string
#define SOAP_TYPE_string (4)
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_default_string(struct soap*, char **);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_string(struct soap*, char *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_string(struct soap*, char *const*, const char*, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_string(struct soap*, const char*, int, char*const*, const char*);
SOAP_FMAC3 char ** SOAP_FMAC4 soap_get_string(struct soap*, char **, const char*, const char*);
SOAP_FMAC3 char * * SOAP_FMAC4 soap_in_string(struct soap*, const char*, char **, const char*);

#endif

/* End of soapH.h */
