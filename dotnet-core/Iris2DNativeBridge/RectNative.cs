using System;
using System.Runtime.InteropServices;

namespace Iris2D.NativeBridge
{
    public static class RectNative
    {
        [DllImport("libiris2d.dll", EntryPoint = "Rect_Create", CharSet = CharSet.Unicode)]
        public static extern IntPtr Create(float fX, float fY, float fWidth, float fHeight);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_Create2", CharSet = CharSet.Unicode)]
        public static extern IntPtr Create2(float fLeft, float fTop, float fRight, float fBottom);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_Release", CharSet = CharSet.Unicode)]
        public static extern void Release(ref IntPtr pRect);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_SetX", CharSet = CharSet.Unicode)]
        public static extern void SetX(IntPtr hHandle, float fX);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_GetX", CharSet = CharSet.Unicode)]
        public static extern float GetX(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_SetY", CharSet = CharSet.Unicode)]
        public static extern void SetY(IntPtr hHandle, float fY);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_GetY", CharSet = CharSet.Unicode)]
        public static extern float GetY(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_SetWidth", CharSet = CharSet.Unicode)]
        public static extern void SetWidth(IntPtr hHandle, float fWidth);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_GetWidth", CharSet = CharSet.Unicode)]
        public static extern float GetWidth(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_GetHeight", CharSet = CharSet.Unicode)]
        public static extern void SetHeight(IntPtr hHandle, float fHeight);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_GetHeight", CharSet = CharSet.Unicode)]
        public static extern float GetHeight(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_SetLeft", CharSet = CharSet.Unicode)]
        public static extern void SetLeft(IntPtr hHandle, float fLeft);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_GetLeft", CharSet = CharSet.Unicode)]
        public static extern float GetLeft(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_SetTop", CharSet = CharSet.Unicode)]
        public static extern void SetTop(IntPtr hHandle, float fTop);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_GetX", CharSet = CharSet.Unicode)]
        public static extern float GetTop(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_SetRight", CharSet = CharSet.Unicode)]
        public static extern void SetRight(IntPtr hHandle, float fRight);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_GetRight", CharSet = CharSet.Unicode)]
        public static extern float GetRight(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_SetBottom", CharSet = CharSet.Unicode)]
        public static extern void SetBottom(IntPtr hHandle, float fBottom);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_GetBottom", CharSet = CharSet.Unicode)]
        public static extern float GetBottom(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_Set", CharSet = CharSet.Unicode)]
        public static extern void Set(IntPtr hHandle, float fX, float fY, float fWidth, float fHeight);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_Set2", CharSet = CharSet.Unicode)]
        public static extern void Set2(IntPtr hHandle, float fLeft, float fTop, float fRight, float fBottom);

        [DllImport("libiris2d.dll", EntryPoint = "Rect_CheckInsectionWith", CharSet = CharSet.Unicode)]
        public static extern bool CheckInsectionWith(IntPtr hHandle, IntPtr pRect);
    }
}
