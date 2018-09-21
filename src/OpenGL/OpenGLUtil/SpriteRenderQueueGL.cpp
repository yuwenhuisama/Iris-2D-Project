#include "OpenGL/OpenGLUtil/SpriteRenderQueueGL.h"
#include "OpenGL/Iris2D/Sprites/SpriteStaticGL.h"
#include "OpenGL/Iris2D/Sprites/SpriteIndexedGL.h"
#include "OpenGL/Iris2D/BitmapGL.h"
#include "OpenGL/Iris2D/Shaders/SpriteShaderGL.h"
#include "OpenGL/OpenGLUtil/OpenGLHelper.h"
#include "OpenGL/OpenGLUtil/TextureGL.h"

#include "Common/Iris2D/Bitmap.h"
#include "Common/Iris2D/Viewport.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.inl>

namespace Iris2D {

	SpriteRenderQueueGL* SpriteRenderQueueGL::Instance() {
		static SpriteRenderQueueGL instance;
		return &instance;
	}

	ResultCode SpriteRenderQueueGL::Push(const RenderCommand& rcCommand) {
		auto eResult = ResultCode::IRR_Success;

		if (rcCommand.m_eTargetType == TargetType::End) {
			eResult = Render();
			m_dqRenderCommandQueue.clear();
		}
		else {
			if (m_dqRenderCommandQueue.empty()) {
				m_dqRenderCommandQueue.push_back(rcCommand);
			}
			else {
				auto& rcCurrent = m_dqRenderCommandQueue.back();

				if (rcCurrent.m_eTargetType == rcCommand.m_eTargetType) {
					switch (rcCurrent.m_eTargetType) {
					case TargetType::SpriteStatic:
					{
						auto pFirst = static_cast<SpriteStaticGL*>(rcCurrent.m_pSprite);
						const auto pSecond = static_cast<SpriteStaticGL*>(rcCommand.m_pSprite);

						if (pFirst->CheckMergeableWith(pSecond)) {
							m_dqRenderCommandQueue.push_back(rcCommand);
						} else {
							Render();
							m_dqRenderCommandQueue.clear();
							m_dqRenderCommandQueue.push_back(rcCommand);
						}
					}
					break;
					case TargetType::SpriteIndexed:
					{
					}
					case TargetType::None:
					case TargetType::End:
					default:
						break;
					}
				}
				else {
					// Break selecting
					Render();
					m_dqRenderCommandQueue.clear();
					m_dqRenderCommandQueue.push_back(rcCommand);
				}
			}
		}

		return eResult;
	}

	ResultCode SpriteRenderQueueGL::Push(RenderCommand&& rcCommand) {
		auto eResult = ResultCode::IRR_Success;

		if (rcCommand.m_eTargetType == TargetType::End) {
			eResult = Render();
			m_dqRenderCommandQueue.clear();
		}
		else {
			if (m_dqRenderCommandQueue.empty()) {
				m_dqRenderCommandQueue.push_back(rcCommand);
			}
			else {
				auto& rcCurrent = m_dqRenderCommandQueue.back();

				if (rcCurrent.m_eTargetType == rcCommand.m_eTargetType) {
					switch (rcCurrent.m_eTargetType) {
					case TargetType::SpriteStatic:
					{
						auto pFirst = static_cast<SpriteStaticGL*>(rcCurrent.m_pSprite);
						const auto pSecond = static_cast<SpriteStaticGL*>(rcCommand.m_pSprite);

						if (pFirst->CheckMergeableWith(pSecond)) {
							m_dqRenderCommandQueue.push_back(rcCommand);
						}
						else {
							Render();
							m_dqRenderCommandQueue.clear();
							m_dqRenderCommandQueue.push_back(rcCommand);
						}
					}
					break;
					case TargetType::SpriteIndexed:
					{
					}
					case TargetType::None:
					case TargetType::End:
					default:
						break;
					}
				}
				else {
					// Break selecting
					Render();
					m_dqRenderCommandQueue.clear();
					m_dqRenderCommandQueue.push_back(rcCommand);
				}
			}
		}

		return IRR_Success;
	}


	ResultCode SpriteRenderQueueGL::Render() {

		const auto& rcFirst = m_dqRenderCommandQueue.front();

		switch (rcFirst.m_eTargetType) {
		case TargetType::SpriteStatic:
			return RenderSpriteStatics();
		case TargetType::SpriteIndexed:
			break;
		case TargetType::None:
			return IRR_WrongRenderCommand;
		case TargetType::End:
			break;
		default:
			break;
		}

		return IRR_Success;
	}

	ResultCode SpriteRenderQueueGL::RenderSpriteStatics() {
		const auto& dqQueue = m_dqRenderCommandQueue;
		const auto& rcFirst = m_dqRenderCommandQueue.front();

		// Generate
		const auto pEffectTexture = static_cast<SpriteStaticGL*>(rcFirst.m_pSprite)->RenderEffect();
		auto pTexture = GetProxied<BitmapGL*>(rcFirst.m_pSprite->GetBitmap())->GetTexture();
		if (pEffectTexture) {
			pTexture = pEffectTexture;
		}

		const auto pShader = SpriteShaderGL::Instance();
		pShader->Use();

		pTexture->UseTexture();

		const auto pViewport = rcFirst.m_pSprite->GetViewport();

		// Generate instance buffer
		// TODO: Use memory pool
		const auto pBuffer = new SpriteInstanceAttributeGL[m_dqRenderCommandQueue.size()];

		for (size_t i = 0; i < m_dqRenderCommandQueue.size(); ++i) {
			pBuffer[i] = static_cast<SpriteStaticGL*>(m_dqRenderCommandQueue[i].m_pSprite)->GetInstanceAttribute();
		}

		GLuint nVAO = 0;
		GLuint nVBO = 0;
		GLuint nEBO = 0;
		GLuint nInstanceVBO = 0;

		CreateSpriteStaticVertexBuffer(pTexture, nVAO, nVBO, nEBO, nInstanceVBO, pBuffer, m_dqRenderCommandQueue.size());

		const auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(pViewport->GetWidth()), static_cast<float>(pViewport->GetHeight()), 0.0f, 0.0f, 9999.0f);

		glViewport(0, 0, pViewport->GetWidth(), pViewport->GetHeight());

		pShader->SetProjectionMatrix(c_mt4Projection);

		glBindVertexArray(nVAO);
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, m_dqRenderCommandQueue.size());
		glBindVertexArray(0);

		delete[] pBuffer;

		glDeleteVertexArrays(1, &nVAO);
		glDeleteBuffers(1, &nVBO);
		glDeleteBuffers(1, &nEBO);
		glDeleteBuffers(1, &nInstanceVBO);

		return IRR_Success;
	}

	bool SpriteRenderQueueGL::CreateSpriteStaticVertexBuffer(const TextureGL* pTexture, GLuint& nVAO, GLuint& nVBO, GLuint& nEBO, GLuint& nInstanceVBO, SpriteInstanceAttributeGL* pAttribArray, unsigned int nArraySize) {
		const auto nWidth = pTexture->GetWidth();
		const auto nHeight = pTexture->GetHeight();

		SpriteVertexGL arrBuffers[] = {
			{ { static_cast<float>(nWidth),  static_cast<float>(nHeight),  0.0f, 1.0f },{ 1.0f, 1.0f } },
			{ { static_cast<float>(nWidth),  0.0f,						   0.0f, 1.0f },{ 1.0f, 0.0f } },
			{ { 0.0f,					     0.0f,						   0.0f, 1.0f },{ 0.0f, 0.0f } },
			{ { 0.0f,					     static_cast<float>(nHeight),  0.0f, 1.0f },{ 0.0f, 1.0f } },
		};

		static unsigned int arrIndiecs[] = {
			0, 1, 3,
			1, 2, 3,
		};

		GLuint InstanceVBO;
		glGenBuffers(1, &InstanceVBO);
		glBindBuffer(GL_ARRAY_BUFFER, InstanceVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(SpriteInstanceAttributeGL) * nArraySize, pAttribArray, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLuint VAO, VBO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(arrIndiecs), arrIndiecs, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(arrBuffers), arrBuffers, GL_STATIC_DRAW);

		// Vertex Attribute
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteVertexGL), reinterpret_cast<void*>(offsetof(SpriteVertexGL, m_v4Position)));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVertexGL), reinterpret_cast<void*>(offsetof(SpriteVertexGL, m_v2Texture)));
		glEnableVertexAttribArray(1);

		// Vertex Attribute Array
		glBindBuffer(GL_ARRAY_BUFFER, InstanceVBO);

		glVertexAttribPointer(2, sizeof(glm::vec2) / sizeof(glm::float32), GL_FLOAT, GL_FALSE, sizeof(SpriteInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteInstanceAttributeGL, m_v2OrgPosition)));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(SpriteInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteInstanceAttributeGL, m_f32Opacity)));
		glEnableVertexAttribArray(3);

		glVertexAttribPointer(4, 1, GL_INT, GL_FALSE, sizeof(SpriteInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteInstanceAttributeGL, m_i32Mirror)));
		glEnableVertexAttribArray(4);

		glVertexAttribPointer(5, sizeof(glm::vec4) / sizeof(glm::float32), GL_FLOAT, GL_FALSE, sizeof(SpriteInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteInstanceAttributeGL, m_v4Rect)));
		glEnableVertexAttribArray(5);

		glVertexAttribPointer(6, sizeof(glm::ivec4) / sizeof(glm::int32), GL_INT, GL_FALSE, sizeof(SpriteInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteInstanceAttributeGL, m_v4Tone)));
		glEnableVertexAttribArray(6);

		glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteInstanceAttributeGL, m_v4TranslateAndZoom)));
		glEnableVertexAttribArray(7);

		glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteInstanceAttributeGL, m_mtRotation)));
		glEnableVertexAttribArray(8);

		glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteInstanceAttributeGL, m_mtRotation) + 4 * sizeof(glm::float32)));
		glEnableVertexAttribArray(9);

		glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteInstanceAttributeGL, m_mtRotation) + 8 * sizeof(glm::float32)));
		glEnableVertexAttribArray(10);

		glVertexAttribPointer(11, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteInstanceAttributeGL, m_mtRotation) + 12 * sizeof(glm::float32)));
		glEnableVertexAttribArray(11);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		for (int i = 2; i <= 11; ++i) {
			glVertexAttribDivisor(i, 1);
		}

		glBindVertexArray(0);

		nVAO = VAO;
		nVBO = VBO;
		nEBO = EBO;
		nInstanceVBO = InstanceVBO;

		return true;
	}
}
