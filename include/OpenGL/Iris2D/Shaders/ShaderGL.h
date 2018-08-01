//
// Created by Huisama on 2018/4/19.
//

#ifndef _SHADER_GL_H_
#define _SHADER_GL_H_

#include <string>
#include <functional>
#include <glm/detail/type_mat.hpp>
#include <glm/glm.hpp>

#include "OpenGL/Common.h"

namespace Iris2D {
	class ShaderGL {
	protected:
		GLuint m_nID = 0;

	public:
		ShaderGL() = default;
		virtual ~ShaderGL();

		virtual bool Initialize(const std::string &strVertexShaderPath, const std::string &strFragmentShaderPath);

		void Use();
		void Unuse();
		void SetBool(const std::string& strUniformName, bool bValue) const;
		void SetInt(const std::string& strUniformName, int nValue) const;
		void SetFloat(const std::string& strUniformName, float fValue) const;
		void SetFloat4(const std::string& strUniformName, float fR, float fG, float fB, float fA);
		void SetMatrix(const std::string& strUniformName, const glm::mat4& mtMatrix);
		void SetFloat3(const std::string& strUniformName, float fR, float fG, float fB);
		void SetFloat3(const std::string& strUniformName, const glm::vec3& v3Vector);

		GLUnit GetID() const;

	private:
		GLUnit LoadShader(const std::string& strPath, std::function<GLuint()> fGenerate) const;
		std::string GetShaderCode(const std::string &strPath) const;

	};
}

#endif //_SHADER_GL_H_
