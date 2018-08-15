#include "OpenGL/Iris2D/Effects/EffectBaseGL.h"
#include "OpenGL/OpenGLUtil/TextureGL.h"
#include "OpenGL/Iris2D/Shaders/ShaderGL.h"
#include "OpenGL/OpenGLUtil/EffectFrameBufferVertexGL.h"
#include "OpenGL/OpenGLUtil/OpenGLHelper.h"
#include "OpenGL/Iris2D/GraphicsGL.h"

namespace Iris2D {
	namespace Effect {

		bool EffectBaseGL::Initialize(unsigned int nWidth, unsigned int nHeight) {
			m_pTexture = TextureGL::CreateFrameBuffer(nWidth, nHeight);
			if (!m_pTexture) {
				return false;
			}

			m_pShader = new ShaderGL();
			if (!m_pShader->Initialize(GetVertexShaderFile(), GetFragmentShaderFile())) {
				return false;
			}

			return CreateVertexBuffer(nWidth, nHeight);
		}

		void EffectBaseGL::Draw() {
			glViewport(0, 0, m_pTexture->GetWidth(), m_pTexture->GetHeight());

			glBindVertexArray(m_nVAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);

			glViewport(0, 0, GraphicsGL::Instance()->GetWidth(), GraphicsGL::Instance()->GetHeight());
		}

		bool EffectBaseGL::CreateVertexBuffer(unsigned int nWidth, unsigned int nHeight) {

			EffectFrameBufferVertexGL arrBuffers[] = {
				{ { static_cast<float>(nWidth),  static_cast<float>(nHeight),  0.0f, 1.0f },{ 1.0f, 0.0f } },
				{ { static_cast<float>(nWidth),  0.0f,						   0.0f, 1.0f },{ 1.0f, 1.0f } },
				{ { 0.0f,					     0.0f,						   0.0f, 1.0f },{ 0.0f, 1.0f } },
				{ { 0.0f,					     static_cast<float>(nHeight),  0.0f, 1.0f },{ 0.0f, 0.0f } },
			};

			return OpenGLHelper::Instance()->CreateVertextBuffer(arrBuffers, sizeof(arrBuffers), m_nVAO, m_nVBO, m_nEBO, []() -> void {
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(EffectFrameBufferVertexGL), reinterpret_cast<void*>(offsetof(EffectFrameBufferVertexGL, m_v4Position)));
				glEnableVertexAttribArray(0);

				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(EffectFrameBufferVertexGL), reinterpret_cast<void*>(offsetof(EffectFrameBufferVertexGL, m_v2Texture)));
				glEnableVertexAttribArray(1);
			});
		}

		EffectBaseGL::~EffectBaseGL() {
			TextureGL::Release(m_pTexture);
			delete m_pShader;

			if (m_nVAO) {
				glDeleteVertexArrays(1, &m_nVAO);
			}

			if (m_nVBO) {
				glDeleteBuffers(1, &m_nVBO);
			}

			if (m_nEBO) {
				glDeleteBuffers(1, &m_nEBO);
			}

		}
	}
}
