using System;
using Iris2D.NativeBridge;

namespace Iris2D.Core
{
    class Color
    {
        private IntPtr m_handle;
        public IntPtr Handle
        {
            get => m_handle;
            set => throw new NotImplementedException();
        }

        public Color(IntPtr handle) {
            m_handle = handle;
        }
    }
}
