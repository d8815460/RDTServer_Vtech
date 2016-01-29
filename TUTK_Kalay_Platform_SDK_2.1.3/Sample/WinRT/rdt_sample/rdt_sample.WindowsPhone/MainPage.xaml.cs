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

namespace rdt_sample
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        const int MAX_BUF_SIZE = 1024;
        const int RDT_WAIT_TIMEMS = 20000;
        const int RDT_ER_TIMEOUT = -10007;
        tutk.iotc.IOTC iotc;

        tutk.iotc.RDT rdt;
        int SID, nRDTIndex;
        byte[] buf2;

        public MainPage()
        {
            this.InitializeComponent();

            this.NavigationCacheMode = NavigationCacheMode.Required;

            iotc = new tutk.iotc.IOTC();
            rdt = new tutk.iotc.RDT();
            buf2 = new byte[MAX_BUF_SIZE];
            UpdateUI("");
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
            textblock1.Text += "\n";
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            int ret;
            iotc.IOTC_Initialize2(0);
            ret = rdt.RDT_Initialize();
            if (ret < 0)
                UpdateUI("RDT Initialize FAIL [" + ret + "]");

            else
                UpdateUI("Initialize OK");
        }

        private void Button_Click2(object sender, RoutedEventArgs e)
        {
            int ret;
            IAsyncAction ConnectAction = Windows.System.Threading.ThreadPool.RunAsync((ConnectThread) =>
            {

                SID = iotc.IOTC_Get_SessionID();
		ret = iotc.IOTC_Connect_ByUID_Parallel("XXXXXXXXXXXXXXXXXXXXX", SID); //put UID here

                CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(
                    Windows.UI.Core.CoreDispatcherPriority.High,
                    new Windows.UI.Core.DispatchedHandler(() =>
                    {
                        UpdateUI("IOTC_Get_SessionID = " + SID + ", Connect [" + ret + "]");
                    }));




                nRDTIndex = rdt.RDT_Create(SID, RDT_WAIT_TIMEMS, 0);
                CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(
                    Windows.UI.Core.CoreDispatcherPriority.High,
                    new Windows.UI.Core.DispatchedHandler(() =>
                    {
                        UpdateUI("RDT Create [" + nRDTIndex + "]");
                    }));
                if (nRDTIndex < 0)
                {
                    iotc.IOTC_Session_Close(SID);
                    iotc.IOTC_DeInitialize();
                    rdt.RDT_DeInitialize();
                }
            });



        }

        private void Button_Click3(object sender, RoutedEventArgs e)
        {


            IAsyncAction RecvAction = Windows.System.Threading.ThreadPool.RunAsync((RecvThread) =>
            {
                int ret, filesize, remainReadSize;
                byte[] buf = new byte[MAX_BUF_SIZE];

                buf = System.Text.Encoding.UTF8.GetBytes("1");
                ret = rdt.RDT_Write(nRDTIndex, buf, 1);
                if (ret < 0)
                {
                    CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(
                    Windows.UI.Core.CoreDispatcherPriority.High,
                    new Windows.UI.Core.DispatchedHandler(() =>
                    {
                        UpdateUI("RDT send cmd FAIL [" + ret + "]");
                    }));

                    iotc.IOTC_Session_Close(SID);
                    return;
                }
                buf = new byte[1024];
                ret = rdt.RDT_Read(nRDTIndex, buf, MAX_BUF_SIZE, RDT_WAIT_TIMEMS);
                string strFileSize = System.Text.Encoding.UTF8.GetString(buf, 0, ret);
                filesize = int.Parse(strFileSize);

                if (ret < 0)
                {
                    CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(
                    Windows.UI.Core.CoreDispatcherPriority.High,
                    new Windows.UI.Core.DispatchedHandler(() =>
                    {
                        UpdateUI("RDT receive file size FAIL [" + ret + "]");
                    }));

                    iotc.IOTC_Session_Close(SID);
                    return;
                }


                //new System.Threading.ManualResetEvent(false).WaitOne(500);                

                buf = System.Text.Encoding.UTF8.GetBytes("Start");
                ret = rdt.RDT_Write(nRDTIndex, buf, buf.Length);
                if (ret < 0)
                {
                    CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(
                    Windows.UI.Core.CoreDispatcherPriority.High,
                    new Windows.UI.Core.DispatchedHandler(() =>
                    {
                        UpdateUI("RDT send start FAIL [" + ret + "]");
                    }));

                    iotc.IOTC_Session_Close(SID);
                    return;
                }

                remainReadSize = filesize;
                buf = new byte[MAX_BUF_SIZE];
                while (true)
                {

                    if (remainReadSize < MAX_BUF_SIZE)
                        ret = rdt.RDT_Read(nRDTIndex, buf, remainReadSize, RDT_WAIT_TIMEMS);
                    else
                        ret = rdt.RDT_Read(nRDTIndex, buf, MAX_BUF_SIZE, RDT_WAIT_TIMEMS);

                    if (ret < 0 && ret != RDT_ER_TIMEOUT)
                    {
                        CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(
                        Windows.UI.Core.CoreDispatcherPriority.High,
                        new Windows.UI.Core.DispatchedHandler(() =>
                        {
                            UpdateUI("READ ERROR [" + ret + "]");
                        }));

                        break;
                    }

                    if (ret > 0)
                    {
                        remainReadSize -= ret;
                    }

                    if (remainReadSize == 0)
                        break;
                } //while
                CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(
                    Windows.UI.Core.CoreDispatcherPriority.High,
                    new Windows.UI.Core.DispatchedHandler(() =>
                    {
                        UpdateUI("receive file finished. filesize[" + filesize + "]");
                    }));

            });


        }




        private void Button_Click4(object sender, RoutedEventArgs e)
        {
            IAsyncAction DestroyAction = Windows.System.Threading.ThreadPool.RunAsync((DestroyThread) =>
            {
                rdt.RDT_Destroy(nRDTIndex);
                iotc.IOTC_Session_Close(SID);
                rdt.RDT_DeInitialize();
                iotc.IOTC_DeInitialize();
            });
            UpdateUI("DeInitialize");
        }
    }
}
