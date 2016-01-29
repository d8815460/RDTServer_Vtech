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

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace tunnel_sample
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        tutk.iotc.Tunnel T1;
        int nSID, gRetryConnectFailedCnt, nStart;
        uint gMapIndex;
        string UID = "XXXXXXXXXXXXXXXXXX"; //put UID here

        public MainPage()
        {
            this.InitializeComponent();

            this.NavigationCacheMode = NavigationCacheMode.Required;

            T1 = new tutk.iotc.Tunnel();
            updateUI("\n\n");
            gRetryConnectFailedCnt = 0;
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

        private void updateUI(string s)
        {
            textblock1.Text += s;
            textblock1.Text += "\n";
        }

        private void Button_Click2(object sender, RoutedEventArgs e)
        {
            IAsyncAction StopAction = Windows.System.Threading.ThreadPool.RunAsync((StopThread) =>
            {
                T1.P2PTunnelAgent_StopPortMapping(gMapIndex);
                T1.P2PTunnelAgent_Disconnect(nSID);
                T1.P2PTunnelAgentDeInitialize();

                CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(
                Windows.UI.Core.CoreDispatcherPriority.High,
                new Windows.UI.Core.DispatchedHandler(() =>
                {
                    updateUI("Tunnel Agent DeInitialize");
                }));
            });
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            IAsyncAction TunnelAction = Windows.System.Threading.ThreadPool.RunAsync((TunnelThread) =>
            {
                T1.P2PTunnelAgentInitialize(4);
                string username = "Tutk.com", password = "P2P Platform";
                if (username.Length < 64)
                {
                    for (int i = 0; username.Length < 64; i++)
                        username += "\0";
                }
                if (password.Length < 64)
                {
                    for (int i = 0; password.Length < 64; i++)
                        password += "\0";
                }
                byte[] bAuthData = System.Text.Encoding.UTF8.GetBytes(username + password);
                tutk.iotc.TunnelConnectInfo stConnectInfo = new tutk.iotc.TunnelConnectInfo();
                stConnectInfo.nErrFromDeviceCB = 1;

                nStart = T1.P2PTunnelAgent_Connect(UID, bAuthData, bAuthData.Length, stConnectInfo);
                int ret = T1.P2PTunnel_SetBufSize(nStart, 5120000);
                gMapIndex = (uint)T1.P2PTunnelAgent_PortMapping(nStart, 8080, 80);
                CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(
                Windows.UI.Core.CoreDispatcherPriority.High,
                new Windows.UI.Core.DispatchedHandler(() =>
                {
                    updateUI("visit http://127.0.0.1:8080");
                }));
            });


        }

        private void Button_Click3(object sender, RoutedEventArgs e)
        {

        }

        private void Button_Click4(object sender, RoutedEventArgs e)
        {

        }
    }
}
