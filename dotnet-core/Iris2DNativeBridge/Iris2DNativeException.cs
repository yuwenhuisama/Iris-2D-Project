using System;

namespace Iris2D.NativeBridge
{
    public class Iris2DNativeException : Exception
    {
        public Iris2DNativeException(ResultCode code): base(String.Format("Native exception hanpended : {0}", Enum.GetName(code.GetType(), code)))
        {
        }
    }
}
