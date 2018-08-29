namespace Iris2D.NativeBridge
{
    public enum ResultCode
    {
        Success = 0,
        OpenGLInitializeFailed,
        WindowInitializeFailed,
        TextureSettingInitializeFailed,
        GraphicsInitializeFailed,
        ShaderInitializeFailed,
        OpenGLVertexBufferCreateFailed,
        EffectInitializeFailed,
        EffectUpdateFailed,
        RenderBufferCreateFailed,
        D2DInitializeFailed,
        D3DInitializeFailed,
        D2DOperationFailed,
        TextureOutputFailed,
    }
}
