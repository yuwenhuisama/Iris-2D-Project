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
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/matrix_transform.inl>
//#include <glm/ext/matrix_clip_space.inl>

#include "Common/Util/DebugUtil.h"
#include "Common/Iris2D/Sprites/SpriteIndexed.h"
#include "OpenGL/Iris2D/ViewportGL.h"
#include "OpenGL/Iris2D/Shaders/SpriteIndexedShaderGL.h"

namespace Iris2D {

	SpriteRenderQueueGL* SpriteRenderQueueGL::Instance() {
		static SpriteRenderQueueGL instance;
		return &instance;
	}

	void SpriteRenderQueueGL::InitializeSpriteStaticBuffers() {
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

			m_vcStaticVAOs.push_back(VAO);
		}
	}

	void SpriteRenderQueueGL::InitializeSpriteIndexedBuffers() {
		auto& vcVBO = m_pIndexedSpriteVertexBufferManager->GetVBOs();
		auto& vcInstanceVBO = m_pIndexedSpriteVertexInstanceBufferManager->GetVBOs();

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
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteIndexedVertexGL), reinterpret_cast<void*>(offsetof(SpriteIndexedVertexGL, m_v4Position)));
			glEnableVertexAttribArray(0);

			// Bind InstanceVAO
			glBindBuffer(GL_ARRAY_BUFFER, vcInstanceVBO[i]);

			// Vertex Instance Attribute
			glVertexAttribPointer(1, sizeof(glm::vec4) / sizeof(glm::float32), GL_FLOAT, GL_FALSE, sizeof(SpriteIndexedInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteIndexedInstanceAttributeGL, m_v4TextureA)));
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(2, sizeof(glm::vec4) / sizeof(glm::float32), GL_FLOAT, GL_FALSE, sizeof(SpriteIndexedInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteIndexedInstanceAttributeGL, m_v4TextureB)));
			glEnableVertexAttribArray(2);

			glVertexAttribPointer(3, sizeof(glm::vec2) / sizeof(glm::float32), GL_FLOAT, GL_FALSE, sizeof(SpriteIndexedInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteIndexedInstanceAttributeGL, m_svAttribute) + offsetof(SpriteInstanceAttributeGL, m_v2OrgPosition)));
			glEnableVertexAttribArray(3);

			glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(SpriteIndexedInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteIndexedInstanceAttributeGL, m_svAttribute) + offsetof(SpriteInstanceAttributeGL, m_f32Opacity)));
			glEnableVertexAttribArray(4);

			glVertexAttribPointer(5, 1, GL_INT, GL_FALSE, sizeof(SpriteIndexedInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteIndexedInstanceAttributeGL, m_svAttribute) + offsetof(SpriteInstanceAttributeGL, m_i32Mirror)));
			glEnableVertexAttribArray(5);

			glVertexAttribPointer(6, sizeof(glm::vec4) / sizeof(glm::float32), GL_FLOAT, GL_FALSE, sizeof(SpriteIndexedInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteIndexedInstanceAttributeGL, m_svAttribute) + offsetof(SpriteInstanceAttributeGL, m_v4Rect)));
			glEnableVertexAttribArray(6);

			glVertexAttribPointer(7, sizeof(glm::ivec4) / sizeof(glm::int32), GL_INT, GL_FALSE, sizeof(SpriteIndexedInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteIndexedInstanceAttributeGL, m_svAttribute) + offsetof(SpriteInstanceAttributeGL, m_v4Tone)));
			glEnableVertexAttribArray(7);

			glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteIndexedInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteIndexedInstanceAttributeGL, m_svAttribute) + offsetof(SpriteInstanceAttributeGL, m_v4TranslateAndZoom)));
			glEnableVertexAttribArray(8);

			glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteIndexedInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteIndexedInstanceAttributeGL, m_svAttribute) + offsetof(SpriteInstanceAttributeGL, m_mtRotation)));
			glEnableVertexAttribArray(9);

			glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteIndexedInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteIndexedInstanceAttributeGL, m_svAttribute) + offsetof(SpriteInstanceAttributeGL, m_mtRotation) + 4 * sizeof(glm::float32)));
			glEnableVertexAttribArray(10);

			glVertexAttribPointer(11, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteIndexedInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteIndexedInstanceAttributeGL, m_svAttribute) + offsetof(SpriteInstanceAttributeGL, m_mtRotation) + 8 * sizeof(glm::float32)));
			glEnableVertexAttribArray(11);

			glVertexAttribPointer(12, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteIndexedInstanceAttributeGL), reinterpret_cast<void*>(offsetof(SpriteIndexedInstanceAttributeGL, m_svAttribute) + offsetof(SpriteInstanceAttributeGL, m_mtRotation) + 12 * sizeof(glm::float32)));
			glEnableVertexAttribArray(12);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			for (int j = 1; j <= 12; ++j) {
				glVertexAttribDivisor(j, 1);
			}

			glBindVertexArray(0);

			m_vcIndexedVAOs.push_back(VAO);
		}
	}

	bool SpriteRenderQueueGL::Initialize() {
		m_pStaticSpriteInstanceBufferManager = BufferManagerGL<SpriteInstanceAttributeGL>::Create(IR_VERTEX_BUFFER_NUM, 128);
		m_pStaticSpriteVertexBufferManager = BufferManagerGL<SpriteVertexGL>::Create(IR_VERTEX_BUFFER_NUM, 4);
		m_pIndexedSpriteVertexBufferManager = BufferManagerGL<SpriteIndexedVertexGL>::Create(IR_VERTEX_BUFFER_NUM, 4);
		m_pIndexedSpriteVertexInstanceBufferManager = BufferManagerGL<SpriteIndexedInstanceAttributeGL>::Create(IR_VERTEX_BUFFER_NUM, 128);

		// Initialize EBO
		static unsigned int arrIndices[] = {
			0, 1, 3,
			1, 2, 3,
		};

		glGenBuffers(1, &m_nEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(arrIndices), arrIndices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		InitializeSpriteStaticBuffers();
		InitializeSpriteIndexedBuffers();

		return true;
	}

	bool SpriteRenderQueueGL::Release() {
		BufferManagerGL<SpriteInstanceAttributeGL>::Release(m_pStaticSpriteInstanceBufferManager);
		BufferManagerGL<SpriteVertexGL>::Release(m_pStaticSpriteVertexBufferManager);
		BufferManagerGL<SpriteIndexedVertexGL>::Release(m_pIndexedSpriteVertexBufferManager);
		BufferManagerGL<SpriteIndexedInstanceAttributeGL>::Release(m_pIndexedSpriteVertexInstanceBufferManager);

		if (m_nEBO) {
			glDeleteBuffers(1, &m_nEBO);
		}
		return true;
	}

	ResultCode SpriteRenderQueueGL::Push(const RenderCommand& rcCommand) {
		auto eResult = ResultCode::IRR_Success;

		if (rcCommand.m_eTargetType == TargetType::End) {
			if (!m_dqRenderCommandQueue.empty()) {
				eResult = Render();
				m_dqRenderCommandQueue.clear();
			}
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
						auto pFirst = static_cast<SpriteIndexedGL*>(rcCurrent.m_pSprite);
						const auto pSecond = static_cast<SpriteIndexedGL*>(rcCommand.m_pSprite);

						if (pFirst->CheckMergeableWith(pSecond)) {
							m_dqRenderCommandQueue.push_back(rcCommand);

							if (m_dqRenderCommandQueue.size() >= IR_MAX_BATCH_SPRITE_SIZE) {
								Render();
								m_dqRenderCommandQueue.clear();
							}
						}
						else {
							Render();
							m_dqRenderCommandQueue.clear();
							m_dqRenderCommandQueue.push_back(rcCommand);
						}
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
			return RenderSpriteIndices();
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
		for (size_t i = 0; i < dqQueue.size(); ++i) {
			pInstanceBuffer[i] = static_cast<SpriteStaticGL*>(dqQueue[i].m_pSprite)->GetInstanceAttribute();
		}
		m_pStaticSpriteInstanceBufferManager->UnMapBuffer();

		const auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(pViewport->GetWidth()), static_cast<float>(pViewport->GetHeight()), 0.0f, 0.0f, 9999.0f);
		glViewport(0, 0, pViewport->GetWidth(), pViewport->GetHeight());
		pShader->SetProjectionMatrix(c_mt4Projection);

		const auto nVAO = m_vcStaticVAOs[m_nCurrentStaticVAOIndex];
		glBindVertexArray(nVAO);
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, dqQueue.size());
#if !defined(NDEBUG) | defined(_DEBUG)
		DebugCounter::Instance()->IncreaseDrawCallTimesPerFrame();
#endif
		glBindVertexArray(0);

		m_pStaticSpriteVertexBufferManager->SwitchBuffer();
		m_pStaticSpriteInstanceBufferManager->SwitchBuffer();
		m_nCurrentStaticVAOIndex = (m_nCurrentStaticVAOIndex + 1) % IR_VERTEX_BUFFER_NUM;

		return IRR_Success;
	}

	ResultCode SpriteRenderQueueGL::RenderSpriteIndices() {
		const auto& dqQueue = m_dqRenderCommandQueue;
		const auto& rcFirst = m_dqRenderCommandQueue.front();

		// Generate
		//const auto pEffectTexture = static_cast<SpriteIndexedGL*>(rcFirst.m_pSprite)->RenderEffect();
		auto pTexture = GetProxied<BitmapGL*>(rcFirst.m_pSprite->GetBitmap())->GetTexture();
		//if (pEffectTexture) {
		//	pTexture = pEffectTexture;
		//}

		const auto pShader = SpriteIndexedShaderGL::Instance();
		pShader->Use();

		pTexture->UseTexture();

		const auto pViewport = rcFirst.m_pSprite->GetViewport();

		// Update Buffer
		const auto nWidth = pTexture->GetWidth();
		const auto nHeight = pTexture->GetHeight();

		SpriteIndexedVertexGL arrBuffers[] = {
			{ { static_cast<float>(nWidth),  static_cast<float>(nHeight),  0.0f, 1.0f } },
			{ { static_cast<float>(nWidth),  0.0f,						   0.0f, 1.0f } },
			{ { 0.0f,					     0.0f,						   0.0f, 1.0f } },
			{ { 0.0f,					     static_cast<float>(nHeight),  0.0f, 1.0f } },
		};

		m_pIndexedSpriteVertexBufferManager->UpdateBuffer(arrBuffers, 4);

		const auto pBuffer = m_pIndexedSpriteVertexInstanceBufferManager->MapBuffer();

//		std::cout << dqQueue.size();
		for (size_t i = 0; i < dqQueue.size(); ++i) {
			pBuffer[i] = static_cast<SpriteIndexedGL*>(dqQueue[i].m_pSprite)->GetInstanceAttribute();
		}

		m_pIndexedSpriteVertexInstanceBufferManager->UnMapBuffer();

		const auto c_mt4Projection = glm::ortho(0.0f, static_cast<float>(pViewport->GetWidth()), static_cast<float>(pViewport->GetHeight()), 0.0f, 0.0f, 9999.0f);
		glViewport(0, 0, pViewport->GetWidth(), pViewport->GetHeight());
		pShader->SetProjectionMatrix(c_mt4Projection);

		const auto nVAO = m_vcIndexedVAOs[m_nCurrentIndexVAOIndex];
		glBindVertexArray(nVAO);
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, dqQueue.size());
//		glDrawElementsInstancedBaseVertexBaseInstance(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, dqQueue.size(), 0, 0);

		// glDrawElements(GL_TRIANGLES, 6 * dqQueue.size(), GL_UNSIGNED_INT, nullptr)
#if !defined(NDEBUG) | defined(_DEBUG)
		DebugCounter::Instance()->IncreaseDrawCallTimesPerFrame();
#endif
		glBindVertexArray(0);

		m_pIndexedSpriteVertexBufferManager->SwitchBuffer();
		m_pIndexedSpriteVertexInstanceBufferManager->SwitchBuffer();
		m_nCurrentIndexVAOIndex = (m_nCurrentIndexVAOIndex + 1) % IR_VERTEX_BUFFER_NUM;

		return IRR_Success;
	}
}
