#ifndef _H_IRISVIEWPORT_
#define _H_IRISVIEWPORT_

#include "IrisCommon.h"
#include "Iris2D Util/IrisViewportShaderBuffers.h"

namespace Iris2D
{
	class IrisSprite;
	class IrisRect;
	class IrisTexture;

	__declspec(align(16))
	class IrisViewport
	{
	private:
		std::unordered_set<IrisSprite*> m_stSprits;

		ID3D11Buffer* m_pVertexBuffer = nullptr;
		IrisTexture* m_pTexture = nullptr;

		IrisViewportVertexShaderBuffer m_ivvsVertexBuffer;
		IrisViewportPixelShaderBuffer m_ivpsPixelBuffer;

		DirectX::XMMATRIX m_mxViewProjMatrix = DirectX::XMMatrixIdentity();

		float m_fX = 0.0f;
		float m_fY = 0.0f;
		float m_fZ = 1.0f;

		bool m_bVertexBufferDirtyFlag = false;
		bool m_bVisible = true;

	public:
		static IrisViewport* sm_pGlobalViewport;

	public:
		static IrisViewport* Create(float fX, float fY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT);
		static IrisViewport* Create(IrisRect* pRect, IR_PARAM_RESULT);
		static void Release(IrisViewport*& pViewport);
		static void InnerRelease(IrisViewport*& pViewport);

		static bool InitGlobalViewport(unsigned int nWindowWidth, unsigned int nWindowHeight);
		static void ReleaseGlobalViewport();
		static IrisViewport* GetGlobalViewport();

	public:
		bool Dispose();
		bool RenderSprite();
		bool RenderSelf();

		void AddSprite(IrisSprite* pSprite);
		void RemoveSprite(IrisSprite* pSprite);

	private:
		bool CreateViewportVertexBuffer(unsigned int nWidth, unsigned int nHeight);

		IrisViewport() = default;
		~IrisViewport();
	};

}

#endif // !_H_IRISVIEWPORT_
