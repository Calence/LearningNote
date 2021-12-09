#pragma  once

#include <glad/glad.h>
#include <glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	Shader(){}
	Shader(const char* pVertexShader,const char* pFragShader,bool bPath = true)
	{
		std::string szVertexSource, szFragSource;
		if (bPath)
		{
			if (NULL == pVertexShader || NULL == pFragShader)
				return;

			szVertexSource = LoadShader(pVertexShader).c_str();
			szFragSource = LoadShader(pFragShader).c_str();
		}
		else
		{
			szVertexSource = pVertexShader;
			szFragSource = pFragShader;
		}
		if (szVertexSource.empty() || szFragSource.empty())
		{
			std::cout << "Shader::Shader() error." << std::endl;
			return;
		}

		const char* sVS = szVertexSource.c_str();
		const char* sFS = szFragSource.c_str();

// 		std::cout << "Vertex source:\n" << szVertexSource << std::endl;
// 		std::cout << "Fragment source:\n" << szFragSource << std::endl;
		//create shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &sVS, NULL);
		glCompileShader(vertexShader);
		CheckCompileErrors(vertexShader,"VERTEX");

		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &sFS, NULL);
		glCompileShader(fragShader);
		CheckCompileErrors(fragShader, "FRAGMENT");

		m_nProgram = glCreateProgram();
		glAttachShader(m_nProgram, vertexShader);
		glAttachShader(m_nProgram, fragShader);
		glLinkProgram(m_nProgram);
		CheckCompileErrors(m_nProgram, "PROGRAM");

		glDeleteShader(vertexShader);
		glDeleteShader(fragShader);

	}
	~Shader(){}

	void Use()
	{
		glUseProgram(m_nProgram);
	}

	void UnUse()
	{
		glUseProgram(0);
	}

	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool(const std::string &strName, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_nProgram, strName.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string &strName, int value) const
	{
		glUniform1i(glGetUniformLocation(m_nProgram, strName.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string &strName, float value) const
	{
		glUniform1f(glGetUniformLocation(m_nProgram, strName.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string &strName, const glm::vec2 &value) const
	{
		glUniform2fv(glGetUniformLocation(m_nProgram, strName.c_str()), 1, &value[0]);
	}
	void setVec2(const std::string &strName, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(m_nProgram, strName.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string &strName, const glm::vec3 &value) const
	{
		glUniform3fv(glGetUniformLocation(m_nProgram, strName.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string &strName, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(m_nProgram, strName.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string &strName, const glm::vec4 &value) const
	{
		glUniform4fv(glGetUniformLocation(m_nProgram, strName.c_str()), 1, &value[0]);
	}
	void setVec4(const std::string &strName, float x, float y, float z, float w) const
	{
		glUniform4f(glGetUniformLocation(m_nProgram, strName.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string &strName, const glm::mat2 &mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(m_nProgram, strName.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string &strName, const glm::mat3 &mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(m_nProgram, strName.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string &strName, const glm::mat4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_nProgram, strName.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

private:
	const std::string LoadShader(const char* pShaderPath)
	{
		if (NULL == pShaderPath)
			return "";

		std::ifstream vShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			// open files
			vShaderFile.open(pShaderPath);
			std::stringstream vShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			// convert stream into string
			return vShaderStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << pShaderPath<< std::endl;
		}
		return "";
	}

	void CheckCompileErrors(GLuint shader, std::string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}

protected:
	GLuint		m_nProgram;
};