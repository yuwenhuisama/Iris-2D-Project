#ifndef _H_BUFFER_MANAGER_GL_
#define _H_BUFFER_MANAGER_GL_
#include "Common/Common.h"
#include <vector>

namespace Iris2D {
	template <typename T>
	class BufferManagerGL {
	private:
		std::vector<GLuint> m_vcBuffers {};
		unsigned int m_nCurrentBufferIndex = 0;

		unsigned int m_nBufferAmount = 0;
		unsigned int m_nBufferMaxSize = 0;

	public:
		static BufferManagerGL<T>* Create(unsigned int nBufferAmount, unsigned nBufferMaxSize) {
			auto pObject = new BufferManagerGL<T>();

			pObject->m_nBufferAmount = nBufferAmount;
			pObject->m_nBufferMaxSize = nBufferMaxSize;

			pObject->InitializeBuffer();

			return pObject;
		}

		static void Release(BufferManagerGL* pManager) {
			delete pManager;
		}

	public:
		void SwitchBuffer() {
			m_nCurrentBufferIndex = (m_nCurrentBufferIndex + 1) % m_vcBuffers.size();
		}

	private:
		void InitializeBuffer() {
			for (int i = 0; i < m_nBufferAmount; ++i) {
				GLuint nVBO = 0;
				glGenBuffers(1, &nVBO);
				
				glBindBuffer(GL_ARRAY_BUFFER, nVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(T) * m_nBufferMaxSize, nullptr, GL_STREAM_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				m_vcBuffers.push_back(nVBO);;
			}
		}

	public:
		void UpdateBuffer(T* pNewMemBuffer, unsigned int nBufferSize) {
			const auto nVBO = GetCurrentVBO();

			glBindBuffer(GL_ARRAY_BUFFER, nVBO);
			const auto pBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			memcpy(pBuffer, pNewMemBuffer, sizeof(T) * nBufferSize);
			glUnmapBuffer(GL_ARRAY_BUFFER);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		T* MapBuffer() {
			const auto nVBO = GetCurrentVBO();
			glBindBuffer(GL_ARRAY_BUFFER, nVBO);
			const auto pBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
			return static_cast<T*>(pBuffer);
		}

		void UnMapBuffer() {
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		GLuint GetCurrentVBO() {
			return m_vcBuffers[m_nCurrentBufferIndex];
		}

		const std::vector<GLuint>& GetVBOs() {
			return m_vcBuffers;
		}


	private:
		BufferManagerGL() = default;
		~BufferManagerGL() {
			for (auto& nVBO : m_vcBuffers) {
				glDeleteBuffers(1, &nVBO);
			}
		}
	};
}

#endif // !_H_BUFFER_MANAGER_GL_
