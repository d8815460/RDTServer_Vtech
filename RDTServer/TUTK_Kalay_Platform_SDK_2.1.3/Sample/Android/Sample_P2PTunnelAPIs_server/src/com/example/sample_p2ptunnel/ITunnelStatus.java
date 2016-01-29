package com.example.sample_p2ptunnel;
import com.tutk.IOTC.sP2PTunnelSessionInfo;
public interface ITunnelStatus {
	public void onTunnelStatus(int nErrCode, int nSID);
    public void onTunnelSessionInfo(sP2PTunnelSessionInfo sSessionInfo);
}
