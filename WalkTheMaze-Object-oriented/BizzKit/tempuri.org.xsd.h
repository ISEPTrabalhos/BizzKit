﻿
// File generated by Wsutil Compiler version 1.0092 
// This file defines C/C++ functions, callbacks, types that correspond to operations,
// and types specified in WSDL and XSD files processed by WsUtil compiler. The generated 
// type definitions, function and callback declarations can be used with various 
// Web Services APIs either in applications that send and receive requests to and 
// from a running web service, or in the implementation of web services, or in both. 
//
// If Wsutil has generated this file from an XSD file, the file contains definition of 
// C/C++ structures types that correspond to types defined in the XSD file. 
// For example, if the following XSD complexType is defined in the XSD file
//
//      <xsd:complexType name="AddRequest">
//          <xsd:sequence>
//              <xsd:element minOccurs="0" name="a" type="xsd:int" />
//              <xsd:element minOccurs="0" name="b" type="xsd:int" />
//          </xsd:sequence>
//      </xsd:complexType>
// 
// this file contains the following definitions of the structure 
//      // AddRequest (xsd:complexType)
//      // <AddRequest xmlns='http://tempuri.org'>
//      // WS_STRUCT_DESCRIPTION* = &calculator_xsd.globalTypes.AddRequest
//      struct AddRequest
//      {
//          int a;
//          int b;
//      };
//
// For more information on how to use the C/C++ types generated in this file to read or write elements of XML documents that conform to 
// this XSD, please see the documentation for 
// WsReadType() and WsWriteType() functions.
// 
#if _MSC_VER > 1000 
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

// The following types were generated:

//     struct _Login;
//     struct _LoginResponse;
//     struct _Score;
//     struct _ScoreResponse;

// The following header files must be included in this order before this one

// #include <WebServices.h>

////////////////////////////////////////////////
// C structure definitions for generated types
////////////////////////////////////////////////

// typeDescription: n/a
typedef struct _Login 
{
    WCHAR* username; // optional
    WCHAR* password; // optional
} _Login;

// typeDescription: n/a
typedef struct _LoginResponse 
{
    WCHAR* LoginResult; // optional
} _LoginResponse;

// typeDescription: n/a
typedef struct _Score 
{
    WCHAR* username; // optional
    int score;
} _Score;

// typeDescription: n/a
typedef struct _ScoreResponse 
{
    int ScoreResult;
} _ScoreResponse;

////////////////////////////////////////////////
// Global web service descriptions.
////////////////////////////////////////////////

typedef struct _tempuri_org_xsd
{
    struct // globalElements
    {
        // xml element: Login ("http://tempuri.org/")
        // c type: _Login
        // elementDescription: tempuri_org_xsd.globalElements.Login
        WS_ELEMENT_DESCRIPTION Login;
        
        // xml element: LoginResponse ("http://tempuri.org/")
        // c type: _LoginResponse
        // elementDescription: tempuri_org_xsd.globalElements.LoginResponse
        WS_ELEMENT_DESCRIPTION LoginResponse;
        
        // xml element: Score ("http://tempuri.org/")
        // c type: _Score
        // elementDescription: tempuri_org_xsd.globalElements.Score
        WS_ELEMENT_DESCRIPTION Score;
        
        // xml element: ScoreResponse ("http://tempuri.org/")
        // c type: _ScoreResponse
        // elementDescription: tempuri_org_xsd.globalElements.ScoreResponse
        WS_ELEMENT_DESCRIPTION ScoreResponse;
        
    } globalElements;
    struct // externallyReferencedTypes
    {
        WS_STRUCT_DESCRIPTION Login;
        WS_STRUCT_DESCRIPTION LoginResponse;
        WS_STRUCT_DESCRIPTION Score;
        WS_STRUCT_DESCRIPTION ScoreResponse;
    } externallyReferencedTypes;
} _tempuri_org_xsd;

extern const _tempuri_org_xsd tempuri_org_xsd;

#ifdef __cplusplus
}
#endif

