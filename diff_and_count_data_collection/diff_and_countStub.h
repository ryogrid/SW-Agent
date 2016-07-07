/* diff_and_countStub.h
   Generated by gSOAP 2.7.11 from diff_count.h
   Copyright(C) 2000-2008, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#ifndef diff_and_countStub_H
#define diff_and_countStub_H
#include "stdsoap2.h"
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************\
 *                                                                            *
 * Enumerations                                                               *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Classes and Structs                                                        *
 *                                                                            *
\******************************************************************************/


#if 0 /* volatile type: do not redeclare here */

#endif

#ifndef SOAP_TYPE__xop__Include
#define SOAP_TYPE__xop__Include (7)
/* Base64 schema type: */
struct _xop__Include
{
	unsigned char *__ptr;
	int __size;
	char *id;	/* optional element of type xsd:string */
	char *type;	/* optional element of type xsd:string */
	char *options;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_xsd__hexBinary
#define SOAP_TYPE_xsd__hexBinary (11)
/* hexBinary schema type: */
struct xsd__hexBinary
{
	unsigned char *__ptr;
	int __size;
};
#endif

#ifndef SOAP_TYPE_xsd__base64Binary
#define SOAP_TYPE_xsd__base64Binary (12)
/* Base64 schema type: */
struct xsd__base64Binary
{
	unsigned char *__ptr;
	int __size;
};
#endif

#ifndef SOAP_TYPE_xsd__Dimebase64Binary
#define SOAP_TYPE_xsd__Dimebase64Binary (13)
/* Base64 schema type: */
struct xsd__Dimebase64Binary
{
	unsigned char *__ptr;
	int __size;
	char *id;	/* optional element of type xsd:string */
	char *type;	/* optional element of type xsd:string */
	char *options;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_x__mtomBinary
#define SOAP_TYPE_x__mtomBinary (14)
/* x:mtomBinary */
struct x__mtomBinary
{
	struct _xop__Include xop__Include;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* required element of type xop:Include */
	char *xmlmime__contentType;	/* optional attribute of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns__getCurrentFoundCountResponse
#define SOAP_TYPE_ns__getCurrentFoundCountResponse (17)
/* ns:getCurrentFoundCountResponse */
struct ns__getCurrentFoundCountResponse
{
	int *result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:int */
};
#endif

#ifndef SOAP_TYPE_ns__getCurrentFoundCount
#define SOAP_TYPE_ns__getCurrentFoundCount (18)
/* ns:getCurrentFoundCount */
struct ns__getCurrentFoundCount
{
#ifdef WITH_NOEMPTYSTRUCT
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#ifndef SOAP_TYPE_ns__changeConditionToFindResponse
#define SOAP_TYPE_ns__changeConditionToFindResponse (20)
/* ns:changeConditionToFindResponse */
struct ns__changeConditionToFindResponse
{
	int *result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:int */
};
#endif

#ifndef SOAP_TYPE_ns__changeConditionToFind
#define SOAP_TYPE_ns__changeConditionToFind (21)
/* ns:changeConditionToFind */
struct ns__changeConditionToFind
{
	int color;	/* required element of type xsd:int */
	int threshold;	/* required element of type xsd:int */
};
#endif

#ifndef SOAP_TYPE_ns__resetCounterResponse
#define SOAP_TYPE_ns__resetCounterResponse (23)
/* ns:resetCounterResponse */
struct ns__resetCounterResponse
{
	int *result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:int */
};
#endif

#ifndef SOAP_TYPE_ns__resetCounter
#define SOAP_TYPE_ns__resetCounter (24)
/* ns:resetCounter */
struct ns__resetCounter
{
#ifdef WITH_NOEMPTYSTRUCT
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#ifndef SOAP_TYPE_ns__getAFrameHexBinaryResponse
#define SOAP_TYPE_ns__getAFrameHexBinaryResponse (27)
/* ns:getAFrameHexBinaryResponse */
struct ns__getAFrameHexBinaryResponse
{
	struct xsd__hexBinary *result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:hexBinary */
};
#endif

#ifndef SOAP_TYPE_ns__getAFrameHexBinary
#define SOAP_TYPE_ns__getAFrameHexBinary (28)
/* ns:getAFrameHexBinary */
struct ns__getAFrameHexBinary
{
#ifdef WITH_NOEMPTYSTRUCT
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#ifndef SOAP_TYPE_ns__getAFramebase64BinaryResponse
#define SOAP_TYPE_ns__getAFramebase64BinaryResponse (31)
/* ns:getAFramebase64BinaryResponse */
struct ns__getAFramebase64BinaryResponse
{
	struct xsd__base64Binary *result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:base64Binary */
};
#endif

#ifndef SOAP_TYPE_ns__getAFramebase64Binary
#define SOAP_TYPE_ns__getAFramebase64Binary (32)
/* ns:getAFramebase64Binary */
struct ns__getAFramebase64Binary
{
#ifdef WITH_NOEMPTYSTRUCT
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#ifndef SOAP_TYPE_ns__getAFramebaseDimeStreamResponse
#define SOAP_TYPE_ns__getAFramebaseDimeStreamResponse (35)
/* ns:getAFramebaseDimeStreamResponse */
struct ns__getAFramebaseDimeStreamResponse
{
	struct xsd__Dimebase64Binary *result;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:Dimebase64Binary */
};
#endif

#ifndef SOAP_TYPE_ns__getAFramebaseDimeStream
#define SOAP_TYPE_ns__getAFramebaseDimeStream (36)
/* ns:getAFramebaseDimeStream */
struct ns__getAFramebaseDimeStream
{
#ifdef WITH_NOEMPTYSTRUCT
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#ifndef SOAP_TYPE_ns__getAFrameMtom
#define SOAP_TYPE_ns__getAFrameMtom (39)
/* ns:getAFrameMtom */
struct ns__getAFrameMtom
{
#ifdef WITH_NOEMPTYSTRUCT
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (40)
/* SOAP Header: */
struct SOAP_ENV__Header
{
#ifdef WITH_NOEMPTYSTRUCT
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (41)
/* SOAP Fault Code: */
struct SOAP_ENV__Code
{
	char *SOAP_ENV__Value;	/* optional element of type xsd:QName */
	struct SOAP_ENV__Code *SOAP_ENV__Subcode;	/* optional element of type SOAP-ENV:Code */
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (43)
/* SOAP-ENV:Detail */
struct SOAP_ENV__Detail
{
	int __type;	/* any type of element <fault> (defined below) */
	void *fault;	/* transient */
	char *__any;
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (46)
/* SOAP-ENV:Reason */
struct SOAP_ENV__Reason
{
	char *SOAP_ENV__Text;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (47)
/* SOAP Fault: */
struct SOAP_ENV__Fault
{
	char *faultcode;	/* optional element of type xsd:QName */
	char *faultstring;	/* optional element of type xsd:string */
	char *faultactor;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *detail;	/* optional element of type SOAP-ENV:Detail */
	struct SOAP_ENV__Code *SOAP_ENV__Code;	/* optional element of type SOAP-ENV:Code */
	struct SOAP_ENV__Reason *SOAP_ENV__Reason;	/* optional element of type SOAP-ENV:Reason */
	char *SOAP_ENV__Node;	/* optional element of type xsd:string */
	char *SOAP_ENV__Role;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *SOAP_ENV__Detail;	/* optional element of type SOAP-ENV:Detail */
};
#endif

/******************************************************************************\
 *                                                                            *
 * Types with Custom Serializers                                              *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Typedefs                                                                   *
 *                                                                            *
\******************************************************************************/

#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (5)
typedef char *_QName;
#endif

#ifndef SOAP_TYPE__XML
#define SOAP_TYPE__XML (6)
typedef char *_XML;
#endif


/******************************************************************************\
 *                                                                            *
 * Typedef Synonyms                                                           *
 *                                                                            *
\******************************************************************************/

typedef struct _xop__Include _xop__Include;

/******************************************************************************\
 *                                                                            *
 * Externals                                                                  *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Service Operations                                                         *
 *                                                                            *
\******************************************************************************/


SOAP_FMAC5 int SOAP_FMAC6 ns__getCurrentFoundCount(struct soap*, int *result);

SOAP_FMAC5 int SOAP_FMAC6 ns__changeConditionToFind(struct soap*, int color, int threshold, int *result);

SOAP_FMAC5 int SOAP_FMAC6 ns__resetCounter(struct soap*, int *result);

SOAP_FMAC5 int SOAP_FMAC6 ns__getAFrameHexBinary(struct soap*, struct xsd__hexBinary *result);

SOAP_FMAC5 int SOAP_FMAC6 ns__getAFramebase64Binary(struct soap*, struct xsd__base64Binary *result);

SOAP_FMAC5 int SOAP_FMAC6 ns__getAFramebaseDimeStream(struct soap*, struct xsd__Dimebase64Binary *result);

SOAP_FMAC5 int SOAP_FMAC6 ns__getAFrameMtom(struct soap*, struct x__mtomBinary *result);

/******************************************************************************\
 *                                                                            *
 * Stubs                                                                      *
 *                                                                            *
\******************************************************************************/


SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__getCurrentFoundCount(struct soap *soap, const char *soap_endpoint, const char *soap_action, int *result);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__changeConditionToFind(struct soap *soap, const char *soap_endpoint, const char *soap_action, int color, int threshold, int *result);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__resetCounter(struct soap *soap, const char *soap_endpoint, const char *soap_action, int *result);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__getAFrameHexBinary(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct xsd__hexBinary *result);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__getAFramebase64Binary(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct xsd__base64Binary *result);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__getAFramebaseDimeStream(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct xsd__Dimebase64Binary *result);

SOAP_FMAC5 int SOAP_FMAC6 soap_call_ns__getAFrameMtom(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct x__mtomBinary *result);

/******************************************************************************\
 *                                                                            *
 * Skeletons                                                                  *
 *                                                                            *
\******************************************************************************/

SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__getCurrentFoundCount(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__changeConditionToFind(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__resetCounter(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__getAFrameHexBinary(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__getAFramebase64Binary(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__getAFramebaseDimeStream(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve_ns__getAFrameMtom(struct soap*);

#ifdef __cplusplus
}
#endif

#endif

/* End of diff_and_countStub.h */