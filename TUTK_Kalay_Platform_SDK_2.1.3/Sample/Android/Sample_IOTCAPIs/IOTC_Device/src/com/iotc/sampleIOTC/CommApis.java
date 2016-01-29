/******************************************************************************
 *                                                                            *
 * Copyright (c) 2013 by TUTK Co.LTD. All Rights Reserved.                    *
 *                                                                            *
 * Author: Chun Chen                                                          *
 * Date: 2013-01-24                                                           *

 ******************************************************************************/

package com.iotc.sampleIOTC;

import java.io.UnsupportedEncodingException;

import android.R.string;
import android.os.Message;

import com.iotc.sampleIOTC.Sample_IOTCAPIs.MainHandler;
import com.tutk.IOTC.IOTCAPIs;
import com.tutk.IOTC.St_SInfo;

public class CommApis extends IOTCAPIs 
{
	public static final int	COMMAPIS_STOPPED		=-1001;
	private static final int CMD_REQUEST_DATA_CH = 1;
	private static final int CMD_DATA_CHANNEL_ON = 2;
	private static final int Default_Channel = 0;
	private static final int	MAXSIZE_RECVBUF	=1400;
	protected Sample_IOTCAPIs actMainView			=null;
	public static int 		  ms_nIOTCInit 			=IOTCAPIs.IOTC_ER_TIMEOUT;
	protected ThreadLogin	  m_threadLogin=null;
	protected ThreadListen 	  m_threadListen=null;

	protected String		  m_strUID;
	protected boolean		  m_bAsDevice=true;
	protected St_SInfo		  m_stSInfo=new St_SInfo();
	boolean m_bStoped=true;
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
			return ms_nIOTCInit;
		}

		return 0;
	}
	public void unInitIOTC()
	{
		if(ms_nIOTCInit==IOTCAPIs.IOTC_ER_NoERROR){
			IOTC_DeInitialize();
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
	
	public int startSess(String strUID,boolean isControl){
		m_strUID=strUID;
		m_bStoped=false;
		
		if(m_threadLogin==null)
		{
			m_threadLogin=new ThreadLogin();
			m_threadLogin.start();
			
			try {Thread.sleep(100);}
			catch(InterruptedException e) { e.printStackTrace(); }
		}
		
		if(m_threadListen==null)
		{
			m_threadListen=new ThreadListen();
			m_threadListen.start();
			
			try {Thread.sleep(100);}
			catch(InterruptedException e) { e.printStackTrace(); }
		}
		return 0;
		
	}
	
	public void stopSess()
	{
		m_bStoped=true;		
		int nCount=0;	
		
		if(m_bAsDevice){//as device
			nCount=0;
			if(m_threadLogin!=null){
				do{
					if(m_threadLogin.mbStopedSure) break;
					try {Thread.sleep(40);}
					catch(InterruptedException e) { e.printStackTrace(); }
					nCount++;
				}while(nCount<50);
				if(nCount>=50) m_threadLogin.interrupt();
				m_threadLogin=null;
			}

			nCount=0;
			if(m_threadListen!=null){
				do{
					if(m_threadListen.mbStopedSure) break;
					try {Thread.sleep(40);}
					catch(InterruptedException e) { e.printStackTrace(); }
					nCount++;
				}while(nCount<50);
				if(nCount>=50) m_threadListen.interrupt();
				m_threadListen=null;
			}
		}
	}
	
	
	
	class ThreadLogin extends Thread
	{
		int nRet=-1;
		boolean mbStopedSure=false;
		
		public ThreadLogin(){
			mbStopedSure=false;
		}
		
		public void run() {
			System.out.println("ThreadLogin going...");
			int i=0;
			do{
				nRet=IOTC_Device_Login(m_strUID,null,null);
				System.out.println("IOTC_Device_Login(...)="+nRet);
				
				if(nRet==IOTCAPIs.IOTC_ER_NoERROR) 
				{
					String str="IOTC_Device_Login(.), success";
					setLog(MainHandler.MSGTYPE_LOG, str);
					break;
				}
				
				//2s=10*200ms
				for(i=0;i<10;i++)
				{
					try {Thread.sleep(200);}
					catch(InterruptedException e) { e.printStackTrace(); }					
					if(m_bStoped) break;
				}
			}while(!m_bStoped);
			
			System.out.println("===ThreadLogin exit.");
			mbStopedSure=true;
		}
	}
	
	class ThreadListen extends Thread
	{

		boolean mbStopedSure=false;
		int nSID = -1;

		public ThreadListen(){
			mbStopedSure=false;
		}
		
		public void run() 
		{

			do{
				
				setLog(MainHandler.MSGTYPE_LOG, "ThreadListen going...");

				nSID=IOTC_Listen(0);

				if(m_bStoped) break;
				
				if(clientConnectDev(nSID)<0) continue;

				synchronized(this){
					
					int nCheck = IOTC_Session_Check(nSID, m_stSInfo);
										
					if(nCheck >= 0)
					{
						new ThreadSession(nSID).start();
						
						try {Thread.sleep(5000);}
						catch(InterruptedException e) { e.printStackTrace(); }

					}
				}
				
			}while(!m_bStoped);
			
			mbStopedSure=true;
		}
		
		private int clientConnectDev(int SID)
		{
			nSID = SID;
			String str = "";	
			if(nSID<0){
				switch(nSID)
				{
					case IOTC_ER_NOT_INITIALIZED:
						str=String.format("Don't call IOTC_Initialize() when connecting.(%d)", m_nSearchDev);					
						break;

					case IOTC_ER_CONNECT_IS_CALLING:
						str=String.format("IOTC_Connect_ByXX() is calling when connecting.(%d)", nSID);
						break;

					case IOTC_ER_FAIL_RESOLVE_HOSTNAME:
						str=String.format("Can't resolved server's Domain name when connecting.(%d)", nSID);
						break;

					case IOTC_ER_SERVER_NOT_RESPONSE:
						str=String.format("Server not response when connecting.(%d)", nSID);
						break;

					case IOTC_ER_FAIL_GET_LOCAL_IP:
						str=String.format("Can't Get local IP when connecting.(%d)", nSID);
						break;

					case IOTC_ER_UNKNOWN_DEVICE:
						str=String.format("Wrong UID when connecting.(%d)", nSID);
						break;

					case IOTC_ER_UNLICENSE:
						str=String.format("UID is not registered when connecting.(%d)", nSID);
						break;

					case IOTC_ER_CAN_NOT_FIND_DEVICE:
						str=String.format("Device is NOT online when connecting.(%d)", nSID);
						break;

					case IOTC_ER_EXCEED_MAX_SESSION:
						str=String.format("Exceed the max session number when connecting.(%d)", nSID);
						break;

					case IOTC_ER_TIMEOUT:
						str=String.format("Timeout when connecting.(%d)", nSID);
						break;

					case IOTC_ER_DEVICE_NOT_LISTENING:
						str=String.format("The device is not on listening when connecting.(%d)", nSID);
						break;

					default:
						str=String.format("Failed to connect device when connecting.(%d)", nSID);
				}
				setLog(MainHandler.MSGTYPE_LOG, str);
				
				try {Thread.sleep(200);}
				catch(InterruptedException e) { e.printStackTrace(); }	
				
			}else{
				IOTC_Session_Check(nSID, m_stSInfo);
				str="  "+((m_stSInfo.Mode==0) ? "P2P" : "Relay")+", NAT=type"+IOTC_Get_Nat_Type();
				setLog(MainHandler.MSGTYPE_LOG, str);
			}
			
			if(m_bStoped) return COMMAPIS_STOPPED;
			else return nSID;
		}
	}
	
	class ThreadSession extends Thread
	{
		private int nSID;
		

		
		private byte[] mRecvBuf = new byte[MAXSIZE_RECVBUF];

		
		public ThreadSession(int SID)
		{
			this.nSID = SID;
			
		}
		
		public void run() 
		{
			int nCount = 0;

			setLog(MainHandler.MSGTYPE_LOG, "ThreadSession Start");
			byte[] bufWrite = new byte[MAXSIZE_RECVBUF];
			String strReadBuf = null;
			int nRead=-1;
			int nWrite = -1;
			
			do{
				nCount++;
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
				nRead=IOTC_Session_Read(nSID, mRecvBuf, MAXSIZE_RECVBUF, 500, Default_Channel);
				
				try {
					strReadBuf = new String(mRecvBuf, "UTF-8");
				} catch (UnsupportedEncodingException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				setLog(MainHandler.MSGTYPE_LOG, "IOTC_Session_Read = " + nRead +", Content = " + strReadBuf);
				
				bufWrite = "HI".getBytes();
				
				nWrite = IOTC_Session_Write(nSID, bufWrite, bufWrite.length, 0);
				setLog(MainHandler.MSGTYPE_LOG, "IOTC_Session_Write = " + nWrite);
				
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}while(!m_bStoped);
		}
	}
}
