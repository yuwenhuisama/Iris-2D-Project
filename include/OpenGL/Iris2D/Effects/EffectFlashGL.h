#ifndef _H_EFFECT_FLASH_GL_
#define _H_EFFECT_FLASH_GL_

#include "OpenGL/Iris2D/Effects/EffectBaseGL.h"
#include "Common/Iris2D/Proxied.h"

namespace Iris2D {
	class IEffect;
	class TextureGL;
	class Color;

	namespace Effect {
		class EffectFlashGL : public EffectBaseGL, public Proxied<IEffect>{
		private:
			Color * m_pColor = nullptr;
			unsigned int m_nDuration = 0;
			unsigned int m_nCounter = 0;
			bool m_bLoop = false;

		public:
			static EffectFlashGL* Create(Color*& pColor, unsigned int nDuration, bool bLoop);
			static void Release(EffectFlashGL*& pEffectFlash);

		public:
			bool Update() override;
			std::string GetVertexShaderFile() override;
			std::string GetFragmentShaderFile() override;
			TextureGL* Render(TextureGL* pPreTexture) override;
			~EffectFlashGL();
		};
	}
}

#endif
