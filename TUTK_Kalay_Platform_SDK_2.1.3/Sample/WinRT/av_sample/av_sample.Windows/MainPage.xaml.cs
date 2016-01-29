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

namespace av_sample
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        tutk.iotc.IOTC IOTC1;
        tutk.iotc.AVAPI AV1;
        int SID, avIndex;
        bool running;
        public MainPage()
        {
            this.InitializeComponent();

            this.NavigationCacheMode = NavigationCacheMode.Required;
            UpdateUI("");
            IOTC1 = new tutk.iotc.IOTC();
            AV1 = new tutk.iotc.AVAPI();
            running = true;
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

        private bool startIpcamStream()
        {
            int ret;

            ret = AV1.avSendIOCtrl(avIndex, 0xFF, new byte[2], 2);
            if (ret < 0)
                return false;

            ret = AV1.avSendIOCtrl(avIndex, 0x1FF, new byte[8], 8);
            if (ret < 0)
                return false;

            ret = AV1.avSendIOCtrl(avIndex, 0x300, new byte[8], 8);
            if (ret < 0)
                return false;

            return true;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            int ret;

            ret = IOTC1.IOTC_Initialize2(0);
            UpdateUI("Initialize = " + ret);
            ret = AV1.avInitialize(3);
            UpdateUI("avInitialize = " + ret);


        }

        private void Button_Click2(object sender, RoutedEventArgs e)
        {
            int ret;
            byte[] acc = new byte[20];
            byte[] pwd = new byte[20];

            acc = System.Text.Encoding.UTF8.GetBytes("admin");
            pwd = System.Text.Encoding.UTF8.GetBytes("888888");

            tutk.iotc.ClientStartInfo clientInfo = new tutk.iotc.ClientStartInfo();

            IAsyncAction ConnectAction = Windows.System.Threading.ThreadPool.RunAsync((ConnectThread) =>
            {
		SID = IOTC1.IOTC_Get_SessionID();
                CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(
                    Windows.UI.Core.CoreDispatcherPriority.High,
                    new Windows.UI.Core.DispatchedHandler(() =>
                    {
                        UpdateUI("IOTC_Get_SessionID = " + ret);
                    }));

                ret = IOTC1.IOTC_Connect_ByUID_Parallel("XXXXXXXXXXXXXXXXXXXX", SID); //put UID here
                CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(
                    Windows.UI.Core.CoreDispatcherPriority.High,
                    new Windows.UI.Core.DispatchedHandler(() =>
                    {
                        UpdateUI("IOTC Connect = " + ret);
                    }));

                avIndex = AV1.avClientStart(SID, acc, pwd, 10, clientInfo, 0);
                CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(
                    Windows.UI.Core.CoreDispatcherPriority.High,
                    new Windows.UI.Core.DispatchedHandler(() =>
                    {
                        UpdateUI("avClientStart = " + avIndex);
                    }));
            });
        }

        private void Button_Click3(object sender, RoutedEventArgs e)
        {
            byte[] recvBuf = new byte[1024];
            byte[] frameinfo = new byte[100];
            int last_time_tick;
            last_time_tick = System.Environment.TickCount;
            tutk.iotc.AVRecvFrmNo frameNO = new tutk.iotc.AVRecvFrmNo();
            IAsyncAction Thread1 = Windows.System.Threading.ThreadPool.RunAsync((THREAD1) =>
            {

                int fps_cnt = 0;
                CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(
                    Windows.UI.Core.CoreDispatcherPriority.High,
                    new Windows.UI.Core.DispatchedHandler(() =>
                    {
                        UpdateUI("Received Thread Start");
                    }));

                if (startIpcamStream())
                {
                    IAsyncAction videoThread = Windows.System.Threading.ThreadPool.RunAsync((VIDEOTHREAD) =>
                    {
                        const int VIDEO_BUF_SIZE = 100000;
                        const int FRAME_INFO_SIZE = 16;
                        int ret;
                        byte[] frameInfo = new byte[FRAME_INFO_SIZE];
                        byte[] videoBuffer = new byte[VIDEO_BUF_SIZE];
                        tutk.iotc.AVRecvFrmNo frameNumber = new tutk.iotc.AVRecvFrmNo();

                        CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(
                        Windows.UI.Core.CoreDispatcherPriority.High,
                        new Windows.UI.Core.DispatchedHandler(() =>
                        {
                            UpdateUI("VideoThread Start");
                        }));

                        while (running)
                        {

                            ret = AV1.avRecvFrameData(avIndex, videoBuffer, VIDEO_BUF_SIZE, frameInfo, FRAME_INFO_SIZE, frameNumber);
                            if (ret == -20015 || ret == -20016 || ret == -20010)
                            {
                                break;
                            }
                            else if (ret < 0)
                            {
                                new System.Threading.ManualResetEvent(false).WaitOne(50);
                                continue;
                            }

                        }
                    });

                    IAsyncAction audioThread = Windows.System.Threading.ThreadPool.RunAsync((AUDIOTHREAD) =>
                    {
                        const int AUDIO_BUF_SIZE = 1024;
                        const int FRAME_INFO_SIZE = 16;
                        byte[] frameInfo = new byte[FRAME_INFO_SIZE];
                        byte[] audioBuffer = new byte[AUDIO_BUF_SIZE];
                        int ret;
                        tutk.iotc.AVRecvFrmNo frameNumber = new tutk.iotc.AVRecvFrmNo();

                        CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(
                        Windows.UI.Core.CoreDispatcherPriority.High,
                        new Windows.UI.Core.DispatchedHandler(() =>
                        {
                            UpdateUI("AudioThread Start");
                        }));

                        while (running)
                        {
                            ret = AV1.avCheckAudioBuf(avIndex);
                            if (ret < 0)
                                break;
                            else if (ret < 3)
                            {
                                new System.Threading.ManualResetEvent(false).WaitOne(120);
                                continue;
                            }
                            ret = AV1.avRecvAudioData(avIndex, audioBuffer, AUDIO_BUF_SIZE, frameInfo, FRAME_INFO_SIZE, frameNumber);
                            if (ret == -20015 || ret == -20016 || ret == -20010)
                            {
                                break;
                            }
                            else if (ret < 0)
                            {
                                new System.Threading.ManualResetEvent(false).WaitOne(50);
                                continue;
                            }
                        }

                    });

                }

            });

        }

        private void Button_Click4(object sender, RoutedEventArgs e)
        {
            running = false;
            new System.Threading.ManualResetEvent(false).WaitOne(500);
            AV1.avClientStop(avIndex);
            new System.Threading.ManualResetEvent(false).WaitOne(500);
            AV1.avDeInitialize();
            IOTC1.IOTC_DeInitialize();
            UpdateUI("DeInitialize");
        }
    }
}
