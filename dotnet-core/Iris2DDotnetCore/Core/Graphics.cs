﻿using System;
using Iris2D.NativeBridge;

namespace Iris2D.Core
{
    public class Graphics
    {
        private readonly IntPtr m_handle;

        private Graphics(IntPtr handle)
        {
            m_handle = handle;
        }

        public static readonly Graphics Instance = new Graphics(GraphicsNative.GetInstance());

        public void Update() => NativeHelper.AssertSuccess(GraphicsNative.Update(m_handle, IntPtr.Zero));

        public void UpdateNoLock() => NativeHelper.AssertSuccess(GraphicsNative.UpdateNoLock(m_handle, IntPtr.Zero));

        public void Wait(UInt32 duration) => NativeHelper.AssertSuccess(GraphicsNative.Wait(m_handle, duration, IntPtr.Zero));

        public void FadeOut(UInt32 duration) => NativeHelper.AssertSuccess(GraphicsNative.FadeOut(m_handle, duration, IntPtr.Zero));

        public void FadeIn(UInt32 duration) => NativeHelper.AssertSuccess(GraphicsNative.FadeIn(m_handle, duration, IntPtr.Zero));

        public void Freeze() => NativeHelper.AssertSuccess(GraphicsNative.Freeze(m_handle));

        public void Transition(UInt32 duration, string filename, UInt32 vague) => NativeHelper.AssertSuccess(GraphicsNative.Transition(m_handle, duration, filename, vague, IntPtr.Zero));

        public void FrameReset() => GraphicsNative.FrameReset(m_handle);

        public void ResizeScreen(UInt32 width, UInt32 height) => NativeHelper.AssertSuccess(GraphicsNative.ResizeScreen(m_handle, width, height, IntPtr.Zero));

        public UInt32 Width
        {
            get => GraphicsNative.GetWidth(m_handle);
            set => GraphicsNative.SetWidth(m_handle, value);
        }

        public UInt32 Height
        {
            get => GraphicsNative.GetHeight(m_handle);
            set => GraphicsNative.SetHeight(m_handle, value);
        }

        public UInt32 FrameCount => GraphicsNative.GetFrameCount(m_handle);

        public float Brightness
        {
            get => GraphicsNative.GetBrightness(m_handle);
            set => GraphicsNative.SetBrightness(m_handle, value);
        }

        public float FrameRate
        {
            get => GraphicsNative.GetFrameRate(m_handle);
            set => GraphicsNative.SetFrameRate(m_handle, value);
        }

        public void Release() => GraphicsNative.Release(m_handle);
}
}
