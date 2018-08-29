using System;
using System.Runtime.InteropServices;

namespace Iris2DNativeBridge
{
    public static class BitmapNative
    {
        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_Create1", CharSet = CharSet.Unicode)]
        public static extern IntPtr Create(string fileName);

        [DllImport("libiris2d.dll", EntryPoint = "Bitmap_Create2", CharSet = CharSet.Unicode)]
        public static extern IntPtr Create(UInt32 nWidth, UInt32 nHeight);
    }
}