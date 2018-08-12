#pragma once

#include "glew.h"
#include "freeglut.h"
#include <iostream>
#include <map>
#include <string>
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

class ShaderLoader
{
	private:

		std::string ReadShader(char *filename);
		GLuint CreateShader(GLenum shaderType,
			std::string source,
			char* shaderName);

	public:
		ShaderLoader(void);
		~ShaderLoader(void);
		GLuint CreateProgram(char* VertexShaderFilename,
			char* FragmentShaderFilename);		

		std::map<std::string, GLuint> VertexShaders;
		std::map<std::string, GLuint> FragmentShaders;
		std::map<std::string, GLuint> Programs;
};
