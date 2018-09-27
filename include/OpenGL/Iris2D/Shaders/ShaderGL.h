//
// Created by Huisama on 2018/4/19.
//

#ifndef _SHADER_GL_H_
#define _SHADER_GL_H_

#include <string>
#include <functional>
#include <glm/glm.hpp>

#include "OpenGL/Common.h"

namespace Iris2D {
	class ShaderGL {
	private:
		static GLuint sm_nPreShaderID;

	protected:
		GLuint m_nID = 0;

	public:
		ShaderGL() = default;
		virtual ~ShaderGL();

		virtual bool Initialize(const std::string &strVertexShaderPath, const std::string &strFragmentShaderPath);

		void Use();
		void Unuse();
		bool SetBool(const std::string& strUniformName, bool bValue);
		bool SetInt(const std::string& strUniformName, int nValue);
		bool SetInt4(const std::string& strUniformName, int nR, int nG, int nB, int nA);
		bool SetFloat(const std::string& strUniformName, float fValue);
		bool SetFloat2(const std::string& strUniformName, const glm::vec2& v2Vector);
		bool SetFloat4(const std::string& strUniformName, float fR, float fG, float fB, float fA);
		bool SetMatrix(const std::string& strUniformName, const glm::mat4& mtMatrix);
		bool SetFloat3(const std::string& strUniformName, float fR, float fG, float fB);
		bool SetFloat3(const std::string& strUniformName, const glm::vec3& v3Vector);

		GLuint GetID() const;

	private:
		GLuint LoadShader(const std::string& strPath, std::function<GLuint()> fGenerate) const;
		std::string GetShaderCode(const std::string &strPath) const;

	};
}

#endif //_SHADER_GL_H_
