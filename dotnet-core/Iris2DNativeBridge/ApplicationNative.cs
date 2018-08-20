using System;
using System.Runtime.InteropServices;

namespace Iris2DNativeBridge
{
    public static class ApplicationNative
    {
        public delegate Int32 GameFunc();

        [StructLayout(LayoutKind.Sequential, Pack = 8, CharSet = CharSet.Unicode)]
        public struct AppStartupInfo
        {
            public IntPtr Instance;

            public int ShowCmd;

            public UInt32 X;
            public UInt32 Y;

            public UInt32 Width;
            public UInt32 Height;

            public GameFunc GameFunc;

            public string Title;
        }

        [DllImport("libiris2d.dll", EntryPoint = "App_GetInstance")]
        public static extern IntPtr GetInstance();

        [DllImport("libiris2d.dll", EntryPoint = "App_Initialize1", CharSet = CharSet.Unicode)]
        public static extern Int32 Initialize(IntPtr handle, IntPtr instance, UInt32 width, UInt32 height, GameFunc gameFunc, string title);

        [DllImport("libiris2d.dll", EntryPoint = "App_Initialize2", CharSet = CharSet.Unicode)]
        public static extern Int32 Initialize(IntPtr handle, IntPtr info);

        [DllImport("libiris2d.dll", EntryPoint = "App_Run")]
        public static extern Int32 Run(IntPtr handle);

        [DllImport("libiris2d.dll", EntryPoint = "App_Release")]
        public static extern void Release(IntPtr handle);

        [DllImport("libiris2d.dll", EntryPoint = "App_IsUninitialized")]
        public static extern Int32 IsUninitialized(IntPtr handle);

        [DllImport("libiris2d.dll", EntryPoint = "App_IsRunning")]
        public static extern Int32 IsRunning(IntPtr handle);

        [DllImport("libiris2d.dll", EntryPoint = "App_IsQuited")]
        public static extern Int32 IsQuited(IntPtr handle);

        [DllImport("libiris2d.dll", EntryPoint = "App_Quite")]
        public static extern void Quite(IntPtr handle);

        [DllImport("libiris2d.dll", EntryPoint = "GetTimeDelta")]
        public static extern float GetTimeDelta(IntPtr handle);
    }
}

