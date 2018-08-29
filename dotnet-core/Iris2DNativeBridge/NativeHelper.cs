using System;

namespace Iris2D.NativeBridge
{
    public static class NativeHelper
    {
        public static bool Success(ResultCode code)
        {
            return code == ResultCode.Success;
        }

        public static bool Failed(ResultCode code)
        {
            return !Success(code);
        }

        public static void AssertSuccess(Int32 numCode)
        {
            var code = (ResultCode) Enum.ToObject(typeof(ResultCode), numCode);

            if (!Success(code))
            {
                throw new Iris2DNativeException(code);
            }
        }
    }
}
