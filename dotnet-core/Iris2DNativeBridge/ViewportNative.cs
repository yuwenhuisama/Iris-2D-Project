using System;
using System.Runtime.InteropServices;

namespace Iris2D.NativeBridge
{
    public static class ViewportNative
    {
        [DllImport("libiris2d.dll", EntryPoint = "Viewport_Create", CharSet = CharSet.Unicode)]
        public static extern IntPtr Create(float fX, float fY, UInt32 nWidth, UInt32 nHeight);

        [DllImport("libiris2d.dll", EntryPoint = "Viewport_Create2", CharSet = CharSet.Unicode)]
        public static extern IntPtr Create(IntPtr pRect);

        [DllImport("libiris2d.dll", EntryPoint = "Viewport_Release", CharSet = CharSet.Unicode)]
        public static extern void Release(ref IntPtr pViewport);

        [DllImport("libiris2d.dll", EntryPoint = "Viewport_ForceRelease", CharSet = CharSet.Unicode)]
        public static extern void ForceRelease(ref IntPtr pViewport);

        [DllImport("libiris2d.dll", EntryPoint = "Viewport_SetOX", CharSet = CharSet.Unicode)]
        public static extern void SetOX(IntPtr hHandle, float fOX);

        [DllImport("libiris2d.dll", EntryPoint = "Viewport_GetOX", CharSet = CharSet.Unicode)]
        public static extern float GetOX(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Viewport_SetOY", CharSet = CharSet.Unicode)]
        public static extern void SetOY(IntPtr hHandle, float fOY);

        [DllImport("libiris2d.dll", EntryPoint = "Viewport_GetOY", CharSet = CharSet.Unicode)]
        public static extern float GetOY(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Viewport_SetSrcRect", CharSet = CharSet.Unicode)]
        public static extern void SetSrcRect(IntPtr hHandle, ref IntPtr pSrcRect);

        [DllImport("libiris2d.dll", EntryPoint = "Viewport_GetSrcRect", CharSet = CharSet.Unicode)]
        public static extern IntPtr GetSrcRect(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Viewport_SetTone", CharSet = CharSet.Unicode)]
        public static extern void SetTone(IntPtr hHandle, ref IntPtr pTone);

        [DllImport("libiris2d.dll", EntryPoint = "Viewport_GetTone", CharSet = CharSet.Unicode)]
        public static extern IntPtr GetTone(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Viewport_SetZ", CharSet = CharSet.Unicode)]
        public static extern void SetZ(IntPtr hHandle, float fZ);

        [DllImport("libiris2d.dll", EntryPoint = "Viewport_GetZ", CharSet = CharSet.Unicode)]
        public static extern float GetZ(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Viewport_GetWidth", CharSet = CharSet.Unicode)]
        public static extern UInt32 GetWidth(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Viewport_GetHeight", CharSet = CharSet.Unicode)]
        public static extern UInt32 GetHeight(IntPtr hHandle);
    }
}
