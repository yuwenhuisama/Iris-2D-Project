using System;
using System.Runtime.InteropServices;

namespace Iris2DNativeBridge
{
    public static class GraphicsNative
    {
        [DllImport("libiris2d.dll", EntryPoint = "Graphics_GetInstance")]
        public static extern IntPtr GetInstance();

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_Update")]
        public static extern void Update(IntPtr handle, IntPtr result);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_UpdateNoLock")]
        public static extern void UpdateNoLock(IntPtr handle, IntPtr result);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_Wait")]
        public static extern void Wait(IntPtr handle, UInt32 duration, IntPtr result);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_FadeOut")]
        public static extern void FadeOut(IntPtr handle, UInt32 duration, IntPtr result);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_FadeIn")]
        public static extern void FadeIn(IntPtr handle, UInt32 duration, IntPtr result);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_Freeze", CharSet = CharSet.Unicode)]
        public static extern void Freeze(IntPtr handle);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_Transition", CharSet = CharSet.Unicode)]
        public static extern void Transition(IntPtr handle, UInt32 duration, string filename, UInt32 vague, IntPtr result);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_FrameReset")]
        public static extern void FrameReset(IntPtr handle);

        [DllImport("libiris2d.dll", EntryPoint = "Graphics_ResizeScreen", CharSet = CharSet.Unicode)]
        public static extern void ResizeScreen(IntPtr handle, UInt32 width, UInt32 height, IntPtr result);

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