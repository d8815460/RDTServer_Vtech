using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

using Windows.ApplicationModel.Core;

public struct st_info
{
    public int num_a;
    public int num_b;
}

public struct st_SInfo
{
    public System.Byte Mode; //!< 0: P2P mode, 1: Relay mode, 2: LAN mode
    public char CorD; //!< 0: As a Client, 1: As a Device
    public string UID; //!< The UID of the device
    public string RemoteIP; //!< The IP address of remote site used during this IOTC session
    public System.Int16 RemotePort; //!< The port number of remote site used during this IOTC session
    public System.UInt32 TX_Packetcount; //!< The total packets sent from the device and the client during this IOTC session
    public System.UInt32 RX_Packetcount; //!< The total packets received in the device and the client during this IOTC session
    public System.UInt32 IOTCVersion; //!< The IOTC version
    public System.UInt16 VID; //!< The Vendor ID, part of VPG mechanism
    public System.UInt16 PID; //!< The Product ID, part of VPG mechanism
    public System.UInt16 GID; //!< The Group ID, part of VPG mechanism
    public System.Byte NatType; //!< The remote NAT type
    public System.Byte isSecure; //!< 0: The IOTC session is in non-secure mode, 1: The IOTC session is in secure mode
};
// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace iotc_sample
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>



    public sealed partial class MainPage : Page
    {
        tutk.iotc.IOTC IOTC1;
        int SID;
        public MainPage()
        {
            this.InitializeComponent();

            this.NavigationCacheMode = NavigationCacheMode.Required;

            IOTC1 = new tutk.iotc.IOTC();
        }

        /// <summary>
        /// Invoked when this page is about to be displayed in a Frame.
        /// </summary>
        /// <param name="e">Event data that describes how this page was reached.
        /// This parameter is typically used to configure the page.</param>
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            // TODO: Prepare page for display here.

            // TODO: If your application contains multiple pages, ensure that you are
            // handling the hardware Back button by registering for the
            // Windows.Phone.UI.Input.HardwareButtons.BackPressed event.
            // If you are using the NavigationHelper provided by some templates,
            // this event is handled for you.
        }
        private void UpdateUI(String s)
        {
            textblock1.Text += s;
        }
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            
            int ret;
            ret = IOTC1.IOTC_Initialize2(0);
            textblock1.Text += "\nInitialize = " + ret + "\n";

            IAsyncAction ConnectAction = Windows.System.Threading.ThreadPool.RunAsync((ConnectThread) =>
            {
                SID = IOTC1.IOTC_Get_SessionID();
                CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(
                Windows.UI.Core.CoreDispatcherPriority.High,
                new Windows.UI.Core.DispatchedHandler(() =>
                {
                    UpdateUI("IOTC_Get_SessionID = [" + SID + "]\n");
                }));
		ret = IOTC1.IOTC_Connect_ByUID_Parallel("XXXXXXXXXXXXXXXXXXXX", SID);
                CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(
                Windows.UI.Core.CoreDispatcherPriority.High,
                new Windows.UI.Core.DispatchedHandler(() =>
                {
                    UpdateUI("Connect = [" + ret + "]\n");
                }));
            });

        }
        private void Button_Click2(object sender, RoutedEventArgs e)
        {
            IAsyncAction asynAction2 = Windows.System.Threading.ThreadPool.RunAsync((RWThread) =>
            {
                byte[] buf = new byte[20];
                byte[] readbuf = new byte[20];
                tutk.iotc.SInfo info = new tutk.iotc.SInfo();
                int i, ret;

                CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(
                    Windows.UI.Core.CoreDispatcherPriority.High,
                    new Windows.UI.Core.DispatchedHandler(() =>
                    {
                        UpdateUI("Read/Write Thread Start\n");
                    }));

                //IOTC1.IOTC_Session_Check(SID, info);
                /*if (info.Mode == 0)
                    text1block1 += "\najk";*/
                //new System.Threading.ManualResetEvent(false).WaitOne(500);
                for (i = 0; i < 3; i++)
                {
                    //Sleep
                    //new System.Threading.ManualResetEvent(false).WaitOne(500);

                    ret = IOTC1.IOTC_Session_Read(SID, readbuf, 50, 2000, 0);
                    CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(
                        Windows.UI.Core.CoreDispatcherPriority.High,
                        new Windows.UI.Core.DispatchedHandler(() =>
                        {
                            UpdateUI("Session Read = " + ret + "\n");
                        }));
                }

                for (i = 0; i < 3; i++)
                {
                    buf = System.Text.Encoding.UTF8.GetBytes(string.Format("IOTC Hello World: {0}", i));
                    ret = IOTC1.IOTC_Session_Write(SID, buf, 50 * sizeof(byte), 0);
                    CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(
                        Windows.UI.Core.CoreDispatcherPriority.High,
                        new Windows.UI.Core.DispatchedHandler(() =>
                        {
                            UpdateUI("Session Write = " + ret + "\n");
                        }));
                }






            });

        }
        private void Button_Click3(object sender, RoutedEventArgs e)
        {
            IOTC1.IOTC_Session_Close(SID);
            IOTC1.IOTC_DeInitialize();
        }
        private void Button_Click4(object sender, RoutedEventArgs e)
        {
            UpdateUI("XXX\n");
        }
    }
}
