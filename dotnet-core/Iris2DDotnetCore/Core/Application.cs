using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using Iris2D.NativeBridge;

namespace Iris2D.Core
{
    public class Application
    {

        public delegate bool GameFunc();

        public class AppStartupInfo
        {
            public UInt32 X { get; set; }
            public UInt32 Y { get; set; }

            public UInt32 Width { get; set; }
            public UInt32 Height { get; set; }

            public GameFunc GameFunc { get; set; }

            public string Title { get; set; }
        }

        private Application(IntPtr handle)
        {
            m_handle = handle;
        }

        public static readonly Application Instance = new Application(ApplicationNative.GetInstance());

        private readonly IntPtr m_handle;

        public void Initialize(UInt32 width, UInt32 height, GameFunc gameFunc, string title) =>
            NativeHelper.AssertSuccess(ApplicationNative.Initialize(m_handle, Process.GetCurrentProcess().Handle,
                width, height,
                () => gameFunc() ? 0 : 1,
                title));

        public void Initialize(AppStartupInfo startupInfo)
        {
            var nativeInfo = new ApplicationNative.AppStartupInfo()
            {
                Instance = Process.GetCurrentProcess().Handle,
                GameFunc = () => startupInfo.GameFunc() ? 1 : 0,
                Height = startupInfo.Height,
                Width = startupInfo.Width,
                ShowCmd = 0,
                Title = startupInfo.Title,
                X = startupInfo.X,
                Y = startupInfo.Y,
            };

            int nSizeOfStructure = Marshal.SizeOf<ApplicationNative.AppStartupInfo>();
            IntPtr intPtr = Marshal.AllocHGlobal(nSizeOfStructure);
            Marshal.StructureToPtr(nativeInfo, intPtr, false);

            var result = ApplicationNative.Initialize(m_handle, intPtr);
            Marshal.FreeHGlobal(intPtr);

            NativeHelper.AssertSuccess(result);
        }

        public bool Run() => ApplicationNative.Run(m_handle) != 0;

        public void Release() => ApplicationNative.Release(m_handle);

        public bool IsUninitialized => ApplicationNative.IsUninitialized(m_handle) != 0;

        public bool IsQuited => ApplicationNative.IsQuited(m_handle) != 0;

        public void Quite() => ApplicationNative.Quite(m_handle);

        public float TimeDelta => ApplicationNative.GetTimeDelta(m_handle);
    }
}
