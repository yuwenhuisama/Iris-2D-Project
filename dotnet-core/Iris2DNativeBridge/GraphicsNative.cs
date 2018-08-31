using System;
using System.Runtime.InteropServices;

namespace Iris2D.NativeBridge
{
    public static class GraphicsNative
    {
        [DllImport("libiris2d.dll", EntryPoint = "Graphics_GetInstance")]
        public static extern IntPtr GetInstance();

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_Update")]
        public static extern Int32 Update(IntPtr handle);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_UpdateNoLock")]
        public static extern Int32 UpdateNoLock(IntPtr handle);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_Wait")]
        public static extern Int32 Wait(IntPtr handle, UInt32 duration);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_FadeOut")]
        public static extern Int32 FadeOut(IntPtr handle, UInt32 duration);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_FadeIn")]
        public static extern Int32 FadeIn(IntPtr handle, UInt32 duration);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_Freeze", CharSet = CharSet.Unicode)]
        public static extern Int32 Freeze(IntPtr handle);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_Transition", CharSet = CharSet.Unicode)]
        public static extern Int32 Transition(IntPtr handle, UInt32 duration, string filename, UInt32 vague);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_FrameReset")]
        public static extern void FrameReset(IntPtr handle);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_ResizeScreen", CharSet = CharSet.Unicode)]
        public static extern Int32 ResizeScreen(IntPtr handle, UInt32 width, UInt32 height);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_SetWidth")]
        public static extern void SetWidth(IntPtr handle, UInt32 width);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_GetWidth")]
        public static extern UInt32 GetWidth(IntPtr handle);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_SetHeight")]
        public static extern void SetHeight(IntPtr handle, UInt32 height);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_GetHeight")]
        public static extern UInt32 GetHeight(IntPtr handle);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_GetFrameCount")]
        public static extern UInt32 GetFrameCount(IntPtr handle);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_GetBrightness")]
        public static extern float GetBrightness(IntPtr handle);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_SetBrightness")]
        public static extern void SetBrightness(IntPtr handle, float brightness);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_SetFrameRate")]
        public static extern void SetFrameRate(IntPtr handle, float frameRate);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_GetFrameRate")]
        public static extern float GetFrameRate(IntPtr handle);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_Release")]
        public static extern void Release(IntPtr handle);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_GetMsPerUpdate")]
        public static extern float GetMsPerUpdate(IntPtr handle);
    }
}