#pragma once

#include <iostream>
#include <map>
#include <string>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

class ShaderLoader
{
	private:
		ShaderLoader(void);
		~ShaderLoader(void);

		std::string ReadShader(char *filename);
		GLuint CreateShader(GLenum shaderType,
			std::string source,
			char* shaderName);
		static ShaderLoader* s_pInstance;

	public:
		static ShaderLoader& GetInstance();
		static void DestroyInstance();
		GLuint CreateProgram(char* VertexShaderFilename,
			char* FragmentShaderFilename);		

		std::map<std::string, GLuint> VertexShaders;
		std::map<std::string, GLuint> FragmentShaders;
		std::map<std::string, GLuint> Programs;
};
