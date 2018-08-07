#ifndef _H_EFFECT_BASE_GL_
#define _H_EFFECT_BASE_GL_

#include "Common/Iris2D/Effects/IEffect.h"
#include "Common/Util/RefCounter.h"
#include <string>
#include "OpenGL/Common.h"

namespace Iris2D {
	class TextureGL;
	class ShaderGL;
	namespace Effect {
		class EffectBaseGL : public IEffect, public RefCounter {
		protected:
			TextureGL* m_pTexture = nullptr;
			ShaderGL* m_pShader = nullptr;

			GLuint m_nVAO = 0;
			GLuint m_nVBO = 0;
			GLuint m_nEBO = 0;

		public:
			virtual bool Initialize(unsigned int nWidth, unsigned int nHeight);
			bool Update(const Sprite* pSprite) override = 0;
			virtual std::string GetVertexShaderFile() = 0;
			virtual std::string GetFragmentShaderFile() = 0;
			virtual TextureGL*  Render(TextureGL* pPreTexture) = 0;

		protected:
			virtual void Draw();

		private:
			bool CreateVertexBuffer(unsigned int nWidth, unsigned int nHeight);

		public:
			virtual ~EffectBaseGL();
		};
	}
}

#endif
