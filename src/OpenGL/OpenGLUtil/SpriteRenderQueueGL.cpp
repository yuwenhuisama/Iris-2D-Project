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

	bool SpriteRenderQueueGL::Initialize() {
		m_pStaticSpriteInstanceBufferManager = BufferManagerGL<SpriteInstanceAttributeGL>::Create(IR_VERTEX_BUFFER_NUM, IR_VERTEX_BUFFER_MAX_SIZE);
		m_pStaticSpriteVertexBufferManager = BufferManagerGL<SpriteVertexGL>::Create(IR_VERTEX_BUFFER_NUM, 4);

		// Initialize EBO
		static unsigned int arrIndices[] = {
			0, 1, 3,
			1, 2, 3,
		};

		glGenBuffers(1, &m_nEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(arrIndices), arrIndices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		auto& vcVBO = m_pStaticSpriteVertexBufferManager->GetVBOs();
		auto& vcInstanceVBO = m_pStaticSpriteInstanceBufferManager->GetVBOs();

		// Initialize VAOs
		for (size_t i = 0; i < IR_VERTEX_BUFFER_NUM; ++i) {
			GLuint VAO;
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);

			// Bind EBO
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nEBO);

			// Bind VAO
			glBindBuffer(GL_ARRAY_BUFFER, vcVBO[i]);

			// Vertex Attribute
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteVertexGL), reinterpret_cast<void*>(offsetof(SpriteVertexGL, m_v4Position)));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVertexGL), reinterpret_cast<void*>(offsetof(SpriteVertexGL, m_v2Texture)));
			glEnableVertexAttribArray(1);

			// Bind InstanceVAO
			glBindBuffer(GL_ARRAY_BUFFER, vcInstanceVBO[i]);

			// Vertex Instance Attribute
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

			for (int j = 2; j <= 11; ++j) {
				glVertexAttribDivisor(j, 1);
			}

			glBindVertexArray(0);

			m_vcVAOs.push_back(VAO);
		}

		return true;
	}

	bool SpriteRenderQueueGL::Release() {
		BufferManagerGL<SpriteInstanceAttributeGL>::Release(m_pStaticSpriteInstanceBufferManager);
		BufferManagerGL<SpriteVertexGL>::Release(m_pStaticSpriteVertexBufferManager);

		if (m_nEBO) {
			glDeleteBuffers(1, &m_nEBO);
		}
		return true;
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

							if (m_dqRenderCommandQueue.size() >= IR_MAX_BATCH_SPRITE_SIZE) {
								Render();
								m_dqRenderCommandQueue.clear();
							}
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

		// Update Buffer
		const auto nWidth = pTexture->GetWidth();
		const auto nHeight = pTexture->GetHeight();

		SpriteVertexGL arrBuffers[] = {
			{ { static_cast<float>(nWidth),  static_cast<float>(nHeight),  0.0f, 1.0f },{ 1.0f, 1.0f } },
			{ { static_cast<float>(nWidth),  0.0f,						   0.0f, 1.0f },{ 1.0f, 0.0f } },
			{ { 0.0f,					     0.0f,						   0.0f, 1.0f },{ 0.0f, 0.0f } },
			{ { 0.0f,					     static_cast<float>(nHeight),  0.0f, 1.0f },{ 0.0f, 1.0f } },
		};

		m_pStaticSpriteVertexBufferManager->UpdateBuffer(arrBuffers, 4);
		const auto pInstanceBuffer = m_pStaticSpriteInstanceBufferManager->MapBuffer();
		for (size_t i = 0; i < m_dqRenderCommandQueue.size(); ++i) {
			pInstanceBuffer[i] = static_cast<SpriteStaticGL*>(m_dqRenderCommandQueue[i].m_pSprite)->GetInstanceAttribute();
		}
		m_pStaticSpriteInstanceBufferManager->UnMapBuffer();

		const auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(pViewport->GetWidth()), static_cast<float>(pViewport->GetHeight()), 0.0f, 0.0f, 9999.0f);
		glViewport(0, 0, pViewport->GetWidth(), pViewport->GetHeight());
		pShader->SetProjectionMatrix(c_mt4Projection);

		const auto nVAO = m_vcVAOs[m_nCurrentVAOIndex];
		glBindVertexArray(nVAO);
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, m_dqRenderCommandQueue.size());
		glBindVertexArray(0);

		m_pStaticSpriteVertexBufferManager->SwitchBuffer();
		m_pStaticSpriteInstanceBufferManager->SwitchBuffer();
		m_nCurrentVAOIndex = (m_nCurrentVAOIndex + 1) % IR_VERTEX_BUFFER_NUM;

		return IRR_Success;
	}
}
