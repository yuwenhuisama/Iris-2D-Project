using System;
using Iris2D.NativeBridge;

namespace Iris2D.Core
{
    class Bitmap
    {
        private IntPtr m_handle;
        public IntPtr Handle
        {
            get => m_handle;
            set => throw new NotImplementedException();
        }

        public Bitmap(IntPtr handle) {
            m_handle = handle;
        }

        public static Bitmap Create(string fileName) => new Bitmap(BitmapNative.Create(fileName));

        public static Bitmap Create(UInt32 nWidth, UInt32 nHeight) => new Bitmap(BitmapNative.Create(nWidth, nHeight));

        public static Bitmap Create(Bitmap bitmap) => new Bitmap(BitmapNative.Create(bitmap.m_handle));

        public static Bitmap CopyFrom(Bitmap bitmap) => new Bitmap(BitmapNative.CopyFrom(bitmap.m_handle));

        public static void Release(Bitmap bitmap) => BitmapNative.Release(ref bitmap.m_handle);

        public void Blt(UInt32 nDestX, UInt32 nDestY, Bitmap hSrcBitmap, Rect hSrcRect, float fOpacity) =>
            NativeHelper.AssertSuccess(BitmapNative.Blt(m_handle, nDestX, nDestY, hSrcBitmap.m_handle, hSrcRect.Handle, fOpacity));

        public void StretchBlt(Rect hDestRect, Bitmap hSrcBitmap, Rect hSrcRect, float fOpacity) =>
            NativeHelper.AssertSuccess(BitmapNative.StretchBlt(m_handle, hDestRect.Handle, hSrcBitmap.m_handle, hSrcRect.Handle, fOpacity));

        public void FillRect(UInt32 nX, UInt32 nY, UInt32 nWidth, UInt32 nHeight, Color hColor) =>
            NativeHelper.AssertSuccess(BitmapNative.FillRect(m_handle, nX, nY, nWidth, nHeight, hColor.Handle));

        public void FillRect(Rect hRect, Color hColor) => 
            NativeHelper.AssertSuccess(BitmapNative.FillRect(m_handle, hRect.Handle, hColor.Handle));

        public void Clear() => NativeHelper.AssertSuccess(BitmapNative.Clear(m_handle));

        public void ClearRect(UInt32 nX, UInt32 nY, UInt32 nWidth, UInt32 nHeight) =>
            NativeHelper.AssertSuccess(BitmapNative.ClearRect(m_handle, nX, nY, nWidth, nHeight));

        public void ClearRect(Rect hRect) => NativeHelper.AssertSuccess(BitmapNative.ClearRect(m_handle, hRect.Handle));

        public Color GetPixel(UInt32 nX, UInt32 nY) => new Color(BitmapNative.GetPixel(m_handle, nX, nY));

        public void SetPixel(UInt32 nX, UInt32 nY, Color hColor) => NativeHelper.AssertSuccess(BitmapNative.SetPixel(m_handle, nX, nY, hColor.Handle));

        public void SaveToFile(string wstrFilePath) => NativeHelper.AssertSuccess(BitmapNative.SaveToFile(m_handle, wstrFilePath));

        public void HueChange(float fHue) => NativeHelper.AssertSuccess(BitmapNative.HueChange(m_handle, fHue));

        public UInt32 TextSize(Font hFont, string wstrText) => BitmapNative.TextSize(m_handle, hFont.Handle, wstrText);

        public void DrawText(UInt32 nX, UInt32 nY, UInt32 nWidth, UInt32 nHeight, string wstrText, BitmapAlignType nAlign) =>
            NativeHelper.AssertSuccess(BitmapNative.DrawText(m_handle, nX, nY, nWidth, nHeight, wstrText, nAlign));

        public void DrawText(Rect hRect, string wstrText, BitmapAlignType nAlign) => NativeHelper.AssertSuccess(BitmapNative.DrawText(m_handle, hRect.Handle, wstrText, nAlign));

        public void Dispose() => NativeHelper.AssertSuccess(BitmapNative.Dispose(m_handle));

        public UInt32 Width {
            get => BitmapNative.GetWidth(m_handle);
            private set => throw new NotImplementedException();
        }

        public UInt32 Height {
            get => BitmapNative.GetHeight(m_handle);
            private set => throw new NotImplementedException();
        }

        public Font Font {
            get => new Font(BitmapNative.GetFont(m_handle));
            set {
                IntPtr fontHandle = value.Handle;
                BitmapNative.SetFont(m_handle, ref fontHandle);
            }
        }
    }
}
