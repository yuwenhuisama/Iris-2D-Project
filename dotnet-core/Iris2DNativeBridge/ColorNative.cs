using System;
using System.Runtime.InteropServices;


namespace Iris2D.NativeBridge
{
    public static class ColorNative
    {
        [DllImport("libiris2d.dll", EntryPoint = "Color_Create", CharSet = CharSet.Unicode)]
        public static extern IntPtr Create(Byte cRed, Byte cGreen, Byte cBlue, Byte cAlpha);

        [DllImport("libiris2d.dll", EntryPoint = "Color_Release", CharSet = CharSet.Unicode)]
        public static extern void Release(ref IntPtr pColor);

        [DllImport("libiris2d.dll", EntryPoint = "Color_SetRed", CharSet = CharSet.Unicode)]
        public static extern void SetRed(IntPtr hHandle, Byte cRed);

        [DllImport("libiris2d.dll", EntryPoint = "Color_GetRed", CharSet = CharSet.Unicode)]
        public static extern Byte GetRed(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Color_SetGreen", CharSet = CharSet.Unicode)]
        public static extern void SetGreen(IntPtr hHandle, Byte cGreen);

        [DllImport("libiris2d.dll", EntryPoint = "Color_GetGreen", CharSet = CharSet.Unicode)]
        public static extern Byte GetGreen(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Color_SetBlue", CharSet = CharSet.Unicode)]
        public static extern void SetBlue(IntPtr hHandle, Byte cBlue);

        [DllImport("libiris2d.dll", EntryPoint = "Color_GetBlue", CharSet = CharSet.Unicode)]
        public static extern Byte GetBlue(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Color_SetAlpha", CharSet = CharSet.Unicode)]
        public static extern void SetAlpha(IntPtr hHandle, Byte cAlpha);

        [DllImport("libiris2d.dll", EntryPoint = "Color_GetAlpha", CharSet = CharSet.Unicode)]
        public static extern Byte GetAlpha(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Color_Set", CharSet = CharSet.Unicode)]
        public static extern void Set(IntPtr hHandle, Byte cRed, Byte cGreen, Byte cBlue, Byte cAlpha);
    }
}
