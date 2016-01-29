/******************************************************************************
 *                                                                            *
 * Copyright (c) 2013 by TUTK Co.LTD. All Rights Reserved.                    *
 *                                                                            *
 * Author: Chun Chen                                                          *
 * Date: 2013-02-7                                                           *

 ******************************************************************************/

package com.iotc.sampleIOTC;

import java.io.UnsupportedEncodingException;

import android.os.Message;

import com.iotc.sampleIOTC.Sample_IOTCAPIs.MainHandler;
import com.tutk.IOTC.IOTCAPIs;
import com.tutk.IOTC.St_SInfo;
import com.tutk.IOTC.st_LanSearchInfo;
import com.tutk.IOTC.st_SearchDeviceInfo;
public class CommApis extends IOTCAPIs 
{
	public static final int	COMMAPIS_STOPPED		=-1001;
	private static final int CMD_REQUEST_DATA_CH = 1;
	private static final int CMD_DATA_CHANNEL_ON = 2;
	
	protected Sample_IOTCAPIs actMainView			=null;
	public static int 		  ms_nIOTCInit 			=IOTCAPIs.IOTC_ER_TIMEOUT;
	private int nFristGet = 0;
	private int nSID = -1;
	protected String		  m_strUID;
	protected boolean		  m_bAsDevice=true;
	protected St_SInfo		  m_stSInfo=new St_SInfo();
	
	boolean m_bStoped=true;
	boolean m_bStopedSearch = true;
	boolean mbStopedSure = true;
	boolean mb_bStopedGetDate = true;
	
	public static final int	STATUS_INIT_SEARCH_DEV	=10;
	int 	m_nSearchDev=STATUS_INIT_SEARCH_DEV;
	
	public CommApis(Sample_IOTCAPIs mainView)
	{
		actMainView = mainView;
	}
	
	public int initIOTC()
	{
		if(ms_nIOTCInit!=IOTCAPIs.IOTC_ER_NoERROR)
		{
			ms_nIOTCInit=IOTC_Initialize2(0);
			actMainView.setLog("IOTC_Initialize(.)="+ms_nIOTCInit);
			mLanSearch();	
			
			return ms_nIOTCInit;
		}

		return 0;
	}
	public void unInitIOTC()
	{
		if(ms_nIOTCInit==IOTCAPIs.IOTC_ER_NoERROR){
			IOTC_DeInitialize();
			nFristGet = 0;
			ms_nIOTCInit=IOTCAPIs.IOTC_ER_TIMEOUT;
			setLog(MainHandler.MSGTYPE_LOG, "IOTC_DeInitialize()");
		}
	}
	
	protected void setLog(int msgType, String strLog)
	{
		Message msg=new Message();
		msg.what=msgType;
		msg.obj =strLog;
		actMainView.mainHandler.sendMessageDelayed(msg, 0);
	}
	
	private void mLanSearch() 
	{
		int[] nArray = new int[1];
		
		IOTC_Search_Device_Start(3000,100);
		
		while(true)
		{
		
			st_SearchDeviceInfo[] ab_LanSearchInfo = IOTC_Search_Device_Result(nArray,0);
			
			if(nArray[0] < 0)
			{
				break;
			}
			
			setLog(MainHandler.MSGTYPE_LOG, "st_SearchDeviceInfo  === " + nArray[0]);
			
			for(int i = 0; i < nArray[0];i++){
				
				try 
				{
					setLog(MainHandler.MSGTYPE_LOG, "UID = " + i +  " = " + new String(ab_LanSearchInfo[i].UID,0, ab_LanSearchInfo[i].UID.length,"utf-8"));
					setLog(MainHandler.MSGTYPE_LOG, "IP " + i +  " = " + new String(ab_LanSearchInfo[i].IP,0, ab_LanSearchInfo[i].IP.length,"utf-8"));
				} catch (UnsupportedEncodingException e) {

					e.printStackTrace();
				}
				setLog(MainHandler.MSGTYPE_LOG, "Port " + i +  " = " + String.valueOf(ab_LanSearchInfo[i].port));
				setLog(MainHandler.MSGTYPE_LOG, "****************************");			
			}
			
			try {
					Thread.sleep(1000);
			} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
			}
		}
	}

	public void stopSess()
	{
		mbStopedSure=true;
		m_bStoped=true;		
		m_bStopedSearch=true;

		IOTC_Connect_Stop();

	}
	class ThreadSession extends Thread
	{
		public ThreadSession()
		{
			
		}
		public void run()
		{
			int nRead=-1;
			int nWrite = -1;

			int nCount = 0;
			
			final	int	MAXSIZE_RECVBUF	=1400;
			byte[] sendBuf = new byte[MAXSIZE_RECVBUF];
			byte[] readBuf = new byte[MAXSIZE_RECVBUF];
			
			do{
				if(nCount % 60 == 1)
				{
					IOTC_Session_Check(nSID, m_stSInfo);
					switch(m_stSInfo.Mode)
					{
					case 0:
						setLog(MainHandler.MSGTYPE_LOG, "SESSION CHECK, MODE = P2P");
						break;
					case 1:
						setLog(MainHandler.MSGTYPE_LOG, "SESSION CHECK, MODE = Relay");
						break;
					case 2:
						setLog(MainHandler.MSGTYPE_LOG, "SESSION CHECK, MODE = Lan");
						break;
					}
				}
				sendBuf = ("HELLO" + nCount).getBytes();
				nWrite = IOTC_Session_Write(nSID, sendBuf, sendBuf.length, 0);
				setLog(MainHandler.MSGTYPE_LOG, "IOTC_Session_Write[" + nCount +"] = " + nWrite);
				
				nRead = IOTC_Session_Read(nSID, readBuf, MAXSIZE_RECVBUF, 500, 0);
				setLog(MainHandler.MSGTYPE_LOG, "got HI " + nCount + ", nRead = " + nRead);
				
				nCount++;
				
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}while(!m_bStopedSearch);
		}
	}
	public void start(String strUID, boolean isControl)
	{
		m_strUID=strUID;
		
		m_bStoped=false;
		mbStopedSure=false;
		m_bStopedSearch= false;
		
		
			
		nSID = clientConnectDev();

		setLog(MainHandler.MSGTYPE_LOG, "doClient got nSID = " + nSID);
		
		if(nSID<0) return;
		
		new ThreadSession().start();
		nFristGet++;
	}
	
	public int clientConnectDev()
	{
			//connect this device
//			int nSID = -1;
			int ret = -1;
			setLog(MainHandler.MSGTYPE_LOG, "Connecting...");
			if(nFristGet == 0)
			{
				String err;
				nSID = IOTC_Get_SessionID();
				if(nSID < 0)
				{
					err = ("IOTC_Get_SessionID(.)="+nSID);
					setLog(MainHandler.MSGTYPE_LOG, err);
				}
				ret = IOTC_Connect_ByUID_Parallel(m_strUID, nSID);
			}
			String str = ("IOTC_Connect_ByUID_Parallel(.)="+ret);
			setLog(MainHandler.MSGTYPE_LOG, str);			
			if(ret<0)
			{
				switch(ret)
				{
					case IOTC_ER_NOT_INITIALIZED:
						str=String.format("Don't call IOTC_Initialize() when connecting.(%d)", m_nSearchDev);					
						break;

					case IOTC_ER_CONNECT_IS_CALLING:
						str=String.format("IOTC_Connect_ByXX() is calling when connecting.(%d)", ret);
						break;

					case IOTC_ER_FAIL_RESOLVE_HOSTNAME:
						str=String.format("Can't resolved server's Domain name when connecting.(%d)", ret);
						break;

					case IOTC_ER_SERVER_NOT_RESPONSE:
						str=String.format("Server not response when connecting.(%d)", ret);
						break;

					case IOTC_ER_FAIL_GET_LOCAL_IP:
						str=String.format("Can't Get local IP when connecting.(%d)", ret);
						break;

					case IOTC_ER_UNKNOWN_DEVICE:
						str=String.format("Wrong UID when connecting.(%d)", ret);
						break;

					case IOTC_ER_UNLICENSE:
						str=String.format("UID is not registered when connecting.(%d)", ret);
						break;

					case IOTC_ER_CAN_NOT_FIND_DEVICE:
						str=String.format("Device is NOT online when connecting.(%d)", ret);
						break;

					case IOTC_ER_EXCEED_MAX_SESSION:
						str=String.format("Exceed the max session number when connecting.(%d)", ret);
						break;

					case IOTC_ER_TIMEOUT:
						str=String.format("Timeout when connecting.(%d)", ret);
						break;

					case IOTC_ER_DEVICE_NOT_LISTENING:
						str=String.format("The device is not on listening when connecting.(%d)", ret);
						break;

					default:
						str=String.format("Failed to connect device when connecting.(%d)", ret);
				}
				setLog(MainHandler.MSGTYPE_LOG, str);
			}
			else
			{
				IOTC_Session_Check(nSID, m_stSInfo);
				str="  "+((m_stSInfo.Mode==0) ? "P2P" : "Relay")+", NAT=type"+IOTC_Get_Nat_Type();
				setLog(MainHandler.MSGTYPE_LOG, str);
			}
			
			if(m_bStoped) return COMMAPIS_STOPPED;
			else return nSID;
	}
}
