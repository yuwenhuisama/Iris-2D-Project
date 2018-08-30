using System;
using System.Runtime.InteropServices;

namespace Iris2D.NativeBridge
{
    public enum BitmapAlignType
    {
        nLeft = 0,
        nCenter,
        nRight,
    }

    public static class BitmapNative
    {
        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_Create", CharSet = CharSet.Unicode)]
        public static extern IntPtr Create(string fileName);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_Create2", CharSet = CharSet.Unicode)]
        public static extern IntPtr Create(UInt32 nWidth, UInt32 nHeight);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_Create3", CharSet = CharSet.Unicode)]
        public static extern IntPtr Create(IntPtr hBitmap);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_CopyFrom", CharSet = CharSet.Unicode)]
        public static extern IntPtr CopyFrom(IntPtr hBitmap);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_Release", CharSet = CharSet.Unicode)]
        public static extern void Release(ref IntPtr hBitmap);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_GetWidth", CharSet = CharSet.Unicode)]
        public static extern UInt32 GetWidth(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_GetHeight", CharSet = CharSet.Unicode)]
        public static extern UInt32 GetHeight(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_Blt", CharSet = CharSet.Unicode)]
        public static extern ResultCode Blt(IntPtr hHandle, UInt32 nDestX, UInt32 nDestY, IntPtr hSrcBitmap, IntPtr hSrcRect, float fOpacity);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_StretchBlt", CharSet = CharSet.Unicode)]
        public static extern ResultCode StretchBlt(IntPtr hHandle, IntPtr hDestRect, IntPtr hSrcBitmap, IntPtr hSrcRect, float fOpacity);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_FillRect", CharSet = CharSet.Unicode)]
        public static extern ResultCode FillRect(IntPtr hHandle, UInt32 nX, UInt32 nY, UInt32 nWidth, UInt32 nHeight, IntPtr hColor);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_FillRect2", CharSet = CharSet.Unicode)]
        public static extern ResultCode FillRect(IntPtr hHandle, IntPtr hRect, IntPtr hColor);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_Clear", CharSet = CharSet.Unicode)]
        public static extern ResultCode Clear(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_ClearRect", CharSet = CharSet.Unicode)]
        public static extern ResultCode ClearRect(IntPtr hHandle, UInt32 nX, UInt32 nY, UInt32 nWidth, UInt32 nHeight);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_ClearRect2", CharSet = CharSet.Unicode)]
        public static extern ResultCode ClearRect(IntPtr hHandle, IntPtr hRect);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_GetPixel", CharSet = CharSet.Unicode)]
        public static extern IntPtr GetPixel(IntPtr hHandle, UInt32 nX, UInt32 nY);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_SetPixel", CharSet = CharSet.Unicode)]
        public static extern ResultCode SetPixel(IntPtr hHandle, UInt32 nX, UInt32 nY, IntPtr hColor);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_SaveToFile", CharSet = CharSet.Unicode)]
        public static extern ResultCode SaveToFile(IntPtr hHandle, string wstrFilePath);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_HueChange", CharSet = CharSet.Unicode)]
        public static extern ResultCode HueChange(IntPtr hHandle, float fHue);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_SetFont", CharSet = CharSet.Unicode)]
        public static extern void SetFont(IntPtr hHandle, ref IntPtr pFont);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_GetFont", CharSet = CharSet.Unicode)]
        public static extern IntPtr GetFont(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_TextSize", CharSet = CharSet.Unicode)]
        public static extern UInt32 TextSize(IntPtr hHandle, IntPtr hFont, string wstrText);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_DrawText", CharSet = CharSet.Unicode)]
        public static extern ResultCode DrawText(IntPtr hHandle, UInt32 nX, UInt32 nY, UInt32 nWidth, UInt32 nHeight, string wstrText, BitmapAlignType nAlign);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_DrawText2", CharSet = CharSet.Unicode)]
        public static extern ResultCode DrawText(IntPtr hHandle, IntPtr hRect, string wstrText, BitmapAlignType nAlign);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_Dispose", CharSet = CharSet.Unicode)]
        public static extern ResultCode Dispose(IntPtr hHandle);
    }
}