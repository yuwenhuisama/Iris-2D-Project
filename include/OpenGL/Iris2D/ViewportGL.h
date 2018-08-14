#ifndef _H_VIEWPORT_GL_
#define _H_VIEWPORT_GL_

#include "Common/Iris2D/IViewport.h"
#include "Common/Iris2D/Proxied.h"
#include "Common/Util/Result.h"

//#include <unordered_set>
#include <map>
#include "OpenGL/OpenGLUtil/ViewportShaderBuffersGL.h"
#include "Common/Util/DirtyChecker.h"

namespace Iris2D {
	class Viewport;
	class Rect;
	class Color;

	class SpriteGL;
	class TextureGL;
	typedef Color Tone;

	class ViewportGL : public Proxied<Viewport>, public IViewport {
	public:
		static ViewportGL* Create(float fX, float fY, unsigned int nWidth, unsigned int nHeight, IR_PARAM_RESULT);
		static ViewportGL* Create(const Rect* pRect, IR_PARAM_RESULT);
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

		std::multimap<unsigned int, SpriteGL*, std::less<float>> m_stSprites;

		unsigned int m_nVAO = 0;
		unsigned int m_nVBO = 0;
		unsigned int m_nEBO = 0;

		TextureGL* m_pTexture = nullptr;

		ViewportVertexBufferGL m_vvbBuffer;

		DirtyChecker m_dcChecker;
		DirtyChecker::DirtyCheckerHandler m_hPosHandler = 0;

	public:
		// Í¨¹ý IViewport ¼Ì³Ð
		virtual void SetOX(float fOX) override;
		virtual float GetOX() const override;
		virtual void SetOY(float fOY) override;
		virtual float GetOY() const override;
		virtual void SetSrcRect(Rect *& pSrcRect) override;
		virtual Rect * GetSrcRect() const override;
		virtual void SetTone(Tone *& pTone) override;
		virtual Tone * GetTone() const override;
		virtual void SetZ(float fZ) override;
		virtual float GetZ() override;
		virtual unsigned int GetWidth() const override;
		virtual unsigned int GetHeight() const override;

	public:
		void RenderSprites();
		void Render();

		void AddSprite(SpriteGL*& pSprite);
		void RemoveSprite(SpriteGL*& pSprite);

	private:
		bool CreateViewportVertexBufferAndFrameBuffer(unsigned int nWidth, unsigned int nHeight);

		ViewportGL();
		~ViewportGL();
	};
}

#endif // !_H_VIEWPORT_GL_
