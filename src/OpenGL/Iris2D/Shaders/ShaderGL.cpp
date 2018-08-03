//
// Created by Huisama on 2018/4/19.
//

#include "OpenGL/Iris2D/Shaders/ShaderGL.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "OpenGL/Common.h"
#include <glm/gtc/type_ptr.hpp>

#include <limits>

namespace Iris2D {
	void ShaderGL::Use() {
		glUseProgram(m_nID);
	}

	void ShaderGL::Unuse() {
		glUseProgram(0);
	}

	void ShaderGL::SetBool(const std::string &strUniformName, bool bValue) const {
		glUniform1i(glGetUniformLocation(m_nID, strUniformName.c_str()), bValue ? 1 : 0);
	}

	void ShaderGL::SetInt(const std::string &strUniformName, int nValue) const {
		glUniform1i(glGetUniformLocation(m_nID, strUniformName.c_str()), nValue);
	}

	void ShaderGL::SetFloat(const std::string &strUniformName, float fValue) const {
		auto id = glGetUniformLocation(m_nID, strUniformName.c_str());
		glUniform1f(id, fValue);
	}

	GLuint ShaderGL::LoadShader(const std::string &strPath, std::function<GLuint()> fGenerate) const {
		auto strCode = this->GetShaderCode(strPath);

		if (strCode.empty()) {
			return std::numeric_limits<unsigned int>::max();
		}

		auto szCode = strCode.c_str();

		const auto nShader = fGenerate();
		glShaderSource(nShader, 1, &szCode, nullptr);
		glCompileShader(nShader);

		int nSuccess;
		char szLog[512];
		glGetShaderiv(nShader, GL_COMPILE_STATUS, &nSuccess);

		if (!nSuccess) {
			glGetShaderInfoLog(nShader, 512, nullptr, szLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << szLog << std::endl;
		}

		return nShader;
	}

	std::string ShaderGL::GetShaderCode(const std::string &strPath) const {
		std::ifstream fFile(strPath);
		std::stringstream ssBuffer;
		ssBuffer << fFile.rdbuf();
		std::string strContents(ssBuffer.str());
		return strContents;
	}

	bool ShaderGL::Initialize(const std::string &strVertexShaderPath, const std::string &strFragmentShaderPath) {
		const auto nVertexShader = this->LoadShader(strVertexShaderPath, []() -> GLuint {
			return glCreateShader(GL_VERTEX_SHADER);
		});

		if (nVertexShader == std::numeric_limits<unsigned int>::max()) {
			return false;
		}

		const auto nFragmentShader = this->LoadShader(strFragmentShaderPath, []() -> GLuint {
			return glCreateShader(GL_FRAGMENT_SHADER);
		});

		if (nFragmentShader == std::numeric_limits<unsigned int>::max()) {
			return false;
		}

		const unsigned int nShaderProgram = glCreateProgram();

		glAttachShader(nShaderProgram, nVertexShader);
		glAttachShader(nShaderProgram, nFragmentShader);
		glLinkProgram(nShaderProgram);

		int nSuccess;
		char szLog[512];

		glGetProgramiv(nShaderProgram, GL_LINK_STATUS, &nSuccess);
		if (!nSuccess) {
			glGetProgramInfoLog(nShaderProgram, 512, nullptr, szLog);
			std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << szLog << std::endl;

			return false;
		}

		glDeleteShader(nVertexShader);
		glDeleteShader(nFragmentShader);

		m_nID = nShaderProgram;

		return true;
	}

	void ShaderGL::SetFloat4(const std::string &strUniformName, float fR, float fG, float fB, float fA) {
		glUniform4f(glGetUniformLocation(m_nID, strUniformName.c_str()), fR, fG, fB, fA);
	}

	GLuint ShaderGL::GetID() const {
		return m_nID;
	}

	ShaderGL::~ShaderGL() {
		if (m_nID) {
			glDeleteProgram(m_nID);
		}
	}

	void ShaderGL::SetMatrix(const std::string &strUniformName, const glm::mat4 &mtMatrix) {
		auto id = glGetUniformLocation(m_nID, strUniformName.c_str());
		glUniformMatrix4fv(glGetUniformLocation(m_nID, strUniformName.c_str()), 1, GL_FALSE, glm::value_ptr(mtMatrix));
	}

	void ShaderGL::SetFloat3(const std::string &strUniformName, float fR, float fG, float fB) {
		glUniform3f(glGetUniformLocation(m_nID, strUniformName.c_str()), fR, fG, fB);
	}

	void ShaderGL::SetFloat3(const std::string &strUniformName, const glm::vec3 &v3Vector) {
		glUniform3f(glGetUniformLocation(m_nID, strUniformName.c_str()), v3Vector.x, v3Vector.y, v3Vector.z);
	}
}
