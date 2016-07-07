/* soapClient.cpp
   Generated by gSOAP 2.7.11 from diff_count.h
   Copyright(C) 2000-2008, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/
#include "soapH.h"

SOAP_SOURCE_STAMP("@(#) soapClient.cpp ver 2.7.11 2008-11-17 08:24:46 GMT")


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

/* End of soapClient.cpp */
