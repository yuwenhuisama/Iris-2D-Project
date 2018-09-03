using System;
using System.Runtime.InteropServices;

namespace Iris2D.NativeBridge
{
    public static class FontNative
    {
        [DllImport("libiris2d.dll", EntryPoint = "Font_Existed", CharSet = CharSet.Unicode)]
        public static extern bool Existed(ref string wstrFontName);

        [DllImport("libiris2d.dll", EntryPoint = "Font_Create", CharSet = CharSet.Unicode)]
        public static extern IntPtr Create(ref string wstrFontName);

        [DllImport("libiris2d.dll", EntryPoint = "Font_Release", CharSet = CharSet.Unicode)]
        public static extern void Release(ref IntPtr pFont);

        [DllImport("libiris2d.dll", EntryPoint = "Font_GetDefaultName", CharSet = CharSet.Unicode)]
        public static extern string GetDefaultName();

        [DllImport("libiris2d.dll", EntryPoint = "Font_GetDefaultSize", CharSet = CharSet.Unicode)]
        public static extern UInt32 GetDefaultSize();

        [DllImport("libiris2d.dll", EntryPoint = "Font_GetDefaultBold", CharSet = CharSet.Unicode)]
        public static extern bool GetDefaultBold();

        [DllImport("libiris2d.dll", EntryPoint = "Font_GetDefaultItalic", CharSet = CharSet.Unicode)]
        public static extern bool GetDefaultItalic();

        [DllImport("libiris2d.dll", EntryPoint = "Font_GetDefaultShadow", CharSet = CharSet.Unicode)]
        public static extern bool GetDefaultShadow();

        [DllImport("libiris2d.dll", EntryPoint = "Font_GetDefaultColor", CharSet = CharSet.Unicode)]
        public static extern IntPtr GetDefaultColor();

        [DllImport("libiris2d.dll", EntryPoint = "Font_SetName", CharSet = CharSet.Unicode)]
        public static extern void SetName(IntPtr hHandle, ref string wstrFontName);

        [DllImport("libiris2d.dll", EntryPoint = "Font_GetName", CharSet = CharSet.Unicode)]
        public static extern ref string GetName(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Font_SetSize", CharSet = CharSet.Unicode)]
        public static extern void SetSize(IntPtr hHandle, UInt32 nSize);

        [DllImport("libiris2d.dll", EntryPoint = "Font_GetSize", CharSet = CharSet.Unicode)]
        public static extern UInt32 GetSize(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Font_SetBold", CharSet = CharSet.Unicode)]
        public static extern void SetBold(IntPtr hHandle, bool bBold);

        [DllImport("libiris2d.dll", EntryPoint = "Font_GetBold", CharSet = CharSet.Unicode)]
        public static extern bool GetBold(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Font_SetItalic", CharSet = CharSet.Unicode)]
        public static extern void SetItalic(IntPtr hHandle, bool bItalic);

        [DllImport("libiris2d.dll", EntryPoint = "Font_GetItalic", CharSet = CharSet.Unicode)]
        public static extern bool GetItalic(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Font_SetShadow", CharSet = CharSet.Unicode)]
        public static extern void SetShadow(IntPtr hHandle, bool bShadow);

        [DllImport("libiris2d.dll", EntryPoint = "Font_GetShadow", CharSet = CharSet.Unicode)]
        public static extern bool GetShadow(IntPtr hHandle);

        [DllImport("libiris2d.dll", EntryPoint = "Font_SetColor", CharSet = CharSet.Unicode)]
        public static extern void SetColor(IntPtr hHandle, ref IntPtr pColor);

        [DllImport("libiris2d.dll", EntryPoint = "Font_GetColor", CharSet = CharSet.Unicode)]
        public static extern IntPtr GetColor(IntPtr hHandle);
    }
}
