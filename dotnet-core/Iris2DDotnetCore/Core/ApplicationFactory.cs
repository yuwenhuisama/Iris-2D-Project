using System;
using System.Collections.Generic;
using System.Text;
using Iris2D.NativeBridge;

namespace Iris2D
{
    public static class ApplicationFactory
    {
        public enum GameApiType
        {
            OpenGL = 0,
            DirectX,
        }

        public static void InitApiType(GameApiType type) => ApplicationFactoryNative.InitApiType((Int32)type);

        public static GameApiType ApiType => (GameApiType)Enum.ToObject(typeof(GameApiType), ApplicationFactoryNative.GetApiType());
    }
}
