#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/unistd.h>
#include <sys/time.h>

#include "ppapi/c/pp_errors.h"
#include "ppapi/c/pp_module.h"
#include "ppapi/c/pp_var.h"
#include "ppapi/c/ppb.h"
#include "ppapi/c/ppb_core.h"
#include "ppapi/c/ppb_instance.h"
#include "ppapi/c/ppb_messaging.h"
#include "ppapi/c/ppb_var.h"
#include "ppapi/c/ppp.h"
#include "ppapi/c/ppp_instance.h"
#include "ppapi/c/ppp_messaging.h"
#include "nacl_io/nacl_io.h"
#include "IOTCAPIs.h"
#include "RDTAPIs.h"

PPB_Messaging*   ppb_messaging_interface = NULL;
PPB_Var*         ppb_var_interface = NULL;
PPB_Core*        ppb_core_interface = NULL;

pthread_t   g_initIOTCThread;
pthread_t   g_IOTCClientThread;
pthread_t   g_RDTClientThread;
pthread_t   g_PPAPIThread;

PP_Instance 		g_Instance;
PPB_GetInterface 	g_Browser;

#define MSG_IOTC 	'i'
#define MSG_RDT 	'r'

#define START_STRING 			"Start"
#define SESSION_READ_TIMEOUTMS 	1000
#define RDT_WAIT_TIMEOUTMS 		30000
#define MAX_BUF_SIZE 			102400
#define DEFAULT_CHANNEL 		0


void PostMessage(const char* str) 
{
	if (NULL == str) {
		return;
	}
		
	if (NULL == ppb_messaging_interface) {
		return;
	}
		
	if (0 == g_Instance) {
		return;
	}
		
	if (NULL != ppb_var_interface) {
		struct PP_Var var = ppb_var_interface->VarFromUtf8(str, strlen(str));
		ppb_messaging_interface->PostMessage(g_Instance, var);
		ppb_var_interface->Release(var);
	}
}

void* IOTCClientThreadFunc(void* data)
{
	char *deviceUID = (char *)data;
	char message[255];
	int  sessionID = 0;
	int ret;
	
	unsigned int version = 0;
	IOTC_Get_Version(&version);
	sprintf(message, "IOTC Version %X", version);
	PostMessage(message);
	
	sessionID = IOTC_Get_SessionID();
	if(sessionID < 0)
	{
		sprintf(message, "IOTC_Get_SessionID error code [%d]", sessionID);
		PostMessage(message);
		return (void *)(-1);
	}
	ret = IOTC_Connect_ByUID_Parallel(deviceUID ,sessionID);
	if(ret < 0){
		sprintf(message, "Connect to %s failed, return value %d", deviceUID, ret);
		PostMessage(message);
		return (void *)(-1);
	} else {
		sprintf(message, "Connect to %s success, IOTCSessionID %d", deviceUID, sessionID);
		PostMessage(message);
	}

	
	char ReadBuf[IOTC_MAX_PACKET_SIZE];
	int  nByte = 0;	
    int  sessionCheckRet = 0;
    struct st_SInfo sessionInfo;
	
    sessionCheckRet = IOTC_Session_Check(sessionID, &sessionInfo);
    sprintf(message, "sessionCheckRet = %d", sessionCheckRet);
	PostMessage(message);
	sprintf(message, "Mode       = %c", sessionInfo.Mode+'0');
	PostMessage(message);
	sprintf(message, "NatType    = %c", sessionInfo.NatType+'0');
	PostMessage(message);
	sprintf(message, "RemoteIP   = %s", sessionInfo.RemoteIP);
	PostMessage(message);
	sprintf(message, "RemotePort = %d", sessionInfo.RemotePort);
	PostMessage(message);
	

	do{
		nByte = IOTC_Session_Read(sessionID, ReadBuf, IOTC_MAX_PACKET_SIZE, SESSION_READ_TIMEOUTMS, DEFAULT_CHANNEL);
		if(0 < nByte) {
			ReadBuf[nByte] = 0;
			sprintf(message, "IOTC_Session_Read  %d:%s\r\n", nByte, ReadBuf);
			PostMessage(message);
			
			if (strcmp(ReadBuf, "end") == 0)
				break;

			// echo back
			nByte = IOTC_Session_Write(sessionID, ReadBuf, (int)strlen(ReadBuf), DEFAULT_CHANNEL);
			
		} else if( IOTC_ER_REMOTE_TIMEOUT_DISCONNECT == nByte
				|| IOTC_ER_SESSION_CLOSE_BY_REMOTE ==  nByte
				|| IOTC_ER_INVALID_SID == nByte ) {
				sprintf(message, "IOTC_Session_Write failed, return value %d\r\n", nByte);
				PostMessage(message);
				break;
		} else {
			sprintf(message, "IOTC_Session_Write failed, return value %d\r\n", nByte);
			PostMessage(message);
		}
	}while(1);

	sprintf(message, "IOTC_Session_Write  %d:%s\r\n", nByte, ReadBuf);
	PostMessage(message);

	IOTC_Session_Close(sessionID);
	sprintf(message, "IOTC_Session_Close(%d)\n", sessionID);
	PostMessage(message);
	
	return NULL;
}

void* RDTClientThreadFunc(void* data)
{
	char *deviceUID = (char *)data;
	char message[255];
	int  sessionID = 0;
	int  ret = 0;
	
	ret = IOTC_Initialize2(0);

	if(IOTC_ER_NoERROR == ret) {
		PostMessage("IOTC_Initialize2 Success");
	} else if(IOTC_ER_ALREADY_INITIALIZED == ret) {
		PostMessage("IOTC_ER_ALREADY_INITIALIZED");
	} else {
		sprintf(message, "IOTC_Initialize2 failed  %d", ret);
		PostMessage(message);
		return (void *)(-1);
	}
	unsigned int version = 0;
	IOTC_Get_Version(&version);
	sprintf(message, "IOTC Version %X", version);
	PostMessage(message);
	
	ret = RDT_Initialize();
	
	if(IOTC_ER_NoERROR <= ret) {
		PostMessage("RDT_Initialize Success");
	} else if(RDT_ER_ALREADY_INITIALIZED == ret){
		PostMessage("RDT_ER_ALREADY_INITIALIZED");
	} else {
		sprintf(message, "RDT_Initialize failed  %d", ret);
		PostMessage(message);
		return (void *)(-1);
	}
	
	ret = RDT_GetRDTApiVer();
	sprintf(message, "RDT Api Version %x!\n", ret);
	PostMessage(message);

	
	sessionID = IOTC_Get_SessionID();
	if(sessionID < 0)
	{
		sprintf(message, "IOTC_Get_SessionID error code [%d]", sessionID);
		PostMessage(message);
		return (void *)(-1);
	}
	ret = IOTC_Connect_ByUID_Parallel(deviceUID, sessionID);
	if(ret < 0) {
		sprintf(message, "Connect to %s failed, return value %d", deviceUID, ret);
		PostMessage(message);
		return (void *)(-1);
	} else {
		sprintf(message, "Connect to %s success, IOTCSessionID %d", deviceUID, sessionID);
		PostMessage(message);
	}
	
	int nRDTIndex = RDT_Create(sessionID, RDT_WAIT_TIMEOUTMS, 0);
	if(nRDTIndex < 0) {
		sprintf(message, "RDT_Create failed  %d", nRDTIndex);
		PostMessage(message);
		IOTC_Session_Close(sessionID);
		return (void *)(-1);
	}
	
	/*
    int sessionCheckRet = 0;
    struct st_SInfo sessionInfo;
    sessionCheckRet = IOTC_Session_Check(sessionID, &sessionInfo);
    sprintf(message, "\nsessionCheckRet = %d", sessionCheckRet);
	PostMessage(message);
	sprintf(message, "Mode       = %c", sessionInfo.Mode+'0');
	PostMessage(message);
	sprintf(message, "NatType    = %c", sessionInfo.NatType+'0');
	PostMessage(message);
	sprintf(message, "RemoteIP   = %s", sessionInfo.RemoteIP);
	PostMessage(message);
	sprintf(message, "RemotePort = %d", sessionInfo.RemotePort);
	PostMessage(message);
    */
	
	int sessionCheckRet = 0;
	unsigned char sessionMode; 
    struct st_SInfoEx sessionInfo;
	sessionInfo.size = sizeof(struct st_SInfoEx);
	
    sessionCheckRet = IOTC_Session_Check_Ex(sessionID, &sessionInfo);
    sprintf(message, "\nsessionCheckRet = %d", sessionCheckRet);
	PostMessage(message);
	strncpy((char*)&sessionMode, (char*)&sessionInfo.Mode, 1);
	sprintf(message, "Mode          = %c", sessionInfo.Mode+'0');
	PostMessage(message);
	sprintf(message, "LocalNatType  = %c", sessionInfo.LocalNatType+'0');
	PostMessage(message);
	sprintf(message, "RemoteNatType = %c", sessionInfo.RemoteNatType+'0');
	PostMessage(message);
	sprintf(message, "RemoteIP      = %s", sessionInfo.RemoteIP);
	PostMessage(message);
	sprintf(message, "RemotePort    = %d", sessionInfo.RemotePort);
	PostMessage(message);
	
	char buf[MAX_BUF_SIZE] = {0};
	sprintf(buf, "%d", 1);
	ret = RDT_Write(nRDTIndex, buf, strlen(buf));
	if(ret < 0) {
		sprintf(message, "RDT_Write failed  %d", ret);
		PostMessage(message);
		RDT_Destroy(nRDTIndex);
		IOTC_Session_Close(sessionID);
		return (void *)(-1);
	}
	
	ret = RDT_Read(nRDTIndex, buf, 1024, RDT_WAIT_TIMEOUTMS);
	if(ret < 0) {
		sprintf(message, "RDT_Read file size failed  %d", ret);
		PostMessage(message);
		RDT_Destroy(nRDTIndex);
		IOTC_Session_Close(sessionID);
		return (void *)(-1);
	}
	int fileSize = atoi(buf);
	int remainReadSize;
	int totalReadSize;
	
	strcpy(buf, START_STRING);
	ret = RDT_Write(nRDTIndex, buf, strlen(buf));
	if(ret < 0) {
		sprintf(message, "RDT_Write send start failed  %d", ret);
		PostMessage(message);
		RDT_Destroy(nRDTIndex);
		IOTC_Session_Close(sessionID);
		return (void *)(-1);
	}
	
	sprintf(message, "fileSize  %d", fileSize);
	PostMessage(message);
	
	struct timeval tvStart, tvEnd;
	struct st_RDT_Status rdtStatus;
	unsigned int round = 0;
	int i;
	
	for(i=0; i<1; i++) {
		if(RDT_Status_Check(nRDTIndex, &rdtStatus) < 0) {
			sprintf(message, "RDT_Status_Check error!");
			PostMessage(message);
			break;
		}
		remainReadSize = fileSize;
		totalReadSize = 0;
		
		//PostMessage("\nfile content\n");
		
		gettimeofday(&tvStart, NULL);
		while(1) {
			sessionCheckRet = IOTC_Session_Check_Ex(sessionID, &sessionInfo);
			if(strncmp((char*)&sessionMode, (char*)&sessionInfo.Mode, 1)) {
				sprintf(message, "\nsession mode changed from %c to %c\n", sessionMode+'0', sessionInfo.Mode+'0');
				strncpy((char*)&sessionMode, (char*)&sessionInfo.Mode, 1);
			}
			
			if(remainReadSize < MAX_BUF_SIZE) {
				ret = RDT_Read(nRDTIndex, buf, remainReadSize, RDT_WAIT_TIMEOUTMS);
			} else {
				ret = RDT_Read(nRDTIndex, buf, MAX_BUF_SIZE, RDT_WAIT_TIMEOUTMS);
			}
			
			if(ret < 0 && ret != RDT_ER_TIMEOUT) {
				sprintf(message, "RDT_Read data failed  %d", ret);
				PostMessage(message);
				break;
			}
			remainReadSize -= ret;
			totalReadSize += ret;
			if(round++ % 5 == 0) {
				PostMessage(".");
			}
		    // print received file content
			//PostMessage(buf);
			
			if(remainReadSize == 0) {
				break;
			}
		}
		gettimeofday(&tvEnd, NULL);
		
		if(ret >= 0){
			sprintf(message, "\nRDT_Read receive file %d  OK, received size : %d ,elapsed time : %lldms\n", i+1, totalReadSize, (tvEnd.tv_sec - tvStart.tv_sec)*1000+(tvEnd.tv_usec - tvStart.tv_usec)/1000);
		} else {
			sprintf(message, "\nRDT_Read receive file %d  failed, received size : %d, elapsed time : %lldms\n", i+1, totalReadSize, (tvEnd.tv_sec - tvStart.tv_sec)*1000+(tvEnd.tv_usec - tvStart.tv_usec)/1000);
		}
		
		PostMessage(message);
	}
	
	struct st_RDT_Status RDT_Status;
	
	ret =  RDT_Status_Check(nRDTIndex, &RDT_Status);
	if(ret){
		sprintf(message, "RDT_Status_Check calling....failed  %d\n", ret);
		PostMessage(message);
	} else {
		PostMessage("RDT_Status_Check calling....success");
		sprintf(message, "Timeout            %u", RDT_Status.Timeout);
		PostMessage(message);
		sprintf(message, "TimeoutThreshold   %u", RDT_Status.TimeoutThreshold);
		PostMessage(message);
		sprintf(message, "BufSizeInSendQueue %u", RDT_Status.BufSizeInSendQueue);
		PostMessage(message);
		sprintf(message, "BufSizeInRecvQueue %u\n", RDT_Status.BufSizeInRecvQueue);
		PostMessage(message);
	}
	
	ret = RDT_Destroy(nRDTIndex);
	if(ret) {
		sprintf(message, "RDT_Destroy failed  %d", ret);
		PostMessage(message);
	} else {
		PostMessage("RDT_Destroy success");
	}
	
	IOTC_Session_Close(sessionID);
	sprintf(message, "IOTC_Session_Close(%d)", sessionID);
	PostMessage(message);

	ret = RDT_DeInitialize();
	if(ret) {
		sprintf(message, "RDT_DeInitialize failed  %d", ret);
		PostMessage(message);
	} else {
		PostMessage("RDT_DeInitialize success");
	}

	ret = IOTC_DeInitialize();
	if(ret) {
		sprintf(message, "IOTC_DeInitialize failed  %d", ret);
		PostMessage(message);
	} else {
		PostMessage("IOTC_DeInitialize success");
	}
	
	return (void *)0;
}

void* initIOTCThreadFunc(void* data)
{
	int ret = 0;
	char message[128];
	
	ret = IOTC_Initialize2(0);
	
	if(IOTC_ER_NoERROR == ret){
		PostMessage("IOTC_Initialize Success");
	} else {
		sprintf(message, "IOTC_Initialize failed  ret = %d", ret);
		PostMessage(message);
	}
	
	return NULL;
}



static PP_Bool Instance_DidCreate(PP_Instance instance, uint32_t argc, const char* argn[], const char* argv[])
{
  g_Instance    = instance;
  g_PPAPIThread = pthread_self();
  PostMessage("Instance_DidCreate");
  
  char message[128];
  
  int ret = nacl_io_init_ppapi(g_Instance, g_Browser);
  sprintf(message, "Instance_DidCreate  nacl_io_init_ppapi  ret = %d", ret);
  PostMessage(message);

  pthread_create(&g_initIOTCThread, NULL, initIOTCThreadFunc, (void*)0);

  return PP_TRUE;
}

static void Instance_DidDestroy(PP_Instance instance) {}

static void Instance_DidChangeView(PP_Instance instance, PP_Resource view_resource) {}

static void Instance_DidChangeFocus(PP_Instance instance, PP_Bool has_focus) {}

static PP_Bool Instance_HandleDocumentLoad(PP_Instance instance, PP_Resource url_loader)
{
	return PP_FALSE;
}

static void Messaging_HandleMessage(PP_Instance instance, struct PP_Var message)
{

	if(PP_VARTYPE_STRING != message.type) {
		PostMessage("Not a PP_VARTYPE_STRING PP_Var\n");
		return;
	}

	const char *str;
	uint32_t strLength;

	if (NULL != ppb_var_interface) {
		str = ppb_var_interface->VarToUtf8(message, &strLength);
		if(NULL == str) {
			PostMessage("NULL == str");
			return;
		}
		if(0 == strLength) {
			PostMessage("0 == strLength");
			return;
		}
	} else {
		PostMessage("ppb_var_interface == NULL");
		return;
	}

	PostMessage(str);
  
	switch (str[0]) {
		case MSG_IOTC:
		{
			// deviceUID is passed as an argument like "i;deviceUID".
			char message[255];
			char *deviceUID;
			deviceUID = strchr(str, ';')+1;

			sprintf(message, "deviceUID %s", deviceUID);
			PostMessage(message);

			pthread_create(&g_IOTCClientThread, NULL, IOTCClientThreadFunc, (void*)deviceUID);
			break;
		}
		case MSG_RDT:
		{
			// deviceUID is passed as an argument like "r;deviceUID".
			char message[255];
			char *deviceUID;
			deviceUID = strchr(str, ';')+1;

			sprintf(message, "deviceUID %s", deviceUID);
			PostMessage(message);
		
			pthread_create(&g_RDTClientThread, NULL, RDTClientThreadFunc, (void*)deviceUID);
			break;
		}
    
		default:
			PostMessage("Unhandled message from JavaScript");
			break;
	}
}

PP_EXPORT int32_t PPP_InitializeModule(PP_Module a_module_id, PPB_GetInterface get_browser)
{
	g_Browser = get_browser;
	ppb_messaging_interface   = (PPB_Messaging*)(get_browser(PPB_MESSAGING_INTERFACE));
	ppb_var_interface         = (PPB_Var*)(get_browser(PPB_VAR_INTERFACE));
	ppb_core_interface        = (PPB_Core*)(get_browser(PPB_CORE_INTERFACE));

	return PP_OK;
}

PP_EXPORT const void* PPP_GetInterface(const char* interface_name)
{
	if (strcmp(interface_name, PPP_INSTANCE_INTERFACE) == 0) {
		static PPP_Instance instance_interface = {
			&Instance_DidCreate,
			&Instance_DidDestroy,
			&Instance_DidChangeView,
			&Instance_DidChangeFocus,
			&Instance_HandleDocumentLoad,
		};
		return &instance_interface;
	}

	if (strcmp(interface_name, PPP_MESSAGING_INTERFACE) == 0) {
		static PPP_Messaging messaging_interface = {
			&Messaging_HandleMessage,
		};
		return &messaging_interface;
	}
	return NULL;
}

PP_EXPORT void PPP_ShutdownModule() {}
