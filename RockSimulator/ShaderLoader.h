#ifndef __SHADERLOADER_H__
#define __SHADERLOADER_H__
//	Library includes.
#include <iostream>
#include <map>
#include <string>


//	Local includes.
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"


class ShaderLoader
{
public:
	static ShaderLoader& GetInstance();
	static void DestroyInstance();
	GLuint CreateProgram(char* VertexShaderFilename,
		char* FragmentShaderFilename);		

	std::map<std::string, GLuint> VertexShaders;
	std::map<std::string, GLuint> FragmentShaders;
	std::map<std::string, GLuint> Programs;


private:
	ShaderLoader(void);
	~ShaderLoader(void);

	std::string ReadShader(char *filename);
	GLuint CreateShader(GLenum shaderType,
		std::string source,
		char* shaderName);
	static ShaderLoader* s_pInstance;

};

#endif