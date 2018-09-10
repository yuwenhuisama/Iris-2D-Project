#ifndef _H_VIEWPORT_GL_
#define _H_VIEWPORT_GL_

#include "Common/Iris2D/IViewport.h"
#include "Common/Iris2D/Proxied.h"
#include "Common/Util/Result.h"

//#include <unordered_set>
#include <map>
#include "OpenGL/OpenGLUtil/ViewportShaderBuffersGL.h"
#include "Common/Util/DirtyChecker.h"
#include "Common/Util/RefCounter.h"

namespace Iris2D {
	class Viewport;
	class Rect;
	class Color;

	class SpriteBaseGL;
	class TextureGL;
	typedef Color Tone;

	class ViewportGL : public Proxied<Viewport>, public IViewport, public RefCounter {
		REF_FRIEND_DECLARE

	public:
		static ViewportGL* Create(float fX, float fY, unsigned int nWidth, unsigned int nHeight);
		static ViewportGL* Create(const Rect* pRect);
		static void Release(ViewportGL*& pViewport);

		static void ForceRelease(ViewportGL*& pViewport);

		static bool InitializeGlobalViewport(float fX, float fY, unsigned int nWindowWidth, unsigned int nWindowHeight);
		static bool ReleaseGlobalViewport();

		static Viewport* GetGlobalViewport();

	private:
		static Viewport* sm_pGlobalViewport;

	private:
		Rect* m_pSrcRect = nullptr;
		Tone* m_pTone = nullptr;

		float m_fX = 0.0f;
		float m_fY = 0.0f;
		float m_fZ = 0.0f;

		std::multimap<float, SpriteBaseGL*, std::less<>> m_stSprites;

		unsigned int m_nVAO = 0;
		unsigned int m_nVBO = 0;
		unsigned int m_nEBO = 0;

		TextureGL* m_pTexture = nullptr;

		ViewportVertexBufferGL m_vvbBuffer;

		DirtyChecker m_dcChecker;
		DirtyChecker::DirtyCheckerHandler m_hPosHandler = 0;

	public:
		// Í¨¹ý IViewport ¼Ì³Ð
		void SetOX(float fOX) override;
		float GetOX() const override;
		void SetOY(float fOY) override;
		float GetOY() const override;
		void SetSrcRect(Rect *& pSrcRect) override;
		Rect * GetSrcRect() const override;
		void SetTone(Tone *& pTone) override;
		Tone * GetTone() const override;
		void SetZ(float fZ) override;
		float GetZ() override;
		unsigned int GetWidth() const override;
		unsigned int GetHeight() const override;

	public:
		ResultCode RenderSprites();
		ResultCode Render();

		void AddSprite(SpriteBaseGL* pSprite);
		void RemoveSprite(SpriteBaseGL* pSprite);

	private:
		bool CreateViewportVertexBufferAndFrameBuffer(unsigned int nWidth, unsigned int nHeight);

		ViewportGL();
		virtual ~ViewportGL();
	};
}

#endif // !_H_VIEWPORT_GL_
