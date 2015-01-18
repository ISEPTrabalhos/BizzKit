﻿
// File generated by Wsutil Compiler version 1.0092 
// This file defines C/C++ functions, callbacks, types that correspond to operations,
// and types specified in WSDL and XSD files processed by WsUtil compiler. The generated 
// type definitions, function and callback declarations can be used with various 
// Web Services APIs either in applications that send and receive requests to and 
// from a running web service, or in the implementation of web services, or in both. 
//
// If Wsutil has generated this file from a WSDL file, the file may contain up to three 
// sets of C/C++ definitions. The first set consists of function declarations that can be 
// used in calling operations on a running web service from client applications. 
// The second set consists of callback declarations that can be used in the 
// implementation of web services.  
// The third set contains definitions C/C++ structures that are used for serialization of 
// C/C++ types to schema types defined in the WSDL file.
//
// The set of function declarations for web services clients may contain the 
// following declaration: 
//
//    HRESULT WINAPI DefaultBinding_ICalculator_Add(
//       __in WS_SERVICE_PROXY* _serviceProxy,
//       __in int a, 
//       __in int b, 
//       __out int* result, 
//       __in WS_HEAP* _heap,
//       __in_opt WS_CALL_PROPERTY* _callProperties,
//       __in const ULONG _callPropertyCount,
//       __in_opt const WS_ASYNC_CONTEXT*_asyncContext,
//       __in_opt WS_ERROR* _error);
//
// This function can be called from an application code to request ICalculator web 
// service to perform operation Add using two integers a and b as input data.
// Once the web service processes this request and sends the result back,
// the result is returned to the caller of this function in the "result" parameter.
// A WS_SERVICE_PROXY must be created using WsCreateServiceProxy() function
// before this proxy function can be invoked.
//
// The set of callbacks for implementation of web services may contain the following 
// definition of a callback: 
//
//    typedef HRESULT (CALLBACK* DefaultBinding_ICalculator_AddCallback) (
//       __in const WS_OPERATION_CONTEXT* _context,
//       __in int a, 
//       __in int b, 
//       __out int* result, 
//       __in const WS_ASYNC_CONTEXT* _asyncContext,
//       __in WS_ERROR* _error); 
//
//    typedef struct DefaultBinding_ICalculatorFunctionTable 
//    {
//         DefaultBinding_ICalculator_AddCallback DefaultBinding_ICalculator_Add;
//    } DefaultBinding_ICalculatorFunctionTable;
//
// This definition can be used to implement a function that defines the Add operation 
// as a part of an ICalculator web service. Once this callback is implemented and 
// the web service is deployed and running, if a client applications attempts to 
// execute the operation Add, the implementation of this callback is called and 
// it receives two integers a and b as input data and it returns a third integer 
// that is the result of the operation. A WS_SERVICE_ENDPOINT must be filled out, 
// and its contract field set tosinstance of such a function table.  
// WsCreateServiceHost may then be used to register the endpoint as a service.
// 
// The set with definitions of C/C++ structures may contain a definition of the following 
// structure:
//    typedef struct ContactInfo 
//    {
//			WCHAR*  name;
//			WCHAR*  email;
//			__int64 contactID;
//	  } ContactInfo;
//
// This structure corresponds to the following complex type defined in the WSDL file:
//    <s:complexType name="ContactInfo">
//      <s:sequence>
//        <s:element minOccurs="1" maxOccurs="1" name="name" type="s:string" />
//        <s:element minOccurs="1" maxOccurs="1" name="email" type="s:string" />
//        <s:element minOccurs="1" maxOccurs="1" name="contactID" type="s:long" />
//      </s:sequence>
//    </s:complexType>
//
// For more information about content of this file, please see the documentation for
// Wsutil compiler.
// If Wsutil generates this file from a WSDL file and policy processing is enabled using
// policy switch, the file may contain declaration of functions that can be used 
// for creating a proxy to a web service or an endpoint of a web service. 
// For example, the file may contain declaration of the following function:
//
//    HRESULT DefaultBinding_ICalculator_CreateServiceProxy(
//    __in WS_HTTP_SSL_BINDING_TEMPLATE* templateValue,
//    __in_ecount_opt(proxyPropertyCount) const WS_PROXY_PROPERTY* proxyProperties,
//    __in const ULONG proxyPropertyCount,
//    __deref_out_opt WS_SERVICE_PROXY** proxy,
//    __in_opt WS_ERROR* error);
//
// This function can be called from application code to create a service
// proxy object. A service proxy must be created before any request can be sent 
// to the web service.
//
// Also, the file may contain declaration of the following function :
//
//    HRESULT DefaultBinding_ICalculator_CreateServiceEndpoint(
//    __in WS_HTTP_SSL_BINDING_TEMPLATE* templateValue,
//    __in_opt WS_STRING address,
//    __in_opt struct DefaultBinding_ICalculatorFunctionTable* functionTable,
//    __in_opt WS_SERVICE_SECURITY_CALLBACK authorizationCallback,
//    __in_ecount_opt(endpointPropertyCount) WS_SERVICE_ENDPOINT_PROPERTY* endpointProperties,
//    __in const ULONG endpointPropertyCount,
//    __in WS_HEAP* heap,
//    __deref_out_opt WS_SERVICE_ENDPOINT** serviceEndpoint,
//    __in_opt WS_ERROR* error);
//
// This function can be used to create a Service Host object, which has to be 
// created before a web services starts receiving requests from its clients.
//
// For more information about content of this file, please see the documentation for
// Wsutil compiler.
#if _MSC_VER > 1000 
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

// The following client functions were generated:

//     BasicHttpBinding_IService_Login
//     BasicHttpBinding_IService_Score
//     BasicHttpBinding_IService_ListLevels
//     BasicHttpBinding_IService_LoadLevel
//     BasicHttpBinding_IService_getTexturesList
//     BasicHttpBinding_IService_downloadTexture
//     BasicHttpBinding_IService_getSoundsList
//     BasicHttpBinding_IService_downloadSound
//     BasicHttpBinding_IService_uploadRoute
//     BasicHttpBinding_IService_getEnemiesModelsList
//     BasicHttpBinding_IService_downloadEnemiesModels

// The following server function tables were generated:

//     struct BasicHttpBinding_IServiceFunctionTable

// the following policy helpers were generated:

//  BasicHttpBinding_IService_CreateServiceProxy;
//  BasicHttpBinding_IService_CreateServiceEndpoint;

// The following header files must be included in this order before this one

// #include <WebServices.h>
// #include "tempuri.org.xsd.h"

////////////////////////////////////////////////
// Policy helper routines
////////////////////////////////////////////////

//  WS_CHANNEL_PROPERTY_ENCODING = WS_ENCODING_XML_UTF8,
//  WS_CHANNEL_PROPERTY_ADDRESSING_VERSION = WS_ADDRESSING_VERSION_TRANSPORT,
//  WS_ENVELOPE_VERSION = WS_ENVELOPE_VERSION_SOAP_1_1,
// client channel type: WS_CHANNEL_TYPE_REQUEST, service endpoint channel type: WS_CHANNEL_TYPE_REPLY

HRESULT BasicHttpBinding_IService_CreateServiceProxy(
    __in_opt WS_HTTP_BINDING_TEMPLATE* templateValue,
    __in_ecount_opt(proxyPropertyCount) const WS_PROXY_PROPERTY* proxyProperties,
    __in const ULONG proxyPropertyCount,
    __deref_out_opt WS_SERVICE_PROXY** _serviceProxy,
    __in_opt WS_ERROR* error);

struct BasicHttpBinding_IServiceFunctionTable;
HRESULT BasicHttpBinding_IService_CreateServiceEndpoint(
    __in_opt WS_HTTP_BINDING_TEMPLATE* templateValue,
    __in_opt CONST WS_STRING* address,
    __in_opt struct BasicHttpBinding_IServiceFunctionTable* functionTable,
    __in_opt WS_SERVICE_SECURITY_CALLBACK authorizationCallback,
    __in_ecount_opt(endpointPropertyCount) WS_SERVICE_ENDPOINT_PROPERTY* endpointProperties,
    __in const ULONG endpointPropertyCount,
    __in WS_HEAP* heap,
    __deref_out_opt WS_SERVICE_ENDPOINT** serviceEndpoint,
    __in_opt WS_ERROR* error);

////////////////////////////////////////////////
// Client functions definitions
////////////////////////////////////////////////

// operation: BasicHttpBinding_IService_Login
HRESULT WINAPI BasicHttpBinding_IService_Login(
    __in WS_SERVICE_PROXY* _serviceProxy,
    __in_opt __nullterminated WCHAR* username, 
    __in_opt __nullterminated WCHAR* password, 
    __out int* LoginResult, 
    __in WS_HEAP* _heap,
    __in_ecount_opt(_callPropertyCount) const WS_CALL_PROPERTY* _callProperties,
    __in const ULONG _callPropertyCount,
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

// operation: BasicHttpBinding_IService_Score
HRESULT WINAPI BasicHttpBinding_IService_Score(
    __in WS_SERVICE_PROXY* _serviceProxy,
    __in_opt __nullterminated WCHAR* username, 
    __in_opt __nullterminated WCHAR* levelName, 
    __in int score, 
    __in WS_HEAP* _heap,
    __in_ecount_opt(_callPropertyCount) const WS_CALL_PROPERTY* _callProperties,
    __in const ULONG _callPropertyCount,
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

// operation: BasicHttpBinding_IService_ListLevels
HRESULT WINAPI BasicHttpBinding_IService_ListLevels(
    __in WS_SERVICE_PROXY* _serviceProxy,
    __out_opt __deref __nullterminated WCHAR** ListLevelsResult, 
    __in WS_HEAP* _heap,
    __in_ecount_opt(_callPropertyCount) const WS_CALL_PROPERTY* _callProperties,
    __in const ULONG _callPropertyCount,
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

// operation: BasicHttpBinding_IService_LoadLevel
HRESULT WINAPI BasicHttpBinding_IService_LoadLevel(
    __in WS_SERVICE_PROXY* _serviceProxy,
    __in_opt __nullterminated WCHAR* levelName, 
    __out_opt __deref __nullterminated WCHAR** LoadLevelResult, 
    __in WS_HEAP* _heap,
    __in_ecount_opt(_callPropertyCount) const WS_CALL_PROPERTY* _callProperties,
    __in const ULONG _callPropertyCount,
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

// operation: BasicHttpBinding_IService_getTexturesList
HRESULT WINAPI BasicHttpBinding_IService_getTexturesList(
    __in WS_SERVICE_PROXY* _serviceProxy,
    __out_opt __deref __nullterminated WCHAR** getTexturesListResult, 
    __in WS_HEAP* _heap,
    __in_ecount_opt(_callPropertyCount) const WS_CALL_PROPERTY* _callProperties,
    __in const ULONG _callPropertyCount,
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

// operation: BasicHttpBinding_IService_downloadTexture
HRESULT WINAPI BasicHttpBinding_IService_downloadTexture(
    __in WS_SERVICE_PROXY* _serviceProxy,
    __in_opt __nullterminated WCHAR* textureName, 
    __out_opt __deref __nullterminated WCHAR** downloadTextureResult, 
    __in WS_HEAP* _heap,
    __in_ecount_opt(_callPropertyCount) const WS_CALL_PROPERTY* _callProperties,
    __in const ULONG _callPropertyCount,
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

// operation: BasicHttpBinding_IService_getSoundsList
HRESULT WINAPI BasicHttpBinding_IService_getSoundsList(
    __in WS_SERVICE_PROXY* _serviceProxy,
    __out_opt __deref __nullterminated WCHAR** getSoundsListResult, 
    __in WS_HEAP* _heap,
    __in_ecount_opt(_callPropertyCount) const WS_CALL_PROPERTY* _callProperties,
    __in const ULONG _callPropertyCount,
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

// operation: BasicHttpBinding_IService_downloadSound
HRESULT WINAPI BasicHttpBinding_IService_downloadSound(
    __in WS_SERVICE_PROXY* _serviceProxy,
    __in_opt __nullterminated WCHAR* soundName, 
    __out_opt __deref __nullterminated WCHAR** downloadSoundResult, 
    __in WS_HEAP* _heap,
    __in_ecount_opt(_callPropertyCount) const WS_CALL_PROPERTY* _callProperties,
    __in const ULONG _callPropertyCount,
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

// operation: BasicHttpBinding_IService_uploadRoute
HRESULT WINAPI BasicHttpBinding_IService_uploadRoute(
    __in WS_SERVICE_PROXY* _serviceProxy,
    __in_opt __nullterminated WCHAR* username, 
    __in_opt __nullterminated WCHAR* level, 
    __in_opt __nullterminated WCHAR* route, 
    __in WS_HEAP* _heap,
    __in_ecount_opt(_callPropertyCount) const WS_CALL_PROPERTY* _callProperties,
    __in const ULONG _callPropertyCount,
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

// operation: BasicHttpBinding_IService_getEnemiesModelsList
HRESULT WINAPI BasicHttpBinding_IService_getEnemiesModelsList(
    __in WS_SERVICE_PROXY* _serviceProxy,
    __out_opt __deref __nullterminated WCHAR** getEnemiesModelsListResult, 
    __in WS_HEAP* _heap,
    __in_ecount_opt(_callPropertyCount) const WS_CALL_PROPERTY* _callProperties,
    __in const ULONG _callPropertyCount,
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

// operation: BasicHttpBinding_IService_downloadEnemiesModels
HRESULT WINAPI BasicHttpBinding_IService_downloadEnemiesModels(
    __in WS_SERVICE_PROXY* _serviceProxy,
    __in_opt __nullterminated WCHAR* modelName, 
    __out_opt __deref __nullterminated WCHAR** downloadEnemiesModelsResult, 
    __in WS_HEAP* _heap,
    __in_ecount_opt(_callPropertyCount) const WS_CALL_PROPERTY* _callProperties,
    __in const ULONG _callPropertyCount,
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

////////////////////////////////////////////////
// Service functions definitions
////////////////////////////////////////////////

typedef HRESULT (CALLBACK* BasicHttpBinding_IService_LoginCallback) (
    __in const WS_OPERATION_CONTEXT* _context,
    __in_opt __nullterminated WCHAR* username, 
    __in_opt __nullterminated WCHAR* password, 
    __out int* LoginResult, 
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

typedef HRESULT (CALLBACK* BasicHttpBinding_IService_ScoreCallback) (
    __in const WS_OPERATION_CONTEXT* _context,
    __in_opt __nullterminated WCHAR* username, 
    __in_opt __nullterminated WCHAR* levelName, 
    __in int score, 
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

typedef HRESULT (CALLBACK* BasicHttpBinding_IService_ListLevelsCallback) (
    __in const WS_OPERATION_CONTEXT* _context,
    __out_opt __deref __nullterminated WCHAR** ListLevelsResult, 
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

typedef HRESULT (CALLBACK* BasicHttpBinding_IService_LoadLevelCallback) (
    __in const WS_OPERATION_CONTEXT* _context,
    __in_opt __nullterminated WCHAR* levelName, 
    __out_opt __deref __nullterminated WCHAR** LoadLevelResult, 
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

typedef HRESULT (CALLBACK* BasicHttpBinding_IService_getTexturesListCallback) (
    __in const WS_OPERATION_CONTEXT* _context,
    __out_opt __deref __nullterminated WCHAR** getTexturesListResult, 
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

typedef HRESULT (CALLBACK* BasicHttpBinding_IService_downloadTextureCallback) (
    __in const WS_OPERATION_CONTEXT* _context,
    __in_opt __nullterminated WCHAR* textureName, 
    __out_opt __deref __nullterminated WCHAR** downloadTextureResult, 
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

typedef HRESULT (CALLBACK* BasicHttpBinding_IService_getSoundsListCallback) (
    __in const WS_OPERATION_CONTEXT* _context,
    __out_opt __deref __nullterminated WCHAR** getSoundsListResult, 
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

typedef HRESULT (CALLBACK* BasicHttpBinding_IService_downloadSoundCallback) (
    __in const WS_OPERATION_CONTEXT* _context,
    __in_opt __nullterminated WCHAR* soundName, 
    __out_opt __deref __nullterminated WCHAR** downloadSoundResult, 
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

typedef HRESULT (CALLBACK* BasicHttpBinding_IService_uploadRouteCallback) (
    __in const WS_OPERATION_CONTEXT* _context,
    __in_opt __nullterminated WCHAR* username, 
    __in_opt __nullterminated WCHAR* level, 
    __in_opt __nullterminated WCHAR* route, 
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

typedef HRESULT (CALLBACK* BasicHttpBinding_IService_getEnemiesModelsListCallback) (
    __in const WS_OPERATION_CONTEXT* _context,
    __out_opt __deref __nullterminated WCHAR** getEnemiesModelsListResult, 
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

typedef HRESULT (CALLBACK* BasicHttpBinding_IService_downloadEnemiesModelsCallback) (
    __in const WS_OPERATION_CONTEXT* _context,
    __in_opt __nullterminated WCHAR* modelName, 
    __out_opt __deref __nullterminated WCHAR** downloadEnemiesModelsResult, 
    __in_opt const WS_ASYNC_CONTEXT* _asyncContext,
    __in_opt WS_ERROR* _error);

// binding: BasicHttpBinding_IService
typedef struct BasicHttpBinding_IServiceFunctionTable 
{
    BasicHttpBinding_IService_LoginCallback BasicHttpBinding_IService_Login;
    BasicHttpBinding_IService_ScoreCallback BasicHttpBinding_IService_Score;
    BasicHttpBinding_IService_ListLevelsCallback BasicHttpBinding_IService_ListLevels;
    BasicHttpBinding_IService_LoadLevelCallback BasicHttpBinding_IService_LoadLevel;
    BasicHttpBinding_IService_getTexturesListCallback BasicHttpBinding_IService_getTexturesList;
    BasicHttpBinding_IService_downloadTextureCallback BasicHttpBinding_IService_downloadTexture;
    BasicHttpBinding_IService_getSoundsListCallback BasicHttpBinding_IService_getSoundsList;
    BasicHttpBinding_IService_downloadSoundCallback BasicHttpBinding_IService_downloadSound;
    BasicHttpBinding_IService_uploadRouteCallback BasicHttpBinding_IService_uploadRoute;
    BasicHttpBinding_IService_getEnemiesModelsListCallback BasicHttpBinding_IService_getEnemiesModelsList;
    BasicHttpBinding_IService_downloadEnemiesModelsCallback BasicHttpBinding_IService_downloadEnemiesModels;
} BasicHttpBinding_IServiceFunctionTable;

////////////////////////////////////////////////
// Global web service descriptions.
////////////////////////////////////////////////

typedef struct _tempuri_org_wsdl
{
    struct // messages
    {
        // message: IService_Login_InputMessage
        // c type: _Login
        // action: "http://tempuri.org/IService/Login"
        // messageDescription: tempuri_org_wsdl.messages.IService_Login_InputMessage
        WS_MESSAGE_DESCRIPTION IService_Login_InputMessage;
        
        // message: IService_Login_OutputMessage
        // c type: _LoginResponse
        // action: "http://tempuri.org/IService/LoginResponse"
        // messageDescription: tempuri_org_wsdl.messages.IService_Login_OutputMessage
        WS_MESSAGE_DESCRIPTION IService_Login_OutputMessage;
        
        // message: IService_Score_InputMessage
        // c type: _Score
        // action: "http://tempuri.org/IService/Score"
        // messageDescription: tempuri_org_wsdl.messages.IService_Score_InputMessage
        WS_MESSAGE_DESCRIPTION IService_Score_InputMessage;
        
        // message: IService_Score_OutputMessage
        // c type: _ScoreResponse
        // action: "http://tempuri.org/IService/ScoreResponse"
        // messageDescription: tempuri_org_wsdl.messages.IService_Score_OutputMessage
        WS_MESSAGE_DESCRIPTION IService_Score_OutputMessage;
        
        // message: IService_ListLevels_InputMessage
        // c type: _ListLevels
        // action: "http://tempuri.org/IService/ListLevels"
        // messageDescription: tempuri_org_wsdl.messages.IService_ListLevels_InputMessage
        WS_MESSAGE_DESCRIPTION IService_ListLevels_InputMessage;
        
        // message: IService_ListLevels_OutputMessage
        // c type: _ListLevelsResponse
        // action: "http://tempuri.org/IService/ListLevelsResponse"
        // messageDescription: tempuri_org_wsdl.messages.IService_ListLevels_OutputMessage
        WS_MESSAGE_DESCRIPTION IService_ListLevels_OutputMessage;
        
        // message: IService_LoadLevel_InputMessage
        // c type: _LoadLevel
        // action: "http://tempuri.org/IService/LoadLevel"
        // messageDescription: tempuri_org_wsdl.messages.IService_LoadLevel_InputMessage
        WS_MESSAGE_DESCRIPTION IService_LoadLevel_InputMessage;
        
        // message: IService_LoadLevel_OutputMessage
        // c type: _LoadLevelResponse
        // action: "http://tempuri.org/IService/LoadLevelResponse"
        // messageDescription: tempuri_org_wsdl.messages.IService_LoadLevel_OutputMessage
        WS_MESSAGE_DESCRIPTION IService_LoadLevel_OutputMessage;
        
        // message: IService_getTexturesList_InputMessage
        // c type: _getTexturesList
        // action: "http://tempuri.org/IService/getTexturesList"
        // messageDescription: tempuri_org_wsdl.messages.IService_getTexturesList_InputMessage
        WS_MESSAGE_DESCRIPTION IService_getTexturesList_InputMessage;
        
        // message: IService_getTexturesList_OutputMessage
        // c type: _getTexturesListResponse
        // action: "http://tempuri.org/IService/getTexturesListResponse"
        // messageDescription: tempuri_org_wsdl.messages.IService_getTexturesList_OutputMessage
        WS_MESSAGE_DESCRIPTION IService_getTexturesList_OutputMessage;
        
        // message: IService_downloadTexture_InputMessage
        // c type: _downloadTexture
        // action: "http://tempuri.org/IService/downloadTexture"
        // messageDescription: tempuri_org_wsdl.messages.IService_downloadTexture_InputMessage
        WS_MESSAGE_DESCRIPTION IService_downloadTexture_InputMessage;
        
        // message: IService_downloadTexture_OutputMessage
        // c type: _downloadTextureResponse
        // action: "http://tempuri.org/IService/downloadTextureResponse"
        // messageDescription: tempuri_org_wsdl.messages.IService_downloadTexture_OutputMessage
        WS_MESSAGE_DESCRIPTION IService_downloadTexture_OutputMessage;
        
        // message: IService_getSoundsList_InputMessage
        // c type: _getSoundsList
        // action: "http://tempuri.org/IService/getSoundsList"
        // messageDescription: tempuri_org_wsdl.messages.IService_getSoundsList_InputMessage
        WS_MESSAGE_DESCRIPTION IService_getSoundsList_InputMessage;
        
        // message: IService_getSoundsList_OutputMessage
        // c type: _getSoundsListResponse
        // action: "http://tempuri.org/IService/getSoundsListResponse"
        // messageDescription: tempuri_org_wsdl.messages.IService_getSoundsList_OutputMessage
        WS_MESSAGE_DESCRIPTION IService_getSoundsList_OutputMessage;
        
        // message: IService_downloadSound_InputMessage
        // c type: _downloadSound
        // action: "http://tempuri.org/IService/downloadSound"
        // messageDescription: tempuri_org_wsdl.messages.IService_downloadSound_InputMessage
        WS_MESSAGE_DESCRIPTION IService_downloadSound_InputMessage;
        
        // message: IService_downloadSound_OutputMessage
        // c type: _downloadSoundResponse
        // action: "http://tempuri.org/IService/downloadSoundResponse"
        // messageDescription: tempuri_org_wsdl.messages.IService_downloadSound_OutputMessage
        WS_MESSAGE_DESCRIPTION IService_downloadSound_OutputMessage;
        
        // message: IService_uploadRoute_InputMessage
        // c type: _uploadRoute
        // action: "http://tempuri.org/IService/uploadRoute"
        // messageDescription: tempuri_org_wsdl.messages.IService_uploadRoute_InputMessage
        WS_MESSAGE_DESCRIPTION IService_uploadRoute_InputMessage;
        
        // message: IService_uploadRoute_OutputMessage
        // c type: _uploadRouteResponse
        // action: "http://tempuri.org/IService/uploadRouteResponse"
        // messageDescription: tempuri_org_wsdl.messages.IService_uploadRoute_OutputMessage
        WS_MESSAGE_DESCRIPTION IService_uploadRoute_OutputMessage;
        
        // message: IService_getEnemiesModelsList_InputMessage
        // c type: _getEnemiesModelsList
        // action: "http://tempuri.org/IService/getEnemiesModelsList"
        // messageDescription: tempuri_org_wsdl.messages.IService_getEnemiesModelsList_InputMessage
        WS_MESSAGE_DESCRIPTION IService_getEnemiesModelsList_InputMessage;
        
        // message: IService_getEnemiesModelsList_OutputMessage
        // c type: _getEnemiesModelsListResponse
        // action: "http://tempuri.org/IService/getEnemiesModelsListResponse"
        // messageDescription: tempuri_org_wsdl.messages.IService_getEnemiesModelsList_OutputMessage
        WS_MESSAGE_DESCRIPTION IService_getEnemiesModelsList_OutputMessage;
        
        // message: IService_downloadEnemiesModels_InputMessage
        // c type: _downloadEnemiesModels
        // action: "http://tempuri.org/IService/downloadEnemiesModels"
        // messageDescription: tempuri_org_wsdl.messages.IService_downloadEnemiesModels_InputMessage
        WS_MESSAGE_DESCRIPTION IService_downloadEnemiesModels_InputMessage;
        
        // message: IService_downloadEnemiesModels_OutputMessage
        // c type: _downloadEnemiesModelsResponse
        // action: "http://tempuri.org/IService/downloadEnemiesModelsResponse"
        // messageDescription: tempuri_org_wsdl.messages.IService_downloadEnemiesModels_OutputMessage
        WS_MESSAGE_DESCRIPTION IService_downloadEnemiesModels_OutputMessage;
        
    } messages;
    struct // contracts
    {
        // binding: BasicHttpBinding_IService
        // portType: IService
        // operation: BasicHttpBinding_IService_Login
        //     input message: IService_Login_InputMessage
        //     output message: IService_Login_OutputMessage
        // operation: BasicHttpBinding_IService_Score
        //     input message: IService_Score_InputMessage
        //     output message: IService_Score_OutputMessage
        // operation: BasicHttpBinding_IService_ListLevels
        //     input message: IService_ListLevels_InputMessage
        //     output message: IService_ListLevels_OutputMessage
        // operation: BasicHttpBinding_IService_LoadLevel
        //     input message: IService_LoadLevel_InputMessage
        //     output message: IService_LoadLevel_OutputMessage
        // operation: BasicHttpBinding_IService_getTexturesList
        //     input message: IService_getTexturesList_InputMessage
        //     output message: IService_getTexturesList_OutputMessage
        // operation: BasicHttpBinding_IService_downloadTexture
        //     input message: IService_downloadTexture_InputMessage
        //     output message: IService_downloadTexture_OutputMessage
        // operation: BasicHttpBinding_IService_getSoundsList
        //     input message: IService_getSoundsList_InputMessage
        //     output message: IService_getSoundsList_OutputMessage
        // operation: BasicHttpBinding_IService_downloadSound
        //     input message: IService_downloadSound_InputMessage
        //     output message: IService_downloadSound_OutputMessage
        // operation: BasicHttpBinding_IService_uploadRoute
        //     input message: IService_uploadRoute_InputMessage
        //     output message: IService_uploadRoute_OutputMessage
        // operation: BasicHttpBinding_IService_getEnemiesModelsList
        //     input message: IService_getEnemiesModelsList_InputMessage
        //     output message: IService_getEnemiesModelsList_OutputMessage
        // operation: BasicHttpBinding_IService_downloadEnemiesModels
        //     input message: IService_downloadEnemiesModels_InputMessage
        //     output message: IService_downloadEnemiesModels_OutputMessage
        // contractDescription: tempuri_org_wsdl.contracts.BasicHttpBinding_IService
        WS_CONTRACT_DESCRIPTION BasicHttpBinding_IService;
        
    } contracts;
    struct // policies
    {
        // policy for binding: BasicHttpBinding_IService
        // port name: BasicHttpBinding_IService, binding: BasicHttpBinding_IService, namespace: http://tempuri.org/
        WS_HTTP_POLICY_DESCRIPTION BasicHttpBinding_IService;
    } policies;
} _tempuri_org_wsdl;

extern const _tempuri_org_wsdl tempuri_org_wsdl;

#ifdef __cplusplus
}
#endif

