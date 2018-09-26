#include "OpenGL/Iris2D/Effects/EffectFlashGL.h"
#include "OpenGL/Iris2D/Shaders/ShaderGL.h"
#include "OpenGL/OpenGLUtil/TextureGL.h"
#include "Common/Iris2D/Color.h"
#include "OpenGL/Iris2D/ColorGL.h"
#include "Common/Util/ProxyConvert.h"

namespace Iris2D {
	namespace Effect {
		EffectFlashGL* EffectFlashGL::Create(Color*& pColor, unsigned int nDuration, bool bLoop) {

			if (!pColor || nDuration <= 0) {
				return nullptr;
			}

			const auto pEffect =  new EffectFlashGL();

			pEffect->m_bLoop = bLoop;
			pEffect->m_nDuration = nDuration;
			pEffect->m_nCounter = nDuration;

			RefferAssign<ColorGL*>(pEffect->m_pColor, pColor);

			return pEffect;
		}

		void EffectFlashGL::Release(EffectFlashGL*& pEffectFlash) {

			if (!pEffectFlash) {
				return;
			}

			RefferRelease(pEffectFlash);
		}

		bool EffectFlashGL::Update() {

			if (m_bLoop && m_nCounter == 0) {
				m_nCounter = m_nDuration;
			} else if (m_nCounter > 0) {
				--m_nCounter;
			}

			return true;
		}

		std::string EffectFlashGL::GetVertexShaderFile() {
			return "shaders/GLSL/effects/effect_common_vertex_shader.vert";
		}

		std::string EffectFlashGL::GetFragmentShaderFile() {
			return "shaders/GLSL/effects/effect_flash_fragment_shader.frag";
		}

		TextureGL*  EffectFlashGL::Render(TextureGL* pPreTexture) {
			
			if (!m_bLoop && m_nCounter == 0) {
				return pPreTexture;
			}

			const auto mt4Projection = glm::ortho(0.0f, static_cast<float>(m_pTexture->GetWidth()), static_cast<float>(m_pTexture->GetHeight()), 0.0f, -1.0f, 1.0f);
			m_pShader->Use();
			m_pShader->SetMatrix("projectionMat", mt4Projection);
			m_pShader->SetFloat4("targetColor", m_pColor->GetRed() / 255.f, m_pColor->GetGreen() / 255.f, m_pColor->GetBlue() / 255.f, m_pColor->GetAlpha() / 255.f);
			m_pShader->SetFloat2("counter", glm::vec2 { m_nCounter, m_nDuration });

			pPreTexture->UseTexture();

			m_pTexture->UseTextureAsFrameBuffer();

			glClearColor(0.f, 0.f, 0.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			Draw();
			m_pTexture->RestoreFrameBuffer();

			return m_pTexture;
		}

		EffectFlashGL::~EffectFlashGL() {
			Color::Release(m_pColor);
		}
	}
}
