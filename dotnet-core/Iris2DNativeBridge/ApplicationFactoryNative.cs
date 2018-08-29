using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;

namespace Iris2D.NativeBridge
{
    public static class ApplicationFactoryNative
    {
        [DllImport("libiris2d.dll", EntryPoint = "App_InitApiType")]
        public static extern void InitApiType(Int32 type);

        [DllImport("libiris2d.dll", EntryPoint = "App_GetApiType")]
        public static extern Int32 GetApiType();
    }
}
