/*
	calc.h

	This is a gSOAP header file with web service definitions.

	The service operations and type definitions use familiar C/C++ syntax.

	The following methods are defined by this gSOAP service definition:

	add(a,b)
	sub(a,b)
	mul(a,b)
	div(a,b)
	pow(a,b)

	Compilation in C (see samples/calc):
	$ soapcpp2 -c calc.h
	$ cc -o calcclient calcclient.c stdsoap2.c soapC.c soapClient.c
	$ cc -o calcserver calcserver.c stdsoap2.c soapC.c soapServer.c

	Compilation in C++ (see samples/calc++):
	$ soapcpp2 -i calc.h
	$ cc -o calcclient++ calcclient.cpp stdsoap2.cpp soapC.cpp soapcalcProxy.cpp
	$ cc -o calcserver++ calcserver.cpp stdsoap2.cpp soapC.cpp soapcalcService.cpp

	Note that soapcpp2 option -i generates proxy and service classes, which
	encapsulate the method operations in the class instead of defining them
	as global functions as in C. 

	The //gsoap directives are used to bind XML namespaces and to define
	Web service properties:

	//gsoap <ns> service name: <WSDLserviceName> <documentationText>
	//gsoap <ns> service style: [rpc|document]
	//gsoap <ns> service encoding: [literal|encoded]
	//gsoap <ns> service namespace: <WSDLnamespaceURI>
	//gsoap <ns> service location: <WSDLserviceAddressLocationURI>

	Web service operation properties:

	//gsoap <ns> service method-style: <methodName> [rpc|document]
	//gsoap <ns> service method-encoding: <methodName> [literal|encoded]
	//gsoap <ns> service method-action: <methodName> <actionString>
	//gsoap <ns> service method-documentation: <methodName> <documentation>

	and type schema properties:

	//gsoap <ns> schema namespace: <schemaNamespaceURI>
	//gsoap <ns> schema elementForm: [qualified|unqualified]
	//gsoap <ns> schema attributeForm: [qualified|unqualified]
	//gsoap <ns> schema documentation: <documentationText>
	//gsoap <ns> schema type-documentation: <typeName> <documentationText>

	where <ns> is an XML namespace prefix, which is used in C/C++ operation
	names, e.g. ns__add(), and type names, e.g. xsd__int.

	See the documentation for the full list of //gsoap directives.

--------------------------------------------------------------------------------
gSOAP XML Web services tools
Copyright (C) 2001-2008, Robert van Engelen, Genivia, Inc. All Rights Reserved.
This software is released under one of the following two licenses:
GPL or Genivia's license for commercial use.
--------------------------------------------------------------------------------
GPL license.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

nThis program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA

Author contact information:
engelen@genivia.com / engelen@acm.org
--------------------------------------------------------------------------------
A commercial use license is available from Genivia, Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#import "import/soap12.h"
/* alternatively, without the import above, use:
//gsoap SOAP-ENV schema namespace: http://www.w3.org/2003/05/soap-envelope
//gsoap SOAP-ENC schema namespace: http://www.w3.org/2003/05/soap-encoding
*/
#import "import/xop.h"
#import "import/xmlmime.h"

//gsoap ns service name:	diff_count Do framedifferencing and Count pixels
//gsoap ns service style:	rpc
//gsoap ns service encoding:	encoded
//gsoap ns service namespace:	http://hoge/~hoge/diff_count.wsdl
//gsoap ns service location:	http://localhost:1024/

//gsoap ns schema namespace:	urn:diff_count

//for byte array with hexBinary data type
struct xsd__hexBinary
{
  unsigned char *__ptr;
  int __size;
};

//for byte array with base64Binary data type
struct xsd__base64Binary
{
  unsigned char *__ptr;
  int __size;
};

struct xsd__Dimebase64Binary
{
  unsigned char *__ptr;
  int __size;
  char *id;
  char *type;
  char *options;
};

/* //gsoap xop schema import: http://www.w3.org/2004/08/xop/include */
/* struct _xop__Include */
/* { */
/*   unsigned char *__ptr; */
/*   int __size; */
/*   char *id; */
/*   char *type; */
/*   char *options; */
/* }; */
/* typedef struct _xop__Include _xop__Include; */

//gsoap x schema namespace: http://my.first.mtom.net
struct x__mtomBinary
{
  _xop__Include xop__Include; // attachment
  @char *xmlmime__contentType; // and its contentType
};

int ns__getCurrentFoundCount(int *result);

int ns__changeConditionToFind(int color,int threshold,int *result);

int ns__resetCounter(int *result);

int ns__getAFrameHexBinary(struct xsd__hexBinary *result);

int ns__getAFramebase64Binary(struct xsd__base64Binary *result);

int ns__getAFramebaseDimeStream(struct xsd__Dimebase64Binary *result);

int ns__getAFrameMtom(struct x__mtomBinary *result);
